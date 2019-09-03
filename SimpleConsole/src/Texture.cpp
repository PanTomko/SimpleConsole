#include "Texture.h"

using namespace sc;

Texture::Texture() {
	is_wide = false;
	marks = nullptr;
}

Texture::~Texture(){
	if (marks != nullptr) delete[]marks;
}

void Texture::setWide(bool flag) {
	is_wide = flag;
}

bool Texture::getWide() {
	return is_wide;
}

void Texture::setTextureSize(const Vector2D & size) {
	texture_size = size;
	if (marks != nullptr) delete[]marks;
	marks = new CHAR_INFO[size.x * size.y];
}

void Texture::fill(char c, WORD at) {
	int max = texture_size.x * texture_size.y;
	for (int i = 0; i < max; i++) {
		marks[i].Char.AsciiChar = c;
		marks[i].Attributes = at;
	}
}

void Texture::fill(wchar_t c, WORD at) {
	int max = texture_size.x * texture_size.y;
	for (int i = 0; i < max; i++) {
		marks[i].Char.UnicodeChar = c;
		marks[i].Attributes = at;
	}
}

void sc::Texture::setCharAt(const Vector2D & posssition, const char & c) {
	if( c != 0)
		marks[posssition.x + posssition.y * texture_size.x].Char.AsciiChar = c;
}

void sc::Texture::setCharAt(const Vector2D & posssition, const wchar_t & c) {
	if (c != 0)
		marks[posssition.x + posssition.y * texture_size.x].Char.UnicodeChar = c;
}

void sc::Texture::setAttrAt(const Vector2D & posssition, const WORD & attribute) {
	if (attribute != 0)
		marks[posssition.x + posssition.y * texture_size.x].Attributes = attribute;
}
