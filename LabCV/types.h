///	@file		Image.h
///	@brief		...
///	@licence	...
///	@designer	Tankle L.
///	@date		First created at < November 6th, 2015 >
///
///	@version	0.1.0
///
///	@programmer	Tankle L.
///	@programmer ...

#pragma once


#ifndef	_TYPES_H
#define	_TYPES_H



namespace insight
{


	typedef	struct Pixel24
	{
		BYTE	r;
		BYTE	g;
		BYTE	b;
	} PIXEL24, *PPIXEL24;

	typedef	unsigned int	PIXEL, PIXEL32;
	typedef PIXEL			*PPIXEL, *PPIXEL32;
	typedef BYTE			PIXELCHANNEL, *PPIXELCHANNEL;

	typedef enum _ImageFileType
	{
		IFT_Unknown = 0,
		IFT_BMP_24,
		IFT_BMP_32,
		IFT_JPEG,
		IFT_PNG
	} IMAGEFILETYPE, *PIMAGEFILETYPE;

	typedef struct resolution
	{
		resolution() : width(0), height(0)
		{}

		resolution(const resolution& reso) :
			width(reso.width), height(reso.height)
		{}

		int		width;
		int		height;
	} RESOLUTION, *PRESOLUTION;




}




#endif // _TYPES_H