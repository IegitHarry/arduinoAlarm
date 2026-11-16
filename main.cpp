// C++ code
//
#include <Keypad.h>

#define STATE_Roz 1
#define STATE_Zbr 2
#define STATE_Uzb 3
#define STATE_Rozbr 4
#define STATE_Alarm 5

uint8_t STATE = 1;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '#'},
  {'4', '5', '6', '#'},
  {'7', '8', '9', '#'},
  {'#', '0', '#', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const String correctPassword = "1234";
String password;
char c;

unsigned long startTime;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  switch(STATE) {
  	case STATE_Roz:
    	c = customKeypad.getKey();
    	if (c) {
          if (c != '#') {
              if (password.length() < 4)
                  password += c;
          }
          else if (c == '#') {
            if (password == correctPassword) {
                password = "";
              	startTime = millis();
                STATE = 2;
            }
            else
            	password = "";
          }
        }
    	break;
    case STATE_Zbr:
    	digitalWrite(11, HIGH);
    	if (millis() - startTime >= 5000) {
         	digitalWrite(11, LOW);
    		STATE += 1;
        }
    	break;
    case STATE_Uzb:
    	digitalWrite(13, HIGH);
    	if (digitalRead(12) == HIGH) {
          startTime = millis();
          STATE = 4;
        }
    	break;
    case STATE_Rozbr:
      	if (millis() - startTime >= 5000) {
          password = "";
          STATE = 5;
          digitalWrite(11, LOW);
          break;
        }
    	digitalWrite(11, HIGH);
    	c = customKeypad.getKey();
    	if (c) {
          if (c != '#') {
              if (password.length() < 4)
                  password += c;
          }
          else if (c == '#') {
            if (password == correctPassword) {
                password = "";
              	digitalWrite(13, LOW);
              	digitalWrite(11, LOW);
                STATE = 1;
            }
            else {
            	password = "";
            	STATE = 5;
            }
          }
        }
    	break;
    case STATE_Alarm:
    	if (millis() - startTime < 20000) {
        	tone(A3, 500);
        	if (((millis() - startTime) / 1000) % 2 == 0) {
        		digitalWrite(10, HIGH);
         	} 
          	else
            	digitalWrite(10, LOW);
        } 
    	else {
          noTone(A3);
          digitalWrite(10, LOW);
          STATE = 3;
        }
    	break;
  }
}
