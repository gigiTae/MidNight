#pragma once
#include "MonoBehaviour.h"


class Button : public MonoBehaviour
{
public:
	Button();
	~Button();

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

	bool* GetInputOn() { return &m_isInputOn; }

	void OnCollisionStay(const Collision& _collision) override;

	void SetSwitchOn(bool val) { m_isSwitchOn = val; }
	bool GetSwitchOn()const { return m_isSwitchOn; }



private:
	// �޾ƿ� �Ŵ���
	const InputManager* m_myButtonInputManager;
	
	// �޾ƿ� ������Ʈ
	BoxCollider* m_boxCollider;
	TextureRenderer* m_textureRenderer;

	bool m_isInputOn; // Ű�Է��� �޴� ���� 
	bool m_isSwitchOn; // Ű�Է��� �޴� ���� 


};

