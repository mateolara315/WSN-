/* 
/* 
 * File:   nRF24L01.h
 * Author: Mateo Lara y Cristian Benitez 
 *
 * Created on October 21, 2018, 11:41 PM
 */

#ifndef NRF24L01_H
#define	NRF24L01_H

#ifdef	__cplusplus
extern "C" {
#endif

#define R_RX_PAYLOAD 0b01100001 

#define T_TX_PAYLOAD 0b10100000

#define FLUSH_TX 0b11100001

#define FLUSH_RX 0b11100010

#define NOP1 0b11111111 

#define CEpin  PORTDbits.RD1 

#define CEpin_dir TRISDbits.TRISD1

#define IRQ PORTBbits.RB0

//char byte[10];

    void config_receiver()

{

     CEpin_dir = 0;                     // CE pin output

     ChipSelect = 0;

     SPI_write(0x20);                   // write CONFIG

     SPI_write(0b00110011);             // receiver  !!!!!!!!!!!!!!!!!!!!!!!!!!! 0b00110011 

     ChipSelect = 1;

     CEpin = 0;                          //0 why? 

}

void config_transmiter()

{

     CEpin_dir = 0;                     // CE pin output

     ChipSelect = 0;

     SPI_write(0x20);                   // write CONFIG

     SPI_write(0b01010010);             // transmitter  !!!!!!!!!!!!!!!!!!!!!!!! 0b00110011

     ChipSelect = 1;

}

void setRADDR()

{
     ChipSelect = 0;
     
     SPI_write(0x23);
     
     SPI_write(0x03);                  // Address field with 5 bytes 
     
     ChipSelect = 1;
     
     __delay_ms(10);

     ChipSelect = 0;

     SPI_write(0x2A);                   // write receiver address

     SPI_write(0xF0);                   // for pipe 0

     SPI_write(0xF0);                   // address: 0xF0F0F0F0F0

     SPI_write(0xF0);

     SPI_write(0xF0);

     SPI_write(0xF0);

     ChipSelect = 1;

}

void setTADDR()

{
     ChipSelect = 0;

     SPI_write(0x30);                   // write transmitter address

     SPI_write(0xF0);                   // same as receiver

     SPI_write(0xF0);                   // address: 0xF0F0F0F0F0

     SPI_write(0xF0);

     SPI_write(0xF0);

     SPI_write(0xF0);

     ChipSelect = 1;

}

void payload_size() // short int x

{

     ChipSelect = 0;

     SPI_write(0x31);                   // setting the number of bytes (x)

     SPI_write(0x01);                      // in RX payload for pipe 0

     ChipSelect = 1;

}

void setRF_CH()

{

     ChipSelect = 0;

     SPI_write(0x25);                   // RF Channel

     SPI_write(0x1F);                   // 2.4 + 0.031 = 2.431GHz 

     ChipSelect = 1;

}

void flushRX()

{

     ChipSelect = 0;

     SPI_write(FLUSH_RX);                   // Flush RX

     ChipSelect = 1;

}

void flushTX()

{

     ChipSelect = 0;

     SPI_write(FLUSH_TX);                   // Flush TX

     ChipSelect = 1;

}

void auto_ack()

{
    

     ChipSelect = 0;

     SPI_write(0x21);                   // write EN_AA

     SPI_write(0x00);                      // disable/enable auto-ack 3F !!!!!!!!!!!!!!!!!!!!!!! 

     ChipSelect = 1;

}

 

void nRF_write_register() //char reg, char pod

{

     ChipSelect = 0;

     SPI_write(0x27);                    //reg register which to write

     SPI_write(0x40);                    //pod data to write  to register

     ChipSelect = 1;

}

 

char nRF_read_register(char reg)

{

     char pod;

     ChipSelect = 0;

     SPI_write(reg);

     pod = SPI_read();

     ChipSelect = 1;

     return pod;

}

 

void send_data() //short int number_of_bytes

{

     //int k;

     ChipSelect = 0;                              // announce the transmission

     SPI_write(T_TX_PAYLOAD);           // write the command byte

     SPI_write(0b01010101);
     
     //for(k = 0; k < number_of_bytes; k++) SPI_write(byte[k]);
     
     //SPI_write(0b01101100);

     ChipSelect = 1;

 

     CEpin = 1;

     __delay_us(20) ;           // send the payload

     CEpin = 0;

}

 

void read_data()

{

     //int k;

     ChipSelect = 0;

     SPI_write(R_RX_PAYLOAD);              // command byte (read data)

     //for(k = 0; k < x; k++) byte[k] = SPI_read();
     SPI_read();
     
     ChipSelect = 1;

}

void read_address(char x)

{   

     ChipSelect = 0;

     SPI_write(x);

     SPI_write(NOP1);           // 5 dummy bytes

     SPI_write(NOP1);

     SPI_write(NOP1);

     SPI_write(NOP1);

     SPI_write(NOP1);

     ChipSelect = 1;

}

void en_RXADDR()

{

     ChipSelect = 0;

     SPI_write(0x22);                   // write EN_RXADDR

     SPI_write(0x01);                      // disable/enable pipes 0

     ChipSelect = 1;

}

void wait_for_data()

{

     CEpin = 1;                        //receive mode

     while(IRQ){}                      //waiting for IRQ to go low

     CEpin = 0;
     
     __delay_us(20) ;           // send the payload

}
void RF_Setup()
{
    
     ChipSelect = 0;

     SPI_write(0x26);                   // write RF_SETUP

     SPI_write(0x26);                   // Set as 250kbps 0dbm TX power

     ChipSelect = 1;
    
}

void Setup_retr()
{
    
     ChipSelect = 0;

     SPI_write(0x24);                   

     SPI_write(0x00);                   // Auto retransmit disabled 

     ChipSelect = 1;    
}


#ifdef	__cplusplus
}
#endif

#endif	/* NRF24L01_H */
