#include <Wire.h>
#define DA380_ADDRESS   0x27 
float accelDatax, accelDatay, accelDataz;
void setup() {
  // put your setup code here, to run once:
 Wire.begin();
 Serial.begin(9600);
 Wire.beginTransmission((byte)DA380_ADDRESS);
 write8((byte)DA380_ADDRESS,(byte)0x0F,(byte)0x3);
 write8((byte)DA380_ADDRESS,(byte)0x10,(byte)0xF);
  write8((byte)DA380_ADDRESS,(byte)0x11,(byte)0x1F);
  Wire.endTransmission();
 
}

void loop() {
  // put your main code here, to run repeatedly:
read();
Serial.print("X: ");
Serial.println(accelDatax);
Serial.print("Y: ");
Serial.println(accelDatay);
Serial.print("Z: ");
Serial.println(accelDataz);
Serial.println();
delay(100);
}

void write8(byte address, byte reg, byte value)
{
  Wire.beginTransmission(address);
  #if ARDUINO >= 100
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)value);
  #else
    Wire.send(reg);
    Wire.send(value);
  #endif
  Wire.endTransmission();
}

byte read8(byte address, byte reg)
{
  byte value;

  Wire.beginTransmission(address);
  #if ARDUINO >= 100
    Wire.write((uint8_t)reg);
  #else
    Wire.send(reg);
  #endif
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)1);
  #if ARDUINO >= 100
    value = Wire.read();
  #else
    value = Wire.receive();
  #endif  
  Wire.endTransmission();

  return value;
}

void read(){
  // Read the accelerometer
  Wire.beginTransmission((byte)DA380_ADDRESS);
  //  Wire.write(LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80);
  Wire.endTransmission();
 // Wire.requestFrom((byte)DA380_ADDRESS, (byte)6);

  // Wait around until enough data is available

    uint8_t xlo = read8(DA380_ADDRESS,0x03);
    uint8_t xhi = read8(DA380_ADDRESS,0x02);
    uint8_t ylo = read8(DA380_ADDRESS,0x05);
    uint8_t yhi = read8(DA380_ADDRESS,0x04);
    uint8_t zlo = read8(DA380_ADDRESS,0x07);
    uint8_t zhi = read8(DA380_ADDRESS,0x06);
 

  // Shift values to create properly formed integer (low byte first)
  accelDatax = ((int16_t)(xlo << 8 | xhi)) >> 2;
  accelDatay = ((int16_t)(ylo << 8 | yhi)) >> 2;
  accelDataz = ((int16_t)(zlo << 8 | zhi)) >> 2;

    accelDatax = accelDatax / 512;
  accelDatay = accelDatay / 512;
  accelDataz = accelDataz / 512;
  
  accelDatax = accelDatax* 9.80665F;
   accelDatay = accelDatay * 9.80665F;
    accelDataz = accelDataz* 9.80665F;

}


