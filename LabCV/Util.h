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

#define	SAFE_RELEASE(pObj)			{if(nullptr != pObj) {(pObj)->Release(); pObj = nullptr;}}
#define	SAFE_DELETE(pObj)			{if(nullptr != pObj) {delete pObj; pObj = NULL;}}
#define SAFE_DELETE_ARRAY(pObj)		{if(nullptr != pObj) {delete[] pObj; pObj = NULL;}}
#define SAFE_FREE(pObj)				{if(nullptr != pObj) {free(pObj); pObj = NULL;}}
#define	SAFE_CLOSEHANDLE(pObj)		{if(nullptr != pObj || INVALID_HANDLE_VALUE != pObj) {CloseHandle(pObj); pObj = NULL;}}


namespace insight
{



	_inline PIXELCHANNEL GetPixelAValue(PIXEL pixel)
	{
		return LOBYTE((pixel) >> 24);
	}

	_inline PIXELCHANNEL GetPixelRValue(PIXEL pixel)
	{
		return LOBYTE((pixel) >> 16);
	}

	_inline PIXELCHANNEL GetPixelGValue(PIXEL pixel)
	{
		return LOBYTE(((WORD)(pixel)) >> 8);
	}

	_inline PIXELCHANNEL GetPixelBValue(PIXEL pixel)
	{
		return LOBYTE(pixel);
	}

	_inline	PIXEL PixelRGB(BYTE r, BYTE g, BYTE b)
	{
		return (PIXEL)(((BYTE)(b) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(r)) << 16) | (((DWORD)(BYTE)(0xff)) << 24));
	}

	_inline	PIXEL PixelARGB(BYTE a, BYTE r, BYTE g, BYTE b)
	{
		return (PIXEL)(((BYTE)(b) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(r)) << 16) | (((DWORD)(BYTE)(a)) << 24));
	}




}