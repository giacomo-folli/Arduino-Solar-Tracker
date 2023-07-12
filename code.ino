#include <Servo.h>

// DEFINE SERVO
Servo servohori;
const int servohPin = 7;
const int servohLimitHigh = 160;
const int servohLimitLow = 60;

// SET PINs
const int ldrtoprPin = A1;  // fotoresistenza destra
const int ldrbotrPin = A0;  // fotoresistenza sinistra
const int VRX_PIN = A5;     // joystick X axis
const int buttonPin = 8;
const int ledPin = 13;

// SET VARIABLES
int servoh = servohLimitLow;
int buttonState = 0;
int oldButtonState = 0;
int ledState = 0;

// SETUP
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  servohori.attach(servohPin);
  servohori.write(servoh);
  delay(500);
}

// LOOP
void loop() {
  // READ
  int left = analogRead(ldrtoprPin);
  int right = analogRead(ldrbotrPin);

  // Check button state
  buttonState = digitalRead(buttonPin);
  if (buttonState != oldButtonState && buttonState == 1) {
    ledState = 1 - ledState;
    digitalWrite(ledPin, ledState);
    delay(50);
  }
  oldButtonState = buttonState;

  if (ledState == 1) {  // Automatic control
    if (left < right) {
      servoh++;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    } else if (right < left) {
      servoh--;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    }
  } else if (ledState == 0) {  // Manual control
    int vrxValue = analogRead(VRX_PIN);
    if (506 < vrxValue && vrxValue < 519) {
      // Do nothing
    } else if (vrxValue < 505) {
      servoh--;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    } else if (vrxValue > 520) {
      servoh++;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    }
  }
  
  servohori.write(servoh);
  delay(10);
}
