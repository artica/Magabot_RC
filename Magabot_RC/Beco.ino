int veloc1=0,veloc2=0;
int velocity = 15;
int turnVel = 8;

int becoBackwardsTime = 1500;

boolean forward = true;
boolean stopped = true;
boolean turning = false;
boolean right = false;

int reverseState =0;
unsigned long becoTime;
unsigned long bTime;
unsigned long iTime;

boolean beco()
{
  robot.readBumpers();
  
  veloc1 = velocity;
  veloc2 = velocity;

  if(robot.bumperRead[1])
  {
    reverseState = 1;
    motionUpdate(-5, -veloc2);
    becoTime = millis()+becoBackwardsTime;  
    return false;
  }
  else if(robot.bumperRead[0])
  {
    reverseState = 1;
    motionUpdate(-veloc1, -5); 
    becoTime = millis()+becoBackwardsTime;  
    return false;
  }
  
  if (reverseState ==1 && millis()>becoTime)
  {
    reverseState = 0;
    return true;
  }
  /*
  int bestDirection = 0;
  int bestDirectionValue = 0;

  for (int count = 1;count<6;count++)
  {
    if(robot.sonarRead[count].read() > bestDirectionValue)
    {
      bestDirectionValue = robot.sonarRead[count].read();
      bestDirection = count;
    }
  }
  String dir;
  if (reverseState == 0)
  {    
    if(robot.sonarRead[3].read() > frontDistance)
    {
      robot.actuateMotors(veloc1,veloc2);
      robot.actuateLEDs(0,255,0);
      if(robot.sonarRead[1].read() < sideDistance || robot.sonarRead[2].read() < sideDistance)
      {
        robot.actuateMotors(veloc1,0);  
        robot.actuateLEDs(255,255,0);
      }
      else if(robot.sonarRead[4].read() < sideDistance || robot.sonarRead[5].read() < sideDistance)
      {
        robot.actuateMotors(0,veloc2);  
        robot.actuateLEDs(255,255,0);
      } 
    }
    else
    {
      robot.actuateMotors(veloc1,0);
      robot.actuateLEDs(255,255,0);
    }
  }
  else
  {
    robot.actuateLEDs(255,0,0);
  }
  */
}
