#include "UserScriptsPCH.h"
#include "PlayerComponent.h"
#include "Inventory.h"
#include "SlideTile.h"
#include "Icicle.h"
#include "FreezeEffect.h"
#include "PassPlatform.h"
#include "Actor.h"
#include "PlayerLife.h"
#include <random>

/// <summary>
/// ĳ���� �̵�, ���߷��� ������
/// </summary>
PlayerComponent::PlayerComponent()
	:MonoBehaviour(typeid(this).name()), m_speed(0.f), m_transform(nullptr), m_animator(nullptr), m_isRightDirection(true), m_isOnGround(false), m_rigidBody(nullptr)
	, m_jumpCount(0), m_isInverseGravity(false), m_changeObject(false), m_isGravitySwtchOn(false), m_rabbit(nullptr), m_inventory(nullptr), m_rabbitInventory(nullptr)
	, m_myInputManager(nullptr), m_myCollisionManager(nullptr), m_isJump(false), m_boxCollider(nullptr), m_isInputOn(false), m_myCameraManager(nullptr), m_isRun(false)
	, m_changeAnimationTime(0.f), m_deltaTime(0.f), m_isChangeAnimationOn(false), m_isKeyDown(false), m_keepRunningTime(0.f), m_isOnIce(0), m_jumpPower(0.f), m_isFreeze(false)
	, m_freezeEffect(nullptr), m_isFirstKey(false), m_playerLife(nullptr), m_isOneStep(false), m_walkSoundTime(0.f), m_jumpTime(0.f), m_lateJumpTime(0.f), m_playInverseAnimaitionTime(0.f)
	, m_isPlayInverseAnimaition(false), m_isPrevRightDirection(true), m_actor(nullptr), m_isJumpControl(false), m_walkStyle(0), m_rStop(false)
{

}

PlayerComponent::~PlayerComponent()
{

}

Component* PlayerComponent::Clone()
{
	PlayerComponent* clone = new PlayerComponent();

	return clone;
}

void PlayerComponent::Start()
{
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();   // �Է¿� ���� �ִϸ��̼��� ��Ʈ���Ϸ��� ������ ���� �ִϸ����� ������Ʈ�� ������ 
	m_rigidBody = GetComponent<RigidBody>();
	m_boxCollider = GetComponent<BoxCollider>();
	m_freezeEffect = GetComponent<FreezeEffect>();
	m_actor = GetComponent<Actor>();

	// �κ��丮 ���� 
	m_inventory = GetComponent<Inventory>();
	m_rabbitInventory = m_rabbit->GetComponent<Inventory>();

	m_speed = 300.f;
	m_jumpPower = 600.f; //�÷��̾� ������

	m_jumpCount = 0; // ���� ���� Ƚ��

	m_isInputOn = true; // Ű�Է� Ȱ��ȭ

	// �Ŵ��� �޾ƿ��� ���
	m_myInputManager = GetInputManager();
	m_myCollisionManager = GetCollisionManager();
	m_myCameraManager = GetCameraManager();
	m_changeAnimationTime = 0.416f;		// 25������ �ִϸ��̼��� ����ϴ� �ð� 
	m_keepRunningTime = 0.1f;			// �޸��� ����
	//m_transform->SetScale(Vector2(31.5f, 10000.f));
	//m_boxRenderer=CreateComponent<BoxRenderer>();
	m_walkSoundTime = 0.52f;				//�ȱ�ȿ���� Ÿ�̹�
	m_isOneStep = true;
	m_jumpTime = 1.f;					// ���� �ִϸ��̼� �ð�

	m_lateJumpTime = 0.1f;			// ���� ������ �ð� ����

	m_isJumpControl = false;
	

}

void PlayerComponent::Update(float _deltaTime)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(1, 5);
	m_walkStyle = dis(gen);

	m_deltaTime = _deltaTime;
	// ���� ������ �޾ƿ���
	m_position = m_transform->GetPosition();

	m_myCollisionManager->DetectBoxToCollider(Vector2(m_position.x - 31.5f, -10000.f), Vector2(m_position.x + 31.5f, +10000.f), m_colliderVector);

	m_isKeyDown = false; // Ű�� ���� �ִϸ��̼� ������ 0���� �ʱ�ȭ

	if (m_changeObject)
	{
		// �� ������ �� ó��
		if (GetRightDirection())
		{
			m_animator->Play(playerFreeHand, true);
		}
		else
		{
			m_animator->Play(playerFreeHandFlip, true);
		}
	}
	else
	{
		// Idle �ִϸ��̼��� �ֻ�ܿ� ��ġ

		if (GetRightDirection())
		{
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeIdle, true);
			}
			else
			{
				m_animator->Play(playerIdle, true);
			}
		}
		else
		{
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeIdleFlip, true);
			}
			else
			{
				m_animator->Play(playerIdleFlip, true);
			}
		}

		if (m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::TAP) && m_isInputOn)
		{
			m_isRightDirection = false;

		}
		if (m_myInputManager->IsKeyState(KEY::RIGHT, KEY_STATE::TAP) && m_isInputOn)
		{
			m_isRightDirection = true;

		}

		/// ����Ű �Է� 
		if (m_myInputManager->IsKeyState(KEY::UP, KEY_STATE::HOLD) && m_isInputOn)
		{
			// ��ȣ�ۿ�
		}

		/// �������� �ȱ�
		if (m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD) && m_isInputOn && m_isRightDirection == false)
		{
			if (m_isOnIce)
			{
				if (m_isInverseGravity)
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed() * -1.f, m_rigidBody->GetVelocity().y * -1));
				}
				else
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed() * -1.f, m_rigidBody->GetVelocity().y));
				}
			}
			else
			{
				if (m_isInverseGravity == true)
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y * -1));
				else
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y));

				m_position.x -= GetSpeed() * _deltaTime;
			}
			if (m_isInverseGravity)
			{
				m_animator->SetOffset(Vector2(20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(-20.f, +10.f));
			}
			else
			{
				m_animator->SetOffset(Vector2(20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(-20.f, -10.f));
			}
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeWalkFlip, true);
			}
			else
			{
				m_animator->Play(playerWalkFlip, true);
			}


			// �ȱ� �Ҹ�
			if (m_isOnGround)
			{
				WalkSound();
			}

			m_isRun = true;
			m_keepRunningTime = 0.1f;
			SetRightDirection(false);
			m_isKeyDown = true;
		}
		else
		{
			m_animator->Reset(playerWalkFlip);
			m_animator->Reset(playerFreezeWalkFlip);

		}

		/// ���������� �ȱ�
		if (m_myInputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD) && m_isInputOn && m_isRightDirection == true//&& !m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD)
			)
		{
			if (m_isInverseGravity)
			{
				m_animator->SetOffset(Vector2(-20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(20.f, +10.f));
			}
			else
			{
				m_animator->SetOffset(Vector2(-20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(20.f, -10.f));
			}

			if (m_isOnIce)
			{
				if (m_isInverseGravity)
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed(), m_rigidBody->GetVelocity().y * -1.f));
				}
				else
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed(), m_rigidBody->GetVelocity().y));
				}

			}
			else
			{
				if (m_isInverseGravity == true)
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y * -1.f));
				else
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y));
				m_position.x += GetSpeed() * _deltaTime;
			}
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeWalk, true);
			}
			else
			{
				m_animator->Play(playerWalk, true);
			}

			if (m_isOnGround)
			{
				WalkSound();
			}

			m_isRun = true;

			m_isKeyDown = true;
			m_keepRunningTime = 0.1f;
		}
		else
		{
			m_animator->Reset(playerWalk);
			m_animator->Reset(playerFreezeWalk);
		}

		/// ���� ��������
		if (m_myInputManager->IsKeyState(KEY::DOWN, KEY_STATE::TAP) && m_isInputOn && !m_isFreeze)
		{
			m_isRun = false;	// �޸��鼭 ������ ���������� �ִϸ��̼� ���� ����
			// ������ Ȱ��ȭ�ϸ� ĳ���ʹ� �⺻���� �ִϸ��̼� ���
			if (GetRightDirection())
			{
				m_animator->Play(playerIdle, true);
			}
			else
			{
				m_animator->Play(playerIdleFlip, true);
			}

			if (m_isOnGround)
			{
				SetChangeObject(true);

				m_rigidBody->SetFixed(true);

				// �κ��丮�� �������� �䳢���� �����Ѵ�.
				m_inventory->SetActive(false);

				// �ڽ��� �κ��丮 ������ �䳢�� �κ��丮�� �����Ѵ�.
				m_inventory->PassItemList(m_rabbitInventory->GetInventory());

				// �䳢 �κ��丮 Ȱ��ȭ 
				m_rabbitInventory->SetActive(true);

				m_rabbit->GetComponent<BoxCollider>()->SetActive(true);
				GetCameraManager()->SetTargetObject(m_rabbit);

			}
		}
		/// ����
		if (m_myInputManager->IsKeyState(KEY::SPACE, KEY_STATE::TAP) && m_isInputOn)
		{
			if (m_jumpCount > 0 && m_isOnGround)
			{
				if (SoundManager::GetInstance()->isPlayingChannel(7) == false)
					SoundManager::GetInstance()->PlaySFXSound(L"jump", 1, 7);

				m_rigidBody->SetVelocity(Vector2(0.f, m_jumpPower));				// ���� ��
				m_jumpCount--;												// ������ ���� Ƚ��
				m_prevPosition = m_position;
				m_isJump = true;
				m_isOnIce = 0;
			}
			m_isOnGround = false;
		}

		/// ���� �ִϸ��̼�
		if (m_isJump)
		{
			JumpAnimation();
		}

		/// ���߷��� �� ���� �Ǵ� �͵�
		if (m_isOnGround && GetGravitySwtchOn() == false)
		{
			// ���߷� ���Ű
			if (m_myInputManager->IsKeyState(KEY::R, KEY_STATE::TAP) && m_isInputOn && !m_isFreeze && !GetStop())
			{
				// �ִϸ��̼� �ʱ�ȭ
				m_playInverseAnimaitionTime = 0.f;
				m_isPlayInverseAnimaition = true;
				m_isPrevRightDirection = m_isRightDirection;

				Vector2 offset = m_boxCollider->GetOffset();
				offset.y *= -1.f;
				m_boxCollider->SetOffset(offset);

				if (m_isInverseGravity == false)
				{
					m_isInverseGravity = true;
				}
				else
				{
					m_isInverseGravity = false;
				}

				SetGravitySwtchOn(true);
				
				m_isOnGround = false;

				m_jumpCount--;
				m_prevPosition = m_position; // ���߷� �����ϸ� ���� �������� ����Ѵ�.
				SetSpeed(150.f);

				if (m_actor)
				{
					if (m_isInverseGravity)
						m_actor->SetInverse(true);
					else
						m_actor->SetInverse(false);
				}

			}
		}
		InverseGravityAnimation(_deltaTime);	// ���߷� �ִϸ��̼�
	}
	/// Ű�� �������� �� ó��
	if (m_isKeyDown == false)
	{
		m_changeAnimationTime = 0.416f; // idleToWalk �ִϸ��̼��� ����ð�

		KeepRunnig(); // Ű�� ���� ���� �� �ð��� �����ؼ� �ִϸ��̼��� ��Ʈ��
		WalkAnimationCheck();
		if (GetRightDirection() && m_isRun && m_isInverseGravity == false)
		{
			m_animator->Play(playerWalkToIdle, true);
		}
		else if (GetRightDirection() && m_isRun && m_isInverseGravity)
		{
			m_animator->Play(playerWalkToIdle, true);
		}

		if (GetRightDirection() == false && m_isRun)
		{
			m_animator->Play(playerWalkToIdleFlip, true);
		}
		//m_animator->Reset();
	}

//   	m_isCanJump = true;
// 	if (m_isJumpControl)
// 	{
// 		m_lateJumpTime -= 1.f * m_deltaTime;
// 		
// 		if (m_lateJumpTime < 0)
// 		{
// 			m_isOnGround = true;
// 			m_isCanJump = false;
// 			m_lateJumpTime = 0.1f;
// 		}
// 	}


	m_isChangeAnimationOn = true;

	// �߷� ����
	m_rigidBody->SetInverseGravity(m_isInverseGravity);

	// Ʈ������ ������Ʈ�� ���ؼ� ��ġ ����
	m_transform->SetPosition(m_position);


}

void PlayerComponent::Render(D2DRenderer* _d2DRenderer)
{

}

void PlayerComponent::PostRender(D2DRenderer* _d2DRenderer)
{

}

void PlayerComponent::DebugRender(D2DRenderer* _d2DRenderer)
{
	// 	std::wstringstream wss;
	// 	wss << m_rigidBody->GetVelocity().y;
	// 	wstring c = L" y �ӵ�: ";
	// 	c += wss.str();
	// 	_d2DRenderer->DrawTextW(c, m_transform->GetPosition() + Vector2(0,300)
	// 		,m_transform->GetPosition() + Vector2(300, 0));
}

void PlayerComponent::OnCollisionEnter(const Collision& _collision)
{
	// ���� ������ ó���� ��

	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_jumpTime = 1.f;
			m_isOnGround = true;
			SetGravitySwtchOn(false);
			m_jumpCount = 1;								// �������� Ƚ��
			SetSpeed(300.f);
			m_isJump = false;
			m_isJumpControl = true;
//			if (m_animator->GetCurrentAnmation() != nullptr)
//				m_animator->GetCurrentAnmation()->SetFrame(0);	// �ִϸ��̼��� ó������ ���
			// Ÿ�� ������ �Ҹ�����
			//SoundManager::GetInstance()->PlaySFXSound(L"step", 2, 0); //���� �ֱ�
			
		}
	}

	// ��� ���� ���� �ִϸ��̼� ����
	if (_collision.direct == COLLISION_DIRECT::DOWN && m_isInverseGravity == false)
	{
		playerIdle = L"playerIdle";
		playerIdleFlip = L"playerIdleFlip";
		playerWalk = L"playerWalk";
		playerWalkFlip = L"playerWalkFlip";
		playerJump = L"playerJump";
		playerJumpFlip = L"playerJumpFlip";

		playerWalkToIdle = L"playerWalkToIdle";
		playerWalkToIdleFlip = L"playerWalkToIdleFlip";

		playerFreeHand = L"playerFreeHand";
		playerFreeHandFlip = L"playerFreeHandFlip";

		playerFreezeIdle = L"playerFreezeIdle";
		playerFreezeIdleFlip = L"playerFreezeIdleFlip";
		playerFreezeWalk = L"playerFreezeWalk";
		playerFreezeWalkFlip = L"playerFreezeWalkFlip";
		playerFreezeJump = L"playerFreezeJump";
		playerFreezeJumpFlip = L"playerFreezeJumpFlip";

		playerJumping = L"playerJumping";
		playerJumpingFlip = L"playerJumpingFlip";

		// ���߷�
		playerInverseGravity = L"playerInverseGravity";
		playerInverseGravityFlip = L"playerInverseGravityXFlip";
		//m_myCameraManager->SetGravityMode(1); // ���� ���� �� ī�޶�
	}
	else if (_collision.direct == COLLISION_DIRECT::UP && m_isInverseGravity)
	{
		playerIdle = L"playerIdleInverse";
		playerIdleFlip = L"playerIdleFlipInverse";
		playerWalk = L"playerWalkInverse";
		playerWalkFlip = L"playerWalkFlipInverse";
		playerJump = L"playerJumpInverse";
		playerJumpFlip = L"playerJumpFlipInverse";
		playerWalkToIdle = L"playerWalkToIdleInverse";
		playerWalkToIdleFlip = L"playerWalkToIdleFlipInverse";

		playerFreeHand = L"playerFreeHandInverse";
		playerFreeHandFlip = L"playerFreeHandFlipInverse";
		//m_myCameraManager->SetGravityMode(-1); // ���߷� ���� �� ī�޶�

		playerFreezeIdle = L"playerFreezeIdleInverse";
		playerFreezeIdleFlip = L"playerFreezeIdleFlipInverse";
		playerFreezeWalk = L"playerFreezeWalkInverse";
		playerFreezeWalkFlip = L"playerFreezeWalkFlipInverse";
		playerFreezeJump = L"playerFreezeJumpInverse";
		playerFreezeJumpFlip = L"playerFreezeJumpFlipInverse";

		playerJumping = L"playerJumpingInverse";
		playerJumpingFlip = L"playerJumpingFlipInverse";

		// ���߷�
		playerInverseGravity = L"playerInverseGravityYFlip";
		playerInverseGravityFlip = L"playerInverseGravityXYFlip";
	}

	//���� �ٴ�
	if (_collision.otherObject->GetName() == "slideTile")
	{
		if (!_collision.otherObject->GetComponent<SlideTile>()->GetIsMelt())
			m_isOnIce++;
	}

}

void PlayerComponent::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isJump = false;
			m_jumpCount = 1;


			m_isOnGround = true;
		}
	}
}

void PlayerComponent::OnCollisionExit(const Collision& _collision)
{
	// ������ �������� ��
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE
		//&& (_collision.direct == COLLISION_DIRECT::DOWN || _collision.direct == COLLISION_DIRECT::UP)
		)
	{
		m_isJumpControl = true;
		m_isOnGround = false; 
	}

	//���� �ٴ�
	if (_collision.otherObject->GetName() == "slideTile")
	{
		if (!_collision.otherObject->GetComponent<SlideTile>()->GetIsMelt())
			m_isOnIce--;
	}

	// ���� 
	if (_collision.otherObject->GetName() == "feather")
	{
		m_rigidBody->SetFixed(false);
		m_rigidBody->SetMass(0.1f);
	}


}

void PlayerComponent::OnTriggerEnter(const Collision& _collision)
{

	// ��帧�� ������ ���߷� ����
	if (_collision.otherObject->GetName() == "icicle")
	{
		// true ������ ���߷� false ������ �߷»��� 
		bool inverseGravity = _collision.otherObject->GetComponent<Icicle>()->IsInverseGravity();

		m_rigidBody->SetVelocity(Vector2::Zero);
		m_isFreeze = true;
		m_freezeEffect->Freeze();
		
		m_walkSoundTime = 1.4f;

		// �÷��̾� hp ����
		m_playerLife->DicreaseLife();
		if (m_playerLife->GetLife() <= 0)
		{

// 			// ��帧 ����
// 			if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::INTERACTIVE_ITEM)
// 				return;

			// �����
			GetSceneManager()->RegisterNextScene(GetSceneManager()->GetCurrentScene()->GetSceneName());
		}

		if (m_isInverseGravity == inverseGravity)
			return;

		Vector2 offset = m_boxCollider->GetOffset();
		offset.y *= -1.f;
		m_boxCollider->SetOffset(offset);

		if (m_isInverseGravity == false)
		{
			m_isInverseGravity = true;
		}
		else
		{
			m_isInverseGravity = false;

		}
		SetGravitySwtchOn(true);
		m_isOnGround = false;

		m_jumpCount--;
		m_prevPosition = m_position; // ���߷� �����ϸ� ���� �������� ����Ѵ�.

	}
}


void PlayerComponent::InverseGravityAnimation(float dt)
{
	if (!m_isPlayInverseAnimaition)
		return;

// 	if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
// 		SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //���� �ֱ�

	m_playInverseAnimaitionTime += dt;

	// ȸ���ִϸ��̼� ����
	if (m_playInverseAnimaitionTime >= 0.8f)
	{
		m_animator->Reset(playerInverseGravity);
		m_animator->Reset(playerInverseGravityFlip);
		m_isPlayInverseAnimaition = false;

		if (m_isInverseGravity == false)
		{
			playerIdle = L"playerIdle";
			playerIdleFlip = L"playerIdleFlip";
			playerWalk = L"playerWalk";
			playerWalkFlip = L"playerWalkFlip";
			playerJump = L"playerJump";
			playerJumpFlip = L"playerJumpFlip";

			playerWalkToIdle = L"playerWalkToIdle";
			playerWalkToIdleFlip = L"playerWalkToIdleFlip";

			playerFreeHand = L"playerFreeHand";
			playerFreeHandFlip = L"playerFreeHandFlip";

			playerFreezeIdle = L"playerFreezeIdle";
			playerFreezeIdleFlip = L"playerFreezeIdleFlip";
			playerFreezeWalk = L"playerFreezeWalk";
			playerFreezeWalkFlip = L"playerFreezeWalkFlip";
			playerFreezeJump = L"playerFreezeJump";
			playerFreezeJumpFlip = L"playerFreezeJumpFlip";

			playerJumping = L"playerJumping";
			playerJumpingFlip = L"playerJumpingFlip";

			// ���߷�
			playerInverseGravity = L"playerInverseGravity";
			playerInverseGravityFlip = L"playerInverseGravityXFlip";
			//m_myCameraManager->SetGravityMode(1); // ���� ���� �� ī�޶�
		}
		else if (m_isInverseGravity)
		{
			playerIdle = L"playerIdleInverse";
			playerIdleFlip = L"playerIdleFlipInverse";
			playerWalk = L"playerWalkInverse";
			playerWalkFlip = L"playerWalkFlipInverse";
			playerJump = L"playerJumpInverse";
			playerJumpFlip = L"playerJumpFlipInverse";
			playerWalkToIdle = L"playerWalkToIdleInverse";
			playerWalkToIdleFlip = L"playerWalkToIdleFlipInverse";

			playerFreeHand = L"playerFreeHandInverse";
			playerFreeHandFlip = L"playerFreeHandFlipInverse";
			//m_myCameraManager->SetGravityMode(-1); // ���߷� ���� �� ī�޶�

			playerFreezeIdle = L"playerFreezeIdleInverse";
			playerFreezeIdleFlip = L"playerFreezeIdleFlipInverse";
			playerFreezeWalk = L"playerFreezeWalkInverse";
			playerFreezeWalkFlip = L"playerFreezeWalkFlipInverse";
			playerFreezeJump = L"playerFreezeJumpInverse";
			playerFreezeJumpFlip = L"playerFreezeJumpFlipInverse";

			playerJumping = L"playerJumpingInverse";
			playerJumpingFlip = L"playerJumpingFlipInverse";

			// ���߷�
			playerInverseGravity = L"playerInverseGravityYFlip";
			playerInverseGravityFlip = L"playerInverseGravityXYFlip";
		}
	}

	if (m_isInverseGravity == true)
	{
		if (GetGravitySwtchOn() == true)
		{
			if (m_isPrevRightDirection)
				m_animator->Play(playerInverseGravityFlip, true);			// ���߷� �� �ö� �� �ִϸ��̼�
			else
				m_animator->Play(playerInverseGravity, true);			// ���߷� �� �ö� �� �ִϸ��̼�

			m_myCameraManager->SetGravityMode(-1); // ���� ���� �� ī�޶�
			if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //���� �ֱ�
		}
		else
		{
			m_animator->Reset(playerInverseGravity);
			m_animator->Reset(playerInverseGravityFlip);
		}
		
	}
	else if (!m_isInverseGravity)
	{
		if (GetGravitySwtchOn() == true)
		{
			if (m_isPrevRightDirection)
				m_animator->Play(playerInverseGravityFlip, true);			// ���߷� �� �ö� �� �ִϸ��̼�
			else
				m_animator->Play(playerInverseGravity, true);			// ���߷� �� �ö� �� �ִϸ��̼�

			m_myCameraManager->SetGravityMode(1); // ���� ���� �� ī�޶�
			if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //���� �ֱ�

		}
		else
		{
			m_animator->Reset(playerInverseGravity);
			m_animator->Reset(playerInverseGravityFlip);
		}

	}
}

void PlayerComponent::WalkAnimationCheck()
{
	m_changeAnimationTime -= 1.f * m_deltaTime;
	if (m_changeAnimationTime < 0)
	{
		m_isChangeAnimationOn = false;

	}
}

void PlayerComponent::JumpAnimation()
{
	m_jumpTime -= 1.f * m_deltaTime;

	if (GetRightDirection() == true)
	{
		if (m_isFreeze)
		{
			m_animator->Play(playerFreezeJump, true);
		}
		else
		{
			if (m_jumpTime < 0)
			{
				m_animator->Play(playerJumping, true);

			}
			else
			{
				m_animator->Play(playerJump, true);
			}
		}
	}
	else
	{
		if (m_isFreeze)
		{
			m_animator->Play(playerFreezeJumpFlip, true);
		}
		else
		{
			if (m_jumpTime < 0)
			{
				m_animator->Play(playerJumpingFlip, true);
			}
			else
			{
				m_animator->Play(playerJumpFlip, true);
			}
		}
	}
}

void PlayerComponent::KeepRunnig()
{
	m_keepRunningTime -= 1.f * m_deltaTime;
	if (m_keepRunningTime < 0)
	{
		m_isRun = false;
	}
}

void PlayerComponent::WalkSound()
{
	m_walkSoundTime -= 1.f * m_deltaTime;

	//SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound", 5); //���� �ֱ�

	if (m_walkSoundTime < 0)
	{
		if (m_walkStyle==1)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound1", 1, 5); //���� �ֱ�
				//m_isOneStep = false;
			}
		}
		else if(m_walkStyle == 2)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound2", 1, 5); //���� �ֱ�
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 3)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound3", 1, 5); //���� �ֱ�
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 4)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound4", 1, 5); //���� �ֱ�
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 5)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound5", 1, 5); //���� �ֱ�
				//m_isOneStep = true;
			}
		}
		if(m_isFreeze)
			m_walkSoundTime = 1.0f;

		else
			m_walkSoundTime = 0.52f;

	}
}
