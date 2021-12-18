
#ifndef TIMER_H
	#define TIMER_H

	// Подключение заголовочных файлов модулей проекта
	#include "link.h"


	// Прототипы функций
	void Timer2_init(void);										// Инициализация Таймера 2

	void delay_us(MDR_TIMER_TypeDef *TIMER,
									uint16_t us);							// Функия задержки в мкс
	void delay_ms(MDR_TIMER_TypeDef *TIMER,
									uint16_t ms);							// Функия задержки в мс

	
	void Timer1_init(void);
	void Timer1_IRQHandler(void);
	
	
#endif
