
#ifndef LINK_H
	#define LINK_H

	// подключение стандартных библиотек
	#include "stdbool.h"
	#include "MDR32Fx.h"                    // Device header
	#include "core_cm3.h"                   // Keil::Device:Startup
	#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
	#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
	#include "MDR32F9Qx_bkp.h"              // Keil::Drivers:BKP
	#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
	#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

	
	// подключение заголовочных файлов модулей проектов
	#include "CPU.h"
	#include "Timer.h"
	#include "Port_Cfg.h"
	#include "Port_Setup.h"
	#include "ADC.h"
	#include "SPI.h"
	#include "Font.h"
	#include "Picture.h"
	#include "LCD_ILI9341.h"
	//#include "Touch_FT6236.h"
	#include "GUI.h"
	#include "FFT.h"


#endif
