#pragma once
#include <BaseStatement.h>
class Transform;
class Component;
class Chaser;
class SpeechBubble;
class PlayerLife;



enum class CHASER_STATE
{
	IDLE,		//
	TRANS,		// ���� �̵��� ����
	MOVE,		// �̵�
	FLIP,		// ���� ��ȯ
	CHASE,		// �÷��̾� �߰�
	SUSPICION,	// �ǽ�
	RETURN,		// ���� ��Ʈ�� ����
	//STAY		// ������ȯ�Ҷ� �ʿ��ϸ� �ֱ�
	OBJ_TRACE,	// ������Ʈ �ǽ�
	CAPTURE,	// ������ ���� ���¿��� �÷��̾ ������� ��
	GAMEOVER,	// ������ ���� ���� ���¿��� �÷��̾ ������� ��
	RABBIT_GAMEOVER //�䳢 ���·� ���ӿ���
};


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserIdle : public BaseStatement
{
public:
	ChaserIdle(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserIdle();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	float m_waitingTime;

};


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserMove : public BaseStatement
{
public:
	ChaserMove(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _moveSpeed);
	~ChaserMove();
	
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

	void setTargetPos(Vector2 _pos) { m_targetPos = _pos; }

private:
	Chaser* m_chaser;
	Animator* m_animator;
	Transform* m_transform;
	Vector2 m_targetPos;
	Vector2 m_lastPos;
	float m_moveSpeed;
	Vector2 m_currentPos;
	int m_direction;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserFlip : public BaseStatement
{
public:
	ChaserFlip(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserFlip();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	Chaser* m_chaser;
	Animator* m_animator;

};


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
class ChaserChase : public BaseStatement
{
public:
	ChaserChase(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _chaseSpeed);
	~ChaserChase();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

	void SetTargetObj(GameObject* _obj) { m_targetObj = _obj; }

private:
	Chaser* m_chaser;
	GameObject* m_targetObj;
	Transform* m_targetTransform;
	Transform* m_transform;
	Animator* m_animator;
	SpeechBubble* m_speechBubble;
	float m_chaseSpeed;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserSuspiction : public BaseStatement
{
public:
	ChaserSuspiction(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser);
	~ChaserSuspiction();

public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;

private:
	Chaser* m_chaser;
	Animator* m_animator;
	SpeechBubble* m_speechBubble;

	int m_count;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
class ChaserTrans : public BaseStatement
{
///�����ڿ� �Ҹ���
public:
	ChaserTrans(BaseFSM* _fsm, GameObject* _obj, wstring _nextState);
	~ChaserTrans();


///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///��� ����
private:


};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserReturn : public BaseStatement
{
///�����ڿ� �Ҹ���
public:
	ChaserReturn(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _moveSpeed);
	~ChaserReturn();


///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///��� ����
private:
	Chaser* m_chaser;
	Vector2 m_targetPos;
	Animator* m_animator;
	Transform* m_transform;
	float m_moveSpeed;
	Vector2 m_lastPos;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserObjectTrace : public BaseStatement
{
///�����ڿ� �Ҹ���
public:
	ChaserObjectTrace(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _traceSpeed);
	~ChaserObjectTrace();


///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///��� ����
private:
	Chaser* m_chaser;
	Vector2 m_targetPos;
	Animator* m_animator;
	float m_moveSpeed;
	Transform* m_transform;
	int m_direction;
	SpeechBubble* m_speechBubble;

	float minExitPosX;
	float maxExitPosX;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
class ChaserCapture : public BaseStatement
{
///�����ڿ� �Ҹ���
public:
	ChaserCapture(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserCapture();


///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


///��� ����
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserGameOver : public BaseStatement
{
	///�����ڿ� �Ҹ���
public:
	ChaserGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserGameOver();


	///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


	///��� ����
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
	GameObject* m_player;

	Transform* m_playerTransform;
	Transform* m_thisTransform;

	int m_act;
};

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class ChaserRabbitGameOver : public BaseStatement
{
	///�����ڿ� �Ҹ���
public:
	ChaserRabbitGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life);
	~ChaserRabbitGameOver();


	///��� �Լ�
public:
	void Update(float _deltaTime) override;
	void OnStateEnter() override;
	void OnStateExit() override;


	///��� ����
private:
	Chaser* m_chaser;
	PlayerLife* m_Playerlife;
	int m_direction;
	SpeechBubble* m_speechBubble;
	GameObject* m_rabbit;

	Transform* m_rabbitTransform;
	Transform* m_thisTransform;

	int m_act;
};