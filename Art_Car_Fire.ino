/*
Art Car Flame Effect
Version 1
2014
*/

//The following go to the pins that control firing the effect
const byte LeftFireSw=2;        //Green button switch for left fire
const byte RightFireSw=3;        //Green button switch for right fire
const byte ActivateSw=4;        //Red button switch to start sequence 

//Next are pins that power the LEDs on the control switches
const byte LeftLED=5;          //LED for fire button (Green)
const byte RightLED=6;        //LED for fire button (Green)
const byte ActivateLED=7;      //LED for Activate button (Red)

/*Now we have the pins that trigger the MOSFETs that open
the solenoids and shoot fire.
*/
const byte LeftSol=8;    //Left solenoid
const byte RightSol=9    //Right solenoid

/*
Next are the input pins for the ternery number switches. These will control
what sequence the Arduino will play when the activate button is pressed.
*/
const byte 18Sw=10;    //12's
const byte 09Sw=11;
const byte 06Sw=12;
const byte 03Sw=13;
const byte 02Sw=A0;
const byte 01Sw=A1;
const unsigned long dumbAssTimeOut=300000;
void setup()
{
  pinMode(LeftFireSw,INPUT);
  pinMode(RightFireSw,INPUT);
  pinMode(ActivateSw,INPUT);
  
  pinMode(LeftLED,OUTPUT);
  pinMode(RightLED,OUTPUT);
  pinMode(ActivateLED,OUTPUT);
  
  pinMode(LeftSol,OUTPUT);
  pinMode(RightSol,OUTPUT);
  
  pinMode(18Sw,INPUT);
  pinMode(09Sw,INPUT);
  pinMode(06Sw,INPUT);
  pinMode(03Sw,INPUT);
  pinMode(02Sw,INPUT);
  pinMode(01Sw,INPUT);
  
}

void loop()
{
  turnOnLEDs()    //Turns on all LED control lights, indicating it's ready
  
  byte selectedSequence=determineSequence;
  
  
  digitalRead(LeftFireSw);  //These 3 lines check the switches so the
  digitalRead(RightFireSw); //program can figure out what to do next.
  digitalRead(ActivateSw);
  
  if (ActivateSw==HIGH) activateIsPressed();
}



/*
What follows is a function to determine what to do when someone
presses the activate button. Tt determines whether the operator
is trying to send the program into idle mode, or if he is
calling for a fire sequence.
*/
void activateIsPressed()
{

void dumbAss()
{
  digitalWrite(LeftSol,LOW);
  digitalWrite(RightSol,LOW);
  turnOffLEDs;
  delay(dumbAssTimeOut);
}


/*
Teh following function turns on all teh LEDs.
*/
void turnOnLEDs()
{
  digitalWrite(LeftLED,HIGH);
  digitalWrite(RightLED,HIGH);
  digitalWrite(ActivateLED,HIGH);
}



void turnOffLEDs() //Shuts off all LEDs
{
  digitalWrite(LeftLED,LOW);
  digitalWrite(RightLED,LOW);
  digitalWrite(ActivateLED,LOW);
}

byte determineSequence();  //syntax if fuxx0red! get a review! Can I use array??
{
  byte 01SwStatus = digitalRead(01Sw);
  byte 02SwStatus = digitalRead(02Sw);
  byte 03SwStatus = digitalRead(03Sw);
  byte 06SwStatus = digitalRead(06Sw);
  byte 09SwStatus = digitalRead(09Sw);
  byte 18SwStatus = digitalRead(18Sw);
  
  
  if (01SwStatus == 0 &&
      02SwStatus == 0 &&
      03SwStatus == 0 &&
      06SwStatus == 0 &&
      09SwStatus == 0 &&
      18SwStatus == 0)
        {return 0};      //sequence 0 is active

  if (01SwStatus == 1 &&
      02SwStatus == 0 &&
      03SwStatus == 0 &&
      06SwStatus == 0 &&
      09SwStatus == 0 &&
      18SwStatus == 0)
        {return 1};      //sequence 1 is active
        
  if (01SwStatus == 0 &&
      02SwStatus == 1 &&
      03SwStatus == 0 &&
      06SwStatus == 0 &&
      09SwStatus == 0 &&
      18SwStatus == 0)
        {return 2};      //sequence 2 is active
        
  if (01SwStatus == 0 &&
      02SwStatus == 0 &&
      03SwStatus == 1 &&
      06SwStatus == 0 &&
      09SwStatus == 0 &&
      18SwStatus == 0)
        {return 3};    //sequence 3 is active
        
  if (01SwStatus == 1 &&
      02SwStatus == 0 &&
      03SwStatus == 1 &&
      06SwStatus == 0 &&
      09SwStatus == 0 &&
      18SwStatus == 0)
        {return 4};    // sequence 4 is active
