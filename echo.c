#include <18F4620.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

int FlagSerial=0, FlagEnter=0;
char caracter;

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

#INT_RDA
void isr_rda (void)
{
   FlagSerial=1;
   caracter = getc();
}

void main()
{
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   set_tris_c(0x80);
   while(TRUE)
   {
      if(FlagSerial==1)
      {
         printf("%c,%u,%x  ",caracter,caracter,caracter);
         printf("%c,%u,%x  ",caracter+1,caracter+1,caracter+1);
         FlagSerial=0;
      }
   }

}
