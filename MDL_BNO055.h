
#ifndef MDL_BNO055
#define MDL_BNO055

class COMPASS {
  public:
    COMPASS();
    void init();
    void setOperationMode(byte);
    void remapAxis();
    void setPage(byte);
    byte getPage();
    byte getChipID();
    void getDegrees();
    void getAngularVelocity();
    void getLinerAcce();

    double yaw, roll, pitch;
    double yawAngularVelocity, rollAngularVelocity, pitchAngularVelocity;
    double xLinerAcce, yLinerAcce, zLinerAcce;
    
  private:
    const byte BNO055_FIRST_PAGE   = 0x00;
    const byte BNO055_SECOND_PAGE  = 0x01;
    const byte BNO055_RES_PAGE     = 0x07;

    const byte BNO055_ADDRESS      = 0x28;
    const byte BNO055_RES_OPR_MODE = 0x3D;
    const byte BNO055_RES_CHIP_ID  = 0x00;
    const byte BNO055_IMU_MODE     = 0x08;

    const byte BNO055_X_AXIS       = 0x00;
    const byte BNO055_Y_AXIS       = 0x01;
    const byte BNO055_Z_AXIS       = 0x02;
    const byte BNO055_RES_AXIS_MAP_CONFIG = 0x41;

    const byte BNO055_RES_EUR_HEADING_L = 0x1A;
    const byte BNO055_RES_EUR_HEADING_H = 0x1B;

    const byte BNO055_RES_QUA_X_H = 0x23;
    const byte BNO055_RES_QUA_X_L = 0x22;
    const byte BNO055_RES_QUA_Y_H = 0x25;
    const byte BNO055_RES_QUA_Y_L = 0x24;
    const byte BNO055_RES_QUA_Z_H = 0x27;
    const byte BNO055_RES_QUA_Z_L = 0x26;
    const byte BNO055_RES_QUA_W_H = 0x21;
    const byte BNO055_RES_QUA_W_L = 0x20;

    const byte BNO055_RES_GYR_DATA_X_L = 0x14;
    const byte BNO055_RES_GYR_DATA_X_H = 0x15;
    const byte BNO055_RES_GYR_DATA_Y_L = 0x16;
    const byte BNO055_RES_GYR_DATA_Y_H = 0x17;
    const byte BNO055_RES_GYR_DATA_Z_L = 0x18;
    const byte BNO055_RES_GYR_DATA_Z_H = 0x19;

    const byte BNO055_RES_LIA_DATA_X_L = 0x28;
    const byte BNO055_RES_LIA_DATA_X_H = 0x29;
    const byte BNO055_RES_LIA_DATA_Y_L = 0x2A;
    const byte BNO055_RES_LIA_DATA_Y_H = 0x2B;
    const byte BNO055_RES_LIA_DATA_Z_L = 0x2C;
    const byte BNO055_RES_LIA_DATA_Z_H = 0x2D;
};

#endif