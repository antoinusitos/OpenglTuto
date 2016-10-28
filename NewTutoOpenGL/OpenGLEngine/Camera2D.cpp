#include "Camera2D.h"

namespace OpenGLEngine
{
	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		scale(1.0f),
		orthoMatrix(1.0f),
		needsMatrixUpdate(true),
		screenWidth(500),
		screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int theScreenWidth, int theScreenHeight)
	{
		screenWidth = theScreenWidth;
		screenHeight = theScreenHeight;
		orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	}

	void Camera2D::Update()
	{
		if (needsMatrixUpdate)
		{
			glm::vec3 translate(-position.x, -position.y, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);
			glm::vec3 matrixScale(scale, scale, 0.0f);
			cameraMatrix = glm::scale(cameraMatrix, matrixScale);
			needsMatrixUpdate = false;
		}
	}
}