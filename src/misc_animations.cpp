#include <FastLED.h>
#include "leds.h"
static uint8_t gHue = 0; 

#define FRAMES_PER_SECOND  120

void breath_loop() {
  const int bpm = 40;
  CRGB color = CHSV(beatsin8(bpm/4, 0, 255), 193, beatsin8(bpm, 0, 255));
  for (auto i = 0; i < FastLED.size(); i++) {
    leds[i] = color;
  }

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void rainbow_loop() 
{
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
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