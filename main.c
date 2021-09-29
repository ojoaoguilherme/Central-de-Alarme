/*
 * File:   main.c
 * Author 1: João Guilherme, RU: 2824600
 * Author 2: João Vitor, RU: 2815080
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
void validaUser();


//Usuario
int input = 10;
char *aux;
char senhaUser[5] = "1212";
char senhaUserConfere[5];
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

        if (userFalse == 1){
            validaUser(); 
        }
        int a = 3;
        while (a > 0){
            LCD_escreve('E');
            a--;
        }

//        LCD_linha1();
//        
//        if(userFalse == 0){
//            LCD_escreve('X');
//        }else {
//            LCD_escreve('L');
//            LCD_escreve('o');
//            LCD_escreve('g');
//            LCD_escreve('a');
//            LCD_escreve('d');
//            LCD_escreve('o');
//            
//        }
        
          
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
        
        if(userFalse == 1){
            input = 0;
        }
        
        LCD_escreve('0');
        LCD_escreve('0');
        LCD_escreve('0');
        LCD_escreve('0');
          
    }
    // ***
    // Numero 1
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('1');
        
        if(userFalse == 1){
            input = 1;
        }
        
    }

    // ***
    // Numero 2
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('2');
        
        if(userFalse == 1){
            input = 2;
        }
        
    }
    // ***
    // Numero 3
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('3');
        
        if(userFalse == 1){
            input = 3;
        }
       
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
        
        if(userFalse == 1){
            input = 4;
        }
       
    }
    // ***
    // Numero 5
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('5');
        
        if(userFalse == 1){
            input = 5;
        }
       
    }

    // ***
    // Numero 6
    // ***
    if (RB2 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('6');
        
        if(userFalse == 1){
            input = 6;
        }

    }
    // ***
    // Numero 7
    // ***
    if (RB3 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('7');
        
        if(userFalse == 1){
            input = 7;
        }
        
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
        
        if(userFalse == 1){
            input = 8;
        }
        
        
    }
    // ***
    // Numero 9
    // ***
    if (RB1 == 0){
        __delay_ms(200);
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('9');
        
        if(userFalse == 1){
            input = 9;
        }
        
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

void validaUser(){
    int n = 3;
    while( userFalse == 1 ){
        while(n > 0){
            
            if(n == 1){
                LCD_escreve('U');
                LCD_escreve('l');
                LCD_escreve('t');
                LCD_escreve('i');
                LCD_escreve('m');
                LCD_escreve('a');
                LCD_escreve(' ');
                LCD_escreve('C');
                LCD_escreve('h');
                LCD_escreve('a');
                LCD_escreve('n');
                LCD_escreve('c');
                LCD_escreve('e');
                liga_buzzer(2);
            }
            
            while (input == 10){
                teclado();
            }
        
        
            switch (input){

                case 1: 
                    aux = "1";
                break;
                case 2: 
                    aux = "2";
                break;
                case 3: 
                    aux = "3";
                break;
                case 4: 
                    aux = "4";
                break;
                case 5: 
                    aux = "5";
                break;
                case 6: 
                    aux = "6";
                break;
                case 7: 
                    aux = "7";
                break;
                case 8: 
                    aux = "8";
                break;
                case 9: 
                    aux = "9";
                break;
                case 0: 
                    aux = "0";
                break;

            };
            strcat(strcpy(senhaUserConfere, senhaUserConfere), aux);
            
            if (strcmp(senhaUser, senhaUserConfere) == 0){
                userFalse = 0;
                LCD_escreve('S');
                LCD_escreve('e');
                LCD_escreve('n');
                LCD_escreve('h');
                LCD_escreve('a');
                LCD_escreve(' ');
                LCD_escreve('c');
                LCD_escreve('o');
                LCD_escreve('r');
                LCD_escreve('r');
                LCD_escreve('e');
                LCD_escreve('t');
                LCD_escreve('a');
                __delay_ms(2500);
            }
            
            n--;
        }
        
    }
    
    
}

