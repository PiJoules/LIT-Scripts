#include <Servo.h>
#include <NewPing.h>
Servo myservo;
int pos;
int servopin = 5; // Whatever the PWN pin is off the servo
int UP = 0; // Degree to move the servo up
int DOWN = 180; //Degree to move the servo down
int Count = 0; //Makes sure it doesn't keep spinning
int NOTHING = 90; //Degree to move the servo to do nothing
double val;
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  myservo.attach(servopin);
  Serial.begin(115200);
}

void loop() {
  
//  val = analogRead(AnRead);
//  Serial.println(val);
  delay(50);
  int uS = sonar.ping();
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  
  if(uS < 15){ // if it detects go up
    myservo.write(UP);
    Serial.println("Servo is going up");
    Count++;
  }else if(uS > 15 && Count > 0){ //if it detects go down 
    myservo.write(DOWN); 
    Serial.println("Servo is going down");
    Count--;
  }else{
    myservo.write(NOTHING);
    Serial.println("Servo is doing nothing");
  }
  
//  delay(10);
  Serial.print("Count is " );
  Serial.print(Count);
  Serial.println("\n");
}
