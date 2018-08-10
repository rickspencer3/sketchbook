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
  for(int i = 0; i < ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);    
  }
}

void loop() {
  switch(random(0,2)) {
    case 0:
      for(int i = 0; i < random(4,10) ; i++)
      {
        blink();
      }
      break;
    case 1:
      pulse();
      reverse_pulse();
      break;
    case 2:
     for(int i = 0; i < 20 ; i++)
    {
      randomize();
    }
    break;
       
  }
  delay(random(10000,120000));
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

