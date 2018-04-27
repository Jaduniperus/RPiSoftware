#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>

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
#define ADChipSelect 10


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

void setPot(int pot, int level)
{
  uint8_t buff[2];
  buff[0] = pot;
  buff[1] = level;
  digitalWrite(ADChipSelect, 0); //active le composant
  wiringPiSPIDataRW(0, buff, 2);
  digitalWrite(ADChipSelect, 1); //désactive le composant
}

void allOff()
{
  int z;
  for(z=0; z<4; z++)
  {
    setPot(z,0);
  }
}

void allOn()
{
  for(int z=0; z<4; z++)
  {
    setPot(z,255);
  }
}

int main() 
{
  // Définition des variables du programme
  int state = 0; // Niveau du relais: 1 = fermé (contact) 0 = ouvert (pas contact)
  unsigned char init;     // Lecture des conditions d'activation des périphériques série
  //char read[8]; // Lecture des commande hexa opur TDA
  uint8_t read;
  int ack; // int recu apres un wiringPiI2CWrite

  // Initialisation de wiringPi
  if(wiringPiSetup() == -1) //when initialize wiringPi failed, print message to screen
  { 
    printf("setup wiringPi failed !\n");
    return -1; 
  }

  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(RelayPin, OUTPUT);
  pullUpDnControl(8, PUD_UP); // SDA
  pullUpDnControl(9, PUD_UP); // SCL
  // Initialisation des périphériques i2c au moyen de wiringPiI2CSetup
  char devIdTDABass = 0x43;
  char devIdTDATrebble = 0x42;

  // Initialisation des périphériques série
  // création de l'objet I2C à l'adresse 0x86 (pour TDA bass)
	int fd = wiringPiI2CSetup((int)devIdTDABass);
  ack = wiringPiI2CWrite(fd,1000110);
  cout << "I2C_TDABASS CONFIGURE = " << fd << "ack = " << ack << endl;
  // test validant la création de l'objet I2C
  if(fd < 0) 
    cout << "Erreur avec la connexion au TDA bass | Errno is: " << errno << endl;

    // création de l'objet I2C à l'adresse 0x82 (pour TDA trebble)
  int I2C_TDATREBL = wiringPiI2CSetup((int)devIdTDATrebble);
  cout << "I2C_TDATREBL CONFIGURE = " << I2C_TDATREBL << endl;
  // test validant la création de l'objet I2C
  if(I2C_TDATREBL < 0) 
    cout << "Error. TDA trebble Errno is: " << errno << endl;

  //Initialisation des périphériques SPI au moyen de wiringPiSPISetup
  int devIdAD1 = 0;
  int devIdAD2 = 1;
  int speed = 500000;

  cout << "Utiliser le AD avec l'addresse  ? y/n" << endl;
  cin >> init;
  if(init == 'y')
  {
    // création de l'objet SPI à l'adresse (premier digipot)
    int SPI_AD1 = wiringPiSPISetup(devIdAD1, speed);
    // test validant la création de l'objet SPI
      if(SPI_AD1 < 0) cout << "Error. AD1 creation  Errno is: " << errno << endl;
    //création de l'objet SPI à l'adresse (deuxième digipot)
    int SPI_AD2 = wiringPiSPISetup(devIdAD2, speed);
    // test validant la création de l'objet SPI
      if(SPI_AD2 < 0) cout << "Error. AD2 Errno is: " << errno << endl;
  }
  
  cout << "Fin de l'initialisation des périphériques série" << endl;
  uint8_t buff[2];
  buff[0] = 0;
  // Boucle infinie du programme
  while(true)
  {
    /*
    cin >> read; 
    /*
    ack = wiringPiI2CWrite(fd,read);
    cout << " ack = " << ack << endl;
    if( ack < 0) cout << "Communication ratée" << endl;
    else cout << "Byte envoyé: " << read << endl;*/


    cout<<"Blink all"<<endl;
    digitalWrite(ADChipSelect, 0); //active le composant   
    //allOn();
    buff[1] = 255;
    wiringPiSPIDataRW(0, buff, 2);
    digitalWrite(ADChipSelect, 1); //désactive le composant
    usleep(1000*1000);


    cout<<"Shut all"<<endl;
    digitalWrite(ADChipSelect, 0); //active le composant   
    //allOff();
    buff[1] = 0;
    wiringPiSPIDataRW(0, 0, 2);
    digitalWrite(ADChipSelect, 1); //désactive le composant
    usleep(1000*1000);

  }

  cout << "FIN" << endl;
  return 0;
}