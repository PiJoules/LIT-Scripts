// 9 Combinations of Numbers want to make a program to hit all of them
int pin1 = 0;
int randy = 0;
int pinstates[] = {50,50,50};


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
  
  if (pinstates[randy] < 200 ){
      for(int i = 50; i < 256; i+=5){
        analogWrite(pin1,i);
        delay(10);
        pinstates[randy]=i;
      }
  }else if( pinstates[randy] > 250){
      for(int i = 256; i > 50; i-=5){
        analogWrite(pin1,i);
        delay(10);
        pinstates[randy]=i;
    } 
  } 
//  pinstates[randy] = i;
  
}
