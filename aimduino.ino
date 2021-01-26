#include <Mouse.h>
#include <math.h>
#define SERIAL_MSG_SIZE 16
#define TOKEN_LENGTH 64
#define TOKEN_TABLE 2.f
#define TOKEN_SHOOT 1.f
#define TOKEN_STOP 0.f
#define ELEMENTCOUNT(x)  (sizeof(x) / sizeof(x[0]))
float* x = 0;
float* y = 0;
float timeout;
int capacity = 0;
long currTimeout;
bool shoot = false;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  Mouse.begin();
}
void mouseMove(long x, long y) {
  long max = max(abs(x), abs(y));
  int count = (int) (max / 127);
  signed char diffX = x / (count + 1);
  signed char diffY = y / (count + 1);
  for (int i = 0; i < count; i++) {
    Mouse.move(diffX, diffY);
  }
  signed char resX = x - (diffX * count);
  signed char resY = y - (diffY * count);
  if (resX != 0 || resY != 0) {
    Mouse.move(resX, resY);
  }
}
unsigned int idx = 0;
unsigned long lastMillis = 0;
void loop() {
  if(Serial.available() >= SERIAL_MSG_SIZE){
    String serial_string = Serial.readString();
    char* sptr = (char*) serial_string.c_str();
    char* token;
    float tokens[TOKEN_LENGTH];
    int index = 0;
    while((token = strtok_r(sptr, ",", &sptr))){
      if(index < TOKEN_LENGTH){
        tokens[index++] = atof(token);
      }
    }
    if(tokens[0] == TOKEN_SHOOT){
      shoot = true;
    }
    if(tokens[0] == TOKEN_STOP){
      shoot = false;
    }
    if(tokens[0] == TOKEN_TABLE){
      lastMillis = millis();
      delete[] x;
      delete[] y;
      capacity = tokens[2];
      x = new float[capacity];
      y = new float[capacity];
      timeout = tokens[1];
      int idx = 0;
      int idy = 0;
      for(int i = 3; i < capacity * 2; i++){
        if(i % 2 ){
          x[idx++] = tokens[i];
        }else {
          y[idy++] = tokens[i];
        }
      }
      for(int i = 0; i < capacity; i ++){
        Serial.print(x[i]);
        Serial.print(",");
        Serial.print(y[i]);
        Serial.print("\n");
      }
    }
    Serial.flush();
  }
  if(shoot){
    if((millis() - lastMillis) >= timeout && capacity != idx){
      mouseMove(x[idx], y[idx]);
      idx++;
      lastMillis = millis();
    }
  }else{
    idx = 0;
  }
}
