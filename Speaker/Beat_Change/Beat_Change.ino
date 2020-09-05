#include <FastLED.h>
//#include <color_tables.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14
#define RED 0
#define GREEN 1
#define BLUE 2

//Parameters that can be changed
#define NUM_LEDS 300
#define NUM_LIGHTS 10
#define MAX_LEDS
#define BOUNCING false
#define JUMP 2

CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
uint8_t state;
uint16_t reading;
int timer;
int k;
int thresh = 2500;
bool forward = true;

class Light{
  public:
  int id;
  int color = 0;
  int adress;
  int interval;
  void inc_pixel(Light lights[]){
    leds[adress] = CRGB(0,0,0);
    if (forward){
      adress+=JUMP;
      adress %= NUM_LEDS;
      leds[adress] = color_array[color];
    }
    else{
      adress-=JUMP;
      if (adress < 0){
        adress = NUM_LEDS-1;
      }
      leds[adress] = color_array[color];
    }
    color++;
    color%=156;
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
  colors[0] = CRGB(0,0,255);
  colors[1] = CRGB(255,0,255);
  colors[2] = CRGB(0,255,0);
  colors[3] = CRGB(255,0,0);
  colors[4] = CRGB(255,255,0);
  colors[5] = CRGB(0,128,128);
  colors[6] = CRGB(255,255,255);
  for (int i = 0; i < NUM_LIGHTS; i++){
     j+=1;
     j%=156;
     lights[i].adress = 3*i;
     lights[i].interval = 2;
     lights[i].id = i;
  }
  Serial.println(1);
}

void loop() {
  reading = analogRead(A4);
  for (int i = 0; i < NUM_LIGHTS; i++){
    lights[i].inc_pixel(lights);
  }
  if (reading > thresh){
    forward = !forward;
  }
  FastLED.show();
  timer++;
  delay(1);
}
