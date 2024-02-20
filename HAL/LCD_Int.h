
#ifndef LCD_INT_H_
#define LCD_INT_H_




void LCD_Init(void);

void WriteIns(u8 ins);

void WriteData(u8 data);

void LCD_WriteChar(u8 ch);

void LCD_WriteString(u8 *str);

void LCD_SetCursor(u8 line,u8 cell);

void LCD_Clear(void);

void LCD_ClearCursor(u8 line , u8 cell , u8 num);

void LCD_WriteBinary(u8 num);

void LCD_WriteBinaryu16(u16 num);

void LCD_WriteHex(u8 num);

void LCD_WriteHexu16(u16 num);

void LCD_WriteNumber(s32 num);

void LCD_SnakeWord(u8 *str);

void LCD_WriteNumber4D(u16 num);

void LCD_CustomChar(u8 location,u8*pattern);

void LCD_FUNC(void);

void LCD_Clear_Cursor(u8 line , u8 cell , u8 num);

void LCD_Write_String_Cursor(u8 line , u8 cell , u8 *str);

s32 String_To_Int (u8 *str);




#endif /* LCD_INT_H_ */