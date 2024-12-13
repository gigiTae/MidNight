#pragma once

enum class KEY_STATE
{
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,
	F1, F2, F3, F4, F5,

	LAST, //enum�� ��
};


struct KeyInfo
{
	KEY_STATE state; // Ű�� ���°�
	bool      prevPush;  // ���� �����ӿ��� ���ȴ��� ����
};

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

	void Initalize(HWND _main);
	void Update();
	void Finalize();

	KEY_STATE GetKeyState(KEY _key)const { return m_keyInfo[static_cast<int>(_key)].state; }
	bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;
	ImVec2 GetMousePosition() const { return m_mousePosition; }
private:

	// ���� ������ �ڵ�
	HWND m_hwnd;

	// Ű �������� ���� �迭
	vector<KeyInfo> m_keyInfo;

	// KEY ���� ����Ű���� ��Ī�����ִ� �迭
	const int m_matchVK[static_cast<int>(KEY::LAST)];

	ImVec2 m_mousePosition;
};

