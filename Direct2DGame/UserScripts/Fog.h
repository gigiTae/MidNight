#pragma once
#include "MonoBehaviour.h"

class Button;
class Fog : public MonoBehaviour
{
public:
	Fog();
	~Fog();

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
	void SetButton(GameObject* val) { 
		m_button = val; 
	}
private:
	GameObject* m_button;
	TextureRenderer* m_textureRenderer;
	Button* m_buttonConmponent;
	float m_alpha;
};

