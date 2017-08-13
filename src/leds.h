#pragma once
#include <FastLED.h>

#ifdef PROTRINKET5
#define LED_PIN     3
#else
#define LED_PIN     7
#endif

#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    100

#define BRIGHTNESS  200


extern CRGB leds[NUM_LEDS];
