
#ifndef CPU_H
	#define CPU_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// прототипы функций
	void clockSetup(void);				// SYS.00001 Требования к настройке тактирования микроконтроллера
	bool clockCpuSetup(void);			// SYS.00002 Настройка тактирования ядра процессора
	void clockPeriphInit(void);		// SYS.00003 Настройка тактирования периферии процессора


#endif
