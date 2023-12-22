#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Basic loop code
}
