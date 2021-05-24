#include "EUP.h"
#include "funcoes_EUP.h"
#include "Paciente.h"
#include "funcoes_Paciente.h"
#include "Paciente_Ler_e_Escrever_ListaEncadeada.h"
//#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Menu de operacoes para um dado paciente.
void menu_paciente(Paciente *p){
  printf("----MENU PACIENTE----\n");
  printf("---------------------------\nNome  | %s \nidade | %d \ncpf  | %lu \nstatus| %d\n---------------------------\nEUP   | %d \n---------------------------\nPSCP  | %d\nPSLP  | %d\nPSGRT | %d\n---------------------------\nSOFA  | %d\nICC   | %d\nCFS   | %d\nKPS   | %d\n---------------------------\n",p->Nome,p->idade,p->cpf,p->status,p->eup.pont_EUP, p->eup.pont_PSCP,p->eup.pont_PSLP,p->eup.pont_PSGRT,p->eup.sofa.pont_SOFA,p->eup.icc.pont_ICC,p->eup.cfs.pont_CFS,p->eup.kps.pont_KPS);

  printf("0 - voltar \n1 - mostrar dados EUP \n2 - re-calcular pontuação SOFA. \n3 - re-calcular pontuacao ICC.  \n4 - re-calcular pontuacao CFS (apenas para maiores de 60 anos).  \n5 - re-calcular pontuacao KPS.  \n6 - re-calcular pontuacao EUP (recalcula SOFA, ICC, CFS e KPS). \n. \n7 - mudar status paciente.\n");

  int escolha_menu = 0;
  do{
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
        printf("o paciente tem menos de 60 anos\n");
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
	
  printf("\n1 - Inserção de paciente\n2 - Listar Pacientes\n3 - Busca de paciente (por CPF)\n0 - Sair"); 
  
  printf("\n->");
  scanf("%d", &escolha);
  getchar();// limpa o buffer de quebras de linha indesejadas.
  return escolha;  
}

// Esta funcao ordena a lista encadeada de menor a maior pontu EUP.
void ordenar_por_EUP(Paciente *lista_p){
  if (lista_p == NULL || (lista_p)->prox_paciente == NULL){
    return;
  }
   Paciente *p = lista_p, *aux;
  int x;

  while(p != NULL){
    aux = (Paciente *) p->prox_paciente;
    while(aux != NULL){
      if(p->eup.pont_EUP > aux->eup.pont_EUP){
        x = p->eup.pont_EUP;
        p->eup.pont_EUP = aux->eup.pont_EUP;
        aux->eup.pont_EUP = x;
        /*strcpy(x,p->Nome);
        strcpy(p->Nome,aux->Nome);
        strcpy(aux->Nome,x);*/
      }
      aux = (Paciente *) aux->prox_paciente;
    }
    p = (Paciente *)p->prox_paciente;
  }
  
}

void Principal() {
	Paciente* Lista_de_Pacientes; // Lista encadeada com todos os pacientes.
  
	int escolha_menu;			        // Operacao escolhida pelo user.
	long int cpf;		    // variavel auxiliar.
	Lista_de_Pacientes = criar_lista_pacientes(); // cria uma lista vazia de valor NULL.

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
        ordenar_por_EUP(Lista_de_Pacientes);
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
	Principal();
  //teste();
	return 0;
}
