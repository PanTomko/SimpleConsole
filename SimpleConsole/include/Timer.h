#pragma once
#define DllExport __declspec( dllexport )
#include <chrono>

namespace sc  
{
	/*!
	 * Timer is used to masure time pass. Intended use for physic and event hadling.
	 */
	class DllExport Timer {
	public:
		bool one_shot;

		/// Starts to cout time
		void start();

		/// Stops to count time
		void stop();

		/// Reset timer to 0
		void reset();

		/// returns duration of total time that passed since start/reset
		std::chrono::steady_clock::duration getElepasedTime();

		/// returns duration of stored time ( time that was only counted if timer was not stoped or reseted )
		std::chrono::steady_clock::duration getStoredTime();

		Timer();
		~Timer();

	private:
		std::chrono::steady_clock::duration stored_time;

		std::chrono::steady_clock::time_point time_start;
		std::chrono::steady_clock::time_point time_end;
	};
}