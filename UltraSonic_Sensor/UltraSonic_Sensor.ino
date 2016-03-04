#include <Servo.h>
Servo myservo;
int pos;
int servopin = 6; // Whatever the PWN pin is off the servo
int digread = 8; //Whatever pin is digital read
int UP = 90; // Degree to move the servo up
int DOWN = 180; //Degree to move the servo down
int Count = 0; //Makes sure it doesn't keep spinning

void setup() {
  myservo.attach(servopin);
  pinMode(digread,INPUT);  
}

void loop() {
  
  val = digitalRead(digread);
  
  if(val == HIGH){ // if it detects go up
    myservo.write(UP);
    Count++;
  }else if(val == LOW && Count > 0){ //if it detects go down 
    myservo.write(DOWN); 
    Count--;
  }
   
  delay(10);

}
