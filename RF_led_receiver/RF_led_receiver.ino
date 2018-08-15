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
 
unsigned long last_time = 0;    

int led_pins[] = {RED_PIN, YELLOW_PIN, WHITE_PIN, BLUE_PIN, GREEN_PIN, PURPLE_PIN, ORANGE_PIN};
String led_strs[] = {"RED", "YEL", "WHI", "BLU", "GRE", "PUR", "ORA"};
int led_states[] = {0, 0, 0, 0, 0, 0, 0};//0 = off, 1 = on, 2 = blinking
const int led_count = 7;
const int blink_rate = 500;

int blink_state = LOW;

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  for(int i = 0; i < led_count; i++)
  {
    pinMode(led_pins[i], OUTPUT);    
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
    String req_led(led_chars);
   
    char command_chars[4];
    int j = 0;
    for(int i = 3; i < 6; i++ ) {
      command_chars[j] = CMD[i];
      j++;
    }
    command_chars[3]='\0';
    String command(command_chars);
    
    if(req_led == "NON")
    {
      do_all_command(command);
    }
    
    else {
    set_pin_state(req_led, command);
    light_leds();
    }
  }
  unsigned long now = millis(); 
  if(now - last_time > blink_rate){
     blink_leds();
     last_time = now;
  }
}

void blink_leds() {
  for(int i = 0 ; i < led_count; i++) {
    if(led_states[i] == 2) {
      digitalWrite(led_pins[i], blink_state);
    }
    blink_state == LOW ? blink_state = HIGH : blink_state = LOW;
  }
}

void do_all_command(String command) {
  if(command == "PLS")
  {
    temp_off_leds();
    pulse();
    reverse_pulse(); 
  }
  light_leds();
}

void temp_off_leds() {
  for(int i = 0 ; i < led_count; i++) {
    digitalWrite(led_pins[i], LOW); 
  }
}

void light_leds() {
  for(int i = 0 ; i < led_count; i++) {
    if(led_states[i] == 1)
    {
      digitalWrite(led_pins[i], HIGH);
    }
    else {
      digitalWrite(led_pins[i], LOW);
    }
  } 
}

void set_pin_state(String req_led, String command) { 
  
  //try to match the requested led color to one of the support leds
  int pin_index = -1;
  
  for(int i = 0 ; i < led_count; i++)
  {
     if(led_strs[i] == req_led) {
       pin_index = i;
       break;
     }
  }
  
  if(pin_index == -1) return; //led color not found, exit doing nothing
  
  int pin = led_pins[pin_index]; //get the pin number for the requested pin color
  
  //set the pin states
  if(command == "ON ") led_states[pin_index] = 1;
  else if(command == "OFF")  led_states[pin_index] = 0;
  
}
 
void pulse() {
 for(int i = 0; i < led_count; i++) {
    digitalWrite(led_pins[i], HIGH);
    delay(100);
    digitalWrite(led_pins[i], LOW);
  }
}

void reverse_pulse() {
   for(int i = (led_count - 1) ; i >= 0 ; i--) {
    digitalWrite(led_pins[i], HIGH);
    delay(100);
    digitalWrite(led_pins[i], LOW);
  }
}

void randomize() {
int pin = random(0, led_count);
digitalWrite(led_pins[pin], HIGH);
delay(random(50,500));
digitalWrite(led_pins[pin], LOW);
}

void blink() {
  for(int i = 0; i < led_count; i++)
  {  
    digitalWrite(led_pins[i], HIGH);
  }
  delay(200); 
  for(int i = 0; i < led_count; i++)
  {  
    digitalWrite(led_pins[i], LOW);
  } 
  delay(200); 
}

