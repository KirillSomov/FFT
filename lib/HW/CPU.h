
#ifndef CPU_H
#define CPU_H


// подключение заголовочных файлов модулей проекта
#include "link.h"


// прототипы функций
void Clock_Set(void);		// тактирование
void PLL_init(void);			// инициализация умножителя
void CPU_set(void);				// настройка для 80 MHz
void CPU_init(void);			// инициализация CPU

// таймер
extern volatile uint32_t Delay_dec;
void SysTick_init(void);								// инициализация системного таймера
void SysTick_Handler(void);							// обработчик прерывания системного таймера
void delay_us(uint32_t Delay_us_Data);	// функия задержки в мкс
void delay_ms(uint32_t Delay_ms_Data);	// функия задержки в мс


#endif
