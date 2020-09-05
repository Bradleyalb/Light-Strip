#include <IRremoteESP8266.h>
#include <IRrecv.h> 
#include <FastLED.h>
#include "bouncing.h"
int RECV_PIN = 4; //an IR detector/demodulatord is connected to GPIO pin 2

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14
#define RED 0
#define GREEN 1
#define BLUE 2
#define BOUNCING 0
#define RANDOM 1
#define STOP_LIGHTS 2

//Parameters that can be changed
#define NUM_LEDS 300
#define NUM_LIGHTS 5
#define Bouncing true
#define NEXT 5

bool on;
int timer;
int k;
IRrecv irrecv(RECV_PIN);

decode_results results;

CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
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
void setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("AAAAAAAAAAAA");
}

void start(){
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
  for (int i = 0; i < NUM_LIGHTS; i++){
     j+=1;
     j%=7;
     lights[i].adress = 9*i;
     lights[i].color = 20*j;
     lights[i].interval = 2;
     lights[i].id = i;
  }
}
void loop() {
  if (irrecv.decode(&results)) {
    uint16_t val = results.value;
    if (val == 0x30CF){
      start();
      on = true;
    }
    if (val  == 0x6897){
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      on = false;
    }
    Serial.println(val,HEX);
    irrecv.resume(); // Receive the next value
  }
  if (on){
    for (int i = 0; i < NUM_LIGHTS; i++){
      lights[i].inc_pixel(lights);
    }
  }
  FastLED.show();
  timer++;
  delay(1);
}
