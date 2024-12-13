#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// üũ ����Ʈ�� ����ϴ� ������Ʈ
/// 
/// 
/// 2023.8.12 23:16 gitae
/// </summary>
class CheckPoint :   public MonoBehaviour
{
public:
	CheckPoint();
	~CheckPoint();
	Component* Clone() override;
	
	void Start() override;

public:
	void OnTriggerEnter(const Collision& _collision) override;

	int GetOrder() const { return m_order; }
	void SetOrder(int _order) { m_order = _order; }
private:
	int m_order;
	Vector2 m_position;
};

