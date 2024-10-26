#include <Arduino.h>
#include <Wire.h>
#include "FARM_I2c.h"

I2c::I2c():address(0x00) {

}

void I2c::setAddress(byte add) {
    address = add;
}

void I2c::write(byte resister, byte data) {
    Wire.beginTransmission(address);
    Wire.write(resister);
    Wire.write(data);
    Wire.endTransmission();
}

byte I2c::read(byte resister) {
    Wire.beginTransmission(address);
    Wire.write(resister);
    Wire.endTransmission(false);
    Wire.requestFrom(address, 1);

    return Wire.read();
}

int I2c::reads(byte resister, int bytes) {
    Wire.beginTransmission(address);
    Wire.write(resister);
    Wire.endTransmission(false);
    Wire.requestFrom(address, bytes);

    int data = 0, dataCount = 0;

    while(Wire.available()) {
        data = (data << (dataCount*8)) | Wire.read();
        dataCount++;
    }

    return data;
}