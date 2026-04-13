#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

int leds[4] = {30, 4, 12, 6};
int modeLED = 13;

// Buttons
const int BTN_TIME  = 0;   // Show time (mode 0)
const int BTN_DATE  = 1;   // Show date dd/mm (mode 1)
const int BTN_YEAR  = 11;  // Show year (mode 2)

// Mode blink durations (ON time, OFF time in ms)
// Mode 0 = time  -> fastest
// Mode 1 = date  -> medium
// Mode 2 = year  -> slowest
int blinkOn[3]  = {200, 400, 700};
int blinkOff[3] = {200, 400, 700};

int currentMode = 0; // Default: show time

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(modeLED, OUTPUT);

  pinMode(BTN_TIME, INPUT_PULLUP);
  pinMode(BTN_DATE, INPUT_PULLUP);
  pinMode(BTN_YEAR, INPUT_PULLUP);

  Wire.begin();

  if (!rtc.begin()) {
    while (1) {
      for (int j = 0; j < 4; j++) digitalWrite(leds[j], HIGH);
      digitalWrite(modeLED, HIGH);
      delay(100);
      for (int j = 0; j < 4; j++) digitalWrite(leds[j], LOW);
      digitalWrite(modeLED, LOW);
      delay(100);
    }
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2026, 4, 7, 22, 4, 00));
  }
}

void displayBinary(int num) {
  for (int i = 0; i < 4; i++) {
    int bit = (num >> (3 - i)) & 0x01;
    digitalWrite(leds[i], bit ? HIGH : LOW);
  }
}

// Mode-aware blink: blinks count times at the rate for currentMode
// Also checks buttons during the pauses so input feels responsive
void blinkMode(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(modeLED, HIGH);
    delayWithButtonCheck(blinkOn[currentMode]);
    digitalWrite(modeLED, LOW);
    delayWithButtonCheck(blinkOff[currentMode]);
  }
  delayWithButtonCheck(300);
}

void clearBinary() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void blinkAll() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(leds[j], HIGH);
    digitalWrite(modeLED, HIGH);
    delay(300);
    for (int j = 0; j < 4; j++) digitalWrite(leds[j], LOW);
    digitalWrite(modeLED, LOW);
    delay(300);
  }
}

// Non-blocking delay that checks buttons every 50ms
// If a button is pressed, updates currentMode immediately and returns
void delayWithButtonCheck(int ms) {
  int elapsed = 0;
  while (elapsed < ms) {
    checkButtons();
    delay(50);
    elapsed += 50;
  }
}

void checkButtons() {
  if (digitalRead(BTN_TIME) == LOW) {
    currentMode = 0;
    delay(50); // debounce
  }
  else if (digitalRead(BTN_DATE) == LOW) {
    currentMode = 1;
    delay(50);
  }
  else if (digitalRead(BTN_YEAR) == LOW) {
    currentMode = 2;
    delay(50);
  }
}

void showTime(DateTime now) {
  int hours   = now.hour();
  int minutes = now.minute();
  int digits[4] = {
    hours   / 10,
    hours   % 10,
    minutes / 10,
    minutes % 10
  };
  for (int i = 0; i < 4; i++) {
    clearBinary();
    blinkMode(i + 1);
    displayBinary(digits[i]);
    delayWithButtonCheck(1000);
  }
}

void showDate(DateTime now) {
  int day   = now.day();
  int month = now.month();
  int digits[4] = {
    day   / 10,
    day   % 10,
    month / 10,
    month % 10
  };
  for (int i = 0; i < 4; i++) {
    clearBinary();
    blinkMode(i + 1);
    displayBinary(digits[i]);
    delayWithButtonCheck(1000);
  }
}

void showYear(DateTime now) {
  int year = now.year(); // e.g. 2026
  int digits[4] = {
    (year / 1000) % 10,
    (year / 100)  % 10,
    (year / 10)   % 10,
     year         % 10
  };
  for (int i = 0; i < 4; i++) {
    clearBinary();
    blinkMode(i + 1);
    displayBinary(digits[i]);
    delayWithButtonCheck(1000);
  }
}

void loop() {
  checkButtons();
  DateTime now = rtc.now();

  if (currentMode == 0) {
    showTime(now);
  } else if (currentMode == 1) {
    showDate(now);
  } else if (currentMode == 2) {
    showYear(now);
  }

  blinkAll();
  delayWithButtonCheck(1000);
}