#pragma once
#include "CameraEffect.h"

class FadeOut :
    public CameraEffect
{
public:
    FadeOut(bool _affectUI, const CameraManager* _cameraManager);
    ~FadeOut();

public:
    void Render(D2DRenderer* _d2DRenderer) override;
    void Update(float _deltaTime) override;
    void SetVeilColor(ColorF _color) { m_veilColor = _color; }

private:
    float m_alpha;  // ���� ����
    D2D1::ColorF m_veilColor; // ������ �÷� 

};

