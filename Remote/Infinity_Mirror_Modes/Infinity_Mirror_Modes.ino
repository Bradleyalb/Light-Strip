#include <IRremoteESP8266.h>
#include <IRrecv.h> 
#include <FastLED.h>
int RECV_PIN = 4;
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB 
#define DATA_PIN 14
#define RED 0
#define GREEN 1
#define BLUE 2
#define OFF 0
#define BI 1
#define RID 2
#define CC 3


//Parameters that can be changed
#define NUM_LEDS 300
#define NUM_LIGHTS 5
#define Bouncing true
#define NEXT 5
#define DELAY 7
#define MAX_B 15
#define INTERVAL 2

IRrecv irrecv(RECV_PIN);

decode_results results;
int cb=50;
bool on;
int timer;
int k;
int b;
int repeat;
int state;

CRGB leds[NUM_LEDS];
CRGB color_array[158];
CRGB colors[10];
int max_b = MAX_B;
class Light{
  public:
  int red;
  int green;
  int blue;
  int hue;
  bool act;
  bool inc = true;
  int adress;
  int brightness = 1;
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
    //Serial.print(hue);
    leds[adress] = CHSV(hue,255,brightness*6);
    }
  }
};
Light lights[NUM_LEDS]; 
void setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  Serial.println("AAAAAAAAAAAA");
  irrecv.enableIRIn();
  for (int i = 0; i < NUM_LEDS; i++){
    lights[i].adress = i;
  }
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

void restart() {
  // put your setup code here, to run once:
  FastLED.setBrightness(255);
  Light lights[NUM_LEDS]; 
  k = 0;
  b = 0;
}

void loop() {
  FastLED.show();
  if (irrecv.decode(&results)) {
    uint16_t val = results.value;
    if (val == 0x30CF){
      restart();
      state = BI;
    }
    if (val == 0x18E7){
      restart();
      state = RID;
    }
    if (val == 0x7A85){
      restart();
      state = CC;
    }
    if (val  == 0x6897){
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      state = OFF;
    }
    Serial.println(val,HEX);
    irrecv.resume(); // Receive the next value
  }
  if (state == BI){
    b+=ceil(log(b+2));
    b%=255;
    fill_solid(leds, NUM_LEDS, CRGB(b,0,b));
    delay(60);
  }
  else if(state == RID){
     uint16_t val = results.value;
     if (val == 0xE01F){
        max_b--;
     }
     if (val == 0xA857){
        max_b++;
     }
     for (int i = 0; i < NUM_LEDS; i++){
      lights[i].inc_pixel();
     }
     if (timer % INTERVAL == 0){
       for (int i = 0; i < NUM_LIGHTS; i++){
         int randint = random16(NUM_LEDS);
         lights[randint].act = true;
         lights[randint].hue = k;
       }
     }
     repeat++;
     repeat%=10;
     if (repeat == 0){
        Serial.println(k);
        k+=1;
        k%=255;
     }
     delay(DELAY);
  }
  else if(state == CC){
    uint16_t val = results.value;
    Serial.print(cb);
     if (val == 0xE01F){
        cb = max(cb-1,0);
     }
     if (val == 0xA857){
        cb = min(cb+1,255);
        Serial.println("hello");
     }
    fill_solid(leds,NUM_LEDS, color_array[k]);
    k+=1;
    k %= 151;
    delay(20);
  }
  //FastLED.show();
  timer++;
  delay(1);
}
