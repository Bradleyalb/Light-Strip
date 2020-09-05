const int buzzer = 3; 
const int sensor = 4;
int state;
int reading; // 0 close - 1 open wwitch
#include <FastLED.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14

#define CLOSED 0
#define OPENING 1
#define OPEN 2

#define NUM_LEDS 300
#define NUM_LIGHTS 20
int k;
int i;
bool inc;
CRGB leds[NUM_LEDS];
CRGB color_array[158];
void setup()
{
  Serial.begin(115200);
  pinMode(sensor, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
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

void loop()
{
  reading = digitalRead(sensor);
  //Serial.println(state);
  switch(state){
    case CLOSED:
      if (reading == HIGH){
        state = OPENING;
        i = 1;
        inc = true;
      }
    break;
    case OPENING:
    Serial.print(i);
    Serial.println(inc);
      if (inc){
        leds[i] = color_array[i];
        i += 1;
        if (i == NUM_LEDS){
          inc = false;
        }
      }
      else{
        leds[i] = CRGB(0,0,0);
        i -= 1;
      }
      if (i == 0){
        leds[0] = CRGB(0,0,0);
        state = OPEN;
      }
    break;
    case OPEN:
      if (reading !=HIGH){
        state = CLOSED;
      }
    break;
  }

  FastLED.show();
  delay(2);
}
