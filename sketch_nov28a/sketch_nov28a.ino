//Libraries
 
#include <LiquidCrystal.h>
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
 
 	int val=0;
//Constants
#define ROWS 4
#define COLS 4
//Parameters
 
//Variables
 
int k = 0;
 
 
char data,nom;
String tab;
 LiquidCrystal_I2C lcd(0x27, 16, 2);
int etat = 0;
void setup() {
  //Init Serial USB
  Serial.begin(9600);
 
  lcd.init();
  lcd.backlight();
 
 }
void loop() {
 

 
  if (etat == 0) //etat intial
  {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("***welcome***");
  }
  if (Serial.available()) //code introuvable
  {
    etat = 1;
    k = 0;
    data = Serial.read();
    tab=data;

    tab+=Serial.readString();
      
    lcd.clear();
    lcd.setCursor(0, 0);
    if (data == '0')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("client invalide");
       delay(1000);
       lcd.clear();
      etat = 0;
      k = 0;
    }
    if(data != '0') //code trouvé
    {
      int j=0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("****bonjour****");
       lcd.setCursor(0, 1);
       lcd.print(tab);
       delay(1000);
 
      delay(3000);
      lcd.clear();
      etat = 0;
 
      k = 0;
    }
  }

 
 
 }

 