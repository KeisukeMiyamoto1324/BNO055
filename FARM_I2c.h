
#ifndef FARM_I2C
#define FARM_I2C

class I2c {
  public:
    I2c();
    void setAddress(byte);
    void write(byte, byte);
    byte read(byte);
    int reads(byte, int);
    
  private:
    int address;
};

#endif