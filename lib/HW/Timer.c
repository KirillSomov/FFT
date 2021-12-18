
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
	\brief Блокирующая функия задержки в мкс
  \param TIMER	Указатель на таймер
	\param ms			Время задержки в мкс
 */
void delay_us(MDR_TIMER_TypeDef *TIMER, uint16_t us)
{
	volatile uint16_t	startCount	=	0;
	
	TIMER->PSG = 9;
	TIMER->CNT = 0;
	startCount	=	TIMER->CNT;
	
	while(((uint16_t)((uint16_t)TIMER->CNT - startCount)) < us) {;}
}

/*!
	\brief Блокирующая функия задержки в мс
  \param TIMER	Указатель на таймер
	\param ms			Время задержки в мс
 */
void delay_ms(MDR_TIMER_TypeDef *TIMER, uint16_t ms)
{
	volatile uint16_t	startCount	=	0;
	
	TIMER->PSG = 9999;
	TIMER->CNT = 0;
	startCount	=	TIMER->CNT;
	
	while(((uint16_t)((uint16_t)TIMER->CNT - startCount)) < ms) {;}
}


void Timer1_init(void)
{
	// настройка Т2 на генерирование прерывания каждую мкс
	MDR_RST_CLK->TIM_CLOCK	|=	((1 << 0)			// делитель 2: F_Timer1 = 80 / 2 = 40 MHz
															|(1 << 24));	// вкл. тактирование Таймера 1
		
	// режим счета – вверх,начальное значение – число из регистра CNT
	MDR_TIMER1->CNTRL	=	1;
	MDR_TIMER1->PSG		=	39999;				// предделитель частоты
	MDR_TIMER1->ARR		=	1;						// основание счета
	MDR_TIMER1->CNT		=	0;						// начальное значение счетчика
	MDR_TIMER1->IE		=	2;						// разрешение генерир. прерывание при CNT=ARR
	
	NVIC_EnableIRQ(Timer1_IRQn);
	__enable_irq();
}


void Timer1_IRQHandler(void)
{
	for(uint8_t objButNum = 0; objButNum < OBJ_BUTTON_AMOUNT; objButNum++)
	{
		if(GUI.objList.ObjButtonList[objButNum].timerVal > 0)
		{
			GUI.objList.ObjButtonList[objButNum].timerVal--;
		}
		else
		{
			GUI.objList.ObjButtonList[objButNum].flag_buttonWasClicked = 0;
		}
	}
	
	MDR_TIMER1->CNT	=	0;									// сброс счетчика таймера
	MDR_TIMER1->STATUS	=	0;							// сброс статуса прерывания
	NVIC_ClearPendingIRQ(Timer1_IRQn);		// сброс статуса прерывания
}
