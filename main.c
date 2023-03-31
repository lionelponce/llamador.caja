/* 
 * File:   main.c
 * Author: Tecnicos
 * Title: Indicador Caja v2
 *
 * Created on October 16, 2014, 9:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000

void ButtonLamp(char Lamp){
    switch(Lamp){
        case 1:
            PORTA = 0x40;
            break;
        case 2:
            PORTA = 0x80;
            break;
        case 3:
            PORTA = 0x01;
            break;
        default:
            PORTA = 0xC1;
            break;
    }
}

void Bell(char Times){
    char i=0;
    for(i==0; i<Times; i++){
        PORTBbits.RB0 = 1;
        __delay_ms(20);
        PORTBbits.RB0 = 0;
        __delay_ms(230);
    }
}

void Show(char Number){
    char n=0;
    switch(Number){
        case 1:
            n = 0x0C;
            break;
        case 2:
            n = 0xB6;
            break;
        case 3:
            n = 0x9E;
            break;
        default:
            n = 0x80;
            break;
    }
    char i=0;
    for(i==0; i<3; i++){
        __delay_ms(400);
        PORTB = 0;
        __delay_ms(400);
        PORTB = n;
    }
}

void main(void){
//  Configuracion
    PCONbits.OSCF = 1;
    CMCON = 0x07;
    TRISA = 0x3C;
    TRISB = 0x00;
    PORTA = 0;
    PORTB = 0;

//  Programa
    ButtonLamp(0);
    Bell(2);
    Show(0);
    while(1){
        if(PORTAbits.RA2==0){
            ButtonLamp(2);
            Bell(3);
            Show(2);
            while(PORTAbits.RA2==0){
            };
        }
        if(PORTAbits.RA3==0){
            ButtonLamp(3);
            Bell(3);
            Show(3);
            while(PORTAbits.RA3==0){
            };
        }
        if(PORTAbits.RA4==0){
            ButtonLamp(1);
            Bell(3);
            Show(1);
            while(PORTAbits.RA4==0){
            };
        }
    };
}

