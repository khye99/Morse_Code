#include"MorseCodes.h"


//Delta timing variables
unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long unit = 500;
unsigned long delta = 0;

//Other variables
const int led = 13;
int counter = 0;
String w;

//FSM Enum
enum State {
  standby,
  dot,
  dash,
  space,
  btwn,
  spacebar,
};

State s = standby; //Initialize state as standby

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
} 

char toUpper(char c) {
  if (c >= 'a' && c <= 'z') {
    return c^=(1 << 5);
  }
  else {
    return c;
  }
}

void convertIncomingCharsToMorseCode() {
    s = nextState(s);
}

void loop() {
   convertIncomingCharsToMorseCode();
    // each char is its own array
    // space is its own array
}

State nextState(State state) {
      currentTime = millis();
    if (currentTime - previousTime > delta) { //Case switch only runs if delta timing reaches threshold
        previousTime = currentTime; //Set previous time to currentTime (millis)
        
    switch(state) {
        
    case standby:
      if(Serial.available() > 0) {
        digitalWrite(led, LOW);
        String words = morseEncode(Serial.read());
        w = words;
        if(w[counter] == '.') {
          s = dot;
        }
        else if(w[counter] == '-') {
          s = dash;
        }
        else if(w[counter] == ' ') {
          s = spacebar;
        }
        else {
          Serial.println(w[counter]);
        }
      }
      break;

    case dot:
      Serial.print(".");
      digitalWrite(led, HIGH);
      delta = unit;
      s = btwn;
      counter++;
      break;

    case dash:
      Serial.print("-");
      digitalWrite(led, HIGH);
      s = btwn;
      delta = 3*unit;
      counter++;
      break;

    case btwn:                //Gaps between dots/dashes
      digitalWrite(led, LOW);
      if(w[counter] == '.') {
         s = dot;
      }
      else if(w[counter] == '-') {
        s = dash;
      }
      else {
        s = space;
      }
      delta = unit;
      break;

    case space:               //Gaps between letters
      digitalWrite(led, LOW);
      delta = unit;
      s = standby;
      counter = 0;
      break;

      case spacebar:          //Gaps between words
      digitalWrite(led, LOW);
      delta = 2*unit;
      s = standby;
      counter = 0;
      break;
    }
  }
  return s;
}
