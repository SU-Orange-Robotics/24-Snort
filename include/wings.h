
#include "vex.h"

#pragma once

class Wings {
private:
    bool wingState; // for toggling expansion or retraction motion ()
    bool pushing; // true for pushing, false for retracted
public:
    Wings();
    void initWings();
    void toggleWings();
    void expandWings();
    void retractWings();
    bool pushingState();
};