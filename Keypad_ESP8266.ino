// Blynk template and authentication information
#define BLYNK_TEMPLATE_ID "TMPL3gxKbEIS5" 
#define BLYNK_TEMPLATE_NAME "HomeSecurity"
#define BLYNK_AUTH_TOKEN "RDs-5TaFIsxVHn6VEC483jSQKw_JjJ0q"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Annmon"; // WiFi network name
char pass[] = "childsafe"; // WiFi password

#include <Keypad.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},

  {'*','0','#'}
};

// Connect keypad ROW0 to D0, ROW1 to D1, and ROW3 to D2
//Removed ROW2 because of lack of PINS in microcontroller
byte rowPins[ROWS] = {D0, D1, D2}; 
// Connect keypad COL0 to D3, COL1 to D4, and COL3 to D5.
byte colPins[COLS] = {D3, D4, D5};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Initialize the keypad
String v_passcode = ""; // String to store the entered passcode
BlynkTimer timer; // timer object created, BlynkTimer is a class.
void setup() {
  Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  pinMode(D6, OUTPUT); // Buzzer
  pinMode(D7, OUTPUT); // Green LED
  pinMode(D8, OUTPUT); // Red LED
  timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 millisecond
}
// emailsetup being scheduled to be called repeatedly by the BlynkTimer object.
// emailsetup() is scheduled to run every 1 millisecond, almost every time loop() runs, timer.run() will execute emailsetup().
void emailsetup() { 
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
        Blynk.logEvent("password_entry", "Your child reached home"); // Log correct password entry
        Serial.println("Access Granted");
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED
      } else if (v_passcode == "5050#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals as wrong password to parents]*/
      Blynk.logEvent("password_entry", "Your Child is in danger"); // Log wrong password entry
      Serial.println("Pseudo-password entered");
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED
      } else { // Password is wrong
         Blynk.logEvent("password_entry", "Wrong Passcode Entered"); // Log wrong password entry
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
  void loop() {
  Blynk.run(); // Run Blynk process
  timer.run(); // checks if it's time to call any function scheduled by the timer.
}