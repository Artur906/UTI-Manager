# UTI-Manager
***

## O que é? 

O _**UTI Manager**_ é um organizador de leitos para Unidade de Terapia Intensiva (UTI), que se baseia principalmente nas [recomendações](https://www.cremepe.org.br/wp-content/uploads/2020/04/RECOMENDAÇÃO-CREMEPE-Nº-05_v.final_.pdf) fornecidas pelo Conselho Regional de Medicina de Pernambuco (CREMEPE) e também na [Calculadora do Escore Unificado para Priorização em Unidades de Terapia Intensiva - EUP-UTI](http://cremepe.org.br/portal2015/calculadoraeup/), igualmente disponibilizada pela CREMEPE. 

## Pra que serve? 

O programa foi pensado para auxiliar na tomada de decisão dos médicos, em relação a ocupação de leitos de UTI.

### Escore Unificado para Priorização (EUP)

O _EUP_ é composto por 3 grupos de informações, que são:
* Previsão de sobrevivência a curto prazo
  * Sequential Organ Failure Assessment (**SOFA**) - simplificado
* Previsão de sobrevivência a longo prazo 
  * Indice de comorbidades (**ICC**) 
  * Clinical Frailt Scale (**CFS**)
* Previsão de sobrevivência global e de resposta terapeutica 
  * Karnofsky Performance Status (**KPS**) - adaptado

**OBS**: o CFS só é considerado para pacientes com mais de 60 anos. 

### Como a pontuação EUP é calculada? 

#### 1 - _*Previsão de sobrevivência a curto prazo*_
 Pontuação SOFA - simplificado | Pontuação EUP
 :--: | :--: 
 Menor que 6 | +1
 Entre 6 e 9 | +2
 Entre 10 e 12 | +3
 Maior que 12 | +4
#### 2 - _*Previsão de sobrevivência a longo prazo*_
 Pontuação ICC | CFS | Pontuação EUP
 :--: | :--: | :--: 
 Igual a 0 ou 1| Menor que 4 | +1
 Igual a 2 |Igual a 4| +2
 Entre 3 e 5 |Igual a 5 ou 6| +3
 Maior que 5 |Igual a 7 ou 8| +4
#### 3 - _*Previsão de sobrevivência global e de resposta terapêutica*_
 Estado do paciente | Porcentagem KPS - adaptado | Pontuação EUP
 :--: | :--: | :--: 
 Com ou sem doença crônica, consegue trabalhar normalmente| 100% | +1
 Com doença crônica, consegue trabalhar apesar de ter sintomas |80-90%| +2
 Não consegue trabalhar mas mantém hobbies e autocuidado |50-60-70%| +3
 É incapaz de cuidar de si mesmo|10-20-30-40%| +4

### Estrutura básica do programa
O programa dividi-se em duas partes, como mostra o diagrama a seguir.

![imagem de exemplo](imagens/diagrama.png) 


Aqui nesse readme, vamos resumir o que o nosso programa faz, qual a finaldade dele, como o usar, e outras paradas.

INTEGRANTRES: Andre, Artur, Joao Paulo e Wellyngton.