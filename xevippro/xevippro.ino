#include "SoftwareSerial.h"
SoftwareSerial HC06 (4, 3); //TX, RX
#include <Wire.h> //Gọi thư viện I2C để sử dụng các thư viện I2C
// SDA, SCL nối chân A4, A5
#include <LiquidCrystal_I2C.h> //Thư viện LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2); //Khai báo địa chỉ I2C (0x27 or 0x3F) và LCD 16x02
//
#include <Servo.h>
Servo servomotor1;
Servo servomotor2;
Servo servomotor3;
Servo myServo; 
//
int ENA = 5;
int IN1 = 10;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENB = 6;

//kết nối của 5 cảm biến hồng ngoại (dò line ) (1,2,3,4,5 từ trái qua phải)
const int L_S = 2;
const int L_SS = 12;
const int R_S = 11;
const int R_SS = 13;

char dieu_khien;
int Speed = 90;

void setup() {
  HC06.begin(9600);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);     
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(L_S, INPUT);
  pinMode(L_SS, INPUT);
  pinMode(R_S, INPUT);
  pinMode(R_SS, INPUT);
  
  Stop();

  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);

  lcd.init(); //Khởi tạo màn hình LCD
  lcd.backlight(); //Bật đèn màn hình lCD
//
  servomotor1.attach(A0);
  servomotor2.attach(A3);
  servomotor3.attach(A2);


  servomotor1.write(30);
  servomotor2.write(0);
  servomotor3.write(130);

//
}

void loop() 
{
  lcd.setCursor(1, 0); //Chọn vị trí đặt con trỏ. 0 đầu là chọn cột (từ 0 - 16), 0 kế là chọn hàng (có 2 hàng 0 và 1)
  lcd.print("FPT POLYTECHNIC"); //in lên lcd chữ tỏng dấu ""
  lcd.setCursor(2, 1); //Chọn vị trí đặt con trỏ. 0 đầu là chọn cột (từ 0 - 16), 0 kế là chọn hàng (có 2 hàng 0 và 1)
  lcd.print("X-AUTOMATION"); //in lên lcd chữ tỏng dấu ""
  if (HC06.available() > 0) 
  {
    dieu_khien = HC06.read();
    Serial.println(dieu_khien);
    switch (dieu_khien) 
    {
      case 'F':
        tien();
        break;
      case 'B':
        lui();
        break;
      case 'L':
        trai();
        break;
      case 'R':
        phai();
        break;
      case 'G':
        tien_phai();
        break;
      case 'I':
        tien_trai();
        break;
      case 'H':
        lui_phai();
        break;
      case 'J':
        lui_trai();
        break;
      case 'S':
        Stop();
        break;
      case 'X':
        do_line();
        break;
      case 'x':
        Stop();
        break;
      case 'W':
        sv1chuyendong();
        break;
      case 'w':
        sv1dungyen();
        break;
      case 'U':
        sv2chuyendong();
        break;
      case 'u':
        sv2dungyen();
        break;
      case '0':
       Speed=90;
       break;
      case '1':
        Speed=70;
        break;
      case '2':
       Speed=120;
       break;
      case 'V':
        sv3xuong();
        break;
      case 'v':
        sv3len();
        break;
    }
  }
}


void tien() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void lui() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void phai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void trai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void tien_trai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void tien_phai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
void lui_phai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
void lui_trai() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void do_line() 
{
  do {
    if ((digitalRead(L_S) == 0) && (digitalRead(R_S) == 0) && (digitalRead(L_SS) == 0) && (digitalRead(R_SS) == 0)) {
      tien();
    } 
    else if ((digitalRead(L_S) == 1) || (digitalRead(L_SS) == 1)) {
      phai();
    }else if ((digitalRead(R_S) == 1) || (digitalRead(R_SS) == 1)){
      trai();
    } }
   while (!((digitalRead(L_S) == 1) && (digitalRead(R_S) == 1) && (digitalRead(L_SS) == 1) && (digitalRead(R_SS) == 1)));{
    Stop();
  }
}

void sv1chuyendong()
  {
    for(int i=30; i>=0;i--)
    {
      servomotor1.write(i);
      delay(25);
    }
  }
void sv1dungyen()
  {
    for(int i=0; i<=30; i++)
    {
     servomotor1.write(i);
      delay(25);
    } 
  }
void sv2chuyendong()
{
  for(int i=0; i<=55;i++)
  {
    servomotor2.write(i);
    delay(25);
  }
}
void sv2dungyen()
{
  for(int i=55; i>=0; i--)
  {
    servomotor2.write(i);
    delay(25);
  }
}
  void sv3xuong()
  {
    for(int i =130 ; i<=170; i++)
    {
      servomotor3.write(i);
      delay(25);
    }
  }
  void sv3len()
  {
    for(int i=170; i>=130; i--)
    {
      servomotor3.write(i);
      delay(25);
    }
  }