#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <mcp23017.h>

// Definition des pin GPIO utilisées
#define RelayRight 1
#define RelayLeft 0

// Definitions des constantes pour l'I2C

#define I2CAddEgaliseur1 0x43 // Adresse du TDA gérant le filtre grave
#define I2CAddEgaliseur2 0x42  // Adresse du TDA gérant le filtre aïgu
#define I2CAddGpioExpandeur 0x20
#define I2CGPIOID 100

// Definitions des constantes pour le SPI

#define SPIADVolMax 0 // Potentiomètre réglé au minimum => maximum de son
#define SPIADVolMed 49 // Potentiomètre réglé au minimum => maximum de son
#define SPIADVolMin 98 // Potentiomètre réglé au maximum => minimum de son
#define SPIChannelAD1 0 // Chip sur bus SPI0
#define SPIChannelAD2 1 // Chip sur bus SPI1
#define SPISpeed 1000000

#define SPIPotVoie1 0
#define SPIPotVoie2 1
#define SPIPotVoie3 2
#define SPIPotVoie4 3
#define SPIPotVoie5 0
#define SPIPotVoie6 1
#define SPIPotVoieSub 2

#endif