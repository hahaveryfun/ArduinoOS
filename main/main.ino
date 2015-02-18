#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int up = 7;
int down = 8;
int select = 9;

void setup() 
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
}

void loop() 
{
  // set the cursor to column 0, line 1
  
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  if(digitalRead(up)==HIGH)
  {
    lcd.print("up  ");
  }
  else if(digitalRead(down)==HIGH)
  {
    lcd.print("down");
  }
  else if(digitalRead(select)==HIGH)
  {
    lcd.print("selc");
  }
  else
  {
    lcd.print("nope");
  }
}

