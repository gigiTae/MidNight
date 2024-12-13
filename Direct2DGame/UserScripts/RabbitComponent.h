#pragma once
#include "MonoBehaviour.h"

class Inventory;

class RabbitComponent : public MonoBehaviour
{
public:
	RabbitComponent();
	~RabbitComponent();

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

	GameObject* GetMainPlayer() const { return m_mainPlayer; }
	void SetMainPlayer(GameObject* val) { m_mainPlayer = val; }
	
	bool* GetInputOn() { return &m_isInputOn; }
	bool GetisChangeObject() { return m_isChangeObject; }
	void ReturnToPlayer();
	void ReturnPaticle();
	void ReturnLight();

	//���� ����
	void WalkSound();
private:
	// ---------�÷��̾� ����------------
	GameObject* m_mainPlayer;
	Transform* m_playerTransform;
	Inventory* m_playerInventory;
	RigidBody* m_playerRigidBody;
	BoxCollider* m_boxColiider;

	// ---------------------------------
	float m_deltaTime;
	float m_speed;
	bool m_isInputOn; // Ű �Է� Ȱ��ȭ ����
	bool m_isChangeObject;

	float m_walkSoundTime;
	float m_isOneStep;

	Transform* m_transform;
	Animator* m_animator;
	RigidBody* m_rigidBody;
	Inventory* m_inventory;
	Actor* m_actor;

	Vector2 position;

	bool m_isRightDirection;
	bool m_isOnGround;
	bool m_isInverseGravity;
	int m_jumpCount;
	bool m_isJump;
	bool m_isReturnPlayer;
	bool m_isFall;
	//----------�䳢 ī�޶� ó��-----------
	const CameraManager* m_myCameraManager;
	Vector2 m_cameraPosition;
	float m_rabbitRangeX;
	float m_rabbitRangeY;
	bool m_isGravitySwtchOn;

 	const wchar_t* rabbitIdle = L"rabbitIdle";
 	const wchar_t* rabbitIdleFlip = L"rabbitIdleFlip";
	const wchar_t* rabbitWalk = L"rabbitWalk";
	const wchar_t* rabbitWalkFlip = L"rabbitWalkFlip";
 	const wchar_t* rabbitJump = L"rabbitJump";
 	const wchar_t* rabbitJumpFlip = L"rabbitJumpFlip";

	//�䳢 �����̵�
	ParticleSystem* m_paticleSystem;
	float returnPaticlePlayTime;
	PointLightRenderer* m_pointLight;
	float brightness;
	bool m_isReturn;
	Vector2 m_prePosition;
};



