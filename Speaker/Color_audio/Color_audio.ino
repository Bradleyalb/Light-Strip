#include <FastLED.h>
//#include <color_tables.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 25 
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
  FastLED.setBrightness(5);
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
  if (reading > max_r){
    max_r = reading;
  }
  if (timer % 2000 == 0){
    Serial.println(max_r);
    current = max(0,max_r-1600);
    Serial.println(current);
    k_i = (current/2048.0)*250;
    Serial.println(k_i);
    fill_solid(leds, NUM_LEDS, color_array[k_i]);
    FastLED.show();
    max_r = 0;
  }  
  timer++;
}
