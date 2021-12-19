
// подключение заголовочного файла
#include "link.h"


// отрисовка шкал
void interface_init(void)
{
	LCD_printString(175, 1, "0-312.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(176, 11, "312.5-625", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(176, 21, "625-937.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(167, 31, "937.5-1250", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 41, "1250-1562.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 51, "1562.5-1875", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 61, "1875-2187.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 71, "2187.5-2500", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 81, "2500-2812.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 91, "2812.5-3125", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 101, "3125-3437.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 111, "3437.5-3750", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 121, "3750-4062.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 131, "4062.5-4375", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 141, "4375-4687.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 151, "4687.5-5000", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 161, "5000-5312.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 171, "5312.5-5625", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 181, "5625-5937.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 191, "5937.5-6250", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 201, "6250-6562.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 211, "6562.5-6875", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 221, "6875-7187.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 231, "7187.5-7500", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 241, "7500-7812.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 251, "7812.5-8125", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 261, "8125-8437.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 271, "8437.5-8750", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 281, "8750-9062.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 291, "9062.5-9375", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 301, "9375-9687.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 311, "9687.5-10k", 0x0000, &calibri_14ptFontInfo);
}


int main(void)
{	
	// тактирование
	clockSetup();
	
	Timer2_init();
	Timer1_init();

	//
	portsSetup();
	
	// инициализация АЦП
	ADC_init();
	
	// инициализация SPI2
	SPI2_Init();
	I2C_init();
	
	// инициализация LCD
	LCD_init();
	
	// белый фон LCD
	LCD_fill(0xFFFF);
	
	FT6236_init();
	
	// отрисовка шкал
	//interface_init();
	
	inputNum = 0;
	appState = 3;

	while(1)
	{
		switch(appState)
		{
			case 1:
				LCD_fill(0xFFFF);
				GUI_objectListReset();
				GUI_objSetHandlerFunc(0);
				GUI_createButton(BUTTON_ID12_CHANGE_FREQ_X0,	BUTTON_ID12_CHANGE_FREQ_X1,
												BUTTON_ID12_CHANGE_FREQ_Y0,		BUTTON_ID12_CHANGE_FREQ_Y1,
												BUTTON_ID12_CHANGE_FREQ_BORDER,
												BUTTON_ID12_CHANGE_FREQ_MAIN_COLOR,
												BUTTON_ID12_CHANGE_FREQ_BORDER_COLOR,
												BUTTON_ID12_CHANGE_FREQ_TEXT,
												BUTTON_ID12_CHANGE_FREQ_TEXT_COLOR,
												BUTTON_ID12_CHANGE_FREQ_TEXT_FONT,
												BUTTON_ID12_CHANGE_FREQ_TEXT_MARGIN_X,
												BUTTON_ID12_CHANGE_FREQ_TEXT_MARGIN_Y,
												BUTTON_ID12_CHANGE_FREQ_STATE,
												BUTTON_ID12_CHANGE_FREQ_DELAY_SEC,
												BUTTON_ID12_CHANGE_FREQ_ACTION_PTR);
				GUI_createLabel(LABEL_ID1_FREQ_X0,	LABEL_ID1_FREQ_X1,
												LABEL_ID1_FREQ_Y0,	LABEL_ID1_FREQ_Y1,
												LABEL_ID1_FREQ_BORDER,
												LABEL_ID1_FREQ_MAIN_COLOR,
												LABEL_ID1_FREQ_BORDER_COLOR,
												LABEL_ID1_FREQ_TEXT,
												LABEL_ID1_FREQ_TEXT_COLOR,
												LABEL_ID1_FREQ_TEXT_FONT,
												LABEL_ID1_FREQ_TEXT_MARGIN_X,
												LABEL_ID1_FREQ_TEXT_MARGIN_Y,
												LABEL_ID1_FREQ_ACTION_PTR);
				GUI_labelChangeText(LABEL_FREQ_ID, inputNumStr, LABEL_ID1_FREQ_TEXT_COLOR, LABEL_ID1_FREQ_TEXT_FONT);
				MDR_TIMER1->CNTRL	=	0;
				NVIC_DisableIRQ(Timer1_IRQn);
				__disable_irq();
				appState = 2;
				break;
			case 2:
				fft_page(freqBlock);
				GUI_Handler();
				break;
			case 3:
				Timer1_init();
				GUI_FFT_numInputInterfaceInit();
				appState = 4;
				break;
			case 4:
				GUI_Handler();
				delay_ms(MDR_TIMER2, 10);
				break;
		}
	}
}
