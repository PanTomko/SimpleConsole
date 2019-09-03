#include "Camera.h"

using namespace sc;

Camera::Camera() : centred{false} {}

Camera::~Camera(){}

void Camera::isCentred(bool flag) {
	centred = flag;
}

bool Camera::isInView(const Vector2D & vector) {

	if (vector.y < possition.y ||
		vector.y > possition.y + camera_size.y ||
		vector.x < possition.x ||
		vector.x > possition.x + camera_size.x)
		return false;
	else
		return true;
}
