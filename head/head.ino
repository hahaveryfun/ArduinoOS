#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int up = 7;
int down = 8;
int select = 9;

String currentmenu;
int menuindex = 0;
String mainmenu[3] = {"Start", "Some Options", "Exit"};
String options[3] = {"Option 1", "Option 2", "Option 3"};
int currentmenulength = sizeof(mainmenu)/sizeof(mainmenu[0]);
//da faq ^
//idk, stackoverflow said so, and it worked
boolean uppressed = false;
boolean downpressed = false;
boolean topcursor = true;

String formatForLCD(String _s)
{
  if(_s.length()>15)
    return _s.substring(0, 15);
  String ret = _s;
  for(int i = _s.length(); i<15; i++)
  {
    ret = ret + " ";
  }
  return ret;
}

void blinkSelect()
{
  if ((millis()/500)%2==1)
  {
    //odd second
    if(topcursor)
    {
      lcd.setCursor(15,1);
      lcd.print(" ");
      lcd.setCursor(15,0);
    }
    else
    {
      lcd.setCursor(15,0);
      lcd.print(" ");
      lcd.setCursor(15,1);
    }
    lcd.print("<"); 
  }
  else
  {
    //even second
    if(topcursor)
    {
      lcd.setCursor(15,1);
      lcd.print(" ");
      lcd.setCursor(15,0);
    }
    else
    {
      lcd.setCursor(15,0);
      lcd.print(" ");
      lcd.setCursor(15,1);
    }
    lcd.print(" "); 
  }
}

void setupMenu(String _menu[])
{
  lcd.print(formatForLCD(_menu[0]));
  lcd.setCursor(0, 1);
  if(sizeof(_menu)>1)
  {
    lcd.print(formatForLCD(_menu[1]));
    lcd.setCursor(0, 0); 
  }
}

void navigateUp(int _menuIndex, String _menu[])
{
  //only occurs when the cursor is at the top
  if (_menuIndex-1>=0)
  {
    lcd.setCursor(0,0);
    lcd.print(formatForLCD(_menu[_menuIndex-1]));
    lcd.setCursor(0,1);
    lcd.print(formatForLCD(_menu[_menuIndex]));
  }
}

void navigateDown(int _menuIndex, String _menu[])
{
  //only occurs when the cursor is at the bottom
  if (_menuIndex+1<currentmenulength)
  {
    lcd.setCursor(0,0);
    lcd.print(formatForLCD(_menu[_menuIndex]));
    lcd.setCursor(0,1);
    lcd.print(formatForLCD(_menu[_menuIndex+1]));
  }
}

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("ArduinoOS!");
  lcd.setCursor(0, 0);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  delay(1000);
  setupMenu(mainmenu);
}

void loop() 
{ 
  blinkSelect();
  
  if(digitalRead(up)==LOW)
  {
    uppressed = true;
  }
  else if (uppressed==true)
  {
    //button has been released after a press, do action
    uppressed = false;
    if (topcursor==false)
    {
      //cursor is on the bottom, no need to navigate up
      topcursor = true;
    }
    else
    {
      //cursor is on the top
      navigateUp(menuindex, mainmenu);
    }
    menuindex--;
    if (menuindex<0)
      menuindex=0;
  }
  //down nav button below
  else if(digitalRead(down)==LOW)
  {
    downpressed = true;
  }
  else if (downpressed==true)
  {
    //button has been released after a press, do action
    downpressed = false;
    if (topcursor)
    {
      //cursor is on the top, no need to navigate down
      topcursor = false;
    }
    else
    {
      //cursor is on the bottom
      navigateDown(menuindex, mainmenu);
    }
    menuindex++;
    if (menuindex>=currentmenulength)
      menuindex=currentmenulength-1;
  }
  else
  {
    
  }
}

