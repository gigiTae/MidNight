#pragma once
#include <MonoBehaviour.h>

/// <summary>
///  ������ ���� ������Ʈ 
/// </summary>
class FinalAct :
    public MonoBehaviour
{
public:
    FinalAct();
    ~FinalAct();
    Component* Clone() override;

public:

    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;
    void OnMouseClicked() override;

   
private:
    bool m_isStart;
    int m_index;
    float m_ratio;
    
};
