//external i2c test Ben Cohen 11/12/22
//defining pins
byte en_ext_I2C = 11;
byte SDA_NON_CRIT = 3;
 byte SCL_NON_CRIT = 4;
//intizaling pins
void setup(){
pinMode(en_ext_I2C, OUTPUT);
pinMode(SDA_NON_CRIT, OUTPUT);
pinMode(SCL_NON_CRIT, OUTPUT);
}
//turns on and off every half second
void loop(){
  digitalWrite(en_ext_I2C, HIGH);
 digitalWrite(SDA_NON_CRIT, HIGH);
 digitalWrite(SCL_NON_CRIT, HIGH);
  delay(500);
 digitalWrite(en_ext_I2C, LOW);
 digitalWrite(SDA_NON_CRIT, LOW);
 digitalWrite(SCL_NON_CRIT, LOW);
  delay(500);
}
