
#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"




void ADC_Init(ADC_VolRef_t vref,ADC_Prescaler_t scaler)
{
	//modes
	//vref
	switch(vref){
		case VREF_AREF:
		CLE_BIT(ADMUX,REFS0);
		CLE_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLE_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
		
	}
	//prescaler ADC clk
	
	ADCSRA=ADCSRA&0xF8;//0b11111000
	scaler=scaler&0x07;//0b00000111
	ADCSRA=ADCSRA|scaler;
	
	
	//ADC anable
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_Channel_t ch)
{
	// select channel using mux
	
	ADMUX=ADMUX&0xe0;//0b11100000
	ADMUX=ADMUX|ch;
	//start conversion
	SET_BIT(ADCSRA,ADSC);
	//w8 until conversion end
	while(READ_BIT(ADCSRA,ADSC));
	//get read
	return ADC;
}

u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	
	u16 adc=ADC_Read(ch);
	u16 volt;
	
	volt=(adc*(u32)5000)/1024;
	
	return volt;
	
}



