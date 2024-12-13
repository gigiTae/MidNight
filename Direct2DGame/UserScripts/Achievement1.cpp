#include "UserScriptsPCH.h"
#include "Achievement1.h"
#include "Window.h"

Achievement1::Achievement1()
	:MonoBehaviour(typeid(this).name()), m_transform(nullptr)
	, m_input(nullptr), m_isOpen(false), m_showDuration(3.f), m_showTimer(0.f)
{

}

Achievement1::~Achievement1()
{}

/// �ɹ� �Լ��� ���� ����� �𸣰ھ �������������� �ھ���,
// x��ǥ �������� ���� 
bool SortbyX(Window* chan1, Window* chan2)
{
	if (chan1->GetGameObject()->GetComponent<Transform>()->GetPosition().x
		< chan2->GetGameObject()->GetComponent<Transform>()->GetPosition().x)
		return true;
	else
		return false;
}

void Achievement1::Start()
{
	m_input = GetInputManager();
	m_transform = GetComponent<Transform>();
	m_isOn = { false, false, false, false};

	// ��� ���鸮�� ã��
	const vector<GameObject*>& objs = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::INTERACTIVE_ITEM);
	for (auto obj : objs)
	{
		if (obj->GetComponent<Window>() != nullptr)
			m_windows.push_back(obj->GetComponent<Window>());
	}

	// x �������� ����
	std::sort(m_windows.begin(), m_windows.end(), SortbyX);
}

void Achievement1::Update(float _deltaTime)
{
	// �ݺ� ���鼭 �������� Ȯ��
	m_Count = 0;
	for (int i = 0; i < m_windows.size(); i++)
	{
		if (m_windows[i]->IsOpen())
		{
			m_isOn[i] = true;
			m_Count++;
		}
	}

	// ���� �������̶� �޶����ٸ� ����
	if (m_Count != m_lastCount)
	{
		m_isOpen = true;
		m_showTimer = m_showDuration;
	}

	m_lastCount = m_Count;

	// Ű �Է½� ����
	if (m_input->GetKeyState(KEY::Q) == KEY_STATE::HOLD)
	{
		m_isOpen = true;
		m_showTimer = m_showDuration;
	}

	// �ð��� ������ ���� (�� : 580, �Ʒ� : 505)
	if (0 < m_showTimer)
	{
		m_showTimer -= _deltaTime;
		if (m_showTimer < 0)
		{
			m_showTimer = 0;
			m_isOpen = false;
		}

		float y = m_transform->GetPosition().y;
		y = FMath::Lerp(y, 505, _deltaTime * 5);
		m_transform->SetPosition(Vector2(0.f, y));
	}
	else
	{
		float y = m_transform->GetPosition().y;
		y = FMath::Lerp(y, 580, _deltaTime * 5);
		m_transform->SetPosition(Vector2(0.f, y));
	}
}

void Achievement1::Render(D2DRenderer* _d2DRenderer)
{
	// ��� ����
	Vector2 pos = m_transform->GetPosition();
	_d2DRenderer->DrawBitmap(L"���൵â", pos);

	// ������ ����
	pos.x -= 65 * (m_isOn.size() - 1) * 0.5;
	for (auto obj : m_isOn)
	{
		if (obj == true)
		{
			_d2DRenderer->DrawBitmap(L"Ŀư Ȱ��", pos);
		}
		else
		{
			_d2DRenderer->DrawBitmap(L"Ŀư ��Ȱ��", pos);
		}
		pos.x += 65;
	}
}
