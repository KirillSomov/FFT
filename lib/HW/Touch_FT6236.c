
#include "Touch_FT6236.h"


// экземпляр структуры координат нажатия
FT6236_Tpoint_TypeDef FT6236_Tpoint = {0};


// инициализация портов
void FT6236_ports_init(void)
{
	// RSTN pin
	FT6236_RSTN_PORT->OE     |= (1 << FT6236_RSTN_PIN);   	// выход
	FT6236_RSTN_PORT->ANALOG |= (1 << FT6236_RSTN_PIN);   	// режим работы - цифровой
  FT6236_RSTN_PORT->FUNC   &= ~(3 << FT6236_RSTN_PIN*2);  // сброс регистра FUNC - порт IO
  FT6236_RSTN_PORT->PWR    |= (3 << FT6236_RSTN_PIN*2);  	// максимально быстрый фронт
	
	// INT pin
	FT6236_INT_PORT->OE     |= (1 << FT6236_INT_PIN);   		// выход
  FT6236_INT_PORT->ANALOG |= (1 << FT6236_INT_PIN);   		// режим работы - цифровой
  FT6236_INT_PORT->FUNC   &= ~(3 << FT6236_INT_PIN*2);		// сброс регистра FUNC - порт IO
  FT6236_INT_PORT->PWR    |=  (3 << FT6236_INT_PIN*2); 		// максимально быстрый фронт
}


// сброс контроллера
void FT6236_reset(void)
{
	FT6236_RSTN_PORT->RXTX	&=	~(1	<< FT6236_RSTN_PIN);	// сброс контроллера
	delay_ms(5);
	FT6236_RSTN_PORT->RXTX	|=	(1 << FT6236_RSTN_PIN);		// рабочий режим
	delay_ms(350);
	
	// вывод контроллера из режима гибернации
	FT6236_INT_PORT->RXTX	&=	~(1	<< FT6236_INT_PIN);
	delay_ms(1);
	FT6236_INT_PORT->RXTX	|=	(1 << FT6236_INT_PIN);
	
	// настройка порта INT на вход
	FT6236_INT_PORT->OE &= ~(1 << FT6236_INT_PIN);
}


// сброс структуры данных
void	FT6236_dataStruct_reset(FT6236_Tpoint_TypeDef *FT6236_Tpoint)
{
	FT6236_Tpoint->Xt = 0;
	FT6236_Tpoint->Yt = 0;
}


// инициализация контроллера
void FT6236_init(void)
{
	// инициализация портов touch панели
	FT6236_ports_init();
	
	// сброс контроллера
	FT6236_reset();
	
	// установка рабочего режима
	I2C_write_data(FT6236_I2C_ADDR, FT6236_DEV_MODE_REG, FT6236_DEV_MODE_WORKING_MODE);
	I2C_write_data(FT6236_I2C_ADDR, FT6236_TH_GROUP_REG, 0x80);
	I2C_write_data(FT6236_I2C_ADDR, FT6236_TH_DIFF, 0x80);
	I2C_write_data(FT6236_I2C_ADDR, FT6236_CTRL_REG, FT6236_CTRL_KEEP_ACTIVE_MODE);
	I2C_write_data(FT6236_I2C_ADDR, FT6236_PERIOD_ACTIVE_REG, 0x0E);
	I2C_write_data(FT6236_I2C_ADDR, FT6236_G_MODE_REG, FT6236_G_MODE_POLLING_MODE);
}


// 
uint8_t	FT6236_checkInt(void)
{
	uint8_t flagInt = 0;
	
	flagInt = !((uint8_t)((FT6236_INT_PORT->RXTX & (1 << FT6236_INT_PIN)) >> FT6236_INT_PIN));
	
	return flagInt;
}


void FT6236_get_Tpoint(FT6236_Tpoint_TypeDef *FT6236_Tpoint)
{
	// буффер для чтения координат нажатия
	uint8_t TpointXY_buf[4] = {0};
	
	// чтение координат нажатия
	I2C_read_data_burst(FT6236_I2C_ADDR, FT6236_P1_XH_REG, 4, &TpointXY_buf[0]);
	
	// занесение координат в структуру
	FT6236_Tpoint->Xt	 =	0x0F00 & ((uint16_t)TpointXY_buf[0] << 8);
	FT6236_Tpoint->Xt	|=	0x00FF & (uint16_t)TpointXY_buf[1];
	FT6236_Tpoint->Yt	 =	0x0F00 & ((uint16_t)TpointXY_buf[2] << 8);
	FT6236_Tpoint->Yt	|=	0x00FF & (uint16_t)TpointXY_buf[3];
	FT6236_Tpoint->Yt = (LCD_HEIGHT-1) - FT6236_Tpoint->Yt;
}
