#include <REGX51.H>

//khai bao LCD
sbit LCD_RS = P3^4;
sbit LCD_EN = P3^5;
#define LCD_DATA P1

//khai bao  ADC0804
#define ADC_DATA P2
sbit ADC_CS=P3^3;
sbit ADC_RD=P3^2;
sbit ADC_WR=P3^1;
sbit ADC_INTR=P3^0;

void Delay_us(unsigned int t)
{
    unsigned int x;
	for(x=0; x<t; x++);
}

void Delay_ms(unsigned int t) //Hàm delay
{
	unsigned int x, y ;
	for(x=0; x<t; x++)
	{
	 for(y=0; y<123; y++);
	}
}

void LCD_cmd(unsigned char cmd){
	LCD_RS=0;
	LCD_DATA = cmd;
	LCD_EN=0;
	LCD_EN=1;
	Delay_ms(2);
}
void LCD_chr_cp(char c){
	LCD_RS=1;
	LCD_DATA = c;
	LCD_EN=0;
	LCD_EN=1;
	Delay_ms(2);
	}
void LCD_out_String_cp(char *str){
	unsigned char i=0;
	while(str[i] !=0){
		LCD_chr_cp(str[i]);
		i++;
		}
	}
void LCD_int(){
	LCD_cmd(0x30);
	Delay_ms(5);
	LCD_cmd(0x30);
	Delay_ms(1);
	LCD_cmd(0x30);
	LCD_cmd(0x38);// Set 2 dong Lcd,font 5*8
	LCD_cmd(0x01);//clear LCD
	LCD_cmd(0x0C);// display and delete cursor;
}
void LCD_out_String(unsigned char row,unsigned char col,char *str){
	 unsigned char cmd;
	//di chuyen con tro den vi tri can thiet
	cmd=row==1?0x80:0xC0+col-1;
	LCD_cmd(cmd);
	//xuat ki tu
	LCD_out_String_cp(str);
	}
void LCD_out_char(unsigned char row,unsigned char col,char c){
	 unsigned char cmd;
	//di chuyen con tro den vi tri can thiet
	cmd=row==1 ? 0x80 : 0xC0 + col - 1;
	LCD_cmd(cmd);
	//xuat ki tu
	LCD_chr_cp(c);
	}

  unsigned char ADC_Read()
{
		 unsigned char kq;
	 	 //chip select
	           ADC_CS=0;
	  	//generate pulse start convert
	  	ADC_WR=0;
	   	ADC_WR=1;
	          // wait until convertion ended
		while(ADC_INTR);
		// read ADC
		ADC_RD=0;
		kq=ADC_DATA;
		ADC_RD=1;
		return kq;
	
          }
int main(void)
	{
		unsigned char adc_value;
		unsigned int t;
                     LCD_int();
		LCD_out_String_cp("TEMP:");
		//LCD_cmd(0xC0);//set cursor  to row 2;
		while(1){
			adc_value= ADC_Read();
			t = adc_value*1.961f;
			 LCD_out_char(2,1,t/100+0x30);
			 LCD_chr_cp(t%100/10+0x30);
			 LCD_chr_cp(t%10+0x30);
			Delay_ms(500);
                                   }
         }

