#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cChip.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cCommands.h"

i2cChip::i2cChip()
{
}

i2cChip::i2cChip(int i2cChipAddress)
{
	m_i2cChip = wiringPiI2CSetup(i2cChipAddress);
	i2cSetNull();
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