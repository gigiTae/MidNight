#include "UserScriptsPCH.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Inventory.h"


RabbitComponent::RabbitComponent()
	:MonoBehaviour(typeid(this).name()), m_speed(0.f), m_transform(nullptr), m_animator(nullptr), m_isRightDirection(true), m_isOnGround(true)
	, m_rigidBody(nullptr), m_jumpCount(0), m_isInverseGravity(false), m_inventory(nullptr), m_isInputOn(false), m_playerInventory(nullptr)
	, m_playerTransform(nullptr), m_mainPlayer(nullptr), m_playerRigidBody(nullptr), m_actor(nullptr), m_isJump(false), m_myCameraManager(nullptr)
	, m_rabbitRangeX(0.f), m_rabbitRangeY(0.f), m_isGravitySwtchOn(false), m_deltaTime(0.f), m_isReturnPlayer(false), m_pointLight(nullptr)
	, m_isOneStep(false), m_walkSoundTime(0.f), returnPaticlePlayTime(0.f), m_paticleSystem(nullptr), m_isReturn(false), m_isFall(false)
	, brightness(0.f), m_isChangeObject(false)

{

}

RabbitComponent::~RabbitComponent()
{

}

Component* RabbitComponent::Clone()
{
	RabbitComponent* clone = new RabbitComponent();

	return clone;
}

void RabbitComponent::Start()
{
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();   // �Է¿� ���� �ִϸ��̼��� ��Ʈ���Ϸ��� ������ ���� �ִϸ����� ������Ʈ�� ������ 
	m_rigidBody = GetComponent<RigidBody>();
	m_actor = GetComponent<Actor>();
	m_boxColiider = GetComponent<BoxCollider>();

	// �κ��丮 ����
	m_playerInventory = m_mainPlayer->GetComponent<Inventory>();
	m_inventory = GetComponent<Inventory>();

	m_isInputOn = true; // Ű�Է� Ȱ��ȭ

	m_speed = 200.f;
	m_jumpCount = 1; // ���� ���� Ƚ��
	m_mainPlayer = GetMainPlayer();

	m_playerTransform = m_mainPlayer->GetComponent<Transform>();
	m_playerRigidBody = m_mainPlayer->GetComponent<RigidBody>();

	m_myCameraManager = GetCameraManager();
	m_rabbitRangeX = 960 - 50;
	m_rabbitRangeY = 540 - 30;

	m_paticleSystem = GetComponent<ParticleSystem>();

	//returnPaticlePlayTime = 0.3f;
	m_pointLight = CreateComponent<PointLightRenderer>();
	brightness = 0.f;
	m_pointLight->SetIntensity(brightness);
	
}

void RabbitComponent::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;
	// �÷��̾��� ������ ������
	Vector2 m_playerPosition = m_playerTransform->GetPosition();
	m_isChangeObject = m_mainPlayer->GetComponent<PlayerComponent>()->GetChangeObject();
	m_isInverseGravity = m_mainPlayer->GetComponent<PlayerComponent>()->GetIsInverseGravity();
	m_isGravitySwtchOn = m_mainPlayer->GetComponent<PlayerComponent>()->GetGravitySwtchOn();

	// ���� ������ �޾ƿ���
	Vector2 position = m_transform->GetPosition();

	// �Ŵ��� �޾ƿ��� ���
	const InputManager* input = GetInputManager();

	m_cameraPosition = m_myCameraManager->GetCamera()->GetPosition();

	if (m_isChangeObject)
	{
		m_myCameraManager->SetTargetObject(m_mainPlayer);		// �÷��̾ ī�޶� ����
		m_animator->SetShow(true);
		// Idle �ִϸ��̼��� �ֻ�ܿ� ��ġ
		if (m_isRightDirection)
		{
			m_animator->Play(rabbitIdle, true);
		}
		else
		{
			m_animator->Play(rabbitIdleFlip, true);
		}

		/// ����Ű �Է�
		if (input->IsKeyState(KEY::UP, KEY_STATE::TAP) && m_isInputOn)
		{
			// ������ ���õ� ��ȣ�ۿ� Ű
			//ReturnToPlayer();
			//ReturnPaticle();
			returnPaticlePlayTime = 0.5f;
			m_isReturnPlayer = true;

			
		}
		if (input->IsKeyState(KEY::DOWN, KEY_STATE::TAP) && m_isInputOn)
		{
			brightness = 0.f;
			

		}
		if (input->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD) && m_isInputOn)
		{
			position.x += m_speed * _deltaTime;

			m_animator->Play(rabbitWalk, true);
			m_isRightDirection = true;


			if (m_isOnGround)
			{
				WalkSound();
			}
		}
		if (input->IsKeyState(KEY::LEFT, KEY_STATE::HOLD) && m_isInputOn)
		{
			position.x -= m_speed * _deltaTime;
			m_animator->Play(rabbitWalkFlip, true);

			m_isRightDirection = false;

	
			if (m_isOnGround)
			{
				WalkSound();
			}
		}
		if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP) && m_isInputOn)
		{
			if (m_jumpCount > 0 && m_isOnGround)
			{
		
				if (SoundManager::GetInstance()->isPlayingChannel(7) == false)
					SoundManager::GetInstance()->PlaySFXSound(L"jump", 1, 7); //���� �ֱ�
				m_rigidBody->SetVelocity(Vector2(0.f, 650.f));				// ���� ��
				m_jumpCount--;				 								// ������ ���� Ƚ��
				m_isJump = true;

			}
			m_isOnGround = false;
		}

		// ���� �ִϸ��̼�
		if (m_isOnGround == false)
		{
			if (m_isRightDirection == true)
			{
				m_animator->Play(rabbitJump, true);
			}
			else
			{
				m_animator->Play(rabbitJumpFlip, true);
			} 
	
		}
	}
	else
	{
		m_animator->SetShow(false);
		//�÷��̾��� �������� �䳢 �����ǿ� �ִ´�. 
		if(m_mainPlayer->GetComponent<PlayerComponent>()->GetRightDirection())
			position = Vector2(m_playerPosition.x + 40.f, m_playerPosition.y);
		else
			position = Vector2(m_playerPosition.x - 40.f, m_playerPosition.y);
	}

	if (m_isOnGround==false && m_isJump == false)
	{
		m_isFall = true;
	}

	if (m_actor)
	{
		if (m_isInverseGravity)
			m_actor->SetInverse(true);
		else
			m_actor->SetInverse(false);
	}


	// �߷� ����
	m_rigidBody->SetInverseGravity(m_isInverseGravity);

	if (m_isInverseGravity)
	{
		m_boxColiider->SetOffset(Vector2(0.f, 12.5f));
	}
	else
	{
		m_boxColiider->SetOffset(Vector2(0.f, -12.5f));
	}

	// ī�޶� ���� �䳢 ������ ����

	if (abs(position.x - m_cameraPosition.x) >= m_rabbitRangeX)			// ����ȭ��width/2 - �䳢�� width/2
	{
		// ����?
		m_isReturnPlayer = true;
	}
	else if ((abs(position.y - m_cameraPosition.y) -100.f >= m_rabbitRangeY) && m_isGravitySwtchOn == false && m_isReturnPlayer==false)
	{
	
		m_isReturnPlayer = true;
		m_prePosition = position;
		
	}

	else
	{
		m_transform->SetPosition(position);
	}
// 	else
// 	{
// 		// Ʈ������ ������Ʈ�� ���ؼ� ��ġ ����
// 		m_transform->SetPosition(position);
// 	}


	if (m_isReturnPlayer)
	{

		m_isInputOn = false;
		ReturnPaticle();
		if(m_isFall==false)
			m_transform->SetPosition(position);
		else if(m_isFall//&&m_isOnGround==false && m_isJump==false
			) //�䳢�� �׳� �پ����
		{
			m_transform->SetPosition(m_prePosition);
		}


	}
// 	else
// 		m_transform->SetPosition(position);

	if (m_isReturn)
		ReturnLight();
}

void RabbitComponent::Render(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::PostRender(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::OnCollisionEnter(const Collision& _collision)
{
	// ���� ������ ó���� ��
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isOnGround = true;
			m_jumpCount = 1;									// �������� Ƚ��
			//m_animator->GetCurrentAnmation()->SetFrame(0);	// �ִϸ��̼��� ó������ ���
			m_isJump = false;

		}
	}

	// ��� ���� ���� �ִϸ��̼� ����
	if (_collision.direct == COLLISION_DIRECT::DOWN && m_isInverseGravity == false)
	{
		rabbitIdle = L"rabbitIdle";
		rabbitIdleFlip = L"rabbitIdleFlip";
		rabbitWalk = L"rabbitWalk";
		rabbitWalkFlip = L"rabbitWalkFlip";
		rabbitJump = L"rabbitJump";
		rabbitJumpFlip = L"rabbitJumpFlip";
	}
	else if (_collision.direct == COLLISION_DIRECT::UP && m_isInverseGravity)
	{
		rabbitIdle = L"rabbitIdleInverse";
		rabbitIdleFlip = L"rabbitIdleFlipInverse";
		rabbitWalk = L"rabbitWalkInverse";
		rabbitWalkFlip = L"rabbitWalkFlipInverse";
		rabbitJump = L"rabbitJumpInverse";
		rabbitJumpFlip = L"rabbitJumpFlipInverse";
	}
}

void RabbitComponent::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isJump = false;
			m_jumpCount = 1;
			m_isOnGround = true;
			m_isFall = false;
		}
	}
}

void RabbitComponent::OnCollisionExit(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		m_isOnGround = false;
	}
}

void RabbitComponent::OnTriggerEnter(const Collision& _collision)
{
	// ��帧�� ������ ���߷� ����
	if (_collision.otherObject->GetName() == "icicle")
	{
		//ReturnToPlayer();
	
		m_isReturnPlayer = true;
	}
}

void RabbitComponent::ReturnToPlayer()
{
	returnPaticlePlayTime = 0.5f;
	// ��ȣ�ۿ� Ű
	m_mainPlayer->GetComponent<PlayerComponent>()->SetChangeObject(false);

	// �κ��丮�� �������� �䳢���� �����Ѵ�.
	m_inventory->SetActive(false);

	// �ڽ��� �κ��丮 ������ �䳢�� �κ��丮�� �����Ѵ�.
	m_inventory->PassItemList(m_playerInventory->GetInventory());

	// �䳢 �κ��丮 Ȱ��ȭ 
	m_playerInventory->SetActive(true);

	m_playerRigidBody->SetFixed(false);
	m_playerRigidBody->SetMass(0.1f);

	GetComponent<BoxCollider>()->SetActive(false);
	
	GetCameraManager()->SetTargetObject(m_mainPlayer);
	//brightness = 0.f;
	m_pointLight->SetIntensity(brightness);
	m_isReturn = true;
	//brightness = 1.f;

}

void RabbitComponent::ReturnPaticle()
{
	returnPaticlePlayTime -= 1.f * m_deltaTime;
	brightness += 1.f * m_deltaTime;
	m_pointLight->SetIntensity(brightness);

	//����Ʈ ����Ʈ ũ��
	m_pointLight->SetScale(Vector2(3.f, 3.f));
	//m_transform->SetPosition(m_prePosition);
	if (SoundManager::GetInstance()->isPlayingChannel(11) == false)
		SoundManager::GetInstance()->PlaySFXSound(L"rabbitReturn", 1, 11);
	if (returnPaticlePlayTime < 0)
	{
		m_isReturnPlayer = false;
		m_isInputOn = true;
		ReturnToPlayer();
		m_animator->SetShow(false);
		m_paticleSystem->Play();
		brightness = 1.f;
	}
}

void RabbitComponent::ReturnLight()
{
	brightness -= 1.f * m_deltaTime;
	m_pointLight->SetIntensity(brightness);

	if (brightness <= 0.f)
	{
		m_isReturn = false;
		brightness = 0.f;
	}
}

void RabbitComponent::WalkSound()
{
	m_walkSoundTime -= 1.f * m_deltaTime;

	if (m_walkSoundTime < 0)
	{
		if (m_isOneStep)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(3) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"dollWalkSound1", 1,3); //���� �ֱ�
			m_isOneStep = false;
		}
		else
		{
			if (SoundManager::GetInstance()->isPlayingChannel2(10) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"dollWalkSound2", 2,10); //���� �ֱ�
			m_isOneStep = true;
		}
		m_walkSoundTime = 0.25;

	}
}
