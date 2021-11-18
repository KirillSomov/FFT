
#ifndef PORT_SETUP_H
	#define PORT_SETUP_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// DI
	#define	ADR_ALL_MCU_PORT									MDR_PORTA
	#define	ADR_1_MCU_PORT										MDR_PORTA
	#define	ADR_1_MCU_PIN											PORT_Pin_0
	#define	ADR_2_MCU_PORT										MDR_PORTA
	#define	ADR_2_MCU_PIN											PORT_Pin_1
	#define	ADR_3_MCU_PORT										MDR_PORTA
	#define	ADR_3_MCU_PIN											PORT_Pin_2
	#define	ADR_4_MCU_PORT										MDR_PORTA
	#define	ADR_4_MCU_PIN											PORT_Pin_3
	#define	ADR_5_MCU_PORT										MDR_PORTA
	#define	ADR_5_MCU_PIN											PORT_Pin_4
	#define	ADR_6_MCU_PORT										MDR_PORTA
	#define	ADR_6_MCU_PIN											PORT_Pin_5
	#define	ADR_7_MCU_PORT										MDR_PORTA
	#define	ADR_7_MCU_PIN											PORT_Pin_6
	#define	DI_MAIN_REZERV_MCU_PORT						MDR_PORTB
	#define	DI_MAIN_REZERV_MCU_PIN						PORT_Pin_10
	#define	DI_AD7091R_BUSY_PORT							MDR_PORTD
	#define	DI_AD7091R_BUSY_PIN								PORT_Pin_1	
	
	// DO
	#define	DO_CAN1_LED_GREEN_PORT						MDR_PORTE
	#define	DO_CAN1_LED_GREEN_PIN							PORT_Pin_2
	#define	DO_CAN2_LED_GREEN_PORT						MDR_PORTE
	#define	DO_CAN2_LED_GREEN_PIN							PORT_Pin_3
	#define	DO_MCU_STAT_LED_GREEN_PORT				MDR_PORTC
	#define	DO_MCU_STAT_LED_GREEN_PIN					PORT_Pin_1
	#define	DO_MCU_ERROR_LED_RED_PORT					MDR_PORTC
	#define	DO_MCU_ERROR_LED_RED_PIN					PORT_Pin_2	
	#define	DO_MCP_RES_MCU_PORT								MDR_PORTD
	#define	DO_MCP_RES_MCU_PIN								PORT_Pin_0
	#define	DO_AD7091R_RST_PORT								MDR_PORTD
	#define	DO_AD7091R_RST_PIN								PORT_Pin_7
	#define	DO_AD7091R_CNV_PORT								MDR_PORTD
	#define	DO_AD7091R_CNV_PIN								PORT_Pin_4
	#define	DO_MUX_ADR0_MCU_PORT							MDR_PORTB
	#define	DO_MUX_ADR0_MCU_PIN								PORT_Pin_5
	#define	DO_MUX_ADR1_MCU_PORT							MDR_PORTB
	#define	DO_MUX_ADR1_MCU_PIN								PORT_Pin_6
	#define	DO_MUX_EN_MCU_PORT								MDR_PORTB
	#define	DO_MUX_EN_MCU_PIN									PORT_Pin_7

	// CAN1
	#define	DO_CAN1_RX_MCU_PORT								MDR_PORTE
	#define	DO_CAN1_RX_MCU_PIN								PORT_Pin_0
	#define	DO_CAN1_TX_MCU_PORT								MDR_PORTE
	#define	DO_CAN1_TX_MCU_PIN								PORT_Pin_1
	
	// CAN2
	#define	DO_CAN2_RX_MCU_PORT								MDR_PORTE
	#define	DO_CAN2_RX_MCU_PIN								PORT_Pin_6
	#define	DO_CAN2_TX_MCU_PORT								MDR_PORTE
	#define	DO_CAN2_TX_MCU_PIN								PORT_Pin_7
	
	// SPI1
	#define	SPI1_MCP_SCK_MCU_PORT							MDR_PORTF
	#define	SPI1_MCP_SCK_MCU_PIN							PORT_Pin_1
	#define	SPI1_MCP_MISO_MCU_PORT						MDR_PORTF
	#define	SPI1_MCP_MISO_MCU_PIN							PORT_Pin_3
	#define	SPI1_MCP_MOSI_MCU_PORT						MDR_PORTF
	#define	SPI1_MCP_MOSI_MCU_PIN							PORT_Pin_0
	#define	SPI1_MCP_CS_MCU_0_PORT						MDR_PORTF
	#define	SPI1_MCP_CS_MCU_0_PIN							PORT_Pin_2
	#define	SPI1_MCP_CS_MCU_1_PORT						MDR_PORTA
	#define	SPI1_MCP_CS_MCU_1_PIN							PORT_Pin_7
	#define	SPI1_MCP_CS_MCU_2_PORT						MDR_PORTB
	#define	SPI1_MCP_CS_MCU_2_PIN							PORT_Pin_8
	#define	SPI1_MCP_CS_MCU_3_PORT						MDR_PORTB
	#define	SPI1_MCP_CS_MCU_3_PIN							PORT_Pin_9
	
	// SPI2
	#define	SPI2_LCD_SDI_PORT							MDR_PORTD
	#define	SPI2_LCD_SDI_PIN							PORT_Pin_6
	#define	SPI2_LCD_SDO_PORT							MDR_PORTD
	#define	SPI2_LCD_SDO_PIN							PORT_Pin_2
	#define	SPI2_LCD_SCLK_PORT						MDR_PORTD
	#define	SPI2_LCD_SCLK_PIN							PORT_Pin_5
	#define	SPI2_LCD_CS_PORT							MDR_PORTD
	#define	SPI2_LCD_CS_PIN								PORT_Pin_3	
	
	
	// прототипы функций
	void portsSetup(void);				// SYS.00004 Инициализация портов
	void portSetupGpi(void);			// SYS.00005 Настройка портов входных разовых команд
	void portSetupGpo(void);			// SYS.00006 Настройка портов выходных разовых команд
	void portSetupCanA(void);			// SYS.00008 Настройка CAN основной линии
	void portSetupCanB(void);			// SYS.00009 Настройка CAN резервной линии
	void portSetupSpi1(void);			// SYS.00013 Настройка портов SPI1
	void portSetupSpi2(void);			// SYS.00013 Настройка портов SPI2


#endif
