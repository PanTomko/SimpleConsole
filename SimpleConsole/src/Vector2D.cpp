#include "Vector2D.h"
#include <iostream>
#include <utility>

using namespace sc;

Vector2D::Vector2D() {}

Vector2D::Vector2D(const Vector2D & vec) {
	x = vec.x;
	y = vec.y;
}

Vector2D::Vector2D(Vector2D && vec) {
	x = (std::exchange(vec.x, 0));
	y = (std::exchange(vec.y, 0));
}

Vector2D::Vector2D(const COORD & cor) {
	x = cor.X;
	y = cor.Y;
}

Vector2D Vector2D::operator=(const Vector2D & vec) {
	if (&vec != this)
	{
		this->x = vec.x;
		this->y = vec.y;
	}
	
	return *this;
}

Vector2D Vector2D::operator=(const COORD & cor)
{
	this->x = static_cast<int>(cor.X);
	this->y = static_cast<int>(cor.Y);

	return *this;
}

Vector2D Vector2D::operator+(Vector2D const & vec) {
	return { vec.x + x, vec.y + y };
}

Vector2D::Vector2D(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2D::~Vector2D() {}

Vector2D sc::Vector2D::relativeTo(const Vector2D & vector) {
	return Vector2D(x - vector.x, y - vector.y);
}

Vector2D::operator COORD&() const {
	COORD cor;
	cor.X = static_cast<short>(x);
	cor.Y = static_cast<short>(y);
	return cor;
}




