#pragma once
#include <MonoBehaviour.h>
class Icicle : public MonoBehaviour
{
public:
	Icicle();
	~Icicle();
	Component* Clone() { return nullptr; }
	void Start() override;


public:
	void Update(float _deltaTime) override;
	void OnTriggerEnter(const Collision& _collision) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	// true: ������ ���߷� ���� false ������ �߷� ����
	bool IsInverseGravity() const { return m_isInverseGravity; }
	void SetInverseGravity(bool val) { m_isInverseGravity = val; }

private:
	bool IsAffected(Vector2 candlePos, const vector<Vector2>& vertices, float distance);

private:
	TextureRenderer* m_texture;

	int m_targetCount;
	int m_currentCount;
	bool m_isMelt;
	bool m_isWorkingDone;
	bool m_isInverseGravity; // �÷��̾ �Ʒ��� ���������� ���� ����������
};

