/*****************************************
ECE 110 Final Project
Author: Ali Afridi 
Start Date: 11/13/2012
Last Edited: 12/10/2012
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Inputs
#define LS1 A4
#define LS2 A3
#define LS4 A2
#define LS5 A1

//Outputs
#define LM 9 //Left motor
#define RM 10 //Right motor
#define white_val 315 //Value at which white tape is detected
#define outer_white_val 250 //Value at which white tape is detected
#define turn_val 260 //Value at which white tape is detected
#define split_val 90 //Value at which grey tape is detected
#define motor_speed 95
#define speed0 0
#define speed80 80

void setup()
{
  Serial.begin(9600);
  int i; 
  for (i=2; i<7; i++) //pins 2 through 6 are now inputs
  {
    pinMode(i,INPUT); 
  }
  for (i=9; i<13; i++) //pins 7 through 9 are now outputs
  {
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  Serial.println(" ");
  if((analogRead(LS1) < white_val || analogRead(LS5)<white_val) && analogRead(LS2) > split_val && analogRead(LS4) > split_val ) //Split, Both center sensors see white
  {
    //Implement Split Circuit
    int color_val1 = analogRead(0);
    Serial.println("Split");

    if((color_val1 < 340)) //grey (turn right)
    {
      right();
    }

    else
    {
      left();
    }
  }

  else if(analogRead(LS1) < white_val && analogRead(LS2) < white_val && analogRead(LS4) < white_val && analogRead(LS5) < white_val) //All sensors see black
  {
    straight();
  }

  else if(analogRead(LS1) < white_val && analogRead(LS2) < white_val && analogRead(LS4) > white_val && analogRead(LS5) < white_val) //LS4 sees white, turn right
  {
    right();
  }

  else if(analogRead(LS1) < white_val && analogRead(LS2) < white_val && analogRead(LS4) > white_val && analogRead(LS5) > outer_white_val) //LS4 and LS5 see white, right angle turn right
  {
    sharper_right();
  }

  else if(analogRead(LS1) < white_val && analogRead(LS2) > white_val && analogRead(LS4) > white_val && analogRead(LS5) > outer_white_val) //LS4 and LS5 see white, right angle turn right
  {
    sharper_right(); 
  }
  
  else if(analogRead(LS1) < white_val && analogRead(LS2) > white_val && analogRead(LS4) < white_val && analogRead(LS5) < white_val) //LS2 sees white, Turn Left
  {
    left();
  }

  else if(analogRead(LS1) > outer_white_val && analogRead(LS2) > white_val && analogRead(LS4) < white_val && analogRead(LS5) < white_val) //LS1 and LS2 see white, Right angle turn left
  {
    sharper_left();
  }

  else if(analogRead(LS1) > outer_white_val && analogRead(LS2) > white_val && analogRead(LS4) > white_val && analogRead(LS5) < white_val) //LS1 and LS2 see white, Right angle turn left
  {
    sharper_left();
  }

  else if(analogRead(LS1) > white_val && analogRead(LS2) > white_val && analogRead(LS4) > white_val && analogRead(LS5) > white_val)//all sensors see white, stop 
  {
    halt();
  }

  else //something else happened, which shouldn't have happened
  {
    digitalWrite(13, HIGH);
    halt();
  }
}

//Functions

void straight()
{
  analogWrite(9, motor_speed);
  analogWrite(10, motor_speed);
}

void left()
{
  analogWrite(9, speed0);
  analogWrite(10, motor_speed);
}

void right()
{
  analogWrite(9, motor_speed);
  analogWrite(10, speed0);
}

void sharper_left()
{
  while (analogRead(LS4) < turn_val)
  {
  analogWrite(9, speed0);
  analogWrite(10, speed80);
  }
}

void sharper_right()
{
  while (analogRead(LS2) < turn_val)
  {
    analogWrite(9, speed80);
    analogWrite(10,speed0);
  }
}

void halt()
{
  analogWrite( 9, speed0 );
  analogWrite( 10, speed0 ); 
}
