#pragma once
#include <Component.h>


/// <summary>
/// �÷��̾ �������� ������������ ��Ŀ� ������Ʈ
/// </summary>
class FrontDeco : public Component
{
public:
	FrontDeco();
	~FrontDeco();
	Component* Clone() override;

public:
	void Update(float _deltaTime);
	void OnTriggerEnter(const Collision& _collision) override;
	void OnTriggerExit(const Collision& _collision) override;

private:
	TextureRenderer* m_textureRenderer;
	int m_state; // 0 : ����X,  1 : ���� ����, -1 : ���� ����
	const float m_alphaHold = 0.65f;
};

