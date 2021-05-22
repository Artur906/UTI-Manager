#ifndef EUP_H
#define  EUP_H
// ifndef necessario, pois evita que "EUP.h" seja definido mais de uma vez, causando erros. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SOFA{

  int pont_SOFA;// pontuacao SOFA final.

  //para todas as metricas: -1 = nao informado (n.i.).

  // COAGULAÇÃO
  float plaquetas;    //10^3/μl

  // RENAL
  float creatinina;   //mg/dL
  float diurese;      //mL/dia

  // CARDIOVASCULAR
  float pam;          //mmHg (Pressao Arterial Media);
  float dopamina;     //dosagem.   -1 = n.i. ; 0 = nao esta tomando
  float dobutamina;   //dosagem.    ||
  float noradrenalina;//dosagem. ||

  // NEUROLOGICO
  int ecg;//Escala de Coma de Glasgow.
  //vai de 0 a 15.


  // RESPIRATORIO
                            //litros por minuto
  float cateter_nasal_O2;   // l/min . -1 = n.i. ; 0 = nao esta usando cateter nasal.

  float ventilacao_mec_FiO2;// % . -1 = n.i. ; 0 = nao esta usando ventilacao mecanica.
  //vai de 0% a 100%


  // HEPATICO
  float inr;// International Normalized Ratio.


}SOFA;

/*
const char lista_todas_comorbidades_ICC[40][19] = {"1. Demência","2. Diabetes com complicação","3. Diabetes sem complicação","4. Doença cérebro – vascular","5. Doença do fígado severa ou moderada","6. Doença do tecido conjuntivo","7. Doença hepática crônica ou cirrose","8. Doença pulmonar crônica","9. Doença renal severa ou moderada","","","","",""}*/

typedef struct ICC{

  int pont_ICC; // pontuacao ICC final.

  // -Alguma lista que guarda todas as comorbidades-.
  //ex:
  //int[19] comorbidades;
  
}ICC;


typedef struct CFS{
  //*so deve ser aplicado para maiores de 60 anos.

                  //-1 = nao informado.

                  // 0 = esta abaixo dos 60.
  int pont_CFS;   // 1 = muito ativo
                  // ...
                  // 8 = severamente fragil.
                  
}CFS;


typedef struct KPS{
  
                  //-1 = nao informado.

  int pont_KPS;   // 1 (100%) = Com ou sem doenca cronica, consegue trabalhar normalmente
                  // 2 (80%-90%) = Com doenca cronica, consegue trabalhar apesar dos sintomas.
                  // ...
                  // 4 (10%-40%) = É incapaz de cuidar de si mesmo.
}KPS;

//---ESTRUTURA PRINCIPAL.
typedef struct EUP{

  ICC icc;
  SOFA sofa;
  CFS cfs;
  KPS kps;
  

  // 1 - Previsão de Sobrevivência a Curto Prazo (PSCP).
  int pont_PSCP;

  // 2 - Previsão de Sobrevivência a Longo Prazo (PSLP).
  int pont_PSLP; 
  
  // 3 - Previsão de Sobrevivência Global e de Resposta Terapêutica (PSGRT)
  int pont_PSGRT;

  // Pontuação final do Escore Unificado de Priorização(EUP) = pont_PSCP + pont_PSLP + pont_PSGRT.
  int pont_EUP;

}EUP;

#endif