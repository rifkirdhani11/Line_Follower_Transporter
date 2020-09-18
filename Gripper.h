//Gripper Initialization
Servo Servo1, Servo2, Servo3;

void GripperSetup()
{
  // Pin mode gripper setup
  Servo1.attach(4); Servo1.write(70);
  Servo2.attach(5); Servo2.write(160);
  Servo3.attach(6); Servo3.write(50);
}

void buka(){
  Servo3.write(0);
  delay(5);
}

void tutup(){
  Servo3.write(57);
  delay(5);
}

void GripTake()
{
  Servo3.write(62);
  delay(150);
  Servo1.write(45);
  delay(10);
}

void angkat(){
  Servo1.write(45);
  delay(5);
}

void turun(){
  Servo1.write(70);
  delay(5);
}

void GripRelease()
{
  Servo1.write(70);
  delay(200);
  Servo3.write(0);
  delay(10);
}

void GripTurn()
{
  //Servo3.write(57); //tutup
  Servo1.write(45); //angkat
  delay(300);
  Servo2.write(50); //puter
}

void GripAntiTurn()
{
  //Servo3.write(57); //tutup
  Servo1.write(45); //angkat
  delay(300);
  Servo2.write(160); //meneng
}
