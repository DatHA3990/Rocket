// MPU-6050

/*

  Copyright <2017> <Dat HA>

  Redistribution and use in source and binary forms,
  with or without modification, are permitted
  provided that the following conditions are met:

  1. Redistributions of source code must retain the
  above copyright notice, this list of conditions
  and the following disclaimer.

  2. Redistributions in binary form must reproduce
  the above copyright notice, this list of
  conditions and the following disclaimer in the
  documentation and/or other materials provided
  with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
  HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
  GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
  IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.




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

Gyroscope::~Gyroscope()
{

}

bool Gyroscope::GetStatus()
{
  Gyro.resetFIFO(); // reset the fifo, here to prevent lag or code freeze
  bool mpuInterrupt = false;
  mpuIntStatus = Gyro.getIntStatus();
  fifoCount = Gyro.getFIFOCount();

  return (mpuIntStatus & 0x02) ? true : false;
}

void Gyroscope::GetCalibratedAngle(float *ypr) // get gyroscope's angle
{
  while (fifoCount < packetSize) fifoCount = Gyro.getFIFOCount();
  Gyro.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;

  Gyro.dmpGetQuaternion(&q, fifoBuffer);
  Gyro.dmpGetGravity(&gravity, &q);
  Gyro.dmpGetYawPitchRoll(ypr, &q, &gravity); // get actual angle values

  ypr[0] = (ypr[0] * 180 / M_PI);
  ypr[1] = (ypr[1] * 180 / M_PI) + 90;
  ypr[2] = (ypr[2] * 180 / M_PI) + 90;
}
