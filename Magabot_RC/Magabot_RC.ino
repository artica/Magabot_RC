/*  ----------------------------------------------------------------------------
    Artica Creative Computing :: http://artica.cc
    RC Magabot by Guilherme Martins aka guibot

    ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
    ! ! ! ! ! ! ATTENTION ! ! ! ! ! ! !
    
    The program uses 3 RC channels, these channels are connected to the
    Digital Pins 14, 15, 16 (originally analog pins 0 1 2)

    The use of the analog pins 0 1 2 were originally assigned to the battery
    status, this feature was removed from the original lybrary <Magabot.h>
    ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
    ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !

    Enjoy!
    http://artica.cc

    Credits:

    RC PulseIn Serial Read out
    By: Nick Poole
    SparkFun Electronics
    Date: 5
    License: CC-BY SA 3.0 - Creative commons share-alike 3.0
    use this code however you'd like, just keep this license and
    attribute. Let me know if you make hugely, awesome, great changes.
    https://www.sparkfun.com/tutorials/348
  
  
    Code for mixing the analog joytsicks with the differential drive can be found on the following thread:
    http://electronics.stackexchange.com/questions/19669/algorithm-for-mixing-2-axis-analog-input-to-control-a-differential-motor-drive

    ----------------------------------------------------------------------------*/

#include <Wire.h>
#include <Magabot.h>
#include <Metro.h>

Magabot robot;
Metro robotMetro = Metro(2000);
int robotState = 1;

//Define here what protocol you want to use:
char protocol = 'H'; // 'L' for Low Level and 'H' for High Level // EPROM

int inByte = 'p';
char order = '1';

/*  ----------------------------------------------------------------------------
    RC pins and vars
    ----------------------------------------------------------------------------*/

int ch1_pin = 14; //4; // left_horizontal  ???
int ch2_pin = 15; //5; // left_vertical  ???

int ch5_pin = 16; //3; // right_knob

int left_horizontal;
int left_vertical;

int ch1_val;  // left v
int ch2_val;  // left h
int ch5_val;  // speed knob

int speed_knob;
float ch_knob_left_mapped;

// Variables used for mappings maxs and mins input values from the sticks

// motion A max and minimum
#define MA_MAX 1975
#define MA_MIN 986

// motion B max and minimum
#define MB_MAX 1975
#define MB_MIN 986

/*  ----------------------------------------------------------------------------
    rc command vars to be applied to motion control
    ----------------------------------------------------------------------------*/

int analogTmp = 0; //temporary variable to store
int throttle, direction = 0; //throttle (Y axis) and direction (X axis)

int leftMotor, leftMotorScaled = 0; //left Motor helper variables
float leftMotorScale = 0;
float leftMotor_reScaled;

int rightMotor, rightMotorScaled = 0; //right Motor helper variables
float rightMotorScale = 0;
float rightMotor_reScaled;

float maxMotorScale = 0; //holds the mixed output scaling factor

int deadZone = 10; //jostick dead zone


int leftSpeed, rightSpeed;

/*  ----------------------------------------------------------------------------
    SETUP
    ----------------------------------------------------------------------------*/

void setup()
{
  Serial.begin(9600);

  // RC pins
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(ch5_pin, INPUT);

  robot.actuateMotors(0, 0);
  robot.actuateLEDs(255, 255, 255);
}

/*  ----------------------------------------------------------------------------
    LOOP
    ----------------------------------------------------------------------------*/


unsigned long bTimex;

void loop()
{


  if (!beco())
  {
    //Serial.print("beco");
  }
  else
  {

    // map RC RAW values to usable values
    rc_mapper();

    // map usable values to PWM values
    motionMapper();

    // controls motion with IR sensor and RC control
    motionControl();
  }

  // debug function, keep it commented
  //debug();

}

void motionUpdate(int _lspeed, int _rspeed)
{

  robot.actuateMotors(_lspeed, _rspeed);
  robot.update();
}

