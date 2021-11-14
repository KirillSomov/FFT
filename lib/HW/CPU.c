
#include "CPU.h"


/*======================================== CLOCKING ========================================*/
void Clock_Set(void)
{
	// тактирование
//	MDR_RST_CLK->PER_CLOCK |= ((1 << 7) 		// UART2
//														|(1 << 17)		// ADC
//														|(1 << 20)		// SSP2
//														|(1 << 21)		// PORTA
//														|(1 << 24)		// PORTD
//														|(1 << 25)		// PORTE
//														|(1 << 27));	// BKP
	
	MDR_RST_CLK->PER_CLOCK = 0xffffffff;  //
	
}
/*======================================== CLOCKING ========================================*/


/*======================================== PLL ========================================*/
void PLL_init(void)
{	
	while(!(MDR_BKP->REG_0F & (1 << 23))) {;} // ожидание установки флага генератора HSI_RDY в рабочий режим
		
	MDR_RST_CLK->CPU_CLOCK |= (0 << 0); // CPU_C1_SEL: выбор источника HSI
	
	MDR_RST_CLK->HS_CONTROL |= (1 << 0); // HSE_ON: включение внешнего осциллятора
			
	while(!(MDR_RST_CLK->CLOCK_STATUS & (1 << 2))) {;} // ожидание установки флага осциллятора HSE в рабочий режим
		
	MDR_RST_CLK->CPU_CLOCK |= (2 << 0); // CPU_C1_SEL: выбор источника HSE
		
	MDR_RST_CLK->PLL_CONTROL |= ((7 << 8)		// коэффициент умножения PLL_CPU_MUL - 10 * (7 + 1) = 80 MHz
															|(1 << 2));	// включение умножителя - PLL_CPU_ON
	 
	while(!(MDR_RST_CLK->CLOCK_STATUS & (1 << 1))) {;} // ожидание установки флага PLL_CPU_RDY - выхода в рабочий режим CPU_PLL
		
	MDR_RST_CLK->CPU_CLOCK |= ((1 << 2) 	// CPU_C2_SEL: выбор источника PLLCPUo - умножитель = 80 MHz
														|(0 << 4) 	// CPU_C3_SEL: CPU_C3 = CPU_C2 = 80 MHz
														|(1 << 8)); // HCLK_SEL: CPU_CLOCK - CPU_C3 = 80 MHz
		
	SystemCoreClockUpdate();
}
/*======================================== PLL ========================================*/


/*======================================== CPU_set ========================================*/
// использовать при 80 MHz
void CPU_set(void)
{
	// необходимая пауза для работы Flash-памяти программ
	MDR_EEPROM->CMD |= (3 << 3);
	
	MDR_BKP->REG_0E |= (6 << 0); // режим встроенного регулятора напряжения DUcc(в зависимости от частоты МК)
	MDR_BKP->REG_0E |= (6 << 3); // выбор доп.стабилизирующей нагрузки
}
/*======================================== CPU_set ========================================*/


/*======================================== CLOCK_INIT ========================================*/
void CPU_init(void)
{
	Clock_Set();
	PLL_init();
	CPU_set();
}
/*======================================== CLOCK_INIT ========================================*/


/*======================================== SYSTICK ========================================*/
void SysTick_init(void)
{
	SysTick->LOAD = (80000000/1000000)-1;
	SysTick->CTRL |= ((1 << 2)		// CLKSOURCE: источник сигнала HCLK
										|(1 << 1)		// TCKINT: прерывание разрешено
										|(1 << 0));	// ENABLE: работа разрешена
}

volatile uint32_t Delay_dec = 0;

void SysTick_Handler(void)
{
	if(Delay_dec)
		Delay_dec--;
}

void delay_us(uint32_t Delay_us_Data)
{
	Delay_dec = Delay_us_Data;
	while (Delay_dec) {};
}

void delay_ms(uint32_t Delay_ms_Data)
{
	Delay_dec = Delay_ms_Data * 1000;
	while (Delay_dec) {};
}
/*======================================== SYSTICK ========================================*/
