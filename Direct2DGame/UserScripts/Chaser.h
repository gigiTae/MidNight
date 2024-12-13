#pragma once
#include <MonoBehaviour.h>
/// <summary>
/// 
/// FSM�� ��ôµ� �̰Ը³�
/// �׳� �ڵ尡 ������Ͽ� ���ֳ� ���̰�����!!
/// 
/// ���¸� Enum���� ���� ���Ұ� ������ 
/// �׷��� �Ϸ��� BaseFSM�� ��ӹ��� ���𰡸� ����� ����Ѵ�
/// 
/// 2023.08.08 �ռ���
/// </summary>

class ChasersLight;
class BaseFSM;
class PlayerLife;
class SpeechBubble;
class ClearCheck;

///�÷��̾ �����ϴ� �༮
class Chaser : public MonoBehaviour
{
///�����ڿ� �Ҹ��� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	Chaser();
	~Chaser();
	Component* Clone();

	void SetUp(vector<Vector2> _nodes, UINT _startNode, UINT _direction, GameObject* _life, ClearCheck* _clear);
	void SetInverse();

	int GetNumbering() const { return m_numbering; }
	void SetNumbering(int val) { m_numbering = val; }
	/// �ɹ� �Լ� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	void Update(float _deltaTime);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);

	void FlipNodeDirection() { m_nodeDirection *= -1; }
	int GetNodeDirection() { return m_nodeDirection; }

	void SetFacingDirection(int _direction);
	void FlipFacingDirection() { m_facingDirection *= -1; }
	int GetFacingDirection() { return m_facingDirection; }	

	UINT GetNodeEndIndex() { return m_nodeEndIndex; }
	void SetTargetNode(UINT _node) { m_targetNode = _node; }
	UINT GetTargetNode() { return m_targetNode; }
	Vector2 GetTargetPos() { return m_nodes[m_targetNode]; }
	ChasersLight* GetLight() { return m_light; }
	
	GameObject* GetChasingPlayerObj() { return m_chasingPlayerObj; }
	void SetChasingPlayerObj(GameObject* _obj) { m_chasingPlayerObj = _obj; }

	GameObject* GetChasingInGameObj() { return m_chasingInGameObj; }
	void SetChasingInGameObj(GameObject* _obj) { m_chasingInGameObj = _obj; }

	GameObject* GetPlayerObj() { return m_player; }
	GameObject* GetRabbitObj() { return m_rabbit; }

	bool IsBlocked() { return m_isBlocked; }

	void ObjectSuspictionCallback(GameObject* _obj);
	void SetIgnorePlayer(float _time) { m_isIgnorePlayer = true; m_ignoreTime = _time; }
	bool IsIngoringPlayer() { return m_isIgnorePlayer; }

	bool IsInverse() { return m_isInverse; }
	bool IsBright() { return m_isBright; }
	bool IsGameClear() { return m_isGameClear; }

///�ɹ� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
protected:
	vector<Vector2> m_nodes;	// �̵� ��� ( �� -> �� ���� )
	UINT m_nodeEndIndex;		// ����� ������ �ε���
	UINT m_targetNode;			// �������� �̵��� ���
	
	int m_nodeDirection;		// ���� ��� �̵� ���� (1 : ->) (-1 : <-)
	int m_facingDirection;		// ���� �ٶ󺸴� ����

	float m_moveSpeed;			// ��ȸ �ӵ�
	float m_traceSpeed;			// ���� �ӵ�

	SpeechBubble* m_bubble;		// ��ǳ��
	Animator* m_animator;		// �ִϸ�����
	ChasersLight* m_light;		// �ڽĿ�����Ʈ�� light ������Ʈ
	BaseFSM* m_fsm;				// fsm
	GameObject* m_chasingPlayerObj;
	GameObject* m_chasingInGameObj;
	PlayerLife* m_playerLife;
	ClearCheck* m_clearCheck;

	bool m_isBlocked;			// ���� �����ִ°�(���� ���ΰ�)

	bool m_isIgnorePlayer;		// �÷��̾ ������ �ð�
	float m_ignoreTimer;		
	float m_ignoreTime;			

	bool m_isInverse;			// ���߷� �ϳ��ΰ�
	bool m_isBright;			// �ݵ����� or ���鸮�� �����ΰ�
	bool m_isGameClear;

	int m_numbering;
	GameObject* m_player;
	GameObject* m_rabbit;
};


//FireFly
//Chandlier