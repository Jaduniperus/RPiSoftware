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
#define SPION 0x00
#define SPIOFF 0xFF

char devIdTDABass = 0x43;
char devIdTDATrebble = 0x42;
int channelAD1 = 0;
int channelAD2 = 1;
int speed = 1000000;

void setPot(int pot, int level)
{
  uint8_t buff[2];
  buff[0] = pot;
  buff[1] = level;
  wiringPiSPIDataRW(0, buff, 2);
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
  uint8_t read;
  unsigned char buff[2];
  buff[0] = 0x00;

  // Initialisation de wiringPi
  wiringPiSetup();

  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(RelayPin, OUTPUT);
  pinMode(ADChipSelect, OUTPUT);

  // Initialisation des périphériques I2C
	wiringPiI2CSetup((int)devIdTDABass);
  wiringPiI2CSetup((int)devIdTDATrebble);

  //Initialisation des périphériques SPI
  wiringPiSPISetup(channelAD1, speed);
  wiringPiSPISetup(channelAD2, speed);

  cout << "Fin de l'initialisation des périphériques série" << endl;

  // Boucle infinie du programme
  while(true)
  {
    /*
    cin >> read; 
    wiringPiI2CWrite(fd,read);*/

    cout<<"Blink all"<<endl;
    buff[1] = SPION;
    wiringPiSPIDataRW(channelAD1, buff, sizeof(buff));
    usleep(1000*5000);


    cout<<"Shut all"<<endl;
    //allOff();
    buff[1] = SPIOFF;
    wiringPiSPIDataRW(channelAD1, buff, sizeof(buff));
    usleep(1000*1000);

  }

  cout << "FIN" << endl;
  return 0;
}