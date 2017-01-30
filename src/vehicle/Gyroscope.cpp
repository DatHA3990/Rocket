// MPU-6050

#include "Gyroscope.h"

Gyroscope::Gyroscope() // gyroscope setup
{
  Wire.begin();          // connect I2C
  Wire.setClock(400000); // set I2C speed

  Gyro.initialize();

  devStatus = Gyro.dmpInitialize();

  Gyro.setXGyroOffset(220);   // X, Y, Z offset
  Gyro.setYGyroOffset(76);
  Gyro.setZGyroOffset(-85);
  Gyro.setZAccelOffset(1788); // 1688 factory default for my test chip

  if (devStatus == 0) {
    Gyro.setDMPEnabled(true);
    mpuIntStatus = Gyro.getIntStatus();
    dmpReady = true;
    packetSize = Gyro.dmpGetFIFOPacketSize();
  }
}

void Gyroscope::GetAngle(float *ypr) // get gyroscope's angle
{
  Gyro.resetFIFO(); // reset the fifo, here to prevent lag or code freeze
  bool mpuInterrupt = false;
  mpuIntStatus = Gyro.getIntStatus();
  fifoCount = Gyro.getFIFOCount();

  if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = Gyro.getFIFOCount();
    Gyro.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    Gyro.dmpGetQuaternion(&q, fifoBuffer);
    Gyro.dmpGetGravity(&gravity, &q);
    Gyro.dmpGetYawPitchRoll(ypr, &q, &gravity); // get actual angle values
  }

  ypr[0] = (ypr[0] * 180 / M_PI);
  ypr[1] = (ypr[1] * 180 / M_PI) + 90;
  ypr[2] = (ypr[2] * 180 / M_PI) + 90;
}
