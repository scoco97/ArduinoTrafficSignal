int sig[4][3] = {13,12,11,10,9,8,7,6,5,4,3,2};
int buz = 1;


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
 int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<3;j++)
      pinMode(sig[i][j], OUTPUT);
  pinMode(buz,OUTPUT);
}

//defines signal statuses when 'k' th  road is green
void stateGo(int k)
{
   //buzzer is off
   analogWrite(buz,0); 

   int i,j;
    for(i=0;i<4;i++)
      for(j=0;j<3;j++)
        digitalWrite(sig[i][j],LOW);
        
    //all roads except the 'k'th road is red.
    for(i=0;i<4;i++)
      if(i!=k)
        digitalWrite(sig[i][0],HIGH);
    
    //kth road is green.
    digitalWrite(sig[k][2],HIGH);
    
    //wait 10 seconds
    delay(15000);
    
    //blink green as a "hurry up" warning for next 6 seconds
    for(i=0;i<6;i++)
    {
      digitalWrite(sig[k][2],LOW);
      delay(500);
      digitalWrite(sig[k][2],HIGH);
      delay(500);
    }
}


void statePause(int k)
{
  int i,j;
  int p = k-1;
  if(p==-1)
    p=3;
    
  //turn off all lights for a fraction of a second.
  for(i=0;i<4;i++)
      for(j=0;j<3;j++)
        digitalWrite(sig[i][j],LOW);
        
  //all red lights except p (i.e k-1) are red.
  for(i=0;i<4;i++)
    if(i!=p)
          digitalWrite(sig[i][0], HIGH);
  
  //also  p and k roads have yellow
  digitalWrite(sig[p][1],HIGH);
  digitalWrite(sig[k][1],HIGH);
  
  //for 5 seconds switch off and switch on buzzer.
  for(i=0;i<10;i++)
  {
    analogWrite(buz,255);
    delay(250);
    analogWrite(buz,0);
    delay(250);
  }
}


// the loop routine runs over and over again forever:
void loop() {
   stateGo(0);
  statePause(1);
  stateGo(1);
  statePause(2);
  stateGo(2);
  statePause(3);
  stateGo(3);
  statePause(0);
}