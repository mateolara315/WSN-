/* 
 * File:   Sender.c
 * Author: Mateo Lara y Cristian Benitez
 *
 * Created on September 30, 2018, 3:14 PM
 */

#include <stdio.h> //printf, puts, putchar
#include <stdlib.h>
#include "Header.h"

// -------------------------Receiver_Of_Data_to_be_shown----------------------

// --------------------------------------------------------------------------

#define _XTAL_FREQ 4000000      // Fosc  frequency for _delay()  library

#include "SPI.h"
#include "nRF24L01.h"

/*
 Code for  data to the 
 */

void nRF_Config()
{
    config_receiver();             // set as receiver and power up
    
    auto_ack();                    // turn on auto ack !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Al final  enable auto acknowledgment
    
    Setup_retr();                  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  Auto retransmit disabled
    
    en_RXADDR();                    // enable data pipe 0 !!!!!!!!!!!!!!!!!!!!!!

    setRADDR();                    // address for pipe 0 (oxF0F0F0F0)

    setTADDR();                    // same for transmitter
    
    RF_Setup();

    payload_size();              // just 1 bytes

    setRF_CH();                    // 2.431GHz

    flushRX();                     // clear any data in RX FIFO

}

void senderF()
{
    int i = 0;
    for (i=0; i<6; i++)
    {
    //while(1){  // Cambia While con un solo intento de envio 
    unsigned char my_byte1 = 'a'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte1; //assign the value to TXREG to send 
    __delay_ms(10);
    unsigned char my_byte2 = 'b'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte2; //assign the value to TXREG to send 
    __delay_ms(10);
    unsigned char my_byte3 = 'c'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte3; //assign the value to TXREG to send 
    __delay_ms(10);
    unsigned char my_byte4 = 'd'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte4; //assign the value to TXREG to send 
    __delay_ms(10);
    unsigned char my_byte5 = 'e'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte5; //assign the value to TXREG to send 
    __delay_ms(10);
    unsigned char my_byte6 = 'y'; //message  
        while(!TXIF){ // wait for TXIF to become ready 
        continue;
    }
    TXREG = my_byte6; //assign the value to TXREG to send 
    __delay_ms(10);
    //__delay_ms(1000);
    //}
}
}
    
int main(int argc, char** argv) {
    
    /*Registers initialization*/
  
    //Init PORTS 
    
    ANSEL =  0;
    ANSELH = 0;
    
    TRISA = 0;
    PORTA = 0;
    
    TRISB = 0;
    PORTB = 0;
    TRISBbits.TRISB0 = 1;                      //IRQ pin
    
    TRISC =  0;
    PORTC = 0;
    
    //Init USART 
    OSCCON =  0b01100101; // Defining the internal oscillator 4Mhz
    SPBRG =   0b00011001; // Baud rate configuration 25 for 9600 baud
    SPBRGH =  0b00000000; // Not needed 
    TXSTA =   0b00100100; // Configuration of Tx mode  (High speed conf) 
    RCSTA =   0b10010000; // No reception required 
    BAUDCTL = 0b00000000; // Baud Control 
     
    SPI_Init();
    CEpin = 0;                           //For what this? 
    nRF_Config();                        //receive mode
    
    __delay_ms(2000);
    
    while(1)
    {
        PORTAbits.RA2 = 1;                  //test LED

        CEpin = 0;                          //0 why? 
        wait_for_data();
        read_data();                        // 2 = number of bytes
        
        PORTAbits.RA2 = 0;
        
        senderF(temp);              

        flushRX();                          //not mandatory but recommended

        nRF_write_register();               //clear the RX_DR bit from STATUS register

        __delay_ms(10);
    }
    return (EXIT_SUCCESS);
}