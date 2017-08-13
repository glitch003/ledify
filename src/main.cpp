#include <FastLED.h>
#include "fire.h"
#include "leds.h"
#include "cylon.h"
#include "misc_animations.h"
#include <assert.h>

CRGB leds[NUM_LEDS];

void setup() {
  #ifndef PROTRINKET5
  #endif
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}


void fadeToBlack() {
  for (int i = 0; i < 30; i++) {
   for(int j = 0; j < NUM_LEDS; j++) {
      leds[j].fadeToBlackBy(32);
   }
    FastLED.show();
    FastLED.delay(20);
  }

}

typedef void (*animation_t)();

struct AnimationEntry {
 animation_t func;
 uint32_t duration;
};

const long DEFAULT_DURATION = 1000L * 120L;
AnimationEntry animations[] = {
  {
    confetti_loop,
    DEFAULT_DURATION,
  },
  {
    Cylon_loop,
    DEFAULT_DURATION
  },
  {
    juggle,
    DEFAULT_DURATION,
  },
  {
    rainbowWithGlitter,
    DEFAULT_DURATION,
  },
};

const int ANIMATION_COUNT  = sizeof(animations) / sizeof(animations[0]);
static_assert(ANIMATION_COUNT > 1, "should have more than one animation!");
static_assert(ANIMATION_COUNT < 100, "Something might be wrong here");

void loop()
{
  static int currentAnimationIndex = 0;
  static uint32_t animationStartTime = 0;
  uint32_t now = millis();
  auto anim = animations[currentAnimationIndex];

  if (now - animationStartTime > anim.duration) {
    fadeToBlack();
    currentAnimationIndex = (currentAnimationIndex + 1) % ANIMATION_COUNT;
    animationStartTime = now;
  } else {
    anim.func();
  }
  // Add entropy to random number generator; we use a lot of it.
  // random16_add_entropy( random());

}
