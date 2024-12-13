#pragma once
#include "MonoBehaviour.h"

class Chandlier;
class ChandlierSwich : public MonoBehaviour
{
public:
	ChandlierSwich();
	~ChandlierSwich();

	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionStay(const Collision& _collision) override;
	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;
	void SetChandlier(GameObject* val) { m_chandlier = val; }

	void SetShow(bool val) { m_isShow = val; }
private:
	bool m_isLightOn;
	bool m_isSwitchOn;
	bool m_isRabbit;
	bool m_isShow;

	const InputManager* m_inputManager;

	GameObject* m_chandlier;
	GameObject* m_light;
	TextureRenderer* m_textureRenderer;
	ParticleSystem* m_psSwitch;
};

