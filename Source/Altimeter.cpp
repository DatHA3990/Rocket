// Altimeter

#include <Altimeter.h>

Altimeter::Altimeter()
{
  Wire.begin();      // connect I2C
  baro.begin(); // connect to altimeter

  baro.setModeAltimeter();   // Measure altitude above sea level in meters
  baro.setOversampleRate(7); // Set Oversample to the recommended 128
  baro.enableEventFlags();   // Enable all three pressure and temp event flags


  altitudeCalibration = baro.readAltitude(); // get calibration for altitude
}

int Altimeter::GetCalibratedAltitude() // get calibrated altitude
{
  int altitude = baro.readAltitude() - altitudeCalibration; // get current altitude - altitude at takeoff.

  if (altitude < apogeeAltitude) apogeeAltitude = altitude;

  return altitude;
}

int Altimeter::GetApogeeAltitude()
{
  return apogeeAltitude;
}

int Altimeter::GetTemperature() // get temperature in degrees celsius
{
  return baro.readTemp();
}
