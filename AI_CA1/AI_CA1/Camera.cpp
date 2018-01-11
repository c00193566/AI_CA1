#include "Camera.h"

Camera::Camera()
{
	//CameraView = View(FloatRect(0, 0, 1280, 720));
	CameraView = View(FloatRect(0, 0, 2000, 1000));
}

Camera::~Camera()
{

}

void Camera::Update(Vector2f PlayerPosition)
{
	CameraView.setCenter(PlayerPosition.x, PlayerPosition.y);
}