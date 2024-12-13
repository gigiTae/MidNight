#pragma once

#include "MonoBehaviour.h"
class Unit;

/// <summary>
/// Unit�� ������ ����ϴ� Ŭ�����̴�.
/// </summary>
class UnitAttack :
    public MonoBehaviour
{
public:
    UnitAttack();
    ~UnitAttack();

public:
    void Update(float _deltaTime) override;
    void Attack(GameObject* _target);
    void Start() override;

private:
    // �ѽ�� 
    void Shoot(GameObject* _target);

private:
    float m_attackCoolTime; // ���� ��Ÿ��

    ATTACK_TYPE m_attackType;
    float m_attackSpeed;
    Unit* m_unit;
};

