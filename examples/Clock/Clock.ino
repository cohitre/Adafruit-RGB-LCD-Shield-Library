#include <LcdScreen.h>

LcdScreen screen = LcdScreen();

static String states[] = {
  "TIME",
  "CHRONO",
  "EDIT"
};

void setup() {
  screen.reset();
}

int currentState = 0;
long timeOffset = 0;
unsigned long chronometerOffset = 0;
unsigned long lapOffset = 0;

void loop() {
  delay(10);
  screen.readButtons();
  long time = millis();
  long clock = time + timeOffset;

  if (states[currentState] == "TIME") {
    screen.print(0, 0, "TIME");
    screen.printDayTime(0, 1, clock);
  } else if (states[currentState] == "CHRONO") {
    if (lapOffset == 0) {
      screen.print(0, 0, "CHRONOMETER");
    } else {
      screen.printChronometerTime(0, 0, lapOffset);
    }
    screen.printChronometerTime(0, 1, time - chronometerOffset);
    if (screen.wasButtonPressed(BUTTON_UP)) {
      lapOffset = time - chronometerOffset;
    }
  } else if (states[currentState] == "EDIT") {
    screen.print(0, 0, "SET TIME");
    screen.printDayTime(0, 1, clock);
    if (screen.wasButtonPressed(BUTTON_UP)) {
      timeOffset += 3600000;
    } else if (screen.wasButtonPressed(BUTTON_RIGHT)) {
      timeOffset += 60000;
    }
  }
  if (screen.wasButtonPressed(BUTTON_SELECT)) {
    screen.clear();
    lapOffset = 0;
    chronometerOffset = millis();
    currentState = (currentState + 1) % 3;
  }
}
