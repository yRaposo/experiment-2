/*******************************************************************************
* Sensor de Umidade de Solo Capacitivo - Coletor de Media de Leituras (v1.0)
* 
* Este codigo realiza um calculo de media de leitura de uma determinada 
* quantidade de amostras, para facilitar na calibracao futura do sensor. 
* O ideal e iniciar o teste com o sensor ja inserido na terra e em duas
* circunstancias distintas, com o solo seco e com o solo com a concentracao 
* maxima de agua desejada. Talvez seja melhor comecar os testes com o solo seco,
* para facilitar a obtencao dos valores.
* 
* Copyright 2020 RoboCore.
* Escrito por Giovanni de Castro (08/10/2020).
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version (<https://www.gnu.org/licenses/>).
*******************************************************************************/

//Declaracao do pino conectado ao sensor
const int PINO_SENSOR = 34;

//Declaracao da variavel que armazena as leituras do sensor
int leitura_sensor = 0;

//Declaracao da variavel que armazena a quantidade de amostras que serao coletadas
const int NUMERO_AMOSTRAS = 100; 
//Altere a variavel acima com a quantidade de amostras que deseja coletar para o calculo da media

//Declaracao da variavel que armazena a soma das leituras
long somatoria = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("                  ---*****---                  ");
  Serial.println("Sensor de Umidade de Solo Capacitivo - Primeiros Passos");
  Serial.println("Coletando media de leituras do sensor...");
  Serial.println("");

  //Configuracao do pino conectado ao sensor como uma entrada
  pinMode(PINO_SENSOR, INPUT);

  //Realiza a leitura do sensor de acordo com a variavel "NUMERO_AMOSTRAS"
  for(int i = 1; i <= NUMERO_AMOSTRAS; i++){
    leitura_sensor = analogRead(PINO_SENSOR); //Le o sensor
    somatoria = somatoria + leitura_sensor; //Soma a variavel "somatoria" a leitura atual do sensor com seu valor anterior
    float tensao = leitura_sensor*(5.0/1023); //Converte a leitura para tensao para referencia
    Serial.print("Amostra ");
    Serial.print(i);
    Serial.print("  |  ");
    Serial.print("Leitura: ");
    Serial.print(leitura_sensor);
    Serial.print("  |  ");
    Serial.print("Tensao: ");
    Serial.println(tensao);
    delay(1000);
  }

  //Calcula a media das leituras utilizando a variavel "somatoria" e a variavel "NUMERO_AMOSTRAS"
  int media = somatoria / NUMERO_AMOSTRAS;
  Serial.println("");
  Serial.print("Media obtida: ");
  Serial.println(media);

}

void loop() {
  //Nao ha nada para executar aqui
}