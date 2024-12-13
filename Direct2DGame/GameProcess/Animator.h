#pragma once
#include "Component.h"

class Animation;

/// <summary>
/// �ִϸ��̼� ����� ����ϴ� ������Ʈ�̴�
/// �ִϸ����ʹ� ���������� �ִϸ��̼��� ������ �ִ� �����̴�
///
/// 
/// �̸� ������ �ִϸ��̼� ������ �д� �ʿ��غ��� -> ��Ȱ�밡�ɼ� ����
/// 
/// 20203.07.04 ���� 10�� 
/// </summary>
class Animator :
    public Component
{
public:
    Animator();
    ~Animator();

    Component* Clone() override;



    float GetTimeRatio() const { return m_timeRatio; }
    void SetTimeRatio(float val) { m_timeRatio = val; }
    bool IsShow() const { return m_isShow; }
    void SetShow(bool val) { m_isShow = val; }
    float GetAlpha() const { return m_alpha; }
    void SetAlpha(float val) { m_alpha = val; }
public:

    /// <summary>
    /// �ִϸ����Ͱ� ������ �ִϸ��̼��� ����
    /// </summary>
    /// <param name="_name">�ִϸ��̼� �̸�</param>
    /// <param name="_textureKey">�ؽ�ó Ű��</param>
    /// <param name="_startLeftTop">�ؽ�ó�� ���� �»��</param>
    /// <param name="_sliceSize">��������Ʈ �Ѱ��� ũ��</param>
    /// <param name="_sliceOffeset">��������Ʈ ����</param>
    /// <param name="_duration">�ִϸ��̼� �� �������� �ð�</param>
    /// <param name="_frameCount">��������Ʈ ����</param>
    void CreateAnimation(const wstring& _name, const wstring& _textureKey
    , Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset
    , float _duration, UINT _frameCount, FLIP_TYPE _type);

	void CreateAnimation2(const wstring& _name, const wstring& _textureKey
		, Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _sliceOffset
		, float _duration, UINT _frameCount, FLIP_TYPE _type 
        , Vector2 _nextLineOffset, int _width);


    // �ִϸ��̼� ã��
    Animation* FindAnimation(const wstring& _name);

    // �ִϸ��̼� ���
    void Play(const wstring& _name, bool _repeat);

    void LateUpdate(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;
    void Reset();
    void Reset(const wstring& _name);
    void SetFlipType(const wstring& _animation, FLIP_TYPE _type);


    // ���� ������� �ִϸ��̼� ��ȯ
    const wstring& GetCurrentAnmationName();
    

	Animation* GetCurrentAnmation() {
        return m_currentAnimation;
	}

	bool IsEffectOn() const { return m_onEffect; }
	void SetEffect(bool val) { m_onEffect = val; }
	float GetEffectRatio() const { return m_effectRatio; }
	void SetEffectRatio(float val) { m_effectRatio = val; }

    Vector2 GetOffset() { return m_offset; }
    void SetOffset(Vector2 _offset) { m_offset = _offset; }

private:
    map<wstring, Animation*> m_animations; // ��� animation ����
    Animation* m_currentAnimation; // ���� ������� �ִϸ��̼�
    bool m_repeat; // �ݺ��������
    bool m_onEffect; // ���ȿ��
    float m_effectRatio; // �󸮱� ȿ�� ���� 0.f~1.f
    float m_timeRatio;
    bool m_isShow;

    Vector2 m_offset;

    float m_alpha;
};

