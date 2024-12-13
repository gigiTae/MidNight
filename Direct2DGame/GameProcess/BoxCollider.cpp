#include "GameProcessPCH.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider()
	:Collider(typeid(this).name(), COLLIDER_TYPE::BOX)
	,m_positionOffset{}
	, m_position{}
	, m_rotation(0.f)
	, m_scale{}
	, m_isRotatable(false)
{
}

BoxCollider::~BoxCollider()
{
}

Component* BoxCollider::Clone()
{
	BoxCollider* clone = new BoxCollider();

	clone->m_currentCollision = 0;
	clone->m_isRotatable = m_rotation;
	clone->m_position = m_position;
	clone->m_rotation = m_rotation;
	clone->m_scale = m_scale;
	clone->m_positionOffset = m_positionOffset;
	clone->SetTrigger(IsTrigger());

	return clone; 
}

void BoxCollider::LateUpdate(float _deltaTime)
{
	// ������Ʈ�� ��ġ�� ���� ���� �ݶ��̴� �̵�
	Vector2 ownerPosition = GetComponent<Transform>()->GetPosition();
	m_position = ownerPosition + m_positionOffset;
	// ������Ʈ ȸ���� ���� �ݶ��̴��� ���� ȸ��
	if (m_isRotatable)
	{
		float ownerRotation = GetComponent<Transform>()->GetRotation();
		m_rotation = ownerRotation;
	}
}

void BoxCollider::DebugRender(D2DRenderer* _d2DRenderer) 
{
	Vector2 leftTop;
	leftTop.x = m_position.x + m_scale.x * 0.5f;
	leftTop.y = m_position.y + m_scale.y * 0.5f;

	Vector2 rightBottom;
	rightBottom.x = m_position.x - m_scale.x * 0.5f;
	rightBottom.y = m_position.y - m_scale.y * 0.5f;

	Vector2 postion = GetComponent<Transform>()->GetPosition();

	// �浹��Ȳ�� ���� ������
	if (!IsActive())
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Gray);
	}
	else if (GetCurrentCollison() == 0)
	{ 
		_d2DRenderer->DrawRectangle(leftTop, rightBottom,D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
	}
}

void BoxCollider::OnCollisionEnter(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		++m_currentCollision;
}

void BoxCollider::OnCollisionExit(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		--m_currentCollision;
}


void BoxCollider::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		++m_currentCollision;
}

void BoxCollider::OnTriggerExit(const Collision& _collision)
{
	if (_collision.myCollider->GetColliderType() == GetColliderType())
		--m_currentCollision;
}

bool BoxCollider::Collides(Vector2 _position)
{
	Vector2 maxPoint = GetMaxPoint();
	Vector2 minPoint = GetMinPoint();

	if (_position.x <= maxPoint.x && _position.x >= minPoint.x
		&& _position.y <= maxPoint.y && _position.y >= minPoint.y)
		return true;

	return false;
}

bool BoxCollider::Collides(CircleCollider* _circle)
{
	// �ڽ� 
	Vector2 boxPosition = GetPosition();
	Vector2 boxHalfScale = GetScale() * 0.5f;

	// ��
	Vector2 circlePoisiton = _circle->GetPosition();
	float radius = _circle->GetRadius();

	// ȸ���� �簢���� ���� �浹 -> ������ ���� ������ �����
	if (IsRotatable())
	{
		float rotation = GetRotation();
		circlePoisiton = Vector2::RotateRadian(circlePoisiton, boxPosition, -rotation);
	}

	float minBoxX = boxPosition.x - boxHalfScale.x;
	float maxBoxX = boxPosition.x + boxHalfScale.x;
	float minBoxY = boxPosition.y - boxHalfScale.y;
	float maxBoxY = boxPosition.y + boxHalfScale.y;

	// 1. ���� �簢���� ������ ��������ŭ Ȯ���ؼ� ���� �߽���ǥ�� ���ؼ� �Ǵ�
	if ((minBoxX - radius <= circlePoisiton.x && maxBoxX + radius >= circlePoisiton.x
		&& minBoxY <= circlePoisiton.y && maxBoxY >= circlePoisiton.y) ||
		(minBoxX <= circlePoisiton.x && maxBoxX >= circlePoisiton.x
			&& maxBoxY + radius >= circlePoisiton.y && minBoxY - radius <= circlePoisiton.y))
	{
		return true;
	}

	// 2. ���� ����� �簢���� ������ ��ǥ�� ����ؼ� ������ �Ÿ��� ��� 
	Vector2 boxVertex{};
	boxVertex.x = (boxPosition.x < circlePoisiton.x) ? maxBoxX : minBoxX;
	boxVertex.y = (boxPosition.y < circlePoisiton.y) ? maxBoxY : minBoxY;

	float distanceSquared = (boxVertex - circlePoisiton).LengthSquared();
	if (distanceSquared <= radius * radius)
	{
		return true;
	}

	// �浹���� ����
	return false;
}

bool BoxCollider::Collides(BoxCollider* _box)
{
	// �ڽ�
	Vector2 leftPosition = GetPosition();
	Vector2 leftScale = GetScale();

	// �ڽ�
	Vector2 rightPosition = _box->GetPosition();
	Vector2 rightScale = _box->GetScale();

	// OBB �浹ó�� 
	if (IsRotatable() || _box->IsRotatable())
	{
		// ȸ������
		float leftRotation = GetRotation();
		float rightRotation = _box->GetRotation();

		Vector2 boxToBox = rightPosition - leftPosition;

		// ������ ���μ��� ���͸� ���Ѵ�.
		Vector2 leftWidth = Vector2::RotateRadian(Vector2(leftScale.x * 0.5f, 0.f), Vector2::Zero, leftRotation);
		Vector2 leftHeight = Vector2::RotateRadian(Vector2(0.f, leftScale.y * 0.5f), Vector2::Zero, leftRotation);
		Vector2 rightWidth = Vector2::RotateRadian(Vector2(rightScale.x * 0.5f, 0.f), Vector2::Zero, rightRotation);
		Vector2 rightHeight = Vector2::RotateRadian(Vector2(0.f, rightScale.y * 0.5f), Vector2::Zero, rightRotation);

		vector<Vector2> basis{ leftWidth, leftHeight, rightWidth, rightHeight };

		for (int i = 0; i < 4; ++i)
		{ 
			float sum = 0.f;
			Vector2 normal = basis[i].GetNormalize();
			for (int j = 0; j < 4; ++j)
			{
				sum += abs(normal.Dot(basis[j]));
			}

			float distance = abs(boxToBox.Dot(normal));
			if (distance >= sum)
			{
				return false;
			}
		}
		return true;
	}
	// AABB �浹
	else
	{
 		Vector2 leftMin = leftPosition - leftScale * 0.5f;
		Vector2 leftMax = leftPosition + leftScale * 0.5f;
		Vector2 rightMin = rightPosition - rightScale * 0.5f;
		Vector2 rightMax = rightPosition + rightScale * 0.5f;

		if (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x
			&& leftMin.y <= rightMax.y && leftMax.y >= rightMin.y)
			return true;
			
	}
	return false;
}

Vector2 BoxCollider::GetMinPoint() const
{
	// OBB�� ���
	if (m_isRotatable)
	{
		assert(nullptr);
		// TODO : OBB MinPoint
	}
	// AABB
	
	return Vector2(m_position.x - m_scale.x * 0.5f
		, m_position.y - m_scale.y * 0.5f);
}

Vector2 BoxCollider::GetMaxPoint() const
{
	// OBB
	if (m_isRotatable)
	{
		assert(nullptr);
		// TODO : OBB MaxPoint
	}
	// AABB
	return Vector2(m_position.x + m_scale.x * 0.5f
		, m_position.y + m_scale.y * 0.5f);
}

