#pragma once
#define DllExport __declspec( dllexport )
#include <windows.h>

namespace sc
{
	// Events for mouse dont work for repetinh/holding buttons !

	enum class DllExport MouseKeys {
		Null = 0x0000,
		LeftButton = 0x0001,
		RightButton = 0x0002,
		WeelButton = 0x0004
	};

	/*
	 * Holds informations about mouse single mouse event.
	 */
	class DllExport MouseEvent {
	public:

		unsigned char keyState; // just_pressed/just_relased/pressed
		MouseKeys key;
		COORD position;

		bool isKey(const MouseKeys & key);
		bool isKeyJustRelased(const MouseKeys & key);
		bool isKeyJustPressed(const MouseKeys & key);

		MouseEvent();
		~MouseEvent();
	};
}