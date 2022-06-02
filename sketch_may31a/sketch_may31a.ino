#include <LiquidCrystal.h> // biblioteca necesara pentru comunicarea dintre Arduino si LCD
#include "MQ135.h" //biblioteca necesara pentru senzorul de CO2

int co2lvl; //variabila ce va contine valoarea ppm de CO2
MQ135 senzor_gaz = MQ135(A0); //definire variabila functie de citire a valorii de CO2 emisa de senzor

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //valori porturi conectate la placuta arduino

byte bun[8] = {0b00000, 0b01010, 0b01010, 0b00000, 0b00000, 0b10001, 0b01110, 0b00000}; //valori pentru desenare smiley face :)
byte rau[8] = {0b00000, 0b01010, 0b01010, 0b00000, 0b00000, 0b01110, 0b10001, 0b00000}; //valori pentru desenare sad face 


void setup() {

  lcd.begin(16, 2); //specificam dimensiunea ecranului lcd cu care vom lucra: 16-coloane; 2-linii;    
            
  lcd.setCursor (0,0); //setam pozitia cursorului la inceput
  lcd.print("Sistem masurare"); //afisam la inceput acest mesaj de introducere
  lcd.setCursor (0,1); //setam cursorul la linia urmatoare
  lcd.print("      CO2      "); //afisam 

  delay(2000); //mentinem pe lcd mesajul pentru o perioada de 2 secunde
  lcd.clear(); // stergem mesajul
  lcd.print("Pregatire...");
  
  for(int i=0; i<=100; i++){ //folosim un for pentru a afisa in procente timpul de asteptare pentru incalzirea senzorului
    lcd.setCursor(12,0);
    if (i<100) lcd.print(" ");
    if (i<10) lcd.print(" ");
    lcd.print(i);
    lcd.print("%");
    delay(700);
  }

  lcd.createChar(0, bun); //cream un vector pentru functia write pe care il vom folosi pentru afisare
  lcd.createChar(1, rau);
  
}


void loop() {
                        
  co2lvl = senzor_gaz.getPPM(); //preluam valoarea ppm de la senzor
  lcd.setCursor (0,0); //afisam
  lcd.print("Nivelul de CO2:");
  lcd.setCursor(0,1);
  lcd.print(co2lvl);
  lcd.print(" ppm");
  
  if((co2lvl >= 350)&&(co2lvl <= 1000)){ //daca valoarea ppm este intre 350 si 1000, aerul este de calitate buna
    lcd.print("  Bun ");
    lcd.write(byte(0));
  }

  else if((co2lvl >= 1000)&&(co2lvl <= 2000)){ //daca valoarea ppm este intre 1000 si 2000, aerul este de calitate rea
    lcd.print("  Rau ");
    lcd.write(byte(1));
  }
  
  else{
    lcd.print(" Pericol"); //in alt caz nu este ok !!!
  }
  
  delay(300);
  lcd.clear();
}
