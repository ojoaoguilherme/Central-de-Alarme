

#ifndef LCD_H
#define	LCD_H

#define rs RA5	
#define rw RA4
#define e  RA3

void init();                   
void LCD_init();               
void LCD_escreve(char x);            
void LCD_enable();             
void delay();                  
void LCD_linha1();
void LCD_linha2();
void LCD_limpa();
void LCD_escreveFrase(char *frase);




void init()
{
	ADCON1 = 0X07;               
     RA1=1;
	TRISA = 0X00;                
	TRISD = 0X00;                
}

void LCD_init()
{
    init();
	PORTD = 0X1;                 
	LCD_enable();
	PORTD = 0X38;                
	LCD_enable();
	PORTD = 0X0e;                
	LCD_enable();
	PORTD = 0X06;                
	LCD_enable();
	PORTD = 0X80;                
	LCD_enable();
}

void LCD_escreve(char x)
{
	PORTD = x;                   
	rs = 1;                      
	rw = 0;                      
	e = 0;                       
	delay();                   	 
	e = 1;                       
}

void LCD_limpa(){
    PORTD = 0x01;
    rs = 0;
    rw = 0;
    e=0;
    delay();                   	 
	e = 1;
}

void LCD_linha1(){
    PORTD = 0x02;
    rs = 0;
    rw = 0;
    e=0;
    delay();                   	 
	e = 1;
}
void LCD_linha2(){
    PORTD = 0xC0;
    rs = 0;
    rw = 0;
    e=0;
    delay();                   	 
	e = 1;
}




void LCD_enable()
{
	rs = 0;                     
	rw = 0;                     
	e = 0;                      
	delay();                  	
	e = 1;                      
}

void delay()
{
	int i;
	for (i = 0;i < 5000;i++);
}


void LCD_escreveFrase(char *frase)
{
    int i=0;
    for(i=0;i<frase[i]!='\0';i++){
        LCD_escreve(frase[i]);
    }      
}






#endif	/* LCD_H */

