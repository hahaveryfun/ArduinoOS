#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int up = 7;
int down = 8;
int select = 9;

int menuindex = 0;
String mainmenu[3] = {"Start", "Some Options", "Exit"};
String options[3] = {"Option 1", "Option 2", "Option 3"};
String *currentmenu = mainmenu;
int currentmenulength = sizeof(currentmenu)/sizeof(currentmenu[0]);
//da faq ^
//idk, stackoverflow said so, and it worked
boolean uppressed = false;
boolean downpressed = false;
boolean selectpressed = false;
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
  if(currentmenulength>1)
  {
    lcd.print(formatForLCD(_menu[1]));
    lcd.setCursor(0, 0); 
  }
}

void selectItem(int _menuindex, String _currentmenu[])
{
  if(_currentmenu[_menuindex]=="Some Options")
  {
    menuindex=0;
    topcursor=true;
    currentmenu = options;
    setupMenu(options);
  }
}

void navigateUp(int _menuindex, String _menu[])
{
  //only occurs when the cursor is at the top
  if (_menuindex-1>=0)
  {
    lcd.setCursor(0,0);
    lcd.print(formatForLCD(_menu[_menuindex-1]));
    lcd.setCursor(0,1);
    lcd.print(formatForLCD(_menu[_menuindex]));
  }
}

void navigateDown(int _menuindex, String _menu[])
{
  //only occurs when the cursor is at the bottom
  if (_menuindex+1<currentmenulength)
  {
    lcd.setCursor(0,0);
    lcd.print(formatForLCD(_menu[_menuindex]));
    lcd.setCursor(0,1);
    lcd.print(formatForLCD(_menu[_menuindex+1]));
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
  currentmenulength = sizeof(currentmenu)/sizeof(currentmenu[0]);
  
  //up button code
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
  
  //down button code
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
  
  //select button code
  else if(digitalRead(select)==LOW)
  {
    selectpressed = true;
  }
  else if (selectpressed==true)
  {
    //button has been released after a press, do action
    selectpressed = false;
    selectItem(menuindex, currentmenu);
  }
}

