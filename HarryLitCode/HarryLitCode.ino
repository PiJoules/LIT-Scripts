// -------------------------------- //
// Harrison Katz - hzk27@drexel.edu //
// -------------------------------- //
#include <NewPing.h>
#include <Servo.h>
Servo myservo;

// Define each pin that's used for this loop
const int SERVO_PIN = 9;  // Data Pin for Servo Motor
const int TRIG_PIN = 10;   // Trigger Pin for Ultrasonic
const int ECHO_PIN = 11;   // Echo Pin for Ultrasonic
const int TOP_PIN = 8;    // 
const int RED_PIN = 3;    // Red Pin for the LEDs
const int GREEN_PIN = 5; // Green Pin for the LEDs
const int BLUE_PIN = 6;  // Blue Pin for the LEDs

// Define integers that can change over time
int countMax = 100;
int topSwitch;
int count;
int flag;
int time;
int x;

// Define the sonar function for the Ultraonic
NewPing sonar(TRIG_PIN, ECHO_PIN, countMax);

// Setup Function that runs once
void setup(){
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  
  // Define Pin Modes for the LED Output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(TOP_PIN, INPUT);
}

// ------------------------ //
// Define the Loop Function //
// ------------------------ //
// This is the main looping function that will run while
// the arduino is functioning continuously
void loop(){
  
  // Define the Pin Mode for the Top Switch and take reading
  // Either the pin will read HIGH or LOW
  topSwitch = digitalRead(TOP_PIN);
  
  // Take Ultrasonic Reading; pass through moveServo Function
  // Rotate will be used to write values to the Servo Motor
  int uS = sonar.ping()/100;
  int rotate = moveServo(uS);
  
  // If the Top Switch is high, rotate equals 95
  if(topSwitch == HIGH){
    rotate = 135;
    Serial.print("HIT");
    delay(50);
  }
  
  // Write rotate values to Servo Motor
  myservo.write(rotate);
  
  // x is used as a color identifyer; Change based on rotate
  // Count used as a heigh measure; Change based on rotate
  x = round(x + (0.50)*(90 - rotate));
  count = round(count + (0.25)*(90 - rotate));
  
  // Small delay and pass color through showRGB Function
  showRGB(x);
  delay(50);
  
  // Keep the Color values within certain range
  if(x > 769 || x < 6){
    x = 7;
  }
  
  // Used to print various values and identifiers to monitor
  Serial.print("Ultra | ");
  Serial.println(uS);
  Serial.print("Rotate | ");
  Serial.println(rotate);
  Serial.print("Count | ");
  Serial.println(count);
  Serial.println("\n");
  
  // If Stationary, flag equals 1
  // Otherwise, flag equals 0 and time resets
  if(rotate == 90){
    flag = 1;
  }
  else{
    flag = 0;
    time = 0;
  }
  
  // If flag continues to equal one, add value to time
  if(flag == 1){
    time = time++;
  }
  
  // If time is greater than 200, start the Waiting Function
  if(time > 200){
    waitingFunction();
  }
}


// % - % - % - % - % - % - % - % - % - % - % - % //
// OTHER FUNCTIONS USED WITHIN THE LOOP FUNCTION //
// % - % - % - % - % - % - % - % - % - % - % - % //

// ------------------------------ //
// Define the Move Servo Function //
// ------------------------------ //
// This function is used to determine which direction and
// how quickly to turn the Servo Motors depending on how
// close the Ultrasonic Sensor reads
int moveServo(int distance){
  
  // Define a variable for servo output
  int servoAction;
  
  // Ensures the distance is within a reasonable range
  if(distance > 20){
    distance = 20;
  }
  
  // This occurs when objects are far away
  if(distance == 0 && count == 0){
    servoAction = 90;
  }
  
  // This occurs when objects are close
  else if(distance < 10 && distance > 0){
    //int y = (3.14/20)*(10-distance) + (3.14/2);
    //servoAction = round(90 - ((45/2)*-cos(y)+(45/2)));
  int y = 90 + 5*(distance - 10);
  servoAction = y; 
  }
  
  // This occurs when objects are in seeable range
  else if(distance > 10){
    //int y = (3.14/20)*(distance-10) + (3.14/2);
    //servoAction = round(90 + ((45/2)*-cos(y)+(45/2)));
  int y = 90 + 5*(distance - 10);
  servoAction = y;
  }
  
  // This occurs when objects are far away
  else if(distance == 0 && count > 0){
    servoAction = 135;
  }
  
  // Anything else, the servo stops moving
  else{
    servoAction = 90;
  }
  
  Serial.print("Dist | ");
  Serial.println(distance);
  Serial.print("Servo | ");
  Serial.println(servoAction);
  
  // The servoAction is returned to be passed as rotation
  return servoAction;
}

// -------------------------- //
// Define the showRGBFunction //
// -------------------------- //
// This function is used to set the various colors through
// the spectrum for each of the RGB LEDs
void showRGB(int color){
  
  // Define initial variables for RGB Intensities
  int redIntensity;
  int greenIntensity;
  int blueIntensity;
  
  // If color falls within range
  if (color <= 255){          // zone 1
  redIntensity = 255 - color;    // red on to off
  greenIntensity = color;        // green off to on
  blueIntensity = 0;}            // blue is off
  
  // If color falls within range
  else if (color <= 511){     // zone 2
  redIntensity = 0;                     // red is off
  greenIntensity = 255 - (color - 256); // green on to off
  blueIntensity = (color - 256);}       // blue off to on
  
  // If color falls within range
  else{ // color >= 512       // zone 3
  redIntensity = (color - 512);         // red off to on
  greenIntensity = 0;                   // green is off
  blueIntensity = 255 - (color - 512);} // blue on to off
  
  // Write all the values to the different RGB Pins
  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
}

// --------------------------- //
// Define the Waiting Function //
// --------------------------- //
// This function is used when the LIT is inactive
// A for loop is used to pulse the Green LED while the
// Ultrasonic waits for a different reading than before
void waitingFunction(){
  
  // Define the integers used for this Function
  int uSPrev = sonar.ping()/100; // Define initial Ultrasonic
  int greenIntensity = 255;      // Define initial greenvalue
  int i;                         // Define for loop iteration
  
  // For Loop to go through the Green LED iterations
  for(i = 1; i<10000; i++){
    
    // Subtract one from the Green Value and add Delay
    greenIntensity--;
    delay(3);
    
    // If the Green Value is less than 0, reset it to 255
    if(greenIntensity < 0){
      greenIntensity = 255;
    }
    
    // Write the values to the different Pins
    analogWrite(BLUE_PIN, greenIntensity);
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    
    // Take a new Ultrasonic Sensor Reading for Comparison
    int uSCurr = sonar.ping()/100;
    
    // Compare the previous and current Ultrasonic Value
    // If the value has changed during the loop: Break
    if(uSCurr != uSPrev){
      break;
    }
  }
  
  // Reset the time back to zero
  time = 0;
}

