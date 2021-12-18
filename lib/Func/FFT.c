/************************************************************************
	FFT.c

    FFT Audio Analysis
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/


#include "FFT.h"

struct complexNum fftNums[FFT_DOTS];

// fix_fft.c - Быстрое преобразование Фурье с фиксированной точкой

/*
	Все данные являются короткими целыми (short integer - int16) с фиксированной точнкой,
	в которых диапазон от -32768 до +32767 соответствует
	тригонометрическому диапазону от -1.0 до +1.0.
	Целочисленная арифметика используется для скорости,
	в отличие от более естественной плавающей запятой.
*/
	
/*
	Для прямого БПФ (время -> частота) выполняется фиксированное масштабирование,
	чтобы предотвратить арифметическое переполнение и отобразить
	синусоидальную / косинусоидальную волну 0 дБ (то есть амплитуду = 32767)
	на два коэффициента частоты -6 дБ.
*/
	
	
// Written by:  Tom Roberts  11/8/89
// Made portable:  Malcolm Slaney 12/15/94 malcolm@interval.com
// Enhanced:  Dimitrios P. Bouras  14 Jun 2006 dbouras@ieee.org
// Ported to PIC18F:  Simon Inns 20110104

/*
  fix_fft() - выполнить быстрое преобразование Фурье 
  fr[n],fi[n] - массивы мнимых и реальных значений, 
  оба как INPUT так и RESULT, где 0 <= n < 2*m
*/
void fft(struct complexNum *fftNums, uint16_t L)
{
	uint16_t indexEven, indexOdd;				// индексы чётных и нечётных отсчётов
	uint16_t butterflyNum;							// номер графа "бабочка"
	
	uint16_t m;													// 
	
	uint16_t DFT_Length;								// длина вычисляемого ДПФ
	uint16_t DFT_HalfLength;						// половина длины вычисляемого ДПФ
	
	uint16_t N;													// количество точек БПФ
	uint16_t n;													// границы перестановки
	uint16_t index, invesreIndex = 0;		// индексы элементов при перестановке
	uint16_t j;													// 
	int16_t Wr, Wi;											// поворотные коэффициенты
	int16_t qr, qi, tr, ti;							// temp-переменные для расчётов
	
	
	N = 1 << L;		// N = 64 - количество точек БПФ
	n = N - 1;		// n = 63 - границы перестановки

	/* max FFT size = N_WAVE */
	//if (n > N_WAVE) return -1;

	/* прореживание во времени - переупорядочить данные */
	for(index = 1; index < n; index++)
	{
		L = N;
		do
		{
			L >>= 1;
		} while(invesreIndex + L > n);
		
		invesreIndex = (invesreIndex & (L-1)) + L;
		if(invesreIndex <= index)
			continue;
		
		tr = fftNums[index].ReNum;
		fftNums[index].ReNum = fftNums[invesreIndex].ReNum;
		fftNums[invesreIndex].ReNum = tr;
	}
	
	DFT_HalfLength = 1;
	m = LOG2_N_WAVE-1;				// k = 9
	
	while(DFT_HalfLength < N)	// пока L < 64; выполняется 6 раз
	{		
		/*		  
		  Фиксированное масштабирование, для правильной нормализации - 
		  будет log2 (n) проходов, так что в результате 
		  получается общий коэффициент 1 / n, распределенный 
		  для максимизации арифметической точности.
		  
		  Это может быть неочевидно, но сдвиг 
		  будет выполняться для каждой точки данных ровно один раз, 
		  во время этого прохода.
		*/
		
		// Переменные для кода умножения
		long int c;
		short b;
		
		DFT_Length = DFT_HalfLength << 1;
		for(butterflyNum = 0; butterflyNum < DFT_HalfLength; butterflyNum++)
		{
			j = butterflyNum << m;
			/* 0 <= j < N_WAVE/2 */
			Wr =  Sinewave[j+N_WAVE/4];
			Wi = -Sinewave[j];

			Wr >>= 1;
			Wi >>= 1;
			
			for(indexEven = butterflyNum; indexEven < N; indexEven += DFT_Length)
			{
				indexOdd = indexEven + DFT_HalfLength;
				
				/*
					Здесь я развернул умножение,
					чтобы предотвратить накладные расходы для процедурных вызовов
					(нам не нужно быть умным в отношении фактических умножений, 
					так как контроллер имеет встроенный множитель 32x32):
				*/
				
				// tr = FIX_MPY(Wr,fr[j]) - FIX_MPY(Wi,fi[j]);
				c = ((long int)Wr * (long int)fftNums[indexOdd].ReNum);
				c = c >> 14;
				b = c & 0x01;
				tr = (c >> 1) + b;
				
				c = ((long int)Wi * (long int)fftNums[indexOdd].ImNum);
				c = c >> 14;
				b = c & 0x01;
				tr = tr - ((c >> 1) + b);
				
				// ti = FIX_MPY(Wr,fi[j]) + FIX_MPY(Wi,fr[j]);
				c = ((long int)Wr * (long int)fftNums[indexOdd].ImNum);
				c = c >> 14;
				b = c & 0x01;
				ti = (c >> 1) + b;
				
				c = ((long int)Wi * (long int)fftNums[indexOdd].ReNum);
				c = c >> 14;
				b = c & 0x01;
				ti = ti + ((c >> 1) + b);
				
				qr = fftNums[indexEven].ReNum;
				qi = fftNums[indexEven].ImNum;
				qr >>= 1;
				qi >>= 1;

				fftNums[indexEven].ReNum = qr + tr;
				fftNums[indexEven].ImNum = qi + ti;
				fftNums[indexOdd].ReNum = qr - tr;
				fftNums[indexOdd].ImNum = qi - ti;
			}
		}
		
		m--;
		DFT_HalfLength = DFT_Length;
	}
}


int32_t sqrt(uint32_t num)
{
	// (взято из: http://www.codecodex.com/wiki/Calculate_an_integer_square_root)
	
	int32_t place, root;
	
	place = 0x40000000;
	root = 0;
	
	while(place > num)
	{
		place = place >> 2;
	}
	
	while(place)
	{
		if(num >= root + place)
		{
			num = num - root - place;
			root = root + (place << 1);
		}
		root = root >> 1;
		place = place >> 2;
	}
	
	return root;
}


void calcModule(struct complexNum *fftNums, uint16_t L)
{	
	for(uint8_t i = 0; i < 1 << L; i++)
	{
		fftNums[i].ReNum = (fftNums[i].ReNum * fftNums[i].ReNum + fftNums[i].ImNum * fftNums[i].ImNum);
						
		/*
			Теперь мы находим квадратный корень 
			из realNumbers [i], используя очень быстрое 
			(но зависящее от компилятора) целочисленное приближение:
		*/
		
		if (fftNums[i].ReNum >= 0) // Проверяем, что у нас нет отрицательного числа
		{
			fftNums[i].ReNum = sqrt(fftNums[i].ReNum);
		}
		else
		{
			fftNums[i].ReNum = 0;
		}
	}
}


void getAdcSamples(struct complexNum *fftNums, uint16_t L, uint32_t (*getAdcRes)(void))
{
	uint16_t ADC_sum = 0;
	
	for(uint16_t i = 0; i < 1 << L; i++)
	{
		// Выполнение преобразования АЦП
		/*
			Получение 12-разрядного результата АЦП
			и настройка виртуального заземления 1.6 В 
			обратно на 0 В, чтобы входная волна 
			была правильно отцентрирована от 0 (то есть от -512 до +512)
		*/
			
		for(uint8_t j = 0; j < 2; j++)
			ADC_sum += getAdcRes();
		
		// взятие выборок
		fftNums[i].ReNum = ((int16_t)(ADC_sum >> 1) - VIRTUAL_GND_SHIFT) >> 2;
		
		// Установка мнимого число на ноль
		fftNums[i].ImNum = 0;
		ADC_sum = 0;
		
		/*
			Эта задержка калибруется с помощью осциллографа 
			в соответствии с выходным сигналом PA2, 
			чтобы обеспечить правильность периодов выборки
			с учетом накладных расходов
			остальной части кода и времени выборки АЦП.
		*/
		
		delay_us(MDR_TIMER2, 20);
		
		// Дополнительная задержка для получения 50 мкс за цикл
	}
}


/*void drawHistogram(int16_t realNumbers[])
{
	static int16_t column[32] = {0};
	
	// Отрисовка гистограммы выходных данных БПФ
	if(column[i] < realNumbers[i])
		LCD_drawFilledRectangle(0, i*10, realNumbers[i], i*10+9, 0);
	if(column[i] > realNumbers[i])
		LCD_drawFilledRectangle(realNumbers[i], i*10, column[i], i*10+9, 0xFFFF);
	
	column[i] = realNumbers[i];
}*/


uint16_t calcFreqBlock(uint16_t freq)
{
	uint16_t block = 10000/FFT_DOTS*2;
	uint16_t blockNum = 0;
	uint16_t i = 0;
	
	while(blockNum < freq)
	{
		blockNum += block;
		i++;
	}
	
	return i;
}


bool detectFreq(struct complexNum *fftNums, uint16_t L, uint16_t frecBlock)
{
	int32_t n = 1 << L-1;
	int32_t mean = 0;
	int32_t difSum = 0;
	int32_t sigma = 0;
	
	for(uint8_t i = 0; i < n; i++)
	{
		mean += fftNums[i].ReNum;
	}
	
	mean /= (1 << L);
	
	for(uint8_t i = 0; i < n; i++)
	{
		difSum += (fftNums[i].ReNum - mean)*(fftNums[i].ReNum - mean);
	}
	
	sigma = sqrt(difSum/n);
	
	if(fftNums[frecBlock].ReNum >= 3*sigma)
		return true;
	else
		return false;
}
