#include <Keypad.h>

const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect keypad ROW0, ROW1, ROW2, and ROW3 to these pins.
byte rowPins[ROWS] = {D1, D2, D3, D4}; 
// Connect keypad COL0, COL1, COL2, and COL3 to these pins.
byte colPins[COLS] = {D5, D6, D7, D8};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Initialize the keypad
String v_passcode = ""; // String to store the entered passcode

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  pinMode(D6, OUTPUT); // Buzzer
  pinMode(D7, OUTPUT); // Green LED
  pinMode(D8, OUTPUT); // Red LED
}

void loop() {
   char key = keypad.getKey(); // Read the key that is pressed
}
