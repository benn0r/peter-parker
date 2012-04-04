/***************************************************************************
 *
 * File Name:   kollisiontest.c
 * Project  :   ASURO
 *
 * Description: Kollisionstest mit Hilfe der Tastensensoren
 *
 * Ver.     Date         Author               Comments
 * -------  ----------   -----------------    ------------------------------
 * 1.0      10.09.2005   m.a.r.v.i.n          initial build
 * 1.1      08.01.2006   m.a.r.v.i.n          2x PollSwitch + Vergleich,
 *                                            anstelle 8x PollSwitch
 *
 * benoetigt die modifizierte Asuro Bibliothek 'asuro.c'
 * von waste, stochri und andun. Zu finden bei www.roboternetz.de
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"



int main(void)
{
  unsigned char t1;
  unsigned int c = 0;

  Init();
  while (1)
  {
    t1 = PollSwitch();
	
    if (t1 == 1)
    {
	  c = c + 1;
	  BackLED(ON, ON);
	  Msleep(1000);
    }
	else
	{
		if (c > 0)
		{
			BackLED(OFF, OFF);
			SerPrint("Gestoppt: ");
			PrintInt(c);
			SerPrint("\r\n");
			c = 0;
		}			
		
		/*while(c > 0)
		{
			FrontLED(ON);
			Msleep(500);
			FrontLED(OFF);
			Msleep(500);
			c--;
		}*/
	}		
  }
  
  return 0;
}

