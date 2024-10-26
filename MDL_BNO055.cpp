#include <Arduino.h>
#include <Wire.h>
#include "FARM_I2c.h"
#include "MDL_BNO055.h"

// I2c I2C;

COMPASS::COMPASS() {
    // initCompass();
}

void COMPASS::init() {
    setOperationMode(BNO055_IMU_MODE);
    remapAxis();
}

void COMPASS::setOperationMode(byte mode) {
    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);
    I2C.write(BNO055_RES_OPR_MODE, mode);
}

// なぜか使えない
void COMPASS::remapAxis() {
    byte axisMap = (BNO055_Z_AXIS << 4) | (BNO055_X_AXIS << 2) | BNO055_Y_AXIS;

    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);
    // I2C.write(BNO055_RES_AXIS_MAP_CONFIG, axisMap);
    // I2C.write(0x42, 0b11111111);
}

byte COMPASS::getPage() {
    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);
    return I2C.read(BNO055_RES_PAGE);
}

void COMPASS::setPage(byte page) {
    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);
    I2C.write(BNO055_RES_PAGE, page);
}

byte COMPASS::getChipID() {
    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);
    return I2C.read(BNO055_RES_CHIP_ID);
}

void COMPASS::getDegrees() {
    int16_t upperBit, lowerBit;
    int16_t x, y, z, w;
    double X, Y, Z, W;

    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);

    lowerBit = (uint16_t)I2C.read(BNO055_RES_QUA_X_L);
    upperBit = (uint16_t)I2C.read(BNO055_RES_QUA_X_H);
    x = ((upperBit << 8) | lowerBit);
    X = (double)x / 16384;

    lowerBit = (uint16_t)I2C.read(BNO055_RES_QUA_Y_L);
    upperBit = (uint16_t)I2C.read(BNO055_RES_QUA_Y_H);
    y = ((upperBit << 8) | lowerBit);
    Y = (double)y / 16384;

    lowerBit = (uint16_t)I2C.read(BNO055_RES_QUA_Z_L);
    upperBit = (uint16_t)I2C.read(BNO055_RES_QUA_Z_H);
    z = ((upperBit << 8) | lowerBit);
    Z = (double)z / 16384;

    lowerBit = (uint16_t)I2C.read(BNO055_RES_QUA_W_L);
    upperBit = (uint16_t)I2C.read(BNO055_RES_QUA_W_H);
    w = ((upperBit << 8) | lowerBit);
    W = (double)w / 16384;

    double ysqr = Y * Y;

    double t0 = +2.0 * (W * X + Y * Z);
    double t1 = +1.0 - 2.0 * (X * X + ysqr);
    pitch = std::atan2(t0, t1);

    double t2 = +2.0 * (W * Y - Z * X);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    roll = std::asin(t2);

    double t3 = +2.0 * (W * Z + X * Y);
    double t4 = +1.0 - 2.0 * (ysqr + Z * Z);  
    yaw = std::atan2(t3, t4);

    roll *= 57.2957795131;
    pitch *= 57.2957795131;
    yaw *= -57.2957795131;
}

void COMPASS::getAngularVelocity() {
    int16_t upperBit, lowerBit, x, y, z;

    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);

    lowerBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_X_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_X_H);
    x = (upperBit << 8) | lowerBit;
    pitchAngularVelocity = ((double)x) / 16;

    lowerBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_Y_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_Y_H);
    y = (upperBit << 8) | lowerBit;
    rollAngularVelocity = ((double)y) / 16;

    lowerBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_Z_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_GYR_DATA_Z_H);
    z = (upperBit << 8) | lowerBit;
    yawAngularVelocity = ((double)z) / 16;
}

void COMPASS::getLinerAcce() {
    int16_t upperBit, lowerBit, x, y, z;

    I2c I2C;
    I2C.setAddress(BNO055_ADDRESS);

    lowerBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_X_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_X_H);
    x = (upperBit << 8) | lowerBit;
    xLinerAcce = ((double)x) / 100;

    lowerBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_Y_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_Y_H);
    y = (upperBit << 8) | lowerBit;
    yLinerAcce = ((double)y) / 100;

    lowerBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_Z_L);
    upperBit = (int16_t)I2C.read(BNO055_RES_LIA_DATA_Z_H);
    z = (upperBit << 8) | lowerBit;
    zLinerAcce = ((double)z) / 100;
}