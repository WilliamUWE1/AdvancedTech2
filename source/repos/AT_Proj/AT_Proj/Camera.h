#pragma once

#include <cstdint>
#include <DirectXMath.h>

using namespace DirectX;
class Camera
{
public:

	Camera() = default;
	Camera(const Camera& camera) = delete;
	Camera& operator=(const Camera& camera) = delete;
	~Camera() = default;

	XMMATRIX GetView() const noexcept;
	void SetView(XMMATRIX view);
	void UpdateCamera();
	void SetYaw(float new_yaw);
	void SetPitch(float new_pitch);

private:
	
	XMVECTOR camTarget;
	XMVECTOR camPosition;
	XMVECTOR camUp = {0.0f, 1.0f, 0.0f};
	XMMATRIX camView;

	XMVECTOR defaultForward{ 0.0f, 0.0f, 1.0f };
	XMVECTOR defaultRight = { 1.0f, 0.0f, 0.0f };
	XMVECTOR camForward = { 0.0f, 0.0f, 1.0f };
	XMVECTOR camRight = { 1.0f, 0.0f, 0.0f };
	

	XMMATRIX camRotationMatrix;	

	float moveLeftRight = 0.0f;
	float moveForwardBack = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;
};