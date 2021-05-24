#include "EUP.h"
#include "funcoes_EUP.h"
#include "Paciente.h"
#include "funcoes_Paciente.h"
#include "Paciente_Ler_e_Escrever_ListaEncadeada.h"

#include "UTI_Ler_e_Escrever_em_Arquivo.h"
//#include "Fila.h"
#include "UTI.h"
#include "funcoes_UTI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




//LEMBRETE: coisas ruins podem acontecer se existirem pacientes de CPF igual.



//---------------------------------------------------
//--------------------------------------------------

//Menu de operacoes para um dado paciente.
void menu_paciente(Paciente *p){
  printf("----MENU PACIENTE----\n");
  printf("---------------------------\nNome  | %s \nidade | %d \ncpf  | %lu \nstatus| %d\n---------------------------\nEUP   | %d \n---------------------------\nPSCP  | %d\nPSLP  | %d\nPSGRT | %d\n---------------------------\nSOFA  | %d\nICC   | %d\nCFS   | %d\nKPS   | %d\n---------------------------\n",p->Nome,p->idade,p->cpf,p->status,p->eup.pont_EUP, p->eup.pont_PSCP,p->eup.pont_PSLP,p->eup.pont_PSGRT,p->eup.sofa.pont_SOFA,p->eup.icc.pont_ICC,p->eup.cfs.pont_CFS,p->eup.kps.pont_KPS);

  int escolha_menu = 0;
  do{
    

    printf("0 - voltar para menu principal\n1 - mostrar dados EUP \n2 - re-calcular pontuação SOFA. \n3 - re-calcular pontuacao ICC.  \n4 - re-calcular pontuacao CFS (apenas para maiores de 60 anos).  \n5 - re-calcular pontuacao KPS.  \n6 - re-calcular pontuacao EUP (recalcula SOFA, ICC, CFS e KPS). \n");

    printf("->");
    scanf("%d",&escolha_menu);
    getchar();
    switch(escolha_menu){
      case 0: //volta para o menu principal.
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
      
    }

  }
  while(escolha_menu != 0);
  

}

// Menu de operacoes Principais.
int menu_principal(){
  
  printf("----MENU PRINCIPAL----\n");
  int escolha; 
	
  printf("\n1 - Inserção de paciente\n2 - Listar Pacientes\n3 - Busca de paciente (por CPF)\n4 - Listar pacientes em leito\n5 - Remover paciente de leito\n6 - Adicionar paciente a leito\n7 - Mudar quantidade máxima de leitos\n0 - Sair e Salvar"); 
  
  printf("\n->");
  scanf("%d", &escolha);
  getchar();// limpa o buffer de quebras de linha indesejadas.
  return escolha;  
}

void esperaEnter(){
  int tecla;
  printf("pressione ENTER\n");
  tecla = getchar();
    if (tecla != 13){
      //printf("pressione ENTER");
      system("clear");
    }
  /*do{
    tecla = getchar();
    if (tecla != 13){
      //printf("pressione ENTER");
      system("clear");
    }
  }while (tecla != 13);*/
  
}



void Principal() {
  UTI uti;
	Paciente* Lista_de_Pacientes; // Lista encadeada com todos os pacientes.
  int rl = carregar_dados_UTI_arquivo(&uti); //resultado da leitura: 0 = mal sucedido / 1 = bem sucedido.
  if(rl == 0){
    uti = criar_UTI();//cria uma nova uti.
  }
  Lista_de_Pacientes = criar_lista_pacientes(); // cria uma lista vazia de valor NULL.

  Lista_de_Pacientes = ReadListIn(Lista_de_Pacientes);// CARREGA AS INFORMACOES SALVAS NO ARQUIVO.

	int escolha_menu;			        // Operacao escolhida pelo user.
	long int cpf;		              // variavel auxiliar de busca.
	

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
        ordenar_por_EUP(Lista_de_Pacientes);
        esperaEnter();
        break;
      case 2: // 2 - Listar Pacientes.
        listar_pacientes(Lista_de_Pacientes);
        esperaEnter();
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
        
        esperaEnter();
        break;
      case 4: //4 - listar pacientes em leito
        listar_fila(&uti);
        esperaEnter();
        break;

      case 5: //5 - Remover paciente de leito
        uti.fila = remover_paciente_fila(&uti, Lista_de_Pacientes);
        esperaEnter();
        break;

      case 6: //6 - Adicionar paciente a leito
        uti.fila = inserir_paciente_fila(&uti, Lista_de_Pacientes);
        esperaEnter();
        break;
      case 7: //7 - Mudar quantidade máxima de leitos
        mudar_max_leitos_UTI(&uti);
        esperaEnter();
        break;

      case 0: // 0 - Sair.
        printf("Salvando dados e encerrando.\n");
        WriteListToFile(Lista_de_Pacientes);//SALVA AS INFORMACOES NO ARQUIVO.
        salvar_dados_UTI_arquivo(&uti);
        break;
      default:
        printf("Operacao inválida! \n");
        break;
		}

	} while (escolha_menu != 0);
}



int main(void) {
	Principal();
  //testes();
	return 0;
}
