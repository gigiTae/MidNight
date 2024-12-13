#pragma once
#include "Component.h"
#include "ParticleDefine.h"
class GameObject;
class Transform;

/// <summary>
/// ���1. ��ƼŬ ~ �� Ŭ���� or ���ӿ�����Ʈ -> �ϴ��� 2
/// ���2. ���� ��ƼŬ�� ��Ͻ��Ѿ� �ϴ°� -> �ϴ� y
/// 
/// 2023 07 27
/// </summary>

using namespace ps;


// ��ƼŬ�� �����ϴ� ������Ʈ Ŭ����
class ParticleSystem :  public Component
{
/// �����ڿ� �Ҹ���  ===================================================================
public:
	ParticleSystem(); 
	~ParticleSystem();

	Component* Clone() override;

	void Start() override;

///�ɹ� �Լ�  =========================================================================
public:
	void LateUpdate(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	void DebugRender(D2DRenderer* _d2DRendere) override;

	void Play() { m_isPlaying = true; m_durationTimer = 0.f; }
	void Stop();
	void AddParticle(GameObject* _obj); //��ƼŬ ���� �߰�
	void AddDefaultParticle(const wstring& imageKey);
	GameObject* GetParticlePrefab(UINT index) {	if (m_container.size() <= index) return nullptr;
											return m_container[index]; }
		
	void Remove();
	
	void SubEmit(GameObject* particle);	//��ƼŬ Ŭ���� ������ �̰� ȣ���ϰ� �ϰ�ʹ�..


private:
	//��ƼŬ ���� ���� �Լ�
	void Generate();
	
	void SetSquarePosNDir(Vector2& pos, Vector2& direction);
	void SetCirclePosNDir(Vector2& pos, Vector2& direction);
	void SetConePosNDir(Vector2& pos, Vector2& direction);

	void setRandomValue(const ParticleValue& value, float& result);
	void setRandomValue(const VarianceValue& value, float& result);
	

	// ���� �Լ�
	float LinearRandom(const float& min, const float& max);
	float NormalRandom(const float& min, const float& max);
	//float DiscreteRandom();


///�ɹ� ���� =========================================================================

	//--------------------------------------------------------------------
	//								�ý��� ���� 
	//--------------------------------------------------------------------
private:
	Transform* m_transform;				// �θ��� transform
	vector<GameObject*> m_container;	// ������ ��ƼŬ ���� ����Ʈ

	UINT m_typeCount;					// ��ƼŬ ���� ��
	UINT m_count;						// ���� �����ϴ� ��ƼŬ ��
	float m_durationTimer;				// ���� �ð�
	float m_emissionTimer;				// ���� �ð�
	float m_nextEmissionTime;			// ���� �ð�
	bool m_isPlaying = false;			// ���� ��ƼŬ�� ����ǰ� �ִ��� // play on awake?
	
	// ���� ����
	std::random_device rd;
	std::mt19937 gen;

	//--------------------------------------------------------------------
	//							   ��ƼŬ �⺻ ���� 
	//--------------------------------------------------------------------
public:
	EMISSION_SHAPE m_shape = EMISSION_SHAPE::CIRCLE; // ��ƼŬ�� ���� ����
	//�̷��� �ص� �Ǵ��� �𸣰ڴ� ������
	float m_rotation = 0;					// Square ~ ����..�ε� �̰Ը³�
	float m_halfWidth = 100;				// SQUARE ~ �ʺ� ����
	float m_halfHeight = 100;				// Square ~ ���� ����
	
	float &m_radius = m_rotation;			// CONE, CIRCLE ~ ������
	float &m_minDegree = m_halfWidth;		// CONE ~ �ּ� ��
	float &m_maxDegree = m_halfHeight;		// CONE ~ �ִ� ��

	Vector2 m_centerPos;
	Vector2 m_offset = Vector2(0,0);	// �θ�� ��ġ offset	

	UINT m_maxCount = 1000;				// �ִ�� ���� �� �ִ� ��ƼŬ ��
	bool m_isRepeat = true;				// �ݺ� ����

	float m_duration = 5;				// ����� �ð�
	float m_delayTime = 0;				// ���� Ʈ���� �� ������� �����ð�
	ParticleValue m_emitInterval;		// ���� ����(�ð�)
	//bool preWarm;	
	END_ACTION m_endAction = END_ACTION::SLEEP;	// ������ ���� �� �ൿ (Destroy�� ��� �θ� ������Ʈ ����)	

	///�簢���϶� ���̿����� ���� (�ӽ�..)
	RANDOM_TYPE m_SQUAREHeightRandom = RANDOM_TYPE::LINEAR;


	//--------------------------------------------------------------------
	//                          ��ƼŬ ���� ���� 
	//--------------------------------------------------------------------
	
	bool m_isCollide = false;			// �浹 ���� ����
	float m_gravity = 0;				// �߷� ���, 0�̸� �߷�x (��¥ �߷��� �ƴϰ� �����Ӹ�)
	ParticleValue m_lifeTime;			// ���������� �ð�
	
	ParticleValue m_initScale;			// �ʱ� ũ�� ��
	VarianceValue m_scaleVariance;		// ũ�� ��ȭ��

	ParticleValue m_initSpeed;			// �ʱ� �ӵ� ��
	VarianceValue m_speedVariance;		// �ӵ� ��ȭ��

	ParticleValue m_initRotation;		// �ʱ� ȸ�� ��
	VarianceValue m_rotationVariance;   // ȸ�� ��ȭ��

	ParticleValue m_initAlpha;			// �ʱ� ���� ��
	VarianceValue m_AlphaVariance;		// ���� ��ȭ��

	/// �Լ������ͷ� ��������� �Լ� �ޱ�


	//--------------------------------------------------------------------
	//								Sub Emitters
	//--------------------------------------------------------------------

	bool m_subEmit = false;
	TRIGGER m_subEmitTrigger = TRIGGER::TIME;
	float m_subEmitTime = 0.04f;

	//bool m_inherit; // ��� : lifetime, size, ...
	//UINT m_subEmditProbablity;
};

