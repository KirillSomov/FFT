
#ifndef FONT_H
	#define FONT_H


	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	struct fontCharInfoLookup
	{
		uint16_t	startChar;
		uint16_t	endChar;
		const uint16_t	(*descriptorsBlockArray)[3];
	};
	
	struct fontInfo
	{
		uint16_t	startChar;
		uint16_t	endChar;
		uint16_t	spaceWidth;
		const struct fontCharInfoLookup	*fontCharInfoLookupArray;
		uint16_t	charBlockArrayAmount;
		uint16_t	charDescriptorArray;
		const uint8_t	*charBitmapArray;
	};
	
	
	extern const struct fontInfo calibri_14ptFontInfo;
	extern const struct fontInfo impact_18ptFontInfo;
	

#endif
