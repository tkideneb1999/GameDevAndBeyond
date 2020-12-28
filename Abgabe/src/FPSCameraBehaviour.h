#pragma once

#include "InputHandler.h"
#include "Rendering/Camera.h"
#include "Rendering/Transform.h"

class FPSCameraBehaviour
{
public:
	FPSCameraBehaviour();
	Transform transform;
	Camera camera;

	float movementSpeed;
	float rotationSpeed;
private:
	void CameraMove(double xPos, double yPos);
	void ActivateCamera(InputHandling::InputMouseButtonEnum mouseButton, InputHandling::InputPressEnum, int mods);
};
