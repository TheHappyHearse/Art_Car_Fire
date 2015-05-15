/* *********** Hardware Configuration: ************ */


#define SOLENOID_PIN         9 // Connect the solenoid to this pin
#define BUTTON_LIGHT_PIN     6 // Connect the button light to this pin
#define BUTTON_PIN           10 // Connect the button to this pin
#define SYSTEM_ENABLE_PIN    11 // Connect the system disable switch to this pin.
#define RANDOM_SEED_PIN      A0 // Do not connect anything to this pin - leave it floating.

/* *********** Configurable parameters: ************ */

// The amount of time the system will be disabled after firing.
#define CYCLE_TIME           30000   // in milliseconds.  30000 = 30 seconds

// The total # of sequences that have been enabled
#define NUM_SEQUENCES        3       // min of 1, max of 10

// Will the sequences be selected at random or sequentially
#define RANDOM_SEQUENCE      false   // true = random, false = sequential

// Button "throb" effect.  Large numbers will cause a faster "throb". 0 = no throb effect
float     buttonIntInterval  = 0.01; 

// Maximum valve open time. 
// This is a safety feature that will prevent the 
// dangerous situartions if the sequence terminator is accedentally left out.
#define MAX_VALVE_OPEN_TIME  5000

/* *********** System variables: ************ */
// These do not normally need to be edited.
boolean locked               = false;  // Stores the system time lock state
int     currentSeq           = 1; // Stores the number of the current (or next) sequence.
float   buttonIntensity      = 0; // Stores the brightness of the button LED
unsigned long lastSeqTime    = 0; //  Stores the time the last sequence ended.

/* *********** Sequence data: ************ */
/* Structure: first number is the valve state.  0 = closed, 1 = open. 
 Note: The default valve state is closed so there is no need to close it at the start or end of the sequence. 
 The second number is the duration for that valve state in milliseconds.  
 The sequence repeats for each step.  A negative number will end the sequence and close the valve.
 Example: { 1, 1000, 0, 200, 1, 300, -1 }  - This will open the valve for 1 second, close it for 200ms, 
 then open it again for 300ms, the close it and cycle the system. */

//Shave and a hair cut - tested
//  1, 50,
//  0, 500,
//  
//  1, 35,
//  0, 300,
//  
//  1, 35,
//  0, 300,
//  
//  1, 50,
//  0, 500,
//  
//  1, 50,
//  0, 1000,
//  
//  1, 100,
//  0, 750,
//  
//  1, 400,



static int seq1[] = {

  1, 35,
  0, 3500,
  
  1, 35,
  0, 200,
  
  1, 1000,

  -1 // -1 terminates the sequence. 
};

static int seq2[] = {    //This is the barbershop sequence.
  1, 50,
  0, 500,
  
  1, 35,
  0, 300,
  
  1, 35,
  0, 300,
  
  1, 50,
  0, 500,
  
  1, 50,
  0, 1000,
  
  1, 100,
  0, 750,
  
  1, 400,

  -1 // -1 terminates the sequence. 
};

static int seq3[] = {    //Tested and approved.
  0, 5000,

  1, 50,
  0, 200,
  
  1, 100,
  0, 200,
  
  1, 50,

  -1 // -1 terminates the sequence. 
};

static int seq4[] = {  //no good, replace this one 1st attempt at barbershop Redo anything after this.
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

static int seq5[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

static int seq6[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

static int seq7[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

static int seq8[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

static int seq9[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,

  -1 // -1 terminates the sequence. 
};

static int seq10[] = {
  1, 100,
  0, 300,
  1, 75,
  0, 200,
  1, 75,
  0, 200,
  1, 100,
  0, 300,
  1, 100,
  0, 300,
  1, 100,
  0, 500,
  1, 100,
  0, 500,
  -1 // -1 terminates the sequence. 
};

// ************** Setup the system ************

void setup() {
  Serial.begin(9600);

  pinMode(SOLENOID_PIN, OUTPUT);
  //  pinMode(BUTTON_LIGHT_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SYSTEM_ENABLE_PIN, INPUT);
  randomSeed(analogRead(RANDOM_SEED_PIN)); // This will read noise and use the value to seed the random number generator. 

}

void loop() {

  // Make sure the valve is closed.  This is redundent but is a good idea for safety.   
  digitalWrite( SOLENOID_PIN, LOW );

  //Serial.print("Locked = ");
  //Serial.print(locked);
  //Serial.print(" buttonIntensity = ");
  //Serial.println(buttonIntensity);

  if ( locked ) {
    analogWrite(BUTTON_LIGHT_PIN, 0); // Make sure the button is not lit.
    if ( millis() > ( lastSeqTime + CYCLE_TIME ) ) {  //check to see if the cycle time has passed
      if ( digitalRead( SYSTEM_ENABLE_PIN ) ) {  // if the system is disabled, make sure it stays locked.
        locked = false; 
        Serial.println ("Unlock");
      } 
      else {
        locked = true; 
      }
    }
  } 
  else {

    if ( digitalRead( BUTTON_PIN ) ) {

      if ( currentSeq == 1 ) buttonPressed( seq1 );
      if ( currentSeq == 2 ) buttonPressed( seq2 );
      if ( currentSeq == 3 ) buttonPressed( seq3 );
      if ( currentSeq == 4 ) buttonPressed( seq4 );
      if ( currentSeq == 5 ) buttonPressed( seq5 );
      if ( currentSeq == 6 ) buttonPressed( seq6 );
      if ( currentSeq == 7 ) buttonPressed( seq7 );
      if ( currentSeq == 8 ) buttonPressed( seq8 );
      if ( currentSeq == 9 ) buttonPressed( seq9 );
      if ( currentSeq == 10 ) buttonPressed( seq10 );

      if (RANDOM_SEQUENCE) {
        currentSeq = random(1, ( NUM_SEQUENCES + 1 ) );
      } 
      else {
        currentSeq++;
        if ( currentSeq > NUM_SEQUENCES ) currentSeq = 1;
      }

    }
  }

  // light the button...
  if (!locked) { // only light when it's unlocked.
    if ( buttonIntInterval != 0 ) { // do the throb

      buttonIntensity += buttonIntInterval;
      if ( buttonIntensity > 255 ) {
        buttonIntensity = 255;
        buttonIntInterval = -buttonIntInterval;  
      }
      if ( buttonIntensity < 0 ) {
        buttonIntensity = 0;
        buttonIntInterval = -buttonIntInterval;  
      }
      analogWrite(BUTTON_LIGHT_PIN, buttonIntensity);
    } 
    else { // No throb, just light it up.
      analogWrite(BUTTON_LIGHT_PIN, 255);
    }
  }

}

void buttonPressed( int *seqData) {

  Serial.println ("Button Pressed");

  // If the system is time locked, then do not fire.
  if ( locked ) return;

  // Double check: if the disable switch is on, then do not fire.
  if ( !digitalRead( SYSTEM_ENABLE_PIN ) ) {
    return;
  }

  // time lock the system...
  locked = true;

  // make sure the button is not lit.
  analogWrite( BUTTON_LIGHT_PIN, 0 ); 

  Serial.println ("Seq Start");
  int x = 0;

  int y = 0;

  for (y = 0; y < 100; y++ ) { // up to 100 steps

    x = y * 2;
    Serial.print ("Valve State = ");
    Serial.println (seqData[x]);
    Serial.print ("Delay = ");
    Serial.println (seqData[x + 1]);
    Serial.print ("x = ");
    Serial.println (x);

    // Terminates the sequence on any negative number.
    if ( seqData[x] < 0 ) break;
    if ( seqData[x + 1] < 0 ) break;

    // These lines are for safety.  If the data wants to open the valve for more than 5 sec, 
    // then the whole sequence aborts and the valve closes.  
    // If the negative number is left out, then the program will start reading 
    // "garbage" data which could cause the valve to stay open for a long time.
    if ( seqData[x] && (seqData[ x + 1 ] > MAX_VALVE_OPEN_TIME ) ) break;
    // If the valve state number is not 0 or 1, the abort.
    if ( seqData[x] > 1 || seqData[x] < 0 ) break;


    // actually open/close the valve
    digitalWrite( SOLENOID_PIN, seqData[x] );
    delay( seqData[ x + 1 ] );
  }

  Serial.println ("Seq End");

  // record the sequence start time.
  lastSeqTime = millis();

  // Close the valve at the end of the sequence
  digitalWrite( SOLENOID_PIN, LOW );

  buttonIntensity = 0;

}















