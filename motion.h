#include "Line.h"

signed char mission=0;

void kanan(){
  unsigned char sensor=0, count=0;
  motorR.drive(-32);
  motorL.drive(32);
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
    
    
