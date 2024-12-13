#pragma once

class InputManager;
class CameraEffect;
class Transform;

enum class CAMERA_MODE
{
	DEFAULT,
	MIDNIGHT,
	MOUSE,
	MAINSCENE,
};


/// <summary>
/// ī�޶� ����ϴ� �Ŵ���
/// 
/// 2023.07.07 23:04 gitae
/// 2023.08.10 ����
/// </summary>
class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager);
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);


public:
	void SetTargetObject(GameObject* _target) const;

	/// ��ũ�� ��ǥ�迡�� ���� ��ǥ��� ��ȯ���ش�.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

	// ��ũ�� ��ǥ�迡�� ī�޶� ��ǥ��� ��ȯ
	Vector2 ScreenToCamera(const Vector2& _screen) const;
	
	// ������ǥ���� ī�޶� ��ǥ��� ��ȯ
	Vector2 WorldToCamera(const Vector2& _world) const;
	
	// ���� ��ǥ���� ��ũ�� ��ǥ��� ��ȯ 
	Vector2 WorldToScreen(const Vector2& _world) const;
	
	// ī�޶� ��ǥ�迡�� ��ũ�� ��ǥ�� ��ȯ
	Vector2 CameraToScreen(const Vector2& _camera) const;
	
	// ī�޶� ��ǥ�迡�� ���� ��ǥ�� ��ȯ 
	Vector2 CameraToWorld(const Vector2& _camera) const;
	
	void ResetCamera()const;

	Vector2 GetScreenSize()const { return m_screenSize; }
	
	void SetCameraMode(CAMERA_MODE _mode) const { m_mode = _mode; }
	void SetGravityMode(int _i) const;
	D2DCamera* GetCamera() const { return m_camera; } 
	Vector2 GetDxdy() const { return m_dxdy; }
	void SetCameraBorder(float _top, float _bottom, float _left, float _right) const;
	void SetCameraPos(Vector2 _pos = Vector2(0, 0)) const;
	CameraEffect* GetCurrentCameraEffect()const { return m_effectList.front().get(); }
	void SetOffset(Vector2 _offset) const { m_offset = _offset; }

public:
	/// ī�޶� ȿ�� ��� 
	void FadeInCamera(float _duration, bool _isAffectUI,ColorF color = ColorF::Black) const;
	void FadeOutCamera(float _duration, bool _isAffectUI ,ColorF color = ColorF::Black) const;
	void LetterboxCamera(float _heigt, float _speed)const;
	void ClearCameraEffect()const;

private:
	void MouseToCameraMove(float _deltaTime);
	void TargetTracking(float _deltaTime);
	void MidnightMove(float _deltaTime);
	void MainSceneMode(float _dt);

private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
	InputManager* m_inputManager;
	
	float m_moveSpeed;// ī�޶� �̵��ӵ�
	float m_trackingSpeed; // �����ӵ� 
	Vector2 m_tarckDistance;
	float m_prevDistance; // ���� �Ÿ� ����

	mutable GameObject* m_targetObject;
	mutable Transform* m_targetTransform;
	mutable list<std::unique_ptr<CameraEffect>> m_effectList;

	mutable CAMERA_MODE m_mode;

	//�̵峪�� ���� ���� ---------------------------------
	bool m_isTracking;	
	const float m_speed = 2.f;
	const float m_HeightBorder = 80.f;
	const float m_widthBorder = 150.f;
	mutable Vector2 m_offset;
	Vector2 m_currentOffset;
	mutable bool m_isChangingOffset;

	mutable float m_topBorder;
	mutable float m_bottomBorder;
	mutable float m_leftBorder;
	mutable float m_rightBorder;

	bool m_topTouch;

	float dist; ///�ӽú����Դϴٿ� ����볡���� ������ ����!!!!

	//---------------------------------

	Vector2 m_dxdy;
	Vector2 m_prevPosition;
};

