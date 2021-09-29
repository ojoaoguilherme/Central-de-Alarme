/*
 * File:   main.c
<<<<<<< HEAD
 * Author: joaog / joaos
 *
=======
 * Author 1: João Guilherme, RU: 2824600
 * Author 2: João Vitor, RU: -------
>>>>>>> 6e707d99e09842097be116995a87e8bc8f39a05a
 * Created on 27 de Setembro de 2021, 01:31
 */

#define _XTAL_FREQ 20000000
#include <pic16f877a.h>
#include <string.h>
#include "lcd.h"
#include <xc.h>

void liga_buzzer(float tempoSegundos);
void teclado();
void telaInicial();
void Linha2();
void espacoLivre();
int validaUser();


//Usuario
char senhaUser[5];
char senhaCoa[5];
char senhaConfig[5];

//Config
int painel = 1;
int userFalse = 1;
int config = 0;

//Interface
char msg[15] = "Digite a senha";
char msg2[5] = "____";

void main(void) {
    TRISE = 0; //Porta de saida para ligar o buzzer
    TRISD = 0; //liga a porta do display
    TRISB = 0x0F; //pinagem do teclado
    
    PORTE = 0x01; //desligando o buzzer = 0000 0001
    
    //Sequencia de inicialização do LCD
    LCD_init();
    LCD_limpa();
    
    
    while (1){

        if (painel){
            telaInicial();
            Linha2();
            painel = 0;
        }

        while(userFalse){

            userFalse = validaUser();
            
        }
        
        teclado();
        
        
        
    }
}

void liga_buzzer(float tempoSegundos){
    tempoSegundos = tempoSegundos * 1000;
    __delay_ms(10);
    
    //defini quanto tempo queremos o buzzer ligado
    while(tempoSegundos > 0){
       PORTE = 0;
        __delay_ms(1);
        tempoSegundos--;

    }
    
    PORTE = 0x0F;

}

// Mapeamento dos teclados
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
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('0');
          
    }
    // ***
    // Numero 1
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('1');
        
    }

    // ***
    // Numero 2
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('2');
        
    }
    // ***
    // Numero 3
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
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
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('4');
       
    }
    // ***
    // Numero 5
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('5');
       
    }

    // ***
    // Numero 6
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('6');

    }
    // ***
    // Numero 7
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
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
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('8');
        
        
    }
    // ***
    // Numero 9
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('9');
        
    }
    
    // ***
    // Letra A
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('A');
        
    }
    
    // ***
    // Letra B
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
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
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('C');
        
    }
    
    // ***
    // Letra D
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('D');
        
    }
    
    // ***
    // Letra E
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('E');
        
    }
    
    // ***
    // Letra F
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('F');
        
    }
    
}

//Função que escreve na tela "Digite sua senha" centralizado no LCD
void telaInicial(){
    
    LCD_linha1();
    LCD_escreve(' ');
    for (int i = 0; i <= strlen(msg)-1; i++){
        LCD_escreve(msg[i]);
    }
    LCD_escreve(' ');
    
    
}

// Para fundionar o teclado e atualização da função espaçoLivre 
// deve separar o painel em duas partes como "Digite sua senha" sendo estatico
// e "_ _ _ _" sendo atualizada a cada numero inserido 
void Linha2(){
    LCD_linha2();
    espacoLivre();
    for (int i = 0; i <= strlen(msg2)-1; i++){
        LCD_escreve(msg2[i]);  
    }
    espacoLivre();
    
}

// Usado para centralizar os digitos a serem inseridos no painel
// exemplo: "_ _ _ _" quando inserir = "1 _ _ _"
void espacoLivre(){
    LCD_linha2();
    LCD_escreve(' ');
    LCD_escreve(' ');
    LCD_escreve(' ');
    LCD_escreve(' ');
    LCD_escreve(' ');
    LCD_escreve(' ');
    
}

int validaUser(){
    int valor = 0;
    __delay_ms(100);
    liga_buzzer(1);
    
    return valor;
}

