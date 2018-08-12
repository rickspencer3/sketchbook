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

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  for(int i = 0; i < ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);    
  }
}

void loop() {
  if (radio.available()) {
    char CMD[7] = "";
    radio.read(&CMD, sizeof(CMD));
    
    char led_chars[4];
    for(int i = 0; i < 3; i++ ) {
      led_chars[i] = CMD[i]; 

    }
    led_chars[3]='\0';
    String led(led_chars);
    
    char command_chars[4];
    int j = 0;
    for(int i = 3; i < 6; i++ ) {
      command_chars[j] = CMD[i];
      j++;
    }
    command_chars[3]='\0';
    String command(command_chars);
    
    pin_command(led, command);
  }
}

void pin_command(String led, String command) { 
  int pin = 0;
  if(led == "RED") {
    pin = 2;
  }
  if(command == "ON ") digitalWrite(pin, HIGH);
  else if(command == "OFF") digitalWrite(pin, LOW);
}

void pulse() {
 for(int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
}

void reverse_pulse() {
   for(int i = (ledCount - 1) ; i >= 0 ; i--) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
}

void randomize() {
int pin = random(0, ledCount);
digitalWrite(leds[pin], HIGH);
delay(random(50,500));
digitalWrite(leds[pin], LOW);
}

void blink() {
  for(int i = 0; i < ledCount; i++)
  {  
    digitalWrite(leds[i], HIGH);
  }
  delay(200); 
  for(int i = 0; i < ledCount; i++)
  {  
    digitalWrite(leds[i], LOW);
  } 
  delay(200); 
}

