#pragma once
#include "MonoBehaviour.h"

class Feather : public MonoBehaviour
{
public:
	Feather();
	~Feather();
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

	void Wait();
	void Wait2Second();
	void MakeFeather();

private:
	RigidBody* m_rigidBody;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	ParticleSystem* m_particleSystem;

	Vector2 m_featherPosition;

	float m_waitTime;
	float m_deltaTime;
	float m_alpha;
	float m_wait2Second;

	bool m_isStepOn;
	bool m_isFadeOut;
	bool m_isRecreate;
};

