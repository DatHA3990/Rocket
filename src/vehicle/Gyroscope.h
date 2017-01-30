// MPU-6050
// This is a simplified version of Jeff Rowberg's MPU-6050's library

/*
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
