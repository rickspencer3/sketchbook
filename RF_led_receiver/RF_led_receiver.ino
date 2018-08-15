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
      do_none_command(command);
    }
    else if (req_led == "ALL"){
      for(int i = 0; i < led_count; i++)
      {
        set_pin_state(i, command);
      }
    }
    else {
    int index = get_index_for_color(req_led);
    set_pin_state(index, command);
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

void do_none_command(String command) {
  temp_off_leds();
  if(command == "PLS")
  {
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

int get_index_for_color(String req_led) {
    //try to match the requested led color to one of the support leds
  int pin_index = -1;
  
  for(int i = 0 ; i < led_count; i++)
  {
     if(led_strs[i] == req_led) {
       pin_index = i;
       break;
     }
  }
  
  return pin_index;
}

void set_pin_state(int pin_index, String command) { 
 
  //set the pin states
  if(command == "ON ") led_states[pin_index] = 1;
  else if(command == "OFF")  led_states[pin_index] = 0;
  else if(command == "BLI") led_states[pin_index] = 2;
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

