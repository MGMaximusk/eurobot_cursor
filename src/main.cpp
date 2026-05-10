#include <Arduino.h>
#include <Adafruit_AS7341.h>
#include <math.h>
#include "leds.h"

#define LED_BUILTIN 8

#define USW1_PIN 6
#define USW2_PIN 7

Adafruit_AS7341 as7341;

void setup() {
  Serial.begin(115200);
  delay(1000);
  while (!Serial) {
    delay(1);
  }

  Wire.setPins(4, 2); // Set the I2C pins before begin
  Wire.begin(); // join i2c bus (address optional for master)

  pinMode(USW1_PIN, INPUT_PULLUP);
  pinMode(USW2_PIN, INPUT_PULLUP);


  if (!as7341.begin()){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_64X);
  as7341.setLEDCurrent(4); // 4mA
  as7341.enableLED(true);

  ledsInit();

  for(int i = 0; i < 5; i++) {
    displayTemp(i);
    delay(500);
  }
  ledsOff();

  /*Serial.println("Ready");
  while(digitalRead(USW1_PIN) == HIGH && digitalRead(USW2_PIN) == HIGH) {
    delay(10);
  }*/
}

void loop() {
  uint16_t readings[12];
  uint16_t normalized[12];
  uint32_t sum = 0;

  uint16_t blue_score;
  uint16_t red_score;
  
  if (!as7341.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
  }

  for(int i = 0; i < 12; i++) {
    sum += readings[i];
  }
  
  for(int i = 0; i < 12; i++) {
    normalized[i] = (readings[i] * 1000) / sum;
  }

  blue_score = normalized[1] + normalized[2] + normalized[3];
  red_score = normalized[7] + normalized[8] + normalized[9];


  if(blue_score > 180)
    displayTemp(0);
  else if(red_score > 180)
    displayTemp(4);
  else
    displayTemp(2);
  
  
  Serial.print("ADC0/F1 415nm : ");
  Serial.print(readings[0]);
  Serial.print(", ");
  Serial.println(normalized[0]);
  Serial.print("ADC1/F2 445nm : ");
  Serial.print(readings[1]);
  Serial.print(", ");
  Serial.println(normalized[1]);
  Serial.print("ADC2/F3 480nm : ");
  Serial.print(readings[2]);
  Serial.print(", ");
  Serial.println(normalized[2]); 
  Serial.print("ADC3/F4 515nm : ");
  Serial.print(readings[3]);
  Serial.print(", ");
  Serial.println(normalized[3]);
  Serial.print("ADC0/F5 555nm : ");

  /*
  // we skip the first set of duplicate clear/NIR readings
  Serial.print("ADC4/Clear-");
  Serial.println(readings[4]);
  Serial.print("ADC5/NIR-");
  Serial.println(readings[5]);
  */
  
  Serial.print(readings[6]);
  Serial.print(", ");
  Serial.println(normalized[6]);
  Serial.print("ADC1/F6 590nm : ");
  Serial.print(readings[7]);
  Serial.print(", ");
  Serial.println(normalized[7]);
  Serial.print("ADC2/F7 630nm : ");
  Serial.print(readings[8]);
  Serial.print(", ");
  Serial.println(normalized[8]);
  Serial.print("ADC3/F8 680nm : ");
  Serial.print(readings[9]);
  Serial.print(", ");
  Serial.println(normalized[9]);
  Serial.print("ADC4/Clear    : ");
  Serial.print(readings[10]);
  Serial.print(", ");
  Serial.println(normalized[10]);
  Serial.print("ADC5/NIR      : ");
  Serial.print(readings[11]);
  Serial.print(", ");
  Serial.println(normalized[11]);

  Serial.println();
}