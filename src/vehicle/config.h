#ifndef RKT_CONFIG
#define RKT_CONFIG

//motors pin
#define mainEngine 2
#define reEntryEngine 3

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

// key moments during the flight - these are in order
#define WAIT_FOR_LAUNCH true  // wait until we are clear to takeoff
#define GOING_UP        true  // gaining altitude
#define GOING_DOWN      true  // losing altitude

static bool GO_FOR_LAUNCH = false;    // we are go for launch - start engines
static bool APOGEE = false;
static bool RE_ENTRY_BURN = false;    // good for re-entry burn
static bool LANDED = false;           // we have landed

#endif