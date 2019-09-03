#include "Mark.h"

using namespace sc;

Mark::Mark() {}
Mark::~Mark() {}
Mark::Mark(char znak, unsigned short color) {
	this->znak = znak;
	this->color = color;
}

WMark::WMark() {}
WMark::~WMark() {}
WMark::WMark(wchar_t znak, unsigned short color) {
	this->znak = znak;
	this->color = color;
}