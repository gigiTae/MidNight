#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;

/// <summary>
/// �÷��̾��� �� ȿ���� �����ִ� ������Ʈ 
/// 
/// 
/// </summary>
class FreezeEffect :
    public MonoBehaviour
{
public:
    FreezeEffect();
    ~FreezeEffect();
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    void Freeze();

private:
    float m_freezeRatio; // �󸶳� ������� 0.f~ 1.f; 0�� �������� �Ķ������� ����

    bool m_isFreezing; // �������
    float m_elapsedTime; 
    float m_freezeTime; // ���ӽð�

    Animator* m_animator;
    PlayerComponent* m_player;
    ParticleSystem* m_particleSystem;

    float m_defalutJumpPower;
    float m_defalutPlayerSpeed;
};

