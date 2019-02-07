#include "Arduino.h";
class PhotoResistor{
  public:
    PhotoResistor(int pin_id, float pos);
    PhotoResistor(int pin_id, float pos, float weight);
    float readFloat();
  private:
  int   _pin_id;
  float _pos;
  float _weight;
  float value;
};
