#include <SPI.h>
#include "RF24.h"

int motorPin = 4;
int motorPin1 = 9;
int motorPin2 = 10;
int motorPin3 = 2;

RF24 myRadio (7, 8);

struct package
{
  int id = 0;
  int id1 = 0;
};


byte addresses[][6] = {"0"};
struct package data;

void setup()
{
  Serial.begin(115200);
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  delay(1000);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  delay(100);
}

void loop()
{
  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    int s = data.id;
    int j = data.id1;
    Serial.print(s);
    Serial.print(j);
    Serial.print("\n");

    if(s==1 && j==0){
    digitalWrite(motorPin2, HIGH);   
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin, LOW);
     digitalWrite(motorPin1, LOW);    
   }
      
 if(s==0 && j==1){

    digitalWrite(motorPin2, LOW);   
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin, HIGH);
     digitalWrite(motorPin1, LOW);    
   } 
   if(s==0 && j==0){

    digitalWrite(motorPin2, LOW);   
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin, LOW);
     digitalWrite(motorPin1, HIGH);    
   } 
   
   if(s==1 && j==1){
 
    digitalWrite(motorPin2, HIGH);   
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin, HIGH);
     digitalWrite(motorPin1, LOW);    
   }
     
if(s==2 && j==2)   
      {digitalWrite(motorPin2, LOW);   
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin, LOW);
     digitalWrite(motorPin1, LOW);    
   }
      delay(100);


  }
}

