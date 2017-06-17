#include "Wire.h" 
#include "I2Cdev.h"  
#include "MPU6050.h"
#include "math.h"
#include "Servo.h"
 
// AD0 low = 0x68
// AD0 high = 0x69
MPU6050 accelgyro1 (0x68);
MPU6050 accelgyro2 (0x69);
 
int16_t ax1, ay1, az1;  
int16_t ax2, ay2, az2;
int16_t gx1, gy1, gz1;
int16_t gx2, gy2, gz2;
uint8_t Accel_range;
uint8_t Gyro_range;
float rotY1=0;
float rotX1=0;
float rotY2=0;
float rotX2=0;

Servo s1,s2,s3,s4;
int pos1,pos2,pos3,pos4;
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  s1.attach(11);
  s2.attach(10);
  s3.attach(5);
  s4.attach(6);
  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
  while (!Serial) {
    
    ; 
  }
  accelgyro1.initialize();
  accelgyro2.initialize();
  delay(1000);
}
 
void loop() {
  accelgyro1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  accelgyro2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
  
  rotX1=0.87*(rotX1+float(gx1)*0.02/131) + 0.13*atan2((double)ay1,(double)az1)*180/PI;
  rotY1=0.87*(rotY1+float(gy1)*0.02/131) + 0.13*atan2((double)ax1,(double)az1)*180/PI;

  rotX2=0.87*(rotX2+float(gx2)*0.02/131) + 0.13*atan2((double)ay2,(double)az2)*180/PI;
  rotY2=0.87*(rotY2+float(gy2)*0.02/131) + 0.13*atan2((double)ax2,(double)az2)*180/PI;

  
  pos1 = 90-(int)rotY1;
  pos2 = 90-(int)rotX1;
  pos3 = 90-(int)rotY2;
  pos4 = 90-(int)rotX2;
  
  
  Serial.print("accelgyro 1 : rotX : ");
  Serial.print(pos2);
  Serial.print("    rotY: ");
  Serial.println(pos1);

  Serial.print("accelgyro 2 : rotX : ");
  Serial.print(pos4);
  Serial.print("    rotY: ");
  Serial.print(pos3);
  
  s1.write(pos1);
  s2.write(pos2);
  s3.write(pos3);
  s4.write(pos4);
   
  delay(20);
}
