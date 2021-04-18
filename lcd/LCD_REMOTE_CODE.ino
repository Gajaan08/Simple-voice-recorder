#include <Keypad.h>
#include <LiquidCrystal.h>

const byte rows=4;
const byte cols=3;

char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows]={1,2,3,4};
byte colPins[cols]={5,6,7};

Keypad gajo = Keypad(makeKeymap(keys),rowPins,colPins,4,3);
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
char chosenKey;



void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
chosenKey= gajo.getKey();
if(chosenKey=='1'){
  lcd.setCursor(0,0);
  lcd.blink();
  lcd.clear();
  lcd.print("One");
  
}
if(chosenKey=='2'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Two");
  
}
if(chosenKey=='3'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Three");
  
}
if(chosenKey=='4'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Four");
  
}
if(chosenKey=='5'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Five");
  
}
if(chosenKey=='6'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Six");
  
}
if(chosenKey=='7'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Seven");
  
}
if(chosenKey=='8'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Eight");
  
}
if(chosenKey=='9'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("nine");
  
}
if(chosenKey=='0'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.noBlink();
  
}

if(chosenKey=='#'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Hashtag");
  
}
if(chosenKey=='*'){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.blink();
  lcd.print("Star");
  
}
}
