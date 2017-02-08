// Aileron control

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

#include "Aileron.h"

Aileron::Aileron() // servos setup
{
	// attach the servo to the according pin
	Aileron1.attach(aileronPin1);
	Aileron2.attach(aileronPin2);
	Aileron3.attach(aileronPin3);
	Aileron4.attach(aileronPin4);
}

Aileron::~Aileron()
{

}

void Aileron::Write(const float *ypr) // turn the ailerons so that they guide the rocket straight up
{
	int ypr1[3];
	for (int i = 0; i < 3; i++)
		ypr1[i] = ypr[i] * -1;

	int ypr2[3];
	for (int i = 0; i < 3; i++)
		ypr2[i] = ypr[i]; // invert the values

	// aileron 1
	ypr2[2] += adjust1;
	if (ypr2[2] > 30 && ypr2[2] < 150)
		Aileron1.write(ypr2[2]);

	// aileron 2
	ypr1[1] += adjust2;
	if (ypr1[1] > 30 && ypr1[1] < 150)
		Aileron2.write(ypr1[1]);

	// aileron 3
	ypr1[2] += adjust3;
	if (ypr1[2] > 30 && ypr1[2] < 150)
		Aileron3.write(ypr1[2]);

	// ailerons 4
	ypr2[1] += adjust4;
	if (ypr2[1] > 30 && ypr2[1] < 150)
		Aileron4.write(ypr2[1]);
}
