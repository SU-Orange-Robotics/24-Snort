#include "vex.h"
#include "drive.h"
#include "robot-config.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// 8 motor 4 WHEEL mechanum drive
// A front, B back
motor LeftMotorA(PORT17, gearSetting::ratio18_1, false);
motor LeftMotorB(PORT18, gearSetting::ratio18_1, true);
motor LeftMotorC(PORT2, gearSetting::ratio18_1, false);
motor RightMotorA(PORT13, gearSetting::ratio18_1, true);
motor RightMotorB(PORT12, gearSetting::ratio18_1, false);
motor RightMotorC(PORT1, gearSetting::ratio18_1, true);

motor intake(PORT8, gearSetting::ratio18_1, false);
motor intakeRoller(PORT10, gearSetting::ratio18_1, false);

motor wingL(PORT7, gearSetting::ratio18_1, false);
motor wingR(PORT14, gearSetting::ratio18_1, true);

motor catapultA(PORT19, gearSetting::ratio18_1, true); //left
motor catapultB(PORT11, gearSetting::ratio18_1, false); //right

rotation catapultRot(PORT5, false);

inertial imu(PORT15);
gps gps1(PORT4, 0, 0, distanceUnits::mm, 180); // port, x, y, distance units, angle offset, turn direction?
rotation odomLeft(PORT10, true);
rotation odomRight(PORT2, false);
rotation odomCenter(PORT3, true);

optical colorSensor(PORT14);

brain Brain;
controller Controller1(controllerType::primary);

double initialHeading = 0;//initial 

// declare object-oriented stuff here (that should be globally accessible)
Drive drive;
Wings wings;