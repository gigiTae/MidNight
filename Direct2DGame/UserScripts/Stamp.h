#pragma once
#include <MonoBehaviour.h>

class PlayerComponent;

/// <summary>
/// ������ ������Ʈ 
/// 
/// �߷� ���¿����� ���� 
/// ���߷� ���¿����� �Ͼ��.
/// 
/// </summary>
class Stamp :
    public MonoBehaviour
{
public:
    Stamp();
    ~Stamp();
    Component* Clone() override;

public:
    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

    void SetPlayer(GameObject* _player) { m_player = _player; }

private:
    BoxCollider* m_boxCollider;
    GameObject* m_player;
    PlayerComponent* m_playerComponent;
    Transform* m_transform;

};

