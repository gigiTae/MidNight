#pragma once

#include "Component.h"

class BoxCollider;
class GameObject;
class Transform;
/// <summary>
/// ������ �ٵ� ������Ʈ
/// �������� ������ ���� ó���� ��
/// ���� ������ ����� ���� ���� ������Ʈ
/// </summary>
class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();
	Component* Clone() override;

	void LateUpdate(float _deltaTime) override;
	void IntegrateForces(float _deltaTime);

	void Start() override;

	void AddForce(const Vector2& _force) { m_force += _force; }
	void SetVelocity(Vector2 _velocity);
	void ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector);

	void SetMass(float _mass);
	float GetMass() { return m_mass; }
	
	void OnCollisionStay(const Collision& _collision) override;
	void OnCollisionEnter(const Collision& _collision) override;

	Vector2 GetVelocity() { return m_velocity; }
	
	bool IsFixed() const { return m_isFixed; }
	void SetFixed(bool _isFixed);
	bool IsInverseGravity() const { return m_isInverseGravity; }
	void SetInverseGravity(bool val) { m_isInverseGravity = val; }

private:
	COLLISION_DIRECT PushBox(BoxCollider* _other);

private: // ������� ����
	Transform* m_transform;
	// �ӵ�
	Vector2 m_velocity;
	// ��
	Vector2 m_force;
	// ����
	float m_mass, m_invMass;

	bool m_isInverseGravity;
	bool m_isFixed;
};

