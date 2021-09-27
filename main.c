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
void teclado();

void main(void) {
    TRISE = 0; //Porta de saida para ligar o buzzer
    TRISD = 0; //liga a porta do display
    TRISB = 0x0F; //pinagem do teclado
    
    PORTE = 0x01; //desligando o buzzer = 0000 0001
    
    LCD_init();
    LCD_limpa();
    
    
    while (1){
        teclado();
        
    }
}

void liga_buzzer(){
    __delay_ms(10);
    PORTE = 0;

}

void teclado(){
    
    PORTE = 0x01;
    // ***
    // Verificação da primeira linha do teclado
    // ***
    PORTB = 0b11101111; // verifica a primeira linha (botão 0,1,2,3,4)
    // ***
    // Numero 0
    // ***
    if (RB0 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('0');
          
    }
    // ***
    // Numero 1
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('1');
        
    }

    // ***
    // Numero 2
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('2');
        
    }
    // ***
    // Numero 3
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('3');
       
    }

    // ***
    // Verificação da segunda linha do teclado
    // ***
    PORTB = 0b11011111; // verificando a segunda linha

    // ***
    // Numero 4
    // ***
    if (RB0 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('4');
       
    }
    // ***
    // Numero 5
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('5');
       
    }

    // ***
    // Numero 6
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('6');

    }
    // ***
    // Numero 7
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('7');
        
    }

    // ***
    // Verificação da terceira linha do teclado
    // ***
    PORTB = 0b10111111;

    // ***
    // Numero 8
    // ***
    if (RB0 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('8');
        
        
    }
    // ***
    // Numero 9
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('9');
        
    }
    
    // ***
    // Letra A
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('A');
        
    }
    
    // ***
    // Letra B
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('B');
        
    }
    
    // ***
    // Verificação da quarta linha do teclado
    // ***
    PORTB = 0b01111111;

    // ***
    // Letra C
    // ***
    if (RB0 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('C');
        
    }
    
    // ***
    // Letra D
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('D');
        
    }
    
    // ***
    // Letra E
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('E');
        
    }
    
    // ***
    // Letra F
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('F');
        
    }
    
}