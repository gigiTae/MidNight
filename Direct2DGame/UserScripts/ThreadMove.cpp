#include "UserScriptsPCH.h"
#include "ThreadMove.h"

ThreadMove::ThreadMove()
	:MonoBehaviour(typeid(this).name())
	, m_isThreadDestroy(false)
	, m_rigidBody(nullptr)
	, m_transform(nullptr)
{

}

ThreadMove::~ThreadMove()
{

}

Component* ThreadMove::Clone()
{
	ThreadMove* clone = new ThreadMove();
	return clone;
}

void ThreadMove::Start()
{
	m_transform = GetComponent<Transform>();
	m_rigidBody = GetComponent<RigidBody>();
	m_rigidBody->SetFixed(true);

	m_prePosition = m_transform->GetPosition(); // �ʱ� ��ġ�� ����
}

void ThreadMove::Update(float _deltaTime)
{
	// ���� �������� ��
	m_position = m_transform->GetPosition();

	if (m_isThreadDestroy)
	{
		if (GetGameObject()->GetName() == "rightBox")
			m_position.x += 100.f * _deltaTime;
		else
		{
			m_position.x -= 100.f * _deltaTime;

		}


		m_isSoundStop = true;
	}


	if (abs(m_position.x - m_prePosition.x) <= 100.f)
	{
		m_transform->SetPosition(m_position);
		m_rigidBody->SetFixed(true);
		//m_isThreadDestroy = false;
		//SoundManager::GetInstance()->PauseSFXSound(2); //���� �ֱ�
	}

	if (abs(m_position.x - m_prePosition.x) >= 99.f)
	{
	
		if (m_isSoundStop)
		{
			m_isThreadDestroy = false;

			if (SoundManager::GetInstance()->isPlayingChannel2(3) == false)
			{

				//SoundManager::GetInstance()->SetSFXVolume(0.1f, 3);
				SoundManager::GetInstance()->PlaySFXSound(L"boxStop", 2, 3); //���� �ֱ�
				m_isSoundStop = false;
			}
			else if (SoundManager::GetInstance()->isPlayingChannel2(4) == false)
			{
				//SoundManager::GetInstance()->SetSFXVolume(0.1f, 4);
				SoundManager::GetInstance()->PlaySFXSound(L"boxStop", 2, 4); //���� �ֱ�
				m_isSoundStop = false;
			}
			else if (SoundManager::GetInstance()->isPlayingChannel2(5) == false)
			{
				//SoundManager::GetInstance()->SetSFXVolume(0.1f, 5);
				SoundManager::GetInstance()->PlaySFXSound(L"boxStop", 2, 5); //���� �ֱ�
				m_isSoundStop = false;
			}
		}
	}

}

void ThreadMove::Render(D2DRenderer* _d2DRenderer)
{

}

void ThreadMove::PostRender(D2DRenderer* _d2DRenderer)
{

}

void ThreadMove::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void ThreadMove::OnCollisionExit(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::INTERACTIVE_ITEM)
	{
		m_isThreadDestroy = true;
		m_rigidBody->SetFixed(false);

		if (SoundManager::GetInstance()->isPlayingChannel2(2) == false) 
		{
			//SoundManager::GetInstance()->SetSFXVolume(0.1f, 2);
			SoundManager::GetInstance()->PlaySFXSound(L"boxMove2", 2, 2); //���� �ֱ�
		}
		else if (SoundManager::GetInstance()->isPlayingChannel2(6) == false)
		{
			//SoundManager::GetInstance()->SetSFXVolume(0.1f, 6);
			SoundManager::GetInstance()->PlaySFXSound(L"boxMove2", 2, 6); //���� �ֱ�
		}
		else if (SoundManager::GetInstance()->isPlayingChannel2(7) == false)
		{
			//SoundManager::GetInstance()->SetSFXVolume(0.1f, 7);
			SoundManager::GetInstance()->PlaySFXSound(L"boxMove2", 2, 7); //���� �ֱ�
		}


	}
	// 	if (SoundManager::GetInstance()->isPlayingChannel(3) == false)
	// 	{
	// 		SoundManager::GetInstance()->SetSFXVolume(0.2f, 3);
	// 		SoundManager::GetInstance()->PlaySFXSound(L"boxStop", 2, 3); //���� �ֱ�
	// 	}
}

