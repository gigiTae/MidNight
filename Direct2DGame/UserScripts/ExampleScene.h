#pragma once
#include <Scene.h>

/// <summary>
/// ���ÿ� ��
/// </summary>
class ExampleScene : public Scene
{
public:
    ExampleScene();
    ~ExampleScene();

public:
    /// ������ ������ �����ϱ����� ȣ���ϴ� �Լ�
    void Enter() override;
};

