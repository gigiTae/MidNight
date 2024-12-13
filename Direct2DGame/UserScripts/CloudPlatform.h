#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// �ս� �ս� ���ٴϴ� �� �����ִ� ������Ʈ
/// 
/// 
/// </summary>
class CloudPlatform :
    public MonoBehaviour
{
public:
    CloudPlatform();
    ~CloudPlatform();
    Component* Clone() override;

    void Start() override;
    void Update(float _deltaTime) override;
    
    void OnCollisionStay(const Collision& _collision) override;
    
public:
    float m_moveSpeed; // �̵��ӵ� 
    Vector2 m_startPosition;
    Vector2 m_endPosition;
    Transform* m_transform;
    bool m_positive;
};

