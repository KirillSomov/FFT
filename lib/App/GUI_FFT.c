
#include "GUI_FFT.h"


char inputNumStr[5] = {0};
uint16_t inputNum = 0;

extern uint16_t appState;

void GUI_FFT_numInputInterfaceInit(void)
{
	//
	LCD_fill(0xBDD7);
	
	inputNumStr[0] = '\0';
	
	GUI_objSetHandlerFunc(&GUI_FFT_numInputInterfaceAction);
	
	GUI_createLabel(LABEL_ID0_INPUT_NUM_X0,	LABEL_ID0_INPUT_NUM_X1,
									LABEL_ID0_INPUT_NUM_Y0,	LABEL_ID0_INPUT_NUM_Y1,
									LABEL_ID0_INPUT_NUM_BORDER,
									LABEL_ID0_INPUT_NUM_MAIN_COLOR,
									LABEL_ID0_INPUT_NUM_BORDER_COLOR,
									LABEL_ID0_INPUT_NUM_TEXT,
									LABEL_ID0_INPUT_NUM_TEXT_COLOR,
									LABEL_ID0_INPUT_NUM_TEXT_FONT,
									LABEL_ID0_INPUT_NUM_TEXT_MARGIN_X,
									LABEL_ID0_INPUT_NUM_TEXT_MARGIN_Y,
									LABEL_ID0_INPUT_NUM_ACTION_PTR);
	
	GUI_createButton(BUTTON_ID0_1_X0,	BUTTON_ID0_1_X1,
									BUTTON_ID0_1_Y0,		BUTTON_ID0_1_Y1,
									BUTTON_ID0_1_BORDER,
									BUTTON_ID0_1_MAIN_COLOR,
									BUTTON_ID0_1_BORDER_COLOR,
									BUTTON_ID0_1_TEXT,
									BUTTON_ID0_1_TEXT_COLOR,
									BUTTON_ID0_1_TEXT_FONT,
									BUTTON_ID0_1_TEXT_MARGIN_X,
									BUTTON_ID0_1_TEXT_MARGIN_Y,
									BUTTON_ID0_1_STATE,
									BUTTON_ID0_1_DELAY_SEC,
									BUTTON_ID0_1_ACTION_PTR);
	GUI_createButton(BUTTON_ID1_2_X0,	BUTTON_ID1_2_X1,
									BUTTON_ID1_2_Y0,		BUTTON_ID1_2_Y1,
									BUTTON_ID1_2_BORDER,
									BUTTON_ID1_2_MAIN_COLOR,
									BUTTON_ID1_2_BORDER_COLOR,
									BUTTON_ID1_2_TEXT,
									BUTTON_ID1_2_TEXT_COLOR,
									BUTTON_ID1_2_TEXT_FONT,
									BUTTON_ID1_2_TEXT_MARGIN_X,
									BUTTON_ID1_2_TEXT_MARGIN_Y,
									BUTTON_ID1_2_STATE,
									BUTTON_ID1_2_DELAY_SEC,
									BUTTON_ID1_2_ACTION_PTR);
	GUI_createButton(BUTTON_ID2_3_X0,	BUTTON_ID2_3_X1,
									BUTTON_ID2_3_Y0,		BUTTON_ID2_3_Y1,
									BUTTON_ID2_3_BORDER,
									BUTTON_ID2_3_MAIN_COLOR,
									BUTTON_ID2_3_BORDER_COLOR,
									BUTTON_ID2_3_TEXT,
									BUTTON_ID2_3_TEXT_COLOR,
									BUTTON_ID2_3_TEXT_FONT,
									BUTTON_ID2_3_TEXT_MARGIN_X,
									BUTTON_ID2_3_TEXT_MARGIN_Y,
									BUTTON_ID2_3_STATE,
									BUTTON_ID2_3_DELAY_SEC,
									BUTTON_ID2_3_ACTION_PTR);
	GUI_createButton(BUTTON_ID3_4_X0,	BUTTON_ID3_4_X1,
									BUTTON_ID3_4_Y0,		BUTTON_ID3_4_Y1,
									BUTTON_ID3_4_BORDER,
									BUTTON_ID3_4_MAIN_COLOR,
									BUTTON_ID3_4_BORDER_COLOR,
									BUTTON_ID3_4_TEXT,
									BUTTON_ID3_4_TEXT_COLOR,
									BUTTON_ID3_4_TEXT_FONT,
									BUTTON_ID3_4_TEXT_MARGIN_X,
									BUTTON_ID3_4_TEXT_MARGIN_Y,
									BUTTON_ID3_4_STATE,
									BUTTON_ID3_4_DELAY_SEC,
									BUTTON_ID3_4_ACTION_PTR);
	GUI_createButton(BUTTON_ID4_5_X0,	BUTTON_ID4_5_X1,
									BUTTON_ID4_5_Y0,		BUTTON_ID4_5_Y1,
									BUTTON_ID4_5_BORDER,
									BUTTON_ID4_5_MAIN_COLOR,
									BUTTON_ID4_5_BORDER_COLOR,
									BUTTON_ID4_5_TEXT,
									BUTTON_ID4_5_TEXT_COLOR,
									BUTTON_ID4_5_TEXT_FONT,
									BUTTON_ID4_5_TEXT_MARGIN_X,
									BUTTON_ID4_5_TEXT_MARGIN_Y,
									BUTTON_ID4_5_STATE,
									BUTTON_ID4_5_DELAY_SEC,
									BUTTON_ID4_5_ACTION_PTR);
	GUI_createButton(BUTTON_ID5_6_X0,	BUTTON_ID5_6_X1,
									BUTTON_ID5_6_Y0,		BUTTON_ID5_6_Y1,
									BUTTON_ID5_6_BORDER,
									BUTTON_ID5_6_MAIN_COLOR,
									BUTTON_ID5_6_BORDER_COLOR,
									BUTTON_ID5_6_TEXT,
									BUTTON_ID5_6_TEXT_COLOR,
									BUTTON_ID5_6_TEXT_FONT,
									BUTTON_ID5_6_TEXT_MARGIN_X,
									BUTTON_ID5_6_TEXT_MARGIN_Y,
									BUTTON_ID5_6_STATE,
									BUTTON_ID5_6_DELAY_SEC,
									BUTTON_ID5_6_ACTION_PTR);
	GUI_createButton(BUTTON_ID6_7_X0,	BUTTON_ID6_7_X1,
									BUTTON_ID6_7_Y0,		BUTTON_ID6_7_Y1,
									BUTTON_ID6_7_BORDER,
									BUTTON_ID6_7_MAIN_COLOR,
									BUTTON_ID6_7_BORDER_COLOR,
									BUTTON_ID6_7_TEXT,
									BUTTON_ID6_7_TEXT_COLOR,
									BUTTON_ID6_7_TEXT_FONT,
									BUTTON_ID6_7_TEXT_MARGIN_X,
									BUTTON_ID6_7_TEXT_MARGIN_Y,
									BUTTON_ID6_7_STATE,
									BUTTON_ID6_7_DELAY_SEC,
									BUTTON_ID6_7_ACTION_PTR);
	GUI_createButton(BUTTON_ID7_8_X0,	BUTTON_ID7_8_X1,
									BUTTON_ID7_8_Y0,		BUTTON_ID7_8_Y1,
									BUTTON_ID7_8_BORDER,
									BUTTON_ID7_8_MAIN_COLOR,
									BUTTON_ID7_8_BORDER_COLOR,
									BUTTON_ID7_8_TEXT,
									BUTTON_ID7_8_TEXT_COLOR,
									BUTTON_ID7_8_TEXT_FONT,
									BUTTON_ID7_8_TEXT_MARGIN_X,
									BUTTON_ID7_8_TEXT_MARGIN_Y,
									BUTTON_ID7_8_STATE,
									BUTTON_ID7_8_DELAY_SEC,
									BUTTON_ID7_8_ACTION_PTR);
	GUI_createButton(BUTTON_ID8_9_X0,	BUTTON_ID8_9_X1,
									BUTTON_ID8_9_Y0,		BUTTON_ID8_9_Y1,
									BUTTON_ID8_9_BORDER,
									BUTTON_ID8_9_MAIN_COLOR,
									BUTTON_ID8_9_BORDER_COLOR,
									BUTTON_ID8_9_TEXT,
									BUTTON_ID8_9_TEXT_COLOR,
									BUTTON_ID8_9_TEXT_FONT,
									BUTTON_ID8_9_TEXT_MARGIN_X,
									BUTTON_ID8_9_TEXT_MARGIN_Y,
									BUTTON_ID8_9_STATE,
									BUTTON_ID8_9_DELAY_SEC,
									BUTTON_ID8_9_ACTION_PTR);
	GUI_createButton(BUTTON_ID9_0_X0,	BUTTON_ID9_0_X1,
									BUTTON_ID9_0_Y0,		BUTTON_ID9_0_Y1,
									BUTTON_ID9_0_BORDER,
									BUTTON_ID9_0_MAIN_COLOR,
									BUTTON_ID9_0_BORDER_COLOR,
									BUTTON_ID9_0_TEXT,
									BUTTON_ID9_0_TEXT_COLOR,
									BUTTON_ID9_0_TEXT_FONT,
									BUTTON_ID9_0_TEXT_MARGIN_X,
									BUTTON_ID9_0_TEXT_MARGIN_Y,
									BUTTON_ID9_0_STATE,
									BUTTON_ID9_0_DELAY_SEC,
									BUTTON_ID9_0_ACTION_PTR);
	GUI_createButton(BUTTON_ID10_CLR_X0,	BUTTON_ID10_CLR_X1,
									BUTTON_ID10_CLR_Y0,		BUTTON_ID10_CLR_Y1,
									BUTTON_ID10_CLR_BORDER,
									BUTTON_ID10_CLR_MAIN_COLOR,
									BUTTON_ID10_CLR_BORDER_COLOR,
									BUTTON_ID10_CLR_TEXT,
									BUTTON_ID10_CLR_TEXT_COLOR,
									BUTTON_ID10_CLR_TEXT_FONT,
									BUTTON_ID10_CLR_TEXT_MARGIN_X,
									BUTTON_ID10_CLR_TEXT_MARGIN_Y,
									BUTTON_ID10_CLR_STATE,
									BUTTON_ID10_CLR_DELAY_SEC,
									BUTTON_ID10_CLR_ACTION_PTR);
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
}


void GUI_FFT_numInputInterfaceAction(void)
{
	static char inputNumStrPrev[5] = {0};
	
	if(strcmp(inputNumStrPrev, inputNumStr) != 0)
	{
		GUI_labelChangeText(LABEL_INPUT_NUM_ID, inputNumStr, LABEL_ID0_INPUT_NUM_TEXT_COLOR, LABEL_ID0_INPUT_NUM_TEXT_FONT);
		strcpy(inputNumStrPrev, inputNumStr);
	}
}


void GUI_FFT_numButtonClick(char ch)
{
	char* pInputNumStr = &inputNumStr;
	uint8_t strLen = 0;
	
	if((strLen = strlen(pInputNumStr)) < 4)
	{		
		pInputNumStr[strLen++] = ch;
		pInputNumStr[strLen] = '\0';
	}
}


void GUI_FFT_numButtonClick_1(void)
{
	GUI_FFT_numButtonClick('1');
}

void GUI_FFT_numButtonClick_2(void)
{
	GUI_FFT_numButtonClick('2');
}

void GUI_FFT_numButtonClick_3(void)
{
	GUI_FFT_numButtonClick('3');
}

void GUI_FFT_numButtonClick_4(void)
{
	GUI_FFT_numButtonClick('4');
}

void GUI_FFT_numButtonClick_5(void)
{
	GUI_FFT_numButtonClick('5');
}

void GUI_FFT_numButtonClick_6(void)
{
	GUI_FFT_numButtonClick('6');
}

void GUI_FFT_numButtonClick_7(void)
{
	GUI_FFT_numButtonClick('7');
}

void GUI_FFT_numButtonClick_8(void)
{
	GUI_FFT_numButtonClick('8');
}

void GUI_FFT_numButtonClick_9(void)
{
	GUI_FFT_numButtonClick('9');
}

void GUI_FFT_numButtonClick_0(void)
{
	GUI_FFT_numButtonClick('0');
}

void GUI_FFT_entrButtonClick(void)
{
	inputNum = (uint16_t)atoi(inputNumStr);
	freqBlock = calcFreqBlock(inputNum);
	appState = 1;
}


void GUI_FFT_clrButtonClick(void)
{
	inputNumStr[0] = '\0';
}


void GUI_FFT_changeFreqButtonClick(void)
{
	appState = 3;
}

