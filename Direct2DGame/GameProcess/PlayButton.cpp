#include "GameProcessPCH.h"
#include "PlayButton.h"
#include "GameObject.h"
#include "PopupWindow.h"
#include "Transform.h"


PlayButton::PlayButton()
	:MonoBehaviour(typeid(this).name())
	,m_popupWindow(nullptr)
{

}

PlayButton::~PlayButton()
{

}

Component* PlayButton::Clone()
{
	// �������� ����
	assert(nullptr);

	return nullptr;
}

void PlayButton::Start()
{
	m_popupWindow = GetComponent<Transform>()->GetParent()->GetComponent<PopupWindow>();

	// �θ��� ������Ʈ�� popupWindow�� ���°��
	assert(m_popupWindow);


}

void PlayButton::OnMouseClicked()
{
	m_popupWindow->SetActive(false);

}
