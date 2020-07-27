///	@file		Exception.cpp
///	@brief		...
/// @licence	...
///	@designer	Tankle L.
///	@date		First created at < November 15th, 2015 >
///
///	@version	0.1.0
///
///	@programmer	Tankle L.
///	@programmer ...

#include "stdafx.h"

#include "Insight.h"


// < Exception [class, concrete] >
///	@classname	Exception
///	@designer	Tankle L.
///	@programmer	Tankle L.
///
///	@brief		...

Insight::Exception::Exception() :
_text("Exception"),
_code(0)
{}

Insight::Exception::Exception(const Exception& exception) :
_text(exception._text),
_code(exception._code)
{}

Insight::Exception::Exception(const std::string& text, const long& code) :
_text(text),
_code(code)
{}

std::string	Insight::Exception::ReadInfo()
{
	std::string	outText;
	char		czCode[30] = "";			// Max digit count: 29.

	outText.append("Exception: \"");
	outText.append(_text);
	outText.append("\" with Code: ");

	if (0 != _itoa_s(_code, czCode, 10))
	{
		outText = "Error occurs in this Exception";
		return outText;
	}

	outText.append(czCode);

	return outText;
}

void Insight::Exception::WriteInfo(const std::string& text, const long& code)
{
	_text = text;
	_code = code;
}


// </ Exception >
