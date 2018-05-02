#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/spifunctions.h" 

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

int main() 
{
  // Définition des variables du programme
  int read;
  int mode;

  // Initialisation de wiringPi
  wiringPiSetup();

  // Initialisation de l'ensemble des pin utilisées comme GPIO
  pinMode(RelayPin, OUTPUT);
  int state = 0; // Niveau du relais: 1 = fermé (contact) 0 = ouvert (pas contact)

  // Initialisation des périphériques I2C
	int fd = wiringPiI2CSetup((int)I2CAddEgaliseur1);
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
    cout << "Mode :";
    cin >> mode;
    cout << "Commande ";
    cin >> read;
    
    if(mode == 1)
      wiringPiI2CWrite(fd,read);
    if(mode == 2) 
      setPot(SPIChannelAD1,SPIPotVoie1,read);
    usleep(1000*10);

  }

  cout << "FIN" << endl;
  return 0;
}