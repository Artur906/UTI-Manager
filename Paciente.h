#ifndef PACIENTE_H
#define PACIENTE_H
//#include "EUP.h" 


//Arquivo Paciente.h : Contem a estrutura "Paciente".

typedef struct Paciente{
  
  char Nome[40];
  int idade;
  long int cpf; 
  int status;
  // Um numero positivo indica qual leito o paciente esta ocupando, ex: leito 25. leito 0.
  // -1: nao esta internado na UTI.
  //  1: atualmente internado na UTI.
  // -3: alta da UTI.

  EUP eup;// esse eup contem TODAS as informacoes do paciente no que se refere seu EUP. Ou seja, tem a pontuacao geral, a pontuacao do SOFA e outros, quais comorbidades ele tem (ICC), etc.


  struct Paciente *prox_paciente;
  
}Paciente;



#endif