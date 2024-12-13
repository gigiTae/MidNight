#pragma once
#include "MonoBehaviour.h"

class Window : public MonoBehaviour
{
public:
	Window();
	~Window();

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

	void OnCollisionStay(const Collision& _collision) override;

	void SetSwitchOn(bool val) { m_isSwitchOn = val; }
	bool GetSwitchOn()const { return m_isSwitchOn; }
	bool IsOpen() { return m_isOpen; }
	void SetClearCheck(GameObject* val) { m_clearCheck = val; }
private:
	GameObject* m_clearCheck;

	const InputManager* m_myButtonInputManager;

	// �޾ƿ� ������Ʈ
	BoxCollider* m_boxCollider;
	TextureRenderer* m_textureRenderer;

	bool m_isInputOn; // Ű�Է��� �޴� ���� 
	bool m_isSwitchOn; 
	bool m_isOpen;
};

