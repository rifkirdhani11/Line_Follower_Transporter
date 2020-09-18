//Driver Initialization
#define PWMA 3
#define PWMB 2
#define AIN1 29
#define AIN2 27
#define BIN1 33
#define BIN2 35

Motor motorR (AIN1, AIN2, PWMA, 1, 0);
Motor motorL (BIN1, BIN2, PWMB, 1, 0);

void DriverSetup()
{
  // Pin mode driver setup
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}
