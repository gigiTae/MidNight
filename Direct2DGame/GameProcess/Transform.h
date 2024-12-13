#pragma once

#include "Component.h"

/// <summary>
/// ��ġ,ũ�⸦ �����ϴ� ������Ʈ�̴�
/// 
/// + �θ� �ڽİ��赵 �����Ѵ� 23.06.29
/// 
/// 
/// </summary>
class Transform : public Component
{
public:
	Transform();
	~Transform();
	Component* Clone() override;

public:
	/// �̺�Ʈ ���� �Լ�
	void LateUpdate(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	/// Ʈ������ ���� 
	void SetPosition(Vector2 _position) { m_position = _position; }
	void SetRotation(float _radian);
	void SetScale(Vector2 _scale) { m_scale = _scale; }

	void AddRotation(float _radian);
	void AddPosition(Vector2 _addPosition) { m_position += _addPosition; }

	Vector2 GetPosition() { return m_position; }
	Vector2 GetScale() { return m_scale; }
	float GetRotation() { return m_rotation; }

public:
	/// �θ� �ڽİ��� 
	GameObject* GetParent() { return m_parent; }
	
	// ��� �ڽ��� ��ȯ
	vector<GameObject*>& GetChildren() { return m_children; }
	GameObject* GetChild(int _index);
	GameObject* GetChild(const string& _name);
	
	/// �ڽ� ������Ʈ �߰�
	void AddChild(GameObject* _child);
	void SetParent(GameObject* _parent);
	 
	// �θ� ������Ʈ���� ��ġ ���̸� ����
	void SetOffset(const Vector2& _position) { m_positionOffset = _position; }
	// �θ� ������Ʈ�� ȸ�� ���̸� ����
	void SetOffset(const float& _rotation) { m_rotationOffset = _rotation; }
	
	Vector2 GetPositionOffset() { return m_positionOffset; }
	float GetRotationOffset() { return m_rotationOffset; }
private:
	// �θ�������� ��ġ�� ���� �ڽ� ������Ʈ�� ��ġ�� �����ϴ� �Լ�
	void AlignParentPosition();

private:
	Vector2 m_position;
	float m_rotation;
	Vector2 m_scale;

	// �θ� �ڽ� ���踦 Ʈ���� ������ �����Ѵ�.
	Vector2 m_positionOffset;
	float m_rotationOffset;

	GameObject* m_parent;
	vector<GameObject*> m_children;
};
