#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// ��ȣ�ۿ� ������
/// 
/// 2023.8.8 14:18 gitae
/// </summary>
class InteractiveItem :
    public MonoBehaviour
{
public:
    InteractiveItem();
    ~InteractiveItem();
    Component* Clone() override;
    
private:
    void Update(float _deltaTime) override;
    void Start() override;

    void OnTriggerStay(const Collision& _collision) override;

public:
    bool IsActive() const { return m_isActive; }
    void SetActive(bool val) { m_isActive = val; }
    ITEM_TYPE GetItemType() const { return m_itemType; }
    void SetItemType(ITEM_TYPE _type) { m_itemType = _type; }

    /// ��ȣ�ۿ� - ������ Ÿ�Կ����� �ٸ��� ��ȣ�ۿ��Ѵ�. 
    void Interact(GameObject* _user);

private:
    void KeyProcess(GameObject* _user);
    void DoorProcess(GameObject* _user);

private:
    TextureRenderer* m_textureRenderer;
    ITEM_TYPE m_itemType; // ������ Ÿ��
    bool m_isActive; // ��ȣ�ۿ� ������ ���� ǥ��
    bool m_isDissapear; // ������� ������

    const float m_dissapearSpeed = 1.f; // ����ȭ �ӵ�
};

