#pragma once
#include "MonoBehaviour.h"

class StandLightFootSwitch : public MonoBehaviour
{
public:
	StandLightFootSwitch();
	~StandLightFootSwitch();
	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;

	void OnCollisionEnter(const Collision& _collision) override;
	void OnCollisionExit(const Collision& _collision) override;
	void OnCollisionStay(const Collision& _collision) override;

	bool GetFootSwitchOn() const { return m_isFootSwitchOn; }
	void SetFootSwitchOn(bool val) { m_isFootSwitchOn = val; }
private:
	bool m_isFootSwitchOn;
	GameObject* m_lightObject;
	GameObject* m_chandlierSwich;

};

