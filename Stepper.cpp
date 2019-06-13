#include "Stepper.h"

Stepper::Stepper(){
}

void Stepper::DoStep(bool CW, int count){
  for(int i =0; i < count/4; i++){
    if(CW){
      this->_stepCW();
    }else{
      this->_stepCCW();
    }
  }
}

void Stepper::_stepCCW(){
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, HIGH);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, HIGH);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, HIGH);
  delay(this->_delayTime);
  digitalWrite(this->_a, HIGH);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
}

void Stepper::_stepCW(){
  digitalWrite(this->_a, HIGH);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, HIGH);
  delay(this->_delayTime);
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, HIGH);
  digitalWrite(this->_aa, LOW);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
  digitalWrite(this->_a, LOW);
  digitalWrite(this->_b, LOW);
  digitalWrite(this->_aa, HIGH);
  digitalWrite(this->_bb, LOW);
  delay(this->_delayTime);
}