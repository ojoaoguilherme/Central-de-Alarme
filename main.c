#define _XTAL_FREQ 20000000
#include <pic16f877a.h>
#include <string.h>
#include "lcd.h"
#include <xc.h>
#include <xc8debug.h>

//Configura��o func
void setaZona(unsigned char *msgZonaDisparadas, unsigned char *msgConfigDispara, unsigned char *pos);
void rotinaValidaSenha(unsigned char* senhaOp);
void inputSenhaAlter();
unsigned int valida_senha(unsigned char *texto);
void validaUser();
void alteraSenhas(unsigned int opConfig);
unsigned char confereTeclado(unsigned int numero);

//Configura��o var
unsigned int senhaCoaAtivo = 0;
unsigned int  zonaConfig = 0;
unsigned int validaSenha = 0;
unsigned int input = 10;
unsigned int paizonaConfignel = 1;
unsigned int userFalse = 1;
unsigned int menu = 1;
unsigned char *aux = 0;
unsigned char senhaUser[5] = "1212";
unsigned char senhaUserConfere[5] = "0000";
unsigned char senhaCoa[5] = "5555";
unsigned char senhaConfig[5] = "0000";
unsigned int alteraSenha = 0;
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
unsigned char msgZonaDisparadas[15] = "       1 1 1 1";
unsigned char msgSenhaCancelada[16] = "Senha cancelada";
unsigned char msgSenhaAtualizada[17] = "Senha Atualizada";
unsigned char msgSenhaErrada[13] = "Senha errada";
unsigned char msgSenhaCorreta[14] = "Senha correta";
unsigned char msgSenhaConfig[13] = "Senha Config";
unsigned char msgSenhaUsuario[14] = "Senha Usuario";
unsigned char msgSenhaCoacao[13] = "Senha Coacao";
unsigned char msgSenhaDisparo[15] = "Config Disparo";
unsigned char msgDesativarZona[15] = "Desativar Zona";
unsigned char msgReativar[9] = "Reativar";
unsigned char msgDigiteSenha[15] = "Digite a senha";
unsigned char msgDigiteNovaSenha[14] = "   Nova senha";
unsigned char msgValidaSenha[16] = "Ok:F ou Negar:E";
unsigned char msgAceitoOuNego[9] = "Digite: ";
unsigned char msgMascara[5] = "____";
unsigned char msgChamaAjuda[10] = "Sai Ratao";

//controle analogico
void inicioADC ();
unsigned int leituraADC (unsigned char canal);
unsigned int auxSensor = 170;
unsigned int valorSensor = 0;
unsigned int valorSensorAux = 0;

void main(void) {
    TRISE = 0x00; 
    TRISD = 0x00; 
    TRISB = 0x0F; 
    PORTE = 0x01;
    inicioADC();
    while (1){ 
        while (userFalse){
           validaUser();
        }
        while(senhaCoaAtivo){
            LCD_init();
            LCD_limpa();
            LCD_linha1();
            escreveMesagem(msgChamaAjuda);
            __delay_ms(2000);
            infoZonas();
            PORTB = 0b01111111;
            if(RB0 == 0){
                __delay_ms(100);
                senhaCoaAtivo = 0;
                liga_buzzer(0.1);
            }
        }
        while (menu){
            valorSensor = leituraADC(2);
            listaZonas(valorSensor);
            __delay_ms(50); 
            if (opConfig > 0){
                switch (opConfig){
                    case 1:
                        alteraSenhas(opConfig);
                        break;
                    case 2:
                        alteraSenhas(opConfig);
                        break;
                    case 3:
                        alteraSenhas(opConfig);
                        break;
                    case 4:
                        configZonas();
                        break;
                    case 5:
                        //desativar zona
                        break;
                    case 6:
                        //reativar zona
                        break;
                }
                opConfig = 0;
           }  
       }
    }
}
void setaZona(unsigned char *msgZonaDisparadas, unsigned char *msgConfigDispara, unsigned char *pos){
    if (senhaCoaAtivo){
        for (int i = 0; msgZonaDisparadas[i] != '\0'; i++){
            if(msgZonaDisparadas[i] == '1' && msgConfigDispara[i] == pos){
                msgZonaDisparadas[i] = '0';
                __delay_ms(2);
                pos++;
            }
        }
    }
    else if (!senhaCoaAtivo){
        for (int i = 0; msgZonaDisparadas[i] != '\0'; i++){
            if(msgZonaDisparadas[i] == '0' && msgConfigDispara[i] == pos){
                msgZonaDisparadas[i] = '1';
            }
            else if(msgZonaDisparadas[i] == '1' && msgConfigDispara[i] == pos){
                msgZonaDisparadas[i] = '0';
            }
            __delay_ms(2);
        }
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
}
void configZonas(){
    infoZonas();
    __delay_ms(100);
    unsigned char pos = '0';
    zonaConfig = 1;
    while (zonaConfig){
        pos = '0';
        PORTB = 0b11101111;
        if (RB0 == 0){ // k1
            __delay_ms(200);
            pos = '1';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB1 == 0){ // k2
            __delay_ms(200);
            pos = '2';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB2 == 0){ // k3
            __delay_ms(200);
            pos = '3';
            __delay_ms(2);
            setaZona(msgZonaDisparadas, msgConfigDispara, pos);
        }
        if (RB3 == 0){ // k4
            __delay_ms(200);
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
        if (RB2 == 0){ //Nega senha: E
            liga_buzzer(0.1);
            aceito = 0;
            LCD_escreve('E');
        }
        if (RB3 == 0){ //Aceita senha: F
            liga_buzzer(0.1);
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
    alteraSenha = 1;
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
    LCD_init();
    __delay_ms(20);
    LCD_limpa();
    __delay_ms(20);
    telaInicial();
    Linha2();
    while(userFalse){
        for(int n = 0; n < 8; n++){
            input = 10;
            while (input == 10){
                teclado();
            }
            senhaUserConfere[n] = confereTeclado(input);
            if (n == 3){
                if ((strcmp(senhaUser, senhaUserConfere) != 0) && 
                        (strcmp(senhaCoa, senhaUserConfere) != 0)){
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
            else if (strcmp(senhaCoa, senhaUserConfere)==0){
                unsigned char pos;
                userFalse = 0;
                n = 10;
                pos = '1';
                senhaCoaAtivo = 1;
                LCD_limpa();
                LCD_linha1();
                escreveMesagem(msgSenhaCorreta);
                __delay_ms(2000);
                setaZona(msgZonaDisparadas, msgConfigDispara, pos);
            }
        }
    }
}
void listaZonas(unsigned int valorSensor){
    PORTB = 0b10111111; // teclar a letra A para entrar
    if (valorSensor <= auxSensor){
        LCD_init();
        LCD_limpa();
        LCD_linha1();
        LCD_escreve('>');
        escreveMesagem(msgSenhaConfig);
        LCD_linha2();
        escreveMesagem(msgSenhaUsuario);
        if (RB2 == 0){
            __delay_ms(100);
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
            __delay_ms(100);
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
            __delay_ms(100);
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
            __delay_ms(100);
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
            __delay_ms(100);
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
            __delay_ms(100);
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
    // pino 0 = 1 (liga) && pino = 1 (divis�o de clock 32)
    ADCON0 = 0x81; //0b10000001
    // pino 0 <= 4 = 0 (todos analogicos) 
    // pino 7 = 0 (divis�o de clock 32)
    // pino 8 = 1 (dados justificados para direita)
    ADCON1 = 0x80; //0b10000000
}
unsigned int leituraADC (unsigned char canal){
    unsigned int leitura;
    //limpa o registrador para futura valida��o
    ADCON0 &= 0xC5; // 0b11000101
    ADCON0 |= (canal<<3); // seta o canal utilizado
    __delay_ms(2);
    
    //manda o conversor ADC
    GO_nDONE = 1;
    
    //espera a convers�o terminar
    while (GO_nDONE);
    
    leitura = (ADRESH<<8) + ADRESL;
    return leitura;
}

void teclado(){
    PORTE = 0x01;
    // ***
    // Verifica��o da primeira linha do teclado
    // ***
    PORTB = 0b11101111; // verifica a primeira linha (bot�o 0,1,2,3,4)
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
        if (alteraSenha){
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
        if (alteraSenha){
            input = 3;
        }
    }
    // ***
    // Verifica��o da segunda linha do teclado
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
        if (alteraSenha){
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
        if (alteraSenha){
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
        if (alteraSenha){
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
        if (alteraSenha){
            input = 7;
        }
    }
    // ***
    // Verifica��o da terceira linha do teclado
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
        if (alteraSenha){
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
        if (alteraSenha){
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
    // Verifica��o da quarta linha do teclado
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