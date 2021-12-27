/********************************************************************
 * PROJECT NAME: PROTECTIVE SPORTS DEVICE                           *
 * REVISION DATE: 25.12.2021                                        *
 * AUTHOR: SİNAN İLBEY                                              * 
 ********************************************************************
 * PURPOSE  : CHECKING THE HEALTH OF ATHLETES FASTER AND ON SITE    *
 ********************************************************************
 * SYSTEM INPUT  :                                                  *
 *               1)PULSE SENSOR  :  MEASURING THE USER'S PULSE      * 
 ********************************************************************               
 * SYSTEM OUTPUT  :                                                 * 
 *                1)LCD I2C : GUIDING WITH LCD                      *
 *                2)BUZZER  : TO ALERT WİTH SOUND                   *   
 ********************************************************************            
 * SYSTEM WORK  : By evaluating the data from the heart rate        *
 * sensor, there are informative texts and heart rate               *
 * measurements on the LCD screen. At the same time, if the         *
 * measured values pose a health threat, it is warned by the buzzer.*               
 ********************************************************************
 */

// DEfINITIONS
#define USE_ARDUINO_INTERRUPTS true // for program flow
#include <PulseSensorPlayground.h> //sensor library
#include<LiquidCrystal_I2C.h>// LCD display (I2C) library
LiquidCrystal_I2C lcd(0x27,16,2); // lcd screen definition
int nabiz; // integer in which we will keep the heart rate per minute
const int PulseWire = 0; //connects the heart rate sensor to pin A0
const int LED13 = 13; //we use the led on the arduino
int Threshold = 550; 
PulseSensorPlayground pulseSensor;
int i;

void setup() 
{

 pinMode(8,OUTPUT);//We determine the pin we will use for the buzzer.
  Serial.begin(9600);//we establish data communication with computer
  lcd.begin(); // lcd screen start command
 
  Serial.println("ESOGU sensor okuma");
  delay(1000);// wait 1 second
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin())
  {
    Serial.println("Pulse sensoru hazır...");// we make sure the sensor is working
  }
  for(i=0; i<17; i++)// the welcome text will scroll. (1 time)
   {
  {
    lcd.clear();//cleans the lcd screen
    lcd.setCursor(i,1);
    lcd.print("HHOSGELDINIZ");//writes to lcd screen
    Serial.println("HOSGELDINIZ");//writes to computer port
   
    lcd.setCursor(i,1);
    lcd.print(" ");
    delay(200);//wait 200 milliseconds
    
  }
  

  lcd.clear();//cleans the lcd screen
  lcd.setCursor(1,0);//1st line starts writing from the 2nd column 
  lcd.print("SAGLIGINIZ ICIN");//writes to lcd screen
  Serial.println("saglıgınız ıcın");//writes to computer port
  lcd.setCursor(4,1); //2nd line starts typing from 4th column
  lcd.print("BURDAYIZ");//writes to lcd screen
  Serial.println("BURDAYIZ");//writes to computer port
  delay(2000);//wait 2 second
  
  
}

void loop() 
{
  
  if (pulseSensor.sawStartOfBeat()) //screen will work if we detect pulse
  {
    nabiz = pulseSensor.getBeatsPerMinute();//we assigned the data from the sensor to the heart rate integer
    lcd.clear();// cleans the lcd screen
    lcd.setCursor(4,0); // 1st line starts typing from 4th column
    lcd.print("Nabziniz"); //writes to lcd screen
    
    Serial.println("Nabzınız");//writes to computer port
    lcd.setCursor(6,1); //2nd line starts typing from 6th column
    lcd.print(nabiz);//writes to lcd screen
    Serial.println(nabiz);//writes to computer port
    delay(1000);//wait 1 second
    
    if(nabiz <= 60)
    {

      lcd.clear();// cleans the lcd screen
     digitalWrite(8,HIGH);//buzzer active
     delay(1000);//wait 1 second
     digitalWrite(8,LOW);//buzzer inactive
     delay(500);//wait half a second
  
      lcd.setCursor(0,0); //1st line starts typing from 1st column
      lcd.print("Nabziniz Dusuk !");//writes to lcd screen
      Serial.println("Nabzınız Dusuk !");//writes to computer port
      lcd.setCursor(0,1); //2nd line starts typing from 1stcolumn
      lcd.print("Lutfen Dinlenin");//writes to lcd screen
      Serial.println("Lutfen Dinlenin");//writes to computer port
      delay(1000);//wait 1 second
    }
    else if(nabiz >= 100)
    {

      lcd.clear(); // cleans the lcd screen
      digitalWrite(8,HIGH);//buzzer active
      delay(1000);//wait 1 second
      digitalWrite(8,LOW);//buzzer inactive
      delay(500);//wait half a second
      lcd.setCursor(0,0); //1st line starts typing from 1st column
      lcd.print("Nabziniz Yuksek !");//writes to lcd screen
      Serial.println("Nabzınız Yuksek !");//writes to computer port
      lcd.setCursor(0,1); //2nd line starts typing from 1st column
      lcd.print("Lutfen Dinlenin");//writes to lcd screen
      Serial.println("Lutfen Dinlenin");//writes to computer port
      delay(1000);//wait 1 second
    }
    else
    {

      lcd.clear();// cleans the lcd screen
      
      lcd.setCursor(0,0); //1st line starts typing from 1st column
      lcd.print("Nabziniz Normal ");//writes to lcd screen
      Serial.println("Nabziniz Normal ");//writes to computer port
      lcd.setCursor(0,1); //2nd line starts typing from 1st column
      lcd.print("Spora Devam :)");//writes to lcd screen
      Serial.println("spora Devam :)");//writes to computer port
      delay(1000);//wait 1 second
    }
  }
delay(20);//wait 20 milliseconds
}
