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

//motors pin
#define mainEngine 2
#define reEntryEngine 3

// key moments during the flight - these are in order
bool WAIT_FOR_LAUNCH = false;  // wait until we are clear to takeoff
bool GO_FOR_LAUNCH = false;    // we are go for launch - start engines
bool GOING_UP = false;         // gaining altitude
bool GOING_DOWN = false        // losing altitude
bool RE_ENTRY_BURN = false;    // good for re-entry burn
bool LANDED = false;           // we have landed

#endif