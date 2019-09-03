#pragma once
#define DllExport __declspec( dllexport )

namespace sc
{
	/*!
	 * Mark is a combination of atribute ( color ) and char used in .bitA 
	*/
	class DllExport Mark {
	public:
		char znak;
		unsigned short color;
		Mark();
		Mark(char znak, unsigned short color);
		~Mark();
	};

	/*!
	 * Mark is a combination of atribute ( color ) and wchar_t used in .bitA
	*/
	class DllExport WMark {
	public:
		wchar_t znak;
		unsigned short color;
		WMark();
		WMark(wchar_t znak, unsigned short color);
		~WMark();
	};
}

