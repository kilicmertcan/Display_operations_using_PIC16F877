#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF        // FLASH Program Memory Write Enable (Unprotected program memory may not be written to by EECON control)

#include <xc.h>

unsigned int j = 0;
const unsigned char disp[] = {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char thousands = 0;
unsigned char hundreds  = 0;
unsigned char tens = 0;
unsigned char ones  = 0;

void scan(void){
        PORTC = 0x0E;
        PORTB = disp[ thousands  ];
        for(j=0; j<600; j++);
        PORTC = 0x0D;
        PORTB = disp[ hundreds  ];
        for(j=0; j<600; j++);
        PORTC = 0x0B;
        PORTB = disp[ tens ];
        for(j=0; j<600; j++);
        PORTC = 0x07;
        PORTB = disp[ ones  ];
        for(j=0; j<600; j++);
    }

void main(void) {
    TRISB = 0;
    TRISC = 0;
    PORTC = 0x3F;
    
    while(1){
        scan();
        if(RD0){
            ones ++;
            if(ones  == 10){ones  = 0;tens++;}
            if(tens == 10){tens = 0;hundreds ++;}
            if(hundreds  == 10){hundreds  = 0;thousands ++;}
            if(thousands  == 10)thousands  = 0;
            while(RD0)scan();
        }
        if(RD1){
            ones --;
            if(ones  == 255){ones  = 9;tens--;}
            if(tens == 255){tens = 9;hundreds --;}
            if(hundreds  == 255){hundreds  = 9;thousands --;}
            if(thousands  == 255)thousands  = 9;
            while(RD1)scan();            
        }
        if(RD2){
            thousands  = 0;
            hundreds  = 0;
            tens = 0;
            ones  = 0;
            while(RD2)scan();
        }
    }
    return;
}
