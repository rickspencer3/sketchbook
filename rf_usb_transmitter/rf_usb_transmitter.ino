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
boolean red_on = false;
boolean red_button_down = false;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()) {
    String command = Serial.readString();
    Serial.println("Recieved: " + command);
    char CMD[7];
    command.toCharArray(CMD, sizeof(CMD));
    radio.write(&CMD, sizeof(CMD));
  }
}
