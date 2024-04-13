
#include "vex.h"

#pragma once

class Wings {
private:
    bool wingState; // true for expanded, false for retracted
    bool pushing; // true for pushing, false for non-pushing
public:
    Wings();
    void initWings();
    void toggleWings();
    void expandWings();
    void retractWings();
    bool pushingState();
    bool isRetracted();
};