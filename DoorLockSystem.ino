#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Servo setup
Servo myServo;
const int servoPin = 10;

// LCD setup (I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 4x4 Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};  // Rows → Pins 2-5
byte colPins[COLS] = {6, 7, 8, 9};   // Columns → Pins 6-9
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Buzzer pin
const int buzzerPin = 11;

// Password settings
char password[] = "1234";  // Default password
char inputBuffer[4];       // Stores entered digits
int bufferIndex = 0;
bool settingPassword = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Enter Password:");

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    // Debug: Print all key presses to Serial Monitor
    Serial.print("Key Pressed: ");
    Serial.println(key);

    // -- PASSWORD SETTING MODE (Triggered by 'A') --
    if (key == 'A' && !settingPassword) {
      settingPassword = true;
      bufferIndex = 0;
      lcd.clear();
      lcd.print("Set New Password:");
      tone(buzzerPin, 800, 200);
      Serial.println("Mode: Password Setting");
      return;
    }

    // -- NUMERIC KEY INPUT (0-9) --
    if (key >= '0' && key <= '9') {
      if (bufferIndex < 4) {
        inputBuffer[bufferIndex] = key;
        bufferIndex++;
        
        // LCD: Show * for security
        lcd.setCursor(bufferIndex-1, 1);
        lcd.print("*");
        
        // Serial Monitor: Show actual digits (debug)
        Serial.print("Input: ");
        for (int i=0; i<bufferIndex; i++) {
          Serial.print(inputBuffer[i]);
        }
        Serial.println();
      }

      // Check if 4 digits entered
      if (bufferIndex == 4) {
        if (settingPassword) {
          // Save new password
          for (int i=0; i<4; i++) {
            password[i] = inputBuffer[i];
          }
          lcd.clear();
          lcd.print("New Password Set!");
          tone(buzzerPin, 1000, 500);
          Serial.print("New Password: ");
          Serial.println(password);
          settingPassword = false;
        } else {
          // Verify password
          bool correct = true;
          for (int i=0; i<4; i++) {
            if (inputBuffer[i] != password[i]) {
              correct = false;
              break;
            }
          }

          lcd.clear();
          if (correct) {
            lcd.print("Access Granted!");
            myServo.write(0);
            tone(buzzerPin, 1000, 500);
            Serial.println("Result: Correct Password");
          } else {
            lcd.print("Access Denied!");
            myServo.write(90);
            tone(buzzerPin, 300, 1000);
            Serial.println("Result: Wrong Password");
          }
        }

        // Reset for next input
        bufferIndex = 0;
        delay(2000);
        lcd.clear();
        lcd.print(settingPassword ? "Set New Password:" : "Enter Password:");
      }
    }

    // -- SPECIAL KEYS --
    else if (key == '*') {
      // Reset system
      myServo.write(0);
      noTone(buzzerPin);
      settingPassword = false;
      bufferIndex = 0;
      lcd.clear();
      lcd.print("Enter Password:");
      Serial.println("System Reset");
    }
    else if (key == '#') {
      // Cancel password setting
      if (settingPassword) {
        settingPassword = false;
        tone(buzzerPin, 300, 200);
        Serial.println("Password Setting Cancelled");
      }
      noTone(buzzerPin);
      bufferIndex = 0;
      lcd.clear();
      lcd.print("Enter Password:");
    }
  }
}
