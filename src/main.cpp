#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cChip.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/spiChip.h" 

using namespace std;

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
  i2cChip i2cEgaliseur1((int)I2CAddEgaliseur1);
  i2cChip i2cEgaliseur2((int)I2CAddEgaliseur2);
  i2cChip i2cGpioExp((int)I2CAddGpioExpandeur);

  //Initialisation des périphériques SPI
  spiChip spiChip1((int)SPIChannelAD1);
  spiChip spiChip2((int)SPIChannelAD2);

  cout << "Fin de l'initialisation des périphériques série" << endl;

  // Boucle infinie du programme
  
  while(true)
  {
    cout << "Mode :";
    cin >> mode;

    if(mode == 0)
    {
      i2cEgaliseur1.i2cSetNull();
      spiChip1.spiSetOff();
    }

    else
    {  
      cout << "Commande ";
      cin >> read;

      if(mode == 1)
        i2cEgaliseur1.i2cWrite(read);
        
      if(mode == 2) 
        spiChip1.spiWrite(SPIPotVoie1,read);

      if(mode == 3)
        i2cGpioExp.i2cGpioLeft();

      if(mode == 4)
        i2cGpioExp.i2cGpioRight();

      if(mode == 5)
        i2cGpioExp.i2cGpioStereo();

    }

    usleep(1000*10);
  }

  cout << "FIN" << endl;
  return 0;
}