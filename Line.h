// Line Sensors Initializations
int Sensors[] = {A7, A6, A5, A4, A3, A2, A1, A0};
int lineAn[8];
//unsigned int Threshold[8]={470, 450, 450, 300, 350, 350, 520, 350};
unsigned int Threshold[8]={250,300,300,200,250,200,400,250};

unsigned char LineSetup()
{   
  unsigned char i, results = 0;
  for(i = 0; i < 8; i++)
  {
    if(lineAn[i] = analogRead(Sensors[i]) < Threshold[i]) results += (1 << i);
  }
  return results;
}
