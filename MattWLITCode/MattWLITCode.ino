// Light Interative Technology
//Matthew Wiese, March 29th, 2016

//   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
//   distance to the closest object in range. To do this, it sends a pulse
//   to the sensor to initiate a reading, then listens for a pulse 
//   to return.  The length of the returning pulse is proportional to 
//   the distance of the object from the sensor.
//     
//   The circuit:
//  * VCC connection of the sensor attached to +5V
//  * GND connection of the sensor attached to ground
//  * TRIG connection of the sensor attached to digital pin 2
//  * ECHO connection of the sensor attached to digital pin 4
//   Original code for Ping))) example was created by David A. Mellis
//   Adapted for HC-SR04 by Tautvidas Sipavicius
//   This example code is in the public domain.
// */


#include <Servo.h> // including the servo library
Servo myservo;  // create servo object to control a servo

//assigning variables
const int SERVO_PIN = 9;
const int trigPin = 11;
const int echoPin = 10;
int Pin_LED_Red = 6;
int Pin_LED_Green = 3;
int Pin_LED_Blue = 5; 
int threshold = 5; //the distance in inches at which the ball will stop
int leeway = 3; // amount of variance in inches in which the ball will stop (in our case between 4-8 inches)
int color = 0 ; 
int buttonPin = 2; // the number of the pushbutton pin
 
 //Variables will change:
 int buttonState = 0; //Varialbe for reading the pushbutton status
 
void setup() {
  // initialize serial communication for ultrasonic sensor:
  Serial.begin(9600);
   
//we need the mode of the LED pins to be outputs
// thus setting the mode of the pins:
pinMode(Pin_LED_Red, OUTPUT);
pinMode(Pin_LED_Green, OUTPUT);
pinMode(Pin_LED_Blue, OUTPUT); 
myservo.attach(SERV0_PIN);  // attaches the servo on pin 9 to the servo object

//initialize the pushbutton pin as input:
pinMode(buttonPin, INPUT); 

}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //Printing the distance to the command line (control + shift + m)
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //Read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); 
  
  // if the ground is far from the ball:
  if (inches > (threshold + (leeway/2)) ) {
//   digitalWrite(Pin_LED_Green, LOW);
//   digitalWrite(Pin_LED_Blue, LOW);
//   digitalWrite(Pin_LED_Red, HIGH); //turn the LED to red
    showRGB(color);
   myservo.write(70);            // rotate very slowly clockwise (down)
    Serial.print("you're far!");
   color = color + 6; 
  if (color > 765){
        color = 0 ; 
        } 
  }
  
  // if the ground is close to the ball:
  if (inches < (threshold - (leeway/2)) && inches > 0  ) {
//    digitalWrite(Pin_LED_Blue, LOW);
//    digitalWrite(Pin_LED_Red, LOW);
//    digitalWrite(Pin_LED_Green, HIGH); //turn the led to green
    showRGB(color);
    myservo.write(110);                 // rotate very slowly clockwise (UP)
       Serial.print("you're close!");  
       color = color + 6;
       if (color > 765){
        color = 0 ; 
        }
  }
  
  //if the ground is within the threshold, stay still
  if (inches < (threshold + (leeway/2)) && inches > (threshold - (leeway/2))){
//    digitalWrite(Pin_LED_Red, LOW);
//    digitalWrite(Pin_LED_Green, LOW);
//    digitalWrite(Pin_LED_Blue, HIGH); //turn LED to Blue
      showRGB(color);
        Serial.print("you're just right!");
        myservo.write(90);        // stop the servo motor
        color = color + 1; 
        if (color > 765){
        color = 0 ; 
        }
  }
  //if ultrasonic sensor reads zero, ignore it, it's probably an error
        if (inches == 0 ){
//    digitalWrite(Pin_LED_Red, LOW);
//    digitalWrite(Pin_LED_Green, LOW);
//    digitalWrite(Pin_LED_Blue, HIGH); //turn LED to Blue
      showRGB(color);
        Serial.print("zero, this might be an error");
        myservo.write(90);        // stop the servo motor
        color = color + 1; 
        if (color > 765){
        color = 0 ; 
  }
  }
  if (color > 765){
color = 0 ; 
  }
  //If button is pressed, cycle through all the colors; 
  if (buttonState == HIGH){
   Serial.print("I'm cycling baby!");  
    for(int x = 0; x < 767; x++){
      showRGB(x);
      delay(500); 
    }
    }
  Serial.print(color); //writing the color value to the serial monitor
  delay(100); // necessary delay for the ultrasonic sensor.
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void showRGB(int color)
{
int redIntensity;
int greenIntensity;
int blueIntensity;

// Here we'll use an "if / else" statement to determine which
// of the three (R,G,B) zones x falls into. Each of these zones
// spans 255 because analogWrite() wants a number from 0 to 255.

// In each of these zones, we'll calculate the brightness
// for each of the red, green, and blue LEDs within the RGB LED.

if (color <= 255)          // zone 1
{
redIntensity = 255 - color;    // red goes from on to off
greenIntensity = color;        // green goes from off to on
blueIntensity = 0;             // blue is always off
}
else if (color <= 511)     // zone 2
{
redIntensity = 0;                     // red is always off
greenIntensity = 255 - (color - 256); // green on to off
blueIntensity = (color - 256);        // blue off to on
}
else // color >= 512       // zone 3
{
redIntensity = (color - 512);         // red off to on
greenIntensity = 0;                   // green is always off
blueIntensity = 255 - (color - 512);  // blue on to off
}

// Now that the brightness values have been set, command the LED
// to those values

analogWrite(Pin_LED_Red, redIntensity);
analogWrite(Pin_LED_Blue, blueIntensity);
analogWrite(Pin_LED_Green, greenIntensity);
}


