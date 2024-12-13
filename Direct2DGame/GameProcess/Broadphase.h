#pragma once

class Collider;

typedef std::pair<Collider*, Collider*> ColliderPair;
typedef std::list<ColliderPair> ColliderPairList;
typedef std::vector<Collider*> ColliderVector;

struct AABB;

/// <summary>
/// ����ĳ��Ʈ�� ���� ���
/// </summary>
struct RayCastResult
{
	bool hit;
	Collider* collider;
	Vector2 position;
	Vector2 normal;
};

/// <summary>
/// ���� �浹üũ �˰��� �������̽��̴� 
/// 
/// </summary>
class Broadphase abstract
{
public:

	// add a new AABB to the broadphase
	// ���ο� AABB�� ����
	virtual void Add(Collider* _collider) = 0;

	// ������ �ִ� AABB ����
	virtual void Remove(Collider* _collider) = 0;
	
	// update broadphase to react to changes to AABB 
	// AABB�� ������׿� �����ϵ��� broadphase�� ������Ʈ
	virtual void Update() = 0;

	// returns a list of possible colliding colliders
	// �浹 ������ �ݶ��̴� �� ��ȯ�Ѵ�
	virtual const ColliderPairList& ComputePairs() = 0;

	// returns a collider that collides with a point
	// returns null if no such collider exists
	// ���� �浹�ϴ� �浹ü�� ��ȯ�Ѵ�.
	// �׷��� �浹ü�� �������� ������ null�� ��ȯ�մϴ�.
	virtual void Pick(const Vector2& _point, ColliderVector& _colliderVector) = 0;

	// returns a list of colliders whose AABBs collide
	// with a query AABB
	// AABB�� �浹�ϴ� �浹ü ����� ��ȯ �մϴ�. ���� AABB ���
	virtual void Query(const AABB& _aabb, ColliderVector& _output) const = 0;

	// TODO:: �̿ϼ�
	virtual RayCastResult RayCast(const Vector2& _direct, const Vector2& _center, float _maxDistance = 0.f) const =0;

};
