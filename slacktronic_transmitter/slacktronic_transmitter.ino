#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//set up the radio based on the circuit wiring 
RF24 radio(8, 7); 
const byte address[6] = "00001";

//set up the led based on the circuit wiring
const int led_pin = 3;

//set up Slack state
boolean away = false;
boolean message_waiting = false;

//set up led state
int led_state = LOW;
const int blink_rate = 500;
unsigned long last_time = 0;    

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  //set up the USB  and the pin
  Serial.begin(57600);
  Serial.println("<Arduino is ready>");
  pinMode(led_pin, OUTPUT);
  
  //flash the led when turning on
  for(int i = 0 ; i < 5 ; i++) {
    digitalWrite(led_pin, HIGH);
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(100); 
  }
} 

void loop() {
  if (Serial.available()) {
    String slacktronic_message = Serial.readString();
    String command = "      ";
    if(slacktronic_message == "A") {
      command = "YELBLI";
      away = true;
    }
    else if(slacktronic_message == "a") {
      command = "YELOFF"; 
      away = false;
    }
    else if(slacktronic_message == "B") {
       command = "REDBLI"; 
       message_waiting = true;
    }
    else if(slacktronic_message == "b") {
       command = "REDOFF"; 
       message_waiting = false;
    }
    char CMD[7];
    command.toCharArray(CMD, sizeof(CMD));
    radio.write(&CMD, sizeof(CMD));
    Serial.println("Sent: " + command);
    
    //flash the led quickly when a signal is sent
    digitalWrite(led_pin, HIGH);
    delay(100);
    digitalWrite(led_pin, LOW);
  }
  
  //set the led state based on slack state
  unsigned long now = millis(); 
  if(now - last_time > blink_rate){
     if(message_waiting){
       //blink if message(s) waiting (whether or not away)
       
       //toggle the led state
       led_state == LOW ? led_state = HIGH : led_state = LOW;
       digitalWrite(led_pin, led_state);
     }
     else if(away) {
       //if just away but no messages waiting, keep the pin on
       led_state = HIGH;
       digitalWrite(led_pin, led_state);      
     }
     else {
        //of not away and no message, turn off the led
        led_state = LOW;
        digitalWrite(led_pin, LOW);
     }
     
     last_time = now;
  }
}
