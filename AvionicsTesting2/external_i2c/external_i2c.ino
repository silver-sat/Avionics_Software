byte en_ext_I2C = 11;
void setup(){
pinMode(en_ext_I2C, Output);
 
}

void loop(){
  digitalWrite(en_ext_I2C, high);
  delay(500);
 digitalWrite(en_ext_I2c, low);
  delay(500);
}
