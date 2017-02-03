#ifndef RKT_CONFIG
#define RKT_CONFIG

// aileron pinout
#define aileronPin1 7
#define aileronPin2 8
#define aileronPin3 9
#define aileronPin4 10

// ypr adjust potentiometers pins
#define adjustPin1 14
#define adjustPin2 15
#define adjustPin3 16
#define adjustPin4 17

// key moments during the flight

bool WAIT_FOR_LAUNCH = false;
bool GO_FOR_LAUNCH = false;
bool GOING_UP = false;
bool GOING_DOWN = false;
bool RE_ENTRY_BURN = false;
bool LANDED = false;

#endif