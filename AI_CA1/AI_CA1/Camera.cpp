#include "Camera.h"

Camera::Camera()
{
	Width = 720;
	Height = 405;

	//CameraView = View(FloatRect(0, 0, Width, Height));
	CameraView = View(FloatRect(0, 0, 2000, 1000));
}

Camera::~Camera()
{

}

void Camera::Update(Vector2f PlayerPosition)
{
	CameraView.setCenter(PlayerPosition.x, PlayerPosition.y);
}

bool Camera::Visible(Vector2f vec)
{
	Vector2f Left;
	Vector2f Right;

	Left.x = CameraView.getCenter().x - (Width / 2);
	Left.y = CameraView.getCenter().y - (Height / 2);

	Right.x = CameraView.getCenter().x + (Width / 2);
	Right.y = CameraView.getCenter().y + (Height / 2);

	if (vec.x <= Right.x && vec.x >= Left.x)
	{
		if (vec.y <= Right.y && vec.y >= Left.y)
		{
			return false;
		}

		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}