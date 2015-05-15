/*
Art Car Flame Effect
2015

~-~-~-~-~-~-~-~-QUESTIONS: ~-~-~_~-~-~-~-~-~-~-~-~-
Should I be using ints where I put bytes instead?
JKB: I think bytes are fine here; all the values are small

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

So... this means there are three switches "ones," "threes," and "nines". Each switch has an "off" state (no pins),
and two "on" states: 0 or 2 for the first switch; 0 or 6 for the second; 0 or 18 for the third
*/
const byte onesZero=10;    //12's
const byte onesTwo=11;
const byte threesZero=12;
const byte threesSix=13;
const byte ninesZero=A0;
const byte ninesEighteen=A1;
const byte INVALID_SEQUENCE = -1;
const unsigned long dumbAssTimeOut = 300000;  //How long to wait if it's put into "Safe Mode"

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
  
  pinMode(onesZero,INPUT);
  pinMode(onesTwo,INPUT);
  pinMode(threesZero,INPUT);
  pinMode(threesSix,INPUT);
  pinMode(ninesZero,INPUT);
  pinMode(ninesEighteen,INPUT);

  // Turns on all LED control lights, indicating it's ready
  // Shouldn't be in the loop
  turnOnLEDs();   
}

void loop()
{
  // Match states of manual fire buttons
  digitalWrite(LeftSol, LeftFireSw);
  digitalWrite(RightSol, RightFireSw);

  if (digitalRead(ActivateSw) == HIGH) {
    // Does reading it make it go low? How does an input get reset?
    
    byte selectedSequence = determineSequence();
    
    // Make sure it's a valid (defined) sequence
    if (selectedSequence == INVALID_SEQUENCE) {
      indicateError(3);
    }
    else {
      executeSequence(selectedSequence);
    }
  }
}

void executeSequence(byte sequenceID) {
  switch (sequenceID) {
    case 0: {
      // Implement sequence 0 (if long, make it a separate function)
      // Remember to check for button presses
      for (int x = 0; x < 5; x++) {
        digitalWrite(LeftSol, HIGH);
        delay(200);
        
        // Consider using an external interrupt for this. That would be much cleaner!
        // Now you have to remember to check every single time. How about a big red STOP button 
        // that triggers an external interrupt. Then you can just handle that interrupt by going into
        // dumbAss, and you don't need any checks in the real code
        
        if (hitAnyButtons) {
          dumbAss;
          break;
        }
        digitalWrite(RightSol, HIGH);
        delay(200);
        
        if (hitAnyButtons) {
          dumbAss;
          break;
        }
      }
      
      break;
    }
    case 1: break;
    case 2: break;
    case 3: break;
    case 4: break;
    default: {
      indicateError(5);
    }
  }
}

boolean hitAnyButtons() {
  return (digitalRead(LeftFireSw) == HIGH) ||
         (digitalRead(RightFireSw) == HIGH) ||
         (digitalRead(ActivateSw) == HIGH);
}

void indicateError(int x) {
  // Blink the lights x times to indicate invalid sequence
  for (int x = 0; x < x; x++) {
	turnOffLEDs;
	delay(200);
	turnOnLEDs;
	delay(200);
  }
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

byte determineSequence()
{
  /* Assuming switch can only be in one position!
   * Reading rom left to right (nines -> threes -> ones)
   * U = up (e.g., onesTwo is HIGH)
   * D = down (e.g., onesZero is HIGH)
   * - = OFF (not set)
   */
 
  char seq[4] = {'-', '-', '-', '\0'};
  
  /* Separate logic and make it readable!
   * Read pins and express the state as a string: Left to Right, U/D/- for each switch
   * Then match numeric sequences to readable strings
   */
  
  if (digitalRead(ninesEighteen) == HIGH) {
    seq[0] = 'U';
  }
  else if (digitalRead(ninesZero) == HIGH) {
    seq[0] = 'D';
  }

  if (digitalRead(threesSix) == HIGH) {
    seq[1] = 'U';
  }
  else if (digitalRead(threesZero) == HIGH) {
    seq[1] = 'D';
  }

  if (digitalRead(onesTwo) == HIGH) {
    seq[2] = 'U';
  }
  else if (digitalRead(onesZero) == HIGH) {
    seq[2] = 'D';
  }
  
  // seq now has the encoded state of the switches: e.g., UDU, UUU, DDU, D--, ...
  byte activeSequence = INVALID_SEQUENCE;
  
  // Sequence 0 is all down/down/down
  if (seq == "DDD") {
    activeSequence = 0;
  }
  // Sequence 1 is down/down/off
  else if (seq == "DD-") {
    activeSequence = 1;
  }
  // Sequence 2 is down/down/up
  else if (seq == "DDU") {
    activeSequence = 2;
  }       
  // Sequence 3 is down/off/down
  else if (seq == "D-D") {
    activeSequence = 3;
  }        
  // Sequence 4 is down/off/off
  else if (seq == "D--") {
    activeSequence = 4;
  } 
  
  // Return discovered sequence, or INVALID_SEQUENCE if not defined
  return activeSequence;      
}

