#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/spiChip.h"

spiChip::spiChip(int spiChipChannel)
{
  m_spiChipChannel = spiChipChannel;
  m_spiChip = wiringPiSPISetup(m_spiChipChannel, SPISpeed);
  spiSetup();
}

spiChip::~spiChip()
{
}

void spiChip::spiWrite(int pot, int level)
{
  // DEMUTER AMPLI SI LEVEL != 0
  m_buff[0] = pot;
  m_buff[1] = level;
  wiringPiSPIDataRW(m_spiChip, m_buff, sizeof(m_buff));
}

void spiChip::spiSetup()
{  
  spiSetOff();
}

void spiChip::spiSetMed()
{
  int z;
  for(z=0; z<4; z++)
  {
    spiWrite(z,SPIADVolMed);
  }

  std::cout << "Toutes les sorties du AD sont à mi-niveaux" << std::endl;
}

void spiChip::spiSetMax()
{
  int z;
  for(z=0; z<4; z++)
  {
    spiWrite(z,SPIADVolMax);
  }

  std::cout << "Toutes les sorties du AD sont au niveaux max" << std::endl;
}

void spiChip::spiSetOff()
{
  int z;
  for(z=0; z<4; z++)
  {
    spiWrite(z,SPIADVolMin);
  }

  // AJOUTER LA COMMANDE POUR STANDBY LES AMPLIS

  std::cout << "Toutes les sorties du AD sont coupées" << std::endl;
}

void spiChip::spiRainbow()
{
  std::cout << "Augmentation du volume" << std::endl;
  for (int i = SPIADVolMin; i < SPIADVolMax; --i)
  {
    spiWrite(SPIPotVoie1,i);
    usleep(1000*5);
  }

  std::cout << "Diminution du volume" << std::endl;
  for (int i = SPIADVolMax; i < SPIADVolMin; ++i)
  {
    spiWrite(SPIPotVoie1,i);
    usleep(1000*5);
  }
}