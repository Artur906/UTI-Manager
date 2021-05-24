#ifndef FUNCOES_PACIENTE_H
#define FUNCOES_PACIENTE_H

#include "Paciente.h" 
#include "EUP.h"
#include "funcoes_EUP.h"

// Cria uma lista encadeada vazia.
Paciente *criar_lista_pacientes(){
  return NULL;
}

// Esta funcao ordena a lista encadeada de pacientes em ordem alfabetica.
void ordenar(Paciente *lista_p){
  if (lista_p == NULL || (lista_p)->prox_paciente == NULL){
    return;
  }
   Paciente *p = lista_p, *aux;
  char x[40];

  while(p != NULL){
    aux = (Paciente *) p->prox_paciente;
    while(aux != NULL){
      if(strcmp(p->Nome,aux->Nome) > 0){
        strcpy(x,p->Nome);
        strcpy(p->Nome,aux->Nome);
        strcpy(aux->Nome,x);
      }
      aux = (Paciente *) aux->prox_paciente;
    }
    p = (Paciente *)p->prox_paciente;
  }

}


// Cria um paciente. retorna um ponteiro Paciente *p.
Paciente *criar_paciente(){// O usuario insere as informacoes do novo paciente (Nome e Idade).
  Paciente *p;
  p = malloc(sizeof(Paciente));

  printf("Nome: ");
  fgets(p->Nome,40,stdin);
  p->Nome[strcspn(p->Nome, "\n")] = 0;//exclui o "\n" do nome do paciente.

  printf("Idade: "); 
  scanf("%d", &p->idade);

  printf("CPF: ");
  scanf("%li", &p->cpf);
  
  
  // status padrão: -1 (nao informado).
  p->status = -1;

  // preenche os dados EUP com o valor padrao: -1 (nao informado).
  preecher_dados_EUP_com_valor_padrao(&p->eup);
  

  return p;
}

// Insere o novo paciente na primeira posição.
Paciente* inserir_paciente (Paciente *lista_p, Paciente *novo_p){
  //lista_p = lista de pacientes.
  //novo_p = novo paciente a ser inserido.
  ordenar(lista_p);
  novo_p->prox_paciente = (struct Paciente*) lista_p;
  return novo_p;
}

//lista apenas os nomes do paciente.
void listar_pacientes(Paciente *lista_p){
  Paciente *p = lista_p;
  while(p!= NULL){
    printf("nome: %s cpf: %lu\n",p->Nome,p->cpf);
    p = (Paciente *)p->prox_paciente;
  }
}

void print_dados_paciente(Paciente *p){
  printf("------------------\nNome: %s\n",p->Nome);
  printf("Idade: %d\n",p->idade);
  printf("CPF: %ld\n",p->cpf);
  print_dados_EUP(&p->eup);
}


// Funcao apenas diz se um dado paciente esta na lista de pacientes. Nao retorna nada.
Paciente * buscar_paciente_por_CPF(Paciente *lp, long int cpf){
  Paciente *p = lp;
  while(p!=NULL){
  
    if (p->cpf == cpf){
      //printf("Paciente encontrado!\n");
      return p;// retorna o endereco do paciente encontrado.
    }
    p=(Paciente *)p->prox_paciente;
  }

  //printf("Paciente NÃO encontrado.\n");
  return NULL;

}







#endif

