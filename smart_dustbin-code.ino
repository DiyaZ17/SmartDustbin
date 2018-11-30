#include <Servo.h>
/*
  HC-SR04 Ping distance sensor:
  VCC to arduino 5v
  GND to arduino GND
  Echo to Arduino pin 6 & 8.
  Trig to Arduino pin 5 & 7.
  sensor-1 is usd for automatically open the lid
  sensor-2 is usd to show garbadge level
*/

Servo servo;   
int trigPin = 5; // sensor 1 
int echoPin = 6; // sensor 1, 

int trig =7; // sensor 2
int echo=8; // sensor 2
 
int servoPin = 9; //attach servo to Arduino pin 9

long duration, dist, average; // duration used to calculate distance, sensor1
long duration2, dist2, average2; // sensor 2

void setup() 
{       
 Serial.begin(9600);   
 servo.attach(servoPin);     
 pinMode(trigPin, OUTPUT);     
 pinMode(echoPin, INPUT);  

 pinMode(trig, OUTPUT);  // sensor 2   
 pinMode(echo, INPUT);  //sensor 2

 pinMode(13, OUTPUT);
 
 servo.write(0); //close cap on power on  
 delay(100);  
 servo.detach(); 
} 

void measure() // sensor 1
{  
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(25);
digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);

dist = (duration/2) / 29.1;    //obtain distance using sensor1
}

void measure2() // sensor 2
{  
digitalWrite(trig, LOW);
delayMicroseconds(5);
digitalWrite(trig, HIGH);
delayMicroseconds(15);
digitalWrite(trig, LOW);

pinMode(echo, INPUT);
duration2 = pulseIn(echo, HIGH);

dist2 = (duration2/2) / 29.1;    //obtain distance
}
void loop() { 
      
    measure();    
    delay(1000); //delay between measurements
 
  if ( dist<15 ) //Change distance as per your need
  {
    servo.attach(servoPin); // servo motor attach to pin 9
    delay(1);
    servo.write(0); //rotates the servo to rotate at specific angle  
    delay(3000);       
    servo.write(150);    
    delay(1000);
    servo.detach();      
    Serial.print("Open Bin's lid at Distance: "); Serial.println(dist);
  }

measure2(); // sensor-2 for measuring level of garbadge
//Serial.print("Distance:"); Serial.println(dist2);

if (dist2<=6) 
{
    Serial.print("Garbadge Level:"); Serial.println(dist2);
    Serial.println("Dustbin is Full.");

    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second  
}

}
