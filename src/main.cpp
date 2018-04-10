#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <errno.h>
#include <wiringPiI2C.h>

#include "/home/pi/Documents/loudspeakerSoftware/src/settings.h" 

using namespace std;

int main() 
{
	int fd, result;

	// recherche du périphérique dont l'addresse I2C est 0x43 (pour TDA bass)
	fd = wiringPiI2CSetup(devIdTDABass);
    if(fd < 0)
    {
    	cout << "Error.  Errno is: " << errno << endl;
    }
    else  cout << "Init result: "<< fd << endl;

   for(int i = 0; i < 0x0000ffff; i++)
   {
      // I tried using the "fast write" command, but couldn't get it to work.  
      // It's not entirely obvious what's happening behind the scenes as
      // regards to endianness or length of data sent.  I think it's only 
      // sending one byte, when we really need two.
      //
      // So instead I'm doing a 16 bit register access.  It appears to 
      // properly handle the endianness, and the length is specified by the 
      // call.  The only question was the register address, which is the 
      // concatenation of the command (010x = write DAC output) 
      // and power down (x00x = power up) bits.
      result = wiringPiI2CWriteReg16(fd, 0x43, (i & 0xfff) );
      
      cout<<result<<endl;

      if(result == -1)
      {
         cout << "Error.  Errno is: " << errno << endl;
         break;
      }
   }
    return 0;
}

