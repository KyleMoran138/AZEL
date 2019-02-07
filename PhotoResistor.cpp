#include "PhotoResistor.h";

PhotoResistor::PhotoResistor(int pin_id, float pos){
  this->_pin_id = pin_id;
  this->_pos = pos;
  this->_weight = 0.0;
  this->value = 0;
};

PhotoResistor::PhotoResistor(int pin_id, float pos, float weight){
  this->_pin_id = pin_id;
  this->_pos = pos;
  this->_weight = weight;
  this->value = 0;
};

float PhotoResistor::readFloat(){
  value = analogRead(_pin_id);
  return value;
};
