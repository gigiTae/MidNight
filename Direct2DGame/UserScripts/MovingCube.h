#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// �䳢���� �и��� �ڽ�
/// 
/// </summary>
class MovingCube :
    public MonoBehaviour
{
public:
    MovingCube();
    ~MovingCube();
    Component* Clone() override;

public:
    void OnCollisionStay(const Collision& _collision) override;


private:
    float m_pushSpeed; // �̴� �ӵ�

};

