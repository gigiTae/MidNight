#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// �÷��̾ üũ ����Ʈ�� ����ϴ� ������Ʈ 
/// 
/// 
/// </summary>
class ReturnCheckPoint :
    public MonoBehaviour
{
public:
    ReturnCheckPoint();
    ~ReturnCheckPoint();
    Component* Clone() override;

public:
    // �÷��̾ üũ ����Ʈ�� �����̵� ��Ų��.
    void ReturnToCheckPoint();
    void SetCheckPoint(Vector2 _position, int _order);

private:
    Vector2 m_checkPoint; // ���� üũ����Ʈ ��ġ 
    int m_checkPointOrder; // üũ����Ʈ ����

};

