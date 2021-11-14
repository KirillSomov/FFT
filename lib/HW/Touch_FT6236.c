
#include "Touch_FT6236.h"


// экземпляр структуры координат нажатия
FT6236_Tpoint_TypeDef FT6236_Tpoint = {0};


// сброс контроллера
void FT6236_reset(void)
{
	FT6236_RSTN_RESET;
	delay_ms(5);
	FT6236_RSTN_SET;
	delay_ms(350);
	
	// вывод контроллера из режима гибернации
	GPIO_InitTypeDef GPIO_initINT;
	GPIO_StructInit(&GPIO_initINT);
	GPIO_initINT.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_initINT.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_initINT.GPIO_OType = GPIO_OType_PP;
  GPIO_initINT.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_initINT.GPIO_Pin   = FT6236_INT_PIN;					// PD5 - LCD_IRQ
	GPIO_Init(FT6236_INT_PORT, &GPIO_initINT); 				// PD5 - LCD_IRQ
	
	FT6236_INT_RESET;
	delay_ms(1);
	FT6236_INT_SET;
	
	// настройка порта INT на вход
	GPIO_initINT.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_initINT.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(FT6236_INT_PORT, &GPIO_initINT); 				// PD5 - LCD_IRQ
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
	// сброс контроллера
	FT6236_reset();
	
	// установка рабочего режима
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_DEV_MODE_REG, FT6236_DEV_MODE_WORKING_MODE);
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_TH_GROUP_REG, 0x80);
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_TH_DIFF, 0x80);
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_CTRL_REG, FT6236_CTRL_KEEP_ACTIVE_MODE);
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_PERIOD_ACTIVE_REG, 0x0E);
	I2Cx_writeData(I2C1, FT6236_I2C_ADDR, FT6236_G_MODE_REG, FT6236_G_MODE_TRIGGER_MODE);
}


// 
uint8_t	FT6236_checkInt(void)
{
	uint8_t flagInt = 0;
	
	flagInt = !((uint8_t)FT6236_INT_READ);
	
	return flagInt;
}


void FT6236_get_Tpoint(FT6236_Tpoint_TypeDef *FT6236_Tpoint)
{
	// буффер для чтения координат нажатия
	uint8_t TpointXY_buf[4] = {0};
	
	// чтение координат нажатия
	I2Cx_readDataBurst(I2C1, FT6236_I2C_ADDR, FT6236_P1_XH_REG, 4, &TpointXY_buf[0]);
	
	// занесение координат в структуру
	FT6236_Tpoint->Xt	 =	0x0F00 & ((uint16_t)TpointXY_buf[0] << 8);
	FT6236_Tpoint->Xt	|=	0x00FF & (uint16_t)TpointXY_buf[1];
	FT6236_Tpoint->Yt	 =	0x0F00 & ((uint16_t)TpointXY_buf[2] << 8);
	FT6236_Tpoint->Yt	|=	0x00FF & (uint16_t)TpointXY_buf[3];
	FT6236_Tpoint->Yt = (LCD_HEIGHT-1) - FT6236_Tpoint->Yt;
}
