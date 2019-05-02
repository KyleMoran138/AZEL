#include "Sensor.h"

Sensor::Sensor(){};

Sensor::Sensor(int pin_id, float pos){
  this->_pin_id = pin_id;
  this->pos = pos;
  Serial.print("New sensor with location: ");
  Serial.println(this->pos);
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
  Serial.print("base sensor loc: ");
  Serial.println(this->pos);
  Serial.print("second sensor loc: ");
  Serial.println(sensorTwo->pos);
  Serial.print("Distance between sensors: ");
  Serial.println(spaceBetweenSensors);
  int valueDiffBetweenSensors = abs(this->value - sensorTwo->value);
  Serial.print("Value difference between sensors");
  Serial.println(valueDiffBetweenSensors);
  return valueDiffBetweenSensors / ( spaceBetweenSensors * 100 );
}

float Sensor::readFloat(){
  delay(50);
  value = analogRead(_pin_id);
  delay(50);
  return value;
};

bool Sensor::SensorDifferenceSumZero(){
  bool testVal = this->d_u_gt && this->d_u_lt && this->d_d_gt && this->d_d_lt && false;
  // Serial.print("Test value is ");
  // Serial.println(testVal);
  return testVal;
}
