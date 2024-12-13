#pragma once
#include <MonoBehaviour.h>


/// <summary>
/// �ϳ� ��ġ�� ǥ���ϴ� ������Ʈ 
/// 
/// </summary>
class CheckPosition :
    public MonoBehaviour
{
public:
    CheckPosition();
    ~CheckPosition();
    Component* Clone() override;

    void Start() override;
    void Render(D2DRenderer* _d2DRenderer) override;
public:
    bool Flip() const { return m_isFlip; }
    void SetFlip(bool val) { m_isFlip = val; }
    Vector2 m_offset;

private:
    int m_numbering;
    bool m_isFlip;
};

