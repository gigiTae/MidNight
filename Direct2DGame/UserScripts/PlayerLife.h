#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 
/// 23.08.21 �ռ���
/// </summary>


/// �÷��̾��� ü���� ���� & ǥ���ϴ� UI
class PlayerLife : public MonoBehaviour
{
public:
	PlayerLife();
	~PlayerLife();
	Component* Clone() override { return nullptr; }

public:
	void Start() override;
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer);

	UINT GetLife() { return m_remainLife; }
	void DicreaseLife();



private:
	UINT m_remainLife;
	const vector<wstring> m_texture = {L"��Ű0", L"��Ű1", L"��Ű2", L"��Ű3"};
	ParticleSystem* m_particle;
};

