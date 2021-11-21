
#include "GUI.h"


GUI_t GUI;


// отрисовка рамки
void	GUI_drawFrame(uint16_t	X0,	uint16_t	X1,			// X-координаты
										uint16_t	Y0,	uint16_t	Y1,			// Y-координаты
										uint16_t	border,								// ширина рамки
										uint16_t	borderColor)					// цвет рамки
{
	// отрисовка рамки
	LCD_drawFilledRectangle(X0, X0+(border-1), Y0, Y1, borderColor);
	LCD_drawFilledRectangle(X0, X1, Y1-(border-1), Y1, borderColor);
	LCD_drawFilledRectangle(X1-(border-1), X1, Y0, Y1, borderColor);
	LCD_drawFilledRectangle(X0, X1, Y0, Y0+(border-1), borderColor);
}

// отрисовка заполненной рамки
void	GUI_drawFilledFrame(uint16_t	X0,	uint16_t	X1,			// X-координаты
													uint16_t	Y0,	uint16_t	Y1,			// Y-координаты
													uint16_t	border,								// ширина рамки
													uint16_t	mainColor,						// основной цвет
													uint16_t	borderColor)					// цвет рамки
{
	LCD_drawFilledRectangle(X0, X1, Y0, Y1, mainColor);
	// отрисовка рамки
	if(border > 0)
	{
		LCD_drawFilledRectangle(X0, X0+(border-1), Y0, Y1, borderColor);
		LCD_drawFilledRectangle(X0, X1, Y1-(border-1), Y1, borderColor);
		LCD_drawFilledRectangle(X1-(border-1), X1, Y0, Y1, borderColor);
		LCD_drawFilledRectangle(X0, X1, Y0, Y0+(border-1), borderColor);
	}
}

// отрисовка картинки
void	GUI_drawPicture(uint16_t	X0,											// X-координаты объекта
											uint16_t	Y0,											// Y-координаты объекта
											uint16_t	border,									// ширина границ
											uint16_t	pictureColor,						// основной цвет
											uint16_t	borderColor,						// цвет границ
											uint16_t	*picture)								// указатель на картинку
{
	;
}

// 
void	GUI_intToStr(int32_t num, char *strBuf)
{
	uint8_t	charCounter	=	0;
	char		bufChar			=	0;
	
	if(num == 0)
	{
		*strBuf = '0';
		strBuf++;
		*strBuf = '\0';
		return;
	}
	
	if(num < 0)
	{
		*strBuf = '-';
		strBuf++;
	}
	
	while(num)
	{
		*strBuf = '0' + num % 10;
		if(num / 10)
		{
			strBuf++;
			charCounter++;
		}
		num = num / 10;
	}
	
	strBuf = strBuf - charCounter;
	
	for(uint8_t i = 0; i < charCounter/2+1; i++)
	{
		bufChar			=	*(strBuf+i);
		*(strBuf+i)	=	*(strBuf+charCounter-i);
		*(strBuf+charCounter-i) = bufChar;
	}
	
	*(strBuf+charCounter+1) = '\0';
}

// 
void	GUI_floatToStr(float num, char *strBuf)
{
	int32_t	numInt				=	(int32_t)(num*10);
	uint8_t	charCounter		=	0;
	char		bufChar				=	0;
	
	
	if(num < 0)
	{
		*strBuf = '-';
		strBuf++;
	}
	
	if(numInt < 10  && numInt >= 0)
	{
		*strBuf = '0';
		strBuf++;
		*strBuf = '.';
		strBuf++;
		*strBuf = '0' + numInt % 10;
		strBuf++;
		*strBuf = '\0';
		return;
	}
	
	while(numInt)
	{
		if(charCounter == 1)
		{
			*strBuf = '.';
			strBuf++;
			charCounter++;
		}
		*strBuf = '0' + numInt % 10;
		if(numInt / 10)
		{
			strBuf++;
			charCounter++;
		}
		numInt = numInt / 10;
	}
	
	strBuf = strBuf - charCounter;
	
	for(uint8_t i = 0; i < charCounter/2+1; i++)
	{
		bufChar			=	*(strBuf+i);
		*(strBuf+i)	=	*(strBuf+charCounter-i);
		*(strBuf+charCounter-i) = bufChar;
	}
	
	*(strBuf+charCounter+1) = '\0';
}


// очистка списка объектов
void	GUI_objectListReset(void)
{
	GUI.objList.ObjLabelNum 		= 0;
	GUI.objList.ObjButtonNum 		= 0;
	GUI.objList.ObjCanvasNum		= 0;
}

// получить координаты нажатия
void	GUI_getTouchPoint(void)
{
	/*GUI.flag_touch = FT6236_checkInt();
	
	//GUI.flag_touch = 1;
	
	if(GUI.flag_touch)
	{
		FT6236_get_Tpoint(&FT6236_Tpoint);
		
		GUI.touchPoint.X = FT6236_Tpoint.Xt;
		GUI.touchPoint.Y = FT6236_Tpoint.Yt;
	}*/
}

// установить действия для объектов
void	GUI_objSetHandlerFunc(void (*objActionFunc)(void))
{
	GUI.objActionFunc = objActionFunc;
}

// обработчик объетов
void	GUI_objHandler(void)
{
	GUI.objActionFunc();
}

// обработчик нажатия на дисплей
void	GUI_Handler(void)
{	
	//GUI_getTouchPoint();
	
	GUI_objHandler();
	
	#if OBJ_BUTTON_AMOUNT > 0
		if(GUI.flag_touch)
		{
			for(uint8_t objButNum = 0; objButNum < OBJ_BUTTON_AMOUNT; objButNum++)
			{		
				if((GUI.touchPoint.X < GUI.objList.ObjButtonList[objButNum].X0) || (GUI.touchPoint.X > GUI.objList.ObjButtonList[objButNum].X1))
					continue;
				else if((GUI.touchPoint.Y < GUI.objList.ObjButtonList[objButNum].Y0) || (GUI.touchPoint.Y > GUI.objList.ObjButtonList[objButNum].Y1))
					continue;
				else
				{
					if(GUI.objList.ObjButtonList[objButNum].flag_buttonWasClicked == 0)
					{
						GUI.objList.ObjButtonList[objButNum].action();
						
						if(GUI.objList.ObjButtonList[objButNum].msDelay != 0)
						{
							GUI.objList.ObjButtonList[objButNum].flag_buttonWasClicked = 1;
							GUI.objList.ObjButtonList[objButNum].timerVal = GUI.objList.ObjButtonList[objButNum].msDelay;
						}
					}
					GUI.flag_touch				=	0;
					return;
				}
			}
		}
	#endif
	
	#if OBJ_CANVAS_AMOUNT > 0
		if(GUI.flag_touch)
		{
			for(uint8_t objCanvasNum = 0; objCanvasNum < OBJ_CANVAS_AMOUNT; objCanvasNum++)
			{
				if((GUI.touchPoint.X < GUI.objList.ObjCanvasList[objCanvasNum].X0) || (GUI.touchPoint.X > GUI.objList.ObjCanvasList[objCanvasNum].X1))
					continue;
				else if((GUI.touchPoint.Y < GUI.objList.ObjCanvasList[objCanvasNum].Y0) || (GUI.touchPoint.Y > GUI.objList.ObjCanvasList[objCanvasNum].Y1))
					continue;
				else
				{
					GUI_drawPoint(GUI.objList.ObjCanvasList[objCanvasNum].penWeight, GUI.objList.ObjCanvasList[objCanvasNum].penColor);
					
					if(GUI.objList.ObjCanvasList[objCanvasNum].action != 0)
						GUI.objList.ObjCanvasList[objCanvasNum].action();
					GUI.flag_touch				=	0;
					return;
				}
			}
		}
	#endif
}


// создать лейбл
void	GUI_createLabel(uint16_t	X0,	uint16_t	X1,			// X-координаты	// создать лейбл
											uint16_t	Y0,	uint16_t	Y1,			// Y-координаты
											uint16_t	border,								// ширина границ
											uint16_t	mainColor,						// основной цвет
											uint16_t	borderColor,					// цвет границ
											char			*str,									// текст
											uint16_t	textColor,						// цвет текста
					const struct fontInfo *fontInfoStruct,			// шрифт
											uint16_t	textMarginX,					// отступ текста по X
											uint16_t	textMarginY,					// отступ текста по Y
											void			(*action)(void))			// функция привязаная к лейблу
{
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].X0	=	X0;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].X1	=	X1;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].Y0	=	Y0;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].Y1	=	Y1;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].border					=	border;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].mainColor				=	mainColor;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].borderColor			=	borderColor;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].str							=	str;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].textColor				=	textColor;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].fontInfoStruct	=	fontInfoStruct;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].textMarginX			=	textMarginX;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].textMarginY			=	textMarginY;
	GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].action					=	action;
	
	GUI_drawFilledFrame(X0, X1, Y0, Y1, border, mainColor, borderColor);		// отрисовка лейбла
	
	if(str != 0)
		GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].textLenght = LCD_printString(X0+textMarginX, Y0+textMarginY, str, textColor, fontInfoStruct);
	else
		GUI.objList.ObjLabelList[GUI.objList.ObjLabelNum].textLenght = 0;
	
	GUI.objList.ObjLabelNum++;	// инкрементирование индекса для следующего объекта
}

// сменить текст лейбла
void	GUI_labelChangeText(uint8_t labelNum, char *str, uint16_t	textColor, const struct fontInfo *fontInfoStruct)
{
	GUI.objList.ObjLabelList[labelNum].str 						= str;
	GUI.objList.ObjLabelList[labelNum].textColor			=	textColor;
	GUI.objList.ObjLabelList[labelNum].fontInfoStruct	=	fontInfoStruct;
	
	GUI_drawFilledFrame(GUI.objList.ObjLabelList[labelNum].X0+GUI.objList.ObjLabelList[labelNum].textMarginX,
											GUI.objList.ObjLabelList[labelNum].textLenght,
											GUI.objList.ObjLabelList[labelNum].Y0+GUI.objList.ObjLabelList[labelNum].textMarginY,
											GUI.objList.ObjLabelList[labelNum].Y0+GUI.objList.ObjLabelList[labelNum].textMarginY+24,
											0,
											GUI.objList.ObjLabelList[labelNum].mainColor,
											0);																						// закркасить старый цвет
	
	if(str != 0)
		GUI.objList.ObjLabelList[labelNum].textLenght = LCD_printString(GUI.objList.ObjLabelList[labelNum].X0+GUI.objList.ObjLabelList[labelNum].textMarginX,
																																GUI.objList.ObjLabelList[labelNum].Y0+GUI.objList.ObjLabelList[labelNum].textMarginY,
																																str, textColor, fontInfoStruct);
}

// сменить цвет лейбла
void	GUI_labelChangeMainColor(uint8_t labelNum, uint16_t	mainColor)
{
	GUI.objList.ObjLabelList[labelNum].mainColor = mainColor;
	
	GUI_drawFilledFrame(GUI.objList.ObjLabelList[labelNum].X0,
											GUI.objList.ObjLabelList[labelNum].X1,
											GUI.objList.ObjLabelList[labelNum].Y0,
											GUI.objList.ObjLabelList[labelNum].Y1,
											GUI.objList.ObjLabelList[labelNum].border,
											GUI.objList.ObjLabelList[labelNum].mainColor,
											GUI.objList.ObjLabelList[labelNum].borderColor);					// закркасить старый цвет
	
	if(GUI.objList.ObjLabelList[labelNum].str != 0)
		GUI_labelChangeText(labelNum, GUI.objList.ObjLabelList[labelNum].str, GUI.objList.ObjLabelList[labelNum].textColor, GUI.objList.ObjLabelList[labelNum].fontInfoStruct);
}


// создать кнопку
void	GUI_createButton(uint16_t	X0,	uint16_t	X1,			// X-координаты кнопки
											uint16_t	Y0,	uint16_t	Y1,			// Y-координаты кнопки
											uint16_t	border,								// ширина границ
											uint16_t	mainColor,						// основной цвет кнопки
											uint16_t	borderColor,					// цвет границ
											char			*str,									// текст
											uint16_t	textColor,						// цвет текста
					const struct fontInfo *fontInfoStruct,			// шрифт
											uint16_t	textMarginX,					// отступ текста по X
											uint16_t	textMarginY,					// отступ текста по Y											
											uint8_t		state,
											uint16_t	msDelay,							// задержка до следующего нажатия
											void			(*action)(void))			// функция привязаная к кнопке
{
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].X0	=	X0;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].X1	=	X1;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].Y0	=	Y0;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].Y1	=	Y1;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].border							=	border;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].mainColor						=	mainColor;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].borderColor					=	borderColor;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].str									=	str;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].textColor						=	textColor;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].fontInfoStruct			=	fontInfoStruct;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].textMarginX					=	textMarginX;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].textMarginY					=	textMarginY;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].state								=	state;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].msDelay							=	msDelay;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].flag_buttonWasClicked	= 0;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].timerVal 						= 0;
	GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].action							=	action;
	
	GUI_drawFilledFrame(X0, X1, Y0, Y1, border, mainColor, borderColor);		// отрисовка кнопки
	
	if(str != 0)
		GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].textLenght = LCD_printString(X0+textMarginX, Y0+textMarginY, str, textColor, fontInfoStruct);
	else
		GUI.objList.ObjButtonList[GUI.objList.ObjButtonNum].textLenght = 0;
	
	GUI.objList.ObjButtonNum++;	// инкрементирование индекса для следующего объекта
}

// сменить текст кнопки
void	GUI_buttonChangeText(uint8_t buttonNum, char *str, uint16_t	textColor, const struct fontInfo *fontInfoStruct)
{
	GUI.objList.ObjButtonList[buttonNum].str 						= str;
	GUI.objList.ObjButtonList[buttonNum].textColor			=	textColor;
	GUI.objList.ObjButtonList[buttonNum].fontInfoStruct	=	fontInfoStruct;
	
	GUI_drawFilledFrame(GUI.objList.ObjButtonList[buttonNum].X0+GUI.objList.ObjButtonList[buttonNum].textMarginX,
											GUI.objList.ObjButtonList[buttonNum].textLenght,
											GUI.objList.ObjButtonList[buttonNum].Y0+GUI.objList.ObjButtonList[buttonNum].textMarginY,
											GUI.objList.ObjButtonList[buttonNum].Y0+GUI.objList.ObjButtonList[buttonNum].textMarginY+24,
											0,
											GUI.objList.ObjButtonList[buttonNum].mainColor,
											0);																							// закркасить старый цвет
	
	if(str != 0)
		GUI.objList.ObjButtonList[buttonNum].textLenght = LCD_printString(GUI.objList.ObjButtonList[buttonNum].X0+GUI.objList.ObjButtonList[buttonNum].textMarginX,
																																GUI.objList.ObjButtonList[buttonNum].Y0+GUI.objList.ObjButtonList[buttonNum].textMarginY,
																																str, textColor, fontInfoStruct);
}

// сменить цвет кнопки
void	GUI_buttonChangeMainColor(uint8_t buttonNum, uint16_t	mainColor)
{
	GUI.objList.ObjButtonList[buttonNum].mainColor = mainColor;
	
	GUI_drawFilledFrame(GUI.objList.ObjButtonList[buttonNum].X0,
											GUI.objList.ObjButtonList[buttonNum].X1,
											GUI.objList.ObjButtonList[buttonNum].Y0,
											GUI.objList.ObjButtonList[buttonNum].Y1,
											GUI.objList.ObjButtonList[buttonNum].border,
											GUI.objList.ObjButtonList[buttonNum].mainColor,
											GUI.objList.ObjButtonList[buttonNum].borderColor);					// закркасить старый цвет
	
	if(GUI.objList.ObjButtonList[buttonNum].str != 0)
		GUI_buttonChangeText(buttonNum, GUI.objList.ObjButtonList[buttonNum].str, GUI.objList.ObjButtonList[buttonNum].textColor, GUI.objList.ObjButtonList[buttonNum].fontInfoStruct);
}


// создать холст
void	GUI_createCanvas(uint16_t		X0,	uint16_t	X1,			// X-координаты кнопки
											uint16_t		Y0,	uint16_t	Y1,			// Y-координаты кнопки
											uint16_t		border,								// ширина границ
											uint16_t		mainColor,						// основной цвет холста
											uint16_t		borderColor,					// цвет границ
											Pen_Weight	penWeight,						// толщина пера
											uint16_t		penColor,							// цвет пера
											void				(*action)(void))			// функция привязаная к холсту
{
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].X0	=	X0;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].X1	=	X1;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].Y0	=	Y0;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].Y1	=	Y1;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].border			=	border;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].mainColor		=	mainColor;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].borderColor	=	borderColor;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].penWeight		=	penWeight;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].penColor		=	penColor;
	GUI.objList.ObjCanvasList[GUI.objList.ObjCanvasNum].action			=	action;
	
	GUI_drawFilledFrame(X0, X1, Y0, Y1, border, mainColor, borderColor);		// отрисовка холста
	
	GUI.objList.ObjCanvasNum++;
}

// очистить холст
void	GUI_canvasClear(uint8_t canvasNum)
{
	LCD_drawFilledRectangle(GUI.objList.ObjCanvasList[canvasNum].X0+GUI.objList.ObjCanvasList[canvasNum].border,
													GUI.objList.ObjCanvasList[canvasNum].X1-GUI.objList.ObjCanvasList[canvasNum].border,
													GUI.objList.ObjCanvasList[canvasNum].Y0+GUI.objList.ObjCanvasList[canvasNum].border,
													GUI.objList.ObjCanvasList[canvasNum].Y1-GUI.objList.ObjCanvasList[canvasNum].border,
													0xFFFF);
}

// сменить цвет пера холста
void	GUI_canvasChangePenColor(uint8_t canvasNum, uint16_t newPenColor)
{
	GUI.objList.ObjCanvasList[canvasNum].penColor	=	newPenColor;
}

// 
void	GUI_canvasSetPenEraser(uint8_t canvasNum)
{
	GUI.objList.ObjCanvasList[canvasNum].penColor	=	0xFFFF;
}

// поставить точку на холсте
void	GUI_drawPoint(Pen_Weight penWeight, uint16_t pointColor)
{
	// отрисовка точки
	switch(penWeight)
	{
		case Pen_fine:
			LCD_drawPixel(GUI.touchPoint.X, GUI.touchPoint.Y, pointColor);
			break;
		case Pen_small:
			LCD_drawFilledRectangle(GUI.touchPoint.X-1, GUI.touchPoint.X+1, GUI.touchPoint.Y-1, GUI.touchPoint.Y+1, pointColor);
			break;
		case Pen_medium:
			LCD_drawFilledRectangle(GUI.touchPoint.X-2, GUI.touchPoint.X-2, GUI.touchPoint.Y-1, GUI.touchPoint.Y+1, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-1, GUI.touchPoint.X+1, GUI.touchPoint.Y-2, GUI.touchPoint.Y+2, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+2, GUI.touchPoint.X+1, GUI.touchPoint.Y-2, GUI.touchPoint.Y-2, pointColor);
			break;
		case Pen_broad:
			LCD_drawFilledRectangle(GUI.touchPoint.X-3, GUI.touchPoint.X-3, GUI.touchPoint.Y-1, GUI.touchPoint.Y+1, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-2, GUI.touchPoint.X-2, GUI.touchPoint.Y-2, GUI.touchPoint.Y+2, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-1, GUI.touchPoint.X+1, GUI.touchPoint.Y-3, GUI.touchPoint.Y+3, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+2, GUI.touchPoint.X+2, GUI.touchPoint.Y-2, GUI.touchPoint.Y+2, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+3, GUI.touchPoint.X+3, GUI.touchPoint.Y-1, GUI.touchPoint.Y+1, pointColor);
			break;
		case Pen_extraBroad:
			LCD_drawFilledRectangle(GUI.touchPoint.X-6, GUI.touchPoint.X-6, GUI.touchPoint.Y-2, GUI.touchPoint.Y+2, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-5, GUI.touchPoint.X-5, GUI.touchPoint.Y-4, GUI.touchPoint.Y+4, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-4, GUI.touchPoint.X-3, GUI.touchPoint.Y-5, GUI.touchPoint.Y+5, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X-2, GUI.touchPoint.X+2, GUI.touchPoint.Y-6, GUI.touchPoint.Y+6, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+3, GUI.touchPoint.X+4, GUI.touchPoint.Y-5, GUI.touchPoint.Y+5, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+5, GUI.touchPoint.X+5, GUI.touchPoint.Y-4, GUI.touchPoint.Y+4, pointColor);
			LCD_drawFilledRectangle(GUI.touchPoint.X+6, GUI.touchPoint.X+6, GUI.touchPoint.Y-2, GUI.touchPoint.Y+2, pointColor);
			break;
	}		
}
