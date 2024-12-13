#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;
class RabbitComponent;

/// <summary>
/// ��� ������ �÷��� ������Ʈ
/// 
/// �߷�   : �Ʒ������� ����� �����ϰ� �������� ����� �Ұ����ϴ�.
/// ���߷� : �Ʒ������� ����� �Ұ����ϰ� �������� ����� �����ϴ�.
/// </summary>
class PassPlatform :
    public MonoBehaviour
{
public:
    PassPlatform();
    ~PassPlatform(); 
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;


    void SetPlayer(GameObject* _player) { m_player = _player; }
    void SetRabbit(GameObject* _rabbit) { m_rabbit = _rabbit; }
private:
    GameObject* m_player;
    GameObject* m_rabbit;
    PlayerComponent* m_playerComponent;
    RabbitComponent* m_rabbitComponent;
    BoxCollider* m_playerBox;
    BoxCollider* m_rabbitBox;
    BoxCollider* m_platformBox;
    
    TextureRenderer* m_renderer;

    const float OFFSET = 0.1f;
};