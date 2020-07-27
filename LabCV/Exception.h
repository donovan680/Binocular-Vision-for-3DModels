///	@file		Exception.h
///	@brief		...
///	@licence	...
///	@designer	Tankle L.
///	@date		First created at < November 15th, 2015 >
///
///	@version	0.1.0
///
///	@programmer	Tankle L.
///	@programmer ...




#pragma once

namespace Insight{




	// < Exception[class, concrete] >
	///	@classname	Exception
	///	@designer	Tankle L.
	///	@programmer	Tankle L.
	///
	///	@brief		...
	class Exception
	{
	public:
		Exception();
		Exception(const Exception& exception);
		Exception(const std::string& text, const long& code);

	public:
		virtual std::string	ReadInfo();
		virtual void		WriteInfo(const std::string& text, const long& code);

	private:
		std::string		_text;
		long			_code;
	};
	// </ Exception>




}	// ! namespace Insight.