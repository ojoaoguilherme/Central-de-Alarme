/*
 * File:   main.c
 * Author: joaog
 *
 * Created on 27 de Setembro de 2021, 01:31
 */

#define _XTAL_FREQ 20000000
#include <pic16f877a.h>
#include <string.h>
#include "lcd.h"
#include <xc.h>

void liga_buzzer();

void main(void) {
    TRISE = 0; //Porta de saida para ligar o buzzer
    TRISD = 0; //liga a porta do display
    
    PORTE = 0x01; //desligando o buzzer = 0000 0001
    
    LCD_init();
    LCD_limpa();
    
    
    while (1){
        liga_buzzer();
        
    }
}

void liga_buzzer(){
    __delay_ms(10);
    PORTE = 0;

}