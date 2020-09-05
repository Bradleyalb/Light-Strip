#include <FastLED.h>

#define NUM_LEDS 300
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB //Might need to change to GRB
#define DATA_PIN 25 //Also up to change

CRGB leds[NUM_LEDS];
int pi = 0;
int color = 0;
int s = 100;
int timer;
int turn;
bool forward = true;
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (timer % 5000 == 0){
    if (turn == 0){
      Serial.print("0");
      fill_solid(leds, NUM_LEDS, CRGB(3,0,0));
      FastLED.show();
      turn = 1;
    }
    else if (turn == 1){
      Serial.print("1");
      fill_solid(leds, NUM_LEDS, CRGB(2,2,2));
      FastLED.show();
      turn = 0;
    }
    else if (turn == 2){
      Serial.print("2");
      fill_solid(leds, NUM_LEDS, CRGB(0,0,128));
      FastLED.show();
      turn = 0;
    }
  }
  timer++;
  delay(1);
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
