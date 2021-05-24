#ifndef FUNCOES_EUP_H
#define FUNCOES_EUP_H

#include "EUP.h" 

//-------FUNCOES SOFA--------

void calcular_pont_SOFA(SOFA *sofa){
  // o porgrama calcula a pontuacao baseado nos dados presentes nesse "objeto" do tipo SOFA, mudando o valor de pont_SOFA.

  //essa funcao deve ser usada sempre que os dados SOFA de algum paciente mudarem, para atualizar a pontuacao.
  
  //nota: ao atualizar a pontuacao SOFA de um dado paciente, a pontuacao EUP dele tbm deve ser atualizada.

  int soma = 0;

  //-------Calculo ECG (Escala de Coma de Glasgow).
  if (sofa->ecg == 15){
    soma = soma + 0;
  }else if (sofa->ecg == 13 || sofa->ecg == 14){
    soma = soma + 1;
  }else if (sofa->ecg >= 10 && sofa->ecg <= 12){
    soma = soma + 2;
  }else if (sofa->ecg >= 6 && sofa->ecg <= 9){
    soma = soma + 3;
  }else if (sofa->ecg < 6 && sofa->ecg >= 1){
    soma = soma + 4;
  }
  //printf("+ecg %d\n",soma);

  //-------Calculo Cardiovascular.
  if (sofa->dopamina > 15 || sofa->noradrenalina > 0.1){
    //Dopamina > 15 ou Noradrenalina > 0,1.
    soma += 4;
  }
  else if (sofa->dopamina > 5 || (sofa->noradrenalina > 0 &&sofa->noradrenalina <= 0.1)){
    //Dopamina > 5 ou Noradrenalina ≤ 0,1.
    soma += 3;
  }
  else if ((sofa->dopamina > 0 && sofa->dopamina <= 5) || sofa->dobutamina > 0){
    //Dopamina ≤ 5 ou Dobutamina qualquer dose.
    soma += 2;
  }
  else if (sofa->pam < 70){
    //PAM<70mmHg.
    soma += 1;
  }
  //printf("+cardio %d\n",soma);

  //-------Calculo Respiratorio.

  if(sofa->cateter_nasal_O2 > 0 || sofa->ventilacao_mec_FiO2 > 0){
    if (sofa->ventilacao_mec_FiO2 > 40){
      //SpO2> 92% com ventilação mecânica com FiO2> 40%
      soma += 4;
    }
    else if (sofa->ventilacao_mec_FiO2 <= 40 && sofa->ventilacao_mec_FiO2 > 0){
      //SpO2>92% com ventilação mecânica com FiO2 até 40%
      soma += 3;
    }
    else if(sofa->cateter_nasal_O2 <= 5 && sofa->cateter_nasal_O2 > 0){
      //SpO2> 92% com Cateter nasal O2 até 5l/min
      soma += 2;
    }
    else if (sofa->cateter_nasal_O2 <= 2 && sofa->cateter_nasal_O2 > 0){
      //SpO2>92% com Cateter nasal O2 até 2l/min
      soma += 1;
    }

  }
 
  //printf("+resp %d\n",soma);

  //-------Calculo Coagulação.
  if(sofa->plaquetas > 0){
    if(sofa->plaquetas < 20){
      soma += 4;
    }
    else if(sofa->plaquetas < 50){
      soma += 3;
    }
    else if(sofa->plaquetas < 100){
      soma += 2;
    }
    else if(sofa->plaquetas < 150){
      soma += 1;
    }
  }
  //printf("+coag %d\n",soma);

  //-------Calculo Hepatico.
  if(sofa->inr >= 0){
    if(sofa->inr < 1.1){
      soma+= 1;
    }
    else if(sofa->inr >= 1.1 && sofa->inr < 1.36){
      soma+=2;
    }
    else if(sofa->inr >= 1.36 && sofa->inr < 1.8){
      soma+=3;
    }
    else if(sofa->inr >= 1.8 && sofa->inr < 2.15){
      soma+=4;
    }
  }
  //printf("+hep %d\n",soma);

  //-------Calculo Renal (juro que nao foi intensional).
  if(sofa->creatinina > 0 || sofa->diurese > 0){
    if(sofa->creatinina >= 4.9 || sofa->diurese < 200){
      //>5,0  ;  <200
      soma+=4;
    }
    else if((sofa->creatinina >= 3.4 && sofa->creatinina < 4.9) || sofa->diurese < 500){
      //3,5 - 4,9  ;  <500
      soma+=3;
    }
    else if(sofa->creatinina >= 1.9 && sofa->creatinina < 3.4){
      // 2 - 3,4  ;   -
      soma+=2;
    }
    else if((sofa->creatinina >= 1.2 && sofa->creatinina < 1.9) || sofa->diurese >= 500){
      // 1,2 - 1,9  ;  >500
      soma+=1;
    }
  }
  //printf("+ren %d\n",soma);
  //printf("SOMA: %d\n",soma);
  sofa->pont_SOFA = soma;
}// FIM DE calcular_pont_SOFA().



void preencher_dados_SOFA(SOFA *sofa){
  //o programa pede ao usuario para preenche todos os dados relacionados ao SOFA de um dado paciente.
  //feito isso, o programa chama a funcao "calcular_pont_SOFA()", para atualizar a pontuacao (caso tenha mudado)
  printf("---PREENCHENDO SOFA---\n");

  printf("--NEUROLOGICO--\n");
  printf("Insira a pontuação na Escala de Coma de Glasgow\n->");
  scanf("%d",&sofa->ecg );
  
  //float pam, dopamina, dobutanina, noradrenalina;
  
  printf("--CARDIOVASCULAR--\n");
  printf("Insira e Pressao Arterial Media do Paciente (PAM) em mmHg\n->");
  scanf("%f",&sofa->pam);

  printf("O paciente recebe doses de Dopamina? Se sim, insira a quantidade em mcg/kg/min. Se não, insira 0.\n->");
  scanf("%f",&sofa->dopamina);

  printf("O paciente recebe doses de Dobutamina? Se sim, insira a quantidade em mcg/kg/min. Se não, insira 0.\n->");
  scanf("%f",&sofa->dobutamina);

  printf("O paciente recebe doses de Noradrenalina? Se sim, insira a quantidade em mcg/kg/min. Se não, insira 0.\n->");
  scanf("%f",&sofa->noradrenalina);
  
  
  printf("--RESPIRATORIA--\n");
  printf("Para atingir um nivel de SpO2 superior a 92%%, o paciente necessita de um cateter nasal? Se sim, insira a quantidade em L/min. Se não, insira 0.\n->");

  scanf("%f", &sofa->cateter_nasal_O2);

  
  printf("Para atingir um nivel de SpO2 superior a 92%%, o paciente necessita de ventilação mecanica? Se sim, insira a porcentagem de FiO2. Se não, insira 0.\n->");

  scanf("%f", &sofa->ventilacao_mec_FiO2);
  

  printf("--COAGULAÇÃO--\n");
  printf("Insira a quantidade de plaquetas, medida em 10^3/µL\n->");
  scanf("%f",&sofa->plaquetas);

  printf("--HEPATICO--\n");
  printf("Insira o INR do paciente.\n->");
  scanf("%f",&sofa->inr);

  printf("--RENAL--\n");
  printf("Insira a quantidade de Creatinina em mg/dL\n->");
  scanf("%f",&sofa->creatinina);
  printf("Insira a diurese em mL/dia\n->");
  scanf("%f",&sofa->diurese);

  //atualiza a pontuacao SOFA.
  calcular_pont_SOFA(sofa);
  
}// FIM DE preencher_dados_SOFA().



//-------------------------------



void print_dados_SOFA(SOFA *sofa){
  printf("\n----SOFA----\n");
  printf("-PONTUACAO SOFA: %d\n",sofa->pont_SOFA);
  printf("----------------\n");
  printf("-ECG: %d\n",sofa->ecg);
  printf("-PAM: %.2f \n",sofa->pam);
  printf("-Dosagem Dopamina (mcg/kg/min): %.2f \n",sofa->dopamina);
  printf("-Dosagem Dobutamina (mcg/kg/min): %.2f \n",sofa->dobutamina);
  printf("-Dosagem Noradrenalina (mcg/kg/min): %.2f \n",sofa->noradrenalina);
  if(sofa->cateter_nasal_O2 != 0){
    printf("-SpO2 > 92%% , com cateter nasal de (L/min): %.2f \n",sofa->cateter_nasal_O2);
  }
  if(sofa->ventilacao_mec_FiO2 != 0){
    printf("-SpO2 > 92%% , com ventilaçao mecanica com FiO2 de: %.2f%% \n",sofa->ventilacao_mec_FiO2);
  }
  else if(sofa->cateter_nasal_O2 == 0){
    printf("Sem respirador auxiliar.\n");
  }

  printf("-Contagem de plaquetas (10^3/µL) : %.2f \n",sofa->plaquetas);
  printf("-INR: %.2f\n",sofa->inr);
  printf("-Creatinina (mg/dL): %.2f \n",sofa->creatinina);
  printf("-Diurese (mL/dia): %.2f\n",sofa->diurese);

}// FIM DE print_dados_SOFA().


//-------FUNCOES ICC--------
void preenchimento_padrao_lista_comorbidades(ICC *icc){
  for(int i=0;i<19;i++){
    icc->comorbidades[i] = 0; 
  }
}

void calcular_pont_ICC(ICC *icc){
  
  // calcula a pontuacao, somando os pontos equivalentes a cada comorbidade que o paciente tem.
  icc->pont_ICC = 0; // o valor estava chegado aqui como -1; 

  for(int i=0; i<19; i++){
    if(icc->comorbidades[i] == 1){
      //Por alguma razão existe Hipertensão que vale 0, então não faz diferença por aqui.
      /*if(i+1 == 12){
        icc->pont_ICC += 0
      }*/
      if(i+1 == 1 || i+1 == 3 || i+1 == 4 || i+1 == 6 ||i+1 == 7 || i+1 == 8 || i+1 == 10 || i+1 == 13 ||i+1 == 19){
        icc->pont_ICC += 1;
      }
      if(i+1 == 2 || i+1 == 9 || i+1 == 11 || i+1 == 14 || i+1 == 15 || i+1 == 17){
        icc->pont_ICC += 2; 
      }
      if(i+1 == 5){
        icc->pont_ICC += 3;
      }
      if(i+1 == 16 || i+1 == 18){
        icc->pont_ICC += 6;
      }
    }
  }
}


void preencher_dados_ICC(ICC *icc){
  // o usuario diz as comorbidades de um dado paciente.
  preenchimento_padrao_lista_comorbidades(icc);
  int posicao;
  int continua; 

  printf("\n--PREENCHENDO O ICC-- \n-INDICE DE COMORBIDADES-\n");

  for(int i=0;i<19;i++){
    printf("\n%d - %s", i+1, lista_comorbidades[i]);
  }

  printf("\n\nAlguma comorbidade? (1 = sim / 0 = não): ");
  scanf("%d",&continua);
  getchar();
  if(continua != 0){

    // usuário começa a listar as comorbidades do paciente
    
    while(posicao != 0){

      printf("Selecione uma comorbidade(ou 0 para encerrar): "); 
      scanf("%d", &posicao);

      while(posicao < 0 || posicao > 19){
        printf("Informe uma comorbidade entre 1 e 19: ");
        scanf("%d",&posicao);
        getchar();
      }
      
      if(posicao == 0){
        break;
      }else if(icc->comorbidades[posicao-1] == 1){
        icc->comorbidades[posicao-1] = 0; 
      }else{
        icc->comorbidades[posicao-1] = 1; 
      }
    }
  }

  calcular_pont_ICC(icc); 

}

void print_dados_ICC(ICC *icc){
  // printa os dados ICC, ou seja, as comorbidades de um paciente.

  printf("\n----ICC----"); 
  printf("\n-PONTUACAO ICC: %d",icc->pont_ICC);
  printf("\n--------------------");
  printf("\n--COMORBIDADES DO PACIENTE--");
  
  for(int i=0; i<19; i++){
    if(icc->comorbidades[i] == 1){
      printf("\n-%s ",lista_comorbidades[i]);
    }
  }

}



//-------FUNCOES CFS--------

void preencher_dados_CFS(CFS *cfs){
  // Essa funcao NAO eh usada em pacientes com idade menor a 60 anos.
  // o usuario diz o nivel de fragilidade do paciente maior de idade.
  printf("\n\n--PREENCHENDO O CFS-- \nESCALA CRÍTICA DE FRAGILIDADE\n"); 
  printf("1 - Muito ativo \n2 - Ativo \n3 - Regular \n4 - Vulnerável \n5 - Levemente Frágil \n6 - Moderadamente Frágil \n7 - Muito Frágil \n8 - Severamente Frágil\n"); 

  printf("Informe o nível de fragilidade do paciente: ");
  scanf("%d",&cfs->pont_CFS);
  
  while(cfs->pont_CFS <1 || cfs->pont_CFS > 8){
    printf("Escolha um nível entre 1 e 8: ");
    scanf("%d",&cfs->pont_CFS); 
  }
  

}

//vou criar uma lista para os níveis de fragilidade, é mais por uma questão estética 
void print_dados_CFS(CFS *cfs){
  printf("\n----CFS----\n");
  printf("-PONTUAÇÃO CFS: %d \n",cfs->pont_CFS);

  // printa o nivel de fragilidade. 
  // funcao simples de fazer
}

//uma funcao "calcular_pont_CFS" eh completamente desnecessaria, pois a funcao "preencher_dados_CFS" da conta disso. O mesmo vale para KPS.

//-------FUNCOES KPS--------

void preencher_dados_KPS(KPS *kps){
  printf("\n---KPS---- \nSTATUS DE DESEMPENHO KARNOFSKY\n"); 
  printf("\n1 - Com ou sem doença crônica, consegue trabalhar normalmente\nKPS 100%% \n2 - Com doença crônica, consegue trabalhar apesar de ter sintomas\nKPS 80-90%% \n3 - Não consegue travalhar mas mantém hobbies e autocuidado\nKPS 50-60-70%% \n4 - É incapaz de cuidar de si mesmo \nKPS 10-20-30-40%% \n"); 
  
  printf("Informe no que o paciente se encaixa: ");
  scanf("%d",&kps->pont_KPS);
  while(kps->pont_KPS <1 || kps->pont_KPS > 4){
    printf("Escolha entre 1 e 4: ");
    scanf("%d",&kps->pont_KPS); 
  }
  // o usuario diz o nivel de dependencia que o paciente tem.
  // ou seja, um simples numero entre 1 e 4.
  // funcao simples de fazer
}

void print_dados_KPS(KPS *kps){
  printf("\n----KPS----");
  printf("\n-PONTUAÇÃO KPS: %d\n",kps->pont_KPS);
  if(kps->pont_KPS == 1){
    printf("-Com ou sem doença crônica, consegue trabalhar normalmente\n");
  }
  if(kps->pont_KPS == 2){
    printf("-Com doença crônica, consegue trabalhar apesar de ter sintomas\n");
  }
  if(kps->pont_KPS == 3){
    printf("-Não consegue trabalhar mas mantém hobbies e autocuidado\n");
  }
  if(kps->pont_KPS == 4){
    printf("-É incapaz de cuidar de si mesmo\n");
  }
  // printa o nivel de dependencia. 
  // funcao simples de fazer
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-----------FUNCOES EUP-----------

void print_dados_EUP(EUP *eup){
  printf("1 - Previsão de Sobrevivência a Curto Prazo (PSCP): %d\n",eup->pont_PSCP);
  printf("2 - Previsão de Sobrevivência a Longo Prazo (PSLP): %d\n",eup->pont_PSLP);
  printf("3 - Previsão de Sobrevivência Global e de Resposta Terapêutica (PSGRT): %d\n",eup->pont_PSGRT);
  printf("--- EUP-UTI: %d\n",eup->pont_EUP);
  print_dados_SOFA(&eup->sofa);
  print_dados_ICC(&eup->icc);
  print_dados_CFS(&eup->cfs);
  print_dados_KPS(&eup->kps);

}


void calcular_pont_EUP(EUP *eup){
  // Essa funcao pega todos os dados do paciente e calcula a pontuacao final EUP.

  int pont_PSCP =  0;// Previsão de sobrevivência a curto prazo.
  int pont_PSLP =  0;// Previsão de sobrevivência a longo prazo.
  int pont_PSGRT = 0;//Previsão de sobrevivência global e de resposta terapêutica.

  //1. Previsão de sobrevivência a curto prazo, determinado o Sequential Organ Failure Assessment - SOFA (simplificado).
  /*
  SOFA Simplificado	<6	  (1 ponto)
  SOFA Simplificado	6-9	  (2 pontos)
  SOFA Simplificado	10-12	(3 pontos)
  SOFA Simplificado	>12	  (4 pontos)
  */
  if(eup->sofa.pont_SOFA < 6){
    pont_PSCP = 1; 
  }else if(eup->sofa.pont_SOFA >= 6 && eup->sofa.pont_SOFA <= 9){
    pont_PSCP = 2;
  }else if(eup->sofa.pont_SOFA >= 10 && eup->sofa.pont_SOFA <= 12){
    pont_PSCP = 3; 
  }else{
    pont_PSCP = 4;
  }
  eup->pont_PSCP = pont_PSCP;


  //2. Previsão de sobrevivência a longo prazo, avaliado pela presença de comorbidades (pelo Índice de Comorbidades de Charlson) e/ou Fragilidade (pela Clinical Frailtv Scale).
  /*
  ICC 0-1	ou	CFS<4	    (1 ponto)
  ICC 2	ou CFS=4	      (2 pontos)
  ICC 3-5	ou CFS 5 e 6	(3 pontos)
  ICC>5	ou CFS 7 e 8	  (4 pontos)
  */

  // Previsão de sobrevivência a longo prazo
  // Fiz em ordem decrescente, porque pensei que alguns problemas poderiam ocorrer se fossemos do menor para o maior
  if(eup->icc.pont_ICC > 5 || eup->cfs.pont_CFS == 7 || eup->cfs.pont_CFS == 8){
    pont_PSLP = 4; 
  }else if((eup->icc.pont_ICC >= 3 && eup->icc.pont_ICC <= 5) || eup->cfs.pont_CFS == 5 || eup->cfs.pont_CFS == 6){
    pont_PSLP = 3; 
  }else if(eup->icc.pont_ICC == 2 || eup->cfs.pont_CFS == 4){
    pont_PSLP = 2;
  }else if(eup->icc.pont_ICC >= 0 || eup->cfs.pont_CFS >=0){
    pont_PSLP = 1;
  }
  eup->pont_PSLP = pont_PSLP;
  
  

  //3. Previsão de sobrevivência global e de resposta terapêutica, analisada pelo Karnofsky Performance Status KPS (adaptado).
  /*
  Com ou sem doença crônica, consegue trabalhar normalmente	KPS 100%	(1 ponto)
  Com doença crônica, consegue trabalhar apesar de ter sintomas	KPS 80-90%	(2 pontos)
  Não consegue trabalhar mas mantém hobbies e autocuidado	KPS 50-60-70%	(3 pontos)
  É incapaz de cuidar de si mesmo	KPS 10-20-30-40%	(4 pontos)
  */
  eup->pont_PSGRT = eup->kps.pont_KPS;
  if(eup->pont_PSGRT > 0){
    pont_PSGRT = eup->pont_PSGRT;
  }

  //soma final.
  eup->pont_EUP = pont_PSGRT + pont_PSLP + pont_PSCP;
  
}


void preecher_dados_EUP(EUP *eup, int idade){
  //o usuario preecnhe os dados SOFA, ICC, CFS e KPS. Ao final disso, a pontuacao EUP eh calculada ao chamar a funcao "calcular_pont_EUP".
  preencher_dados_SOFA(&eup->sofa);
  preencher_dados_ICC(&eup->icc);
  if(idade >= 60){
    preencher_dados_CFS(&eup->cfs);
  }
  else{
    //pontuacao CFS = 0 caso idade menor que 60.
    eup->cfs.pont_CFS = 0;
  }

  preencher_dados_KPS(&eup->kps);

  //apos o usuario inserir os dados, a pontuacao eh calculada.
  calcular_pont_EUP(eup);
}



// Faz todas as informacoes terem valor -1. Essa funcao é usada ao criar um paciente novo.
void preecher_dados_EUP_com_valor_padrao(EUP *eup){

  eup->sofa.plaquetas = -1;
  eup->sofa.creatinina = -1;
  eup->sofa.diurese = -1;
  eup->sofa.pam = -1;
  eup->sofa.dopamina = -1;
  eup->sofa.dobutamina = -1;
  eup->sofa.noradrenalina = -1;
  eup->sofa.ecg = -1;
  eup->sofa.cateter_nasal_O2 = -1;
  eup->sofa.ventilacao_mec_FiO2 = -1;
  eup->sofa.inr = -1;

  eup->sofa.pont_SOFA = -1;
  eup->icc.pont_ICC = -1;
  eup->cfs.pont_CFS = -1;
  eup->kps.pont_KPS = -1;

  eup->pont_PSCP = -1;
  eup->pont_PSLP = -1;
  eup->pont_PSGRT = -1;

  eup->pont_EUP = -1;
}



#endif
