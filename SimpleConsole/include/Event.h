#pragma once
#define DllExport __declspec( dllexport )
#include "KeyboardEvent.h"
#include "MouseEvent.h"

namespace sc 
{
	/*
	 * Holds informations about single event of one type.
	 */
	class DllExport Event {
	public:
		enum class Type {
			Keyboard = 0x0001,
			Mouse = 0x0002
		};

		Type event_type;
		KeyboardEvent keyboardEvent;
		MouseEvent mouseEvent;

		Event();
		~Event();
	};
}



