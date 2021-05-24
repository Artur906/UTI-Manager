#include "EUP.h"
#include "funcoes_EUP.h"
#include "Paciente.h"
#include "funcoes_Paciente.h"
#include "Paciente_Ler_e_Escrever_ListaEncadeada.h"
//#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Fila{
  int ocupacao;//numero do leito
  long int cpf;


  struct Fila *prox_Fila;
}Fila;

typedef struct UTI{
  int capacidade;//maximo de leitos
  
  //Fila fila;
  
}UTI;

Fila * cria_Fila(){
  return NULL;
}

//AAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAA
Fila * add_p(Fila *lista_fi){
  Paciente *p;
  p = (Paciente *) malloc(sizeof(Fila));

  lista_fi->prox_Fila = (Fila *) p;

  return lista_fi;
}



Fila *add_leito(UTI *uti,Fila **lista_fila, Paciente *lista_p){
  UTI *aux = uti;
  Fila *aux_Fila = *lista_fila;
  Paciente *auxPaci = lista_p;
  long int busc_cpf;
  Paciente *p;

  p = malloc(sizeof(Paciente));

  printf("Insira o CPF do paciente que deseja colocar no leito: ");
  scanf("%li",&busc_cpf);
  p = buscar_paciente_por_CPF(auxPaci, busc_cpf);
  if(p == NULL){
    printf("Paciente não encontrado\n");
  }
  else{
    printf("Paciente encontrado\n");
    //(*lista_fila)->cpf = lista_p->cpf;
  add_p(aux_Fila);
  if (auxPaci->status < 0 || aux->capacidade > 0){
    aux_Fila->ocupacao = aux->capacidade;
    aux_Fila->cpf = auxPaci->cpf;
    auxPaci->status = aux->capacidade;
    auxPaci = auxPaci->prox_paciente;
    aux->capacidade = aux->capacidade - 1;
    add_p(aux_Fila);
    aux_Fila = aux_Fila->prox_Fila;

  }else if(auxPaci->status < 0){
    printf("paciente ja está em um leito\n");
  }else{
    printf("infelizmente não há leitos\n");
  }
  printf("%li",aux_Fila->cpf);
  printf("paciente adicionado\n");
  return aux_Fila;
  }
  
  return *lista_fila;
}

int remov_leito2(UTI *lista_uti,Fila **lista_Fila,Paciente *lista_p){
  if(*lista_Fila == NULL){
    return 0;
  }
  long int exc_cpf;

  Fila *aux = *lista_Fila;

  printf("digite o pacinete que você que excluir");
  scanf("%li",&exc_cpf);

  if((*lista_Fila)->cpf == exc_cpf){
     (*lista_Fila) = (Fila*) (*lista_Fila)->prox_Fila;
     free(aux);

     return 1;
  }

  Fila *ante;

  while(aux){
    ante = aux;
    aux = (Fila *) aux->prox_Fila;
    if((*lista_Fila)->cpf == exc_cpf){
      ante->prox_Fila = aux->prox_Fila;
      free(aux);
      return 1;
    }
  }
  return 0;
}

Fila *remov_leito(UTI *lista_uti,Fila **lista_Fila,Paciente *lista_p){
  UTI *aux = lista_uti;
  Fila *aux_Fila = *lista_Fila;
  Paciente *auxPaci = lista_p;
  long int busc_cpf;
  Paciente *p;

  p = malloc(sizeof(Paciente));

  printf("qual paciente você deseja remover do leito (insira o cpf) ->");
  scanf("%li",&busc_cpf);
  p = buscar_paciente_por_CPF(auxPaci, busc_cpf);
  printf("\n%p",buscar_paciente_por_CPF(auxPaci, busc_cpf));
  /*if(p != NULL){
    //printf("Paciente encontrado\n");
  }
  else{
    printf("Paciente não encontrado\n");
  }*/
  printf(".");
  if(*lista_Fila == NULL){//lista_uti->fila
    printf("UTI vazia");
    //return lista_Fila;
  }
  printf("parou aqui");

  Fila *aux_rem = *lista_Fila;

  if((*lista_Fila)->cpf == busc_cpf){
     (*lista_Fila) = ( Fila *) (*lista_Fila)->prox_Fila;
     free(aux);
     printf("Paciente removido");
     //return *aux_rem;
  }

  Fila *ante;

  while(aux_rem){
    ante = (Fila *) aux_rem;
    aux_rem = (Fila *) aux_rem->prox_Fila;
    if(aux_rem->cpf == busc_cpf){
      aux_rem->prox_Fila = aux_rem->prox_Fila;
      free(aux);
      aux->capacidade = aux->capacidade + 1;
      printf("Paciente removido");
      //return *aux_rem;
    }
  }

  return aux_rem;
  // falta descobrir como expliur
  // pergunatar numero do cpf do paciente
  // dizer de qual leito ele vai sair
  // atualizar status do pacinete
}

void lista_leito(Fila *lista_Fila){
  //Fila *p = *lista_Fila;

  while( lista_Fila != NULL){
    printf("leito: %d \npaciente: %li\n",lista_Fila->ocupacao,lista_Fila->cpf);
    lista_Fila = (Fila *) lista_Fila->prox_Fila;

  }

}

void gere_uti(UTI *uti){
  printf("Digite a quantidade de leitos disponivel: \n");
  scanf("%d", &uti->capacidade);
}



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
  UTI *ctUTI;  // controle de leitos
  ctUTI = malloc(sizeof(UTI));
  Fila *ctFila; // lista encadeada com todos os leitos
  ctFila = malloc(sizeof(Fila));

  //int teste;
	int escolha_menu;			        // Operacao escolhida pelo user.
	long int cpf;		    // variavel auxiliar.
	Lista_de_Pacientes = criar_lista_pacientes(); // cria uma lista vazia de valor NULL.


  ctFila = cria_Fila();// cria uma lista vazia de valor NULL.

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
        lista_leito(ctFila);
        
        break;

      case 5: //5 - Remover paciente de leito
        remov_leito(ctUTI, &ctFila, Lista_de_Pacientes);
         /*printf("%d",teste);
         if(teste == 1){
           printf("paciente excluido");
         }*/
        break;

      case 6: //6 - Adicionar paciente a leito
        ctFila = add_leito(ctUTI,&ctFila, Lista_de_Pacientes);
        printf("%li",ctFila->cpf);
        break;
      case 7: //7 - Número de leitos
         gere_uti(ctUTI);

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

void testes(){
  Paciente *p;
  p = malloc(sizeof(Paciente));
  preecher_dados_EUP_com_valor_padrao(&p->eup);
  p->cpf = 123;
 
  //gere_uti(ctUTI);

}

int main(void) {
	Principal();
	return 0;
}
