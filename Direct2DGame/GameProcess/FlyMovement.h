#pragma once
#include "UnitMovement.h"

/// <summary>
/// ���������� ������
/// </summary>
class FlyMovement :
    public UnitMovement
{
public:
    FlyMovement();
    ~FlyMovement();

public:
    bool Move(float _deltaTime) override;
    
};

