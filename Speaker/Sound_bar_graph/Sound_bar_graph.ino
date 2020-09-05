#include <FastLED.h>
//#include <color_tables.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14 
#define RED 0
#define GREEN 1
#define BLUE 2
#define NEXT 800

//Parameters that can be changed
#define NUM_LEDS 300
#define NUM_LIGHTS 300
#define BOUNCING true


CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];

uint8_t state;
int16_t reading;
int16_t max_r;
int16_t current;
int timer;
int k;
int k_i;
int active_lights;
int max_led = NUM_LEDS-1;
int wait;
int max_l;
class Light{
  public:
  int id;
  CRGB color;
  int adress;
  int interval = 10;
  bool stop = false;
  void inc_pixel(Light lights[]){
    if (!stop){  
      leds[adress] = CRGB(0,0,0);
      adress++;
      if (adress == max_led){
        stop = true;
        max_led--;
      }
      leds[adress] = color;
    }
  }
};

Light lights[NUM_LIGHTS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
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
}

//mid: 2048
//max: 4096
void loop() {
  reading = analogRead(A4);
  //Serial.println(reading);
  if (max_l >= 0 && timer % 65 == 0){
    leds[max_l] = CRGB(0,0,0);
    max_l--;
  }
  if (timer % 200 == 0){
    FastLED.show();
  }
  if (reading > max_r){
    max_r = reading;
  }
  if (timer % 1000 == 0){
    current = max(0,max_r-1900);
    k_i = (current/2048.0)*650;//*600
    k_i = min(299,k_i);//299
    Serial.println(k_i);
    if (k_i > max_l){
     max_l = k_i; 
    }
    for (int i = 0; i < k_i; i++){
      leds[i] = CHSV(i*2,255,255);
    }
    //fill_solid(leds, k_i, CHSV(hue,255,255));
    FastLED.show();
    max_r = 0;
  }  
  timer++;
}
