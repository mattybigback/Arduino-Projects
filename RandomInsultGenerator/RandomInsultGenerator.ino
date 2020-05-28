/*
  Arduino sketch that generates an insulting sentence and displays it on a character display.

  The circuit:
    lcd RS pin to digital pin 7
    lcd Enable pin to digital pin 8
    lcd D4 pin to digital pin 9
    lcd D5 pin to digital pin 10
    lcd D6 pin to digital pin 11
    lcd D7 pin to digital pin 12

    lcd backlight transistor to digital pin 5 (2n7000 mosfet or similar)
    button to digital pin 6

    Rewritten to use PROGMEM instead of arduino String objects.
    
*/

#include <avr/pgmspace.h>
#include <LiquidCrystal.h>

const int insultTime = 5;
const int splashTime = 10;
const int buttonPin = 6;
const int backlightPin = 5;

const char command_0[] PROGMEM = "Fuck off";
const char command_1[] PROGMEM =   "Get bent";
const char command_2[] PROGMEM =   "Suck a dick";
const char command_3[] PROGMEM =   "Eat shit";
const char command_4[] PROGMEM =   "Go to hell";
const char command_5[] PROGMEM =   "Get fucked";
const char command_6[] PROGMEM =   "Piss off";
const char command_7[] PROGMEM =   "Get tae fuck";
const char command_8[] PROGMEM =   "Bugger off";
const char command_9[] PROGMEM =   "Bog off";
const char command_10[] PROGMEM =   "Swivel on it";
const char command_11[] PROGMEM =   "Take a hike";
const char command_12[] PROGMEM =   "Get a wash";
const char command_13[] PROGMEM =   "Leave me be";
const char command_14[] PROGMEM =   "Shit on it";
const char command_15[] PROGMEM =   "Shut it";
const char command_16[] PROGMEM =   "Belt up";
const char command_17[] PROGMEM =   "Bite me";
const char command_18[] PROGMEM =   "Give over";
const char command_19[] PROGMEM =   "Buzz off";
const char command_20[] PROGMEM =   "Go get AIDS";

const char observation_0[] PROGMEM = "You total";
const char observation_1[] PROGMEM = "You're a real";
const char observation_2[] PROGMEM = "You're such a";
const char observation_3[] PROGMEM = "You utter";
const char observation_4[] PROGMEM = "You complete";
const char observation_5[] PROGMEM = "You";
const char observation_6[] PROGMEM = "What an utter";
const char observation_7[] PROGMEM = "You're a";

const char adjective_0[] PROGMEM = "weak";
const char adjective_1[] PROGMEM = "fat";
const char adjective_2[] PROGMEM = "ugly";
const char adjective_3[] PROGMEM = "thick";
const char adjective_4[] PROGMEM = "toxic";
const char adjective_5[] PROGMEM = "utter";
const char adjective_6[] PROGMEM = "fucking";
const char adjective_7[] PROGMEM = "stupid";
const char adjective_8[] PROGMEM = "pompous";
const char adjective_9[] PROGMEM = "spotty";
const char adjective_10[] PROGMEM = "zitty";
const char adjective_11[] PROGMEM = "dim";
const char adjective_12[] PROGMEM = "scabby";
const char adjective_13[] PROGMEM = "smelly";
const char adjective_14[] PROGMEM = "fithy";
const char adjective_15[] PROGMEM = "dirty";
const char adjective_16[] PROGMEM = "failed";
const char adjective_17[] PROGMEM = "cunty";
const char adjective_18[] PROGMEM = "little";
const char adjective_19[] PROGMEM = "sweaty";
const char adjective_20[] PROGMEM = "silly";

const char insult_0[] PROGMEM = "cunt";
const char insult_1[] PROGMEM = "bitch";
const char insult_2[] PROGMEM = "prick";
const char insult_3[] PROGMEM = "arsehole";
const char insult_4[] PROGMEM = "dickhead";
const char insult_5[] PROGMEM = "wanker";
const char insult_6[] PROGMEM = "twat";
const char insult_7[] PROGMEM = "fucker";
const char insult_8[] PROGMEM = "smeghead";
const char insult_9[] PROGMEM = "bastard";
const char insult_10[] PROGMEM = "cretin";
const char insult_11[] PROGMEM = "cumstain";
const char insult_12[] PROGMEM = "douche";
const char insult_13[] PROGMEM = "dumbass";
const char insult_14[] PROGMEM = "freak";
const char insult_15[] PROGMEM = "moron";
const char insult_16[] PROGMEM = "nimrod";
const char insult_17[] PROGMEM = "shithead";
const char insult_18[] PROGMEM = "veruca";
const char insult_19[] PROGMEM = "shitsack";
const char insult_20[] PROGMEM = "plonker";
const char insult_21[] PROGMEM = "snob";
const char insult_22[] PROGMEM = "titbag";
const char insult_23[] PROGMEM = "troll";
const char insult_24[] PROGMEM = "wretch";
const char insult_25[] PROGMEM = "failure";
const char insult_26[] PROGMEM = "wannabe";
const char insult_27[] PROGMEM = "weirdo";
const char insult_28[] PROGMEM = "noob";
const char insult_29[] PROGMEM = "oddball";

// Then set up a table to refer to your strings.

const char *const command_table[] PROGMEM = {command_0,
                                             command_1,
                                             command_2,
                                             command_3,
                                             command_4,
                                             command_5,
                                             command_6,
                                             command_7,
                                             command_8,
                                             command_9,
                                             command_10,
                                             command_11,
                                             command_12,
                                             command_13,
                                             command_14,
                                             command_15,
                                             command_16,
                                             command_17,
                                             command_18,
                                             command_19,
                                             command_20
                                            };

const char *const observation_table[] PROGMEM = {observation_0,
                                                 observation_1,
                                                 observation_2,
                                                 observation_3,
                                                 observation_4,
                                                 observation_5,
                                                 observation_6,
                                                 observation_7
                                                };

const char *const adjective_table[] PROGMEM = { adjective_0,
                                                adjective_1,
                                                adjective_2,
                                                adjective_3,
                                                adjective_4,
                                                adjective_5,
                                                adjective_6,
                                                adjective_7,
                                                adjective_8,
                                                adjective_9,
                                                adjective_10,
                                                adjective_11,
                                                adjective_12,
                                                adjective_13,
                                                adjective_14,
                                                adjective_15,
                                                adjective_16,
                                                adjective_17,
                                                adjective_18,
                                                adjective_19,
                                                adjective_20
                                              };

const char *const insult_table[] PROGMEM = {    insult_0,
                                                insult_1,
                                                insult_2,
                                                insult_3,
                                                insult_4,
                                                insult_5,
                                                insult_6,
                                                insult_7,
                                                insult_8,
                                                insult_9,
                                                insult_10,
                                                insult_11,
                                                insult_12,
                                                insult_13,
                                                insult_14,
                                                insult_15,
                                                insult_16,
                                                insult_17,
                                                insult_18,
                                                insult_19,
                                                insult_20,
                                                insult_21,
                                                insult_22,
                                                insult_23,
                                                insult_24,
                                                insult_25,
                                                insult_26,
                                                insult_27,
                                                insult_28,
                                                insult_29
                                           };

size_t commandCount = sizeof(command_table) / sizeof(command_table[0]);
size_t observationCount = sizeof(observation_table) / sizeof(observation_table[0]);
size_t adjectiveCount = sizeof(adjective_table) / sizeof(adjective_table[0]);
size_t insultCount = sizeof(insult_table) / sizeof(insult_table[0]);

char buffer[15];  // make sure this is large enough for the largest string it must hold

// Holds the current and last states of the button
char buttonState = 1;
char lastButtonState = 1;

//Holds the current and previous timer readings
int timer;
int timerOld;

// Status variable that keeps track of which screen is visible
byte screenNumber = 1;

byte brightness = 255;

// initialize the LCD library
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() {
  //  Serial.begin(9600);
  //  while (!Serial);                  // wait for serial port to connect. Needed for native USB
  pinMode(buttonPin, INPUT_PULLUP);     // Set pinmode to input with internal pullup
  pinMode(backlightPin, OUTPUT);        // Set pinmode to output
  digitalWrite(backlightPin, HIGH);     // Set backlight pin high
  randomSeed(analogRead (A0));          //Seed the random function with two unconnected pins
  lcd.begin(16, 2);                     //Set up lcd display with correct size
  timer = millis() / 1000;              //Set up timer variable
  splashScreen();                       //Load splash screen
}

void loop() {
  buttonState = digitalRead(buttonPin);       // Read button pin
  if (buttonState != lastButtonState) {       // If the button is in a different state to the last reading call the insult function
    if (buttonState == LOW) {
      insultMe();
    }
    lastButtonState = buttonState;            //Store the last button state
  }
  timer = millis() / 1000;                    //Store the current timer value

  /*
    If there have been more than the set number of seconds between the old timer reading and
    the current timer reading AND the splash screen is not currently being displayed
    then call the splash screen
  */
  if (timer - timerOld >= insultTime && screenNumber == 1) {
    splashScreen();
  }

  /*
    If there have been more than the set numnber of seconds between the old timer reading and
    the current timer reading AND the splash screen is currently being displayed
    then dim the backlight and clear the screen.
  */
  if (timer - timerOld >= splashTime && screenNumber == 0 && brightness > 0) {
    if (millis() % 20 == 0) {
      brightness--;
      analogWrite(backlightPin, brightness) ;
    }
    if (brightness == 0) {
      lcd.clear();
    }
  }
  
}

void insultMe() {
  brightness = 255;                                         // Set brigntness variable
  analogWrite(backlightPin, brightness);                    // Write brightness
  screenNumber = 1;                                         // Set the screen status variable to 1
  timerOld = timer;                                         // Store the current value of the timer variable in the timerOld variable
  char insultType = random(2);                              // Randomly select which type of insult to generate
  char idxc = random(commandCount);                         // Generate random number for command_table index
  char idxo = random(observationCount);                     // Generate random number for observation_table index
  char idxa = random(adjectiveCount);                       // Generate random number for adjective_table index
  char idxi = random(insultCount);                          // Generate random number for insult_table index


  lcd.setCursor(0, 0);                                      // Move cursor to home position
  lcd.clear();                                              // Clear LCD
  
  /*
    If insult type is 0 print a command, an adjective and then an insult.
    If insult tyoe is 1 print an observation and then an insult. 
  */
  if (insultType == 0) {
    strcpy_P(buffer, (char *)pgm_read_word(&(command_table[idxc])));  // Necessary casts and dereferencing, just copy.
    lcd.print(buffer);
    lcd.print(" you");
    lcd.setCursor(0, 1);
    strcpy_P(buffer, (char *)pgm_read_word(&(adjective_table[idxa])));  // Necessary casts and dereferencing, just copy.
    lcd.print(buffer);
    lcd.print(" ");

  } else {
    strcpy_P(buffer, (char *)pgm_read_word(&(observation_table[idxo])));  // Necessary casts and dereferencing, just copy.
    lcd.print(buffer);
    lcd.setCursor(0, 1);
  }

  strcpy_P(buffer, (char *)pgm_read_word(&(insult_table[idxi])));  // Necessary casts and dereferencing, just copy.
  lcd.print(buffer);
}

void splashScreen() {
  brightness = 255;
  analogWrite(backlightPin, brightness);
  screenNumber = 0;                                       // Set the screen status variable to 0
  timerOld = timer;                                       // Store the current value of the timer variable in the timerOld variable
  lcd.clear();                                            // Clear screen (sometimes it loads up with garbage)
  lcd.setCursor(0, 0);                                    // Set the cursor to row 0, column 0
  lcd.print("INSULTATRON 9000");                          // Print splash text
  lcd.setCursor(0, 1);                                    // Set the cursor to row 1, column 0
  lcd.print(commandCount * adjectiveCount * insultCount + observationCount * insultCount); // Print total number of possible insults
  lcd.print(" INSULTS!");                                 // Print rest of message
}
