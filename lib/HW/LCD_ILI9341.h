
#ifndef LCD_ILI9341_H
	#define LCD_ILI9341_H


	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// управление линией
	// посылка команды/данных
	#define LCD_DC_RESET  	GPIO_ResetBits(GPIOC, GPIO_Pin_9)
	#define LCD_DC_SET    	GPIO_SetBits(GPIOC, GPIO_Pin_9)

	// вкл/выкл LCD
	#define LCD_RST_RESET		GPIO_ResetBits(GPIOD, GPIO_Pin_3)
	#define LCD_RST_SET			GPIO_SetBits(GPIOD, GPIO_Pin_3)

	// вкл/выкл подсветки LCD
	//#define	LCD_LED_OFF			MDR_PORTA->RXTX &= ~(1 << 7)
	//#define	LCD_LED_ON			MDR_PORTA->RXTX |=	(1 << 7)


	// параметры LCD
	#define LCD_WIDTH      		240
	#define LCD_HEIGHT      	320
	#define LCD_PIXEL_COUNT		LCD_WIDTH * LCD_HEIGHT


	// команды
	#define ILI9341_RESET					0x01
	#define ILI9341_SLEEP_OUT			0x11
	#define ILI9341_GAMMA					0x26
	#define ILI9341_DISPLAY_OFF		0x28
	#define ILI9341_DISPLAY_ON		0x29
	#define ILI9341_COLUMN_ADDR		0x2A
	#define ILI9341_PAGE_ADDR			0x2B
	#define ILI9341_GRAM					0x2C
	#define ILI9341_MAC			      0x36
	#define ILI9341_PIXEL_FORMAT  0x3A
	#define ILI9341_WDB			    	0x51
	#define ILI9341_WCD				    0x53
	#define ILI9341_RGB_INTERFACE	0xB0
	#define ILI9341_FRC				    0xB1
	#define ILI9341_BPC				    0xB5
	#define ILI9341_DFC				    0xB6
	#define ILI9341_POWER1				0xC0
	#define ILI9341_POWER2				0xC1
	#define ILI9341_VCOM1					0xC5
	#define ILI9341_VCOM2					0xC7
	#define ILI9341_POWERA				0xCB
	#define ILI9341_POWERB				0xCF
	#define ILI9341_PGAMMA				0xE0
	#define ILI9341_NGAMMA				0xE1
	#define ILI9341_DTCA					0xE8
	#define ILI9341_DTCB					0xEA
	#define ILI9341_POWER_SEQ			0xED
	#define ILI9341_3GAMMA_EN			0xF2
	#define ILI9341_INTERFACE			0xF6
	#define ILI9341_PRC				    0xF7


	// прототипы функций
	void 			LCD_sendCommand(uint16_t com);																						// посылка команды
	void 			LCD_sendData(uint16_t data);																							// посылка данных
	
	void 			LCD_init(void);																														// инициализация LCD
	
	void 			LCD_setCursorPosition(uint16_t x1, uint16_t y1,
																	uint16_t x2, uint16_t y2);													// установка курсора на LCD
	
	void 			LCD_fill(uint16_t color);																									// заливка всего экрана цветом
	
	void 			LCD_drawPixel(uint16_t x, uint16_t y,
														 uint16_t color);																					// отрисовка пикселя
	void 			LCD_drawFilledRectangle(uint16_t x0, uint16_t x1,
																		uint16_t y0, uint16_t y1,
																				uint16_t color);															// закрасить область
	
	void			LCD_drawPicture(uint32_t	x,	uint32_t	y,
														uint16_t	pictureColor,
														const	struct pictureInfo *pictureInfoStruct);							// отрисовка картинки
	
	uint16_t	LCD_printChar(uint32_t x,	uint32_t y,
													uint16_t	symbol,
													uint16_t	fontColor,
													const struct fontInfo *fontInfoStruct);
	uint16_t	LCD_printString(uint32_t x, uint32_t y,
														char* str,	uint16_t fontColor,
														const struct fontInfo *fontInfoStruct);

	
#endif
