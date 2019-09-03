#pragma once
#include "KeyboardEvent.h"
#include <map>

#define DllExport __declspec( dllexport )

#ifdef SIMPLECONSOLE_EXPORTS
#define DllS __declspec(dllexport)
#else
#define DllS __declspec(dllimport)
#endif

namespace sc
{
	/*
	 * Singleton used for real time keboard information acces
	 */
	class Keyboard {
	public:
		///
		/// map of keys used in program and thier status as bit flag 
		/// just_pressed/just_relased/pressed <- for first 3 bits
		///
		std::map<Key, unsigned char>keys;

		DllS static Keyboard * getInstance();

		~Keyboard();

	private:
		Keyboard();
		Keyboard(const Keyboard& keyboard) = delete;
		Keyboard(const Keyboard&& keyboard) = delete;
		Keyboard & operator=(const Keyboard & keyboard) = delete;
		Keyboard & operator=(const Keyboard && keyboard) = delete;
	};

	//Keyboard * Keyboard::instance = getInstance();
}



