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

	void i2cGpioSetup();

	void i2cSetNull();

	void i2cGpioWrite(int numPin, int state);

	void i2cGpioWriteMode(int r1, int r2);

	void i2cGpioSwitch(int numPin);

	void i2cGpioAllOff();

	void i2cGpioAllOn();

	void i2cGpioLeft();
	void i2cGpioRight();
	void i2cGpioStereo();
	void i2cGpioMute();

private:
	int m_i2cChip;
	int m_i2cGpioId;
};

#endif