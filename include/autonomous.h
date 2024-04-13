#pragma once

#include "vex.h"

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // head to head auto
  /*
  drive.driveForward(100);
  wait(300, msec);
  drive.stop();
  catapultArm();
  drive.driveForward(-100);
  wait(1200, msec);
  drive.stop();

  */
  
  // turning testing auto
  /*
  drive.turnPID(0);

  wait(1, sec);

  drive.turnPID(M_PI);

  wait(1, sec);

  drive.turnPID(M_PI / 2);

  wait(1, sec);

  drive.turnPID(5 * M_PI / 6);
  */
  
  // auto skills code

  drive.driveForward(100);
  wait(300, msec);
  drive.stop();
  catapultArm();
  drive.driveForward(-100);
  wait(600, msec); //tune
  drive.stop();
  drive.turnPID(M_PI / -2);
  drive.driveForward(100);
  wait(1000, msec); //tune
  drive.stop();

  drive.turnPID(0 - 0.3);

  drive.driveForward(-100);
  wait(300, msec); //tune
  drive.stop();

  drive.turnPID((-1 * M_PI / 4) + 0.1);
  drive.driveForward(100);
  wait(1400, msec); // tune
  drive.stop();

  intakeSpin(true);
  wait(300, msec);

  int i;
  for (i = 0; i < 10; i++) {
    //reverse away from bar for match load
    drive.driveForward(-100);
    wait(400, msec); //tune
    drive.stop();

    catapultLaunch();
    waitUntil(getCatAccel() <= 0.05);
    catapultArm();

    // give time for match load to be loaded (in addition to catapult arm time) and allow for 
    drive.turnPID((-1 * M_PI / 4) + 0.03);
    //wait(500, msec);

    //drive forward into bar
    drive.driveForward(100);
    wait(650, msec); //tune
    drive.stop();

    //give time for ball to get into catapult
    wait(600, msec); // tune      or replace with color sensor
  }
  catapultLaunch();
  intakeStop();
}