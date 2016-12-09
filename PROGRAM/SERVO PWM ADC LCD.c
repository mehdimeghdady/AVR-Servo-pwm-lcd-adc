/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 3/9/2015
Author  : MEM
Company :
Comments:


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>

#include <delay.h>
#include <stdio.h>
// Alphanumeric LCD functions
#include <alcd.h>

#define ADC_VREF_TYPE 0x40

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here

void main(void)
{
 char lcdi[10],lcdj[10];
unsigned int i;
unsigned int j;
PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0xff;
PORTC=0x00;
DDRC=0x00;
PORTD=0x00;
DDRD=0xff;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 2000.000 kHz
// Mode: Ph. & fr. cor. PWM top=ICR1
// OC1A output: Non-Inv.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
TCCR1A=0x80;
TCCR1B=0x12;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x4E;
ICR1L=0x20;
OCR1A=1000;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x84;



// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);

while (1)
      {

      i=read_adc(0);
      j=i*3;
      if (j<500)
      j=500;
      if (j>2400)
      j=2400;
      OCR1A=j;
      sprintf(lcdj,"m=%u ",j);
       //OCR1A=i;
       lcd_gotoxy(0,0);
       lcd_puts(lcdj);
       sprintf(lcdi,"v=%u ",i);
       //OCR1A=i;
       lcd_gotoxy(0,1);
       lcd_puts(lcdi);
       lcd_clear();
       delay_ms(1);
      }
}
