
#ifndef PORT_SETUP_H
	#define PORT_SETUP_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// DI
	#define	DI_AD7091R_BUSY_PORT					MDR_PORTD
	#define	DI_AD7091R_BUSY_PIN						PORT_Pin_1	
	
	// DO
	#define	DO_LCD_DC_PORT								MDR_PORTA
	#define	DO_LCD_DC_PIN									PORT_Pin_6
	#define	DO_LCD_LED_PORT								MDR_PORTA
	#define	DO_LCD_LED_PIN								PORT_Pin_7
	#define	DO_LCD_RST_PORT								MDR_PORTE
	#define	DO_LCD_RST_PIN								PORT_Pin_7
		
	// SPI2
	#define	SPI2_LCD_TXD_PORT							MDR_PORTD
	#define	SPI2_LCD_TXD_PIN							PORT_Pin_6
	#define	SPI2_LCD_RXD_PORT							MDR_PORTD
	#define	SPI2_LCD_RXD_PIN							PORT_Pin_2
	#define	SPI2_LCD_SCLK_PORT						MDR_PORTD
	#define	SPI2_LCD_SCLK_PIN							PORT_Pin_5
	#define	SPI2_LCD_CS_PORT							MDR_PORTD
	#define	SPI2_LCD_CS_PIN								PORT_Pin_3

	// I2C
	
	// ADC
	#define	ADC_MIC_PORT									MDR_PORTD
	#define	ADC_MIC_PIN										PORT_Pin_4
	
	// прототипы функций
	void portsSetup(void);				// SYS.00004 Инициализация портов
	void portSetupGpi(void);			// SYS.00005 Настройка портов входных разовых команд
	void portSetupGpo(void);			// SYS.00006 Настройка портов выходных разовых команд
	void portSetupSpi2(void);			// SYS.00013 Настройка портов SPI2
	void portSetupAdc(void);			// Настройка портов ADC


#endif
