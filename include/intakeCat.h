#include "vex.h"

#pragma once

const double intakePow = 100;
const double catPow = 100;

void stopAutoArming();

void intakeSpin(bool reversed = false);

void intakeStop();

void catapultLower();

void catapultRaise();

void catapultArm();

void catapultLaunch();

void catapultStop();

bool catInPosArmed();

void updateCatAccel(double time);

double getCatAccel();