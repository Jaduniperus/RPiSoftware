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



void setPot(int channel, int pot, int level)
{
  uint8_t buff[2];
  buff[0] = pot;
  buff[1] = level;
  wiringPiSPIDataRW(channel, buff, sizeof(buff));
}

void SPIAllOff()
{
  int z;
  for(z=0; z<4; z++)
  {
    setPot(SPIChannelAD1,z,SPIADVolMin);
    setPot(SPIChannelAD2,z,SPIADVolMin);
  }
}

void SPISetup()
{  
  SPIAllOff();  
  cout << "Toutes les voies des AD5204 sont au minimum" << endl;
}

void SPIRainbow()
{
  cout << "Augmentation du volume" << endl;
  for (int i = SPIADVolMin; i < SPIADVolMax; --i)
  {
    setPot(SPIChannelAD1,SPIPotVoie1,i);
    usleep(1000*5);
  }

  cout << "Diminution du volume" << endl;
  for (int i = SPIADVolMax; i < SPIADVolMin; ++i)
  {
    setPot(SPIChannelAD1,SPIPotVoie1,i);
    usleep(1000*5);
  }
}

int main() 
{
  // Définition des variables du programme
  int read;

  // Initialisation de wiringPi
  wiringPiSetup();

  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(RelayPin, OUTPUT);
  int state = 0; // Niveau du relais: 1 = fermé (contact) 0 = ouvert (pas contact)

  // Initialisation des périphériques I2C
	wiringPiI2CSetup((int)I2CAddEgaliseur1);
  wiringPiI2CSetup((int)I2CAddEgaliseur2);

  //Initialisation des périphériques SPI
  unsigned char buff[2];
  buff[0] = 0x00;
  wiringPiSPISetup(SPIChannelAD1, SPISpeed);
  wiringPiSPISetup(SPIChannelAD2, SPISpeed);
  
  SPISetup();
  
  cout << "Fin de l'initialisation des périphériques série" << endl;

  // Boucle infinie du programme
  
  while(true)
  {
    
    cin >> read; 
    //wiringPiI2CWrite(fd,read);*/
    setPot(SPIChannelAD1,SPIPotVoie1,read);
    usleep(1000*10);

  }

  cout << "FIN" << endl;
  return 0;
}