#include <FastLED.h>

#include "leds.h"
#define NUM_LEDS 11

#define DATA_PIN 5

CRGB leds[NUM_LEDS];

void ledsInit() {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    ledsOff();
}
void ledsOff() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void displayTemp(uint8_t temp) {
  uint8_t num = 0;
  CRGB color;
  switch(temp) {
    case 0:
      num = 3;
      color = CRGB::Blue;
      break;
    case 1:
      num = 5;
      color = CRGB::Cyan;
      break;
    case 2:
      num = 7;
      color = CRGB::White;
      break;
    case 3:
      num = 9;
      color = CRGB::Orange;
      break;
    case 4:
    default:
      num = 11;
      color = CRGB::Red;
      break;
  }
  for(uint8_t i = 0; i < NUM_LEDS; i ++) {
    if(i < num)
      leds[i] = color;
    else
      leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void rainbow(){
  uint8_t baseHue = 0;  // starting hue
  while(true) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(baseHue + (i * 10), 255, 100);
    }

    FastLED.show();

    // Shift the rainbow over time
    baseHue++;

    delay(10); // controls animation speed
  }
}