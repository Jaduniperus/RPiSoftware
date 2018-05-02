#ifndef I2CCHIP_H
#define I2CCHIP_H

class i2cChip
{
public:

	i2cChip();

	i2cChip(int i2cChipAddress);

	~i2cChip();

	void i2cWrite(int read);

private:
	int m_i2cChip;
};

#endif