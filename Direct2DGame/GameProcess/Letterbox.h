#pragma once

#include "CameraEffect.h"

/// <summary>
/// ���͹ڽ� ȿ��
/// </summary>
class Letterbox :
    public CameraEffect
{
public:
    Letterbox(bool _affectUI, const CameraManager* _cameraManager);
    ~Letterbox();

public:
	void Render(D2DRenderer* _d2DRenderer) override;
	void Update(float _deltaTime) override;
	void Close() { m_isDone = true; }
	void SetUp(float _maxHeight, float _speed, Vector2 _screenSize);
private:
	float m_isDone; // ���͹ڽ� ȿ���� ��������
	float m_maxHeight; // ���͹ڽ� �ִ� ����
	float m_currentHeight; // ���͹ڽ� ������� 
	float m_speed; // ���͹ڽ� �ö󰡴� �ӵ�
	Vector2 m_screenSize;
};

