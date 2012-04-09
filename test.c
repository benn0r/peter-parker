#include "asuro.h"

#define SPEED 0x8F

static unsigned char ocr2 = 0x91;

void init_ir(void)
{  
	DDRD |= (1 << DDD1);	// Port D1 als Ausgang
	PORTD &= ~(1 << PD1);	// PD1 auf LOW

	UCSRB = 0;
	DDRD |= (1 << DDD1);	// Port D1 als Ausgang
	PORTD &= ~(1 << PD1);	// PD1 auf LOW
	OCR2 = ocr2;
}

/**
 * Überprüft mit Infrarot ob ein Gegenstand im Weg ist. 
 * Der Check wird mehrmals durchgeführt um fehlerhafte
 * Erkennungen zu vermeiden
 *
 * @return int 1 = Kollision
 *			   0 = Keine Kollision
 */
unsigned int check_ir(void)
{
	int i;
	int none = 0;
	int collision = 0;
	
	for (i = 0; i < 20; i++) {
		UCSRB = 0;
		OCR2 = 0xFE;
		
		if (PIND & (1 << PD0)) {
			none++; // Keine Kollision
		} else {
			collision++; // Kollision entdeckt
		}
		
		Msleep(50);
	}
	
	if (none == 0 || collision > none) {
		return 1; // Kollision
	} else {
		return 0;
	}
}

unsigned int get_color(void)
{
	unsigned int lineData[2], i, total;
	
	total = 0;
	for (i = 0; i < 100; i++) {
		LineData(lineData);
		total += lineData[LEFT] + lineData[RIGHT];
	}
	
	return total / 100;
}

int calc_offset(void)
{
	unsigned int lineData[2], j;
	
	for (j = 0; j < 0xFF; j++) LineData(lineData);
	LineData(lineData);
	
	int offset = lineData[LEFT] - lineData[RIGHT];
	
	SerPrint("Calibration Offset: ");
	PrintInt(offset);
	SerPrint("\r\n");
	
	return offset;
}

unsigned int calc_color(int offset)
{
	unsigned int lineData[2];
	
	LineData(lineData);	
    return (lineData[LEFT] - lineData[RIGHT]) - offset;
}

int main(void)
{
	Init();
	
	// IR Sensor für Kollisions-Test einbinden
	init_ir();
	
	/*unsigned int debug = get_color();
	SerPrint("Color Debug: ");
	PrintInt(debug);
	SerPrint("\r\n");
	
	int offset = calc_offset();*/
	
	while(1) {
		StatusLED(GREEN);
		if (check_ir()) {
			// Kollision
			BackLED(ON, ON);
		} else {
			// Keine Kollision
			BackLED(OFF, OFF);
		}
		StatusLED(OFF);
		
		// Nächster Ckeck
		Msleep(1000);
	}
	
	while(1) {
		/*unsigned int color = calc_color(offset);
		
		if (color < -4)
		{
			SetMotorPower(60, 60);
			MotorSpeed(150, 150);
		}
		else
		{
			SetMotorPower(0, 0);
			MotorSpeed(0, 0);
		}*/
	}
	
	
	/*
	int speedLeft,speedRight;
unsigned int lineData[2];
int ADOffset;

void LineLeft (void)
{
  speedLeft  += 1;     
  if (speedLeft > 0xFE) speedLeft = 0xFF;
}

void LineRight (void)
{
  speedRight  += 1;  
  if (speedRight > 0xFE) speedRight = 0xFF;
}*/
	
  /*int i;
  unsigned char j;

  Init();

  FrontLED(ON);
  
  for (j = 0; j < 0xFF; j++) LineData(lineData);
  LineData(lineData);
  
  
  ADOffset = lineData[LEFT] - lineData[RIGHT];
  speedLeft = speedRight = SPEED;
  for (;;)
  {
    LineData(lineData);
    i = (lineData[LEFT] - lineData[RIGHT]) - ADOffset;
    if ( i > 4)
    {
		StatusLED(GREEN);
		SetMotorPower(60, 60);
		speedLeft = speedRight = SPEED;
    }
    else if ( i < -4)
    {
		StatusLED(RED);
		SetMotorPower(0, 0);
		speedLeft = speedRight = 0;
    }
    else
    {
      StatusLED(OFF);
      speedLeft = speedRight = SPEED;
    }
    MotorSpeed(speedLeft, speedRight);
  }*/
  
  return 0;
}