// Main file

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

*/
#include "config.h"
#include "Arduino.h"
#include "Aileron.h"
#include "Altimeter.h"
#include "Engines.h"
#include "Gyroscope.h"
#include "KeyMoment.h"

Aileron   m_Ailerons;
Altimeter m_Altimeter;
Gyroscope m_Gyroscope;
KeyMoment m_KeyMoment;
Engine    m_Engine;

int main()
{

#ifdef DEBUG

  Serial.begin(115200);

#endif // DEBUG


  while (WAIT_FOR_LAUNCH) // before takeoff
  {
    if (m_KeyMoment.GoForLaunch());
    {
      m_Engine.FireMain(); // we have takeoff
      break;
    }

#ifdef DEBUG

    Serial.println();

#endif


  }

  while (GOING_UP) // launch
  {

    static float ypr[3];

    if (m_Gyroscope.GetStatus()) //
    {
      m_Gyroscope.GetCalibratedAngle(ypr); // get gyro
    }

    m_Ailerons.Write(ypr); // turn the ailerons to guide the rocket

    m_Engine.ResetMain();
    if (m_KeyMoment.Apogee())
      break;

#ifdef DEBUG

    Serial.print(ypr[0]);
    Serial.print("  ");
    Serial.print(ypr[1]);
    Serial.print("  ");
    Serial.print(ypr[2]);
    Serial.print("  ");

    Serial.println();

#endif

  }

  while (GOING_DOWN) // re-entry and landing
  {

    static float ypr[3];

    if (m_Gyroscope.GetStatus()) //
    {
      m_Gyroscope.GetCalibratedAngle(ypr); // get gyro
    }

    m_Ailerons.Write(ypr); // turn the ailerons to guide the rocket


    static int altitude = m_Altimeter.GetCalibratedAltitude();    // get altitude
    //static int temperature = m_Altimeter.GetTemperature(); // get temperature

    if (m_KeyMoment.ReEntryBurn())
    {
      m_Engine.FireBack();
      m_Engine.ResetBack();
    }

    if (m_KeyMoment.Landed())
      break;

#ifdef DEBUG

    Serial.print(ypr[0]);
    Serial.print("  ");
    Serial.print(ypr[1]);
    Serial.print("  ");
    Serial.print(ypr[2]);
    Serial.print("  ");

    Serial.println();

#endif

  }

  return 0;
}
