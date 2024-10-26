#include <Wire.h>
#include <Arduino.h>
#include <FARM_I2c.h>
#include <MDL_BNO055.h>

COMPASS Compass;
I2c I2C;
ALTITUDE Altitude;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Compass.init();
}

void loop()
{
  Compass.getDegrees();
  Compass.getAngularVelocity();
  Compass.getLinerAcce();
  
  Serial.print((int)Compass.yaw);
  Serial.print("  ");
  Serial.print((int)Compass.pitch);
  Serial.print("  ");
  Serial.print((int)Compass.roll);
  Serial.print("  ");
  Serial.println("");

  Serial.print((int)Compass.yawAngularVelocity);
  Serial.print("  ");
  Serial.print((int)Compass.pitchAngularVelocity);
  Serial.print("  ");
  Serial.print((int)Compass.rollAngularVelocity);
  Serial.print("  ");
  Serial.println("");

  Serial.print(Compass.xLinerAcce);
  Serial.print("  ");
  Serial.print(Compass.yLinerAcce);
  Serial.print("  ");
  Serial.print(Compass.zLinerAcce);
  Serial.print("  ");
  Serial.println("");
}
