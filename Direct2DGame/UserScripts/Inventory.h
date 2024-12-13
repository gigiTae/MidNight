#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// �÷��̾��� �κ��丮 ������Ʈ 
/// �÷��̾ �����ϰ� �ִ� �������� �����Ѵ�. 
///  
/// ������ ����Ʈ�� �������� �����Ѵ�.
/// 
/// 2023.8.8 14:26 gitae
/// </summary>
class Inventory :
    public MonoBehaviour
{
public:
    Inventory();
    ~Inventory();
    Component* Clone() override;

    bool IsActive() const { return m_active; }
    void SetActive(bool val) { m_active = val; }
public:
    // �κ��丮�� ��ȯ�Ѵ�.
    list<ITEM_TYPE>& GetInventory() { return m_itemList; }

    // ��뿡 �����ϸ� true, ��뿡 �����ϸ� false�� ��ȯ�Ѵ�.
    bool UseItem(ITEM_TYPE _type);

    // �������� �κ��丮�� �߰��Ѵ�. 
    void PusBack(ITEM_TYPE _type);

    // �������� �����Ѵ�. 
    void PassItemList(list<ITEM_TYPE>& _passed);

private:    
    list<ITEM_TYPE> m_itemList; // �κ��丮�� �Ƹ��� ����Ʈ

    bool m_active; // ������ ����Ʈ Ȱ��ȭ ���� Ȯ�� 

};

