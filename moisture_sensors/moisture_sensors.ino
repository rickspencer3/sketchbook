#include <SPI.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#include<stdlib.h>
#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

dht DHT;
int moisturePin = A0;
int dhtPin = A2;
int lightPin = A4;
int powerPin = 0;
int oneWirePin = 2;

OneWire oneWire(oneWirePin);
DallasTemperature sensors(&oneWire);
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "10101";

String deviceCode = "01";
  
void setup() 
{
  Serial.begin(9600);

  sensors.begin();
   
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  Serial.println("Begin Reading");
  Serial.println("-------------");
}

void loop()
{
  digitalWrite(powerPin, HIGH);
  delay(10);
  int moistureSenorReading = analogRead(moisturePin);
  
  DHT.read11(dhtPin);
  int airTemperatureReading = DHT.temperature;
  int himudityReading = DHT.humidity;
  
  sensors.requestTemperatures();
  int soilTemperatureReading = sensors.getTempCByIndex(0);
  
  int lightReading = analogRead(lightPin);
  
  Serial.println(transmitReading("SM",moistureSenorReading));
  Serial.println(transmitReading("AT",airTemperatureReading));
  Serial.println(transmitReading("HU",himudityReading));
  Serial.println(transmitReading("ST",soilTemperatureReading));
  Serial.println(transmitReading("LI",lightReading));
  
  digitalWrite(powerPin, LOW);
  delay(3000);
}

String transmitReading(String sensor, int reading) {
 String transmitString = deviceCode + sensor +  paddedString(reading);
 char r[8];
 transmitString.toCharArray(r,8);
 radio.write(&r, sizeof(r));
 return transmitString;
}

String paddedString(int reading) {
  if(reading < 0) return "ERR";
  
  String str = String(reading);
  if(reading < 10) str = "00"  + str;
  else if(reading < 100) str = "0" + str;
  return str;
}
