#include "GameProcessPCH.h"
#include "Actor.h"
#include "Transform.h"
#include "GameObject.h"
#include "DirectManager.h"
#include "InputManager.h"

Actor::Actor()
	:MonoBehaviour(typeid(this).name())\
	,m_actingOrder(0)
	,m_isInverse(false)
	,m_offset(Vector2::Zero)
	,m_isActing(false)
	,m_currentIndex(0)
	,m_transform(nullptr)
	,m_elapsedTime(0.f)
	,m_textOffset()
	,m_inverseOffset(Vector2::Zero)
{

}

Actor::~Actor()
{

}

Component* Actor::Clone()
{
	assert(nullptr);

	return nullptr;
}

void Actor::Start()
{
	m_transform = GetComponent<Transform>();

	// DirectManger�� �ڱ� �ڽ��� �߰��Ѵ�. 
	GetDirectManager()->AddActor(GetGameObject());

}

void Actor::Update(float _deltaTime)
{
	if (!m_isActing)
		return;

	m_elapsedTime += _deltaTime;

	while (m_elapsedTime > m_talkingInfomation.outputTempo 
		&& m_currentIndex < m_talkingInfomation.text.size())
	{
		m_elapsedTime -= m_talkingInfomation.outputTempo;
		m_outputText += m_talkingInfomation.text[m_currentIndex];
		m_currentIndex++;
	}

	const InputManager* input = GetInputManager();
	
	// ����� ��� �Ǿ����� �����̽� Ű�� �����ų� �⺻ �ؽ�Ʈ �ð� �ʰ��̸� ���� ������ �����Ѵ�.
	if(m_currentIndex == m_talkingInfomation.text.size() 
		&& (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP) || m_elapsedTime > END_TEXT_TIME)) 
	{
		m_isActing = false;
		GetDirectManager()->FinishActing(m_actingOrder);
	}

	if (input->IsKeyState(KEY::CTRL, KEY_STATE::HOLD))
	{
		m_isActing = false;
		GetDirectManager()->FinishActing(m_actingOrder);
	}

}

void Actor::DirectTalking(const TalkingInfomation& _info, int _actingOrder)
{
	m_currentIndex = 0;
	m_elapsedTime = 0.f;
	m_isActing = true;
	m_outputText.clear();
	m_talkingInfomation = _info;

	m_actingOrder = _actingOrder;
}

void Actor::Render(D2DRenderer* _d2DRenderer)
{
	if (!m_isActing)
		return;

	Vector2 position = m_transform->GetPosition();

	// leftBottom �������� ����
	
	// ��ǳ�� ũ�� 
	Vector2 bubbleSize = _d2DRenderer->GetBitmapSize(m_talkingInfomation.imageKey);

	position.x += m_offset.x;

	// ������ ���
	if (m_isInverse)
	{
		position.y -= m_offset.y;
		position.x += bubbleSize.x * 0.5f;
		position.y -= bubbleSize.y * 0.5f;
	}
	else
	{
		position.y += m_offset.y;
		position += bubbleSize * 0.5f;
	}

	// ������ ���� ��ǳ�� ���
	if (m_isInverse)
		_d2DRenderer->DrawBitmap(m_talkingInfomation.imageKey, position, 0.f, 1.f, FLIP_TYPE::Y_FLIP);
	else
		_d2DRenderer->DrawBitmap(m_talkingInfomation.imageKey, position);

	if (m_isInverse)	
	{
		position.x += m_textOffset.x;
		position.y += m_textOffset.y*1.f;
	}
	else
	{
		position.x += m_textOffset.x;
		position.y += m_textOffset.y;
	}

	if (m_isInverse)
	{
		position += m_inverseOffset;
	}

	// �ؽ�Ʈ ���
	Vector2 leftTop{ position.x - bubbleSize.x *0.5f, position.y + bubbleSize.y *0.5f};
	Vector2 rightBottom{ position.x + bubbleSize.x * 0.5f, position.y - bubbleSize.y *0.5f};

	_d2DRenderer->DrawTextW(m_outputText, leftTop, rightBottom, m_talkingInfomation.textColor, FONT_TYPE::TALK);
}
