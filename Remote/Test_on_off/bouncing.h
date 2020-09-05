//class Light{
//  public:
//  int id;
//  int color;
//  int adress;
//  int interval;
//  bool forward = true;
//  bool check_colide(Light lights[]){
//    for (int i = 0; i < NUM_LIGHTS; i++){
//      if (abs(lights[i].adress-adress)<2 && lights[i].id != id){
//        lights[i].forward = !lights[i].forward;
//        return true;
//      }
//    }
//    return false;
//  }
//  void inc_pixel(Light lights[]){
//    if (timer % interval == 0){
//      if (BOUNCING && check_colide(lights)){
//        forward = !forward;
//      }
//      leds[adress] = CRGB(0,0,0);
//      if (forward){
//        adress++;
//        if (adress == NUM_LEDS-1){
//          forward = false;
//        }
//      }
//      else{
//        adress--;
//        if (adress == 0){
//          forward = true;
//        }
//      }
//      leds[adress] = color_array[color];
//      color++;
//      color%=153;
//    }
//  }
//};
//Light lights[NUM_LIGHTS]; 
