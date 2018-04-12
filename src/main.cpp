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
#define RelayPin 29

/* I2C Start condition
* SCL HIGH 
* SDA HIGH -> LOW
*
* I2C Stop condition
* SCL LOW -> HIGH
* SDA LOW -> HIGH
*
* Ne jamais modifier l'état de SCL pendant un changement d'état de SDA
* Modifier SDA que quand SCL est LOW
* 
* Mettre SDA en HIGH au moment du ACKNOWLEDGE. LE TDA passera SDA à LOW si ACK
*
* PULL UP sur SDA et SCL
*/
int main() 
{
  // Définition des variables du programme
  int state = 0; // Niveau du relais: 1 = fermé (contact) 0 = ouvert (pas contact)
  char init;     // Lecture des conditions d'activation des périphériques série
  unsigned __int8 read; // Lecture des commande hexa opur TDA

  // Initialisation de wiringPi
  if(wiringPiSetup() == -1) //when initialize wiringPi failed, print message to screen
  { 
    printf("setup wiringPi failed !\n");
    return -1; 
  }

  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(RelayPin, OUTPUT);
  
  // Initialisation des périphériques i2c au moyen de wiringPiI2CSetup
  unsigned __int8 devIdTDABass = 0x43;
  unsigned __int8 devIdTDATrebble = 0x42;
  //permet de configurer une pin en mode pull-up, pull-down ...
  pullUpDnControl(8, PUD_UP); 
  pullUpDnControl(9, PUD_UP);

  // Initialisation des périphériques série
  cout << "Utiliser le TDA avec l'addresse 0x43 ? y/n" << endl;
  cin >> init;
  if(init == 'y')
  {
    // création de l'objet I2C à l'adresse 0x86 (pour TDA bass)
  	int I2C_TDABASS = wiringPiI2CSetup(devIdTDABass);
    // test validant la création de l'objet I2C
      if(I2C_TDABASS < 0) 
        cout << "Erreur avec la connexion au TDA bass | Errno is: " << errno << endl;
  }

  cout << "Utiliser le TDA avec l'addresse 0x42 ? y/n" << endl;
  cin >> init;
  if(init == 'y')
  {
    // création de l'objet I2C à l'adresse 0x82 (pour TDA trebble)
  int I2C_TDATREBL = wiringPiI2CSetup(devIdTDATrebble);
  // test validant la création de l'objet I2C
    if(I2C_TDATREBL < 0) cout << "Error. TDA trebble Errno is: " << errno << endl;
  }

  // Initialisation des périphériques SPI au moyen de wiringPiSPISetup
  int devIdAD1;
  int devIdAD2;
  int speed = 500000;

  cout << "Utiliser le AD avec l'addresse  ? y/n" << endl;
  cin >> init;
  if(init == 'y')
  {
    // création de l'objet SPI à l'adresse (premier digipot)
    int SPI_AD1 = wiringPiSPISetup(devIdAD1, speed);
    // test validant la création de l'objet SPI
      if(SPI_AD1 < 0) cout << "Error. AD1 creation  Errno is: " << errno << endl;
      // création de l'objet SPI à l'adresse (deuxième digipot)
    int SPI_AD2 = wiringPiSPISetup(devIdAD2, speed);
    // test validant la création de l'objet SPI
      if(SPI_AD2 < 0) cout << "Error. AD2 Errno is: " << errno << endl;
  }
  
  cout << "Fin de l'initialisation des périphériques série" << endl;

  // Boucle infinie du programme
  do
  {
    cin >> read;
    value = wiringPiI2CWrite(I2C_TDABASS,read);
  } while(state != -1);

  return 0;
}