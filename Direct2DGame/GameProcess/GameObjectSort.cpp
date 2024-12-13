#include "GameProcessPCH.h"
#include "GameObjectSort.h"
#include "GameObject.h"
#include "Transform.h"


bool SortVectorFunction(GameObject* _left, GameObject* _right)
{
	Vector2 leftPosition = _left->GetComponent<Transform>()->GetPosition();
	Vector2 rightPosition = _right->GetComponent<Transform>()->GetPosition();

	if (leftPosition.y > rightPosition.y)
		return true;
	else if (leftPosition.y == rightPosition.y
		&& leftPosition.x < rightPosition.x)
		return true;

	return false;
}

bool SortLayerFuction(GameObject* _left, GameObject* _right)
{
	int left = _left->GetSortingLayer();
	int right = _right->GetSortingLayer();

	if (left < right)	return true;
	else				return false;

	//true�� ��� obj1�� obj2�� ��ġ�� �ٲ��.
}