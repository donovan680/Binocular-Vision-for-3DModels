///	@file		Image.cpp
///	@brief		...
///	@licence	...
///	@designer	Tankle L.
///	@date		First created at < November 6th, 2015 >
///
///	@version	0.1.0
///
///	@programmer	Tankle L.
///	@programmer ...



#include "stdafx.h"

#include "Insight.h"

using namespace std;


// < IImage [class, abstract] >
///	@classname	IImage
///	@designer	Tankle L.
///
///	@brief		...
///	@modified	Tankle L.	2015.11.6

Insight::IImage::IImage() : _pBuffer(nullptr)
{}

Insight::IImage::~IImage()
{
	SAFE_DELETE_ARRAY(_pBuffer);
}

void Insight::IImage::CopyFrom(IImage* const pImage)
{
	SAFE_DELETE_ARRAY(_pBuffer);

	pImage->GetImgResolution(_resolution);

	if (_resolution.width == 0 ||
		_resolution.height == 0)
		return;

	_pBuffer = new PIXEL[_resolution.width * _resolution.height];
	
	memcpy(_pBuffer, pImage->GetPixelBuffer(), sizeof(PIXEL)* _resolution.width * _resolution.height);
}

void Insight::IImage::Blank()
{
	if (nullptr != _pBuffer)
	{
		memset(_pBuffer, 0, sizeof(PIXEL)* _resolution.width * _resolution.height);
	}
}

// </ IImage >




// < ImageBitmap24 [class, abstract] >
///	@classname	ImageBitmap24
///	@designer	Tankle L.
///
///	@brief		...
///	@modified	Tankle L.	2015.11.6

Insight::ImageBitmap24::ImageBitmap24()
{}

Insight::ImageBitmap24::ImageBitmap24(const RESOLUTION& reso)
{
	_resolution = reso;

	if (_resolution.width == 0 ||
		_resolution.height == 0)
		return;

	_pBuffer = new PIXEL[_resolution.width * _resolution.height];
	memset(_pBuffer, 0, sizeof(PIXEL)* _resolution.width * _resolution.height);	
}

Insight::ImageBitmap24::~ImageBitmap24()
{
	SAFE_DELETE_ARRAY(_pBuffer);
}

void Insight::ImageBitmap24::FromFile(const std::string& fileName)
{
	Insight::Exception	excep;
	BITMAPFILEHEADER	bfh;
	BITMAPINFOHEADER	bih;

	ifstream	file(fileName, ios_base::in| ios_base::binary);

	if (!file.is_open())
	{
		excep.WriteInfo(string("Cannot open file."), -1);

		throw excep;
	}

	file.read(reinterpret_cast<char*>(&bfh), sizeof(bfh));
	if (file.fail())
	{
		excep.WriteInfo(string("Cannot read bitmap-file-header."), -1);
		file.close();

		throw excep;
	}

	file.read(reinterpret_cast<char*>(&bih), sizeof(bih));
	if (file.fail())
	{
		excep.WriteInfo(string("Cannot read bitmap-info-header."), -1);
		file.close();

		throw excep;
	}

	DWORD	btr = bfh.bfSize - bfh.bfOffBits;
	if (btr == 0)	// no image data
	{
		SAFE_DELETE_ARRAY(_pBuffer);
		_resolution.width = 0;
		_resolution.height = 0;
		return;
	}
	else			// image data exists
	{
		_resolution.width = bih.biWidth;
		_resolution.height = bih.biHeight;

		// Clear old buffer.
		SAFE_DELETE_ARRAY(_pBuffer);

		// create temporary buffer and read pixel24 data.
		BYTE* pBuf24 = new BYTE[btr];

		file.read((char*)pBuf24, btr);
		if (file.fail())
		{
			excep.WriteInfo(string("Cannot read image data."), -1);
			file.close();
			_resolution.width = 0;
			_resolution.height = 0;

			delete[] pBuf24;
			
			throw excep;
		}
		// Close file.
		file.close();

		// create pixel buffer and convert 24bit-data into 32bit-data
		_pBuffer = new PIXEL[_resolution.width*_resolution.height];

			// convert
		BYTE*			pChannel = pBuf24;
		unsigned int	index = 0;
		unsigned int	alignoffset = 0;

		if ((3 * _resolution.width) % 4 != 0)
		{
			alignoffset = 4 - (3 * _resolution.width) % 4;
		}

		for (int y = 0; y < _resolution.height; ++y)
		{
			for (int x = 0; x < _resolution.width; ++x)
			{
				_pBuffer[index] = PixelRGB( pChannel[2],	// r
											pChannel[1],	// g
											pChannel[0]);	// b
				pChannel += 3;
				++index;
			}
			pChannel += alignoffset;
		}

		// release resource
		delete[] pBuf24;
	}
}

void Insight::ImageBitmap24::ToFile(const std::string& fileName)
{
}


Insight::IMAGEFILETYPE Insight::ImageBitmap24::GetImageFileType() const
{
	return Insight::IFT_BMP_24;
}

// </ ImageBitmap24 >





// < ImageBitmap32 [class, abstract] >
///	@classname	ImageBitmap32
///	@designer	Tankle L.
///
///	@brief		...
///	@modified	Tankle L.	2015.11.6

Insight::ImageBitmap32::ImageBitmap32()
{}

Insight::ImageBitmap32::ImageBitmap32(const RESOLUTION& reso)
{
	_resolution = reso;

	if (_resolution.width == 0 ||
		_resolution.height == 0)
		return;

	_pBuffer = new PIXEL[_resolution.width * _resolution.height];
	memset(_pBuffer, 0, sizeof(PIXEL)* _resolution.width * _resolution.height);
}

Insight::ImageBitmap32::~ImageBitmap32()
{
	SAFE_DELETE_ARRAY(_pBuffer);
}

void Insight::ImageBitmap32::FromFile(const std::string& fileName)
{
}

void Insight::ImageBitmap32::ToFile(const std::string& fileName)
{
	ofstream			file(fileName, ios_base::out | ios_base::binary);
	Insight::Exception	excep;
	BITMAPFILEHEADER	bfh;
	BITMAPINFOHEADER	bih;

	if (!file.is_open())
	{
		excep.WriteInfo(string("Cannot open file to write data."), -1);

		throw excep;
	}
	

	bfh.bfType = 0x4d42;	// BM
	bfh.bfSize = sizeof(bfh) + sizeof(bih) + 
		_resolution.width * _resolution.height * sizeof(PIXEL);
	bfh.bfOffBits = sizeof(bfh)+sizeof(bih);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;

	memset(&bih, 0, sizeof(bih));
	bih.biBitCount = 32;
	bih.biCompression = BI_RGB;
	bih.biHeight = _resolution.height;
	bih.biWidth	= _resolution.width;
	bih.biPlanes = 1;
	bih.biSize = sizeof(bih);
	bih.biSizeImage = _resolution.width * _resolution.height * sizeof(PIXEL);

	file.write(reinterpret_cast<char*>(&bfh), sizeof(bfh));
	if (file.fail())
	{
		excep.WriteInfo(string("Cannot write bitmap-file-header into the file."), -1);
		file.close();

		throw excep;
	}

	file.write(reinterpret_cast<char*>(&bih), sizeof(bih));
	if (file.fail())
	{
		excep.WriteInfo(string("Cannot write bitmap-info-header into the file."), -1);
		file.close();

		throw excep;
	}

	file.write(reinterpret_cast<char*>(_pBuffer), _resolution.width * _resolution.height * sizeof(PIXEL));
	if (file.fail())
	{
		excep.WriteInfo(string("Cannot write image data the file."), -1);
		file.close();

		throw excep;
	}

	file.close();
}


Insight::IMAGEFILETYPE Insight::ImageBitmap32::GetImageFileType() const
{
	return Insight::IFT_BMP_24;
}

// </ ImageBitmap24 >