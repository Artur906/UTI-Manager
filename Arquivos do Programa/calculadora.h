#include <stdio.h>
#include <stdlib.h> 


// inicio da Previsão de sobrevivência a longo prazo

int cal_ICC(){
  int * resul;  //O ICC é uma sessão de múltipla escolha, por isso, acho que faz sentido usarmos uma lista dinâmica;  
  int continua; 

  printf("ICC \n Indice de cormobidade\n");
  printf("Digite: \n 1. Demência \n 2. Diabetes com complicação \n 3. Diabetes sem complicação \n 4. Doença cérebro – vascular \n 5. Doença do fígado severa ou moderada \n 6. Doença do tecido conjuntivo \n 7. Doença hepática crônica ou cirrose \n 8. Doença pulmonar crônica \n 9. Doença renal severa ou moderada \n 10. Doença vascular periférica \n 11. Hemiplegia ou paraplegia \n 12. Hipertensão \n 13. Insuficiência cardíaca congestiva \n 14. Leucemia \n 15. Linfoma \n 16. SIDA \n 17. Tumor maligno \n 18. Tumor sólido metastático \n 19. Úlcera gastroduodenal\n");

  printf("Alguma comorbidade? (1 = sim / 0 = não): ");
  scanf("%d",&continua);

  if(continua != 0){

    int cont = 1; //valor para iniciar a lista

    resul = (int *) malloc(cont*sizeof(int));

    // usuário começa a listar as comorbidades do paciente
    
    while(continua != 0 && cont != 19){
      if(cont != 1){
        resul = (int *) realloc(cont*sizeof(int));
      }
      printf("\n Selecione uma comorbidade: "); 
      scanf("%d", &resul[cont-1]);// a lista começa na posição 0, nosso contadoor começa em 1; 

      printf("\nMais alguma? Informe 0 para parar e qualquer outro valor inteiro para continuar ->");
      scanf("%d", &continua);

      if(continua == 0){
        break;
      }else{
        cont++;  
      }
    }
  }
  //conversão das seleções em pontos

  /*
  listinha pra facilitar

  1. Demência = 1
  2. Diabetes com complicação = 2 
  3. Diabetes sem complicação = 1 
  4. Doença cérebro – vascular = 1
  5. Doença do fígado severa ou moderada = 3  
  6. Doença do tecido conjuntivo = 1
  7. Doença hepática crônica ou cirrose = 1
  8. Doença pulmonar crônica = 1
  9. Doença renal severa ou moderada = 2
  10. Doença vascular periférica = 1
  11. Hemiplegia ou paraplegia = 2
  12. Hipertensão = 0
  13. Insuficiência cardíaca congestiva = 1 
  14. Leucemia = 2
  15. Linfoma = 2
  16. SIDA = 6
  17. Tumor maligno = 2 
  18. Tumor sólido metastático = 6  
  19. Úlcera gastroduodenal = 1
  */
}

int cal_CFS(){//a função cal_CFS só sera usada em pacientes com idade >= 60 anos;
  int resul; 

  printf("CFS \n Escala crítica de fragilidade\n"); 
  printf("Digite: \n 1. Muito ativo \n 2. Ativo \n 3. Regular \n 4. Vulnerável \n 5. Levemente Frágil \n 6. Moderadamente Frágil \n 7. Muito Frágil \n 8. Severamente Frágil\n")

  scanf("%d", &resul);
}

// fim da previsão de sobrevivência a longo prazo

// Inicio da previsão de sobrevivência global e de resposta terapêutica 

int cal_KPS(){
  int resul; 

  printf("KPS \n Status de desempenho Karnofsky\n"); 
  printf("Digite: \n 1. Com ou sem doença crônica, consegue trabalhar normalmente \n 2. Com doença crônica, consegue trabalhar apesar de ter sintomas \n 3. Não consegue travalhar mas mantém hobbies e autocuidado \n 4. É incapaz de cuidar de si mesmo \n"); 

  scanf("%d", resul);


}


// inicio da promagação da calculadora EUP
int * Calcula_EUP(Paciente *lista_p){
  Paciente *p = lista_p;

  int sofa, icc, cfs, kps; // variaveis correspondentes aos resultados finais de cada função.

  //pensando na função de atualização do status de um paciente, seria interessante se colocassemos cada uma dessas pontuações nas informações do paciente

  int pontos = 0, add;


  /*
  // fórmula 
  // Previsão de sobrevivência a curto prazo
  if(sofa < 6){
    pontos += 1; 
  }else if(sofa >= 6 || sofa <= 9){
    pontos += 2;
  }else if(sofa >= 10 || sofa <= 12){
    pontos += 3; 
  }else{
    pontos += 4;
  }
  */


  // Previsão de sobrevivência a longo prazo
  // Fiz em ordem decrescente, porque pensei que alguns problemas poderiam ocorrer se fossemos do menor para o maior

  if(icc > 5 || cfs == 7 || cfs == 8){
    pontos += 4; 
  }else if(icc >= 3 || icc <= 5 || cfs == 5 || cfs == 6){
    pontos += 3; 
  }else if(icc == 2 || cfs == 4){
    pontos += 2;
  }else{
    pontos += 1;
  }
  // Previsão de sobrevivência global e de resposta terapêutica


/*
// inicio do SOFA
int cal_neuro(){
  printf(" Neurológico\n")
  printf("qual foi a pontuação na escala de coma de Glasgow");
  scanf("%d", &add);
  if (add == 15){
    soma = soma + 0;
  }else if (add == 13 || add == 14){
    soma = soma + 1;
  }else if (add >= 10 || add <= 12){
    soma = soma + 2;
  }else if (add >= 6 || add <= 9){
    soma = soma + 3;
  }else if (add < 6){
    soma = soma + 4;
  }

  return soma;
}

int cal_cardio(){
  int res;
  printf("cardiovascular \n Hipotensão e mmHG\n");
  printf("digite\n 0. Não se encaixar em nenhum\n 1. PAM<70mmHg\n 2. Dopamina ≤ 5 ou Dobutamina qualquer dose\n 3. Dopamina > 5 ou Noradrenalina ≤ 0,1\n 4. Dopamina > 15 ou Noradrenalina > 0,1 \n");
  scanf("%d", &res);

  return res;

}

int cal_respiratorio(){
  int res;
  printf("Respiratorio \n Saturação Periférica de O2\n");
  printf("digite\n 0. Não se encaixar em nenhum\n 1. SpO2>92% com Cateter nasal O2 até 2l/min\n 2. SpO2> 92% com Cateter nasal O2 até 5l/min\n 3. SpO2>92% com ventilação mecânica com FiO2 até 40%\n 4. SpO2> 92% com ventilação mecânica com FiO2> 40% \n");
  scanf("%d", &res);

  return res;
}

int cal_coagulacao(){
  int res;
  printf("coagulacao \n Plaquetas 10³/µl\n");
  printf("digite\n 0. Não se encaixar em nenhum\n 1. <150\n 2. <100\n 3. <50\n 4. <20 \n");
  scanf("%d", &res);

  return res;
}
 
int cal_hepatico(){
  int res;
  printf("Hepatico \n INR e Inspeção\n");
  printf("digite\n 0. Não se encaixar em nenhum\n 1. <1,1 Anictérico\n 2. 1,1 - 1,36\n 3. 1,36 - 1,8\n 4. 1,88 - 2,15 Ictérico \n");
  scanf("%d", &res);

  return res;
}

int cal_renal(){
  int res;
  printf("Renal \n Creatinina (mg/dL) e Diurese (mL/dia)\n");
  printf("digite\n 0. Não se encaixar em nenhum\n 1. 1,2 - 1,9 >500\n 2. 2 - 3,4 -\n 3. 3,5 - 4,9 <500\n 4. >5,0 <200 \n");
  scanf("%d", &res);

  return res;
}
// fim do SOFA
*/


  

}