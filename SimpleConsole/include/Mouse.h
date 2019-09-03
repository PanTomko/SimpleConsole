#pragma once
#include "MouseEvent.h"
#include "Vector2D.h"
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
	 * Singleton holds informations about mouse status for real time data acces.
	 */
	class Mouse {
	public:
		std::map<MouseKeys, unsigned char>keys;
		Vector2D position;

		/// check if mouse MouseKeys:: is pressed ( real time )
		DllExport bool isKeyPressed(MouseKeys key);
		DllExport Vector2D getPossition();

		DllS static Mouse * getInstance();

		~Mouse();
	private:
		Mouse();
		Mouse(const Mouse& mouse) = delete;
		Mouse(const Mouse&& mouse) = delete;
		Mouse & operator=(const Mouse & mouse) = delete;
		Mouse & operator=(const Mouse && mouse) = delete;
	};
}