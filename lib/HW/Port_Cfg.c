
#include "Port_Cfg.h"


// SYS.00025 Проверка корректности значения регистра бита порта
bool portCheckBitForValid(uint16_t PORT_Pin_x)
{
	bool valBit = false;
	
	// проверка корректности номера бита
	switch(PORT_Pin_x)
	{
		case PORT_Pin_0:
			valBit = true;
			break;
		case PORT_Pin_1:
			valBit = true;
			break;
		case PORT_Pin_2:
			valBit = true;
			break;
		case PORT_Pin_3:
			valBit = true;
			break;
		case PORT_Pin_4:
			valBit = true;
			break;
		case PORT_Pin_5:
			valBit = true;
			break;
		case PORT_Pin_6:
			valBit = true;
			break;
		case PORT_Pin_7:
			valBit = true;
			break;
		case PORT_Pin_8:
			valBit = true;
			break;
		case PORT_Pin_9:
			valBit = true;
			break;
		case PORT_Pin_10:
			valBit = true;
			break;
		case PORT_Pin_11:
			valBit = true;
			break;
		case PORT_Pin_12:
			valBit = true;
			break;
		case PORT_Pin_13:
			valBit = true;
			break;
		case PORT_Pin_14:
			valBit = true;
			break;
		case PORT_Pin_15:
			valBit = true;
			break;
		default:
			valBit = false;
	}
	
	return valBit;
}


// SYS.000?? Проверка корректности значения регистра направления
bool portCheckOeForValid(uint8_t oe)
{
	return true;
}


// SYS.00016 Установка направления порта
void portSetupOe(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_OE_TypeDef oe)
{
	if(oe == PORT_OE_OUT)					// если порт - выход
	{
		PORTx->OE	|=	PORT_Pin_x;		// установить бит на выход - 1
	}
	else													// иначе порт - вход
	{
		PORTx->OE	&=	~PORT_Pin_x;	// устаночить бит на вход - 0
	}
}


// SYS.00017 Установка или отключение аналоговой функции порта
void portSetupMode(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_MODE_TypeDef mode)
{
	if(mode == PORT_MODE_DIGITAL)			// если порт - цифровой
	{
		PORTx->ANALOG	|=	PORT_Pin_x;		// установить цифровой режим - 1
	}
	else															// иначе порт - аналоговый
	{
		PORTx->ANALOG	&=	~PORT_Pin_x;	// установить аналоговый режим - 0
	}
}


// SYS.00018 Установка режима работы порта
void portSetupFunc(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_FUNC_TypeDef func)
{
	// переменная позиция бита
	uint8_t pos = 0;
	
	// нахождение позиции бита
	for(uint16_t i = 1; i < PORT_Pin_x; i = i << 1)
	{
		pos++;
	}
	
	// очистка текущего режима
	PORTx->FUNC	&=	~(3 << pos*2);
	
	// установка нового режима
	switch(func)
	{
		case PORT_FUNC_PORT:
			PORTx->FUNC	|=	(PORT_FUNC_PORT << pos*2);
			break;
		case PORT_FUNC_MAIN:
			PORTx->FUNC	|=	(PORT_FUNC_MAIN << pos*2);
			break;
		case PORT_FUNC_ALTER:
			PORTx->FUNC	|=	(PORT_FUNC_ALTER << pos*2);
			break;
		case PORT_FUNC_OVERRID:
			PORTx->FUNC	|=	(PORT_FUNC_OVERRID << pos*2);
			break;
	}
}


// SYS.00019 Установка подтяжки порта к питанию
void portSetupPullUp(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PULL_UP_TypeDef pull)
{
	if(pull == PORT_PULL_UP_ON)
	{
    PORTx->PULL	|=	((uint32_t)PORT_Pin_x) << 16;
  }
  else
  {
    PORTx->PULL	&=	~(((uint32_t)PORT_Pin_x) << 16);
  }
}


// SYS.00020 Установка подтяжки порта в земле
void portSetupPullDown(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PULL_DOWN_TypeDef pull)
{
	if(pull == PORT_PULL_DOWN_ON)
  {
    PORTx->PULL	|=	PORT_Pin_x;
  }
  else
  {
    PORTx->PULL	&=	~PORT_Pin_x;
  }
}


// SYS.00021 Включение или отключение входного фильтра
void portSetupGfen(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_GFEN_TypeDef gfen)
{
	if(gfen == PORT_GFEN_ON)
  {
    PORTx->GFEN	|=	PORT_Pin_x;
  }
  else
  {
    PORTx->GFEN	&=	~PORT_Pin_x;
  }
}


// SYS.00022.1 Установка режима работы выходного драйвера: вход триггер Шмитта
void portSetupPdShm(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PD_SHM_TypeDef shm)
{
	if(shm == PORT_PD_SHM_ON)
	{
		PORTx->PD	|=	((uint32_t)PORT_Pin_x) << 16;
	}
	else
	{
		PORTx->PD	&=	~(((uint32_t)PORT_Pin_x) << 16);
	}
}


// SYS.00022.2 Установка режима работы выходного драйвера: выход драйвер
void portSetupPd(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_PD_TypeDef driver)
{
	if(driver == PORT_PD_OPEN)
  {
    PORTx->PD	|=	PORT_Pin_x;
  }
  else
  {
    PORTx->PD	&=	~PORT_Pin_x;
  }
}


// SYS.00023 Установка крутизны фронта выходного порта
void portSetupSpeed(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x, PORT_SPEED_TypeDef speed)
{
	// переменная позиция бита
	uint8_t pos = 0;
	
	// нахождение позиции бита
	for(uint16_t i = 1; i < PORT_Pin_x; i = i << 1)
	{
		pos++;
	}	
	
	// очистка текущего значения скорости
	PORTx->PWR	&=	~(3 << pos*2);
	
	// установка нового значения скорости
	switch(speed)
	{
		case PORT_OUTPUT_OFF:
			PORTx->PWR	|=	(PORT_OUTPUT_OFF << pos*2);
			break;
		case PORT_SPEED_SLOW:
			PORTx->PWR	|=	(PORT_SPEED_SLOW << pos*2);
			break;
		case PORT_SPEED_FAST:
			PORTx->PWR	|=	(PORT_SPEED_FAST << pos*2);
			break;
		case PORT_SPEED_MAXFAST:
			PORTx->PWR	|=	(PORT_SPEED_MAXFAST << pos*2);
			break;
	}
}

void portResetBits(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x)
{
	uint16_t tempreg;
	
	tempreg = PORTx->RXTX;
	tempreg &= ~(PORT_Pin_x | 0x001F);
	
	PORTx->RXTX = tempreg;
}

void portSetBits(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x)
{
	uint16_t tempreg;
	
	tempreg = PORTx->RXTX;
	tempreg &= ~(0x001F);
	tempreg |= PORT_Pin_x;
	
	PORTx->RXTX = tempreg;
}

// SYS.00014 Конфигурирования порта как вход
void portsSetupAsInput(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x)
{
	portSetupOe(PORTx, PORT_Pin_x, PORT_OE_IN);
	portSetupMode(PORTx, PORT_Pin_x, PORT_MODE_DIGITAL);
	portSetupFunc(PORTx, PORT_Pin_x, PORT_FUNC_PORT);
	portSetupPullUp(PORTx, PORT_Pin_x, PORT_PULL_UP_OFF);
	portSetupPullDown(PORTx, PORT_Pin_x, PORT_PULL_DOWN_ON);
	portSetupGfen(PORTx, PORT_Pin_x, PORT_GFEN_ON);
}


// SYS.00015 Конфигурирование порта как выход
void portsSetupAsOutput(MDR_PORT_TypeDef* PORTx, uint16_t PORT_Pin_x)
{
	portSetupOe(PORTx, PORT_Pin_x, PORT_OE_OUT);
	portSetupMode(PORTx, PORT_Pin_x, PORT_MODE_DIGITAL);
	portSetupFunc(PORTx, PORT_Pin_x, PORT_FUNC_PORT);
	portSetupPdShm(PORTx, PORT_Pin_x, PORT_PD_SHM_OFF);
	portSetupPd(PORTx, PORT_Pin_x, PORT_PD_DRIVER);
	portSetupSpeed(PORTx, PORT_Pin_x, PORT_SPEED_FAST);
	portSetupPullUp(PORTx, PORT_Pin_x, PORT_PULL_UP_OFF);
	portSetupPullDown(PORTx, PORT_Pin_x, PORT_PULL_DOWN_OFF);
	PORT_ResetBits(PORTx, PORT_Pin_x);
}
