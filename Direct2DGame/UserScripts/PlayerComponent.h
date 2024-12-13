#pragma once
#include "MonoBehaviour.h"

class Inventory;
class FreezeEffect;
class PlayerLife;
class Actor;

class PlayerComponent : public MonoBehaviour
{
public:
	PlayerComponent();
	~PlayerComponent();

	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;
	/// ���� �⺻���� ������ �̺�Ʈ
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// ����� ���� ������ �Լ� F5�� �¿���
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionStay(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;

	void OnTriggerEnter(const Collision& _collision) override;

	bool GetChangeObject() const { return m_changeObject; }
	void SetChangeObject(bool val) { m_changeObject = val; }

	bool GetIsInverseGravity() const { return m_isInverseGravity; }
	void SetIsInverseGravity(bool val) { m_isInverseGravity = val; }
	
	void InverseGravityAnimation(float dt);
	
	bool IsPlayerActive() { return !m_changeObject; }
	GameObject* GetRabbit() const { return m_rabbit; }
	void SetRabbit(GameObject* _rabbit) { m_rabbit = _rabbit; }
	bool* GetInputOn() { return &m_isInputOn; }
	float GetSpeed() const { return m_speed; }
	void SetSpeed(float _speed) { m_speed = _speed; }
	float GetJumpPower() const { return m_jumpPower; }
	void SetJumpPower(float val) { m_jumpPower = val; }
	bool IsFreeze() const { return m_isFreeze; }
	void SetFreeze(bool val) { m_isFreeze = val; }


	/// �ִϸ��̼� ����
	void KeepRunnig();			//�¿� �̵�Ű ���� �� �ִϸ��̼� �ڿ�������
	void WalkAnimationCheck();	// 25������ �ð��� ����
	void JumpAnimation();

	bool GetGravitySwtchOn() const { return m_isGravitySwtchOn; }
	void SetGravitySwtchOn(bool val) { m_isGravitySwtchOn = val; }
	bool GetRightDirection() const { return m_isRightDirection; }
	void SetRightDirection(bool val) { m_isRightDirection = val; }
	PlayerLife* GetPlayerLife() const { return m_playerLife; }
	void SetPlayerLife(PlayerLife* val) { m_playerLife = val; }

	/// ���� ����
	void WalkSound();
	bool GetStop() const { return m_rStop; }
	void SetRStop(bool val) { m_rStop = val; }
private:
	
	GameObject* m_rabbit;
	float m_speed;
	float m_jumpPower;
	bool m_isInputOn; // Ű�Է��� �޴� ���� 
	bool m_isFreeze; // �� ��������
	float m_deltaTime;
	float m_changeAnimationTime;
	float m_keepRunningTime;
	float m_walkSoundTime;
	bool m_isOneStep;
	float m_jumpTime;
	bool m_isJumpControl;
	bool m_isCanJump;
	bool m_rStop;

	// �޾ƿ� ������Ʈ
	Transform* m_transform;
	Animator* m_animator;
	RigidBody* m_rigidBody;
	PlayerLife* m_playerLife;

	BoxCollider* m_boxCollider;
	Inventory* m_inventory;
	Inventory* m_rabbitInventory;
	FreezeEffect* m_freezeEffect;
	Actor* m_actor;
	int m_walkStyle;
	//�ӽ�
	//BoxRenderer* m_boxRenderer;
	
	Vector2 m_position;
	Vector2 m_prevPosition;

	// �޾ƿ� �Ŵ���
	const InputManager* m_myInputManager;
	const CollisionManager* m_myCollisionManager;
	const CameraManager* m_myCameraManager;
	
	bool m_isRightDirection;	// ������ ���� Ȯ��, �ִϸ��̼��� ������ �� ���
	bool m_isOnGround;		 
	bool m_isInverseGravity;
	bool m_isGravitySwtchOn;
	int m_jumpCount;
	bool m_changeObject;		// �䳢�� ������ �� ���
	bool m_isJump;
	bool m_isKeyDown;
	bool m_isChangeAnimationOn;
	bool m_isRun;
	UINT m_isOnIce;  //������ ��Ҵٰ� �������� �� �̲������°� Ǯ���� ���������� �߽��ϴ�
	bool m_isFirstKey;
	bool m_isPlayInverseAnimaition;
	float m_playInverseAnimaitionTime;
	bool m_isPrevRightDirection;
	float m_lateJumpTime;
	// �ִϸ��̼� �̸�
	const wchar_t* playerIdle = L"playerIdle";
	const wchar_t* playerIdleFlip = L"playerIdleFlip";
	const wchar_t* playerWalk = L"playerWalk";
	const wchar_t* playerWalkFlip = L"playerWalkFlip";
	const wchar_t* playerJump = L"playerJump";
	const wchar_t* playerJumpFlip = L"playerJumpFlip";	
	
	const wchar_t* playerJumping = L"playerJumping";
	const wchar_t* playerJumpingFlip = L"playerJumpingFlip";

// 	const wchar_t* playerIdleToWalk = L"playerIdleToWalk";
// 	const wchar_t* playerIdleToWalkFlip = L"playerIdleToWalkFlip";	
	const wchar_t* playerInverseGravity = L"playerInverseGravity";
	const wchar_t* playerInverseGravityFlip = L"playerInverseGravityXFlip";
	
	const wchar_t* playerWalkToIdle = L"playerWalkToIdle";
	const wchar_t* playerWalkToIdleFlip = L"playerWalkToIdleFlip";

	const wchar_t* playerFreeHand = L"playerFreeHand";
	const wchar_t* playerFreeHandFlip = L"playerFreeHandFlip";

	const wchar_t* playerFreezeIdle = L"playerFreezeIdle";
	const wchar_t* playerFreezeIdleFlip = L"playerFreezeIdleFlip";
	const wchar_t* playerFreezeWalk = L"playerFreezeWalk";
	const wchar_t* playerFreezeWalkFlip = L"playerFreezeWalkFlip";
	const wchar_t* playerFreezeJump = L"playerFreezeJump";
	const wchar_t* playerFreezeJumpFlip = L"playerFreezeJumpFlip";
	// �߷� �ִϸ��̼� ����
	vector<Collider*> m_colliderVector;
};

