#pragma once

#include "Collider.h"
class GameObject;
class InputManager;
struct Collision;
/// <summary>
/// �ڽ��� �ݶ��̴��̴�
/// m_rotation ���� ���� 
/// OBB, AABB �浹�� ���� ���Ѵ�.
/// </summary>
class BoxCollider :public Collider
{
public:
	BoxCollider();
	~BoxCollider();
	Component* Clone() override;

public:
	void LateUpdate(float _deltaTime) override;

	void SetPosition(Vector2 _pos) { m_position = _pos; }
	void SetOffset(Vector2 _offset) { m_positionOffset = _offset; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }
	void SetRotation(float _rotation) { m_rotation = _rotation; }
	void SetRotatble(bool _isRoatatble) { m_isRotatable = _isRoatatble; }

	Vector2 GetPosition() { return m_position; }
	Vector2 GetOffset() { return m_positionOffset; }
	Vector2 GetScale() { return m_scale; }

	// ȸ�������� ��ȯ
	float GetRotation() const { return m_rotation; }
	// ȸ�������� �ڽ����� �ƴ���
	bool IsRotatable() const { return m_isRotatable; }

	void DebugRender(D2DRenderer* _d2DRenderer);

	/// �浹ü ī��Ʈ
	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;

	void OnTriggerEnter(const Collision& _collision) override;
	void OnTriggerExit(const Collision& _collision) override;

public:
	bool Collides(Vector2 _position) override;
	bool Collides(CircleCollider* _circle) override;
	bool Collides(BoxCollider* _box) override;

public:
	Vector2 GetMinPoint()const override;
	Vector2 GetMaxPoint()const override;

private:
	Vector2 m_position;
	Vector2 m_positionOffset;
	Vector2 m_scale;

	// ȸ������ ����
	float m_rotation;

	// ȸ�������� �ڽ����� ���θ� üũ�ؼ� AABB,OBB���� ó���� ���ش�
	bool m_isRotatable;
};

