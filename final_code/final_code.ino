#include <SPI.h>  
#include "RF24.h"
#include<Wire.h>
# define accel_module (0x53)
byte values[6];
RF24 myRadio (7, 8);
int pinmotor2=2;
int pinmotor3=3;
int pinmotor4=4;
int pinmotor5=5;
byte addresses[][6] = {"0"};
void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  pinMode(pinmotor2, OUTPUT);
  pinMode(pinmotor3, OUTPUT);
  pinMode(pinmotor4, OUTPUT);
  pinMode(pinmotor5, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(100);
}
 
struct package
{
  int id=-1;
  int id1=-1;
};

int get_a()
{
  int xyzregister=0x32;
  int x,y,z;
  
  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module,6);

  int i=0;
  while(Wire.available()){
    values[i]=Wire.read();
    i++;
  }

  Wire.endTransmission();
  x=(((int)values[1])<<8) | values[0];
  y=(((int)values[3])<<8) | values[2];
  z=(((int)values[5])<<8) | values[4];
  if(x<50  && x>-50)
  {
if(y>30) { x=0; y=1;}
  else if(y<-30) { x=1; y=0;}
  else {x=-1; y=-1;}
  }
  else
  if(x<-10) { x=0;y=0;}
  else if(x>10) { x=1;y=1;}
  return x; 
}


int get_b()
{
   
int xyzregister=0x32;
  int x,y,z;
  
  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module,6);

  int i=0;
  while(Wire.available()){
    values[i]=Wire.read();
    i++;
  }

  Wire.endTransmission();
  x=(((int)values[1])<<8) | values[0];
  y=(((int)values[3])<<8) | values[2];
  z=(((int)values[5])<<8) | values[4];
  if(x<50  && x>-50)
  {
if(y>30) { x=0; y=1;}
  else if(y<-30) { x=1; y=0;}
  else {x=-1; y=-1;}
  }
  else
  if(x<-10) { x=0;y=0;}
  else if(x>10) { x=1;y=1;}
  return y; 
}

struct package data;

void loop()
{
  myRadio.write(&data, sizeof(data)); 

  int s,j;
  s=get_a();
  j=get_b();

 {if(s==0) data.id = s;
  else if(s==1) data.id=s;
  else data.id=2;
  }
  if( s==0 && j==0)
  {
     digitalWrite(pinmotor2, LOW);   
     digitalWrite(pinmotor3, LOW);
     digitalWrite(pinmotor4, LOW);
     digitalWrite(pinmotor5, LOW);
  }
  if( s==2 && j==2)
  {
     digitalWrite(pinmotor2, LOW);   
     digitalWrite(pinmotor3, LOW);
     digitalWrite(pinmotor4, LOW);
     digitalWrite(pinmotor5, LOW);
  }
  if( s==1 && j==1)
  {
     digitalWrite(pinmotor2, HIGH);   
     digitalWrite(pinmotor3, LOW);
     digitalWrite(pinmotor4, HIGH);
     digitalWrite(pinmotor5, LOW);
  }
if( s==0 && j==1)
  {
     digitalWrite(pinmotor2, HIGH);   
     digitalWrite(pinmotor3, LOW);
     digitalWrite(pinmotor4, LOW);
     digitalWrite(pinmotor5, LOW);
  } 
  if( s==1 && j==0)
  {
     digitalWrite(pinmotor2, LOW);   
     digitalWrite(pinmotor3, LOW);
     digitalWrite(pinmotor4, HIGH);
     digitalWrite(pinmotor5, LOW);
  }
{if(j==0) data.id1 = j;
  else if(j==1) data.id1=j;
  else data.id1=2;
  }
  Serial.print(data.id);
  Serial.println(data.id1);
 delay(100);
  
}
