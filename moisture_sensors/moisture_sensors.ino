#include<stdlib.h>
#include <dht.h>

dht DHT;
int moisturePin1 = A0;
int moisturePin2 =  A1;
int dhtPin = A2;
int moistureSenor1Reading = 0;
int moistureSenor2Reading = 0;
int powerPin = 8;

void setup() 
{
  Serial.begin(9600);

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  Serial.println("Begin Reading");
  Serial.println("-------------");
}

void loop()
{
  digitalWrite(powerPin, HIGH);
  delay(10);
  moistureSenor1Reading = analogRead(moisturePin1);
  moistureSenor2Reading = analogRead(moisturePin2);
  
  DHT.read11(dhtPin);
  float tempuReading = DHT.temperature;
  Serial.println(tempuReading);
  char tempuBuffer[15];
  dtostrf(tempuReading,5   , 2, tempuBuffer);

  String tempuString = String(tempuBuffer);
    
  Serial.println("sensor=moisture1:reading=" + String(moistureSenor1Reading));
  Serial.println("sensor=moisture2:reading=" + String(moistureSenor2Reading));
  Serial.println("sensor=temp:reading=" + tempuString);
  /*Serial.println("sensor=humidity:reading=" + String(DHT.humidity);*/
  
  digitalWrite(powerPin, LOW);
  delay(3000);
  /*for(int i = 0; i < 20; i++){
    delay(30000);
  }*/
}


