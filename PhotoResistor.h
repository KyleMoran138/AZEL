#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H
#include "Arduino.h"
#include "Sensor.h"

class PhotoResistor : public Sensor{
  
  public:
    PhotoResistor(int pin_id, float pos);
    PhotoResistor(int pin_id, float pos, float weight);
    float readFloat();
};
#endif