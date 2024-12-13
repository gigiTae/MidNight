#pragma once

#include "MonoBehaviour.h"

class Transform;

/// <summary>
/// ���� �ý��� ������Ʈ  
/// Diretor Ŭ������ Actor�鿡�� ����� ������.
/// 
/// 2023.8.9 15:10 gitae
/// </summary>
class Actor :
    public MonoBehaviour
{
public:
    Actor();
    ~Actor();
    Component* Clone() override;

    Vector2 GetOffset() const { return m_offset; }
    void SetOffset(Vector2 _offset) { m_offset = _offset; }
    Vector2 GetTextOffset() const { return m_textOffset; }
    void SetTextOffset(Vector2 val) { m_textOffset = val; }
    Vector2 GetInverseOffset() const { return m_inverseOffset; }
    void SetInverseOffset(Vector2 val) { m_inverseOffset = val; }
private:
    void Start() override;
    void Update(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

public:
    void SetInverse(bool _isFilp) { m_isInverse = _isFilp; }
    // ��ǳ�� ��� ������ �����Ѵ�. 
    void DirectTalking(const TalkingInfomation& _info, int _actingOrder);

private: 
    Transform* m_transform;
    int m_actingOrder; // ���� ���� ���� 
    size_t m_currentIndex; // ���� ������� ���ڰ���
    bool m_isActing; // ���� ���������� 
    wstring m_outputText; // ���� ������� �ؽ�Ʈ 

    Vector2 m_scale = Vector2(360.f, 120.f);
    Vector2 m_offset; // ��ǳ�� ������
    Vector2 m_textOffset; 
    Vector2 m_inverseOffset;

    bool m_isInverse; // ��ǳ�� ��ġ ���� ���� 
    float m_elapsedTime;

    const float END_TEXT_TIME = 1.8f;

    TalkingInfomation m_talkingInfomation;

};

