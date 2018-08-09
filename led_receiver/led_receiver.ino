#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

const int RED_PIN = 2;
const int YELLOW_PIN = 3;
const int WHITE_PIN = 4;
const int BLUE_PIN = 5;
const int GREEN_PIN = 6;
const int PURPLE_PIN = 7;
const int ORANGE_PIN = 8;

int state = HIGH;

int leds[] = {RED_PIN, YELLOW_PIN, WHITE_PIN, BLUE_PIN, GREEN_PIN, PURPLE_PIN, ORANGE_PIN};
const int ledCount = 7;

void setup() 
{
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

  for(int i = 0; i < ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);    
  }
}


void loop() 
{
  if (radio.available()) {
    char text[32] = "";
    byte msg;
    radio.read(&msg, sizeof(msg));
    
    Serial.println("Message Recieved");
    Serial.println(text);
    radio.flush_rx();
    if(text[0] == 'H'){    
      pulse();
    }
  }

}

void blink() {
 for(int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(20);
   for(int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void pulse() {
 for(int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(10);
    digitalWrite(leds[i], LOW);
  }
}




