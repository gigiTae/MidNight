#include "GameProcessPCH.h"
#include "PopupWindow.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MouseCursor.h"

PopupWindow::PopupWindow()
	:Component(CALL_ORDER::UI,typeid(this).name())
	,m_isActive(false), m_cursor(nullptr)
{

}

PopupWindow::~PopupWindow()
{

}

Component* PopupWindow::Clone()
{
	// �˾�â�� �������� �ʴ´�.
	assert(!L" �˾�â�� �������� �ʽ��ϴ�.");

	return nullptr;
}

void PopupWindow::Render(D2DRenderer* _d2DRenderer)
{
	if (IsActive())
	{
		_d2DRenderer->DrawBitmap(L"SpotLightBase", Vector2::Zero, 0.f, 0.5f);
		_d2DRenderer->DrawBitmap(L"Popup", Vector2(-570.f,400.f));
	}
}

void PopupWindow::Start()
{
	// �ڽ� ������Ʈ���� ��Ȱ��ȭ
	auto& children = GetComponent<Transform>()->GetChildren();

	for (auto& child : children)
	{
		child->SetActive(false);
	}

	//���콺 Ŀ�� ������Ʈ�� �����´�.
	const vector<GameObject*>& objs = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::MOUSE);
	m_cursor = objs[0]->GetComponent<MouseCursor>();
}

void PopupWindow::Update(float _deltaTime)
{
	const InputManager* input = GetInputManager();
		
	
	if (input->IsKeyState(KEY::ESC, KEY_STATE::TAP))
	{
		m_isActive = !m_isActive;
	}

	const SceneManager* scneneManager = GetSceneManager();
	auto& children = GetComponent<Transform>()->GetChildren();

	if (IsActive())
	{
		//���콺 Ŀ���� ���δ�
		m_cursor->SetActive(true);
		
		scneneManager->SetPause(true);

		for (auto& child : children)
		{
			child->SetActive(true);
		}
	}
	else
	{
		//���콺 Ŀ���� �����
		scneneManager->SetPause(false);
		m_cursor->SetActive(false);

		for (auto& child : children)
		{
			child->SetActive(false);
		}
	}
}

void PopupWindow::SetActive(bool _isActive)
{
	m_isActive = _isActive;

	const SceneManager* scneneManager = GetSceneManager();
	auto& children = GetComponent<Transform>()->GetChildren();

	if (m_isActive)
	{
		scneneManager->SetPause(true);

		for (auto& child : children)
		{
			child->SetActive(true);
		}
	}
	else
	{
		scneneManager->SetPause(false);

		for (auto& child : children)
		{
			child->SetActive(false);
		}
	}
}
