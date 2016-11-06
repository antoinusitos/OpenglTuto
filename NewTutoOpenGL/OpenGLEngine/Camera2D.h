#ifndef DEF_CAMERA2D
#define DEF_CAMERA2D

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace OpenGLEngine
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int theScreenWidth, int theScreenHeight);

		void Update();

		glm::vec2 ConvertScreenToWorld(glm::vec2 screenPos);

		// setters
		void SetPosition(const glm::vec2& newPosition) 
		{
			position = newPosition; needsMatrixUpdate = true;
		}
		void SetScale(float newScale) 
		{
			scale = newScale;  needsMatrixUpdate = true;
		}

		// getters
		glm::vec2 GetPosition() { return position; }
		float GetScale() { return scale; }
		glm::mat4 GetCameraMatrix() { return cameraMatrix; }

	private:
		int screenWidth;
		int screenHeight;
		bool needsMatrixUpdate;
		float scale;
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;
	};
}
#endif