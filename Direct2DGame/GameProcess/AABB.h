#pragma once


class Collider;

struct AABB
{
	Vector2 minPoint;
	Vector2 maxPoint;

	AABB();
	AABB(const Vector2& _minPoint, const Vector2& _maxPoint);

	// 2���� AABB�� ����
	AABB Union(const AABB& _other)const;
	// �簢���� ���� ��ȯ  
	float GetArea()const;
	// �ݶ��̴��� Ȯ���� �簢�� ���ο� �ִ��� 
	bool Contains(Collider* _collider) const;

	bool IsCollision(const AABB& _other) const;
};

