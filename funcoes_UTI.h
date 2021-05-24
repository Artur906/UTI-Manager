#ifndef FUNCOES_UTI_H
#define FUNCOES_UTI_H

//#include "UTI_Ler_e_Escrever_em_Arquivo.h"
//#include "Fila.h"
#include "UTI.h"




Fila * criar_Fila(){// cria uma fila vazia.
  return NULL;
}

UTI criar_UTI(){// cria uma nova UTI.
  UTI uti;
  //uti = (UTI*) malloc(sizeof(UTI));
  printf("quantos leitos existem na UTI?\n->");
  int max_leitos;
  scanf("%d",&max_leitos);
  getchar();
  uti.max_leitos = max_leitos;
  uti.leitos_disponiveis = max_leitos;
  uti.fila = criar_Fila();// crai uma fila vazia.
  return uti;
}

UTI *mudar_max_leitos_UTI(UTI *uti){// o usuario atualiza o max de leitos.
  printf("mudar leitos de UTI de %d para: \n->",uti->max_leitos);
  int novo_max_leitos;
  scanf("%d",&novo_max_leitos);
  getchar();
  if(novo_max_leitos >= uti->leitos_disponiveis){
    //o maximo de leitos eh mudados, assim como a quantidade de leitos disponiveis.
    int leitos_ocupados = uti->max_leitos - uti->leitos_disponiveis;
    uti->max_leitos = novo_max_leitos;
    uti->leitos_disponiveis = novo_max_leitos - leitos_ocupados;
  }
  else if(novo_max_leitos < uti->leitos_disponiveis){// caso em que o novo maximo de leitos eh menor que os leitos já ocupados.
    printf("erro: existem %d pacientes ocupando leitos no momento. Remova pacientes de leitos e tente novamente.",uti->leitos_disponiveis);
  }
  return uti;
}


int Fila_remover_item(Fila **f, int long CPF){
    if(!(*f)){return 0;} // encerra se não houver item na lista
        
    Fila *aux = (*f);
    if((*f)->cpf == CPF){ // verifica se posição == 0
        (*f) = (*f)->prox_Fila; // coloca a lista no próximo item
        free(aux); // limpa a memória

        return 1; // finaliza com verdadeiro
    }

    Fila *prev;
    while(aux){ // verifica se aux não chegou ao fim e percorre a posição
        prev = aux; // prev guarda valor da remoção
        aux = aux->prox_Fila;
        if(aux && aux->cpf == CPF){ // verifica o id do avião
            prev->prox_Fila = aux->prox_Fila;
            free(aux);
            return 1;
        }
    }
    return 0;
}

Fila* remover_paciente_fila(UTI *uti, Paciente *lista_p){// remove o paciente de um leito de UTI.

  long int CPF;

  printf("Insira o CPF do paciente que desejas remover de um leito de UTI.\n->");
  scanf("%lu",&CPF);
  getchar();

  Fila *novo_pf = malloc(sizeof(Fila));
  novo_pf->cpf = CPF;//cria um ocupante de fila com o cpf dados de parametro.
  //printf("novo_pf->cpf: %lu \n",novo_pf->cpf);
  Paciente *p;
  p = malloc(sizeof(Paciente));
  p = buscar_paciente_por_CPF(lista_p, CPF);
  if(p!=NULL){//paciente foi encontrado.
    if(p->status == 1){//paciente ocupava leito, logo, podemos remover-lo da internação.
      Fila_remover_item(&uti->fila,CPF);
      p->status = -1;// status muda.
      uti->leitos_disponiveis ++;//leitos disponivei aumenta.

      return uti->fila;// retorna a fila com paciente removido.
    }
    else{//paciente nao cupava leito.
      printf("paciente ja nao ocupava leito.\n");
    }
  }
  else{
    printf("paciente nao encontrado\n");
  }

  return uti->fila;
  //A fazer.

  //O user ira inserir um cpf. Feito isso, eh feita a busca por cpf para encontrar o paciente a ser removido da fila.

  //Se foi encontrado o endereco de memoria do dono do cpf, seu status eh mudado para -1 para indicar que nao está mais internado, e o seu indentificador na fila encadeada eh removido. Feito isso, a fila sem esse paciente eh retornada.

  //Se nao foi encontrado o paciente, retorna a fila sem alterações e printa uma mensagem de erro.
}


//a funcao deve ser chamada com algo assim: uti.fila = inserir_paciente_fila(&uti, Lista_de_Pacientes);
Fila* inserir_paciente_fila (UTI *uti, Paciente *lista_p){
  long int CPF;

  printf("Insira o CPF do paciente que desejas internar em um leito de UTI.\n->");
  scanf("%lu",&CPF);
  getchar();

  Fila *novo_pf = malloc(sizeof(Fila));
  novo_pf->cpf = CPF;//cria um ocupante de fila com o cpf dados de parametro.
  //printf("novo_pf->cpf: %lu \n",novo_pf->cpf);
  Paciente *p;
  p = malloc(sizeof(Paciente));
  p = buscar_paciente_por_CPF(lista_p, CPF);
  if(p!=NULL){//paciente foi encontrado.

    if(uti->leitos_disponiveis > 0 && p->status < 0){// Caso existam leitos disponiveis e o paciente a ser inserido ainda não ocupa um leito (status menor que 0). Logo, realizamos a inserção.
      uti->leitos_disponiveis --;// os leitos disponiveis diminuem, ja que um novo paciente ocupara um.
      p->status = 1;//o status muda para indicar que o paciente está internado.
      novo_pf->prox_Fila = (struct Fila*) uti->fila; // paciente eh inserido na fila.
      return novo_pf;//retorna a fila com o novo paciente inserido.
    }
    else if(uti->leitos_disponiveis == 0){
      printf("erro: UTI lotada!\n");
    }
    else if(p->status >= 0){
      printf("erro: paciente ja internado na UTI!\n");
    }
  }
  else{
    printf("paciente (por CPF) nao encontrado\n");
  }
  return uti->fila;//retorna a fila sem alterações.
  
}

// lista o cpf dos pacientes que ocupam leitos.
void listar_fila(UTI *uti){
  Fila *f = uti->fila;
  printf("Numero de leitos: %d. Numero de ocupantes: %d \n",uti->max_leitos,uti->max_leitos - uti->leitos_disponiveis);
  printf("-Ocupantes de leitos (CPF):\n");
  while(f!= NULL){
    
    printf("%lu\n",f->cpf);
    f = (Fila *)f->prox_Fila;
  }
}





//LEMBRETE: coisas ruins podem acontecer se existirem pacientes de CPF igual.

#endif