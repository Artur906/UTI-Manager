#include "EUP.h"
#include "funcoes_EUP.h"
#include "Paciente.h"
#include "funcoes_Paciente.h"
#include "Paciente_Ler_e_Escrever_ListaEncadeada.h"

//#include "UTI_Ler_e_Escrever_em_Arquivo.h"
//#include "Fila.h"
//#include "UTI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BRANCH DE ANDREEEEEEEEEEEEEEEEEEEE.

typedef struct Fila{
  //int ocupacao; // numero do leito que um dado paciente ocupa.
  
  long int cpf; // CPF de um dado paciente que ocupa o leito.

  struct Fila *prox_Fila; // para lista encadeada.

}Fila;

typedef struct UTI{ // struct principal para gerenciamento de leitos.
  int max_leitos;        // maximo de leitos
  int leitos_disponiveis;// leitos ainda disponiveis
  Fila *fila;// lista encadeada da fila de pacientes em leitos.
  
}UTI;


Fila * criar_Fila(){// cria uma fila vazia.
  return NULL;
}

UTI criar_UTI(){// cria uma nova UTI.
  UTI uti;
  //uti = (UTI*) malloc(sizeof(UTI));
  printf("quantos leitos existem na UTI?\n->");
  int max_leitos;
  scanf("%d",&max_leitos);
  getchar();
  uti.max_leitos = max_leitos;
  uti.leitos_disponiveis = max_leitos;
  uti.fila = criar_Fila();// crai uma fila vazia.
  return uti;
}

UTI *mudar_max_leitos_UTI(UTI *uti){// o usuario atualiza o max de leitos.
  printf("mudar leitos de UTI de %d para: \n->",uti->max_leitos);
  int novo_max_leitos;
  scanf("%d",&novo_max_leitos);
  getchar();
  if(novo_max_leitos >= uti->leitos_disponiveis){
    uti->max_leitos = novo_max_leitos;
  }
  else if(novo_max_leitos < uti->leitos_disponiveis){// caso em que o novo maximo de leitos eh menor que os leitos já ocupados.
    printf("erro: existem %d pacientes ocupando leitos no momento. Remova pacientes de leitos e tente novamente.",uti->leitos_disponiveis);
  }
  return uti;
}


// Insere um paciente (identificado por um cpf) na primeira pos na fila.
//a funcao deve ser chamada com algo assim: uti.fila = inserir_paciente_fila(&uti, Lista_de_Pacientes);
Fila* inserir_paciente_fila (UTI *uti, Paciente *lista_p){
  long int CPF;

  printf("Insira o CPF do paciente que desejas internar em um leito de UTI.\n->");
  scanf("%lu",&CPF);
  getchar();

  Fila *novo_pf = malloc(sizeof(Fila));
  novo_pf->cpf = CPF;//cria um ocupante de fila com o cpf dados de parametro.

  Paciente *p;
  p = malloc(sizeof(Paciente));
  p = buscar_paciente_por_CPF(lista_p, novo_pf->cpf);
  if(p!=NULL){//paciente foi encontrado.

    if(uti->leitos_disponiveis > 0 && p->status < 0){// Caso existam leitos disponiveis e o paciente a ser inserido ainda não ocupa um leito (status menor que 0). Logo, realizamos a inserção.
      uti->leitos_disponiveis --;// os leitos disponiveis diminuem, ja que um novo paciente ocupara um.
      novo_pf->prox_Fila = (struct Fila*) uti->fila;
      return novo_pf;//retorna a fila com o novo paciente inserido.
    }
  }
  else{
    printf("paciente (por CPF) nao encontrado\n");
  }
  return uti->fila;//retorna a fila sem alterações.
  
}

// lista o cpf dos pacientes que ocupam leitos.
void listar_fila(UTI *uti){
  Fila *f = uti->fila;
  while(f!= NULL){
    printf("Numero de leitos: %d. Numero de ocupantes: %d \n",uti->max_leitos,uti->max_leitos - uti->leitos_disponiveis);
    printf("-Ocupantes de leitos (CPF):\n");
    printf("%lu\n",f->cpf);
    f = (Fila *)f->prox_Fila;
  }
}

#define NOME_ARQUIVO_FILA "dados_Fila.bin" //guarda a lista encadeada fila.
#define NOME_ARQUIVO_UTI  "dados_UTI.bin" //guarda as outras informacoes da uti.

void FilaCleanUp(Fila *start) {
	
	Fila *freeMe = start;
	Fila *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = (Fila*)freeMe->prox_Fila;
		free(freeMe);
		freeMe = holdMe;
	}	
}

Fila *FilaReadNextFromFile(Fila *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(Fila));
		returnValue = fread(start, sizeof(Fila), 1, pFile);
		start->prox_Fila = NULL;
	} else {
		Fila *indexPac = start;
		Fila *newPac = malloc(sizeof(Fila));
		while(indexPac->prox_Fila != NULL) {
			indexPac = (Fila*)indexPac->prox_Fila;
		}
		returnValue = fread(newPac, sizeof(Fila), 1, pFile);
		indexPac->prox_Fila = newPac;
		newPac->prox_Fila = NULL;
	}
	return start;
}



//--------FUNCOES DE LER E ESCREVER ------------
// Lê no arquivo a lista encadeada salva, e a retorna.
Fila *FilaReadListIn(Fila *start) {
	
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO, "rb");
	if(pFile != NULL) {
		FilaCleanUp(start);
		start = NULL;
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(Fila)));
    printf("Encontrado(s) %d Fila(s) no arquivo '%s'.\n ",numEntries,NOME_ARQUIVO);
		
		
		int loop = 0;
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(Fila) * loop), SEEK_SET);
			start = FilaReadNextFromFile(start, pFile);
		}
	}  else {
		printf("%s FILE OPEN ERROR FOR READ\n",NOME_ARQUIVO_FILA);
	}
	
	return start;

}

// Escreve uma dada lista encadeada de Filas em um arquivo.
void FilaWriteToFile(Fila *start) {
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO, "wb");
	
	if(pFile != NULL) {
		Fila *FilaAtual = start;	
		Fila *holdProx = NULL;

		while(FilaAtual != NULL) {
			holdProx = FilaAtual->prox_Fila;
			
			FilaAtual->prox_Fila = NULL;
			
			fseek(pFile, 0, SEEK_END);
			fwrite(FilaAtual, sizeof(Fila), 1, pFile);
			//printf("Writing:%s to file\n",FilaAtual->cpf);
			FilaAtual->prox_Fila = holdProx;	
			holdProx = NULL;		
			FilaAtual = FilaAtual->prox_Fila;
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("%s FILE OPEN ERROR\n",NOME_ARQUIVO_FILA);
	}
}

void salvar_dados_UTI_arquivo(UTI *uti){
  //salva dados uti no arquivo "dados_uti.bin", e salva os dados da fila em "dados_fila.bin".
  FILE *fp;
  fp = fopen(NOME_ARQUIVO_UTI,"wb");
  fwrite(uti,sizeof(UTI),1,fp);
  FilaWriteToFile(uti->fila);
  fclose(fp);

}

UTI* carregar_dados_UTI_arquivo(UTI *uti){
  //carrega os dados uti no salvos arquivo "dados_uti.bin", e carrega a fila encadeada salva em "dados_fila.bin".
  FILE *fp;
  
  fp = fopen(NOME_ARQUIVO_UTI,"rb");

  if(fp != NULL){
    fseek(fp, 0, SEEK_SET);
    fread(uti, sizeof(UTI), 1, fp);//atente-se para &uti ou uti.
    printf("carregado max_leitos: %d \n",uti->max_leitos);
    uti->fila = NULL;
    uti->fila = FilaReadListIn(uti->fila);

  }
  else{
    printf("erro ao abrir arquivo %s \n",NOME_ARQUIVO_UTI);
  }
  fclose(fp);
  return uti;// Caso a abertura do arquivo tenha dado erro, retorna o parametro uti sem alterações. Caso tenha sucedido, retorna o que foi carregado do arquivo.
}

//LEMBRETE: se o arquivo dados_pacientes.bin for mudado por fora da aplicação (por exemplo excluido), os dados da fila de UTI (como cpf) serão de pacientes fantasmas, logo, o programa quebra. 

//LEMBRETE: coisas ruins podem acontecer se existirem pacientes de CPF igual.

//-----------TESTES------------------
void testes(){
  Paciente *p1;
  p1 = malloc(sizeof(Paciente));
  p1->status = -1;
  preecher_dados_EUP_com_valor_padrao(&p1->eup);
  p1->cpf = 123;
 

  Paciente *p2;
  p2 = malloc(sizeof(Paciente));
  p2->status = -1;
  preecher_dados_EUP_com_valor_padrao(&p2->eup);
  p2->cpf = 123;

  UTI uti;
  uti = criar_UTI();
  
  //printf("leitos: %d",uti.max_leitos);

  //uti.fila

  salvar_dados_UTI_arquivo(&uti);

}










//---------------------------------------------------
//--------------------------------------------------

//Menu de operacoes para um dado paciente.
void menu_paciente(Paciente *p){
  printf("----MENU PACIENTE----\n");
  printf("---------------------------\nNome  | %s \nidade | %d \ncpf  | %lu \nstatus| %d\n---------------------------\nEUP   | %d \n---------------------------\nPSCP  | %d\nPSLP  | %d\nPSGRT | %d\n---------------------------\nSOFA  | %d\nICC   | %d\nCFS   | %d\nKPS   | %d\n---------------------------\n",p->Nome,p->idade,p->cpf,p->status,p->eup.pont_EUP, p->eup.pont_PSCP,p->eup.pont_PSLP,p->eup.pont_PSGRT,p->eup.sofa.pont_SOFA,p->eup.icc.pont_ICC,p->eup.cfs.pont_CFS,p->eup.kps.pont_KPS);

  int escolha_menu = 0;
  do{
    

    printf("0 - voltar \n1 - mostrar dados EUP \n2 - re-calcular pontuação SOFA. \n3 - re-calcular pontuacao ICC.  \n4 - re-calcular pontuacao CFS (apenas para maiores de 60 anos).  \n5 - re-calcular pontuacao KPS.  \n6 - re-calcular pontuacao EUP (recalcula SOFA, ICC, CFS e KPS). \n. \n7 - mudar status paciente.\n");

    printf("->");
    scanf("%d",&escolha_menu);
    getchar();
    switch(escolha_menu){
      case 0:
      printf("voltando...\n");
      break;
      case 1: //printa dados EUP.
      print_dados_EUP(&p->eup);
      break;
      case 2: // re-caucular pont SOFA.
      preencher_dados_SOFA(&p->eup.sofa);
      calcular_pont_EUP(&p->eup);// recalcula a pontuacao final, ja que a pontuacao SOFA pode ter mudado.
      break;

      case 3: //re-calcular pont ICC.
      preencher_dados_ICC(&p->eup.icc);
      calcular_pont_EUP(&p->eup);// recalcula a pontuacao final, ja que a pontuacao ICC pode ter mudado.
      break;
      case 4: //re-calcular pont CFS.
      if(p->idade >= 60){
        preencher_dados_CFS(&p->eup.cfs);
        calcular_pont_EUP(&p->eup);// recalcula a pontuacao final, ja que a pontuacao CFS pode ter mudado.
      }
      else{
        printf("O paciente tem menos de 60 anos\n");
      }
      break;
      case 5: //re-calcular pont KPS.
      preencher_dados_KPS(&p->eup.kps);
      calcular_pont_EUP(&p->eup);// recalcula a pontuacao final, ja que a pontuacao KPS pode ter mudado.
      break;
      case 6: //re-calcular pont total (EUP).
      preecher_dados_EUP(&p->eup, p->idade);
      break;
      case 7:
      
      break;
      
    }

  }
  while(escolha_menu != 0);
  

}

// Menu de operacoes Principais.
int menu_principal(){
  
  printf("----MENU PRINCIPAL----\n");
  int escolha; 
	
  printf("\n1 - Inserção de paciente\n2 - Listar Pacientes\n3 - Busca de paciente (por CPF)\n4 - Listar paciente em leito\n5 - Remover paciente de leito\n6 - Adicionar paciente a leito\n7 - Número de leitos\n0 - Sair"); 
  
  printf("\n->");
  scanf("%d", &escolha);
  getchar();// limpa o buffer de quebras de linha indesejadas.
  return escolha;  
}





void Principal() {
	Paciente* Lista_de_Pacientes; // Lista encadeada com todos os pacientes.
  /*UTI *ctUTI;  // controle de leitos
  ctUTI = malloc(sizeof(UTI));
  Fila *ctFila; // lista encadeada com todos os leitos
  ctFila = malloc(sizeof(Fila));*/

  //int teste;
	int escolha_menu;			        // Operacao escolhida pelo user.
	long int cpf;		    // variavel auxiliar.
	Lista_de_Pacientes = criar_lista_pacientes(); // cria uma lista vazia de valor NULL.


  //ctFila = cria_Fila();// cria uma lista vazia de valor NULL.

  Lista_de_Pacientes = ReadListIn(Lista_de_Pacientes);// CARREGA AS INFORMACOES SALVAS NO ARQUIVO.

	Paciente *p;				          // paciente. Ponteiro auxiliar.
	p = malloc(sizeof(Paciente)); // aloca a memoria necessaria.

	// menu
	do {
		escolha_menu = menu_principal();

		switch (escolha_menu) {
      case 1: // 1 - Inserção de paciente.
        p = criar_paciente();
        preecher_dados_EUP(&p->eup, p->idade);
        Lista_de_Pacientes = inserir_paciente(Lista_de_Pacientes, p);
        
        break;
      case 2: // 2 - Listar Pacientes.
        listar_pacientes(Lista_de_Pacientes);
        break;
      case 3: // 3 - Busca de paciente (por CPF).
        printf("CPF do paciente a ser buscado: \n");
        scanf("%li", &cpf);
        p = buscar_paciente_por_CPF(Lista_de_Pacientes, cpf);
        if(p != NULL){
          menu_paciente(p);
          //print_dados_paciente(p);
        }
        else{
          printf("Paciente não encontrado\n");
        }
        
        break;
      case 4: //4 - listar paciente em leito

        
        break;

      case 5: //5 - Remover paciente de leito

        break;

      case 6: //6 - Adicionar paciente a leito

        break;
      case 7: //7 - Número de leitos


        break;

      case 0: // 0 - Sair.
        printf("Salvando dados dos pacientes e encerrando.\n");
        WriteListToFile(Lista_de_Pacientes);//SALVA AS INFORMACOES NO ARQUIVO.
        break;
      default:
        printf("Operacao inválida! \n");
        break;
		}

	} while (escolha_menu != 0);
}



int main(void) {
	//Principal();
  testes();
	return 0;
}
