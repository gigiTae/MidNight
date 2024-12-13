#pragma once
#include "CameraEffect.h"
class FadeIn :
    public CameraEffect
{
public:
    FadeIn(bool _affectUI, const CameraManager* _cameraManager);
    ~FadeIn();

public:
    void Render(D2DRenderer* _d2DRenderer) override;
    void Update(float _deltaTime) override;
    void SetVeilColor(ColorF _color) { m_veilColor = _color; }

private:
    float m_alpha; // ���� ����
    ColorF m_veilColor; // ������ �÷� 
};

