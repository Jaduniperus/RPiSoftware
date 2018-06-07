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
  int stateL = 0; // Niveau du relais: 1 = fermé (contact) 0 = ouvert (pas contact)
  int stateR = 0;

  pinMode(RelayLeft, OUTPUT);
  pinMode(RelayRight, OUTPUT);

  digitalWrite(RelayRight, stateR);
  digitalWrite(RelayLeft, stateL);
  
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
      i2cGpioExp.i2cGpioAllOff();
    }

    if(mode == 3)
    {
      //i2cGpioExp.i2cGpioLeft();
      stateL++;
      if(stateL % 2 == 0)
      {
        stateL = 0;
      }
      digitalWrite(RelayLeft,stateL);
    }



    if(mode == 4)
    {
      //i2cGpioExp.i2cGpioRight();
      stateR++;
      if(stateR % 2 == 0)
      {
        stateR = 0;
      }
      digitalWrite(RelayRight,stateR);
    }

    if(mode == 5)
      //i2cGpioExp.i2cGpioStereo();
    {
      stateL = 1;
      
      digitalWrite(RelayLeft,stateL);

      stateR = 1;
     
      digitalWrite(RelayRight,stateR);
    }

    if(mode == 6)
      //i2cGpioExp.i2cGpioMute();
    {

      stateL = 0;
      
      digitalWrite(RelayLeft,stateL);

      stateR = 0;
     
      digitalWrite(RelayRight,stateR);
    
    }

    if(mode == 1)
    {
      cout << "Commande TDA ";
      cin >> read;
      i2cEgaliseur1.i2cWrite(read);
    }        
        
    if(mode == 2)
      {
        cout << "Commande AD ";
        cin >> read;
        spiChip1.spiWrite(SPIPotVoie1,read);
      }
    

    usleep(1000*10);
  }

  cout << "FIN" << endl;
  return 0;
}