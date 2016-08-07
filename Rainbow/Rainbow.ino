/*
  08/01/2016
  Author: Makerbro
  Platforms: ESP8266
  Language: C++
  File: Rainbow.ino
  ------------------------------------------------------------------------
  Description: 
  Demo for NeoPixelBus WS2812 LED Library showcasing a rainbow  pattern
  cycle on a WS2812B LED strip controlled by an ESP8266.  Modified from 
  strandtest.ino in the Adafruit NeoPixel Library.
  ------------------------------------------------------------------------
  Dependencies:
  NeoPixelBus Library -
  https://github.com/acrobotic/Ai_Demos_NeoPixelBusz
  ------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 
  https://acrobotic.com/
  ------------------------------------------------------------------------
  License:
  Released under the MIT license. Please check LICENSE.txt for more
  information.  All text above must be included in any redistribution. 
*/

#include <NeoPixelBus.h>

const uint16_t PixelCount = 60;
const uint8_t PixelPin = 2;  // Ignored for Esp8266

#define colorSaturation 128

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setup()
{
    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();
}

void loop() {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.PixelCount(); i++) {
      strip.SetPixelColor(i, Wheel(((i * 256 / strip.PixelCount()) + j) & 255));
    }
    strip.Show();
    delay(50);
  }  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
RgbColor Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return RgbColor(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return RgbColor(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return RgbColor(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

