#include <FastLED.h>
//#include <color_tables.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14
#define RED 0
#define GREEN 1
#define BLUE 2

//Parameters that can be changed
#define NUM_LEDS 25
#define NUM_LIGHTS 4
#define BOUNCING true


CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
uint8_t state;
int timer;
int k;

class Light{
  public:
  int id;
  int color;
  int adress;
  int interval;
  bool forward = true;
  bool check_colide(Light lights[]){
    for (int i = 0; i < NUM_LIGHTS; i++){
      if (abs(lights[i].adress-adress)<2 && lights[i].id != id){
        lights[i].forward = !lights[i].forward;
        return true;
      }
    }
    return false;
  }
  void inc_pixel(Light lights[]){
    if (timer % interval == 0){
      if (BOUNCING && check_colide(lights)){
        forward = !forward;
      }
      leds[adress] = CRGB(0,0,0);
      if (forward){
        adress++;
        if (adress == NUM_LEDS-1){
          forward = false;
        }
      }
      else{
        adress--;
        if (adress == 0){
          forward = true;
        }
      }
      leds[adress] = color_array[color];
      color++;
      color%=153;
    }
  }
};

Light lights[NUM_LIGHTS]; 

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
  pinMode(26, OUTPUT);
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
     j%=7;
     lights[i].adress = 4*i;
     lights[i].color = 20*j;
     lights[i].interval = 30;
     lights[i].id = i;
  }
  Serial.print("hi");
}

void loop() {
  for (int i = 0; i < NUM_LIGHTS; i++){
    lights[i].inc_pixel(lights);
  }
  FastLED.show();
  timer++;
  delay(1);
}
