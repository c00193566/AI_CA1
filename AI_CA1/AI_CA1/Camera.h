#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class Camera
{
private:
	View CameraView;
	int Width;
	int Height;

public:
	Camera();
	~Camera();
	void Update(Vector2f);
	View & getView() { return CameraView; };
	bool Visible(Vector2f vec);
};