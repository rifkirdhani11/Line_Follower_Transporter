/*
Robotics Project
Mechatronics Engineering 2016
Team:
- Alvionita Rian Permata Putri 3110161001
- Hardefa Rizky Putu Rogonondo 3110161019
- Moch Rifki Ramadhani     3110161020
*/


// biru=760, merah=860;

//90 = 320
//180 = 510 

#include <SparkFun_TB6612.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Button.h"
//#include "Line.h"
#include "MotorDriver.h"
#include "Gripper.h"
#include "IR.h"
#include "myLCD.h"
#include "motion.h"

// Global variables for control
signed char error, delta_error, last_error;
int speed1, speed2, v, cl;
int PD, Kp = 27, Kd = 17.5;
//int PD, Kp = 15, Kd = 100;
signed char intersection, blank;

void setup()
{
  //jumper
  mission = 0;
  // put your setup code here, to run once:
  Serial.begin(9600);
  ButtonSetup();
  LineSetup();
  DriverSetup();
  GripperSetup();
  IRSetup();
  LCDSetup();
  Stop();
  //buka();
  GripAntiTurn();
  delay(500);
  GripRelease();
}

void loop()
{
  // Put your main code here, to run repeatedly:
  // Read the state of the pushbutton value
  SelectState = digitalRead(SELECT);
  DownState = digitalRead(DOWN);
  UpState = digitalRead(UP);
  BackState = digitalRead(BACK);
  IR_Read();
  IR_Print();
  //tutup();
  //Serial.println(IR2V);
  if(UpState != HIGH)
  {
    mission=28;
  }
//  if(DownState != HIGH)
//  {
//    GripTurn();
//  }
//  else
//  {
//    GripAntiTurn();
//  }
//  if(BackState != HIGH)
//  {
//    Bckwrd();
//  }
  while(SelectState != HIGH)
  {
    //delay(100);
    MainProg();
    lcd.print(mission);
    Serial.println(mission);
  }
  if(BackState != HIGH){
    LineRead(100);
//    delay(500);
//    Stop();
  }
  //Stop();
}

unsigned char LineRead(unsigned char speedMtr)
{
  unsigned char sensor;
  sensor = LineSetup();
  intersection = 0;
  switch (sensor)
  {
    case 0B10000000: error = -7; break;
    case 0B11000000: error = -6; break;
    case 0B01000000: error = -5; break;
    case 0B01100000: error = -4; break;
    case 0B00100000: error = -3; break;
    case 0B00110000: error = -2; break;
    case 0B00010000: error = -1; break;
    case 0B00011000: error = 0; break;
    case 0B00001000: error = 1; break;
    case 0B00001100: error = 2; break;
    case 0B00000100: error = 3; break;
    case 0B00000110: error = 4; break;
    case 0B00000010: error = 5; break;
    case 0B00000011: error = 6; break;
    case 0B00000001: error = 7; break;
    case 0B00111000: intersection = 1; break;
    case 0B01111000: intersection = 1; break;
    case 0B11111000: intersection = 1; break;
    case 0B00011100: intersection = 1; break;
    case 0B00011110: intersection = 1; break;
    case 0B00011111: intersection = 1; break;
    case 0B11100111: intersection = 1; break;
    //case 0B11000011: intersection = 1; break;
    //case 0B10000001: intersection = 1; break;
    case 0B00111100: intersection = 1; break;
    case 0B01111110: intersection = 1; break;
    //case 0B11111111: intersection = 1; break;
    case 0B00000000: intersection = 1; break;
    //default:
    //    if(last_error<0)  error = -8;
    //    else              error = 8; 
  }
  //PD Control
  delta_error = error - last_error;
  last_error = error;
  PD = error * Kp + Kd * delta_error;
  speed1 = speedMtr - PD;
  speed2 = speedMtr + PD;
  
  if(speed1 > 255)        speed1 = 255;
  else if (speed1 < -255) speed1 = -255;
  if(speed2 > 255)        speed2 = 255;
  else if (speed2 < -255) speed2 = -255;
  
  if (intersection != 0)
  {
    mission++;
  }
  else
  {
    motorR.drive(speed1);
    motorL.drive(speed2);
    delay (10);
  }
}

//void Kiri(){
//  motorR.drive(100);
//  motorL.drive(-80);
//  mission++;
//}
//
//void Kanan(){
//  motorR.drive(-80);
//  motorL.drive(100);
//  mission++;
//}

void kiri(){
  unsigned char sensor=0, count=0;
  motorR.drive(32);
  motorL.drive(-32);
  delay(200);
  while(1) { 
    sensor = LineSetup();
    if(sensor==0B00000001 or sensor==0B00000011 or 0B0000010){
      count++;
    }
    if(count>3) {
      break;
    }
  }
  mission++;
}

void WallBall(){
  IR_Read();
  if(IR3V>=1000 and IR1V>=1000){
    motorR.drive(150);
    motorL.drive(100);
  }
  else if(IR3V<1000 and IR1V>=1000){
    motorR.drive(70);
    motorL.drive(150);
  }

}

void acc(){
  for(int i=0;i<150;i++){
    motorR.drive(i+8);
    motorL.drive(i);
    delay(2);
  }
  mission++;
}

void fwdW(){
  motorR.drive(98);
  motorL.drive(90);
  if(IR1V<1000){
  mission++;
  }
}

void accB(){
  for(int i=0;i<150;i++){
    motorR.drive(-i-13);
    motorL.drive(-i);
    delay(2);
  }
  mission++;
}

void deacc(){
  for(int i=150;i>30;i--){
    motorR.drive(i+8);
    motorL.drive(i);
    delay(2);
  }
  mission++;
}

void Fwd()
{
  motorR.drive(158);
  motorL.drive(150);
  mission++;
}

void Bckwrd()
{
  motorR.drive(-163);
  motorL.drive(-150);
  mission++;
}

void TurnLeft()
{
  motorR.drive(200);
  motorL.drive(-50);
  mission++;
}

void TurnBack()
{
  motorR.drive(150);
  motorL.drive(-150);
  mission++;
}

void TurnLeftB()
{
  motorR.drive(80);
  motorL.drive(-200);
  mission++;
}

void TurnRight()
{
  motorR.drive(-50);
  motorL.drive(200);
  mission++;
}

void Stop()
{
  motorR.drive(0);
  motorL.drive(0);
}

void MainProg()
{
  IR_Read();
  switch (mission) //red
  {   case 0:
        kiri();
        break;
      case 1:
        Stop();
        break;
//    //=======jalur Hitam==========
//    case 0:   // Forward from start box
//      acc();
//      delay(250);
//      break;
//    case 1:   // Line following until intersection
//      LineRead(100);
//      break;
//    case 2:   // Forward to activate gripper and backward
//      deacc();
//      delay(160);
//      break;
//    case 3:
//      IR_Read();
//      delay(150);
//      Stop();
//      GripTake(); //Take the object ke-1
//      if (color>=800 and color<=900){ // apkahmerah
//        GripAntiTurn(); //jarno
//        cl =0;
//      }
//      else{
//        GripTurn(); //waliken
//        cl = 1; //biru kui cl 1
//      }
//      mission++;
//      delay(100);
//      break;
//    case 4:
//      accB();
//      delay(20);
//      break;
//    case 5:   // Turn left
//      TurnLeft();
//      delay(260);
//      break;
//    case 6:   // Line following until intersection
//      LineRead(60);
//      break;
//    case 7:
//      Fwd();
//      delay(60);
//      //mission++;
//      break;
//    case 8:
//      Kanan();
//      delay(400);
//      break;
//    case 9:   
//      Stop();
//      GripRelease(); //put the object ke-1
//      mission++;
//      delay(150);
//      break;
//    case 10:
//      //GripRelease();
//      Bckwrd();
//      delay(150);
//      Stop();
//      break;
//    case 11:
//      IR_Read();
//      if(cl==1){ // apakah biru tadi?
//        Stop();
//        GripTurn();
//        delay(500);
//      }
//      mission++;
//      break;
//    case 12: // diganti
//      cl=0;
//      GripRelease();
//      TurnLeftB();
//      delay(220);
//      break;
//    case 13:
//      deacc();
//      delay(200);
//      break;
//    case 14:
//      IR_Read();
//      Stop();
//      delay(200);
//      GripTake(); // take the object ke-2
//      if (color>800 and color<900){ // apkahmerah
//        GripAntiTurn(); //jarno
//        cl = 0; //abang kui cl 0
//      }
//      else{
//        GripTurn(); //waliken
//        cl = 1;
//      }
//      mission++;
//      delay(100);
//      break;
//    case 15:
//      accB();
//      delay(1);
//      break;
//    case 16:
//      Kiri();
//      delay(430);
//      break;
//    case 17:
//      LineRead(60);
//      break;
//    case 18:
//      TurnLeft();
//      delay(250);
//      break;
//    case 19:
//      Stop();
//      delay(200);
//      GripRelease(); //put the object -2
//      mission++;
//      delay(100);
//      break;
//    case 20:
//      motorR.drive(-150);
//      motorL.drive(-150);
//      delay(450);
//      mission++;
//      break;
//    case 21:
//      IR_Read();
//      Stop();
//      if(cl==1){ // apakah biru tadi?
//        GripAntiTurn();
//      }
//      delay(500);
//      TurnRight();
//      delay(350);
//      //Stop();
//      GripRelease();
//      break;
//    case 22:
//      cl=0;
//      LineRead(80);
//      break;  
////=========jalur Merah========
//    case 23:
//      TurnRight();
//      delay(300);
//      break;
//    case 24:
//      tutup();
//      //Stop();
//      delay(200);
//      LineRead(100);
//      break;
//    case 25:
//      tutup();
//      TurnRight();
//      delay(340);
//      break;
////====Wall Enter==================
//    case 26:
//      IR_Read();
//      motorR.drive(153);
//      motorL.drive(156);
//      delay(300);
//      mission++;
//      break;
//    case 27:
//      TurnRight();
//      delay(340);
//      break;
//    case 28:
//      WallBall();
//      if(IR1V<1000){
//        mission++;
//      }
//      break;
//    case 29:
//      TurnRight();
//      delay(340);
//      break;
//    case 30:
//      TurnLeft();
//      delay(340);
//      break;
//    case 31:
//      Fwd();
//      delay(320);
//      break;
//    case 32:
//      TurnLeft();
//      delay(310);
//      break;  
//    case 33:
//      acc();
//      delay(400);
//      break;
//    case 34:
//      TurnLeft();
//      delay(310);
//      break;  
//    case 35:
//      WallBall();
//      if(analogRead(A2)<200){
//        mission++;
//      }
//      break; 
////=====Wall Out===========
////=====jalur Biru=========
//    case 36:
//      TurnLeft();
//      delay(160);
//      break; 
//    case 37:
//      Stop();
//      delay(300);
//      mission++;
//    case 38:
//      GripRelease();
//      acc();
//      delay(10);
//      break;
//    case 39:
//      LineRead(75);
//      break;
//    case 40:
//      Fwd();
//      delay(130);
//      break;
//    case 41:
//      deacc();
//      delay(150);
//      break;
//    case 42:
//      IR_Read();
//      Stop();
//      delay(200);
//      GripTake(); // take the object
//      if (color>800 and color<900){ // apkahmerah
//        GripAntiTurn(); //jarno
//        cl = 0; //abang kui cl 1
//      }
//      else{
//        GripTurn(); //waliken
//        cl = 1;
//      }
//      delay(200);
//      mission++;
//      break;
//    case 43:
//      accB();
//      delay(200);
//    case 44:
//      Stop();
//      delay(200);
//      TurnRight();
//      delay(290);
//      break; 
//    case 45:
//      LineRead(75);
//      break;
//    case 46:
//      motorR.drive(98);
//      motorL.drive(90);
//      if(analogRead(A2)<200){
//        mission++;
//      }
//      break;
////===========jalur merah===============
//    case 47:
//      LineRead(125);
//      break;
//    case 48:
//      TurnRight();
//      delay(100);
//      break;
////=======Jalur Hitam Rebutan===========
//    case 49:
//      LineRead(200); 
//      break;
//    case 50:
//      Fwd();
//      delay(350);
//      break;
//    case 51:
//      LineRead(60); // biru
//      break;
//    case 52:
//      motorR.drive(153);
//      motorL.drive(150);
//      delay(920); //nilai nembak ke merah 300 //nilai nembak ke finish 920
//      mission++;
//      break;
//    case 53:
//      LineRead(55); // merah
//      break;
//    case 54:
//      accB();
//      delay(75);
//      break;
//    case 55:
//      Stop();
//      delay(200);
//      GripRelease();
//      break; 
  }
  delay (1);
}
