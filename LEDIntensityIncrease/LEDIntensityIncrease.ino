
//int pin = 13;
int pin1 = 0;
int randy = 0;


void setup() {
  // put your setup code here, to run once:

  analogWrite(13,50);
  analogWrite(11,50);
  analogWrite(10,50);
}

void loop() {
  
  randy = random(0,3);
  Serial.print(randy + "\n");
  
  if (randy == 0){
    pin1 = 13; 
  }
  else if(randy == 1){
    pin1 = 11;
  }
  else if(randy == 2){
    pin1 = 10;
  }
  
  
  for(int i = 50; i < 256; i+=5){
    analogWrite(pin1,i);
    delay(100);
  }
  
  for(int j = 256; j > 50; j-=5){
    analogWrite(pin1,j);
    delay(100);
  }
  
  

}
