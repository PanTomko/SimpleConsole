#pragma once
#define DllExport __declspec( dllexport )
#include <windows.h>

namespace sc
{
	/*!
	 * Vector to is combination of x and y ( int ), used for math, coordinate etc.
	 */
	class DllExport Vector2D {
	public:
		int x, y;

		Vector2D relativeTo(const Vector2D & vector);

		operator COORD & ()const;
		Vector2D operator=(Vector2D const& vec);
		Vector2D operator=(COORD const& cor);
		Vector2D operator+(Vector2D const& vec);

		Vector2D();
		Vector2D(Vector2D const& vec);
		Vector2D(Vector2D && vec);

		Vector2D(int x, int y);
		Vector2D(const COORD & cor);

		~Vector2D();
	};
}



