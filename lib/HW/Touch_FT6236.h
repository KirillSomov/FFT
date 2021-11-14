
#ifndef TOUCH_FT6236_H
	#define TOUCH_FT6236_H
		
	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	// порты
	#define	FT6236_RSTN_PORT	GPIOD
	#define	FT6236_RSTN_PIN		GPIO_Pin_4
	
	#define	FT6236_INT_PORT		GPIOD
	#define	FT6236_INT_PIN		GPIO_Pin_5
	
	#define	FT6236_RSTN_RESET		GPIO_ResetBits(FT6236_RSTN_PORT,	FT6236_RSTN_PIN)
	#define	FT6236_RSTN_SET			GPIO_SetBits(FT6236_RSTN_PORT,		FT6236_RSTN_PIN)
	
	#define	FT6236_INT_RESET		GPIO_ResetBits(FT6236_INT_PORT,	FT6236_INT_PIN)
	#define	FT6236_INT_SET			GPIO_SetBits(FT6236_INT_PORT,		FT6236_INT_PIN)
	#define	FT6236_INT_READ			GPIO_ReadInputDataBit(FT6236_INT_PORT,	FT6236_INT_PIN)
	
	
	// адреса регистров
	#define	FT6236_I2C_ADDR									0x38
	
	#define FT6236_DEV_MODE_REG							0x00
	#define FT6236_TD_STATUS_REG						0x02
	
	#define FT6236_P1_XH_REG								0x03
	#define FT6236_P1_XL_REG								0x04
	#define FT6236_P1_YH_REG								0x05
	#define FT6236_P1_YL_REG								0x06
	
	#define FT6236_TH_GROUP_REG							0x80
	#define FT6236_TH_DIFF									0x85
	#define FT6236_CTRL_REG									0x86
	#define FT6236_TIME_ENTER_MONITOR_REG		0x87
	#define FT6236_PERIOD_ACTIVE_REG				0x88
	#define FT6236_PERIOD_MONITOR_REG				0x89
	
	#define FT6236_G_MODE_REG								0xA4
	#define FT6236_PWR_MODE_REG							0xA5
	#define FT6236_STATE_REG								0xBC
	
	
	// значения полей регистров
	#define FT6236_DEV_MODE_WORKING_MODE					0x00
	#define FT6236_DEV_MODE_FACTORY_MODE					0x40
	#define FT6236_CTRL_KEEP_ACTIVE_MODE					0x00
	#define FT6236_CTRL_AUTOSWITCH_MONITOR_MODE		0x01
	#define FT6236_G_MODE_POLLING_MODE						0x00
	#define FT6236_G_MODE_TRIGGER_MODE						0x01
	
	
	// структура координат нажатия
	typedef struct
	{
		uint16_t	Xt;
		uint16_t	Yt;
	}FT6236_Tpoint_TypeDef;
	
	// прототип структуры координат нажатия
	extern FT6236_Tpoint_TypeDef FT6236_Tpoint;
	
	
	// прототипы функций
	void		FT6236_ports_init(void);																					// инициализация портов
	void		FT6236_reset(void);																								// сброс контроллера
	void		FT6236_Tpoint_reset(FT6236_Tpoint_TypeDef *FT6236_Tpoint);				// сброс структуры данных
	void		FT6236_init(void);																								// инициализация контроллера
	uint8_t	FT6236_checkInt(void);																						// 
	void		FT6236_get_Tpoint(FT6236_Tpoint_TypeDef *FT6236_Tpoint);					// получение координат касания
	
	
#endif
