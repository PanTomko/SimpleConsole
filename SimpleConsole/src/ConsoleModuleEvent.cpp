#include "ConsoleModuleEvent.h"

#include "Keyboard.h"
#include "Mouse.h"

#include <windows.h>
#include <bitset>

using namespace sc;

ConsoleModuleEvent::ConsoleModuleEvent() {
	non_valid_codes = { 
		Key::Alt, 
		Key::Shift, 
		Key::Ctrl, 
		Key::Backspace,					 
		Key::CapsLock, 
		Key::Clear, 
		Key::Delete, 
		Key::Enter,		 
		Key::DownArrow, 
		Key::RightArrow, 
		Key::LeftArrow, 
		Key::UpArrow,
		Key::Escape, 
		Key::Help, 
		Key::Home, 
		Key::Tab, 
		Key::Insert,
		Key::PrintSreen, 
		Key::PageDown, 
		Key::PageUP 
	};
}

ConsoleModuleEvent::~ConsoleModuleEvent(){}

void ConsoleModuleEvent::readInputEvents() {
	while (true) {
		ReadConsoleInputW(
			*console_input_buffer,
			input_buffer,
			254,
			&input_count);

		mutex_evets_buffer.lock();

		for (unsigned int i = 0; i < input_count; i++) {
			Event _event;

			switch (input_buffer[i].EventType) {
				case KEY_EVENT: processKeyboardEvent(input_buffer[i]); break;
				case MOUSE_EVENT: processMouseEvent(input_buffer[i]); break;
			}
		}

		mutex_evets_buffer.unlock();
	}
}

void ConsoleModuleEvent::processKeyboardEvent(const INPUT_RECORD & record) {
	Event _event;

	_event.event_type = Event::Type::Keyboard;
	_event.keyboardEvent.key = static_cast<Key>(record.Event.KeyEvent.wVirtualKeyCode);
	_event.keyboardEvent.repeatCount = record.Event.KeyEvent.wRepeatCount;

	wchar_t tmpWCT = record.Event.KeyEvent.uChar.UnicodeChar;
	_event.keyboardEvent.unicode = isValidCharacter(_event.keyboardEvent.key) ? tmpWCT : L'\0';

	if (Keyboard::getInstance()->keys.find(_event.keyboardEvent.key) == Keyboard::getInstance()->keys.end()) {
		Keyboard::getInstance()->keys[_event.keyboardEvent.key] = 0b000u; // Key not found so make one
	}

	if (record.Event.KeyEvent.bKeyDown) {
		if (!bool(Keyboard::getInstance()->keys[_event.keyboardEvent.key] & 0b001)) {
			Keyboard::getInstance()->keys[_event.keyboardEvent.key] |= 0b101;
		}
	}
	else {
		Keyboard::getInstance()->keys[_event.keyboardEvent.key] &= ~(1UL << 0);
		Keyboard::getInstance()->keys[_event.keyboardEvent.key] |= 0b010;
	}

	_event.keyboardEvent.keyState = Keyboard::getInstance()->keys[_event.keyboardEvent.key];
	evets_buffer.push(_event);

	if (Keyboard::getInstance()->keys[_event.keyboardEvent.key] & 0b010) {
		Keyboard::getInstance()->keys[_event.keyboardEvent.key] &= ~(1UL << 1);
	}

	if (Keyboard::getInstance()->keys[_event.keyboardEvent.key] & 0b100) {
		Keyboard::getInstance()->keys[_event.keyboardEvent.key] &= ~(1UL << 2);
	}
}

void sc::ConsoleModuleEvent::processMouseEvent(const INPUT_RECORD & record) {
	Event _event;

	_event.event_type = Event::Type::Mouse;
	_event.mouseEvent.position = record.Event.MouseEvent.dwMousePosition;
	Mouse::getInstance()->position = record.Event.MouseEvent.dwMousePosition;
	_event.mouseEvent.key = MouseKeys::Null;

	std::bitset<3>set = record.Event.MouseEvent.dwButtonState;

	for (auto & j : Mouse::getInstance()->keys) {

		std::bitset<3>testedKey = static_cast<unsigned int>(j.first);
		std::bitset<3>testedKeyStatus = static_cast<unsigned int>(j.second);

		if (set.to_ulong() & testedKey.to_ulong()) {
			if (testedKeyStatus[0] == 0) {
				testedKeyStatus[2] = 1;

				_event.mouseEvent.keyState = static_cast<unsigned char>(testedKeyStatus.to_ulong());
				_event.mouseEvent.key = j.first;
				j.second = testedKeyStatus.to_ulong();
				evets_buffer.push(_event);

				testedKeyStatus[2] = 0;
			}

			testedKeyStatus[0] = 1;

		}
		else {
			if (testedKeyStatus[0] == 1) {
				testedKeyStatus[1] = 1;

				_event.mouseEvent.keyState = static_cast<unsigned char>(testedKeyStatus.to_ulong());
				_event.mouseEvent.key = j.first;
				j.second = testedKeyStatus.to_ulong();
				evets_buffer.push(_event);

				testedKeyStatus[1] = 0;
			}
			testedKeyStatus[0] = 0;
		}

		j.second = testedKeyStatus.to_ulong(); // save mouse status in Mouse::instance
	}
}

void sc::ConsoleModuleEvent::ini() {
	thread_input = std::thread(&sc::ConsoleModuleEvent::readInputEvents, this);
}

bool ConsoleModuleEvent::poolEvent(Event & _event) {
	std::lock_guard<std::mutex>lock(mutex_evets_buffer);

	if (!evets_buffer.empty()){
		_event = evets_buffer.front();
		evets_buffer.pop();
		return true;
	}

	return false;
}

bool ConsoleModuleEvent::isValidCharacter(const Key & key) {
	for (auto & i : non_valid_codes) {
		if (key == i) {
			return false;
		}
	}
	return true;
}