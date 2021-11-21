
#ifndef PICTURE_H
	#define PICTURE_H


	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	struct pictureInfo
	{
		const uint16_t	(*pictureDescriptorArray)[2];
		const uint8_t		*pictureBitmapArray;
	};
	
	
	extern const struct pictureInfo logoJINRInfo;
	extern const struct pictureInfo logoDialtekBlackInfo;
	extern const struct pictureInfo logoDialtekGreenInfo;
	
	
#endif
