const int buzzer = 3; 
const int sensor = 4;

int state; // 0 close - 1 open wwitch

void setup()
{
  Serial.begin(115200);
  pinMode(sensor, INPUT_PULLUP);
}

void loop()
{
  state = digitalRead(sensor);
  
  if (state == HIGH){
    Serial.println(1);
    //tone(buzzer, 400);
  }
  else{
    Serial.println(0);
    //noTone(buzzer);
  }
  delay(200);
}
