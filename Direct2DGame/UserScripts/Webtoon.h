#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// ���� -������Ʈ-
/// 
/// 
/// </summary>
class Webtoon :
    public MonoBehaviour
{
public:
    Webtoon();
    ~Webtoon();

    Component* Clone() override;

    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;


private:
    unsigned int m_currentIndex; // ���� ���� 
    
    bool m_isDown;
    bool m_isFinish;
    
   
   
    Vector2 m_chaserPos;
    Vector2 m_cameraPos;
    Vector2 m_girlPos;

    
};

