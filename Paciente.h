#include <stdio.h>
#include <stdlib.h>
//#include <main.c>


typedef struct{
  char Nome[40];
  struct Paciente *prox_paciente;
  
}Paciente;

Paciente * criar_lista_pacientes(){//cria uma lista encadeada vazia.
  return NULL;
}

//insere o novo paciente na primeira posição.
Paciente* inserir_paciente (Paciente *lista_p, Paciente *novo_p){
  //lp = lista de pacientes.
  //np = novo paciente a ser inserido.
  novo_p->prox_paciente = (struct Paciente*) lista_p;
  return novo_p;
}


