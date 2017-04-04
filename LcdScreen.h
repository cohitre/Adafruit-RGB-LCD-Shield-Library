#ifndef Screen_h
#define Screen_h

#include <RGBLCDShield.h>

class LcdScreen {
  uint8_t lastButtons;
  RGBLCDShield lcd;

  private:
  static String pad(String val, int l, char paddingChar);

  public:
  uint8_t currentButtons;

  LcdScreen();
  void reset();

  void clear();

  void readButtons();
  bool wasButtonPressed(unsigned int buttonValue);
  bool wasButtonReleased(unsigned int buttonValue);

  void print(uint8_t x, uint8_t y, String v);
  void print(uint8_t x, uint8_t y, unsigned long v);
  void print(uint8_t x, uint8_t y, int v);
  void printDayTime(uint8_t x, uint8_t y, uint8_t unsigned long v);
  void printChronometerTime(uint8_t x, uint8_t y, uint8_t unsigned long v);
};

#endif
