
#ifndef GUI_FFT_H
	#define GUI_FFT_H

	// 
	#include "link.h"


	#define	LABEL_INPUT_NUM_ID											0
	#define	LABEL_ID0_INPUT_NUM_X0									70-1
	#define	LABEL_ID0_INPUT_NUM_X1									170-1
	#define	LABEL_ID0_INPUT_NUM_Y0									240-1
	#define	LABEL_ID0_INPUT_NUM_Y1									270-1
	#define	LABEL_ID0_INPUT_NUM_BORDER							2
	#define	LABEL_ID0_INPUT_NUM_MAIN_COLOR					0x0000
	#define	LABEL_ID0_INPUT_NUM_BORDER_COLOR				0x0000
	#define	LABEL_ID0_INPUT_NUM_TEXT								"0"
	#define	LABEL_ID0_INPUT_NUM_TEXT_COLOR					0xFFFF
	#define	LABEL_ID0_INPUT_NUM_TEXT_FONT						&impact_18ptFontInfo
	#define	LABEL_ID0_INPUT_NUM_TEXT_MARGIN_X				10
	#define	LABEL_ID0_INPUT_NUM_TEXT_MARGIN_Y				3
	#define	LABEL_ID0_INPUT_NUM_ACTION_PTR					0
	
	#define	LABEL_FREQ_ID											0
	#define	LABEL_ID1_FREQ_X0									187-1
	#define	LABEL_ID1_FREQ_X1									LCD_WIDTH-1-3
	#define	LABEL_ID1_FREQ_Y0									250-1
	#define	LABEL_ID1_FREQ_Y1									275-1
	#define	LABEL_ID1_FREQ_BORDER							1
	#define	LABEL_ID1_FREQ_MAIN_COLOR					0x0000
	#define	LABEL_ID1_FREQ_BORDER_COLOR				0x0000
	#define	LABEL_ID1_FREQ_TEXT								"0"
	#define	LABEL_ID1_FREQ_TEXT_COLOR					0xFFFF
	#define	LABEL_ID1_FREQ_TEXT_FONT					&impact_18ptFontInfo
	#define	LABEL_ID1_FREQ_TEXT_MARGIN_X			3
	#define	LABEL_ID1_FREQ_TEXT_MARGIN_Y			0
	#define	LABEL_ID1_FREQ_ACTION_PTR					0
	
	#define	BUTTON_1_ID													0
	#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID0_1_X0											50-1
	#define	BUTTON_ID0_1_X1											100-1
	#define	BUTTON_ID0_1_Y0											170-1
	#define	BUTTON_ID0_1_Y1											220-1
	#define	BUTTON_ID0_1_BORDER									4
	#define	BUTTON_ID0_1_MAIN_COLOR							0x7569
	#define	BUTTON_ID0_1_BORDER_COLOR						0x0000
	#define	BUTTON_ID0_1_TEXT										"1"
	#define	BUTTON_ID0_1_TEXT_COLOR							0x0000
	#define	BUTTON_ID0_1_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID0_1_TEXT_MARGIN_X					20
	#define	BUTTON_ID0_1_TEXT_MARGIN_Y					10
	#define	BUTTON_ID0_1_STATE									0
	#define	BUTTON_ID0_1_DELAY_SEC							100
	#define	BUTTON_ID0_1_ACTION_PTR							GUI_FFT_numButtonClick_1
	
	#define	BUTTON_2_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID1_2_X0											100-1
	#define	BUTTON_ID1_2_X1											150-1
	#define	BUTTON_ID1_2_Y0											170-1
	#define	BUTTON_ID1_2_Y1											220-1
	#define	BUTTON_ID1_2_BORDER									4
	#define	BUTTON_ID1_2_MAIN_COLOR							0x7569
	#define	BUTTON_ID1_2_BORDER_COLOR						0x0000
	#define	BUTTON_ID1_2_TEXT										"2"
	#define	BUTTON_ID1_2_TEXT_COLOR							0x0000
	#define	BUTTON_ID1_2_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID1_2_TEXT_MARGIN_X					20
	#define	BUTTON_ID1_2_TEXT_MARGIN_Y					10
	#define	BUTTON_ID1_2_STATE									0
	#define	BUTTON_ID1_2_DELAY_SEC							100
	#define	BUTTON_ID1_2_ACTION_PTR							GUI_FFT_numButtonClick_2	

	#define	BUTTON_3_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID2_3_X0											150-1
	#define	BUTTON_ID2_3_X1											200-1
	#define	BUTTON_ID2_3_Y0											170-1
	#define	BUTTON_ID2_3_Y1											220-1
	#define	BUTTON_ID2_3_BORDER									4
	#define	BUTTON_ID2_3_MAIN_COLOR							0x7569
	#define	BUTTON_ID2_3_BORDER_COLOR						0x0000
	#define	BUTTON_ID2_3_TEXT										"3"
	#define	BUTTON_ID2_3_TEXT_COLOR							0x0000
	#define	BUTTON_ID2_3_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID2_3_TEXT_MARGIN_X					20
	#define	BUTTON_ID2_3_TEXT_MARGIN_Y					10
	#define	BUTTON_ID2_3_STATE									0
	#define	BUTTON_ID2_3_DELAY_SEC							100
	#define	BUTTON_ID2_3_ACTION_PTR							GUI_FFT_numButtonClick_3

	#define	BUTTON_4_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID3_4_X0											50-1
	#define	BUTTON_ID3_4_X1											100-1
	#define	BUTTON_ID3_4_Y0											120-1
	#define	BUTTON_ID3_4_Y1											170-1
	#define	BUTTON_ID3_4_BORDER									4
	#define	BUTTON_ID3_4_MAIN_COLOR							0x7569
	#define	BUTTON_ID3_4_BORDER_COLOR						0x0000
	#define	BUTTON_ID3_4_TEXT										"4"
	#define	BUTTON_ID3_4_TEXT_COLOR							0x0000
	#define	BUTTON_ID3_4_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID3_4_TEXT_MARGIN_X					20
	#define	BUTTON_ID3_4_TEXT_MARGIN_Y					10
	#define	BUTTON_ID3_4_STATE									0
	#define	BUTTON_ID3_4_DELAY_SEC							100
	#define	BUTTON_ID3_4_ACTION_PTR							GUI_FFT_numButtonClick_4
	
	#define	BUTTON_5_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID4_5_X0											100-1
	#define	BUTTON_ID4_5_X1											150-1
	#define	BUTTON_ID4_5_Y0											120-1
	#define	BUTTON_ID4_5_Y1											170-1
	#define	BUTTON_ID4_5_BORDER									4
	#define	BUTTON_ID4_5_MAIN_COLOR							0x7569
	#define	BUTTON_ID4_5_BORDER_COLOR						0x0000
	#define	BUTTON_ID4_5_TEXT										"5"
	#define	BUTTON_ID4_5_TEXT_COLOR							0x0000
	#define	BUTTON_ID4_5_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID4_5_TEXT_MARGIN_X					20
	#define	BUTTON_ID4_5_TEXT_MARGIN_Y					10
	#define	BUTTON_ID4_5_STATE									0
	#define	BUTTON_ID4_5_DELAY_SEC							100
	#define	BUTTON_ID4_5_ACTION_PTR							GUI_FFT_numButtonClick_5
	
	#define	BUTTON_6_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID5_6_X0											150-1
	#define	BUTTON_ID5_6_X1											200-1
	#define	BUTTON_ID5_6_Y0											120-1
	#define	BUTTON_ID5_6_Y1											170-1
	#define	BUTTON_ID5_6_BORDER									4
	#define	BUTTON_ID5_6_MAIN_COLOR							0x7569
	#define	BUTTON_ID5_6_BORDER_COLOR						0x0000
	#define	BUTTON_ID5_6_TEXT										"6"
	#define	BUTTON_ID5_6_TEXT_COLOR							0x0000
	#define	BUTTON_ID5_6_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID5_6_TEXT_MARGIN_X					20
	#define	BUTTON_ID5_6_TEXT_MARGIN_Y					10
	#define	BUTTON_ID5_6_STATE									0
	#define	BUTTON_ID5_6_DELAY_SEC							100
	#define	BUTTON_ID5_6_ACTION_PTR							GUI_FFT_numButtonClick_6
	
	#define	BUTTON_7_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID6_7_X0											50-1
	#define	BUTTON_ID6_7_X1											100-1
	#define	BUTTON_ID6_7_Y0											70-1
	#define	BUTTON_ID6_7_Y1											120-1
	#define	BUTTON_ID6_7_BORDER									4
	#define	BUTTON_ID6_7_MAIN_COLOR							0x7569
	#define	BUTTON_ID6_7_BORDER_COLOR						0x0000
	#define	BUTTON_ID6_7_TEXT										"7"
	#define	BUTTON_ID6_7_TEXT_COLOR							0x0000
	#define	BUTTON_ID6_7_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID6_7_TEXT_MARGIN_X					20
	#define	BUTTON_ID6_7_TEXT_MARGIN_Y					10
	#define	BUTTON_ID6_7_STATE									0
	#define	BUTTON_ID6_7_DELAY_SEC							100
	#define	BUTTON_ID6_7_ACTION_PTR							GUI_FFT_numButtonClick_7
	
	#define	BUTTON_8_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID7_8_X0											100-1
	#define	BUTTON_ID7_8_X1											150-1
	#define	BUTTON_ID7_8_Y0											70-1
	#define	BUTTON_ID7_8_Y1											120-1
	#define	BUTTON_ID7_8_BORDER									4
	#define	BUTTON_ID7_8_MAIN_COLOR							0x7569
	#define	BUTTON_ID7_8_BORDER_COLOR						0x0000
	#define	BUTTON_ID7_8_TEXT										"8"
	#define	BUTTON_ID7_8_TEXT_COLOR							0x0000
	#define	BUTTON_ID7_8_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID7_8_TEXT_MARGIN_X					20
	#define	BUTTON_ID7_8_TEXT_MARGIN_Y					10
	#define	BUTTON_ID7_8_STATE									0
	#define	BUTTON_ID7_8_DELAY_SEC							100
	#define	BUTTON_ID7_8_ACTION_PTR							GUI_FFT_numButtonClick_8
	
	#define	BUTTON_9_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID8_9_X0											150-1
	#define	BUTTON_ID8_9_X1											200-1
	#define	BUTTON_ID8_9_Y0											70-1
	#define	BUTTON_ID8_9_Y1											120-1
	#define	BUTTON_ID8_9_BORDER									4
	#define	BUTTON_ID8_9_MAIN_COLOR							0x7569
	#define	BUTTON_ID8_9_BORDER_COLOR						0x0000
	#define	BUTTON_ID8_9_TEXT										"9"
	#define	BUTTON_ID8_9_TEXT_COLOR							0x0000
	#define	BUTTON_ID8_9_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID8_9_TEXT_MARGIN_X					20
	#define	BUTTON_ID8_9_TEXT_MARGIN_Y					10
	#define	BUTTON_ID8_9_STATE									0
	#define	BUTTON_ID8_9_DELAY_SEC							100
	#define	BUTTON_ID8_9_ACTION_PTR							GUI_FFT_numButtonClick_9
	
	#define	BUTTON_0_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID9_0_X0											100-1
	#define	BUTTON_ID9_0_X1											150-1
	#define	BUTTON_ID9_0_Y0											20-1
	#define	BUTTON_ID9_0_Y1											70-1
	#define	BUTTON_ID9_0_BORDER									4
	#define	BUTTON_ID9_0_MAIN_COLOR							0x7569
	#define	BUTTON_ID9_0_BORDER_COLOR						0x0000
	#define	BUTTON_ID9_0_TEXT										"0"
	#define	BUTTON_ID9_0_TEXT_COLOR							0x0000
	#define	BUTTON_ID9_0_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID9_0_TEXT_MARGIN_X					20
	#define	BUTTON_ID9_0_TEXT_MARGIN_Y					10
	#define	BUTTON_ID9_0_STATE									0
	#define	BUTTON_ID9_0_DELAY_SEC							100
	#define	BUTTON_ID9_0_ACTION_PTR							GUI_FFT_numButtonClick_0
	
	#define	BUTTON_CLR_ID												0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID10_CLR_X0										50-1
	#define	BUTTON_ID10_CLR_X1										100-1
	#define	BUTTON_ID10_CLR_Y0										20-1
	#define	BUTTON_ID10_CLR_Y1										70-1
	#define	BUTTON_ID10_CLR_BORDER								4
	#define	BUTTON_ID10_CLR_MAIN_COLOR						0x7569
	#define	BUTTON_ID10_CLR_BORDER_COLOR					0x0000
	#define	BUTTON_ID10_CLR_TEXT									"."
	#define	BUTTON_ID10_CLR_TEXT_COLOR						0x0000
	#define	BUTTON_ID10_CLR_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID10_CLR_TEXT_MARGIN_X					20
	#define	BUTTON_ID10_CLR_TEXT_MARGIN_Y					10
	#define	BUTTON_ID10_CLR_STATE									0
	#define	BUTTON_ID10_CLR_DELAY_SEC							100
	#define	BUTTON_ID10_CLR_ACTION_PTR						GUI_FFT_clrButtonClick
	
	#define	BUTTON_ENTR_ID													0
	//#define	BUTTON_TPLUS_CLICK_COLOR						0xFF20
	#define	BUTTON_ID11_ENTR_X0											150-1
	#define	BUTTON_ID11_ENTR_X1											200-1
	#define	BUTTON_ID11_ENTR_Y0											20-1
	#define	BUTTON_ID11_ENTR_Y1											70-1
	#define	BUTTON_ID11_ENTR_BORDER									4
	#define	BUTTON_ID11_ENTR_MAIN_COLOR							0x7569
	#define	BUTTON_ID11_ENTR_BORDER_COLOR						0x0000
	#define	BUTTON_ID11_ENTR_TEXT										":"
	#define	BUTTON_ID11_ENTR_TEXT_COLOR							0x0000
	#define	BUTTON_ID11_ENTR_TEXT_FONT							&impact_18ptFontInfo
	#define	BUTTON_ID11_ENTR_TEXT_MARGIN_X					20
	#define	BUTTON_ID11_ENTR_TEXT_MARGIN_Y					10
	#define	BUTTON_ID11_ENTR_STATE									0
	#define	BUTTON_ID11_ENTR_DELAY_SEC							100
	#define	BUTTON_ID11_ENTR_ACTION_PTR							GUI_FFT_entrButtonClick
	
	#define	BUTTON_CHANGE_FREQ_ID										0
	//#define	BUTTON_TPLUS_CLICK_COLOR							0xFF20
	#define	BUTTON_ID12_CHANGE_FREQ_X0							200-1
	#define	BUTTON_ID12_CHANGE_FREQ_X1							LCD_WIDTH-1-10
	#define	BUTTON_ID12_CHANGE_FREQ_Y0							280-1
	#define	BUTTON_ID12_CHANGE_FREQ_Y1							LCD_HEIGHT-1-10
	#define	BUTTON_ID12_CHANGE_FREQ_BORDER					4
	#define	BUTTON_ID12_CHANGE_FREQ_MAIN_COLOR			0x7569
	#define	BUTTON_ID12_CHANGE_FREQ_BORDER_COLOR		0x0000
	#define	BUTTON_ID12_CHANGE_FREQ_TEXT						0
	#define	BUTTON_ID12_CHANGE_FREQ_TEXT_COLOR			0x0000
	#define	BUTTON_ID12_CHANGE_FREQ_TEXT_FONT				&impact_18ptFontInfo
	#define	BUTTON_ID12_CHANGE_FREQ_TEXT_MARGIN_X		0
	#define	BUTTON_ID12_CHANGE_FREQ_TEXT_MARGIN_Y		0
	#define	BUTTON_ID12_CHANGE_FREQ_STATE						0
	#define	BUTTON_ID12_CHANGE_FREQ_DELAY_SEC				100
	#define	BUTTON_ID12_CHANGE_FREQ_ACTION_PTR			GUI_FFT_changeFreqButtonClick
	
	
	extern char inputNumStr[5];
	extern uint16_t inputNum;
	extern uint16_t appState;
	

	void GUI_FFT_numInputInterfaceInit(void);
	void GUI_FFT_numInputInterfaceAction(void);
	void GUI_FFT_numButtonClick(char ch);
	void GUI_FFT_numButtonClick_1(void);
	void GUI_FFT_numButtonClick_2(void);
	void GUI_FFT_numButtonClick_3(void);
	void GUI_FFT_numButtonClick_4(void);
	void GUI_FFT_numButtonClick_5(void);
	void GUI_FFT_numButtonClick_6(void);
	void GUI_FFT_numButtonClick_7(void);
	void GUI_FFT_numButtonClick_8(void);
	void GUI_FFT_numButtonClick_9(void);
	void GUI_FFT_numButtonClick_0(void);
	
	void GUI_FFT_entrButtonClick(void);
	
	void GUI_FFT_clrButtonClick(void);
	
	void GUI_FFT_changeFreqButtonClick(void);
	

#endif
