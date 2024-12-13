#pragma once

struct KeyInfo
{
	KEY_STATE state; // Ű�� ���°�
	bool      prevPush;  // ���� �����ӿ��� ���ȴ��� ����
};

class CameraManager; 

/// <summary>
/// �Է��� ������ش�.
/// Ű����, ���콺���� �Էµ����͸� �����Ӹ��� �����Ͽ�
/// �����ϰ� ����Ѵ�.
/// 
/// </summary>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void Initalize(HWND _main, CameraManager* _cameraManager);
	void Update();
	void Finalize();

	Vector2 GetWorldMousePosition() const { return m_worldMousePosition; }
	Vector2 GetScreendMousePosition() const { return m_screenMousePosition; }
	Vector2 GetCameraMousePosition() const { return m_cameraMousePosition; }

	KEY_STATE GetKeyState(KEY _key)const { return m_keyInfo[static_cast<int>(_key)].state; }
	bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;
private:
	CameraManager* m_cameraManager;

	// ���� ������ �ڵ�
	HWND m_hwnd;

	// �̹� ������ ���콺 ��ġ
	Vector2 m_worldMousePosition;
	Vector2 m_cameraMousePosition;
	Vector2 m_screenMousePosition;

	// Ű �������� ���� �迭
	vector<KeyInfo> m_keyInfo;

	// KEY ���� ����Ű���� ��Ī�����ִ� �迭
	const int m_matchVK[static_cast<int>(KEY::LAST)];
};

