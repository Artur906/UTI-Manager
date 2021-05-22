#ifndef FILA_H
#define  FILA_H
#include <stdio.h>
#include "EUP.h" 

typedef struct{
  int capacidade;
  
}UTI;

typedef struct{
  int ocupacao;
  long int cpf;


  fila *prox_fila;
}fila;

fila * cria_fila(){
  return NULL;
}

fila * add_p(fila *lista_fi){
  paciente *p;
  p = (paciente *) malloc(sizeof(fila));

  *lista_fi->prox_fila =  (struct fila*) p;

  return *lista_fi;
}

/*fila * adicionar_fi(UTI *p, fila *fila, Paciente *lista_p){
  UTI *aux = p;
  fila *aux2 = fila;
  paciente *auxPaci = lista_p

  while (aux->capacidade > 0 || aux2 != NULL){
    adicionar_fi(aux);
    aux2->ocupacao = aux->capacidade;
    aux2->cpf = auxPaci->CPF;
    auxPaci->prox_paciente;
    aux2->prox_fila;
    aux->capacidade = aux->capacidade - 1;
  }

  return *aux2;
}*/

fila *add_leito(UTI *p, fila *fila, Paciente *lista_p){
  // pergunatar numero do cpf do paciente
  // dizer para qual leite ele vai
  // atualizar stts do pacinete

}

fila *remov_leito(UTI *p, fila *fila, Paciente *lista_p){
  // pergunatar numero do cpf do paciente
  // dizer de qual leite ele vai sair
  // atualizar stts do pacinete
}

int gere_uti(UTI *a){
  struct UTI *p = a;

  printf("Digite a quantidade de leitos disponivel: \n");
  scanf("%d", &p->capacidade);
}

int fila(UTI *a, Paciente *lista_p){
  Paciente *p = lista_p;
  UTI *aux = a;
}
#endif

