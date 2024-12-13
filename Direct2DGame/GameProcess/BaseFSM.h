#pragma once
#include "Component.h"
class BaseStatement;

/// <summary>
/// 
/// �ϴ� ������ -> ��� ���·� ���� �����ϰ� �������. ���߿� ������ ����
/// 
/// 23.08.07 �ռ���
/// </summary>


/// FSM�� �⺻ �߻� Ŭ���� 
class BaseFSM : public Component
{
///�����ڿ� �Ҹ��ڤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	BaseFSM();
	~BaseFSM();

	Component* Clone() override;
	void SetInitState(wstring _name);


///�ɹ� �Լ� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	virtual void Update(float _deltaTime);
	virtual void DebugRender(D2DRenderer* _d2DRenderer);

	void StateTransistion(wstring _key);
	void AddState(wstring _key, BaseStatement* _state) { m_allTransitions.insert({ _key, _state }); }
	wstring GetCurrentStateName();

private:
	BaseStatement* FindState(wstring _key);


///�ɹ� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
private:
	map<wstring, BaseStatement*> m_allTransitions;  //��� Transition ����
	BaseStatement* m_currentState;					//���� Trasnsition
};

