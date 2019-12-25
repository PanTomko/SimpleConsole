#pragma once
#define DllExport __declspec( dllexport )
#include "ConsoleModuleEvent.h"

#include "Vector2D.h"
#include "Camera.h"
#include "BitA.h"
#include "Texture.h"
#include "EventObserver.h"

#include <windows.h>
#include <string>

//#define DllExport __declspec( dllexport )

namespace sc 
{
	/*!
	 * Console provaide interface for windows promp. It supports event handling,
	 * changing settings, drawing on to it, double buffering for non fickering ( intended for games ) 
	*/
	class DllExport Console : public ConsoleModuleEvent {
	public:

		sc::EventObserver<sc::Vector2D> ev_buffer_resize;
		sc::EventObserver<sc::Vector2D> ev_console_resize;
		
		sc::EventObserver<std::wstring> ev_title_change;
		sc::EventObserver<std::wstring> ev_font_family_change;

		sc::EventObserver<unsigned int> ev_font_size_change;

		/// final resul that will be draw to console buffer ( the one that is not visible )
		Texture buffer_texture;

		/// sets console title
		void setTitle( std::wstring title);

		///
		void setFontFamily(std::wstring family);

		void setFontSize(unsigned int size);

		/// enable unicode encoding utf_8 ( if u do that u cant use cout insted use wcout etc. )
		void enableUnicodeEncoding();

		/// cleans active buffer if no other specifed ( the one that is not shown to user )
		void clean(HANDLE * output_buffer = nullptr);

		/// Swaps buffers ( shows active buffer )
		void display();

		///
		/// returns cursor position true for buffer X, be defoult it will check active buffer
		/// ( the one that is not shown to user )
		///
		Vector2D getCursorPossition(HANDLE * handle = nullptr);

		/// sets cursor possition for both buffers
		void setCursorPossition(const Vector2D & possition);

		/// hide/show blinking currsor
		void showCursor(bool flag);

		//void setCamerea( Camera *const cam );
		void setCameraActive(bool flag);

		Camera default_camera;
		Camera *active_camera;
		bool is_camera_active;

		void draw(char z, Vector2D possition);
		void draw(wchar_t z, Vector2D possition);

		void setAtribute(WORD at, Vector2D possition);

		void draw(const Mark& mark, Vector2D possition);
		void draw(const WMark& mark, Vector2D possition);

		void draw(const std::string & str, WORD at, Vector2D possition, char xyz = 'x');
		void draw(const std::wstring & str, WORD at, Vector2D possition, char xyz = 'x');

		void draw(const BitA<WMark>& img, Vector2D possition, Vector2D start = { 0,0 }, Vector2D end = { 0,0 });
		void draw(const BitA<Mark>& img, Vector2D possition, Vector2D start = {0,0}, Vector2D end = { 0,0 });

		/// sets console size
		Vector2D setConsoleSize(const Vector2D & size);
		SMALL_RECT getConsoleSize();
		COORD getLargestConsoleSize();


		/// sets buffer size. first use void setConsoleSize(Vector2D size); to match console size
		Vector2D setBufferSize(const Vector2D & size);
		Vector2D getBufferSize();

		Console(Vector2D size, int font_size);
		~Console();

	private:
		/// handle to orginal console buffer output
		HANDLE console_buffer_one; 
		
		/// new handle to console buffer output
		HANDLE console_buffer_two;

		/// pointer to active buffer for output ( the one that is not shown to user )
		HANDLE * console_active_buffer;
		
		/// for reading events
		HANDLE console_input;

		SMALL_RECT console_size;
		Vector2D buffer_size;

		CONSOLE_FONT_INFOEX font;
	};
}



