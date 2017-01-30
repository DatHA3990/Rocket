// Altimeter
// This is a simplified version of Sparkfun's MPL3115A2's library


#include "Arduino.h"
#include "SparkFunMPL3115A2.h"  // MPL3115A2
#include <Wire.h>               // I2C library

class Altimeter
{

  private:

    int altitudeCalibration; //altitude at launch
    int apogeeAltitude = 0;

    MPL3115A2 baro; // baro object

  public:

    Altimeter();
	~Altimeter();

    int GetCalibratedAltitude(); // get calibrated altitude
    int GetApogeeAltitude();
    int GetTemperature(); // get temperature in degrees celsius

};
