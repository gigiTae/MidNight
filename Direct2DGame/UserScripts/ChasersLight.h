#pragma once
#include <MonoBehaviour.h>

/// <summary>
/// 
/// �����ڰ� ������� ���� ������ ���̻� �ȵ������ �ϴ°� 
/// ���� �߸ŷ� ������µ�
/// ���߿� ���� ������� ���� �� ����..
/// �׶� ���¿����� ���� �Ÿ����� ������� �ٲ�߰ڴ�
/// 
/// 23.08.08 �ռ���
/// </summary>

class Chaser;


///�������� �ڽ� ������Ʈ�� ���ù��� �� �Һ� ��������Ʈ�� ����
class ChasersLight : public MonoBehaviour
{
public:
	ChasersLight();
	~ChasersLight();
	
	Component* Clone();
	void SetUp(Chaser* _parent);
	void SetUpFSM(BaseFSM* _fsm) { m_fsm = _fsm; }

public:
	void Update(float _deltaTime);
	void DebugRender(D2DRenderer* _d2DRenderer);

	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerStay(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);

	void Filp();
	void SetFacingLeft();
	void SetFacingRight();
	void SetFacing(int _direction);



private:
	Vector2 m_offset;
	Transform* m_transform;
	TextureRenderer* m_texture;
	BoxCollider* m_collider;
	Chaser* m_chaserComp;
	BaseFSM* m_fsm;
	const InputManager* m_inputManager;

	bool m_isCollidingPlayer;

	Vector2 m_lastRabbitPos;

	bool m_isBright;
	const Vector2 m_defaultColliderSize = Vector2(350, 240);
	const Vector2 m_defaultColliderOffset = Vector2(0, -80);

	const Vector2 m_brightColliderSize = Vector2(490,240);
	Vector2 m_brightColliderOffset = Vector2(75, -80);

	Vector2 m_imgOffset = Vector2( -70.f,0.f);
};

