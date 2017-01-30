// Main file

#include "Arduino.h"
#include "Aileron.h"
#include "Altimeter.h"
#include "Gyroscope.h"

Aileron Fins;
Altimeter Alt;
Gyroscope Mpu;

int main()
{
	while (Alt.GetCalibratedAltitude() + 2 > Alt.GetApogeeAltitude()) // going up
	{

	}

	while (1) // going down
	{
		static float ypr[3];
		Mpu.GetAngle(ypr); // get gyro angles

		static int altitude = Alt.GetCalibratedAltitude();    // get altitude
		//static int temperature = Alt.GetTemperature(); // get temperature

		Fins.Write(ypr); // turn the ailerons to guide the rocket
	}
}
