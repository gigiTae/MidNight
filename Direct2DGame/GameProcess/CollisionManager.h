#pragma once

// ���漱��
class Collider;
class InputManager;
class SceneManager;
class GameObject;
class AABBTree;
union ColliderKey;


// �浹ó���� �ʿ��� ������ ������.
struct CollisionInfomation
{
	CollisionInfomation(Collider* _collider1, Collider* _collider2
		, bool _prev, bool _current)
		:collider1(_collider1)
		, collider2(_collider2)
		, prevCollision(_prev)
		, currentCollision(_current)
	{}

	Collider* collider1;
	Collider* collider2;
	
	bool prevCollision; // ���������� �浹 ����
	bool currentCollision; // ���� ������ �浹 ����
};

/// <summary>
///  �浹�� �����ϴ� �Ŵ����̴�.
/// �߰�������δ� �پ��� collider�� �����ϰ� 
/// �׿� �°� �Ŵ����� collider�� ������ ���� 
/// �浹������ �����ϰ� �������ش�.
/// </summary>
class CollisionManager
{
public:
	// ColliderID�� �߱��ϴ� �Լ�
	static unsigned int GetColliderID() { static unsigned int ID = 0; return ID++; }  

public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

	void DebugRender(D2DRenderer* _d2DRenderer);

	// �� ������Ʈ�� �浹�ϴ� Ÿ������ ��ȯ�ϴ� �Լ�
	bool IsCollisionType(Collider* _left, Collider* _right);
public:
	// ������Ʈ Ÿ�԰� Ÿ�԰��� �浹������ �Ѵ�.
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const;
	void OffCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right)const;

	// AABB Tree�� ���ο� �ݶ��̴� �߰�
	void AddColider(Collider* _collider) const;
	
	// ���� �����Ҷ�, ������ �����Ҷ� ȣ��
	void Clear();

public:
	// ���� �浹�ϴ� ��� �浹ü ��ȯ
	void DetectPointToCollider(const Vector2& _point, vector<Collider*>& _colliderVector) const;

	// �ڽ��� �浹�ϴ� ��� �浹ü�� ��ȯ�Ѵ�.
	void DetectBoxToCollider(const Vector2& _minPoint, const Vector2& _maxPoint, vector<Collider*>& _colliderVector) const;

	int GetCheckType(OBJECT_TYPE _type)const { return m_collisionCheck[static_cast<int>(_type)]; }

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// Boradphase �˰��� 
	AABBTree* m_aabbTree; 
	// ���� ������, ���� ������ �浹�������� ����
	map<ColliderKey, CollisionInfomation> m_collisionInfomations;

	// ������Ʈ Ÿ�Ժ��� �浹�� �Ǵ� const �Ŵ������� ���������ϰ� mutable�� ����
	mutable int m_collisionCheck[static_cast<int>(OBJECT_TYPE::END)];
};

