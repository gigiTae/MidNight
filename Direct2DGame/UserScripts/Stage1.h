#pragma once
#include <Scene.h>

/// <summary>
/// ù��° ���� �÷��� �� 
/// 
/// ���� 
/// 
/// 
/// 2023.8.10 0:50 gitae
/// </summary>
class Stage1 :
    public Scene
{
public:
    Stage1();
    ~Stage1();

public:
    void Enter() override;

    const Vector2 m_mapSize{ 15500.f,2160.f };
};