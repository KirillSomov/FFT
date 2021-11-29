
#ifndef ADC_H
	#define ADC_H
	
	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	#define ADC_START MDR_ADC->ADC1_CFG |= (1 << 1)	// команда начала преобразования АЦП
	
	// прототипы функций
	void			ADC_init(void); 			// инициализация АЦП
	uint32_t	ADC_read(void);				// чтение результата АЦП
	
	
#endif
