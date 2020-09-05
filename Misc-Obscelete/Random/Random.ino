#include <FastLED.h>

#define NUM_LEDS 300
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB //Might need to change to GRB
#define DATA_PIN 25 //Also up to change
#define RED 0
#define GREEN 1
#define BLUE 2
#define NUM_LIGHTS 35
#define INTERVAL 4
#define DELAY 100


CRGB leds[NUM_LEDS];
CRGB color_array[156];
int timer = 0;
int color = 0;
int jump = 1;
int dly = 10;
int i = 0;
int p1 = 0;
int p2 = 20;
int space = 2;
int colors[10][3];
int next = INTERVAL;

class Light{
  public:
  int adress;
  int brightness = 0;
  void dec_pixel(){
      if (brightness > 0){
//        Serial.println("HHHHHHHHHHHHHHHHHHHHHHH");
//        Serial.println(brightness);
        brightness--;
        leds[adress] = CRGB(3*brightness,2*brightness,brightness);
      }
    }
};

uint8_t state;
Light lights[NUM_LEDS]; 
int val;
int k;
int LA[NUM_LIGHTS];
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
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
  for (int i = 0; i < NUM_LEDS; i++){
    lights[i].adress = i;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    lights[i].dec_pixel();
  }
  if (timer % next == 0){
    for (int i = 0; i < NUM_LIGHTS; i++){
      lights[random16(NUM_LEDS)].brightness = 10;
    }
  }
  FastLED.show();
  timer++;
  delay(DELAY);
}
