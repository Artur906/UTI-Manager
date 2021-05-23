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

fila *add_leito(UTI *uti, fila *fila, Paciente *lista_p){
  UTI *aux = uti;
  //fila *aux_fila = fila;
  Paciente *auxPaci = lista_p
  long int busc_cpf;
  paciente *p;

  p = malloc(sizeof(Paciente));

  printf("qual paciente você deseja colocar no leito (insira o cpf)");
  scanf("%li",&busc_cpf);
  p = buscar_paciente_por_CPF(Lista_de_Pacientes, cpf);
  if(p != NULL){
    fila *aux_fila = p;
  }
  else{
    printf("Paciente não encontrado\n");
  }

  adicionar_fi(aux_fila);
  if (auxPaci->status < 0 || aux->capacidade > 0){
    aux_fila->ocupacao = aux->capacidade;
    aux_fila->cpf = auxPaci->CPF;
    auxPaci->status = aux_capacidade;
    auxPaci->prox_paciente;
    aux->capacidade = aux->capacidade - 1;
    adicionar_fi(aux_fila);
    aux_fila->prox_fila;

  }else if(auxPaci->status < 0){
    printf("paciente ja está em um leito");
  }else{
    printf("infelismente não há leitos");
  }


}

fila *remov_leito(UTI *p, fila **fila, Paciente *lista_p){
  UTI *aux = uti;
  fila *aux_fila = *fila;
  Paciente *auxPaci = lista_p
  long int busc_cpf;
  paciente *p;

  p = malloc(sizeof(Paciente));

  printf("qual paciente você deseja colocar no leito (insira o cpf)");
  scanf("%li",&busc_cpf);
  p = buscar_paciente_por_CPF(Lista_de_Pacientes, cpf);
  if(p != NULL){
    fila *aux_fila = p;
  }
  else{
    printf("Paciente não encontrado\n");
  }
  if(*ag == NULL){
    return 0;
  }

  fila *aux = *fila;

  if( (*fila)->cpf == busc_cpf){
     (*fila) = ( fila *) (*ag)->prox;
     free(aux);

     return 1;
  }

  fila *ante;

  while(aux){
    ante = aux;
    aux = (fila *) aux->prox_fila;
    if(aux->cpf == busc_cpf){
      ante->prox = aux->prox_fila;
      free(aux);
      return 1;
    }
  }
  return 0;
  // falta descobrir como expliur
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

