#ifndef SPICHIP_H
#define SPICHIP_H

class spiChip
{
public:

	spiChip(int spiChipAddress);

	~spiChip();

	void spiWrite(int pot, int level); // fct envoie un packet de données

	void spiSetup();

	void spiSetMed();

	void spiSetMax();

	void spiSetOff();

	void spiAllOff(); 
		// met toutes les voies au minimum de volume a un seul AD a la fois

	void spiRainbow();

private:
	int m_spiChip; // identifiant du composant
	int m_spiChipChannel; // bus utilisé sur le RPi
	uint8_t m_buff[2];  
		// buffer contenant les données a transmettre au AD
		// m_buff[0] : num du potentiomètre (0 - 1 - 2 - 3)
		// m_buff[1] : niveau de résistance à appliquer (compris entre 0 et 98)
};

#endif