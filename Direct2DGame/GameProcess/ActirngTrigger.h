#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// ���� Ʈ���� ����� �Ѵ�
/// 
/// �� ������Ʈ�� ������ ������Ʈ�� DirectManager���� ���� ������ �����Ѵ�.
/// 
/// </summary>
class ActirngTrigger :
    public MonoBehaviour
{
public:
    ActirngTrigger();
    ~ActirngTrigger();
    Component* Clone() override;

    
    void Set(int _actingNumber);
    void OnTriggerStay(const Collision& _collision) override;
    void DebugRender(D2DRenderer* _d2DRenderer) override;

private:
    int m_actingNumber; // �ڽ��� ���� ����
    bool m_isActive; // Ȱ��ȭ �������� 

};

