#include <FastLED.h>
//#include <color_tables.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14

//Parameters that can be changed
#define NUM_LEDS 300
#define NUM_LIGHTS 10
#define GROUPING 14
#define JUMP 2

CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
uint8_t state;
uint16_t reading;
int timer;
int wait;
int new_light;
int k;
int max_leds = NUM_LEDS;
int thresh = 2400;
bool forward = true;

void group(int mid, int color){
  leds[mid] = color_array[color];
  for (int i = 1; i < GROUPING; i++){
    if (mid+i < NUM_LEDS){
      leds[mid+i] = color_array[color];
    }
    if (mid-i >= 0){
      leds[mid-i] = color_array[color];
    }
  }
}
class Light{
  public:
  int color;
  int offset = 0;
  int interval = 3;
  int mid_val = NUM_LEDS/2;
  bool on = false;
  void reset(){
    on = true;
    color = 0;
    offset = 0;
  }
  void inc_pixel(Light lights[]){
    if (on){
      if (offset <= mid_val-1 ){
        group(mid_val+offset,color);
        group(mid_val-offset,color);
        offset+=JUMP;
        color+=JUMP;
      }
      else{
        on = false;
      }
    }
  }
};

Light lights[NUM_LIGHTS]; 

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  int j;
  for (int i = 0; i<256; i+=5){
    color_array[k] = CRGB(i,255-i,0);
    k++;
  }
  for (int i = 0; i<256; i+=5){
    color_array[k] = CRGB(255-i,0,i);
    k++;
  }
  for (int i = 0; i<256; i+=5){
    color_array[k] = CRGB(0,i,255-i);
    k++;
  }
}

void loop() {
  reading = analogRead(A4);
  fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
  for (int i = 0; i < NUM_LIGHTS; i++){
    lights[i].inc_pixel(lights);
  }
  if (reading > thresh && wait > 10){
    lights[new_light].reset();
    wait = 0;
    new_light++;
    new_light %= NUM_LIGHTS;
  }
  FastLED.show();
  timer++;
  wait++;
  delayMicroseconds(1000);
}
