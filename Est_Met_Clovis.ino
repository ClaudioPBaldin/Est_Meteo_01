#include <DHT.h>
#include <math.h>

//definicoes temp e umid
#define DHTPIN 10
DHT dht(DHTPIN, DHT22);

//definicoes anemometro
int rpm = 0;
int velocidade = 0;
const float pi = 3.14159265;
volatile byte pulsos = 0;
unsigned long timeold = 0;
unsigned int pulsos_por_volta = 1;

//definicoes pluviometro
float chuva = -0.25;
float contchuva = 1;
float contchuvatemp = 0;

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), contador,RISING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), cont,RISING);
}
//Contador do Anemometro
void contador()
{
  pulsos ++;
}

//Contador do Pluviometro
void cont()
{
  contchuva ++;
}

//Leitura do Sensor DHT22
void infoDHT()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float ym = 0;
  float Tpo = 0;
  
  if (isnan(h) || isnan(t))
    {
    Serial.println(F("Falha DHT22"));
    }
  Serial.print("U");
  Serial.println(h);
  Serial.print("T");
  Serial.println(t); 

  //Ponto de Orvalho
  ym = log((h/100)*exp((17.67-(t/234.5))*(t/(243.5+t))));
  Tpo = (243.5*ym)/(17.67-ym);
  Serial.print("O");
  Serial.println(Tpo);
  
 }
 
// Leitura da Bussola
void infobussola()
{
  float bussola = 0;
  bussola = analogRead(A1)*(5.0/1023.0);
  if (bussola <= 0.58) {
    Serial.print("D");
    Serial.println(8);
  }
  else if (bussola <= 0.63) {
    Serial.print("D");
    Serial.println(7);
  }
  else if (bussola <= 0.75) {
    Serial.print("D");
    Serial.println(6);
  }
  else if (bussola <= 0.86) {
    Serial.print("D");
    Serial.println(5);
  }  
  else if (bussola <= 1.00) {
    Serial.print("D");
    Serial.println(4);
  }
  else if (bussola <= 1.25) {
    Serial.print("D");
    Serial.println(3);
  }
  else if (bussola <= 1.65) {
    Serial.print("D");
    Serial.println(2);
  }
   else {
    Serial.print("D");
    Serial.println(1);
  }    
  
  delay(10);
}

// Leitura do Anemometro
void anemometro()
{
   if (millis() - timeold >= 5000)
 {
  rpm = (60*1000/pulsos_por_volta) / (millis() - timeold) * pulsos;
  timeold = millis();
  pulsos = 0;
  velocidade = (((4*pi*147*rpm)/60)/1000)*3.6;
  Serial.print("V");
  Serial.println(velocidade); 
 }
  delay(1000);
  
}

//Leitura do Pluviometro
void pluviometro()
{
  if (contchuvatemp < contchuva){
    chuva = chuva + 0.25;
    Serial.print("C");
    Serial.println(chuva);
    contchuvatemp = contchuva;
  }
}

// Função de Looping Infinito
void loop() {

//Chama as funcoes dos sensores
  infoDHT();
  delay(5);
  infobussola();
  delay(5);
  anemometro();
  delay(5);
  pluviometro();
  delay(5);
  

}
