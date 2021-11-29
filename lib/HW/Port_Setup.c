
#include "Port_Setup.h"


// SYS.00005 Настройка портов входных разовых команд
void portSetupGpi(void)
{
	;//portsSetupAsInput(ADR_1_MCU_PORT, 					ADR_1_MCU_PIN);							// Сигнал с адресной перемычки ADR_1
}


// SYS.00006 Настройка портов выходных разовых команд
void portSetupGpo(void)
{
	portsSetupAsOutput(DO_LCD_DC_PORT,	DO_LCD_DC_PIN);
	portsSetupAsOutput(DO_LCD_LED_PORT,	DO_LCD_LED_PIN);
	portsSetupAsOutput(DO_LCD_RST_PORT,	DO_LCD_RST_PIN);
}


// SYS.00013 Настройка портов SPI2
void portSetupSpi2(void)
{
	// SSP2_RXD
	portSetupFunc(SPI2_LCD_RXD_PORT,		SPI2_LCD_RXD_PIN,	PORT_FUNC_ALTER);
	portSetupOe(SPI2_LCD_RXD_PORT,			SPI2_LCD_RXD_PIN,	PORT_OE_IN);
	portSetupMode(SPI2_LCD_RXD_PORT,		SPI2_LCD_RXD_PIN,	PORT_MODE_DIGITAL);
	portSetupPdShm(SPI2_LCD_RXD_PORT,		SPI2_LCD_RXD_PIN,	PORT_PD_SHM_OFF);
	portSetupPd(SPI2_LCD_RXD_PORT,			SPI2_LCD_RXD_PIN,	PORT_PD_DRIVER);
	portSetupSpeed(SPI2_LCD_RXD_PORT,		SPI2_LCD_RXD_PIN,	PORT_SPEED_MAXFAST);
	
	// SSP2_TXD
	portSetupFunc(SPI2_LCD_TXD_PORT,		SPI2_LCD_TXD_PIN,	PORT_FUNC_ALTER);
	portSetupOe(SPI2_LCD_TXD_PORT,			SPI2_LCD_TXD_PIN,	PORT_OE_OUT);
	portSetupMode(SPI2_LCD_TXD_PORT,		SPI2_LCD_TXD_PIN,	PORT_MODE_DIGITAL);
	portSetupPdShm(SPI2_LCD_TXD_PORT,		SPI2_LCD_TXD_PIN,	PORT_PD_SHM_OFF);
	portSetupPd(SPI2_LCD_TXD_PORT,			SPI2_LCD_TXD_PIN,	PORT_PD_DRIVER);
	portSetupSpeed(SPI2_LCD_TXD_PORT,		SPI2_LCD_TXD_PIN,	PORT_SPEED_MAXFAST);
	
	// SSP2_CLK
	portSetupFunc(SPI2_LCD_SCLK_PORT,		SPI2_LCD_SCLK_PIN,	PORT_FUNC_ALTER);
	portSetupOe(SPI2_LCD_SCLK_PORT,			SPI2_LCD_SCLK_PIN,	PORT_OE_OUT);
	portSetupMode(SPI2_LCD_SCLK_PORT,		SPI2_LCD_SCLK_PIN,	PORT_MODE_DIGITAL);
	portSetupPdShm(SPI2_LCD_SCLK_PORT,	SPI2_LCD_SCLK_PIN,	PORT_PD_SHM_OFF);
	portSetupPd(SPI2_LCD_SCLK_PORT,			SPI2_LCD_SCLK_PIN,	PORT_PD_DRIVER);
	portSetupSpeed(SPI2_LCD_SCLK_PORT,	SPI2_LCD_SCLK_PIN,	PORT_SPEED_MAXFAST);
	
	// SSP2_FSS
	portsSetupAsOutput(SPI2_LCD_CS_PORT,	SPI2_LCD_CS_PIN);
	PORT_SetBits(SPI2_LCD_CS_PORT,	SPI2_LCD_CS_PIN);
}


// Настройка портов ADC
void portSetupAdc(void)
{
	portSetupOe(ADC_MIC_PORT,			ADC_MIC_PIN,	PORT_OE_IN);
	portSetupMode(ADC_MIC_PORT,		ADC_MIC_PIN,	PORT_MODE_ANALOG);
}


// SYS.00004 Инициализация портов
void portsSetup(void)
{
	//portSetupGpi();		// SYS.00005 Настройка портов входных разовых команд
	portSetupGpo();			// SYS.00006 Настройка портов выходных разовых команд
	portSetupSpi2();		// SYS.00013 Настройка портов SPI
	portSetupAdc();			// Настройка портов ADC
}
