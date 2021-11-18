
#include "CPU.h"


// SYS.00001 Требования к настройке тактирования микроконтроллера
void clockSetup(void)
{	
	clockCpuSetup();
	clockPeriphInit();
}


// SYS.00002 Настройка тактирования ядра процессора
bool clockCpuSetup(void)
{
	// наличие ошибки
	bool oscFailure = true;
	
	// задержка памяти программ - 3 цикла
	MDR_EEPROM->CMD |= (3 << 3);
	
	// установка бита HSE_ON
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	
	// проверка установки флага выхода в рабочий режим осциллятора HSE
	if(RST_CLK_HSEstatus() == SUCCESS)
	{
		// установка прошла успешно
		// конфигурация умножителя: источник - HSE с k = 1, Коэф. умнож. = 10
		RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);
		
		// включение умножителя PLL
		RST_CLK_CPU_PLLcmd(ENABLE);
		
		// проверка установки флага выхода в рабочий режим CPU_PLL
		while(RST_CLK_CPU_PLLstatus() != SUCCESS)	{;}
		
		if(RST_CLK_CPU_PLLstatus() == SUCCESS)
		{
			// установка прошла успешно
			// установка PLLCPUo как вход CPU_C2
			RST_CLK_CPU_PLLuse(ENABLE);
			
			// установка предделителя CPU_C3 = 1
			RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
			
			// установка CPU_C2 как вход для CPU_C3
			RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
			
			// обновить конфигурацию тактирования
			SystemCoreClockUpdate();
			
			// установка прошла успешно
			oscFailure = false;
		}
	}
	
	// выбор режима работы встроенного регулятора напряжения DUcc
	MDR_BKP->REG_0E	|=	(7 << 0);	// частота более 80 МГц
	// установка дополнительной стабилизирующей нагрузки для DUcc
	MDR_BKP->REG_0E	|=	(7 << 3);	// нагрузка 100 Ом, дополнительный ток потребления 19 мА
	
	return oscFailure;
}


// SYS.00003 Настройка тактирования периферии процессора
void clockPeriphInit(void)
{
	// включение тактирования портов
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF,		ENABLE);
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP,			ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP2,		ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC,			ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1,	ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2,	ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER3,	ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK,	ENABLE);
}
