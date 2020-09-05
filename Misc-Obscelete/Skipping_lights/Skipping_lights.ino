#include <FastLED.h>

#define NUM_LEDS 300
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB //Might need to change to GRB
#define DATA_PIN 25 //Also up to change

CRGB leds[NUM_LEDS];
int pi = 0;
int color = 0;
int s = 100;
bool forward = true;
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(130);
}

void loop() {
  // put your main code here, to run repeatedly:
  leds[pi] = CRGB(0,0,0);
  leds[pi] = CRGB(255,255,255);
  for (int i = 0; i<256; i+=5){
    leds[pi] = CRGB(i,255-i,0);
    FastLED.show();
    delay(s);
    leds[pi] = CRGB(0,0,0);
    inc_pixel();
  }
  for (int i = 0; i<256; i+=5){
    leds[pi] = CRGB(255-i,0,i);
    FastLED.show();
    delay(s);
    leds[pi] = CRGB(0,0,0);
    inc_pixel();
  }
  for (int i = 0; i<256; i+=5){
    leds[pi] = CRGB(0,i,255-i);
    FastLED.show();
    delay(s);
    leds[pi] = CRGB(0,0,0);
    inc_pixel();
  }
//  inc_pixel();
//  leds[pi] = CRGB(255,0,0);
  FastLED.show();
}

void inc_pixel(){
  if (forward){
    pi+=5;
    if (pi >= NUM_LEDS){
      pi = 255;
      forward = false;
    }
  }
  else{
    pi-=5;
    if (pi <= 0){
      pi = 0;
      forward = true;
    }
  }
  
}
