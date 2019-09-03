#pragma once
#define DllExport __declspec( dllexport )
#include "Vector2D.h"

namespace sc
{
	/*!
	 *	Camera can be set for console to set what will be drow on console. Intendet for scrollling,
	 *	game view, etc. To it to work you need to set it form sc::Console::setCamera(Camera *const cam)
	 *	function.
	 */
	class DllExport Camera {
	public:
		Vector2D possition;
		Vector2D camera_size;

		/// it will make camera possition start from it center if true else form top left corrners 
		void isCentred(bool flag);

		bool isInView(const Vector2D & vector);

		bool centred;

		Camera();
		~Camera();
	};
}