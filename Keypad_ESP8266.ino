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
    if (key != NO_KEY) { // If a key is pressed, add it to the passcode string
    v_passcode = v_passcode + key; // Append the pressed key to the passcode

    if (key == '*') { // Check if '*' is pressed to reset passcode entry
      Serial.println("Enter Password");
      v_passcode = ""; // Reset the passcode
    }

    if (key == '#') {  // Check if '#' is pressed to validate the passcode
      Serial.println("Validate the Password");
      if (v_passcode == "1234#") { // Password is correct
        Serial.println("Access Granted");
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED
      } else if (v_passcode == "5050#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals as wrong password to parents]*/
      Serial.println("Pseudo-password entered");
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED
      } else { // Password is wrong
         Serial.println("Access Denied");
           for (int i = 0; i < 3; i++) {
          digitalWrite(D6, HIGH);
          delay(50);
          digitalWrite(D6, LOW);
          delay(50);
        }
          digitalWrite(D8,HIGH);
          delay(2000);
          digitalWrite(D8,LOW);
      }
      Serial.println("The entered password is " + v_passcode);
    }
    }
  }