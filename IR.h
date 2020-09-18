//IR Sensors Initializations
#define IR1 A10 //depan
#define IR2 A8 //warna dan jarak
#define IR3 A9 // samping

//IR Sensors Value Initialization
int IR1V = 0;
int color = 0;
int IR3V = 0;

// biru=800, merah=900;

void IRSetup()
{
  // Pin mode IR sensors setup
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

void IR_Read()
{
  IR1V = analogRead(IR1);
  color = analogRead(IR2);
  IR3V = analogRead(IR3);
}

void IR_Print()
{
  Serial.print(IR1V);
  Serial.print("\t");
  Serial.print(color);
  Serial.print("\t");
  Serial.println(IR3V);
}

// Ultrasonic is under maintenance
