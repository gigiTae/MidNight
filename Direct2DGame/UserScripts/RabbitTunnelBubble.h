#pragma once
#include "MonoBehaviour.h"

class RabbitTunnelBubble : public MonoBehaviour
{
public:
	RabbitTunnelBubble();
	~RabbitTunnelBubble();

	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;
	/// ���� �⺻���� ������ �̺�Ʈ
	void Render(D2DRenderer* _d2DRenderer) override;
	void SetRabbitTunnel(GameObject* val) { m_rabbitTunnel = val; }

private:
	GameObject* m_rabbitTunnel;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	Vector2 m_position;
	float 	m_renderTime;
};

