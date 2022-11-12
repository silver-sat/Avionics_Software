byte en_ext_I2C = 11;
void setup(){
pinMode(en_ext_I2C, OUTPUT);
 
}

void loop(){
  digitalWrite(en_ext_I2C, HIGH);
  delay(500);
 digitalWrite(en_ext_I2C, LOW);
  delay(500);
}
