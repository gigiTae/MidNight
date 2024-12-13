#include "UserScriptsPCH.h"
#include "InteractiveItem.h"
#include "Inventory.h"

InteractiveItem::InteractiveItem()
	:MonoBehaviour(typeid(this).name())
	,m_itemType(ITEM_TYPE::NONE)
	,m_isActive(true)
	,m_isDissapear(false)
	,m_textureRenderer(nullptr)
{

}

InteractiveItem::~InteractiveItem()
{

}

Component* InteractiveItem::Clone()
{
	return nullptr;
}

void InteractiveItem::Update(float _deltaTime)
{
	if (m_isDissapear && m_textureRenderer)
	{
		float textureAlpha = m_textureRenderer->GetAlpha();
		textureAlpha -= m_dissapearSpeed * _deltaTime;
		m_textureRenderer->SetAlpha(textureAlpha);
	}
}

void InteractiveItem::Start()
{
	m_textureRenderer = GetComponent<TextureRenderer>();
}

void InteractiveItem::OnTriggerStay(const Collision& _collision)
{
	const InputManager* input = GetInputManager();

	// ��ȣ�ۿ� Ű�� ������ �浹�� ������Ʈ�� �÷��̾� 
	// TODO :: ������ ���¿��� �÷��̾� ��, �䳢�� Ű�տ� ������ ������ �߻�����      
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER
		&& input->IsKeyState(KEY::UP, KEY_STATE::TAP))
	{
		Interact(_collision.otherObject);
	}

}

void InteractiveItem::Interact(GameObject* _user)
{
	if (!m_isActive)
	{
		return;
	}

	switch (m_itemType)
	{
	case ITEM_TYPE::NONE:
		assert(!L"������ �ʱ�ȭ�� ���ּ���");
		break;
	case ITEM_TYPE::KEY:
	{
		KeyProcess(_user);
	}
	break;
	case ITEM_TYPE::DOOR:
	{
		DoorProcess(_user);
	}
	break;
	default:
		break;
	}
}

void InteractiveItem::KeyProcess(GameObject* _user)
{
	Inventory* inven = _user->GetComponent<Inventory>();
	assert(inven);

	if (!inven->IsActive())
		return;

	// ���� �÷���
	SoundManager::GetInstance()->PlaySFXSound(L"coin", 1,2);

	// ������ �κ��丮�� �����Ͽ� Key�� �߰��Ѵ�. 
	inven->PusBack(ITEM_TYPE::KEY); 

	// �ѹ� ��ȣ�ۿ� ���Ŀ��� ��ȣ�ۿ��� �Ұ��� ���·� �����.
	m_isActive = false;
	m_isDissapear = true  ;
	GetGameObject()->Destory(1.f);
}

void InteractiveItem::DoorProcess(GameObject* _user)
{
	Inventory* inven = _user->GetComponent<Inventory>();
    assert(inven);
	
	// �κ��丮 ��Ȱ��ȭ�� 
	if (!inven->IsActive())
		return;

	// �÷��̾ Ű�� �ִ� ��� Ű�� �����
	if (inven->UseItem(ITEM_TYPE::KEY))
	{
		if (SoundManager::GetInstance()->isPlayingChannel(3) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"dooropen", 1,3);
		m_isActive = false;
		m_isDissapear = true;
		GetGameObject()->Destory(1.f);
	}
	else // �÷��̾ Ű�� ���� ��� : ����� ���
	{
		if (SoundManager::GetInstance()->isPlayingChannel(4) == false)
			SoundManager::GetInstance()->PlaySFXSound(L"gun", 1,4);
	}
}
