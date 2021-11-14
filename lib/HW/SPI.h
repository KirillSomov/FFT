
#ifndef SPI_H
#define SPI_H


// подключение заголовочных файлов модулей проекта
#include "link.h"


// директивы работы с линией FSS
#define SPI2_FSS_RESET	MDR_PORTD->RXTX &= ~(1 << 3)
#define SPI2_FSS_SET		MDR_PORTD->RXTX |=	(1 << 3)


// прототипы функций
void SPI2_Reset(void);								// деинициализация контроллера SSP
void SPI2_PortCfg(void);							// конфигурация порта для работы интерфейса SPI (SSP2)
void SPI2_Init(void);									// инициализация нитерфейса SPI2
void SPI2_sendData(uint16_t data);		// передача данных по интерфейсу SPI


#endif
