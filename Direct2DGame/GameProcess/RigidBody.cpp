#include "GameProcessPCH.h"
#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "Transform.h"
#include "BoxCollider.h"

RigidBody::RigidBody()
	:Component(CALL_ORDER::RIGID_BODY, typeid(this).name())
	, m_force(Vector2::Zero)
	, m_velocity(Vector2::Zero)
	, m_mass(1.f)
	, m_invMass(1.f)
	, m_isFixed(false)
	, m_isInverseGravity(false)
	, m_transform(nullptr)
{}

RigidBody::~RigidBody()
{}

Component* RigidBody::Clone()
{
	RigidBody* clone = new RigidBody();

	clone->m_force = m_force;
	clone->m_velocity = m_velocity;
	clone->m_mass = m_mass;
	clone->m_invMass = m_invMass;
	clone->m_transform = nullptr;

	return clone;
}

void RigidBody::LateUpdate(float _deltaTime)
{
	IntegrateForces(_deltaTime);

	// ������ �ӵ��� ������ ������Ʈ�� ��ġ�� �����Ѵ�.
	if (m_invMass == 0.f)
		return;
	Vector2 position = m_velocity * _deltaTime;
	m_transform->AddPosition(position);

	// �� �ʱ�ȭ
	m_force = Vector2::Zero;
}

void RigidBody::SetMass(float _mass)
{
	m_mass = _mass;
	if (m_mass < FLT_MAX)
	{
		m_invMass = 1.0f / m_mass;
	}
	else
	{
		m_invMass = 0.0f;
	}
}

void RigidBody::OnCollisionStay(const Collision& _collision)
{
	RigidBody* otherRigid = _collision.otherObject->GetComponent<RigidBody>();
	
	// ������ �ٵ� �������� ������ �ѱ��.
	if (!otherRigid)
		return;

	float otherMass = otherRigid->GetMass();
	float myMass = GetMass();

	// ���� ������ ���� ��� 
	if (_collision.otherCollider->GetColliderType() == COLLIDER_TYPE::BOX
		&& _collision.myCollider->GetColliderType() == COLLIDER_TYPE::BOX
		&& myMass < otherMass)
	{
		_collision.direct = PushBox(dynamic_cast<BoxCollider*>(_collision.otherCollider));
	}
	 
}   

void RigidBody::OnCollisionEnter(const Collision& _collision)
{
	RigidBody* otherRigid = _collision.otherObject->GetComponent<RigidBody>();
	RigidBody* myRigid = GetComponent<RigidBody>();

	// ������ �ٵ� �������� ������ �ѱ��.
	if (!otherRigid || !myRigid)
		return;

	float otherMass = otherRigid->GetMass();
	float myMass = myRigid->GetMass();

	if (_collision.otherCollider->GetColliderType() == COLLIDER_TYPE::BOX
		&& _collision.myCollider->GetColliderType() == COLLIDER_TYPE::BOX
		&& myMass <	 otherMass)
	{
		_collision.direct = PushBox(dynamic_cast<BoxCollider*>(_collision.otherCollider));
	}
}

void RigidBody::SetFixed(bool _isFixed)
{
	m_isFixed = _isFixed;  
	
	if (m_isFixed)
	{
		SetMass(FLT_MAX);

	}


}

COLLISION_DIRECT RigidBody::PushBox(BoxCollider* _other)
{
	RigidBody* otherRigid = _other->GetComponent<RigidBody>();
	BoxCollider* myCollider = GetComponent<BoxCollider>();

	auto myTransform = GetComponent<Transform>();

	// Radius ���ϱ� : Scale�� ���ݾ� ���ϱ�
	float radX = myCollider->GetScale().x * 0.5f + _other->GetScale().x * 0.5f;
	float radY = myCollider->GetScale().y * 0.5f + _other->GetScale().y * 0.5f;

	// Distance ���ϱ� : �����ִ� ������Ʈ�� ��ġ ���� ���ϱ�
	Vector2 myObjPos = myTransform->GetPosition();

	Vector2 myColliderPos = myCollider->GetPosition();
	Vector2 otherColliderPos = _other->GetPosition();

	float distX = abs(myColliderPos.x - otherColliderPos.x);
	float distY = abs(myColliderPos.y - otherColliderPos.y);

	// �о ��
	float pushX = radX - distX;
	float pushY = radY - distY;

	// �浹 ����
	COLLISION_DIRECT direct = COLLISION_DIRECT::NONE;

	// X�� �б�
	if (pushX < pushY)
	{
		if (myColliderPos.x < otherColliderPos.x)
		{
			pushX *= -1.f;
			direct = COLLISION_DIRECT::RIGHT;
		}
		else
		{
			direct = COLLISION_DIRECT::LEFT;
		}

		myObjPos.x += pushX;
		myTransform->SetPosition(myObjPos);
		myCollider->LateUpdate(0.f);
	
		// �а� ���Ŀ��� �� ���� �ӷ��� 0���� �����.
		m_velocity.x = 0.f;

	}
	// Y�� �б�
	else
	{
		if (myColliderPos.y < otherColliderPos.y)
		{
			pushY *= -1.f;
			direct = COLLISION_DIRECT::UP;
		}
		else
		{
			direct = COLLISION_DIRECT::DOWN;
		}


		myObjPos.y += pushY;
		myTransform->SetPosition(myObjPos);
		myCollider->LateUpdate(0.f);

		// �а� ���Ŀ��� �� ���� �ӷ��� 0���� �����.
		m_velocity.y = 0.f;
	}

	return direct;
}

void RigidBody::IntegrateForces(float _deltaTime)
{
	if (m_invMass == 0.f || m_isFixed)
		return;

	Vector2 gravity = GameWorld::GRAVITY;
	gravity *= m_isInverseGravity ? -1.f : 1.f;

	// ���� ������ �ӵ��� �����Ѵ�
	m_velocity += (m_force * m_invMass + gravity) * _deltaTime;

	m_velocity.y *= std::exp(-GameWorld::linearDamping * _deltaTime);
	m_velocity.x *= std::exp(-GameWorld::linearDamping * _deltaTime * 3);
}

void RigidBody::Start() 
{
	m_transform = GetComponent<Transform>();

	assert(m_transform);
}

void RigidBody::SetVelocity(Vector2 _velocity)
{
	Vector2 velocity = _velocity;

	if (m_isInverseGravity)
	{
		velocity.y *= -1;
	}

	m_velocity = velocity;
}

void RigidBody::ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector)
{
	m_velocity += _impulse * m_invMass;
}
