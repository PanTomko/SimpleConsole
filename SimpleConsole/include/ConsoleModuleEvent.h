#pragma once
#define DllExport __declspec( dllexport )
#include "Event.h"

#include <windows.h>

#include <thread>
#include <mutex>
#include <queue>

namespace sc
{
	class DllExport ConsoleModuleEvent {
	public:
		/// fills Event data if there was any to pool form que, else it returns false.
		bool poolEvent(Event & _event);

		bool isValidCharacter(const Key & key);
		
		std::thread thread_input ;
		void readInputEvents();

		ConsoleModuleEvent();
		~ConsoleModuleEvent();
	private:
		std::queue<Event>evets_buffer;
		std::mutex mutex_evets_buffer;
		
		HANDLE * console_input_buffer;

		DWORD input_count;
		INPUT_RECORD input_buffer[254];
		std::vector<Key>non_valid_codes;

		void processKeyboardEvent( const INPUT_RECORD & record );
		void processMouseEvent( const INPUT_RECORD & record );

		void ini();

		friend class Console;
	};
}