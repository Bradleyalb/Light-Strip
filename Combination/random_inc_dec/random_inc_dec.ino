#include <FastLED.h>

#define NUM_LEDS 300
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB //Might need to change to GRB
#define DATA_PIN 14 //Also up to change
#define RED 0
#define GREEN 1
#define BLUE 2

//Slow mood lighs
//#define NUM_LIGHTS 12
//#define INTERVAL 6
//#define DELAY 45
//#define MAX_B 255

//glitter
#define NUM_LIGHTS 15
#define INTERVAL 3
#define DELAY 5
#define MAX_B 10

//Middle value
//#define NUM_LIGHTS 5
//#define INTERVAL 1
//#define DELAY 30
//#define MAX_B 15

CRGB leds[NUM_LEDS];
CRGB color_array[156];
int timer = 0;
int color = 0;
int colors[10][3];
int next = INTERVAL;

class Light{
  public:
  bool act;
  bool inc = true;
  int adress;
  int brightness = 1;
  int max_b = MAX_B;
  void inc_pixel(){
    if (act){
      if (inc){
        brightness++;
        if (brightness == max_b){
          inc = false;
        }
      }
      else{
        brightness--;
        if (brightness == 0){
          inc = true;
          act = false;
        }
      } 
    leds[adress] = CRGB(1*brightness,1*brightness,1*brightness);
    }
  }
};
Light lights[NUM_LEDS]; 
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  for (int i = 0; i < NUM_LEDS; i++){
    lights[i].adress = i;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    lights[i].inc_pixel();
  }
  FastLED.show();
  if (timer % next == 0){
    for (int i = 0; i < NUM_LIGHTS; i++){
      lights[random16(NUM_LEDS)].act = true;
    }
  }
  timer++;
  delay(DELAY);
}
