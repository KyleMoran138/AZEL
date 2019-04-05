#include "Sensor.h";

Sensor::Sensor(){};

Sensor::Sensor(int pin_id, float pos){
  this->_pin_id = pin_id;
  this->pos = pos;
  this->_weight = 0.0;
  this->value = 0;
};

Sensor::Sensor(int pin_id, float pos, float weight){
  this->_pin_id = pin_id;
  this->pos = pos;
  this->_weight = weight;
  this->value = 0;
};

float Sensor::getValueChangePerDistanceUnit(Sensor* sensorTwo){
  float spaceBetweenSensors = abs(this->pos - sensorTwo->pos);
  int valueDiffBetweenSensors = abs(this->value - sensorTwo->value);
  return valueDiffBetweenSensors / ( spaceBetweenSensors * 100 );
}


float Sensor::readFloat(){
  delay(50);
  value = analogRead(_pin_id);
  delay(50);
  return value;
};
