const int RED =  0;
const int GREEN =  1;
const int sensor = 4; //4 A2
const int esp_in = 2;
const int esp_out = 3;

boolean red_enable = false;
boolean green_enable = true;

unsigned long preMillis_Green = 0;
const long interval_Green = 1000;
unsigned long preMillis_Red = 0;
const long interval_Red = 50;

unsigned long preMillis_blink = 0;

int timeToblink = 5 * 1000; // 1 * 60000 = 60 second or 1 minute

boolean stateGyro;
boolean readGyro() {
  if (analogRead(sensor) < 650) {
    stateGyro = 0;
  } else {
    stateGyro = 1;
  }
  return stateGyro;
}

void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(esp_in, INPUT_PULLUP);
  pinMode(esp_out, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  unsigned long curMillis = millis();

  if (green_enable) {
    if (curMillis - preMillis_Green >= interval_Green) {
      preMillis_Green = curMillis;
      digitalWrite(GREEN, !digitalRead(GREEN));
      digitalWrite(esp_out, LOW);
    }
  } else if (red_enable) {
    if (curMillis - preMillis_Red >= interval_Red) {
      preMillis_Red = curMillis;
      digitalWrite(RED, !digitalRead(RED));
      digitalWrite(esp_out, HIGH);
    }
    if (curMillis - preMillis_blink >= timeToblink ) {
      preMillis_blink = curMillis;
      red_enable = false;
      green_enable = true;
      digitalWrite(RED, 0);
      digitalWrite(esp_out, LOW);
    }
  }

  //  digitalWrite(esp_out, LOW);
  //  boolean reading = readGyro();
  //    if (digitalRead(esp_in) == LOW && red_enable == false || reading == LOW && red_enable == false) {
  boolean reading = digitalRead(sensor);
  //  if (reading == LOW && red_enable == false) {
  if (digitalRead(esp_in) == LOW && red_enable == false || reading == LOW && red_enable == false) {
    //  if (digitalRead(esp_in) == LOW && red_enable == false ) {
    red_enable = true;
    green_enable = false;
    digitalWrite(GREEN, 0);
    digitalWrite(esp_out, HIGH);
  }
}
