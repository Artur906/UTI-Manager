#ifndef PACIENTE_LER_E_ESCREVER_LISTAENCADEADA_H
#define PACIENTE_LER_E_ESCREVER_LISTAENCADEADA_H

#define NOME_ARQUIVO "dados_pacientes.bin"

//Implementação baseada no código por: BlueFeverSoft.
//GitHub: https://github.com/bluefeversoft/Beginning_C/blob/master/ch58.c
//Tutorial: https://www.youtube.com/watch?v=E88ZSIZgGR0


//Esse arquivo tem a funcao e ler dados e salvar dados relacionados a pacientes (struct Paciente).



void CleanUp(Paciente *start) {
	
	Paciente *freeMe = start;
	Paciente *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = (Paciente*)freeMe->prox_paciente;
		/*printf("Free Nome:%s idade:%d\n",
			freeMe->Nome,
			freeMe->idade);*/
		free(freeMe);
		freeMe = holdMe;
	}	
}

Paciente *ReadNextFromFile(Paciente *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(Paciente));
		returnValue = fread(start, sizeof(Paciente), 1, pFile);
		start->prox_paciente = NULL;
	} else {
		Paciente *indexPac = start;
		Paciente *newPac = malloc(sizeof(Paciente));
		while(indexPac->prox_paciente != NULL) {
			indexPac = (Paciente*)indexPac->prox_paciente;
		}
		returnValue = fread(newPac, sizeof(Paciente), 1, pFile);
		indexPac->prox_paciente = newPac;
		newPac->prox_paciente = NULL;
	}
	return start;
}

// Lê no arquivo a lista encadeada salva, e a retorna.
Paciente *ReadListIn(Paciente *start) {
	
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO, "rb");
	if(pFile != NULL) {
	
		CleanUp(start);
		start = NULL;
		
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(Paciente)));
    printf("Encontrado(s) %d paciente(s) no arquivo '%s'.\n ",numEntries,NOME_ARQUIVO);
		
		
		int loop = 0;
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(Paciente) * loop), SEEK_SET);
			start = ReadNextFromFile(start, pFile);
		}
	}  else {
		printf("FILE OPEN ERROR FOR READ\n");
	}
	
	return start;

}

// Escreve uma dada lista encadeada de pacientes em um arquivo.
void WriteListToFile(Paciente *start) {
	FILE *pFile;
	pFile = fopen(NOME_ARQUIVO, "wb");
	
	if(pFile != NULL) {
		Paciente *pacienteAtual = start;
		
		Paciente *holdProx = NULL;

		
		while(pacienteAtual != NULL) {
			holdProx = pacienteAtual->prox_paciente;
			
			pacienteAtual->prox_paciente = NULL;
			
			fseek(pFile, 0, SEEK_END);
			fwrite(pacienteAtual, sizeof(Paciente), 1, pFile);
			
			//printf("Writing:%s to file\n",pacienteAtual->Nome);
			
			pacienteAtual->prox_paciente = holdProx;
			
			holdProx = NULL;
			
			pacienteAtual = pacienteAtual->prox_paciente;
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("FILE OPEN ERROR\n");
	}
	
}


//ABAIXO algumas funcoes que eu(Andre) criei, mas nao funcionam corretamente e foram substituidas por "WriteListToFile" e "ReadListIn".

/*
//FILE *fp;


// Carrega as informacoes salvas no arquivo "NOME_ARQUIVO". Retorna uma lista encadeada de pacientes.

Paciente* carregar_dados_pacientes_arquivo(){
  fp = fopen(NOME_ARQUIVO, "rb");// rb = modo leitura arquivo binario.
  Paciente *p;
  p = malloc(sizeof(Paciente));
  Paciente *lista_p = criar_lista_pacientes();// Cria uma lista vazia (NULL). Essa lista sera o retorno da funcao.

  if(fp != NULL){// Se o arquivo existe.
    int i = 0;
    // fread retorna um size_t representando o numero de elementos lidaos com exito.
    while(fread(p, sizeof(Paciente), 1, fp)){
      i++;
      p->prox_paciente = NULL;// Dentro do arquivo, cada paciente vai ter um ponteiro "prox_paciente", que tera um endereco de memoria. Porem, esse endereco deve ser descartado e substituido por um novo, ja que a aplicacao nao alocou -por ela mesma- esse espaco no qual esse ponteiro aponta.
        
      lista_p = inserir_paciente(lista_p, p);
    
      p = NULL;
      p = realloc(p,sizeof(Paciente));// Muda o endereco de p. Necessario para a lista encadeada funcionar.
    }  
    printf("Encontrado(s) %d paciente(s) no arquivo '%s'.\n ",i,NOME_ARQUIVO);
    fclose(fp);
  }
  else{
    printf("O arquivo '%s' nao foi encontrado.\n",NOME_ARQUIVO);
  }

  return lista_p;
}

// salva os dados dos pacientes no arquivo "NOME_ARQUIVO".
void salvar_dados_pacientes_arquivo(Paciente *lista_p){
  Paciente *p;
  p = lista_p;
  fp = fopen(NOME_ARQUIVO, "wb");// abre em modo escrita (re-escreve todos os dados presentes no arquivo, e se ele nao existir, cria um novo).
  while(p!= NULL){
    fwrite(p,sizeof(Paciente), 1, fp);
    p = (Paciente*) p->prox_paciente;
  }
  fclose(fp);
}

*/




#endif