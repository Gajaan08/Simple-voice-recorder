#include <LiquidCrystal.h>
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
int upSwitch=5;
int downSwitch=6;
int oldUpVal=1;
int oldDownVal=1;
int newUpVal;
int newDownVal;
int stage=0;
int welcome=0;
int dt=1000;
int ini=0;




void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
pinMode(upSwitch,INPUT);
pinMode(downSwitch,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(welcome==0){
    
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    delay(dt);
    lcd.setCursor(0,1);
    lcd.print("Select Clip");
    delay(dt);
    lcd.clear();
    welcome=1;
  
  }
  newUpVal=digitalRead(upSwitch);
  newDownVal=digitalRead(downSwitch);
  


  while(ini==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("One");
    lcd.setCursor(0,1);
    lcd.print("Two");
    lcd.setCursor(3,0);
    lcd.blink();
    ini=1;
  }

  if(newDownVal==1 && oldDownVal==0 && stage==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Two");
    lcd.setCursor(0,1);
    lcd.print("Three");
    lcd.setCursor(3,0);
    lcd.blink();
 
    stage=1;
  }

  if(newUpVal==1 && oldUpVal==0 && stage==1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("One");
    lcd.setCursor(0,1);
    lcd.print("Two");
    lcd.setCursor(3,0);
    lcd.blink();
    stage=0;
}

  oldUpVal=newUpVal;
  oldDownVal=newDownVal;
  
  
  

}
