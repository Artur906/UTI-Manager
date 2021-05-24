
#ifndef FILA_H
#define  FILA_H
#include <stdio.h>
#include "EUP.h" 
#include "Paciente.h"

//TODO O CODIGO ABAIXO EH OBSOLETO, E SERA SUBSTITUIDO.


typedef struct UTI{
  int max_leitos;
  int leitos_disponiveis;
}UTI;

typedef struct fila{
  int ocupacao;
  long int cpf;


  struct fila *prox_fila;
}fila;

fila * cria_fila(){
  return NULL;
}

//AAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAA
/*
Fila * add_p(Fila *lista_fi){ //essa funcao eh bem estranha, n deu pra entender o que ela faz.
  Paciente *p;
  p = (Paciente *) malloc(sizeof(Fila));

  lista_fi->prox_Fila = (Fila *) p; // pq a gente ta adicionando um negocio do tipo Paciente a um ngc do tipo Fila? E pq um paciente sem informações?

  return lista_fi;
}
*/


Fila *add_leito(UTI *uti, Fila *lista_fila, Paciente *lista_p){ //adiciona um paciente a um leito.
  //UTI *auxUti = uti; // O uso de auxiliares para "uti" e "lista_fila" nao faz sentido, eh mais facil simplemente usar as variaveis originais.
  //Fila *auxFila = *lista_fila;
  //Paciente *auxPaci = lista_p;
  long int busc_cpf; // cpf a ser buscado.
  Paciente *p;

  p = malloc(sizeof(Paciente));

  printf("Insira o CPF do paciente que deseja colocar no leito: ");
  scanf("%li",&busc_cpf);
  p = buscar_paciente_por_CPF(lista_p, busc_cpf);
  if(p == NULL){
    printf("Paciente não encontrado\n");
    return lista_fila;
  }
  else{
    printf("Paciente encontrado\n");
    //(*lista_fila)->cpf = lista_p->cpf;

    if (p->status < 0 || uti->max_leitos > 0){// caso em que ha leitos disponiveis e o paciente ainda nao ocupa um.
      lista_fila->ocupacao = uti->max_leitos;
      lista_fila->cpf = p->cpf;
      p->status = uti->max_leitos;
      p = p->prox_paciente;
      uti->max_leitos --;// a max_leitos da UTI dimunui em 1... Nao acho que isso fassa muito sentido, ja que o numero original que indica quantos leitos o hospital tem, se perde.
      //add_p(lista_fila);
      lista_fila = lista_fila->prox_Fila;

    }else if(p->status < 0){ // caso em que o paciente ocupa um leito.
      printf("paciente ja está em um leito\n");
    }else{ // caso em que nao ha leitos.
      printf("infelizmente não há leitos\n");
    }
    printf("%li",lista_fila->cpf);
    printf("paciente adicionado\n");
    return lista_fila;
  }
  
  return lista_fila;
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
      aux->max_leitos = aux->max_leitos + 1;
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

void lista_leito(Fila *lista_Fila){ //printa todos os leitos e os pacientes ocupantes.
  //Fila *p = *lista_Fila;

  while( lista_Fila != NULL){
    printf("leito: %d \npaciente: %li\n",lista_Fila->ocupacao,lista_Fila->cpf);
    lista_Fila = (Fila *) lista_Fila->prox_Fila;

  }

}

void gere_uti(UTI *uti){ //gerenciar max_leitos da UTI.
  printf("Digite a quantidade de leitos disponivel: \n");
  scanf("%d", &uti->max_leitos);
}


#endif

