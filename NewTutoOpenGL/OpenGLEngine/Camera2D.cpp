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
	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenPos)
	{
		// make it so that the 0 is at the center
		screenPos -= glm::vec2(screenWidth / 2, screenHeight / 2);
		// scale the coordinates
		screenPos /= scale;
		// traslate with the camera position;
		screenPos += position;

		return screenPos;
	}
}