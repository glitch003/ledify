#include <FastLED.h>
#include "leds.h"
static uint8_t gHue = 0; 
#define FRAMES_PER_SECOND  120

bool animateSlaveBreath_loop() {
  const int bpm = 50;
  CRGB color = CHSV(120, 193, beatsin8(bpm, 0, 255));
  for (auto i = 0; i < FastLED.size(); i++) {
    leds[i] = color;
  }

  FastLED.show();
  return true;
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void rainbow() 
{
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void confetti_loop() 
{
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}


void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}