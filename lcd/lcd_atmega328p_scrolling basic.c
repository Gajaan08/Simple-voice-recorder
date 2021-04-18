/*
 * lcd_test1ATMEGA328.c
 *
 * Created: 13-Apr-21 7:18:03 PM
 * Author : Acer
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_Port PORTD			//Define LCD Port (PORTA, PORTB, PORTC, PORTD)
#define LCD_DPin  DDRD			//Define 4-Bit Pins (PD4-PD7 at PORT D
#define RSPIN PD0			//RS Pin
#define ENPIN PD1 			//E Pin
#define DEBOUNCE_TIME 25 // time to wait while "de-bouncing" button
int state=0;  // to mark which screen you are in
int newUp;
int newDown;
int oldUp=0;
int oldDown=0;


void init_ports_mcu()

{
	
	DDRB &= ~(1<<PINB1); //Make Pin B1 input
	PORTB |= (1<<PINB1);//Set Pin B1 as high 
	
	DDRC &= ~(1<<PINC1); //Make Pin C1 input
	PORTC |= (1<<PINC1);//Set Pin C1 as high

}

void upVal (){
	if(bit_is_clear(PINB,1)){
		newUp=1;// checking if button for up is pressed
	}
	else{
		newUp=0;
		
	}
	
}

void downVal (){
	if(bit_is_clear(PINC,1)){
		newDown=1; //checking if button for down is pressed
	}
	else{
		newDown=0;
		
	}
	
}



void LCD_Init (void)
{
	LCD_DPin = 0xFF;		//Control LCD Pins (D4-D7)
	_delay_ms(15);		//Wait before LCD activation
	LCD_Action(0x02);	//4-Bit Control
	LCD_Action(0x28);       //Control Matrix @ 4-Bit
	LCD_Action(0x0c);       //Disable Cursor
	LCD_Action(0x06);       //Move Cursor
	LCD_Action(0x01);       //Clean LCD
	_delay_ms(2);
}

void LCD_Action( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
	LCD_Port &= ~ (1<<RSPIN);
	LCD_Port |= (1<<ENPIN);
	_delay_us(1);
	LCD_Port &= ~ (1<<ENPIN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
	LCD_Port |= (1<<ENPIN);
	_delay_us(1);
	LCD_Port &= ~ (1<<ENPIN);
	_delay_ms(2);
}

void LCD_Clear()
{
	LCD_Action (0x01);		//Clear LCD
	_delay_ms(2);			//Wait to clean LCD
	LCD_Action (0x80);		//Move to Position Line 1, Position 1
}


void LCD_Print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0);
		LCD_Port |= (1<<RSPIN);
		LCD_Port|= (1<<ENPIN);
		_delay_us(1);
		LCD_Port &= ~ (1<<ENPIN);
		_delay_us(200);
		LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4);
		LCD_Port |= (1<<ENPIN);
		_delay_us(1);
		LCD_Port &= ~ (1<<ENPIN);
		_delay_ms(2);
	}
}
//Write on a specific location
void LCD_Printpos (char row, char pos, char *str)
{
	if (row == 0 && pos<16)
	LCD_Action((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Action((pos & 0x0F)|0xC0);
	LCD_Print(str);
}
void LCD_Cursorpos (char row, char pos)
{
	if (row == 0 && pos<16)
	LCD_Action((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Action((pos & 0x0F)|0xC0);
	LCD_Action(0x0E); //enable cursor
}
int main()
{
	LCD_Init(); //Activate LCD
	init_ports_mcu(); //activate buttons
	LCD_Print("One");
	LCD_Action(0xC0);		//Go to Line 2, Position 1
	LCD_Print("Two");
	

	while(1) {
		upVal();
		downVal();
		if(state==0 && newDown==0 && oldDown==0 ){
			LCD_Cursorpos(0,3);     //Cursor for first text
			_delay_ms(10);
			LCD_Action(0x0c);   //Disable cursor
			_delay_ms(10);	
		}
		if(state==1 && newUp==0 && oldUp==0){
			LCD_Cursorpos(0,3);     //Cursor for first text
			_delay_ms(10);
			LCD_Action(0x0c);   //Disable cursor
			_delay_ms(10);
		}
		if(state==1 && newUp==0 && oldUp==1 && newDown==0 && oldDown==0){
			LCD_Clear();
		    LCD_Print("One");
		    LCD_Action(0xC0);		//Go to Line 2, Position 1 
		    LCD_Print("Two");
			state=0;
	    }
		if(state==0 && newUp==0 && oldUp==0 && newDown==0 && oldDown==1){
			LCD_Clear();
			LCD_Print("Two");
			LCD_Action(0xC0);		//Go to Line 2, Position 1 
			LCD_Print("Three");
			state=1;
        }
		oldUp=newUp;
		oldDown=newDown;
}
}
