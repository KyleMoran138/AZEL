#ifndef STEPPER_H
#define STEPPER_H
#include "Arduino.h"

class Stepper{
  
  public:
    Stepper();
    void DoStep(bool CW, int count);
    
  private:
    int _delayTime = 3;
    int _a = 11;
    int _b = 10;
    int _aa = 9;
    int _bb = 8;
    void _stepCCW();
    void _stepCW();
};
#endif
