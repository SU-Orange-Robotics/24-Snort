#include "vex.h"
#include "robot-config.h"
#include "wings.h"

using namespace vex;

Wings::Wings() {
  wingState = false;
}

void Wings::initWings() {
  wingL.resetPosition();
  wingR.resetPosition();

  wingL.setStopping(brakeType::hold);
  wingR.setStopping(brakeType::hold);
}

// RETRACTED(default): NON PUSHING
// TRYING TO EXPAND: PUSHING
// EXPANDED or RETRACTING: PUSHING
void Wings::toggleWings() {
  if (wingState == false) {
    // set to pushing
    pushing = true;
    expandWings();
  } else {
    retractWings();
  }

  wingState = !wingState;
}

void Wings::expandWings() {
  wingL.spinToPosition(180, deg, false);
  wait(200, timeUnits::msec);
  wingR.spinToPosition(182, deg, false);
}

void Wings::retractWings() {
  wingR.spinToPosition(0, deg, false);
  wait(200, timeUnits::msec);
  wingL.spinToPosition(0, deg, false);
}

bool Wings::pushingState() {
  return pushing;
}

bool Wings::isRetracted() {
  // check motor position
  return (abs(wingL.position(deg)) < 1) && (abs(wingR.position(deg)) < 1);
  pushing = false;
}