#include "UserScriptsPCH.h"
#include "CheckPoint.h"
#include "ReturnCheckPoint.h"
#include "RabbitComponent.h"

CheckPoint::CheckPoint()
	:MonoBehaviour(typeid(this).name())
	,m_order(0)
	,m_position()
{

}

CheckPoint::~CheckPoint()
{

}

void CheckPoint::Start()
{
	m_position = GetComponent<Transform>()->GetPosition();


}

Component* CheckPoint::Clone()
{
	CheckPoint* clone = new CheckPoint();
	clone->m_order = m_order;
	clone->m_position = m_position;

	return clone;
}

void CheckPoint::OnTriggerEnter(const Collision& _collision)
{
	GameObject* otherObject = _collision.otherObject;

	// �÷��̾�� üũ ����Ʈ�� ����Ѵ� 
	if (otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (otherObject->GetName() == "player") // �÷��̾��� ���
		{
			otherObject->GetComponent<ReturnCheckPoint>()->SetCheckPoint(m_position, m_order);

		}
		else // �䳢�� ���
		{ 

			GameObject* player = otherObject->GetComponent<RabbitComponent>()->GetMainPlayer();
			player->GetComponent<ReturnCheckPoint>()->SetCheckPoint(m_position, m_order);
		}

		GetGameObject()->Destory();
		
		// TODO :: üũ����Ʈ ȿ�� 


	}
}
