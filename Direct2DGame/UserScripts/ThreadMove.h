#pragma once
#include "MonoBehaviour.h"

class ThreadMove : public MonoBehaviour
{
public:
	ThreadMove();
	~ThreadMove();

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

	void OnCollisionExit(const Collision& _collision) override;
private:

	Transform* m_transform;
	RigidBody* m_rigidBody;

	Vector2 m_position;
	Vector2 m_prePosition;
	bool m_isThreadDestroy;
	bool m_isSoundStop;
};

