#include "Arduino.h";
#include "Sensor.h";

class PhotoResistor : Sensor{
  
  public:
    PhotoResistor(int pin_id, float pos);
    PhotoResistor(int pin_id, float pos, float weight);
    float readFloat();
};
