//written for Arduino 1.8.5
//the two libraries below are required to run the controller
//LiquidCrystal is usually comes with Arduino but TimeLib is required to be downloaded
//Look up "TimeLib.h Arduino" in google
#include <LiquidCrystal.h>
#include <TimeLib.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define PHrs 0
#define PMin 1
#define PSec 2
#define P_Hrs 6
#define P_Min 3
#define P_Sec 4
#define PRep 5
int Min = 0;
int Sec = 10;
int Hrs = 0;
int Rep = 5;
int _Min = 0;
int _Sec = 10;
int _Hrs = 0;
int place = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  lcd.begin(8, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read
  if (digitalRead(10) == HIGH){
    //digitalWrite(13, HIGH);
    //Serial.println("10");
    place = place +1;
    if (place >= 6){
      place = 0;
    }
    delay(300);
  }
  
  if (digitalRead(12) == HIGH){
    //Serial.print("12");
    if (place == PSec){Sec = Sec +1;
      if (Sec >= 60){
        Sec = 0;}}
    else if (place == PMin){Min = Min +1;
      if (Min >= 60){
        Min = 0;}}
    else if (place == PHrs){Hrs = Hrs +1;
      if (Hrs >= 2){
        Hrs = 0;}}
    else if (place == PRep){Rep = Rep +1;
      if (Rep >= 51){
        Rep = 1;}}                                        //off time  V
    else if (place == P_Sec){_Sec = _Sec +1;
      if (_Sec >= 60){
        _Sec = 0;}}
    else if (place == P_Min){_Min = _Min +1;
      if (_Min >= 90){
        _Min = 0;}}
    else if (place == P_Hrs){_Hrs = _Hrs +1;
      if (_Hrs >= 3){
        _Hrs = 0;}}
    delay(200);
  }

  if (digitalRead(11) == HIGH){
    if (place == PSec){Sec = Sec -1;
      if (Sec < 0){
        Sec = 59;}}
    else if (place == PMin){Min = Min -1;
      if (Min < 0){
        Min = 59;}}
    else if (place == PHrs){Hrs = Hrs -1;
      if (Hrs < 0){
        Hrs = 1;}}
    else if (place == PRep){Rep = Rep -1;
      if (Rep < 1){
        Rep = 50;}}                                          //off time  V
    else if (place == P_Sec){_Sec = _Sec -1;
      if (_Sec < 0){
        _Sec = 59;}}
    else if (place == P_Min){_Min = _Min -1;
      if (_Min < 0){
        _Min = 89;}}
    else if (place == P_Hrs){_Hrs = _Hrs -1;
      if (_Hrs < 0){
        _Hrs = 2;}}
    delay(200);
  }
  //Serial.print("2");
  //show
  if (place == PSec){
    lcd.print("Sec On: ");
    lcd.setCursor(0,1);
    lcd.print(Sec);
    lcd.print("       ");
  }
  else if (place == PMin){
    lcd.print("Min On: ");
    lcd.setCursor(0,1);
    lcd.print(Min);
    lcd.print("       ");
  }
  else if (place == PHrs){
    lcd.print("Hrs On: ");
    lcd.setCursor(0,1);
    lcd.print(Hrs);
    lcd.print("       ");
  }
  else if (place == PRep){
    lcd.print("Rep:    ");
    lcd.setCursor(0,1);
    lcd.print(Rep);
    lcd.print("       ");                              //off time  V
  }
  else if (place == P_Sec){
    lcd.print("Sec Off:");
    lcd.setCursor(0,1);
    lcd.print(_Sec);
    lcd.print("       ");
  }
  else if (place == P_Min){
    lcd.print("Min Off:");
    lcd.setCursor(0,1);
    lcd.print(_Min);
    lcd.print("       ");
  }
  else if (place == P_Hrs){
    lcd.print("Hrs Off:");
    lcd.setCursor(0,1);
    lcd.print(_Hrs);
    lcd.print("       ");
  }
  //do
  if (digitalRead(9) == HIGH){
    delay(700);
    if (digitalRead(9) == HIGH){
      delay(700);
      if (digitalRead(9) == HIGH){
        lcd.clear();
        lcd.print(Hrs);
        lcd.print(":");
        lcd.print(Min);
        lcd.print(":");
        lcd.print(Sec);
        lcd.setCursor(0,1);
        //lcd.print(_Hrs);
        //lcd.print(":");
        lcd.print(_Min);
        lcd.print(":");
        lcd.print(_Sec);
        lcd.print(" ");
        lcd.print(Rep);
        while(digitalRead(9) == HIGH){
          delay(5);
          }
        while(digitalRead(9) == LOW && digitalRead(10) == LOW && digitalRead(11) == LOW && digitalRead(12) == LOW){
          delay(5);
        }
        if (digitalRead(9) == HIGH){
          lcd.clear();
          lcd.print("STARTING");
          delay(2000);
          int i;
          int totalEndS = now() + Rep*((Hrs+_Hrs) * 3600 + (Min+_Min) * 60 + Sec+_Sec);
          for(i = 0; i < Rep; i++){
            digitalWrite(13, HIGH);
            lcd.clear();
            //lcd.print("ON      ");
            int endtime = now() + (Hrs * 3600 + Min * 60 + Sec);
            while(digitalRead(9) == LOW && digitalRead(10) == LOW && digitalRead(11) == LOW && digitalRead(12) == LOW && now() <= endtime){
              //lcd display time left
              //lcd.setCursor(0,0);
              //lcd.print(endtime + _Hrs * 3600 + _Min * 60 + _Sec - now());
              //lcd.print("     ");
              lcd.setCursor(4,0);
              lcd.print("ON  ");
              lcd.setCursor(0,1);
              //lcd.print(Rep - i);
              //lcd.print(" ");
              lcd.print(int((totalEndS-now())/3600));
              lcd.print(":");
              lcd.print(int(((totalEndS-now())%3600)/60));
              lcd.print(":");
              lcd.print(int((((totalEndS-now())%3600)%60)));
              lcd.print("   ");
              delay(1);
              }
            if (digitalRead(9) == HIGH || digitalRead(10) == HIGH || digitalRead(11) == HIGH || digitalRead(12) == HIGH){
              digitalWrite(13, LOW);lcd.print("Off     ");delay(1000);break;
              }

            digitalWrite(13, LOW);
            lcd.clear();
            //lcd.print("OFF     ");
            endtime = now() + (_Hrs * 3600 + _Min * 60 + _Sec);
            while(digitalRead(9) == LOW && digitalRead(10) == LOW && digitalRead(11) == LOW && digitalRead(12) == LOW && now() <= endtime){
              //lcd display time left
              //lcd.setCursor(0,0);
              //lcd.print(endtime-now());
              //lcd.print("     ");
              lcd.setCursor(4,0);
              lcd.print("ON  ");
              lcd.setCursor(0,1);
              //lcd.print(Rep - i);
              //lcd.print(" ");
              lcd.print(int((totalEndS-now())/3600));
              lcd.print(':');
              lcd.print(int(((totalEndS-now())%3600)/60));
              lcd.print(':');
              lcd.print(int((((totalEndS-now())%3600)%60)));
              lcd.print("   ");
              delay(1);
              }
            if (digitalRead(9) == HIGH || digitalRead(10) == HIGH || digitalRead(11) == HIGH || digitalRead(12) == HIGH){
              digitalWrite(13, LOW);lcd.print("Off     ");delay(1000);break;
            }
            digitalWrite(13, LOW);
          }
        }
        else{}
      }
    }
  }
  lcd.setCursor(0, 0);
}
