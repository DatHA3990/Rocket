// Altimeter

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

#include "Altimeter.h"

Altimeter::Altimeter()
{
	Wire.begin();      // connect I2C
	baro.begin(); // connect to altimeter

	baro.setModeAltimeter();   // Measure altitude above sea level in meters
	baro.setOversampleRate(7); // Set Oversample to the recommended 128
	baro.enableEventFlags();   // Enable all three pressure and temp event flags

	m_altitudeCalibration = baro.readAltitude(); // get calibration for altitude
}

Altimeter::~Altimeter()
{

}

int Altimeter::GetCalibratedAltitude() // get calibrated altitude
{
	int altitude = baro.readAltitude() - m_altitudeCalibration; // get current altitude - altitude at takeoff.

	if (altitude < m_apogeeAltitude)
		m_apogeeAltitude = altitude;

	return altitude;
}

int Altimeter::GetApogeeAltitude()
{
	return m_apogeeAltitude;
}

int Altimeter::GetTemperature() // get temperature in degrees celsius
{
	return baro.readTemp();
}
