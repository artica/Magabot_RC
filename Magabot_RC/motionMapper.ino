
int throttle_min = 20;
int direction_min = 20;
float throttleMapped;
float directionMapped;

void motionControl()
{
  // left joystick dead zone
  if ((throttle > -throttle_min && throttle < throttle_min) && (direction > -direction_min && direction < direction_min))
  {
    //Serial.println("stop");
    motionUpdate(0, 0);
  }
  else if (throttle == -255)
  { 
      motionUpdate(0, 0);
  }
  else
  {
      //motoruino.setSpeedPWM(leftMotorScaled, rightMotorScaled); 
      motionUpdate(leftMotorScaled, rightMotorScaled);
  }
}


void motionMapper(){
  
  //aquire the analog input for Y  and rescale the 0..1023 range to -255..255 range
  analogTmp = left_vertical;
  throttle = (512-analogTmp)/2;

  delayMicroseconds(100);
  //...and  the same for X axis 
  // ATTENTION 
  // direction is being divided by 3, give us around 170
  
  analogTmp = left_horizontal;
  direction = (512-analogTmp)/2;//(speed_knob/2);
  direction = -direction;
  
  // this map is used to map the throttle to the knob
  throttleMapped = (int)map(throttle, 0, 255, 0, speed_knob);  
  directionMapped = (int)map(direction, 0, 255, 0, speed_knob);
  
  //mix throttle and direction
  leftMotor = throttleMapped+directionMapped;
  rightMotor = throttleMapped-directionMapped;
  
  

  //print the initial mix results
//  Serial.print(" , LIN:");
//  Serial.print( leftMotor, DEC);
//  Serial.print(", RIN:");
//  Serial.println( rightMotor, DEC);

  //calculate the scale of the results in comparision base 8 bit PWM resolution
  /**/
  leftMotorScale =  abs(leftMotor/255.0);
  rightMotorScale =  abs(rightMotor/255.0);
  /*
  //calculate the scale of the results in comparision base to speed_knob
  leftMotorScale =  abs(leftMotor/speed_knob);  
  rightMotorScale =  abs(rightMotor/speed_knob);
  */
  //Serial.print("| LSCALE:"); Serial.print( leftMotorScale,2);
  //Serial.print(", RSCALE:"); Serial.print( rightMotorScale,2);

  //choose the max scale value if it is above 1
  maxMotorScale = max(leftMotorScale,rightMotorScale);
  maxMotorScale = max(1,maxMotorScale);

  //and apply it to the mixed values
  leftMotorScaled = constrain(leftMotor/maxMotorScale,-speed_knob,speed_knob);
  rightMotorScaled = constrain(rightMotor/maxMotorScale,-speed_knob,speed_knob);
  
  

  //Serial.print("| LOUT:"); Serial.print( leftMotorScaled);
  //Serial.print(", ROUT:"); Serial.print( rightMotorScaled);

  //Serial.print(" |");
  
  

}
