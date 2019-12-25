#include <iostream>

#include "Console.h"

using namespace std;
using namespace sc;

int main() {
	sc::Console window{ sc::Vector2D(60, 30), 20 };

	window.active_camera->camera_size = window.getBufferSize();
	window.setFontFamily(L"MS Gothic");

	window.buffer_texture.setWide(true);
	
	COORD max_size = window.getLargestConsoleSize();

	while (true)
	{


		window.display();
		
		std::string s = "Max console size : X = " + std::to_string(max_size.X) + " | Y = " +
			std::to_string(max_size.Y);
		std::string s2 = "x size : X = " + std::to_string(window.getConsoleSize().Right) + " | Y = " +
			std::to_string(window.getConsoleSize().Bottom);
		//std::string s3 = "Buffor size : X = " + std::to_string(x2.x ) + " | Y = " +
		//	std::to_string(x2.y);

		window.draw(s, 15, sc::Vector2D{ 0,0 });
		window.draw(s2, 15, sc::Vector2D{ 0,1 });
		//window.draw(s3, 15, sc::Vector2D{ 0,2 });
		window.draw(s, 15, sc::Vector2D{ 0,window.getConsoleSize().Bottom });
		
		window.clean();
	}
	

	cin.get();
	return 0;
}