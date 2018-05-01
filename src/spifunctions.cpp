#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/spifunctions.h" 

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