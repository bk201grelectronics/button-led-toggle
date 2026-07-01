#include <Arduino.h>

#define LED_PIN 4
#define BUTTON_PIN 5
#define BAUD_RATE 115200

const unsigned long DEBOUNCE_MS = 50;

int ledState = LOW;
int currentButtonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceMillis = 0;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("App started ");
}

void loop() {
  int rawReading = digitalRead(BUTTON_PIN);

  if (rawReading != lastButtonState) {
    lastDebounceMillis = millis();
    lastButtonState = rawReading;
  }

  if (millis() - lastDebounceMillis >= DEBOUNCE_MS) {
    if (rawReading != currentButtonState) {
      currentButtonState = rawReading;

      if (currentButtonState == LOW) {
        Serial.println("Button Pressed ");
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      } else if (currentButtonState == HIGH) {
        Serial.println("Button Released ");
      }
    }
  }
}