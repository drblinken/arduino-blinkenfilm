
// available boards BOARD0-BOARD9

#define BOARD0
#include "pins2.h"

int NUMBERLEDS = 12; 
int buttonState = 0;    // variable for reading the pushbutton status
int buttonState2 = 0;
int programNumber = 0;  // variables to iterate through the programs
int programCount = 4;

void setup() { 
    pinMode(buttonPin,INPUT);
    for (int i=0;i<NUMBERLEDS;i++)
      pinMode(pins[i], OUTPUT);   
}

void loop() {
  
  checkButton();
  switch(programNumber) {
    case 0:
      runner();
      blink();
      chase();
      break;
    case 1:
      blink();
      break;
    case 2:
      chase();
      break;
    case 3:
      runner();
      break;
  }   

}
void checkButton(){
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2); // this is garbage if there is no second button
  if ((buttonState == ON) || (hasTwoButtons && (buttonState2 == ON))){
    programNumber = (programNumber+1) % programCount;
    buttonAck();
  }
}
void buttonAck(){
  
  digitalWrite(pins[0],ON);
  digitalWrite(pins[NUMBERLEDS-1],ON);
  delay(200);
  
  digitalWrite(pins[0],OFF);
  digitalWrite(pins[NUMBERLEDS-1],OFF);
}
void allOff(){
  for (int i=0;i<NUMBERLEDS;i++)
    digitalWrite(pins[i],OFF);
}
void chase(){
    
  for (int i=0;i<NUMBERLEDS;i++){
    digitalWrite(pins[i],ON);
    delay(100);
  }
   for (int i=0;i<NUMBERLEDS;i++){
    digitalWrite(pins[i],OFF);
    delay(100);
  } 
}
void blink(){
  for (int i=0;i<2;i++){
  for (int i=0;i<NUMBERLEDS;i++)
    digitalWrite(pins[i],ON);
  delay(500);
  for (int i=0;i<NUMBERLEDS;i++)
    digitalWrite(pins[i],OFF);
    delay(500);
  }
}
int ledbefore(int n){
  if (n == 0)
    return NUMBERLEDS - 1;
  return n-1;
}
void runner(){
  allOff();
  for (int i=0;i<NUMBERLEDS;i++){
    digitalWrite(pins[i],ON);
    digitalWrite(pins[ledbefore(i)],OFF);
    delay(100);
  }

}



