#pragma once

class Animator;

struct Frame
{
	Vector2 leftTop; // �»�� ��ǥ
	Vector2 slice; 
	Vector2 offset;
	FLIP_TYPE flipType;
	float duration;
};


/// <summary>
/// �ִϸ��̼� ������ �����ϴ� Ŭ�����̴�
/// 
/// Animation�� ���� Animator�� �������� ����� ��������
/// 
/// </summary>
class Animation
{
public:
	Animation();
	~Animation();
	
	Animation(const Animation& _other);

public:
	bool IsFinish() { return m_finish; }
	void SetFrame(int _index)
	{
		m_finish = false;
		m_currentFrame = _index;
		m_elapsedTime = 0.f;
	}

	Frame& GetFrame(int _index) { return m_frames[_index]; }
	size_t GetMaxFrame() { return m_frames.size(); }

public: 
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer, bool _onEffect, float _ratio, float _alpha);
	void SetAnimator(Animator* _animator) { m_animator = _animator; }
	void SetFlipType(FLIP_TYPE _type);

	// �ִϸ��̼� ���� ����
	void Create(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop
		, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type);

	// �ִϸ��̼� ���� ����
	void Create2(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop
		, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount, FLIP_TYPE _type
	, Vector2 _nextLineOffSet, int _width);


public:
	const wstring& GetName() {return m_name;}

private:
	wstring m_name; // �ִϸ��̼� �̸�
	wstring m_textureKey; // �ؽ�ó Ű��
	Animator* m_animator; // �ִϸ��̼��� �����ϰ� �ִ� �ִϸ�����
	vector<Frame> m_frames; // ��� ������ ����
	int m_currentFrame; // ���� ������ �ε���
	float m_elapsedTime; 
	bool m_finish; // ����� ������
};

