/* This program is design to control 
 * motor at specific time
 * Programmer: Dr. Aung Win Htut
 * MIT open source license
 * 2016-08-29
 */
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Analog Input Pin no. for three buttons
const int resetPin=A1;
const int plusPin=A2;
const int minusPin=A3;
//buttons on off state (here assume 1 - on   0 - off)
int btnMode = 1;
int btnPlus = 1;
int btnMinus = 1;

//To determine minutes we use two different time
double startTime;
double lastTime;

int Minute=0;  //Minute value storage
int Rest=0;    //Rest status (On/Off)

//Output control pin number
const int outputPin=8;

int RunTime =60;  //Running time setting value
int RestTime=15;  //Resting time setting value

void setup()
{
  pinMode(outputPin , OUTPUT);  //determine output pin as output
  startTime = millis();         //start time to count minutes
  lastTime = millis();          //last time to different to count minutes
  Serial.begin(9600);           //starting serial for debugging  
  lcd.begin(16, 2);             //starting lcd

  //lcd first row printing mode
  lcd.setCursor(0, 0);
  lcd.print("Running Mode");
  
  //lcd second row first column print zero
  lcd.setCursor(0, 1);
  lcd.print(0);
  //lcd second row fifth column print zero  
  lcd.setCursor(5, 1);
  lcd.print(0);
  
  //starting output device
  digitalWrite(outputPin, HIGH);
}

void loop()
{
  Serial.println("loop started!");
  btnMode=1;
  btnMode = digitalRead(resetPin);  
   if(btnMode==0)
    {
      Serial.print("btnMode ");
      Serial.println(btnMode);
      funRunningSetting();      
    }

    //lcd first row printing mode
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Running Mode");
  lastTime = millis();  
  if((lastTime-startTime)>=600)//if((NOW%60000)==0)
  {
    startTime=millis();
    Minute=Minute+1;
    Serial.println(Minute);
    lcd.setCursor(0, 1);
    lcd.print(Minute);
    lcd.noBlink();
    switch(Rest)
    {
      case 0: 
        if(Minute>=6)
        {
          Minute=0;
          Rest=1;
          lcd.setCursor(5, 1);
          lcd.print("Stop Machine");
          digitalWrite(outputPin, LOW);
          delay(1000);
          
        }
        break;
      case 1: 
        if(Minute>=3)
        {
          Minute=0;
          Rest=0;
          lcd.setCursor(5, 1);
          lcd.print("Start Machine");
          digitalWrite(outputPin, HIGH);
        }
        break;
    }
    
  }
  
  
  delay(1000);
  
}



void funRunningSetting()
{
  Serial.println("funRunningSetting started!");
  for(;;)
  {  btnMode = 1;
     btnPlus = 1;
     btnMinus = 1;
    btnMode = digitalRead(resetPin);
    btnPlus = digitalRead(plusPin);
    btnMinus = digitalRead(minusPin);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Run");
    lcd.setCursor(4, 0);
    lcd.print("Rest Setting");
    lcd.setCursor(0, 1);
    lcd.print(RunTime);
    lcd.setCursor(4,1);
    lcd.print(RestTime);
    lcd.setCursor(0, 1);
    lcd.blink();
    if(btnMode==0)
    {
      funRestSetting();
     }
    else if(btnPlus==0)
    {
      RunTime = RunTime+1;
     }
    else if(btnMinus==0)
    {
      RunTime = RunTime-1;
    }
    
    lcd.noBlink();
    lcd.clear();
  }
    
    
    
}

void funRestSetting()
{
  Serial.println("funResetSetting started!");
    for(;;)
  {
    btnMode = 1;
     btnPlus = 1;
     btnMinus = 1;
    btnMode = digitalRead(resetPin);
    btnPlus = digitalRead(plusPin);
    btnMinus = digitalRead(minusPin);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Run");
    lcd.setCursor(4, 0);
    lcd.print("Rest Setting");
    lcd.setCursor(0, 1);
    lcd.print(RunTime);
    lcd.setCursor(4,1);
    lcd.print(RestTime);
    lcd.setCursor(4, 1);
    lcd.blink();
    if(btnMode==0)
    {
      loop();
    }
    else if(btnPlus==0)
    {
      RestTime = RestTime+1;
     }
    else if(btnMinus==0)
    {
      RestTime = RestTime-1;
    }
    
    lcd.noBlink();
    lcd.clear();
  }
    
}




