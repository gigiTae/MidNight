#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// ��ǳ�� ������Ʈ  
/// 
/// Show
/// 
/// 2023.8.7 15:20 gitae
/// </summary>
class SpeechBubble :
    public MonoBehaviour
{
public:
    SpeechBubble();
    ~SpeechBubble();
    Component* Clone() override;
    
private:
    void Start() override;
    void LateUpdate(float _deltaTime) override;
    void PostRender(D2DRenderer* _d2DRenderer) override;

public:
    // ��ǳ���� ǥ���Ѵ�. 
    void ShowText(const wstring& _text, ColorF _color = ColorF::Black);
    // ��ǳ���� �ݴ´�.
    void CloseText();

public:
	Vector2 GetPosition() const { return m_position; }
	void SetPosition(Vector2 val) { m_position = val; }
    Vector2 GetOffset() const { return m_offset; }           
    void SetOffset(Vector2 val) { m_offset = val; }
    void SetXOffset(float val) { m_offset.x = val; }
    void SetYOffset(float val) { m_offset.y = val; }

	Vector2 GetTextOffset() const { return m_textOffset; }
	void SetTextOffset(Vector2 val) { m_textOffset = val; }
    void SetXTextOffset(float val) { m_textOffset.x = val; }
    
    void SetBackground(wstring _key) { m_background = _key; }
    

private:
    Vector2 m_offset; // ��ǳ�� ������
    Vector2 m_textOffset; // �ؽ�Ʈ�� ��ǳ���� ������
    Vector2 m_position; // ��ǳ�� ��ġ
    Transform* m_transform;

    bool m_isShowText;
    ColorF m_textColor;
    wstring m_text; 
    wstring m_background;
};

