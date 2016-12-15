// * How to read remote control data:
// * https://www.sparkfun.com/tutorials/348


int ch1_pin = 4; // right_horizontal
int ch2_pin = 5; // right_vertical
int ch3_pin = 3; // speed knob
/*
int ch2_pin = 4; // left_vertical
int ch4_pin = 3; // left_horizontal

int ch5_pin = 7; // c_stick
int ch6_pin = 8; // right_knob
*/
int ch1_val; 
int ch2_val;
int ch3_val;
/*
int ch3_val; 
int ch4_val;
int ch5_val;
int ch6_val;
*/
void setup() {
  Serial.begin(9600); 
  
  // RC pins
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(ch3_pin, INPUT);

}

void loop() {

  ch1_val = pulseIn(ch1_pin, HIGH, 25000); // Read the pulse width of 
  delay(10);
  ch2_val = pulseIn(ch2_pin, HIGH, 25000); // each channel
  delay(10);
  ch3_val = pulseIn(ch3_pin, HIGH, 25000); // each channel
  delay(10);
  /*
  ch3_val = pulseIn(ch3_pin, HIGH, 25000); // Read the pulse width of 
  ch4_val = pulseIn(ch4_pin, HIGH, 25000);
  ch5_val = pulseIn(ch5_pin, HIGH, 25000); // Read the pulse width of 
  ch6_val = pulseIn(ch6_pin, HIGH, 25000);
  */
  
  Serial.print("ch1: ");
  Serial.print(ch1_val);
  Serial.print("  ch2: ");
  Serial.print(ch2_val);
  Serial.print("  ch3: ");
  Serial.print(ch3_val);
  /*
  Serial.print("  ch3: ");
  Serial.print(ch3_val);
  Serial.print("  ch4: ");
  Serial.print(ch4_val);
  Serial.print("  ch5: ");
  Serial.print(ch5_val);
  Serial.print("  ch6: ");
  Serial.print(ch6_val);/**/
  Serial.println("");
}
