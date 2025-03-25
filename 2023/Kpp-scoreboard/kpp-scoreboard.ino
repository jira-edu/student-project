
#include "score_lib.h"

Scorelib scorelib(3,4,5,10,11,12,13);

bool num[14][23] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},  // 0
  {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},  // 1
  {1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1},  // 2
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1},  // 3
  {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},  // 4
  {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},  // 5
  {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  // 6
  {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},  // 7
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  // 8
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},   // 9
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

bool period[11][35] = {
  // {1,1,1,1,1,1,7,1,1,1,1,1,1,14,1,1,1,1,1,1,21,1,1,1,1,1,1,28,1,1,1,1,1,1}
  {0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,0.0}, // 0
  {0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, // 1
  {0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,1,0,1,0,1,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0}, // 2
  {0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0}, // 3
  {0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}, // 4
  {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0}, // 5
  {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0}, // 6
  {0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0}, // 7
  {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0}, // 8
  {0,1,1,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0},  // 9
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX

int a_score = 0;
int a_score_buff = 0;
int b_score = 0;
int b_score_buff = 0;
int c_score = 0;
int c_score_buff = 0;
int min=0;
int sec=0;
int min_buff;

char bt;
int x;
int y;

volatile uint32_t counter=0;
bool start=0;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(2, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, 0);
  attachInterrupt(digitalPinToInterrupt(2), count, RISING);
}

void loop() {
  if (mySerial.available()) {
    bt=(mySerial.read());
    switch (bt) {
    case '1':
      if(a_score<99){
        a_score++;
      }
      break;
    case '0':
      if(a_score>0){
        a_score--;
      }
      break;
    case '2':
      if(b_score<99){
        b_score++;
      }
      break;
    case '3':
      if(b_score>0){
        b_score--;
      }
      break;
    case '6':
      if(c_score<9){
        c_score++;
      }
      break;
    case '5':
      if(c_score>0){
        c_score--;
      }
      break;
    case '4':
      a_score=0;
      b_score=0;
      break;
    case '7':
      if(min<94){
        min+=5;
      }
      break;
    case '8':
      if(min<89){
        min+=10;
      }
      break;
    case '9':
      if(min<69){
        min+=30;
      }
      break;
    case 'a':
      start=1;
      break;
    case 'b':
      start=0;
      break; 
    case 'c':
      min=0;
      sec=0;
      start=0;
      break; 
    }
    Serial.println(a_score);

    a_score_buff=a_score;
    x=0;
    y=0;
    if(a_score_buff<100){
      while(a_score_buff>=10){
        a_score_buff=a_score_buff-10;
        x=x+1;
      } 
      while(a_score_buff>=1){
        a_score_buff=a_score_buff-1;
        y=y+1;
      }
    }
    
    scorelib.display_number(5, num[x]);
    scorelib.display_number(6, num[y]);  
    
    Serial.println(b_score);
    b_score_buff=b_score;
    x=0;
    y=0;
    if(b_score_buff<100){
      while(b_score_buff>=10){
        b_score_buff=b_score_buff-10;
        x=x+1;
      } 
      while(b_score_buff>=1){
        b_score_buff=b_score_buff-1;
        y=y+1;
      }
    }
    scorelib.display_number(7, num[x]);
    scorelib.display_number(8, num[y]);  

  }

  

  min_buff=min;
  x=0;
  y=0;
  if(min_buff<100){
    while(min_buff>=10){
      min_buff=min_buff-10;
      x=x+1;
    } 
    while(min_buff>=1){
      min_buff=min_buff-1;
      y=y+1;
    }
  }
  scorelib.display_number(1, num[x]);
  scorelib.display_number(2, num[y]);

  min_buff=sec;
  x=0;
  y=0;
  if(min_buff<100){
    while(min_buff>=10){
      min_buff=min_buff-10;
      x=x+1;
    } 
    while(min_buff>=1){
      min_buff=min_buff-1;
      y=y+1;
    }
  }
  scorelib.display_number(3, num[x]);
  scorelib.display_number(4, num[y]);

  Serial.println(min);
  Serial.println(sec);

  scorelib.display_period(period[c_score]);


  if((start==1)&&(min==0)&&(sec==0)){
    digitalWrite(6,1);
    start=0;
    delay(2000);
  }else{
    digitalWrite(6,0);
  }
}

void count() {
  if(counter<32768){
    counter++;
  }else{
    counter=0;
    if(((min>0)||(sec>0))&&(start==1)){
      if(sec>0){
        sec-=1;
      } else{
        if(min>0){
          min-=1;
          sec=59;
        }
      }
    }
  }
}

