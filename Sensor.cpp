#include "Sensor.h"

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
  float valueDiffBetweenSensors = abs(this->value - sensorTwo->value);
  float modifyer = 1;

  if(spaceBetweenSensors > 1){
    modifyer = (spaceBetweenSensors / 1) ;
  }else if(spaceBetweenSensors < 1){
    modifyer = (1 / spaceBetweenSensors) - 1;
  }
  float valuesPerDegree = valueDiffBetweenSensors * modifyer;
  return 0;
}

float Sensor::readFloat(){
  delay(50);
  value = analogRead(_pin_id);
  delay(50);
  return value;
};

bool Sensor::SensorDifferenceSumZero(){
  bool testVal = this->d_u_gt && this->d_u_lt && this->d_d_gt && this->d_d_lt && false;
  return testVal;
}
