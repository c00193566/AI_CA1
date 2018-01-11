#include "Camera.h"

Camera::Camera()
{
	Width = 720;
	Height = 405;
	CameraView = View(FloatRect(0, 0, Width, Height));
	//CameraView = View(FloatRect(0, 0, 1280, 720));
}

Camera::~Camera()
{

}

void Camera::Update(Vector2f PlayerPosition)
{
	CameraView.setCenter(PlayerPosition.x, PlayerPosition.y);
}