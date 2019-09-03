#include "Console.h"

// Macro for _setmode


#include <io.h>
#include <fcntl.h>

// file / io 
#include <fstream> 
#include <iostream>

#include "ConsoleModuleEvent.h"

using namespace sc;

Console::Console(Vector2D size, int font_size) {

	// Setting up buffer and window
	console_buffer_one = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	console_buffer_two = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	/*
	SetConsoleMode(console_buffer_one,
		ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT |
		ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);

	SetConsoleMode(console_buffer_two,
		ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT |
		ENABLE_VIRTUAL_TERMINAL_PROCESSING
	);
	*/

	setConsoleSize(size);
	setBufferSize(size);
	
	CONSOLE_FONT_INFOEX font;
	GetCurrentConsoleFontEx(console_buffer_one, false, &font);

	font.cbSize = sizeof(font);
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = font_size;
	
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	
	wcscpy(font.FaceName, L"Consolas");

	SetCurrentConsoleFontEx(console_buffer_one, false, &font);
	SetCurrentConsoleFontEx(console_buffer_two, false, &font);
	
	SetConsoleActiveScreenBuffer(console_buffer_one);	// show this buffer
	console_active_buffer = &console_buffer_two;

	// Setting up input
	console_input = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(console_input, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	default_camera.isCentred(false);
	default_camera.possition = Vector2D{ 0, 0 };
	default_camera.camera_size = buffer_size;

	active_camera = &default_camera;
	is_camera_active = false;

	// Module ini
	console_input_buffer = &console_input;
	ConsoleModuleEvent::ini();
}

Console::~Console() {}

void Console::setFontSize(int size) {
	CONSOLE_FONT_INFOEX font;
	GetCurrentConsoleFontEx(console_buffer_one, false, &font);

	font.cbSize = sizeof(font);
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = size;

	SetCurrentConsoleFontEx(console_buffer_one, false, &font);
	SetCurrentConsoleFontEx(console_buffer_two, false, &font);
}

void Console::setTitle(std::wstring title) {
	SetConsoleTitle(title.c_str());
}

void Console::setFontFamily(std::wstring family) {
	CONSOLE_FONT_INFOEX font;
	GetCurrentConsoleFontEx(console_buffer_one, false, &font);
	
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy(font.FaceName, family.c_str());

	SetCurrentConsoleFontEx(console_buffer_one, false, &font);
	SetCurrentConsoleFontEx(console_buffer_two, false, &font);
}

void Console::enableUnicodeEncoding() {
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void Console::clean(HANDLE * output_buffer) {

	if (output_buffer == nullptr)
		output_buffer = console_active_buffer;

	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	DWORD cells_to_write;
	DWORD writen_chars;
	DWORD writen_atributes;
	WORD clean_color = 15;
	COORD home_coorde = { 0, 0 };

	if (!GetConsoleScreenBufferInfo(*console_active_buffer, &buffer_info)) {
		return;
	}

	cells_to_write = buffer_info.dwSize.X * buffer_info.dwSize.Y;

	FillConsoleOutputCharacterW(
		*console_active_buffer,
		L' ',
		cells_to_write,
		home_coorde,
		&writen_chars
	);

	FillConsoleOutputAttribute(
		*console_active_buffer,
		clean_color,
		cells_to_write,
		home_coorde,
		&writen_atributes
	);
}

void Console::display() {
	// Dwar buffer texture
	SMALL_RECT consoleWriteArea = { 0, 0, static_cast<short>(buffer_size.x - 1), static_cast<short>(buffer_size.y - 1) };

	if (buffer_texture.getWide()) { 
		WriteConsoleOutputW(
			*console_active_buffer,
			buffer_texture.marks,
			buffer_size,
			COORD{ 0,0 },
			&consoleWriteArea
		);
		buffer_texture.fill(L' ', 15); 
	}
	else {
		WriteConsoleOutput(
			*console_active_buffer,
			buffer_texture.marks,
			buffer_size,
			COORD{ 0,0 },
			&consoleWriteArea
		);
		buffer_texture.fill(' ', 15);
	}

	// Swaping active screen buffers with unactive one
	if (console_active_buffer == &console_buffer_one) {
		console_active_buffer = &console_buffer_two;
		SetConsoleActiveScreenBuffer(console_buffer_one);
	}
	else {
		console_active_buffer = &console_buffer_one;
		SetConsoleActiveScreenBuffer(console_buffer_two);
	}
}

Vector2D Console::getCursorPossition(HANDLE * handle) {
	if (handle == nullptr)
		handle = console_active_buffer;

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(*handle, &info);

	return info.dwCursorPosition;
}

void Console::setCursorPossition(const Vector2D & possition) {
	SetConsoleCursorPosition(console_buffer_one, possition);
	SetConsoleCursorPosition(console_buffer_two, possition);
}

void Console::showCursor(bool flag) {
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(console_buffer_one, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(console_buffer_one, &cursorInfo);

	GetConsoleCursorInfo(console_buffer_two, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(console_buffer_two, &cursorInfo);
}

void Console::setCameraActive(bool flag) {
	is_camera_active = flag;
}

void Console::setConsoleSize(Vector2D size) {
	console_size = { 0, 0, (short)size.x - 1, (short)size.y - 1 };
	SetConsoleWindowInfo(console_buffer_one, TRUE, &console_size);
	SetConsoleWindowInfo(console_buffer_two, TRUE, &console_size);
}

SMALL_RECT Console::getConsoleSize() {
	return console_size;
}

void Console::setBufferSize(Vector2D size) {
	buffer_size = size;
	SetConsoleScreenBufferSize(console_buffer_one, buffer_size);
	SetConsoleScreenBufferSize(console_buffer_two, buffer_size);
	buffer_texture.setTextureSize(size);
}

Vector2D Console::getBufferSize() {
	return buffer_size;
}

void Console::draw(char z, Vector2D possition) {
	if (!active_camera->isInView(possition)) return;
	possition = possition.relativeTo(active_camera->possition);
	buffer_texture.marks[possition.x + possition.y * buffer_size.x].Char.AsciiChar = z;
}

void Console::draw(wchar_t z, Vector2D possition) {
	if (!active_camera->isInView(possition)) return;
	possition = possition.relativeTo(active_camera->possition);
	buffer_texture.marks[possition.x + possition.y * buffer_size.x].Char.UnicodeChar = z;
}

void Console::setAtribute(WORD at, Vector2D possition) {
	if (!active_camera->isInView(possition)) return;
	possition = possition.relativeTo(active_camera->possition);
	buffer_texture.marks[possition.x + possition.y * buffer_size.x].Attributes = at;
}

void Console::draw(const Mark & mark, Vector2D possition) {
	if (!active_camera->isInView(possition)) return;
	possition = possition.relativeTo(active_camera->possition);
	
	buffer_texture.setCharAt(possition, mark.znak);
	buffer_texture.setAttrAt(possition, mark.color);
}

void Console::draw(const WMark & mark, Vector2D possition) {
	if (!active_camera->isInView(possition)) return;
	possition = possition.relativeTo(active_camera->possition);

	buffer_texture.setCharAt(possition, mark.znak);
	buffer_texture.setAttrAt(possition, mark.color);
}

void Console::draw(const std::string & str, WORD at, Vector2D possition, char xyz) {
	for (auto &i : str) {
		if (!active_camera->isInView(possition)) continue;
		Vector2D pos = possition.relativeTo(active_camera->possition);
		
		buffer_texture.setCharAt(pos, i);
		buffer_texture.setAttrAt(pos, at);

		if(xyz == 'y')
			++possition.y;
		else 
			++possition.x;
	}
}

void Console::draw(const std::wstring & str, WORD at, Vector2D possition, char xyz) {
	for (auto &i : str) {
		if (!active_camera->isInView(possition)) continue;
		Vector2D pos = possition.relativeTo(active_camera->possition);

		buffer_texture.setCharAt(pos, i);
		buffer_texture.setAttrAt(pos, at);

		if (xyz == 'y')
			++possition.y;
		else
			++possition.x;
	}
}

void Console::draw(const BitA<WMark>& img, Vector2D possition, Vector2D start, Vector2D end) {
	Vector2D pos;

	end.x = end.x == 0 ? img.size_x : end.x;
	end.y = end.y == 0 ? img.size_y : end.y;

	for ( ; start.y < end.y; ++start.y) {
		for (int x = start.x; x < end.x; ++x) {
			pos.x = possition.x + x;
			pos.y = possition.y + start.y;

			if (!active_camera->isInView(pos)) continue;

			pos = pos.relativeTo(active_camera->possition);
			buffer_texture.setCharAt(pos, img.marks[start.y][x].znak);
			buffer_texture.setAttrAt(pos, img.marks[start.y][x].color);
		}
	}
}

void Console::draw(const BitA<Mark>& img, Vector2D possition, Vector2D start, Vector2D end) {
	Vector2D pos;

	end.x = end.x == 0 ? img.size_x : end.x;
	end.y = end.y == 0 ? img.size_y : end.y;

	for (; start.y < end.y; ++start.y) {
		for (int x = start.x; x < end.x; ++x) {
			pos.x = possition.x + x;
			pos.y = possition.y + start.y;

			if (!active_camera->isInView(pos)) continue;

			pos = pos.relativeTo(active_camera->possition);
			buffer_texture.setCharAt(pos, img.marks[start.y][x].znak);
			buffer_texture.setAttrAt(pos, img.marks[start.y][x].color);
		}
	}
}