
#ifndef GUI_H
	#define GUI_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	#define	OBJ_LABEL_AMOUNT		23
	#define	OBJ_BUTTON_AMOUNT		3
	#define	OBJ_CANVAS_AMOUNT		0


	#ifndef	OBJ_LABEL_AMOUNT
		#error	define OBJ_LABEL_AMOUNT
	#endif
	
	#ifndef	OBJ_BUTTON_AMOUNT
		#error	define OBJ_BUTTON_AMOUNT
	#endif
	
	#ifndef	OBJ_CANVAS_AMOUNT
		#error	define OBJ_CANVAS_AMOUNT
	#endif
	
	
	// структура объекта лейбл
	typedef struct
	{
		uint16_t	X0;															// координаты кнопки
		uint16_t	X1;
		uint16_t	Y0;
		uint16_t	Y1;
		uint16_t	border;													// ширина границ
		uint16_t	mainColor;											// цвет фона
		uint16_t	borderColor;										// цвет границ
		char			*str;														// текст
		const struct fontInfo *fontInfoStruct;		// шрифт
		uint16_t	textColor;											// цвет текста
		uint16_t	textMarginX;										// отступ текста по X
		uint16_t	textMarginY;										// отступ текста по Y
		void 			(*action)(void);								// действие
		
		uint16_t	textLenght;
	}Object_Label;
	
		
	// структура объекта кнопка
	typedef struct
	{
		uint16_t	X0;															// координаты кнопки
		uint16_t	X1;
		uint16_t	Y0;
		uint16_t	Y1;
		uint16_t	border;													// ширина границ
		uint16_t	mainColor;											// цвет кнопки
		uint16_t	borderColor;										// цвет границ
		char			*str;														// текст
		const struct fontInfo *fontInfoStruct;		// шрифт
		uint16_t	textColor;											// цвет текста
		uint16_t	textMarginX;										// отступ текста по X
		uint16_t	textMarginY;										// отступ текста по Y
		uint8_t		state;													//
		volatile	uint16_t	msDelay;							// задержка до следующего нажатия
		
		uint16_t	textLenght;											//
		uint8_t		flag_buttonWasClicked;					// 
		uint16_t	timerVal;												// 
		
		// действие по нажатию кнопки
		void (*action)(void);		
	}Object_Button;
	
	
	// толщина пера
	typedef enum
	{
		Pen_fine	=	0,
		Pen_small,
		Pen_medium,
		Pen_broad,
		Pen_extraBroad
	}Pen_Weight;
	
	
	// структура объекта холст
	typedef struct
	{
		uint16_t		X0;						// координаты холста
		uint16_t		X1;
		uint16_t		Y0;
		uint16_t		Y1;
		uint16_t		border;				// ширина границ
		uint16_t		mainColor;		// цвет холста
		uint16_t		borderColor;	// цвет границ
		uint16_t		penColor;			// цвет пера
		Pen_Weight	penWeight;		// толщина пера
		
		// действие по нажатию на поле холста
		void (*action)(void);
	}Object_Canvas;
		
	
	// список объектов
	typedef struct
	{
		uint8_t					ObjLabelNum;													// кол-во лейблов
		uint8_t					ObjButtonNum;													// кол-во кнопок
		uint8_t					ObjCanvasNum;													// кол-во холстов
		Object_Label		ObjLabelList[OBJ_LABEL_AMOUNT];				// список лейблов
		Object_Button		ObjButtonList[OBJ_BUTTON_AMOUNT];			// список кнопок
		Object_Canvas		ObjCanvasList[OBJ_CANVAS_AMOUNT];			// список холстов
	}Object_List_t;

	
	typedef	struct
	{
		uint16_t	X;
		uint16_t	Y;
	}tPoint_t;
	
	
	typedef	struct
	{
		uint8_t					flag_touch;
		tPoint_t				touchPoint;
		Object_List_t		objList;
		void 						(*objActionFunc)(void);
	}GUI_t;
	
	
	extern GUI_t GUI;
	

	// прототипы функций
	void	GUI_drawFrame(uint16_t	X0,	uint16_t	X1,					// X-координаты объекта	// отрисовка границ объекта
											uint16_t	Y0,	uint16_t	Y1,					// Y-координаты объекта
											uint16_t	border,										// ширина границ
											uint16_t	borderColor);							// цвет гнраниц
	void	GUI_drawFilledFrame(uint16_t	X0,	uint16_t	X1,		// X-координаты объекта	// отрисовка границ объекта
														uint16_t	Y0,	uint16_t	Y1,		// Y-координаты объекта
														uint16_t	border,							// ширина границ
														uint16_t	mainColor,					// основной цвет
														uint16_t	borderColor);				// цвет гнраниц
	void	GUI_drawPicture(uint16_t	X0,											// X-координаты объекта	// отрисовка картинки
												uint16_t	Y0,											// Y-координаты объекта
												uint16_t	border,									// ширина границ
												uint16_t	pictureColor,						// основной цвет
												uint16_t	borderColor,						// цвет границ
												uint16_t	*picture);							// указатель на картинку
	void	GUI_intToStr(int32_t num, char *strBuf);					//
	void	GUI_floatToStr(float num, char *strBuf);					//


	void	GUI_objectListReset(void);													// очистка списка объектов
	void	GUI_getTouchPoint(void);														// получить координаты нажатия
	void	GUI_objSetHandlerFunc(void (*objActionFunc)(void));	// установить действия для объектов
	void	GUI_objHandler(void);																// обработчик объетов
	void	GUI_Handler(void);																	// обработчик нажатия на дисплей

	
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
												void			(*action)(void));			// функция привязаная к лейблу
	void	GUI_labelChangeText(uint8_t	labelNum,
															char	*str,
													uint16_t	textColor,
							const struct fontInfo *fontInfoStruct);					// сменить текст лейбла
	void	GUI_labelChangeMainColor(uint8_t	labelNum,
																uint16_t	mainColor);		// сменить цвет лейбла


	void	GUI_createButton(uint16_t	X0,	uint16_t	X1,			// X-координаты кнопки	// создать кнопку
												uint16_t	Y0,	uint16_t	Y1,			// Y-координаты кнопки
												uint16_t	border,								// ширина границ
												uint16_t	mainColor,						// основной цвет кнопки
												uint16_t	borderColor,					// цвет границ
												char			*str,									// текст
												uint16_t	textColor,						// цвет текста
						const struct fontInfo *fontInfoStruct,			// шрифт
												uint16_t	textMarginX,					// отступ текста по X
												uint16_t	textMarginY,					// отступ текста по Y											
												uint8_t		state,								//
												uint16_t	msDelay,							// задержка до следующего нажатия
												void			(*action)(void));			// функция привязаная к кнопке
	void	GUI_buttonChangeText(uint8_t	buttonNum,
																char	*str,
														uint16_t	textColor,
								const struct fontInfo *fontInfoStruct);				// сменить текст кнопки
	void	GUI_buttonChangeMainColor(uint8_t	buttonNum,
																uint16_t	mainColor);		// сменить цвет кнопки


	void	GUI_createCanvas(uint16_t		X0,	uint16_t	X1,			// X-координаты кнопки	// создать холст
												uint16_t		Y0,	uint16_t	Y1,			// Y-координаты кнопки
												uint16_t		border,								// ширина границ
												uint16_t		mainColor,						// основной цвет холста
												uint16_t		borderColor,					// цвет границ
												Pen_Weight	penWeight,						// толщина пера
												uint16_t		penColor,							// цвет пера
												void				(*action)(void));			// функция привязаная к холсту
	void	GUI_canvasClear(uint8_t canvasNum);								// очистить холст
	void	GUI_canvasChangePenColor(uint8_t	canvasNum,
																uint16_t	newPenColor);		// сменить цвет пера холста
	void	GUI_canvasSetPenEraser(uint8_t	canvasNum);				//
	void	GUI_canvasDrawPoint(Pen_Weight	penWeight,
															uint16_t	pointColor);			// поставить точку на холсте


#endif
