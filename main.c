#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Paciente.h"

void testando_estrutura_e_funcoes_Paciente(){
  Paciente * Lista_de_Pacientes;//lista encadeada com todos os pacientes.
  Lista_de_Pacientes = criar_lista_pacientes();
  Paciente *p;
  p = malloc(sizeof(Paciente));

  strcpy(p->Nome, "jose");
  printf("%s",p->Nome);
  Lista_de_Pacientes = inserir_paciente(Lista_de_Pacientes, p);
}

int main(void) {
  //testando_estrutura_e_funcoes_Paciente();

  return 0;
}