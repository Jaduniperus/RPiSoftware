#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>

#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 

using namespace std;

/*
 *  Architecture du code
 * ------------------------
 * Initialisation de wiringPi
 * Initialisation de la liaison I2C avec les deux TDA 7317
 * Initialisation de la liaison SPI avec les deux AD 5204
 * Initialisation de l'ensemble des pin utilisées comme GPIO
 *
 * Boucle while(1)
 * *  
 * * 
 * * 
 * * 
 * ------------------------
 * Fin de l'architecture
 */

// Definition des pin GPIO utilisées
#define LedPin 29

int main() 
{

  // Définition des variables du programme
     
  // Initialisation de wiringPi
    if(wiringPiSetup() == -1) //when initialize wiringPi failed, print message to screen
    { 
    printf("setup wiringPi failed !\n");
    return -1; 
  }

/*
  // Initialisation des périphériques i2c au moyen de wiringPiI2CSetup
  int devIdTDABass = 0x43;
  int devIdTDATrebble = 0x42;
  // création de l'objet I2C à l'adresse 0x43 (pour TDA bass)
	int I2C_TDABASS = wiringPiI2CSetup(devIdTDABass);
  // test validant la création de l'objet I2C
    if(I2C_TDABASS < 0) cout << "Error. TDA bass Errno is: " << errno << endl;
    else  cout << "Init result for TDA bass: "<< I2C_TDABASS << endl;
    // création de l'objet I2C à l'adresse 0x42 (pour TDA trebble)
  int I2C_TDATREBL = wiringPiI2CSetup(devIdTDATrebble);
  // test validant la création de l'objet I2C
    if(I2C_TDATREBL < 0) cout << "Error. TDA trebble Errno is: " << errno << endl;
    else  cout << "Init result for TDA trebble: "<< I2C_TDATREBL << endl;


  // Initialisation des périphériques SPI au moyen de wiringPiSPISetup
  int devIdAD1;
  int devIdAD2;
  int speed = 500000;
  // création de l'objet SPI à l'adresse (premier digipot)
  int SPI_AD1 = wiringPiSPISetup(devIdAD1, speed);
  // test validant la création de l'objet SPI
    if(SPI_AD1 < 0) cout << "Error. AD1 creation  Errno is: " << errno << endl;
    else  cout << "Init result for AD1: "<< SPI_AD1 << endl;
    // création de l'objet I2C à l'adresse 0x42 (pour TDA trebble)
  int SPI_AD2 = wiringPiSPISetup(devIdAD2, speed);
  // test validant la création de l'objet I2C
    if(SPI_AD2 < 0) cout << "Error. AD2 Errno is: " << errno << endl;
    else  cout << "Init result for AD2: "<< SPI_AD2 << endl;
*/
    
  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(LedPin, OUTPUT);

  // Boucle infinie du programme
  do
  {    
      digitalWrite(LedPin, LOW);   //led on
      delay(500);
      digitalWrite(LedPin, HIGH);   //led off
      delay(500);
  }
  while(1);
  
    return 0;
}

