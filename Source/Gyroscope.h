// MPU-6050

#include "Arduino.h"
#include "I2Cdev.h"                     // I2C
#include <Wire.h>                       // I2C
#include "MPU6050_6Axis_MotionApps20.h" // MPU-6050

class Gyroscope
{

  private:

    MPU6050 Gyro;          // gyro objetct

    Quaternion q;          // [w, x, y, z] quaternion container
    VectorFloat gravity;   // [x, y, z]    gravity vector

    bool dmpReady = false; // set true if DMP init was successful

    int mpuIntStatus;      // holds actual interrupt status byte from mpu
    int devStatus;         // return status after each device operation
    int packetSize;        // expected DMP packet size (default is 42 bytes)
    int fifoCount;         // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64];    // FIFO storage buffer

  public:

    Gyroscope(); // gyroscope setup

    void GetAngle(float *ypr); // get gyroscope's angle
};
