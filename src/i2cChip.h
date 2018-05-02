#ifndef I2CCHIP_H
#define I2CCHIP_H

class i2cChip
{
public:

	i2cChip();

	i2cChip(int i2cChipAddress);

	~i2cChip();

	void i2cWrite(int read);

	int i2cCmdVolume(int x1, int x0);	
		// concatène la commande pour le volume général du TDA

	int i2cCmdBande(int x2, int x1, int x0); 
		// concatène la commande par bande du TDA

	void i2cReset();

	void i2cSetNull();

private:
	int m_i2cChip;
};

#endif