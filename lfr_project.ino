#include<AFMotor.h>
#include<NewPing.h>

#define ultrasonicTrigger A3
#define ultrasonicEcho A4

AF_DCMotor motor_fl(3);   //front left
AF_DCMotor motor_fr(4);   //front right
AF_DCMotor motor_br(1);   //back right
AF_DCMotor motor_bl(2);   //back left

int r_ir = A0;
int c_ir = A1;
int l_ir = A2;
int black = 0;
int white = 0;

const int maxDistance = 400;
NewPing ultrasonic(ultrasonicTrigger, ultrasonicEcho, maxDistance);

const int MIN_DISTANCE_FROM_OBJECT = 12;
// Error of the distance read by the ultrasonic sensor
const float DISTANCE_OFFSET = -0.31;

int maxv = 450;
int maxspeed = 255;
long duration;
int distance;

void setup() {
  
  // put your setup code here, to run once:
  motor_fl.setSpeed(255);
  motor_fr.setSpeed(255);
  motor_br.setSpeed(255);
  motor_bl.setSpeed(255);
  
  pinMode(r_ir,INPUT);
  pinMode(c_ir,INPUT);
  pinMode(l_ir,INPUT);
  Serial.begin(9600);

  pinMode(ultrasonicTrigger, OUTPUT); 
  pinMode(ultrasonicEcho, INPUT);
}


void loop() {

  if (hasObstacle()){
    black = 0;
    white = 0;
    motor_br.setSpeed(maxspeed);
    motor_fr.setSpeed(maxspeed);
    motor_bl.setSpeed(0);
    motor_fl.setSpeed(0);
    
    //motor_fl.run(RELEASE);
    motor_fr.run(FORWARD);
    //motor_bl.run(RELEASE);
    motor_br.run(FORWARD);
  }
  while (hasObstacle()) delay(100);
  
  if ((digitalRead(l_ir) == 0 ) && (digitalRead(c_ir) == 1) && (digitalRead(r_ir) == 0)){
    //forward();
    //delay(100); 
    black = 0;
    white = 0;
    motor_fl.setSpeed(maxspeed);
    motor_fr.setSpeed(maxspeed);
    motor_br.setSpeed(maxspeed);
    motor_bl.setSpeed(maxspeed);
    
    motor_fl.run(FORWARD);
    motor_fr.run(FORWARD);
    motor_bl.run(FORWARD);
    motor_br.run(FORWARD); 
  }
    
  if((digitalRead(l_ir) == 1) && (digitalRead(c_ir) == 1) && (digitalRead(r_ir)  == 0)){
    //left();
    black = 0;
    white = 0;
    motor_br.setSpeed(maxspeed);
    motor_fr.setSpeed(maxspeed);
    motor_bl.setSpeed(0);
    motor_fl.setSpeed(0);
    
    //motor_fl.run(RELEASE);
    motor_fr.run(FORWARD);
    //motor_bl.run(RELEASE);
    motor_br.run(FORWARD);
    
    }
    
  if((digitalRead(l_ir) == 1) && (digitalRead(c_ir) == 0) && (digitalRead(r_ir) == 0)){
    //left();   
    black = 0;
    white = 0;
    motor_br.setSpeed(maxspeed);
    motor_fr.setSpeed(maxspeed);
    motor_bl.setSpeed(0);
    motor_fl.setSpeed(0);
    
    //motor_fl.run(RELEASE);
    motor_fr.run(FORWARD);
    //motor_bl.run(RELEASE);
    motor_br.run(FORWARD);
    }
    
  if((digitalRead(l_ir) == 0) && (digitalRead(c_ir) == 1) && (digitalRead(r_ir) == 1)){
    //rigth();
    black = 0;
    white = 0;
    motor_bl.setSpeed(maxspeed);
    motor_fl.setSpeed(maxspeed);
    motor_br.setSpeed(0);
    motor_fr.setSpeed(0);
    motor_fl.run(FORWARD);
    //motor_fr.run(RELEASE);
    motor_bl.run(FORWARD);
    //motor_br.run(RELEASE);
    }
    
  if((digitalRead(l_ir) == 0) && (digitalRead(c_ir) == 0) && (digitalRead(r_ir) == 1)){
    //rigth();
    black = 0;
    white = 0;
    motor_bl.setSpeed(maxspeed);
    motor_fl.setSpeed(maxspeed);
    motor_br.setSpeed(0);
    motor_fr.setSpeed(0);
    motor_fl.run(FORWARD);
    //motor_fr.run(RELEASE);
    motor_bl.run(FORWARD);
    //motor_br.run(RELEASE);
    }
    
  if((digitalRead(l_ir) == 1) && (digitalRead(c_ir) == 1) && (digitalRead(r_ir) == 1)){
    //Stop();
    black++;
    white = 0;
    if(black>1)
    {
      motor_fl.run(RELEASE);
      motor_fr.run(RELEASE);
      motor_bl.run(RELEASE);
      motor_br.run(RELEASE);
    }
    else
    {
      motor_fl.setSpeed(maxspeed);
      motor_fr.setSpeed(maxspeed);
      motor_br.setSpeed(maxspeed);
      motor_bl.setSpeed(maxspeed);
      
      motor_fl.run(FORWARD);
      motor_fr.run(FORWARD);
      motor_bl.run(FORWARD);
      motor_br.run(FORWARD); 
    }
  }   
}

boolean hasObstacle() {
  int distance = ultrasonic.ping_cm(); 
  return distance > 0 && distance <= MIN_DISTANCE_FROM_OBJECT;
}
