#include "GameProcessPCH.h"
#include "InputManager.h"
#include "CameraManager.h"

InputManager::InputManager()
	:m_matchVK{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	'Q','W','E','R','T','Y','U','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',

	VK_MENU, // ALT,
	VK_CONTROL, // CTRL,
	VK_LSHIFT, // LSHIFT,
	VK_SPACE, // SPACE,
	VK_RETURN, // ENTER,
	VK_ESCAPE, // ESC,
	VK_TAB, //TAB

	VK_LBUTTON, // LBTN
	VK_RBUTTON, // RBTN
	
	VK_F1, // F1
	VK_F2, // F2
	VK_F3, // F3
	VK_F4, // F4
	VK_F5, // F5
	}
	, m_keyInfo{}
	,m_hwnd(nullptr)
	,m_worldMousePosition{}
	,m_cameraManager(nullptr)
{
}

InputManager::~InputManager()
{
}

void InputManager::Initalize(HWND _main, CameraManager* _cameraManager)
{
	m_hwnd = _main;
	m_cameraManager = _cameraManager;

	for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
	{
		m_keyInfo.push_back(KeyInfo{ KEY_STATE::NONE,false });
	}
}

void InputManager::Update()
{ 
	HWND hWnd = GetFocus();

	// ���� ��Ŀ�����϶�
	if (nullptr != hWnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (GetAsyncKeyState(m_matchVK[i]) & 0x8000)
			{
				if (m_keyInfo[i].prevPush)
				{
					m_keyInfo[i].state = KEY_STATE::HOLD;
				}
				else
				{
					m_keyInfo[i].state = KEY_STATE::TAP;
				}
				m_keyInfo[i].prevPush = true;
			}
			else
			{
				if (m_keyInfo[i].prevPush)
				{
					m_keyInfo[i].state = KEY_STATE::AWAY;
				}
				else
				{
					m_keyInfo[i].state = KEY_STATE::NONE;
				}
				m_keyInfo[i].prevPush = false;
			}
		}


		// Mouse ��ġ ���
		POINT mousePosition{};
		GetCursorPos(&mousePosition);

		// ��ũ�� ��ǥ���� ���콺 ��ġ
		ScreenToClient(m_hwnd, &mousePosition);
		m_screenMousePosition = Vector2(static_cast<float>(mousePosition.x)
			, static_cast<float>(mousePosition.y));

		// ���� ��ǥ��� ��ȯ
		m_cameraMousePosition = m_cameraManager->ScreenToCamera(m_screenMousePosition);

		m_worldMousePosition = m_cameraManager->CameraToWorld(m_cameraMousePosition);
	}
	// ��Ŀ�������Ǿ� ����ó�� ����
	else
	{ 
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			m_keyInfo[i].prevPush = false;
			if (KEY_STATE::TAP == m_keyInfo[i].state || KEY_STATE::HOLD == m_keyInfo[i].state)
			{
				m_keyInfo[i].state = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_keyInfo[i].state)
			{
				m_keyInfo[i].state = KEY_STATE::NONE;
			}

		}
	}
}



void InputManager::Finalize()
{
	m_keyInfo.clear();
}

bool InputManager::IsKeyState(const KEY& _key, const KEY_STATE& _state) const 
{
	if (_state == GetKeyState(_key))
	{
		return true;
	}

	return false;
}
