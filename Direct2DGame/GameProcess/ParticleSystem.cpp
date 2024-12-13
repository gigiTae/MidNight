#include "GameProcessPCH.h"
#include "ParticleSystem.h"

#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "TextureRenderer.h"
#include "Animator.h"
#include "Particle.h"
#include "CircleCollider.h"
#include "PointLightRenderer.h"

#include "Scene.h"
#include "SceneManager.h"

using namespace ps;
using namespace FMath;


ParticleSystem::ParticleSystem()
	: Component(CALL_ORDER::PARTICLE_SYSTEM, typeid(this).name())
	, m_transform(nullptr)
	, m_typeCount(0), m_count(0), m_durationTimer(0), m_emissionTimer(0)
	, gen(rd())
	, m_nextEmissionTime(0.f)
{
	//�⺻�� ����

	m_emitInterval = { 0.2f };
	m_lifeTime = { 3.f };
	m_initScale = { 1.f };
	m_scaleVariance = { 0.f };
	m_initSpeed = { 50.f };
	m_speedVariance = { 0.f };
	m_initRotation = { 0.f };
	m_rotationVariance = { 0.f };
	m_initAlpha = { 1.f };
	m_AlphaVariance = { 0.f };
}

ParticleSystem::~ParticleSystem()
{
	//������ �ִ� ��ƼŬ ������ ����
	for (auto i : m_container)
	{
		i->Finalize();
		delete i;
	}
}

Component* ParticleSystem::Clone()
{
	ParticleSystem* clone = new ParticleSystem();
	
	/*clone->m_transform = nullptr;		 

	
	clone->m_particles.clear();
	clone->m_count = 0;
	clone->m_durationTimer = 0;
	clone->m_emissionTimer = 0;
	clone->m_nextEmissionTime = 0;
	clone->m_isPlaying = false;*/

	return clone;
}

void ParticleSystem::Start()
{
	//��ġ �ʱ�ȭ
	m_transform = GetComponent<Transform>();
	m_centerPos = m_transform->GetPosition();
	m_nextEmissionTime = m_delayTime;
}

void ParticleSystem::LateUpdate(float _deltaTime)
{
	if (m_isPlaying)
	{
		// ������ ������Ʈ
		m_centerPos = m_transform->GetPosition() + m_offset;

		// �ð��� ���� ����
		m_emissionTimer += _deltaTime;

		while (m_nextEmissionTime < m_emissionTimer)
		{
			m_emissionTimer -= m_nextEmissionTime;

			if (m_count < m_maxCount)
			{
				Generate();
				m_nextEmissionTime = LinearRandom(m_emitInterval.mininum, m_emitInterval.maximum);
			}
			else
			{
				break;
			}
		}
	}

	//�ѹ� �ݺ��� �������� Ȯ��
	if (!m_isRepeat)
	{
		if (m_duration < m_durationTimer)
		{
			m_isPlaying = false;
			m_durationTimer = 0;
			m_emissionTimer = 0;
			
			if(m_endAction == END_ACTION::DESTROY)
				GetGameObject()->Destory();
		}
		else
		{
			m_durationTimer += _deltaTime;
		}
	}
}

void ParticleSystem::Render(D2DRenderer* _d2DRenderer)
{

}

void ParticleSystem::DebugRender(D2DRenderer* _d2DRendere)
{
	std::wstringstream wss;
	wss << m_count;
	wstring c = L"��ƼŬ �� : ";
	c += wss.str();
	_d2DRendere->DrawTextW(c, m_transform->GetPosition()
		, m_transform->GetPosition() + Vector2(300,0));
}

void ParticleSystem::Stop()
{
	m_isPlaying = false;
	m_durationTimer = 0;
	m_emissionTimer = 0;
}

void ParticleSystem::AddParticle(GameObject* _obj)
{
	if (_obj->GetComponent<Particle>() == nullptr)
	{
		//assert();
	}

	m_container.push_back(_obj);
	m_typeCount++;
}

void ParticleSystem::AddDefaultParticle(const wstring& imageKey)
{
	GameObject* obj = new GameObject("particle", GetManagerSet(), OBJECT_TYPE::PARTICLE);
	Transform* transform = obj->CreateComponent<Transform>();
	Particle* particle = obj->CreateComponent<Particle>();
	particle->SetTextureKey(imageKey);

	if (m_isCollide)
	{
		CircleCollider* collider = obj->CreateComponent<CircleCollider>();
		collider->SetRadius(5.f);
		collider->SetRadius(true);
	}

	m_container.push_back(obj);
	m_typeCount++;
}

void ParticleSystem::Generate()
{
	m_count++;

	//��ƼŬ �� ����
	Vector2 pos;
	Vector2 direction;

	switch (m_shape)
	{
	case EMISSION_SHAPE::SQUARE:
		SetSquarePosNDir(pos, direction);
		break;

	case EMISSION_SHAPE::CIRCLE:
		SetCirclePosNDir(pos, direction);
		break;

	case EMISSION_SHAPE::CONE:
		SetConePosNDir(pos, direction);
		break;
	}

	float scale = 0, scaleVar = 0;
	setRandomValue(m_initScale, scale);
	setRandomValue(m_scaleVariance, scaleVar);

	float speed = 0, speedVar = 0;
	setRandomValue(m_initSpeed, speed);
	setRandomValue(m_speedVariance, speedVar);

	float rotation = 0, rotationVar = 0;
	setRandomValue(m_initRotation, rotation);
	setRandomValue(m_rotationVariance, rotationVar);

	float lifeTime = 0;
	setRandomValue(m_lifeTime, lifeTime);

	float alpha = 0, alphaVar = 0;
	setRandomValue(m_initAlpha, alpha);
	setRandomValue(m_AlphaVariance, alphaVar);

	UINT index = 0;

	if (m_typeCount == 1)
	{
		index = 0;
	}
	else
	{
		std::uniform_int_distribution<int> dis(0, m_typeCount - 1);
		index = dis(gen);
	}

	//��ƼŬ ����
	GameObject* obj = new GameObject(*m_container[index]);

	Particle* p = obj->GetComponent<Particle>();
	p->Setup(this
		, pos, scale, rotation, speed, direction
		, m_gravity, lifeTime, speedVar, scaleVar, rotationVar
		, alpha, alphaVar);

	if (m_subEmit)
	{
		p->SetSubEmit(m_subEmitTrigger, m_subEmitTime);
	}

	//���� ���
	GetSceneManager()->RegisterObject(obj, 0);

	p->Play();
}

void ParticleSystem::Remove()
{
	m_count--;
}

void ParticleSystem::SubEmit(GameObject* particle)
{
	//��ƼŬ ����
	GameObject* obj = new GameObject(*particle);
	m_count++;

	Particle* p = obj->GetComponent<Particle>();
	Particle* origin = particle->GetComponent<Particle>();
	Transform* t = particle->GetComponent<Transform>();
	p->Setup(this
		, t->GetPosition(), t->GetScale().x, t->GetRotation(), 0, Vector2(0,0)
		, 0, origin->m_lifeTime * 0.5f, 0, 0, /*p->m_dRotation*/ 0
		, origin->m_alpha, origin->m_dAlpha);

	//���� ���
	GetSceneManager()->RegisterObject(obj, 0);

	p->Play();
}

void ParticleSystem::SetSquarePosNDir(Vector2& pos, Vector2& direction)
{
	//��ġ
	pos.x = LinearRandom(m_centerPos.x - m_halfWidth
		, m_centerPos.x + m_halfWidth);
	
	///�ӽ�
	if (m_SQUAREHeightRandom == RANDOM_TYPE::NORMAL)
	{
		pos.y = NormalRandom(m_centerPos.y - m_halfHeight
			, m_centerPos.y + m_halfHeight);
		
	}
	else
	{
		pos.y = LinearRandom(m_centerPos.y - m_halfHeight
			, m_centerPos.y + m_halfHeight);
	}


	//����
	///�簢���� ��� �ѹ��� ����صΰ� ������ ���� �ȴ� ���߿� ����ȭ
	float radian = DegToRad(m_rotation);
	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();
}

void ParticleSystem::SetCirclePosNDir(Vector2& pos, Vector2& direction)
{
	//���� -> ����
	float radian = LinearRandom(0.f, (float)6.28318); //0 ~ 360
	float radius = LinearRandom(0.f, m_radius);

	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();

	// �������� ������ ��ǥ ���
	pos.x = radius * direction.x + m_centerPos.x;
	pos.y = radius * direction.y + m_centerPos.y;
}

void ParticleSystem::SetConePosNDir(Vector2& pos, Vector2& direction)
{
	//���� -> ����
	float radian;
	float radius;
	if (m_maxDegree < m_minDegree)
	{
		radian = LinearRandom(DegToRad(m_maxDegree), DegToRad(m_minDegree + 360)); //0 ~ 360
		radius = LinearRandom(0.f, radius);
	}
	else
	{
		radian = LinearRandom(DegToRad(m_minDegree), DegToRad(m_maxDegree)); //0 ~ 360
		radius = LinearRandom(0.f, radius);
	}


	direction.x = cos(radian);
	direction.y = sin(radian);
	direction.Normalize();

	// �������� ������ ��ǥ ���
	pos.x = radius * direction.x + m_centerPos.x;
	pos.y = radius * direction.y + m_centerPos.y;
}

void ParticleSystem::setRandomValue(const ParticleValue& value, float& result)
{
	switch (value.randomType)
	{
	case RANDOM_TYPE::NONE:
		result = value.mininum;
		break;

	case RANDOM_TYPE::LINEAR:
		result = LinearRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::NORMAL:
		result = NormalRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::DISCRETE:
		//�̱���
		break;
	}
}

void ParticleSystem::setRandomValue(const VarianceValue& value, float& result)
{
	switch (value.randomType)
	{
	case RANDOM_TYPE::NONE:
		result = value.mininum;
		break;

	case RANDOM_TYPE::LINEAR:
		result = LinearRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::NORMAL:
		result = NormalRandom(value.mininum, value.maximum);
		break;

	case RANDOM_TYPE::DISCRETE:
		//�̱���
		break;
	}
}



float ParticleSystem::LinearRandom(const float& min, const float& max)
{
	if (min == max) return min;
	//if (min > max) return min;

	//���� ���� ���� 
	//�������� ��������س��� ���°ɷ�)
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

float ParticleSystem::NormalRandom(const float& min, const float& max)
{
	float mean = (min + max) / 2;
	float sigma = (max - min) / (2 * 1);
	std::normal_distribution<float> dis(mean, sigma);

	return dis(gen);
}

// float ParticleSystem::DiscreteRandom()
// {
// 	return 0.0f;
// }