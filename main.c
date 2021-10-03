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
void escreveMesagem(char *texto);
void teclado();
void telaInicial();
void Linha2();
void espacoLivre();
void validaUser();
void listaZonas(int valor);

//Usuario
int input = 10;
char *aux;
char senhaUser[5] = "1212";
char senhaUserConfere[5] = "0000";
char senhaCoa[5] = "5555";
char senhaConfig[5] = "0000";

//Config
int painel = 1;
int userFalse = 1;
int config = 0;
int valorSensor;

//Interface
char msgSenhaErrada[13] = "Senha errada";
char msgSenhaCorreta[14] = "Senha correta";
char msgSenhaConfigActive[14] = ">Senha Config";
char msgSenhaConfig[13] = "Senha Config";
char msgSenhaUsuarioActive[15] = ">Senha Usuario";
char msgSenhaUsuario[14] = "Senha Usuario";
char msgSenhaCoacaoActive[14] = ">Senha Coacao";
char msgSenhaCoacao[13] = "Senha Coacao";
char msgSenhaDisparoActive[15] = ">Senha Disparo";
char msgSenhaDisparo[14] = "Senha Disparo";
char msgDesativarZonaActive[16] = ">Desativar Zona";
char msgDesativarZona[15] = "Desativar Zona";
char msgReativarActive[10] = ">Reativar";
char msgReativar[9] = "Reativar";
char msgDigiteSenha[15] = "Digite a senha";
char msgMascara[5] = "____";

void main(void) {
    TRISE = 0; //Porta de saida para ligar o buzzer
    TRISD = 0; //liga a porta do display
    TRISB = 0x0F; //pinagem do teclado
    
    PORTE = 0x01; //desligando o buzzer = 0000 0001

    //Sequencia de inicialização do LCD
    LCD_init();
    LCD_limpa();
    
    while (1){
        
        //Painel inicial da central
        while (painel){
            telaInicial();
            Linha2();
            painel = 0;
        }

        //Enquanto o usuario não digitar a senha não tem acesso
        while (userFalse){
           validaUser();
        }
        LCD_limpa();
        LCD_linha1();
        LCD_escreve('O');
        LCD_escreve('k');

//        if (userFalse == 0){
//            int i;
//            //implementar o painel das zonas em forma de menu
//            // e rolagem de acordo com o potenciometro
//            // sentido horario - faz o menu descer
//            // sentido anti-horario - faz subir
//
//            //esse for é uma simulação para ajustar a lista de zonas
//            // a cada 2segundos o menu muda simulando o potenciometro girando
//            // sentido horario então a setinha desce.
//            for (i = 0; i < 10; i++){
//                valorSensor = i;
//                listaZonas(valorSensor);
//                __delay_ms(2500);
//            }
//        }
        
        teclado();
    }
}

//Aciona o buzzer com a quantidade de segundos que quisermos
//passando por parametro.
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
    for (int i = 0; i <= strlen(msgDigiteSenha)-1; i++){
        LCD_escreve(msgDigiteSenha[i]);
    }
    LCD_escreve(' ');
     
}

// Para fundionar o teclado e atualização da função espaçoLivre 
// deve separar o painel em duas partes como "Digite sua senha" sendo estatico
// e "_ _ _ _" sendo atualizada a cada numero inserido 
void Linha2(){
    LCD_linha2();
    espacoLivre();
    for (int i = 0; i <= strlen(msgMascara)-1; i++){
        LCD_escreve(msgMascara[i]);  
    }
    espacoLivre();
    
}

// Usado para centralizar os digitos quando inseridos no painel
// exemplo: "_ _ _ _" quando inserir = "1 _ _ _"
void espacoLivre(){
    LCD_linha2();
    for (int i = 0; i < 6; i++){
        LCD_escreve(' ');
    }

}

//Função que valida a senha do usuario
void validaUser(){
    while(userFalse){
        for(int n = 0; n < 8; n++){
            input = 10;
            while (input == 10){
                teclado();
            }
            switch (input){
                case 1: 
                    aux = '1';
                break;
                case 2: 
                    aux = '2';
                break;
                case 3: 
                    aux = '3';
                break;
                case 4: 
                    aux = '4';
                break;
                case 5: 
                    aux = '5';
                break;
                case 6: 
                    aux = '6';
                break;
                case 7: 
                    aux = '7';
                break;
                case 8: 
                    aux = '8';
                break;
                case 9: 
                    aux = '9';
                break;
                case 0: 
                    aux = '0';
                break;
            }
            senhaUserConfere[n] = aux;
            if (n == 3){
                if (strcmp(senhaUser, senhaUserConfere) != 0){
                    userFalse = 1;
                    LCD_limpa();
                    LCD_linha1();
                    escreveMesagem(msgSenhaErrada);
                }
            }
            if (strcmp(senhaUser, senhaUserConfere)==0){
                userFalse = 0;
                n = 10;
                LCD_limpa();
                LCD_linha1();
                escreveMesagem(msgSenhaCorreta);
            }
        }
    }
}

//Listagem das zonas no display
void listaZonas(int valorSensor){
    LCD_limpa();
    
    if (valorSensor == 1){
        LCD_linha1();
        escreveMesagem(msgSenhaConfigActive);
        
        LCD_linha2();
        escreveMesagem(msgSenhaUsuario);
        
    }
    
    if (valorSensor == 2){
        LCD_linha1();
        escreveMesagem(msgSenhaConfig);
        
        LCD_linha2();
        escreveMesagem(msgSenhaUsuarioActive);
        
    }
    
    if (valorSensor == 3){
        LCD_linha1();
        escreveMesagem(msgSenhaCoacaoActive);
        
        LCD_linha2();
        escreveMesagem(msgSenhaDisparo);
    }
    
    if (valorSensor == 4){
        LCD_linha1();
        escreveMesagem(msgSenhaCoacao);
        
        LCD_linha2();
        escreveMesagem(msgSenhaDisparoActive);
    }
    
    if (valorSensor == 5){
        LCD_linha1();
        escreveMesagem(msgDesativarZonaActive);
        
        LCD_linha2();
        escreveMesagem(msgReativar);
    }
    
    if (valorSensor == 6){
        LCD_linha1();
        escreveMesagem(msgDesativarZona);
        
        LCD_linha2();
        escreveMesagem(msgReativarActive);
    }
}

void escreveMesagem(char *texto){
    for (int i = 0; texto[i] != '\0'; i++){
        LCD_escreve(texto[i]);
    }
}
