#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 
#include "/home/pi/Documents/loudspeakerSoftware/src/i2cChip.h" 

i2cChip::i2cChip()
{
}

i2cChip::i2cChip(int i2cChipAddress)
{
	m_i2cChip = wiringPiI2CSetup(i2cChipAddress);
}

i2cChip::~i2cChip()
{
}

void i2cChip::i2cWrite(int read)
{
	wiringPiI2CWrite(m_i2cChip, read);
}
