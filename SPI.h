/* 
 * File:   SPI.h
 * Author: Mateo Lara y Cristian Benitez 
 *
 * Created on October 21, 2018, 8:12 PM
 */

#ifndef SPI_H
#define	SPI_H

#define ChipSelect PORTDbits.RD2 
#define ChipSelect_dir TRISDbits.TRISD2 
#define SDOpin_dir TRISCbits.TRISC5 
#define SDIpin_dir TRISCbits.TRISC4 
#define SCKpin_dir TRISCbits.TRISC3 
#define SSpin_dir  TRISAbits.TRISA5    
unsigned short int temp; 

void SPI_Init()
{    
     //SSPCONbits.SSPEN = 0;  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     
     SSPCON = 0x20;             // SPI Master mode, clock = Fosc/4 !!!!!!!!!!!! 0X00
     SSPSTAT= 0x00;             // CKE = 1   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 0x040 
     
     SDOpin_dir = 0;            //data out
     SDIpin_dir = 1;            //data in
     SCKpin_dir = 0;            //clock
     SSpin_dir  = 1;
     ChipSelect_dir = 0;        //ChipSelect as output
     
     //SSPCONbits.SSPEN = 1;          //enable SPI  !!!!!!!!!!!!!!!!!!!!!!!!!!!!
     ChipSelect = 1;
}

short int SPI_write (short int addr)
{
    SSPBUF = addr;           // send data to the BUFFER
    
    while(!SSPSTATbits.BF && !PIR1bits.SSPIF); 
    //wait for the tramsit/recieve to finish has to be SSPSTAT.BF not 
    //just BF!! (for some reason)
    temp = SSPBUF;   // clear the BF flag
    
    PIR1bits.SSPIF = 0;
    
    //__delay_ms(100);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    return temp; //!!! Save in memory 
}

short int SPI_read()
{

      SSPBUF = 0xFF;           // send a dummy byte

      while(!SSPSTATbits.BF && !PIR1bits.SSPIF);

      temp = SSPBUF;

      PIR1bits.SSPIF = 0;
      
       //__delay_ms(100);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      return temp;

}

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */