
#ifndef TIMER_H
	#define TIMER_H

	// Подключение заголовочных файлов модулей проекта
	#include "link.h"


	// Прототипы функций
	void Timer2_init(void);										// Инициализация Таймера 2

	void delay_us(MDR_TIMER_TypeDef *TIMER,
									uint16_t us);							// Функия задержки в мс


#endif
