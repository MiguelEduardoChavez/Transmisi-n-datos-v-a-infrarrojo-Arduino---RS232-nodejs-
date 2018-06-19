#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int mq2 = A0;
int pir = 2;
int h =0, t=0, gas=0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(mq2,INPUT);
  attachInterrupt(0, manejoPir, RISING);
  sensarMQ2();
  sensarDTH();
  /*Serial.print("m:");
  Serial.println(mq2);
  Serial.print("h:");
  Serial.println(h);
  Serial.print("t:");
  Serial.println(t);*/
}
void loop(){
  Serial.print("pir:");
  Serial.println(digitalRead(pir));
  int temporalM = gas;
  int temporalH = h;
  int temporalT = t;
  /*if(digitalRead(pir==LOW)){
    Serial.println("npir");
  }*/
  sensarMQ2();
  sensarDTH();
  if(temporalM != gas){
    Serial.print("m:");
    Serial.println(gas);
  }
  if(temporalH != h){
    Serial.print("h:");
    Serial.println(h);
  }
  if(temporalT != t){
    Serial.print("t:");
    Serial.println(t);
  }
  delay(2000);
 }

void sensarMQ2(){
  gas  = analogRead(mq2); 
}

void sensarDTH() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("DTH11 no detectado");
  }
}

void manejoPir(){
  Serial.print("pir:");
  Serial.println(digitalRead(pir));
}
