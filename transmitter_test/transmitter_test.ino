#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>

/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int led_pin = 2;
const int red_button_pin = 3;
int red_button_value = HIGH;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(led_pin, OUTPUT);
  pinMode(red_button_pin, INPUT);
}

void loop() {
  //const char text[] = "Hello World";
  //radio.write(&text, sizeof(text));
  red_button_value = digitalRead(red_button_pin);
  if(red_button_value == LOW) {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }
}
