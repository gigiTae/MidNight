#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// �� ������ ������ ��Ÿ���� UI
/// PostRender���� �������� �Ѵ�.
/// 
/// 2023.7.16 13:25 gitae
/// </summary>
class BarUI :
    public MonoBehaviour
{
public:
    BarUI();
    ~BarUI();
    Component* Clone() override;

    void PostRender(D2DRenderer* _d2DRenderer) override;

    void SetBar(const BarUIInfo& _info);
    /// 0.f ~ 1.f�� ������ ���� ���̸� �����Ѵ�.
    void SetBarLength(float _barLen);

private:
    Vector2 m_positionOffset; // ��ü�� ������ �Ÿ�
    Vector2 m_innerBarOffset; // ���� �ٿ� �ܺ� ���� ũ�� ����
    Vector2 m_scale; // ���� ũ�� 
    float m_barLength; // ���� ���� ���� 0.f ~ 1.f ����

    D2D1::ColorF m_innerFillBarColor; // ���θ� ä��� ���� ��
    D2D1::ColorF m_innerEmptyColor; // ���ι��� ����� ���� ��
    D2D1::ColorF m_edgeColor;  // �����ڸ� ���� ��
};

