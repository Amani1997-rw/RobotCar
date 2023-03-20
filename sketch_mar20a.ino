#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

void u8g_prepare(void) 
{
  u8g.setFont(u8g_font_10x20); // use a larger font size
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void drawDistance() {
  u8g.setFont(u8g_font_10x20);
   u8g.drawStr(50, 20, "ROBOT ");
    u8g.setFont(u8g_font_10x20);
  u8g.drawStr(55, 40, "CAR");
}

#include <AFMotor.h>
// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 9; 
// Create a servo object 

//Ultra sonic sensor'
#define Trig 12
#define Echo 13
long duration;
int distance;

Servo Servo1; 

#define ENA 5
#define ENB 6
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 2;
const int IN4 = 7;

float cm; //Distance variable
float temp; //

//int distance = 100;
void setup() { 
Serial.begin(9600);
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin);
//Ultra sonic setup
 pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

//Serial.begin(9600);
Servo1.write(90); 

 // set the data rate for the SoftwareSerial port


  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

move_stop();

u8g_prepare();
}
void loop(){ 
   digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  temp = float(pulseIn(Echo, HIGH));
//  cm = (temp * 17 ) / 1000;
  cm = temp * 0.034 / 2;
//  Serial.print("Echo =");
//  Serial.print(temp);
//  Serial.print(" | | Distance = ");
//  Serial.print(cm);
//  Serial.println("cm");
   int distanceRight = 0;
  int distanceLeft = 0;
  delay(100);
 
// if(cm >100){Servo1.write(90); back(); }
//  else {
//    move_stop();
//      Servo1.write(0); 
//      delay(500);                   
//      if(cm >100)  { move_forward();}
//      else {Servo1.write(180);
//            
//            delay(500);    
//              if(cm >100)  { move_backward();}
//              else{Servo1.write(90);delay(200);
//                      if (cm <100){ forward(); delay(1000);}
//              }
//          } 
//    }


//    autonomous_mode();

  //from 60 to 50
  if (cm < 60 && cm > 20){
    move_stop();
    delay(300);
    forward();
    delay(400);
    move_stop();
    delay(300);
    distanceRight = lookRight();
    Serial.println(distanceRight);
    delay(300);
    distanceLeft = lookLeft();
    if(distanceRight > 30){
    Serial.println(distanceRight);
    delay(300);
   move_forward();
   delay(400);
    }
    else{
      
      delay(300);
   move_backward();
   delay(400);
      }
  }
   else if (cm < 20){
    move_stop();
    delay(300);
    forward();
    delay(400);
    move_stop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    
  }
  else{
    back();
 }

 u8g.firstPage();  
  do {
    drawDistance();
  } while ( u8g.nextPage() );
  delay(1000);
} //.. bluetooth has to be available

// Functions
// autonomous mode

//turnleft
void move_backward() {
    analogWrite(ENA, 220);
  analogWrite(ENB, 220);
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , LOW);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , LOW);
  }

  //turnright
  void move_forward() {
    analogWrite(ENA, 220);
  analogWrite(ENB, 220);
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , LOW);
    digitalWrite(IN4 , HIGH);
  }

  void move_stop() {
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , HIGH);
  }

  void turn_left() {
    analogWrite(ENA, 220);
  analogWrite(ENB, 220);
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , HIGH);
    delay(1000);
  }

  void turn_right() {
    analogWrite(ENA, 220);
  analogWrite(ENB, 220);
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , HIGH);
    digitalWrite(IN3 , LOW);
    digitalWrite(IN4 , HIGH);
    delay(1000);
  }
//moveforward
void back() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
//  Serial.println("Back");
}
//movebackward
void forward() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
//  Serial.println("Forward");
}

int lookRight(){ 
  Servo1.write(0);
  delay(500);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  temp = float(pulseIn(Echo, HIGH));
//  cm = (temp * 17 ) / 1000;
  cm = temp * 0.034 / 2;
  delay(100);
    Servo1.write(90);
  return cm;
}


int lookLeft(){
 Servo1.write(180);
  delay(500);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  temp = float(pulseIn(Echo, HIGH));
//  cm = (temp * 17 ) / 1000;
  cm = temp * 0.034 / 2;
  delay(100);
   Servo1.write(90);
  return cm;
  delay(100);
}

  
