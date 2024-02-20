
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"


#define  F_CPU   8000000
#include <util/delay.h>

#if LCD_MODE==_8_BIT    //  MODE

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);         //RS / Register_Selection / H: Display Data	L: Instruction Code
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);        //EN / Enable Signal. Read data when E is “H”, write data at the falling edge of E.
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);
	WriteIns(0x0C);   //Cursor : 0x0e , 0x0f
	WriteIns(0x01);
	_delay_ms(1);
	WriteIns(0x06);   //increase DDRAM
}

#elif LCD_MODE==_4_BIT         //  MODE

void WriteIns(u8 ins)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0C);//0x0e   0x0f
	WriteIns(0x01);
	_delay_ms(1);
	WriteIns(0x06);//increase DDRAM
}

#endif

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(u8 *str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}

void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==1)
	{
		WriteIns(0x80|(cell-1));
	}
	else if (line ==2)
	{
		WriteIns(0x80|0x40|(cell-1));    // WriteIns((0x80+0x40)|(cell-1));
	}
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}

void LCD_ClearCursor(u8 line , u8 cell , u8 num)
{
	u8 i ;
	LCD_SetCursor(line,cell);
	for (i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
	LCD_SetCursor(line,cell);
}

void LCD_WriteBinary(u8 num)
{
	for(s8 i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteBinaryu16(u16 num)
{
	for(s8 i=15;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteHex(u8 num){
	
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	const u8 hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	/*if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}*/
	LCD_WriteChar(hex[LN]);
	LCD_WriteChar(hex[HN]);
}

void LCD_WriteHexu16(u16 num)
{
	u8 HB1=(num&(u16)0xf000)>>12;
	u8 LB1=(num&(u16)0x0f00)>>8;
	u8 HB2=(num&(u16)0x00f0)>>4;
	u8 LB2=num&(u16)0x000f;
	
	const u16 hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		
    /*if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}*/
	
	LCD_WriteChar(hex[HB1]);
	LCD_WriteChar(hex[LB1]);
	LCD_WriteChar(hex[HB2]);
	LCD_WriteChar(hex[LB2]);
}

void LCD_WriteNumber(s32 num)
{
	u8 str[10],i=0;
	s8 j;
	if (num==0)
	{
		LCD_WriteChar('0');
	}
	else
	{
		if (num<0)
		{
			LCD_WriteChar('-');
			num=num*-1;
		}
		while(num)
		{
			str[i]=num%10+'0';
			i++;
			num=num/10;
		}
		for (j=i-1;j>=0;j--)
		{
			LCD_WriteChar(str[j]);
		}
	}
}

void LCD_WriteNumber4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_SnakeWord(u8 *str)
{
	u8 length ;
	s8 i  ;
	for (i=0;str[i];i++);
	length = i ;
	
	for (i=1;str[i];i++)
	{
		LCD_WriteString(str+length-i);
		_delay_ms(100);
		LCD_Clear();
	}
	for (i=1;i<=16;i++)
	{
		LCD_SetCursor(1,i);
		LCD_WriteString(str);
		_delay_ms(100);
		LCD_Clear();
	}
	for (i=1;str[i];i++)
	{
		LCD_SetCursor(2,1);
		LCD_WriteString(str+length-i);
		_delay_ms(100);
		LCD_Clear();
	}
	for (i=1;i<=16;i++)
	{
		LCD_SetCursor(2,i);
		LCD_WriteString(str);
		_delay_ms(100);
		LCD_Clear();
	}
}

void LCD_CustomChar(u8 location,u8*pattern)  //location  0  for  7
{
	WriteIns(0X40+location*8);
	for (u8 i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}

void LCD_FUNC(void)   //  ^^^^  Optimization
{
	WriteIns(0X40+0);
	WriteData(0X55);
	WriteData(0XAA);
	WriteData(0X55);
	WriteData(0XAA);
	WriteData(0X55);
	WriteData(0XAA);
	WriteData(0X55);
}

s32 String_To_Int (u8 *str)
{
	u8 i=0 , flag = 0  ;
	s32 num = 0 ;
	
	if (str[0] == '-' )
	{
		flag = 1 ;
		i = 1 ;
	}
	
	
	for (;str[i];i++)
	{
		if ((str[i]>='0')&&(str[i]<='9'))
		{
			num = (num * 10) + (str[i] - '0') ;
		}
		
		
	}
	if (1==flag)
	{
		num *= -1 ;
	}
	
	
	return num ;
}

void LCD_Clear_Cursor(u8 line , u8 cell , u8 num)
{
	u8 i ;
	LCD_SetCursor(line,cell);
	for (i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
	LCD_SetCursor(line,cell);
}

void LCD_Write_String_Cursor(u8 line , u8 cell , u8 *str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}







