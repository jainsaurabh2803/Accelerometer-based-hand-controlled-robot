#include<Wire.h>

# define accel_module (0x53)
byte values[6];
char output[512];

void setup() {
  // put your setup code here, to run once
  Wire.begin();
  Serial.begin(115200);

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

}

void loop() {
  // put your main code here, to run repeatedly:
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
  sprintf(output,"%d   %d",x,y);
  Serial.print(output);
  Serial.write(10);
  delay(1000);
}
