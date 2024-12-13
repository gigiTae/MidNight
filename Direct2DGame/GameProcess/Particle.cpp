#include "GameProcessPCH.h"
#include "Component.h"
#include "MonoBehaviour.h"
#include "Particle.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "ParticleSystem.h"
#include "GameObject.h"

using namespace ps;

Particle::Particle()
	:MonoBehaviour(typeid(this).name())
	,m_system(nullptr), m_timer(0), m_isAwake(false), m_gravityAcceleration(0)
	, m_subEmit(false), m_subEmitTrigger(TRIGGER::NONE), m_subEmitTime(0)
{
}

Particle::~Particle()
{
}

Component* Particle::Clone()
{
	Particle* clone = new Particle();
	clone->m_textureKey = this->m_textureKey;
	
	return clone;
}


void Particle::Setup(ParticleSystem* system
	, Vector2 initPos, float scale, float roataion
	, float speed, Vector2 direction, float gravityFactor, float lifeTime
	, float dSpeed, float dScale, float dRotation
	, float alpha, float dAlpha)
{
	m_transform = GetComponent<Transform>();

	m_system = system;
	m_transform->SetPosition(initPos);
	m_transform->SetScale(Vector2(scale,scale));
	m_transform->SetRotation(roataion);
	m_speed = speed;
	m_direction = direction;
	m_gravityFactor = gravityFactor;
	m_lifeTime = lifeTime;
	m_dSpeed = dSpeed;
	m_dScale = dScale;
	m_dRotation = dRotation;
	m_alpha = alpha;
	m_dAlpha = dAlpha;

	m_scaleVarType = system->m_scaleVariance.varianceType;
	m_rotationVarType = system->m_rotationVariance.varianceType;
	m_speedVarType = system->m_speedVariance.varianceType;
	m_alphaVarType = system->m_AlphaVariance.varianceType;
}

void Particle::SetSubEmit(TRIGGER subEmitTrigger, float subEmitTime)
{
	m_subEmit = true;
	m_subEmitTrigger = subEmitTrigger;
	m_subEmitTime = subEmitTime;
}

void Particle::Update(float _deltaTime)
{
	if (m_isAwake)
	{
		m_timer += _deltaTime;

		//lifetime�� ������ ����
		if (m_lifeTime < m_timer && m_system !=nullptr)
		{
			GameObject* parent = GetGameObject();
			if (parent != nullptr)
			{
				m_isAwake = false;
				m_system->Remove(); // ��ƼŬ �ý��� �迭���� ����
				parent->Destory();		  // ������Ʈ ����
			}
		}

		///Transform ������Ʈ�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//ũ��
		float scale = m_transform->GetScale().x;
		Variance(scale, m_dScale, m_scaleVarType, _deltaTime); 
		m_transform->SetScale(Vector2(scale, scale));

		//�ӵ�
		Variance(m_speed, m_dSpeed, m_speedVarType, _deltaTime);
			
		//��ġ ~ �߷� ���
		if (m_gravityFactor != 0)
		{
			m_gravityAcceleration -= m_gravityFactor * _deltaTime;
		}

		Vector2 dxdy = m_direction * m_speed * _deltaTime;
		dxdy.y += m_gravityAcceleration;
		Vector2 pos = m_transform->GetPosition();
		m_transform->SetPosition(dxdy + pos);

		//ȸ��
		float rotation = m_transform->GetRotation();
		Variance(rotation, m_dRotation,m_speedVarType ,_deltaTime);
		m_transform->SetRotation(rotation);

		///TextureRenderer ������Ʈ�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//���İ�
		Variance(m_alpha, m_dAlpha, m_alphaVarType, _deltaTime);
		if (m_alpha < 0.f) m_alpha = 0.f;
		
		/// SubEmit�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		if (m_subEmitTrigger == TRIGGER::TIME)
		{
			m_subEmitTimer += _deltaTime;
			if (m_subEmitTime < m_subEmitTimer)
			{
				m_system->SubEmit(GetGameObject());
				m_subEmitTimer -= m_subEmitTime;
			}
		}
	}
}

void Particle::Render(D2DRenderer* _d2DRenderer)
{
	if (m_textureKey.empty())
		return;

	Vector2 position = m_transform->GetPosition();
	float rotation = m_transform->GetRotation();
	Vector2 scale = m_transform->GetScale();

	_d2DRenderer->DrawBitmap(m_textureKey, position, rotation, m_alpha, FLIP_TYPE::NONE, scale);
}

void Particle::DebugRender(D2DRenderer* _d2DRenderer)
{
// 	std::wstringstream wss;
// 	wss << m_alpha;
// 	wstring c = L" : ";
// 	c += wss.str();
// 	_d2DRenderer->DrawTextW(c, m_transform->GetPosition()
// 		, m_transform->GetPosition() + Vector2(300, 30));
}

void Particle::OnTriggerEnter(const Collision& _collision)
{
	m_dRotation = 0.f;
	m_dSpeed = 0.f;
	m_speed = 0.f;
	m_dAlpha = -0.5f;
	m_timer = m_lifeTime - 1.5f;
}


void Particle::Variance(float& arg, const float& var, const VARIANCE_TYPE& type, const float& dt)
{
	switch (type)
	{
	case VARIANCE_TYPE::VALUE:
		VarianceByValue(arg, var, dt);
		break;

	case VARIANCE_TYPE::PERCENT:
		VarianceByRatio(arg, var, dt);
		break;
	
	//case VARIANCE_TYPE::USER_DEFINE
	
	}
}

void Particle::VarianceByValue(float& arg, const float& var, const float& dt)
{
	arg = arg + var * dt;
}

void Particle::VarianceByRatio(float& arg, const float& var, const float& dt)
{
	arg = arg + (arg * var * dt);
}


