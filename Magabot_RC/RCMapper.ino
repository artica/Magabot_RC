

void rc_mapper()
{
  // read RAW data
  ch1_val = pulseIn(ch1_pin, HIGH, 25000); // left_horizontal
  delay(10);
  ch2_val = pulseIn(ch2_pin, HIGH, 25000); // left_vertical
  delay(10);
  ch5_val = pulseIn(ch5_pin, HIGH, 25000);
  delay(10);
  
  left_horizontal = constrain(map(ch2_val, MA_MIN, MA_MAX, 0, 1023), 0, 1023);
  left_vertical = constrain(map(ch1_val, MB_MIN, MB_MAX, 1023, 0), 0, 1023);
  
  //speed_knob = constrain(map(ch5_val, 986, 1975, 0, 255), 0, 40);
  speed_knob = map(ch5_val, 986, 1975, 0, 40);
  
 
}
