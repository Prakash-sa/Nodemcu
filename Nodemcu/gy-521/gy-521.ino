#include "temp.h"


const uint8_t scl=5;
const uint8_t sda=4;
void setup() {
  Serial.begin(9600);
  Wire.begin(sda,scl);
   //setup_mpu_6050_registers();
MPU6050_Init();
}

void loop() {
  /*
  read_mpu_6050_data();
  */
  double Ax, Ay, Az, T, Gx, Gy, Gz;
  
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  
  float t = ((float)T/340.00)+36.53;
  Serial.print("Temp :");
  Serial.println(t);

  Serial.println();

}
