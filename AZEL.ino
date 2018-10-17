int MTR_PN = 13;
int DIR_PIN_ONE = 12;
int DIR_PIN_TWO = 11;
boolean DIR_EN_ONE = false;
boolean DIR_EN_TWO = false;
boolean MTR_EN = false;

void setup() {
  pinMode(MTR_PN, OUTPUT);
  pinMode(DIR_PIN_ONE, OUTPUT);
  pinMode(DIR_PIN_TWO, OUTPUT);
  digitalWrite(DIR_PIN_TWO, DIR_EN_TWO);
  digitalWrite(DIR_PIN_ONE, DIR_EN_ONE);
  digitalWrite(MTR_PN, MTR_EN);
}

void loop() {
  delay(3000);
  setMotor(false);
  setFwd(false);
  delay(3000);
  setMotor(true);
  setFwd(false);
  delay(3000);
  setMotor(true);
  setFwd(true);
}

void setMotor(bool EN){
  MTR_EN = EN;
  digitalWrite(MTR_PN, EN);
}

void setFwd(bool EN){
  DIR_EN_ONE = EN;
  DIR_EN_TWO = !EN;
  digitalWrite(DIR_PIN_ONE, DIR_EN_ONE);
  digitalWrite(DIR_PIN_TWO, DIR_EN_TWO);

}



