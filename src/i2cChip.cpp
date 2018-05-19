#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cChip.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cCommands.h"

i2cChip::i2cChip()
{
}

i2cChip::i2cChip(int i2cChipAddress)
{
	if (i2cChipAddress == I2CAddEgaliseur1 || 
		i2cChipAddress == I2CAddEgaliseur2)
	{
		m_i2cChip = wiringPiI2CSetup(i2cChipAddress);
		i2cSetNull();
	}

	if (i2cChipAddress == I2CAddGpioExpandeur)
	{
		m_i2cGpioId = I2CGPIOID;
		mcp23017Setup (m_i2cGpioId, I2CAddGpioExpandeur);
			// initialise la com
		i2cGpioSetup();
			// initialise les pins
	}

	std::cout << "Chip i2c " 
			  << i2cChipAddress 
			  << " initialisé" 
			  << std::endl;		
}

i2cChip::~i2cChip()
{
}

void i2cChip::i2cWrite(int read)
{
	wiringPiI2CWrite(m_i2cChip, read);
}

int i2cChip::i2cCmdVolume(int x1, int x0)
{
  return x1 + x0;
}

int i2cChip::i2cCmdBande(int x2, int x1, int x0)
{
  return 128 + x2 + x1 + x0;
}

void i2cChip::i2cReset()
{
	// Met le volume général à -17,25 dB
	i2cWrite(i2cCmdVolume(TDAVOLUME15DB, TDAVOL2625DB));
	// Met le niveau de chaque bande à -14 dB
	i2cWrite(i2cCmdBande(TDABANDE1, TDACUT, TDABANDE14DB));
	i2cWrite(i2cCmdBande(TDABANDE2, TDACUT, TDABANDE14DB));
	i2cWrite(i2cCmdBande(TDABANDE3, TDACUT, TDABANDE14DB));
	i2cWrite(i2cCmdBande(TDABANDE4, TDACUT, TDABANDE14DB));
	i2cWrite(i2cCmdBande(TDABANDE5, TDACUT, TDABANDE14DB));

	std::cout << "Toutes les niveaux du TDA sont au minimum" << std::endl;
}

void i2cChip::i2cSetNull()
{
	// Met le volume général à 0 dB
	i2cWrite(i2cCmdVolume(TDAVOLUME0DB, TDAVOLUME0DB));
	// Met le niveau de chaque bande à 0 dB
	i2cWrite(i2cCmdBande(TDABANDE1, TDABOOST, TDABANDE0DB));
	i2cWrite(i2cCmdBande(TDABANDE2, TDABOOST, TDABANDE0DB));
	i2cWrite(i2cCmdBande(TDABANDE3, TDABOOST, TDABANDE0DB));
	i2cWrite(i2cCmdBande(TDABANDE4, TDABOOST, TDABANDE0DB));
	i2cWrite(i2cCmdBande(TDABANDE5, TDABOOST, TDABANDE0DB));

	std::cout << "Toutes les niveaux du TDA sont à zero" << std::endl;
}

void i2cChip::i2cGpioSetup()
{
	for (int i = 0 ; i < 16 ; ++i) 
		pinMode (m_i2cGpioId + i, OUTPUT) ;
}

void i2cChip::i2cGpioWrite(int numPin, int state)
{
	digitalWrite(m_i2cGpioId + numPin, state);
}

void i2cChip::i2cGpioSwitch(int numPin)
{
	//digitalWrite(m_i2cGpioId + numPin);
}

void i2cChip::i2cGpioAllOff()
{
	for(int z = 0; z < 16 ; ++z) 
		{
			i2cGpioWrite(z,GPIOOPEN);
			usleep(1000*100);
		}
}

void i2cChip::i2cGpioAllOn()
{
	for(int z = 0; z < 16 ; ++z) 
		{
			i2cGpioWrite(z,GPIOCLOSE);
			usleep(1000*100);
		}
}

void i2cChip::i2cGpioWriteMode(int r1, int r2)
{
	i2cGpioWrite(0,r1);
	i2cGpioWrite(1,r2);
}

void i2cChip::i2cGpioLeft()
{
	i2cGpioWriteMode(GPIOCLOSE,GPIOOPEN);
}

void i2cChip::i2cGpioRight()
{
	i2cGpioWriteMode(GPIOOPEN,GPIOCLOSE);
}

void i2cChip::i2cGpioStereo()
{
	i2cGpioWriteMode(GPIOCLOSE,GPIOCLOSE);
}

void i2cChip::i2cGpioMute()
{
	i2cGpioWriteMode(GPIOOPEN,GPIOOPEN);
}