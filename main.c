#define _XTAL_FREQ 20000000
#include <pic16f877a.h>
#include <string.h>
#include "lcd.h"
#include <xc.h>
#include <xc8debug.h>

//Configuração func
void setaZona(unsigned char *var1, unsigned char *var2, unsigned char *pos);
void rotinaValidaSenha(unsigned char* senhaOp);
void inputSenhaAlter();
unsigned int valida_senha(unsigned char *texto);
void validaUser();
void alteraSenhas(unsigned int opConfig);
unsigned char confereTeclado(unsigned int numero);

//Configuração var
unsigned int zonaConfig = 1;
unsigned int validaSenha = 0;
unsigned int input = 10;
unsigned int painel = 1;
unsigned int userFalse = 1;
unsigned int menu = 1;
unsigned char *aux = 0;
unsigned char senhaUser[5] = "1212";
unsigned char senhaUserConfere[5] = "0000";
unsigned char senhaCoa[5] = "5555";
unsigned char senhaConfig[5] = "0000";
unsigned int alteraSenha = 1;
unsigned int opConfig = 0;

//interface func
void infoZonas();
void configZonas();
void liga_buzzer(float tempoSegundos);
void listaZonas(unsigned int valor);
void escreveMesagem(unsigned char *texto);
void teclado();
void telaInicial();
void Linha2();
void espacoLivre();

//interface var
unsigned char msgConfigDispara[15] = " Zona: 1 2 3 4";
unsigned char msgZonaDisparadas[15] = "       0 0 0 0";
unsigned char msgSenhaCancelada[16] = "Senha cancelada";
unsigned char msgSenhaAtualizada[17] = "Senha Atualizada";
unsigned char msgSenhaErrada[13] = "Senha errada";
unsigned char msgSenhaCorreta[14] = "Senha correta";
unsigned char msgSenhaConfig[13] = "Senha Config";
unsigned char msgSenhaUsuario[14] = "Senha Usuario";
unsigned char msgSenhaCoacao[13] = "Senha Coacao";
unsigned char msgSenhaDisparo[14] = "Senha Disparo";
unsigned char msgDesativarZona[15] = "Desativar Zona";
unsigned char msgReativar[9] = "Reativar";
unsigned char msgDigiteSenha[15] = "Digite a senha";
unsigned char msgDigiteNovaSenha[14] = "   Nova senha";
unsigned char msgValidaSenha[16] = "Ok:F ou Negar:E";
unsigned char msgAceitoOuNego[9] = "Digite: ";
unsigned char msgMascara[5] = "____";

//controle analogico
void inicioADC ();
unsigned int leituraADC (unsigned char canal);
unsigned int auxSensor = 204;
unsigned int valorSensor = 0;
unsigned int valorSensorAux = 0;

void main(void) {
    TRISE = 0x00; 
    TRISD = 0x00; 
    TRISB = 0x0F; 
    PORTE = 0x01;
//    inicioADC();
    LCD_init();
    __delay_ms(10);
    while (1){
//        while (painel){
//            LCD_init();
//            LCD_limpa();
//            telaInicial();
//            Linha2();
//            painel = 0;
//        } 
//        while (userFalse){
//           validaUser();
//        }
//        menu = 1;
//        for (int i=0; i < 4; i++){
//            opConfig = i;
//            alteraSenhas(opConfig);
//        }
        
        configZonas();
        zonaConfig = 1;
//        while (menu){
////            valorSensor = leituraADC(2);
////            listaZonas(valorSensor);
////            __delay_ms(100); 
//            if (opConfig > 0){
//                switch (opConfig){
//                    case 1:
////                        alteraSenhas(opConfig);
//                        break;
//                    case 2:
////                        alteraSenhas(opConfig);
//                        break;
//                    case 3:
//                        alteraSenhas(opConfig);
//                        break;
////                    case 4:
////                        //config disparo
////                        break;
////                    case 5:
////                        //desativar zona
////                        break;
////                    case 6:
////                        //reativar zona
////                        break;
//
//                }
//            }  
//        }
    }
}
void setaZona(unsigned char *msgZonaDisparadas, unsigned char *msgConfigDispara, unsigned char *pos){
    for (int i = 0; msgZonaDisparadas[i] != '\0'; i++){
        if(msgZonaDisparadas[i] == '0' && msgConfigDispara[i] == pos){
            msgZonaDisparadas[i] = '1';
        }
        else if(msgZonaDisparadas[i] == '1' && msgConfigDispara[i] == pos){
            msgZonaDisparadas[i] = '0';
        }
        __delay_ms(2);
    }
    zonaConfig = 0;
    infoZonas();
}
void infoZonas(){
    LCD_limpa();
    LCD_linha1();
    escreveMesagem(msgConfigDispara);
    LCD_linha2();
    escreveMesagem(msgZonaDisparadas);
    __delay_ms(1000);
}
void configZonas(){
    infoZonas();
    PORTB = 0b11101111;
    unsigned char pos = '0';
    while (zonaConfig){
        __delay_ms(250);
        if (RB0 == 0){
            pos = '1';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB1 == 0){
            pos = '2';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB2 == 0){
            pos = '3';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB3 == 0){
            pos = '4';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
    }
}
unsigned char confereTeclado(unsigned int numero){
   switch (numero){
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
   return aux;
}
unsigned int valida_senha(unsigned char *texto){
    unsigned int aceito = 3;
    LCD_limpa();
    LCD_linha1();
    escreveMesagem(msgValidaSenha);
    LCD_linha2();
    escreveMesagem(texto);
    LCD_escreve(' ');
    escreveMesagem(msgAceitoOuNego);
    PORTB = 0b01111111;
    while (aceito == 3){
        __delay_ms(200);
        //Nega senha: E
        if (RB2 == 0){
            aceito = 0;
            LCD_escreve('E');
        }
        else if (RB3 == 0){
            //Aceita senha: F
            aceito = 1;
            LCD_escreve('F');
        }
    }
    __delay_ms(2000);
    return aceito;
    
}
void inputSenhaAlter(unsigned char *senhaDestino){
    for (int i = 0; i < 4; i++){
        input = 10;
        while (input == 10){teclado();}
        __delay_ms(2);
        senhaDestino[i] = confereTeclado(input);
    }
    validaSenha = valida_senha(senhaDestino);
}
void rotinaValidaSenha(unsigned char* senhaOp){
    inputSenhaAlter(senhaOp);
        LCD_limpa();
        if (validaSenha){
            escreveMesagem(msgSenhaAtualizada); 
            LCD_linha2();
            escreveMesagem(senhaOp);
        }
        else {
            escreveMesagem(msgSenhaCancelada);
        }
        __delay_ms(2000);
}
void alteraSenhas(unsigned int opConfig){
    LCD_init();
    LCD_limpa();
    __delay_ms(2);
    escreveMesagem(msgDigiteNovaSenha);
    Linha2();
    if (opConfig == 1){
        rotinaValidaSenha(senhaConfig);
    }
    else if (opConfig == 2){
        rotinaValidaSenha(senhaUser);
    } 
    else if (opConfig == 3){
        rotinaValidaSenha(senhaCoa);
    } 
}
void liga_buzzer(float tempoSegundos){
    tempoSegundos = tempoSegundos * 1000;
    __delay_ms(10);
    while(tempoSegundos > 0){
       PORTE = 0;
        __delay_ms(1);
        tempoSegundos--;
    }
    PORTE = 0x0F;
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
        liga_buzzer(0.1); // buzzer ta ligado, buzzer so liga quando esta com os bits em 0
        LCD_escreve('0');
        if(userFalse){
            input = 0;
        }
        if (alteraSenha){
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
        if(userFalse){
            input = 1;
        }
        if (alteraSenha){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
        if(userFalse){
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
void telaInicial(){
    LCD_linha1();
    LCD_escreve(' ');
    for (int i = 0; i <= strlen(msgDigiteSenha)-1; i++){
        LCD_escreve(msgDigiteSenha[i]);
    }
    LCD_escreve(' ');
}
void Linha2(){
    LCD_linha2();
    espacoLivre();
    for (int i = 0; i <= strlen(msgMascara)-1; i++){
        LCD_escreve(msgMascara[i]);  
    }
    espacoLivre();
}
void espacoLivre(){
    LCD_linha2();
    for (int i = 0; i < 6; i++){
        LCD_escreve(' ');
    }
}
void validaUser(){
    while(userFalse){
        for(int n = 0; n < 8; n++){
            input = 10;
            while (input == 10){
                teclado();
            }
            senhaUserConfere[n] = confereTeclado(input);
            if (n == 3){
                if (strcmp(senhaUser, senhaUserConfere) != 0){
                    userFalse = 1;
                    menu = 0;
                    LCD_limpa();
                    LCD_linha1();
                    escreveMesagem(msgSenhaErrada);
                    __delay_ms(2000);
                }
            }
            if (strcmp(senhaUser, senhaUserConfere)==0){
                userFalse = 0;
                menu = 1;
                n = 10;
                LCD_limpa();
                LCD_linha1();
                escreveMesagem(msgSenhaCorreta);
                __delay_ms(2000);
            }
        }
    }
}
void listaZonas(unsigned int valorSensor){
    if (valorSensor <= auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        LCD_escreve('>');
        escreveMesagem(msgSenhaConfig);
        LCD_linha2();
        escreveMesagem(msgSenhaUsuario);
        PORTB = 0b10111111;
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 1;
        }
    }
    else if (valorSensor <= 2*auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        escreveMesagem(msgSenhaConfig);
        LCD_linha2();
        LCD_escreve('>');
        escreveMesagem(msgSenhaUsuario);
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 2;
        }
    }
    else if (valorSensor <= 3*auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        LCD_escreve('>');
        escreveMesagem(msgSenhaCoacao);
        LCD_linha2();
        escreveMesagem(msgSenhaDisparo);
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 3;
        }
    }
    else if (valorSensor <= 4*auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        escreveMesagem(msgSenhaCoacao);
        LCD_linha2();
        LCD_escreve('>');
        escreveMesagem(msgSenhaDisparo);
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 4;
        }
    }
    else if (valorSensor <= 5*auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        LCD_escreve('>');
        escreveMesagem(msgDesativarZona);
        LCD_linha2();
        escreveMesagem(msgReativar);
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 5;
        }
    }
    else if (valorSensor <= 6*auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        escreveMesagem(msgDesativarZona);
        LCD_linha2();
        LCD_escreve('>');
        escreveMesagem(msgReativar);
        if (RB2 == 0){
            __delay_ms(200);
            liga_buzzer(0.1);
            opConfig = 6;
        }
    }
}
void escreveMesagem(unsigned char *texto){
    for (int i = 0; texto[i] != '\0'; i++){
        LCD_escreve(texto[i]);
    }
}
void inicioADC (){
    TRISA = 0xFF;
    // pino 0 = 1 (liga) && pino = 1 (divisão de clock 32)
    ADCON0 = 0x81; //0b10000001
    // pino 0 <= 4 = 0 (todos analogicos) 
    // pino 7 = 0 (divisão de clock 32)
    // pino 8 = 1 (dados justificados para direita)
    ADCON1 = 0x80; //0b10000000
}
unsigned int leituraADC (unsigned char canal){
    unsigned int leitura;
    //limpa o registrador para futura validação
    ADCON0 &= 0xC5; // 0b11000101
    ADCON0 |= (canal<<3); // seta o canal utilizado
    __delay_ms(2);
    
    //manda o conversor ADC
    GO_nDONE = 1;
    
    //espera a conversão terminar
    while (GO_nDONE);
    
    leitura = (ADRESH<<8) + ADRESL;
    return leitura;
}