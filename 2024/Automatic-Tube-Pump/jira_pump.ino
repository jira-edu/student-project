#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define TRIG_PIN 11
#define ECHO_PIN 12

long duration;
float distance;


float alpha = 0.7;  // ค่าคงที่สำหรับ EMA (0.1 = ความไวต่ำ, 0.9 = ความไวสูง)
float smoothedDistance = 0;

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String inputString = "";
bool inputComplete =false;
float set;
float oil;
float liter;
float volume;

float getWaterLevel() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.0344 / 2.0;
    smoothedDistance = alpha * distance + (1 - alpha) * smoothedDistance;
}
float getWaterVolume() {
    getWaterLevel();
//    return ((smoothedDistance-3.0)/(19.0-3.0)) * (3.5-0) + 0;
    int p = map(smoothedDistance, 3, 19, 100, 0);
    return (p/100.0)*3.50;
//    return map(smoothedDistance, 3.0, 19.0, 100, 0);
}



void setup() {
      pinMode(10, OUTPUT);
      digitalWrite(10, HIGH);
      pinMode(TRIG_PIN, OUTPUT);
      pinMode(ECHO_PIN, INPUT);
      display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
      display.clearDisplay(); // clears the screen and buffer
      display.drawPixel(127, 63, WHITE);
      display.display();
      Serial.begin(9600);
}
 
void loop() {
    volume = getWaterVolume();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(volume);
    display.println(smoothedDistance);
    display.display();
    delay(10);
  char key = keypad.getKey();
  
 if (key == 'C') {
     display.clearDisplay();
     display.setTextSize(2);
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     display.println("set ");
     display.display();

     while (1) {
      char key = keypad.getKey();
      if (key){
        if (key == '#'){
          
          inputComplete =true;
         }else if (key == '*'){
          inputString += '.' ;
         }
         else {
          inputString += key;
         }
         display.clearDisplay();
         display.setCursor(0,0);
         display.println("set ");
         display.print(inputString);
         display.display();
      }
       if (inputComplete) {
        set = inputString.toFloat();
        inputString = "";
        inputComplete = false;
        display.clearDisplay();
        display.display();
        break;
       }
     }
     
  }else if (key == 'A') {
     display.clearDisplay();
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     display.println("How much do you want?");
     display.display();
     while (1) {
      char key = keypad.getKey();
      if (key){
        if (key == '#'){
          
          inputComplete =true;
         }else if (key == '*'){
          inputString += '.' ;
         }
         else {
          inputString += key;
         }
         display.clearDisplay();
         display.setCursor(0,0);
         display.println("How much do you want?");
         display.print(inputString);
         display.display();
      }
       if (inputComplete) {
        oil = inputString.toFloat();
        inputString = "";
        inputComplete = false;
        display.clearDisplay();
        display.display();
        break;
       }
     } 
     liter = oil/set;
     display.print(liter);
     display.println(" L");
     display.display();
     delay (1000);

     getWaterVolume();
     delay(100);
     getWaterVolume();
     delay(100);
     getWaterVolume();
     delay(100);
     float a = getWaterVolume();
     delay(100);
     if (liter > a) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Oil not enough");
     } else {
        getWaterVolume();
        delay(100);
        getWaterVolume();
        delay(100);
        getWaterVolume();
        delay(100);
        float b = getWaterVolume() - liter;
        delay(100);
        float current = 0;
        while (getWaterVolume()> b){
          delay(100);
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0,0);
          current = getWaterVolume();
          display.println(a - current);
          digitalWrite(10, LOW);  
          delay(100);
          if (current <= 0) {
            digitalWrite(10, HIGH);
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("Tank Empty !");
          }
          display.display();
        }
        digitalWrite(10, HIGH);
        delay(1000); 
     }
     
     
  }
  delay(100);
}
