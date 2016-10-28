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
			// camera translation
			glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);

			// camera scale
			glm::vec3 matrixScale(scale, scale, 0.0f);
			// scale the matrix identity and apply it to our current scale
			cameraMatrix = glm::scale(glm::mat4(1.0f), matrixScale) * cameraMatrix;
			
			needsMatrixUpdate = false;
		}
	}
}