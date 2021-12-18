
#ifndef I2C_H
	#define I2C_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// прототипы функций
	void I2C_reset(void);							// деинициализация контроллера I2C
	void I2C_port_init(void);					// инициализация порта для работы модуля I2C
	void I2C_init(void);							// инициализация модуля I2C


	// Отправление данных по шине I2C
	void I2C_write_data(uint8_t i2c_address,       				// Адрес устройства на шине I2C
											uint8_t register_address,  				// Адрес регистра памяти устройства
											uint8_t data);              			// Передаваемые данные

	// Получение данных по шине I2C
	uint8_t I2C_read_data(uint8_t i2c_address,       			// Адрес устройства на шине I2C
												uint8_t register_address);  		// Адрес регистра памяти устройства

	// последовательное получение нескольких пакетов данных
	void I2C_read_data_burst(uint8_t i2c_address,       	// Адрес устройства на шине I2C
													 uint8_t register_address,  	// Адрес начального регистра памяти устройства
													 uint8_t amount,            	// Количество циклов чтения
													 uint8_t *buffer);          	// Буфер для хранения результатов чтения


#endif
