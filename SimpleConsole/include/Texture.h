#pragma once
#define DllExport __declspec( dllexport )
#include "Vector2D.h"

#include <windows.h>

namespace sc
{
	/*
	 * Used for final product of all draw calls, maby can be used other ways.
	 */
	class DllExport Texture {
	public:
		CHAR_INFO * marks;
		
		void setWide(bool flag);
		bool getWide();
		void setTextureSize( const Vector2D & size );
		
		/// fills texture with char and at
		void fill(char c, WORD at);

		/// fills texture with wchar_t and at
		void fill(wchar_t, WORD at);

		void setCharAt( const Vector2D & posssition, const char & c );
		void setCharAt( const Vector2D & posssition, const wchar_t & c);
		
		void setAttrAt( const Vector2D & posssition, const WORD & attribute);

		Texture();
		~Texture();

	private:
		Vector2D texture_size;
		bool is_wide;
	};
}



