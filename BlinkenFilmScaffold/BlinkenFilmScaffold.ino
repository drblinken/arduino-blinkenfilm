
// available boards BOARD0-BOARD9
#include <EEPROM.h>
#define BOARD2
#include "pins.h"

#define FILMLENGTH 640
#define MAXDELAY 800
#define DELAYFACTOR 50
#define NUMBERLEDS 12

boolean hasFilm = false;
boolean storing = false;
unsigned int count = 0;
unsigned int nextFrame = 0;
byte rollOverCount = 0;

// these are the loop variables for
// storing and showing films and for
// the counter.
unsigned int nextFrameToStore = 0;
unsigned int nextFrameToShow = 0;
unsigned int counter = 0;
unsigned int delayBeforeStart = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1,INPUT);
  for (int i=0;i<NUMBERLEDS;i++)
    pinMode(pins[i], OUTPUT);
  Serial.println("Arduino ready.");
}

void loop(){
  if (Serial.available() > 0) {
    storeFilm();
    hasFilm = true;
    storing = true;
    delayBeforeStart=100;
  }
  else {
    if (hasFilm)
    {
      if (delayBeforeStart > 0)
        delayBeforeStart--;
      else {
        if (storing){
          displayFilm();
          storing = false;
        }
        playFilm();
      }

    }
    else
      doCount();
  }
}

void playFilm(){
}
void storeFilm(){
}

void showFrame(unsigned int frame){
}
/*
   just a little animation to do somethings before
   a film has been transferred
*/
void doCount(){
  // just to do something: replace this with the counter

  for (int i=0;i<NUMBERLEDS;i++){
    digitalWrite(pins[i],ON);
    delay(100);
  }
   for (int i=0;i<NUMBERLEDS;i++){
    digitalWrite(pins[i],OFF);
    delay(100);
  }

}

int normalizeDelay(int d){
  if (d > MAXDELAY)
    d = MAXDELAY;
  return d/ DELAYFACTOR;
}

int normalizedToDelay(int n){
  if (n == 0) return MAXDELAY;
  return n*DELAYFACTOR;
}



/* 
     debug method to show the film in eeprom 
*/
void displayFilm(){
  int upperBound = (rollOverCount > 0) ? FILMLENGTH : nextFrameToStore;
  for(int i = 0;i<upperBound-1;i=i+2){
    Serial.print("Frame no ");
    Serial.println(i);
    print_binary(EEPROM.read(i),8);
    Serial.println();
    print_binary(EEPROM.read(i+1),8);
    Serial.println();
  }
  Serial.print("rollOverCount ");
  Serial.println(rollOverCount);
}
// copied from http://www.phanderson.com/arduino/arduino_display.html

void print_binary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0))
        {
            Serial.print("_");
        }
    }
}























