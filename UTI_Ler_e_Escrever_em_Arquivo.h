#ifndef UTI_LER_E_ESCREVER_EM_ARQUIVO_H
#define UTI_LER_E_ESCREVER_EM_ARQUIVO_H
#include "UTI.h"
#include "funcoes_UTI.h" //necessario apenas para usar a funcao criar_UTI.

//daria pra guardar em arquivos juntos, so que seria mais trabalhoso

//Implementação baseada no código por: BlueFeverSoft.
//GitHub: https://github.com/bluefeversoft/Beginning_C/blob/master/ch58.c
//Tutorial: https://www.youtube.com/watch?v=E88ZSIZgGR0


//Esse arquivo tem a funcao e ler e salvar dados relacionados a UTI e Fila.
#define NOME_ARQUIVO_FILA "dados_Fila.bin" //guarda a lista encadeada fila.
#define NOME_ARQUIVO_UTI  "dados_UTI.bin" //guarda as outras informacoes da uti.

void FilaCleanUp(Fila *start) {
	
	Fila *freeMe = start;
	Fila *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = (Fila*)freeMe->prox_Fila;
		free(freeMe);
		freeMe = holdMe;
	}	
}

Fila *FilaReadNextFromFile(Fila *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(Fila));
		returnValue = fread(start, sizeof(Fila), 1, pFile);
		start->prox_Fila = NULL;
	} else {
		Fila *indexPac = start;
		Fila *newPac = malloc(sizeof(Fila));
		while(indexPac->prox_Fila != NULL) {
			indexPac = (Fila*)indexPac->prox_Fila;
		}
		returnValue = fread(newPac, sizeof(Fila), 1, pFile);
		indexPac->prox_Fila = newPac;
		newPac->prox_Fila = NULL;
	}
	return start;
}



//--------FUNCOES DE LER E ESCREVER ------------
// Lê no arquivo a lista encadeada salva, e a retorna.
Fila *FilaReadListIn(Fila *start) {
	
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO_FILA, "rb");
	if(pFile != NULL) {
		FilaCleanUp(start);
		start = NULL;
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(Fila)));
    printf("Encontrado(s) %d paciente(s) ocupante(s) de leito(s) no arquivo '%s'.\n ",numEntries,NOME_ARQUIVO_FILA);
		
		
		int loop = 0;
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(Fila) * loop), SEEK_SET);
			start = FilaReadNextFromFile(start, pFile);
		}
	}  else {
		printf("%s FILE OPEN ERROR FOR READ\n",NOME_ARQUIVO_FILA);
	}
	
	return start;

}

// Escreve uma dada lista encadeada de Filas em um arquivo.
void FilaWriteToFile(Fila *start) {
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO_FILA, "wb");
	
	if(pFile != NULL) {
		Fila *FilaAtual = start;	
		Fila *holdProx = NULL;

		while(FilaAtual != NULL) {
			holdProx = FilaAtual->prox_Fila;
			
			FilaAtual->prox_Fila = NULL;
			
			fseek(pFile, 0, SEEK_END);
			fwrite(FilaAtual, sizeof(Fila), 1, pFile);
			//printf("Writing:%s to file\n",FilaAtual->cpf);
			FilaAtual->prox_Fila = holdProx;	
			holdProx = NULL;		
			FilaAtual = FilaAtual->prox_Fila;
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("%s FILE OPEN ERROR\n",NOME_ARQUIVO_FILA);
	}
}

void salvar_dados_UTI_arquivo(UTI *uti){
  //salva dados uti no arquivo "dados_uti.bin", e salva os dados da fila em "dados_fila.bin".
  FILE *fp;
  fp = fopen(NOME_ARQUIVO_UTI,"wb");
  fwrite(uti,sizeof(UTI),1,fp);
  FilaWriteToFile(uti->fila);
  fclose(fp);

}

int carregar_dados_UTI_arquivo(UTI *uti){
  //carrega os dados uti no salvos arquivo "dados_uti.bin", e carrega a fila encadeada salva em "dados_fila.bin".
  FILE *fp;
  
  fp = fopen(NOME_ARQUIVO_UTI,"rb");

  if(fp != NULL){
    fseek(fp, 0, SEEK_SET);
    fread(uti, sizeof(UTI), 1, fp);//atente-se para &uti ou uti.
    printf("carregado max_leitos: %d \n",uti->max_leitos);
    uti->fila = NULL;
    uti->fila = FilaReadListIn(uti->fila);
    return 1;
  }
  else{
    printf("erro ao abrir arquivo %s \n",NOME_ARQUIVO_UTI);
    return 0;
    //uti = criar_UTI(uti);
  }
  fclose(fp);
  //return *uti;// Caso a abertura do arquivo tenha dado erro, retorna o parametro uti sem alterações. Caso tenha sucedido, retorna o que foi carregado do arquivo.
  return 0;
}


//LEMBRETE: se o arquivo dados_pacientes.bin for mudado por fora da aplicação (por exemplo excluido), os dados da fila de UTI (como cpf) serão de pacientes fantasmas, logo, o programa "quebra". 

//ABAIXO algumas funcoes que eu(Andre) criei, mas nao funcionam corretamente e foram substituidas.

/*
//FILE *fp;


// Carrega as informacoes salvas no arquivo "NOME_ARQUIVO". Retorna uma lista encadeada de Filas.

Fila* carregar_dados_Filas_arquivo(){
  fp = fopen(NOME_ARQUIVO, "rb");// rb = modo leitura arquivo binario.
  Fila *p;
  p = malloc(sizeof(Fila));
  Fila *lista_p = criar_lista_Filas();// Cria uma lista vazia (NULL). Essa lista sera o retorno da funcao.

  if(fp != NULL){// Se o arquivo existe.
    int i = 0;
    // fread retorna um size_t representando o numero de elementos lidos com exito.
    while(fread(p, sizeof(Fila), 1, fp)){
      i++;
      p->prox_Fila = NULL;// Dentro do arquivo, cada Fila vai ter um ponteiro "prox_Fila", que tera um endereco de memoria. Porem, esse endereco deve ser descartado e substituido por um novo, ja que a aplicacao nao alocou -por ela mesma- esse espaco no qual esse ponteiro aponta.
        
      lista_p = inserir_Fila(lista_p, p);
    
      p = NULL;
      p = realloc(p,sizeof(Fila));// Muda o endereco de p. Necessario para a lista encadeada funcionar.
    }  
    printf("Encontrado(s) %d Fila(s) no arquivo '%s'.\n ",i,NOME_ARQUIVO);
    fclose(fp);
  }
  else{
    printf("O arquivo '%s' nao foi encontrado.\n",NOME_ARQUIVO);
  }

  return lista_p;
}

// salva os dados dos Filas no arquivo "NOME_ARQUIVO".
void salvar_dados_Filas_arquivo(Fila *lista_p){
  Fila *p;
  p = lista_p;
  fp = fopen(NOME_ARQUIVO, "wb");// abre em modo escrita (re-escreve todos os dados presentes no arquivo, e se ele nao existir, cria um novo).
  while(p!= NULL){
    fwrite(p,sizeof(Fila), 1, fp);
    p = (Fila*) p->prox_Fila;
  }
  fclose(fp);
}

*/

#endif