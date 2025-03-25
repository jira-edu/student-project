#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial mp3(6,7); //-> SoftwareSerial mp3 (RX_Pin, TX_Pin);

#include "player.h"
Player player;

#include <Wire.h>
#include <DS3231.h>
DS3231 myRTC;
bool century = false;
bool h12Flag;
bool pmFlag;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void(* resetFunc) (void) = 0;//declare reset function at address 0

int h=0;
int m=0;
int sec = 0;
int wd=0;
bool sw=1;
bool sw_bp;
bool last_state = false;
int y=0;
int mo=0;
int d=0;

void setup() {
  Serial.begin(9600);
  player.init();
  Wire.begin();
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,OUTPUT);
  digitalWrite(4,1);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("Autoplayer"); //พิมพ์ข้อความ
  lcd.setCursor(2, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 2 บรรทัดที่ 1
  lcd.print("Elec KPPoly");
  delay(3000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
 
 
  h=myRTC.getHour(h12Flag, pmFlag); //24-hr
  m=myRTC.getMinute();
  sec = myRTC.getSecond();
  wd=myRTC.getDoW();
  d=myRTC.getDate();
  mo=myRTC.getMonth(century);
  y=myRTC.getYear();
  sw= digitalRead(2);
  sw_bp = digitalRead(3);
  if(((h==7)&&(m==45)&&(wd>=2 && wd<=6))||(sw==0)) {
     digitalWrite(4,0);
      player.playsound();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("March KPP");
      
    // delay(5000);
    delay(240000);
    resetFunc();
    digitalWrite(4,1);
  }

  if (sw_bp == 0) {
    digitalWrite(4, 0);
    last_state = true;
    delay(100);
  } else {
    if (last_state == true) {
      last_state = false;
      resetFunc();
      digitalWrite(4, 1);
      delay(100);
    }
  }

  lcd.setCursor(0, 0);
   if(h<10){
   lcd.print("0");
  }
   lcd.print(h);
   if ((sec % 2) == 0) {
      lcd.print(":");
   } else {
      lcd.print(" ");
   }

   if(m<10){
   lcd.print("0");
  }
   lcd.print(m);
   lcd.print("  ");
   if(d<10){
   lcd.print("0");
  }
   lcd.print(d);
   lcd.print("/");
   if(mo<10){
   lcd.print("0");
  }
   lcd.print(mo);
   lcd.print("/");
   if(y<10){
   lcd.print("0");
  }
   lcd.print(y);
  // while (player.respond() != "Completed") {
  //   delay(10);
  // }

  // Serial.println("Played");
  delay(100);

}
