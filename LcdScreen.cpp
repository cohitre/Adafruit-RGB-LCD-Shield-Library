#include "LcdScreen.h"

String LcdScreen::pad(String val, int l, char paddingChar) {
  return (val.length() < l) ?
    String(paddingChar) + val :
    val;
}

LcdScreen::LcdScreen() {}

void LcdScreen::reset() {
  lcd.begin(16, 2);
}

void LcdScreen::readButtons() {
  lastButtons = currentButtons;
  currentButtons = lcd.readButtons();
};

bool LcdScreen::wasButtonPressed(unsigned int buttonValue) {
  return ((currentButtons & buttonValue) != (lastButtons & buttonValue)) ?
    currentButtons & buttonValue :
    false;
};

bool LcdScreen::wasButtonReleased(unsigned int buttonValue) {
  return ((currentButtons & buttonValue) != (lastButtons & buttonValue)) ?
    !(currentButtons & buttonValue) :
    false;
};

void LcdScreen::print(uint8_t x, uint8_t y, String v) {
  lcd.setCursor(x % 16, y % 2);
  lcd.print(v);
}

void LcdScreen::print(uint8_t x, uint8_t y, unsigned long v) {
  lcd.setCursor(x % 16, y % 2);
  lcd.print(v);
}

void LcdScreen::print(uint8_t x, uint8_t y, int v) {
  lcd.setCursor(x % 16, y % 2);
  lcd.print(v);
}

void LcdScreen::clear() {
  lcd.clear();
}

void LcdScreen::printDayTime(uint8_t x, uint8_t y, uint8_t unsigned long v) {
  unsigned long seconds = v / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = (minutes / 60) % 24;

  String hrs = LcdScreen::pad(String(hours%12 == 0 ? 12 : (hours % 12)), 2, ' ');
  String mns = LcdScreen::pad(String(minutes % 60), 2, '0');
  String scd = LcdScreen::pad(String(seconds % 60), 2, '0');
  String ms = LcdScreen::pad(String(v % 1000), 3, '0');
  this->print(x, y, hrs + ":" + mns + ":" + scd + (hours >= 12 ? "pm": "am"));
}

void LcdScreen::printChronometerTime(uint8_t x, uint8_t y, uint8_t unsigned long v) {
  unsigned long seconds = v / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  String hrs = LcdScreen::pad(String(hours % 24), 2, ' ');
  String mns = LcdScreen::pad(String(minutes % 60), 2, '0');
  String scd = LcdScreen::pad(String(seconds % 60), 2, '0');
  String ms = LcdScreen::pad(String(v % 1000), 3, '0');
  this->print(x, y, hrs + ":" + mns + ":" + scd + "." + ms);
}
