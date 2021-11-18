
#ifndef PORT_CFG_H
	#define PORT_CFG_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// прототипы функций
	
	bool portCheckBitForValid(uint16_t PORT_Pin_x);			// SYS.00025 Проверка корректности значения регистра бита порта
	bool portCheckOeForValid(uint8_t oe);								// SYS.000?? Проверка корректности значения регистра направления
	
	
	void portSetupOe(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_OE_TypeDef oe);									// SYS.00016 Установка направления порта
	void portSetupMode(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_MODE_TypeDef mode);						// SYS.00017 Установка или отключение аналоговой функции порта
	void portSetupFunc(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_FUNC_TypeDef func);						// SYS.00018 Установка режима работы порта
	void portSetupPullUp(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PULL_UP_TypeDef pull);			// SYS.00019 Установка подтяжки порта к питанию
	void portSetupPullDown(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PULL_DOWN_TypeDef pull);	// SYS.00020 Установка подтяжки порта в земле
	void portSetupGfen(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_GFEN_TypeDef gfen);						// SYS.00021 Включение или отключение входного фильтра
	void portSetupPdShm(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PD_SHM_TypeDef shm);					// SYS.00022.1 Установка режима работы выходного драйвера: вход триггер Шмитта
	void portSetupPd(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PD_TypeDef driver);							// SYS.00022.2 Установка режима работы выходного драйвера: выход драйвер
	void portSetupSpeed(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_SPEED_TypeDef speed);				// SYS.00023 Установка крутизны фронта выходного порта
	
	void portResetBits(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x);
	void portSetBits(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x);
	
	void portsSetupAsInput(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x);			// SYS.00014 Конфигурирования порта как вход
	void portsSetupAsOutput(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x);		// SYS.00015 Конфигурирование порта как выход


#endif
