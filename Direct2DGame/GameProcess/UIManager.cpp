#include "GameProcessPCH.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ManagerSet.h"
#include "InputManager.h"
#include "Component.h"
#include "GameObject.h"
#include "MouseEvent.h"

UIManager::UIManager()
	:m_sceneManager(nullptr)
	,m_focusedUI(nullptr)
	,m_managerSet(nullptr)
{}

UIManager::~UIManager()
{

}
void UIManager::Initalize(SceneManager* _sceneManager, ManagerSet* _managerSet)
{
	m_sceneManager = _sceneManager;
	m_managerSet = _managerSet;
}

void UIManager::Update()
{
	/// ���� ��Ŀ�� ���� UI Ȯ��
	m_focusedUI = GetFocusedUI();

	// ���� ��Ŀ�� ���� UI�� ���� ���
	if (!m_focusedUI)
		return;

	const InputManager* input = m_managerSet->GetInputManager();

	/// �θ������Ʈ�� �ڽ��߿� ������  ��Ŀ���� UI
	GameObject* targetUI = GetTargetedUI(m_focusedUI);

	if (targetUI == nullptr)
		return;

	KEY_STATE LBtnState = input->GetKeyState(KEY::LMOUSE);
	MouseEvent* ui = targetUI->GetComponent<MouseEvent>();
	assert(ui);

	if (LBtnState == KEY_STATE::TAP)
	{
		targetUI->OnMouseDown();
		ui->SetLBtnDown(true);
	}
	else if (LBtnState == KEY_STATE::AWAY)
	{
		targetUI->OnMouseUp();

		if (ui->IsLBtnDown())
		{
			targetUI->OnMouseClicked();
		}

		ui->SetLBtnDown(false);
	}
}

void UIManager::Finalize()
{
	
}

void UIManager::SetFocusedUI(GameObject* _object) const
{
	if (m_focusedUI == _object || nullptr == _object)
	{
		m_focusedUI = _object;
		return;
	}

	// TODO ó���ؾ��� 
	// ��Ŀ���� ������Ʈ�� �迭�� ���������� ������ 
	m_focusedUI = _object;
	Scene* currentScene = m_sceneManager->GetCurrentScene();
}

GameObject* UIManager::GetFocusedUI()
{
	const InputManager* input = m_managerSet->GetInputManager();
	
	// LMouse �Է��� ������ ��Ŀ������ UI�� �����Ѵ�.
	if (!input->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		return m_focusedUI;
	}

	// ���������ӿ� ��Ŀ�� ���� UI
	GameObject* focusedUI = m_focusedUI;

	// ���� ��Ŀ������ UI ã��
	Scene* scene = m_sceneManager->GetCurrentScene();
	
	/// BAKC_UI�� FRONT_UI���� �׻� �ڿ� ���̾� �׷����� �Ѵ�.
	vector<GameObject*>& backUIGroup = scene->GetUIGroupObject(OBJECT_TYPE::BACK_UI);
	
	auto targetBack = backUIGroup.end();

	for (auto iter = backUIGroup.begin(); iter != backUIGroup.end(); ++iter)
	{
		MouseEvent* ui = (*iter)->GetComponent<MouseEvent>();

		
		if (ui == nullptr)
			continue;

		if (ui->IsMouseOn())
		{
			targetBack = iter;
		}
	}

	/// FRONT_UI�� �׻� �տ� �׷����� ������Ʈ Ÿ���̴�.
	vector<GameObject*>& frontUIGroup = scene->GetUIGroupObject(OBJECT_TYPE::FRONT_UI);

	auto targetFront = frontUIGroup.end();

	for (auto iter = frontUIGroup.begin(); iter != frontUIGroup.end(); ++iter)
	{
		MouseEvent* ui = (*iter)->GetComponent<MouseEvent>();
		// ���콺�� �ö� ���¿� �θ�UI�� ��츸
		if (ui->IsMouseOn() && (*iter)->GetParent() == nullptr)
		{
			targetFront = iter;
		}
	}

	// �̺��� ��Ŀ���� UI�� ���� ���
	if (targetBack == backUIGroup.end() && targetFront == frontUIGroup.end())
	{
		return nullptr;
	}

	/// �׷���׳����� ���� �ļ����� ���� 
	/// ��Ŀ���� frontUI�� �ִ� ���
	if (targetFront != frontUIGroup.end())
	{
		focusedUI = (*targetFront);
		frontUIGroup.erase(targetFront);
		frontUIGroup.push_back(focusedUI);
	}
	else /// ��Ŀ���� backUI�� �ִ°��
	{
		focusedUI = (*targetBack);
		backUIGroup.erase(targetBack);
		backUIGroup.push_back(focusedUI);
	}
	return focusedUI;
}

GameObject* UIManager::GetTargetedUI(GameObject* _parent)
{
	const InputManager* input = m_managerSet->GetInputManager();
	KEY_STATE LBtnState = input->GetKeyState(KEY::LMOUSE);

	// �θ� UI����, �ڽ�UI���� ���� Ÿ���õ� UI�� �����´�
	GameObject* targetUI = nullptr;

	list<GameObject*> q;
	vector<GameObject*> noneTarget;

	q.push_back(_parent);
	

	while (!q.empty())
	{
		GameObject* object = q.front();
		q.pop_front();

		MouseEvent* ui = object->GetComponent<MouseEvent>();

		if (ui->IsMouseOn())
		{
			if (nullptr != targetUI)
			{
				noneTarget.push_back(targetUI);
			}

			targetUI = object;
		}
		else
		{
			noneTarget.push_back(object);
		}

		vector<GameObject*>& children = object->GetChildren();
		for (auto child : children)
		{
			q.push_back(child);
		}
	}

	if (LBtnState == KEY_STATE::AWAY)
	{
		for (auto object : noneTarget)
		{
			MouseEvent* ui = object->GetComponent<MouseEvent>();
			ui->SetLBtnDown(false);
		}
	}
	return targetUI;
}
