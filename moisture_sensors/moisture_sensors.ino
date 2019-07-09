#include<stdlib.h>
#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

dht DHT;
int moisturePin = A0;
int dhtPin = A2;
int powerPin = 8;
int oneWirePin = 2;

OneWire oneWire(oneWirePin);
DallasTemperature sensors(&oneWire);
  
void setup() 
{
  Serial.begin(9600);

  sensors.begin();
  
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  
  Serial.println("Begin Reading");
  Serial.println("-------------");
}

void loop()
{
  digitalWrite(powerPin, HIGH);
  delay(10);
  float moistureSenorReading = analogRead(moisturePin);
  
  DHT.read11(dhtPin);
  float airTemperatureReading = DHT.temperature;
  float himudityReading = DHT.humidity;
  
  sensors.requestTemperatures();
  float soilTemperatureReading = sensors.getTempCByIndex(0);
  
  Serial.println("sensor=moisture1:reading=" + floatToString(moistureSenorReading));
  Serial.println("sensor=temp:reading=" + floatToString(airTemperatureReading));
  Serial.println("sensor=temp:reading=" + floatToString(himudityReading)); 
  Serial.println("sensor=temp:reading=" + floatToString(soilTemperatureReading)); 
  
  digitalWrite(powerPin, LOW);
  delay(3000);
  /*for(int i = 0; i < 20; i++){
    delay(30000);
  }*/
}

String floatToString(float reading) {
  char tempBuffer[15];
  dtostrf(reading,5   , 2, tempBuffer);
  return String(tempBuffer);
}


