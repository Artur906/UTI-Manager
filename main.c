#include "EUP.h"
#include "funcoes_EUP.h"
#include "Paciente.h"
#include "funcoes_Paciente.h"
//#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void teste(){
 
	Paciente *p;

  p = criar_paciente();

  preecher_dados_EUP(&p->eup, p->idade);

  print_dados_paciente(p);
  
}
*/




// Menu de operacoes Principais.
int menu_principal(){
  int escolha; 
	
  printf("\n1 - Inserção de paciente\n2 - Listar Pacientes\n3 - Busca de paciente (por nome)\n4 - Atualização de status de paciente\n5 - Sair"); 
  
  printf("\n->");
  scanf("%d", &escolha);
  getchar();// limpa o buffer de quebras de linha indesejadas.
  return escolha;  
}



void Principal() {
	Paciente* Lista_de_Pacientes; // Lista encadeada com todos os pacientes.
  
	int escolha_menu;			        // Operacao escolhida pelo user.
	char nome_a_buscar[40];		    // variavel auxiliar.
	Lista_de_Pacientes = criar_lista_pacientes(); // cria uma lista vazia de valor NULL.
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
		case 3: // 3 - Busca de paciente (por nome).
			printf("Nome a ser buscado: ");
			fgets(nome_a_buscar, 40, stdin);
			nome_a_buscar[strcspn(nome_a_buscar, "\n")] =
				0; // exclui o "\n" do nome do paciente.
			p = buscar_paciente_por_nome(Lista_de_Pacientes, nome_a_buscar);
      if(p != NULL){
        print_dados_paciente(p);
      }
      else{
        printf("Paciente nao encontrado\n");
      }
      
			break;
		case 4: // 4 - Atualização de status de paciente.
				// A fazer...
			break;
		case 5: // 5 - Sair.
			printf("Encerrando");
			break;
		default:
			printf("Operacao inválida!");
			break;
		}

	} while (escolha_menu != 5);
}



int main(void) {
	Principal();
  //teste();
	return 0;
}
