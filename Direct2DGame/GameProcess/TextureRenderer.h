#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// �ؽ�ó�� �������ϴ� ������Ʈ�̴� 
/// 
/// �ؽ�ó �������� Ű�������� �ڼ��� ������ 
/// �������� ����ִ� �����̴�.
/// </summary>
class TextureRenderer :
    public Component
{
public:
    TextureRenderer();
    ~TextureRenderer();
    Component* Clone() override;

    void Render(D2DRenderer* _d2DRenderer) override;
    void Start() override;

    void SetKey(const wstring& _key) { m_textKey = _key; }
    void SetOffset(const Vector2& _offset) { m_offset = _offset; }
    void SetXOffset(const float& _offset) { m_offset.x = _offset; }
    void SetYOffset(const float& _offset) { m_offset.y = _offset; }


    const wstring GetKey() { return m_textKey; }
    const Vector2& GetOffset() { return m_offset; }

    void SetAlpha(float _alpha) 
    {
        m_alpha = FMath::Clamp(_alpha, 0.f, 1.f); 

     }
    float GetAlpha() { return m_alpha; }

    Vector2 GetScale() const { return m_scale; }
    void SetScale(Vector2 val) { m_scale = val; }

    FLIP_TYPE GetFlipType() const { return m_flipType; }
    void SetFlipType(FLIP_TYPE val) { m_flipType = val; }
private:
    wstring m_textKey;// �������ϴ� �ؽ�Ʈ �̹��� Key��
	Vector2 m_offset;    // ������Ʈ���� ������
    Vector2 m_scale;
    float m_alpha;// ���� 
    FLIP_TYPE m_flipType; // �¿� ���� ���� Ÿ��
    Transform* m_transform;
};

