#pragma once
#include "MonoBehaviour.h"


class StandLight : public MonoBehaviour
{
public:
	StandLight();
	~StandLight();

	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;
	void SetFootSwitch(GameObject* val) { m_footSwitch = val; }
private:
	bool m_isSwitchOn;
	GameObject* m_lightObject;
	GameObject* m_chandlierSwich;
	GameObject* m_footSwitch;

};

