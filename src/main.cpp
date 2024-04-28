/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zhuowz                                                    */
/*    Created:      10/6/2023, 6:48:52 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "drive.h"
#include "robot-config.h"
#include "intakeCat.h"
#include "wings.h"
#include "odometry.h"
#include "autonomous.h"
using namespace vex;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // Current limitting
  intakeRoller.setMaxTorque(0.625, currentUnits::amp);
  catapultA.setMaxTorque(2, currentUnits::amp);
  catapultB.setMaxTorque(2, currentUnits::amp);
  wingL.setMaxTorque(0.2, currentUnits::amp);
  wingR.setMaxTorque(0.2, currentUnits::amp);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  wings.initWings();

  // const int initalRotation = 90;
  // imu.setRotation(initalRotation, rotationUnits::deg);

  LeftMotorA.setStopping(brakeType::brake);
  LeftMotorB.setStopping(brakeType::brake);
  LeftMotorC.setStopping(brakeType::brake);
  RightMotorA.setStopping(brakeType::brake);
  RightMotorB.setStopping(brakeType::brake);
  RightMotorC.setStopping(brakeType::brake);
  
  double maxCurrent = 2.5; //hardware maximum current is 2.5A

  LeftMotorA.setMaxTorque(maxCurrent, currentUnits::amp);
  LeftMotorB.setMaxTorque(maxCurrent, currentUnits::amp);
  RightMotorA.setMaxTorque(maxCurrent, currentUnits::amp);
  RightMotorB.setMaxTorque(maxCurrent, currentUnits::amp);


  catapultA.setStopping(brakeType::hold);
  catapultB.setStopping(brakeType::hold);

  intake.setStopping(brakeType::brake);
  intakeRoller.setStopping(brakeType::brake);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  // use this if we have calibration issues. make sure it prevents driver control for at least 2 seconds
  //imu.calibrate(2000);

  Controller1.ButtonLeft.pressed([](){
    wingL.setMaxTorque(1.25, currentUnits::amp);
    wingL.spin(directionType::fwd, -100, velocityUnits::pct);
  });

  Controller1.ButtonLeft.released([](){
    wingL.stop();
    wingL.setMaxTorque(0.2, currentUnits::amp);
  });

  Controller1.ButtonRight.pressed([](){
    wingL.setMaxTorque(1.25, currentUnits::amp);
    wingL.spin(directionType::fwd, 100, velocityUnits::pct);
  });

  Controller1.ButtonRight.released([](){
    wingL.stop();
    wingL.setMaxTorque(0.2, currentUnits::amp);
  });


  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //drive.tankDrive(Controller1.Axis3.position(), Controller1.Axis2.position());

    // 1 stick arcade
    //drive.arcadeDrive(Controller1.Axis3.position(), Controller1.Axis4.position());

    // 2 stick arcade
    drive.arcadeDrive(Controller1.Axis3.position(), Controller1.Axis1.position());

    //intake
    Controller1.ButtonL1.pressed([](){
      intakeSpin();
    });

    Controller1.ButtonL1.released([](){
      intakeStop();
    });

    Controller1.ButtonL2.pressed([](){
      intakeSpin(true);
    });

    Controller1.ButtonL2.released([](){
      intakeStop();
    });

    Controller1.ButtonA.pressed([](){
      wings.toggleWings();
    });

    Controller1.ButtonX.pressed([](){
      drive.toggleInvertedDrive();
    });

    // catapult
    Controller1.ButtonR1.pressed([](){
      catapultLaunch();
      // these three lines here are what does the automatic arming of the catapult.
      wait(50, msec);
      waitUntil(getCatAccel() <= 0.1); // <-- might be blocking, which isnt desirable
      catapultArm();
    });

    // // fliper
    // double flipperSpeed = 0;
    // if (Controller1.ButtonRight.pressing()) {
    //   wingL.setMaxTorque(1.25, currentUnits::amp);
    //   wingR.setMaxTorque(1.25, currentUnits::amp);
    //   flipperSpeed = -100;
    // } else if (Controller1.ButtonLeft.pressing()) {
    //   wingL.setMaxTorque(1.25, currentUnits::amp);
    //   wingR.setMaxTorque(1.25, currentUnits::amp);
    //   flipperSpeed = 100;
    // } else {
    //   wingL.setMaxTorque(0.15, currentUnits::amp);
    //   wingR.setMaxTorque(0.15, currentUnits::amp);
    //   flipperSpeed = 0;
    // }
    // wingL.spin(directionType::fwd, flipperSpeed, velocityUnits::pct);

    Controller1.ButtonR1.released([](){
      //catapultStop();
    });

    Controller1.ButtonR2.pressed([](){
      if (!catInPosArmed()) {
        catapultArm();
      }
    });

    Controller1.ButtonR2.released([](){
      //catapultStop();
    });
    
    Controller1.ButtonDown.pressed([](){
      catapultLower();
    });

    Controller1.ButtonDown.released([](){
      stopAutoArming();
      catapultStop();
    });

    Controller1.ButtonUp.pressed([](){
      catapultRaise();
    });

    Controller1.ButtonUp.released([](){
      stopAutoArming();
      catapultStop();
    });


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(head_to_head_auto);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function.
  pre_auton();
  Controller1.Screen.clearScreen();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    updateCatAccel(0.02);
    odomUpdate();

    // Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    // Controller1.Screen.print("yPosition: %f", gps1.yPosition());
    Controller1.Screen.print(imu.heading());
    Controller1.Screen.setCursor(1,10);
    Controller1.Screen.print(Brain.Battery.capacity()); //gpsAngleRad()
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print(getX());
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print(getY());
    Controller1.Screen.setCursor(2,12);
    //Controller1.Screen.print(drive.getAngleToPoint(0, 1000));
    Controller1.Screen.print(catapultRot.angle(rotationUnits::deg));
    Controller1.Screen.setCursor(3, 12);
    Controller1.Screen.print(drive.getInvertedDrive());

    wait(20, msec);
  }
}
