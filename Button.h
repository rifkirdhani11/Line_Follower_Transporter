//Button Initialization
#define SELECT 22
#define DOWN 23
#define UP 24
#define BACK 25

// User Interface Initialization
int SelectState;
int DownState;
int UpState;
int BackState;

void ButtonSetup()
{  
  // Pin mode button setup
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
}

//User Interface is under maintenance
