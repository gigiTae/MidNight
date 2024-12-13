#include "UserScriptsPCH.h"
#include "ReturnCheckPoint.h"

ReturnCheckPoint::ReturnCheckPoint()
	:MonoBehaviour(typeid(this).name())
	,m_checkPointOrder(0)
{

}

ReturnCheckPoint::~ReturnCheckPoint()
{

}

Component* ReturnCheckPoint::Clone()
{
	ReturnCheckPoint* clone = new ReturnCheckPoint();
	clone->m_checkPoint = m_checkPoint;
	clone->m_checkPointOrder = m_checkPointOrder;

	return clone;
}

void ReturnCheckPoint::ReturnToCheckPoint()
{
	// ī�޶� ȿ�� 
	//GetCameraManager()->FadeOutCamera(f, true);
	GetCameraManager()->ClearCameraEffect();
	GetCameraManager()->FadeInCamera(5.f, true);

	// �÷��̾� �����̵�
	GetComponent<Transform>()->SetPosition(m_checkPoint);

}

void ReturnCheckPoint::SetCheckPoint(Vector2 _position, int _order)
{
	m_checkPoint = _position;
	m_checkPointOrder = _order;
}
