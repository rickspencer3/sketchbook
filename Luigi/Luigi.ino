#include <dht.h>
#include <Servo.h>  // servo library

Servo servo1;  // servo control object

int servoPin = 5;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

dht DHT;
unsigned long rate = 60000L;
void setup()
{
  //Initial all the things
  Serial.begin(9600);
  servo1.attach(servoPin);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  //Test all the things
  setColor(0, 255,255);
  servo1.write(0);
  delay(5000); // give some time to attach something to servo
 
  //cycle the other colors
  setColor(255, 255,0);
  servo1.write(90);
  delay(1000);
  setColor(255, 0, 255);
  servo1.write(180);
  delay(1000);
  Serial.println("<----Indoor Weather Vain---->");
}

void loop() {
  refresh();
  delay(rate); 
}
void refresh()
{
  
  //get a reading
  DHT.read11(A0);
  
  //get the tempuature and set the angle of the servo
  float temp = DHT.temperature;
  float angle = (temp - 15) * 10;//formula for indoors (assumes about 60F - 80F inside)
  servo1.attach(servoPin);
  servo1.write(angle);
  delay(1000); // give the servo some time to reach the right position before detaching
  servo1.detach(); // if you don't detach, the servo may hum
  
  //get the humidity and set the rgb led
  float humidity = DHT.humidity;

  //choose green, blue, purple, or red depending on humidity %
  //for the type of led I am using, you turn OFF the current to turn on the led (0 = full power, 255 = off)
  if(humidity < 50) {
     setColor(255, 0, 255); 
  }
  else if(humidity < 60) {
   setColor(255, 255, 0) ;
  }
  else if(humidity > 75) {
    setColor(0, 255, 255);
  }
  else {
    setColor(254, 255, 0);//red is very bright compared to blue
  }
  
  //print out the results to serial
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");
}

void setColor(int red, int green, int blue)
{                                                          
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

