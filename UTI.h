#ifndef UTI_H
#define UTI_H

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

#endif