/*
Art Car Flame Effect
2015

~-~-~-~-~-~-~-~-QUESTIONS: ~-~-~_~-~-~-~-~-~-~-~-~-
Shold I be using ints where I put bytes instead?

Can I use arrays instead of so much repetition in
  the "determineSequence" function?
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
const byte RightSol=9;   //Right solenoid

/*
Next are the input pins for the ternery number switches. These will control
what sequence the Arduino will play when the activate button is pressed.
*/
const byte onesZero=10;    //12's
const byte onesTwo=11;
const byte threesZero=12;
const byte threesSix=13;
const byte ninesZero=A0;
const byte ninesEighteen=A1;
const unsigned long dumbAssTimeOut=300000;  //How long to wait if it's put into
void setup()                                //"Safe Mode."
{
  pinMode(LeftFireSw,INPUT);
  pinMode(RightFireSw,INPUT);
  pinMode(ActivateSw,INPUT);
  
  pinMode(LeftLED,OUTPUT);
  pinMode(RightLED,OUTPUT);
  pinMode(ActivateLED,OUTPUT);
  
  pinMode(LeftSol,OUTPUT);
  pinMode(RightSol,OUTPUT);
  
  pinMode(onesZero,INPUT);
  pinMode(onesTwo,INPUT);
  pinMode(threesZero,INPUT);
  pinMode(threesSix,INPUT);
  pinMode(ninesZero,INPUT);
  pinMode(ninesEighteen,INPUT);
  
}

void loop()
{
  turnOnLEDs();    //Turns on all LED control lights, indicating it's ready
  
  byte selectedSequence = determineSequence();
  
  
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
  //To be filled in later
}
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

byte determineSequence()  //Can I use array??
{
  if (digitalRead(onesZero) == HIGH &&
      digitalRead(onesTwo) == LOW &&
      digitalRead(threesZero) == HIGH &&
      digitalRead(threesSix) == LOW &&
      digitalRead(ninesZero) == HIGH &&
      digitalRead(ninesEighteen) == LOW)
        return 0;      //sequence 0 is active

  if (digitalRead(onesZero) == LOW &&
      digitalRead(onesTwo) == LOW &&
      digitalRead(threesZero) == HIGH &&
      digitalRead(threesSix) == LOW &&
      digitalRead(ninesZero) == HIGH &&
      digitalRead(ninesEighteen) == LOW)
        return 1;      //sequence 1 is active
        
  if (digitalRead(onesZero) == LOW &&
      digitalRead(onesTwo) == HIGH &&
      digitalRead(threesZero) == HIGH &&
      digitalRead(threesSix) == LOW &&
      digitalRead(ninesZero) == HIGH &&
      digitalRead(ninesEighteen) == LOW)
        return 2;      //sequence 2 is active
        
  if (digitalRead(onesZero) == HIGH &&
      digitalRead(onesTwo) == LOW &&
      digitalRead(threesZero) == LOW &&
      digitalRead(threesSix) == LOW &&
      digitalRead(ninesZero) == HIGH &&
      digitalRead(ninesEighteen) == LOW)
        return 3;      //sequence 3 is active
        
  if (digitalRead(onesZero) == LOW &&
      digitalRead(onesTwo) == LOW &&
      digitalRead(threesZero) == LOW &&
      digitalRead(threesSix) == LOW &&
      digitalRead(ninesZero) == HIGH &&
      digitalRead(ninesEighteen) == LOW)
        return 4;    // sequence 4 is active
 //AND SO ON...       
}

