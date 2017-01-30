// Aileron control

#include "Arduino.h"
#include <Servo.h> // Servo

#ifndef AILERON_H
#define AILERON_H

// aileron pinout
#define pin1 7
#define pin2 8
#define pin3 9
#define pin4 10

// ypr adjust potentiometers pins
#define adjust0 14
#define adjust1 15
#define adjust2 16
#define adjust3 17

class Aileron
{

  private:

    //aileron object
    Servo aileron1;
    Servo aileron2;
    Servo aileron3;
    Servo aileron4;



  private:

    void Adjust(int & a0, int & a1, int & a2, int & a3);

  public:
    Aileron();
	~Aileron();

    void Write(const float *ypr); // turn the ailerons so that they guide the rocket straight up
};

#endif
