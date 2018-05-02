#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/spiChip.h" 


spiChip::spiChip()
{
  spiSetup();
}

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
  m_buff[0] = pot;
  m_buff[1] = level;
  wiringPiSPIDataRW(m_spiChip, m_buff, sizeof(m_buff));
}

void spiChip::spiAllOff()
{
  int z;
  for(z=0; z<4; z++)
  {
    spiWrite(z,SPIADVolMin);
  }
}

void spiChip::spiSetup()
{  
  spiAllOff();  
  std::cout << "Toutes les voies des AD5204 sont au minimum" << std::endl;
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