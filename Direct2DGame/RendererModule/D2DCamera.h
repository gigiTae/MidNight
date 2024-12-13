#pragma once

// 2023.7.5 21:58 gitae
// D2D���� ī�޶� ����Ѵ�.
class D2DCamera
{
public:
	D2DCamera();
	~D2DCamera();
	// ī�޶� ȸ��
	void RotateCamera(float _radian);
	
	// ī�޶� �̵�
	void MoveCamera(Vector2 _distance);

	void SetPosition(Vector2 _position);
	
	// ī�޶� Ȯ�� ���
	void ZoomCamera(Vector2 _scale);

	// ī�޶� �⺻ ��ķ� �ʱ�ȭ�Ѵ�. 
	void ResetCamera(Vector2 _screenSize);

	const D2D1_MATRIX_3X2_F& GetCameraMatrix() { return m_cameraMatrix; }

	Vector2 GetPosition();
	const Vector2& GetScale() { return m_scale; }
	float GetRotation() { return m_rotation; }
	
	
public:
	Vector2 CameraToWorld(const Vector2& _camera);
	Vector2 CameraToScreen(const Vector2& _camera);
	Vector2 WorldToCamera(const Vector2& _world);
	Vector2 WorldtoScreen(const Vector2& _world);
	Vector2 ScreenToWorld(const Vector2& _screen);
	Vector2 ScreenToCamera(const Vector2& _screen);

private:
	void CalculateMatrix();

private:
	float m_rotation; // ī�޶� ȸ��
	Vector2 m_scale; // ī�޶� ����
	Vector2 m_position; // ī�޶� ��ǥ

	Vector2 m_screenSize; // ��ũ�� ������

	D2D1_MATRIX_3X2_F m_cameraMatrix;
};

