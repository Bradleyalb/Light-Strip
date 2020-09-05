#include <FastLED.h>
//#include <color_tables.h>

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
#define NUM_LIGHTS 20
#define Bouncing true
#define NEXT 5


CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
uint8_t state;
int timer = 1;
int k;
int j;
int active_lights;

class Light{
  public:
  int id;
  int color;
  int adress;
  int interval;
  int b = 1;
  int max_b = 10;
  bool inc = true;
  bool act = false;
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
      if (Bouncing && check_colide(lights)){
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
  void ran_pixel(){
    if (act){
      if (inc){
        b++;
        if (b == max_b){
          inc = false;
        }
      }
      else{
        b--;
        if (b == 0){
          inc = true;
          act = false;
        }
      } 
    leds[adress] = CRGB(3*b,2*b,b);
    }
  }
};

Light lights[NUM_LEDS]; 

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
  pinMode(26, OUTPUT);
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
     lights[i].adress = 10*i;
     lights[i].color = 20*j;
     lights[i].interval = 2;
     lights[i].id = i;
  }
}

void loop() {
  switch(state){
    case BOUNCING:
    for (int i = 0; i < NUM_LIGHTS; i++){
      lights[i].inc_pixel(lights);
    }
    if (timer % 1000 == 0){
      state = RANDOM;  
      for (int i = 0; i < NUM_LEDS; i++){
        lights[i].adress = i;
      }
      FastLED.setBrightness(255);
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    }
    break;
    case RANDOM:
    for (int i = 0; i < NUM_LEDS; i++){
      lights[i].ran_pixel();
    }
    if (timer % NEXT == 0){
      for (int i = 0; i < NUM_LIGHTS; i++){
        int ran = random16(NUM_LEDS);
        lights[ran].act = true;
        lights[ran].color = color_array[random16(156)];
      }
    }
    if (timer % 100 == 0){
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      state = BOUNCING;  
      FastLED.setBrightness(5);
      lights = Light lights[NUM_LEDS];
      //Light lights[NUM_LEDS]; 
      for (int i = 0; i < NUM_LIGHTS; i++){
         j+=1;
         j%=7;
         lights[i].adress = 9*i;
         lights[i].color = 20*j;
         lights[i].interval = 3;
         lights[i].id = i;
      }  
      
    }
    //delay(10);
    delay(45);
    break;
    case STOP_LIGHTS:
    Serial.println("STOP");
    if (timer % NEXT == 0 && active_lights < NUM_LIGHTS){
      lights[active_lights].color = colors[active_lights%7];
      active_lights++;
    }
    for (int i = 0; i < active_lights; i++){
      lights[i].inc_pixel(lights);
    }
    if (timer %= 10000){
      state = BOUNCING;
      FastLED.setBrightness(5);
      //Light lights[NUM_LEDS]; 
      for (int i = 0; i < NUM_LIGHTS; i++){
         j+=1;
         j%=7;
         lights[i].adress = 9*i;
         lights[i].color = 20*j;
         lights[i].interval = 3;
         lights[i].id = i;
      }  
    }
    break;
  }
  timer++;
  FastLED.show();
  delay(1);
}
