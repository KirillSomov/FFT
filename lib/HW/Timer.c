
#include "Timer.h"


/*!
	\brief Инициализация Таймера 2
 */
void Timer2_init(void)
{
	// деинициализация текущего таймера
	TIMER_DeInit(MDR_TIMER2);
	// Установка первого делителя тактовой частоты таймера
	// Timer2_CLK = HCLK/8 = 10 МГц
	TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv8);

	// Структура инициализации Таймера 2
	TIMER_CntInitTypeDef 	TIMER_CntInitStruct;
	
	// Установка интервала генерации прерываний по переполнению
	// Инициализация по умолчанию
	TIMER_CntStructInit(&TIMER_CntInitStruct);
	// 10 МГц / 10к = 1 кГц => счётчик считает на частоте 1 кГц, т.е. каждую 1 мс
	TIMER_CntInitStruct.TIMER_Prescaler	=	9999;
	TIMER_CntInitStruct.TIMER_Period		=	0xFFFF;
	
	// Инициализация Таймера 2
	TIMER_CntInit(MDR_TIMER2,	&TIMER_CntInitStruct);

	// Настройка прерываний
	// Выключение прерываний от текущего таймера
	NVIC_DisableIRQ(Timer2_IRQn);
	
	// Запуск Таймера 2
	TIMER_Cmd(MDR_TIMER2, ENABLE);
}


/*!
	\brief Инициализация Таймера 3
 */
void Timer3_init(void)
{
	// Деинициализация текущего таймера
	TIMER_DeInit(MDR_TIMER3);
	// Установка первого делителя тактовой частоты таймера
	// Timer2_CLK = HCLK/8 = 10 МГц	
	TIMER_BRGInit(MDR_TIMER3, TIMER_HCLKdiv8);

	// Структура инициализации Таймера 3
	TIMER_CntInitTypeDef 	TIMER_CntInitStruct;
	
	// Инициализация по умолчанию
	TIMER_CntStructInit(&TIMER_CntInitStruct);
	// 10 МГц / 10к = 1 кГц => счётчик считает на частоте 1 кГц
	TIMER_CntInitStruct.TIMER_Prescaler	=	9999;
	// Каждые 500 мс
	TIMER_CntInitStruct.TIMER_Period		=	499;
	
	// Инициализация Таймера 3
	TIMER_CntInit(MDR_TIMER3,	&TIMER_CntInitStruct);

	// Настройка прерываний
	// Включение прерываний от текущего таймера
	NVIC_EnableIRQ(Timer3_IRQn);
	// Установка приоритета прерываний 0-15
	NVIC_SetPriority(Timer3_IRQn, 2);

	// Включение прерывания при равенстве CNT = ARR
	TIMER_ITConfig(MDR_TIMER3, TIMER_STATUS_CNT_ARR, ENABLE);
	
	// Запуск Таймера 3
	TIMER_Cmd(MDR_TIMER3, ENABLE);
}


/*!
	\brief Обработчик прерываний Таймера 3
 */
void Timer3_IRQHandler(void)
{	
	// Проверка что причина прерывания – обновление таймера
	if(TIMER_GetITStatus(MDR_TIMER3, TIMER_STATUS_CNT_ARR))
	{
		LED_handlerIrq();
		
		// Очистка флага прерывания
		TIMER_ClearITPendingBit(MDR_TIMER3, TIMER_STATUS_CNT_ARR);
	}
}


/*!
	\brief Блокирующая функия задержки в мс
  \param TIMER	Указатель на таймер
	\param ms			Время задержки в мс
 */
void delay_ms(MDR_TIMER_TypeDef *TIMER, uint16_t ms)
{
	volatile uint16_t	startCount	=	TIMER->CNT;
	
	while(((uint16_t)((uint16_t)TIMER->CNT - startCount)) < ms) {;}
}
