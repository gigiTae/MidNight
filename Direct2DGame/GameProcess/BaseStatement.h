#pragma once


class BaseFSM;
class GameObject;

/// <summary>
/// 
/// 23.08.07 �ռ���
/// </summary>


/// FSM�� �� ���¸� �����ϴ� �߻� Ŭ����
class BaseStatement
{
///�����ڿ� �Ҹ��� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	BaseStatement(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~BaseStatement() {};

/// �ɹ� �Լ� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	virtual void Update(float _deltaTime) {};

	virtual void OnStateEnter() {};
	virtual void OnStateExcution() {};
	virtual void OnStateExit() {};

	wstring getNext()			{ return m_nextState; }
	void SetNext(wstring _next)	{ m_nextState = _next; }

	bool isLoop()						{ return m_isLoop; }
	void setLoop(bool _arg)				{ m_isLoop = _arg; }

	wstring getName()					{ return m_name; }


/// �ɹ� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
protected:
	wstring m_name;  //���������� ���� 
	BaseFSM* m_fsm;
	GameObject* m_gameObject;

	float m_timer;
	bool m_isLoop;
	wstring m_nextState;

};





