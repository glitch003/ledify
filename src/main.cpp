#include <FastLED.h>
#include "fire.h"
#include "leds.h"
#include "cylon.h"
#include "misc_animations.h"
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

AnimationEntry animations[] = {
  // {
  //   rainbowWithGlitter,
  //   1000L * 120L,
  // },
  {
    confetti_loop,
    1000L * 120L,
  },
  {
    Cylon_loop,
    1000L * 120L
  },
  {
    juggle,
    1000L * 60L * 5L,
  },
};

#define ANIMATION_COUNT 3
// sizeof(animations) / sizeof(AnimationEntry);

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
