
// подключение заголовочного файла
#include "link.h"


#define		VIRTUAL_GND_SHIFT	2020

// Globals
int16_t	imaginaryNumbers[64];
int16_t	realNumbers[64];
//uint32_t	ADC_sum = 0;
int16_t column[32] = {0};

uint16_t fillColor = 0;

uint16_t freqBlock = 0;

bool isDetected = false;

uint16_t blockColor = 0;

// отрисовка шкал
void interface_init(void)
{
	LCD_printString(175, 1, "0-312.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(176, 11, "312.5-625", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(176, 21, "625-937.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(167, 31, "937.5-1250", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 41, "1250-1562.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 51, "1562.5-1875", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 61, "1875-2187.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 71, "2187.5-2500", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 81, "2500-2812.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 91, "2812.5-3125", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 101, "3125-3437.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 111, "3437.5-3750", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 121, "3750-4062.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 131, "4062.5-4375", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 141, "4375-4687.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 151, "4687.5-5000", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 161, "5000-5312.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 171, "5312.5-5625", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 181, "5625-5937.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 191, "5937.5-6250", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 201, "6250-6562.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 211, "6562.5-6875", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 221, "6875-7187.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 231, "7187.5-7500", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 241, "7500-7812.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 251, "7812.5-8125", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 261, "8125-8437.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 271, "8437.5-8750", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 281, "8750-9062.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 291, "9062.5-9375", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 301, "9375-9687.5", 0x0000, &calibri_14ptFontInfo);
	LCD_printString(160, 311, "9687.5-10k", 0x0000, &calibri_14ptFontInfo);
}


int main(void)
{	
	// тактирование
	clockSetup();
	
	Timer1_init();
	Timer2_init();

	//
	portsSetup();
	
	// инициализация АЦП
	ADC_init();
	
	// инициализация SPI2
	SPI2_Init();
	I2C_init();
	
	// инициализация LCD
	LCD_init();
	
	// белый фон LCD
	LCD_fill(0xFFFF);
	
	FT6236_init();
	
	// отрисовка шкал
	//interface_init();
	
	GUI_FFT_numInputInterfaceInit();
	
	while(1);
	
	freqBlock = calcFreqBlock(4800);

// ============== FFT ===================

// обёртка БПФ
// получение выборок(значение АЦП, разрядность БПФ)
// выполнение БПФ
// вычисление модуля (абсолютное): корень из суммы квадратов
// отображение гистограммы

	while(1)
	{
	
		// Выполнение БПФ
		/*
			Получение 64 выборок с интервалом 50 мкс означает, 
			что наша частота дискретизации составляет 20 кГц, 
			что дает нам предел Найквиста 10 кГц
		*/
		
		getAdcSamples(fftNums, 6, &ADC_read);
		
		// Выполнение прямого преобразования Фурье

		/*
			Примечание: длина результата FFT составляет 
			половину длины входных данных, поэтому, 
			если мы поместим 64 выборки, мы получим 32 сегмента. 
			Первый сегмент не может быть использован, 
			поэтому на самом деле наш результат - 31 сегмент.
			
			Максимальная частота, которую мы можем измерить,
			составляет половину частоты дискретизации,
			поэтому, если мы производим дискретизацию 
			на частоте 20 кГц, наш максимум составляет 10 кГц 
			(это называется частотой Найквиста). 
			Таким образом, если у нас есть 32 сегмента, 
			разделенных на 10 кГц, каждый сегмент 
			представляет диапазон 312,5 кГц, 
			поэтому наш самый низкий сегмент (сегмент 1) 
			составляет 312,5 Гц - 625 Гц и т.д. до 
			нашего 32-го сегмента, который составляет 
			9687,5 Гц - 10 000 Гц.
		*/
		
		//  1 : 312.5 - 625
		//  2 : 625 - 937.5
		//  3 : 937.5 - 1250
		//  4 : 1250 - 1562.5
		//  5 : 1562.5 - 1875
		//  6 : 1875 - 2187.5
		//  7 : 2187.5 - 2500
		//  8 : 2500 - 2812.5
		//  9 : 2812.5 - 3125
		// 10 : 3125 - 3437.5
		// 11 : 3437.5 - 3750
		// 12 : 3750 - 4062.5
		// 13 : 4062.5 - 4375
		// 14 : 4375 - 4687.5
		// 15 : 4687.5 - 5000
		// 16 : 5000 - 5312.5
		// 17 : 5312.5 - 5625
		// 18 : 5625 - 5937.5
		// 19 : 5937.5 - 6250
		// 20 : 6250 - 6562.5
		// 21 : 6562.5 - 6875
		// 22 : 6875 - 7187.5
		// 23 : 7187.5 - 7500
		// 24 : 7500 - 7812.5
		// 25 : 7812.5 - 8125
		// 26 : 8125 - 8437.5
		// 27 : 8437.5 - 8750
		// 28 : 8750 - 9062.5
		// 29 : 9062.5 - 9375
		// 30 : 9375 - 9687.5
		// 31 : 9687.5 - 10000
		
		// Примечание: «6» - это размер входных данных (2 в степени 6 = 64)
		// 6 - это кол-во делений последовательности пополам
		fft(fftNums, 6);
		
		// Взятие абсолютных значений (по модулю) результатов БПФ
		
		/*
			Примечание. Подпрограмма FFT возвращает «комплексные» числа, 
			которые состоят как из вещественной, так и мнимой части. 
			Чтобы найти «абсолютное» значение возвращаемых данных,
			мы должны вычислить расстояние комплексного числа от нуля,
			что требует теоремы Пифагора и, следовательно, 
			вычисления квадратного корня. Поскольку К1986ВЕ92QI имеет 
			аппаратное обеспечение умножения, 
			необходимо оптимизировать только квадратный корень.
		*/
		
		calcModule(fftNums, 6);
		
		isDetected = detectFreq(fftNums, 6, freqBlock);
		
    for(uint8_t i = 0; i < 32; i++)
    {	
			/*
			Теперь у нас есть 32 блока данных звуковой частоты, 
			представленных в виде линейной интенсивности 
			в realNumbers[].
			
			Поскольку максимальное входное значение 
			(теоретически) для функции SQRT равно 32767, 
			пиковый выходной сигнал на этом этапе 
			равен SQRT(32767) = 181.
			*/
			
	    // Отрисовка гистограммы выходных данных БПФ
			//drawHistogram();
			
			if(isDetected == true && i == freqBlock)
				blockColor = 0xAAFF;
			else
				blockColor = 0;
			
			if(column[i] < fftNums[i].ReNum)
				LCD_drawFilledRectangle(0, fftNums[i].ReNum, i*10, i*10+9, blockColor);
			if(column[i] > fftNums[i].ReNum)
				LCD_drawFilledRectangle(fftNums[i].ReNum, column[i], i*10, i*10+9, 0xFFFF);
			
			column[i] = fftNums[i].ReNum;

		}		
		delay_ms(MDR_TIMER2, 50);
		
	}
	
}
