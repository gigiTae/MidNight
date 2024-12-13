#pragma once
#include <MonoBehaviour.h>


class LightWaver : public MonoBehaviour
{
public:
	LightWaver();
	~LightWaver();
	Component* Clone() override;

public:
	void Start() override;
	void Update(float _deltaTime) override;
	
private:
	Transform* m_transform;
	
	float m_amplitute;	//����
	float m_frequency;	//���ӵ�
	float m_phaseShift;	//��������
	Vector2 m_origin;		//���� ��ġ
	float m_time;		//���� �ð�
	float m_speed;		//�ӵ�
};

