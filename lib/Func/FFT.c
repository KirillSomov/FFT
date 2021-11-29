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
void fix_fft(int16_t fr[], int16_t fi[], uint8_t L)
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
		
		tr = fr[index];
		fr[index] = fr[invesreIndex];
		fr[invesreIndex] = tr;
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
				c = ((long int)Wr * (long int)fr[indexOdd]);
				c = c >> 14;
				b = c & 0x01;
				tr = (c >> 1) + b;
				
				c = ((long int)Wi * (long int)fi[indexOdd]);
				c = c >> 14;
				b = c & 0x01;
				tr = tr - ((c >> 1) + b);
				
				// ti = FIX_MPY(Wr,fi[j]) + FIX_MPY(Wi,fr[j]);
				c = ((long int)Wr * (long int)fi[indexOdd]);
				c = c >> 14;
				b = c & 0x01;
				ti = (c >> 1) + b;
				
				c = ((long int)Wi * (long int)fr[indexOdd]);
				c = c >> 14;
				b = c & 0x01;
				ti = ti + ((c >> 1) + b);
				
				qr = fr[indexEven];
				qi = fi[indexEven];
				qr >>= 1;
				qi >>= 1;

				fr[indexEven] = qr + tr;
				fi[indexEven] = qi + ti;
				fr[indexOdd] = qr - tr;
				fi[indexOdd] = qi - ti;
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
