#include "GameProcessPCH.h"
#include "GameObject.h"
#include "AABBTree.h"
#include "CollisionManager.h"


AABBTree::AABBTree(float _margin, CollisionManager* _collisionManager)
	:m_margin(_margin)
	, m_root(nullptr)
	, m_invalidNodes{}
	, m_pairs{}
	,m_collisionManager(_collisionManager)
{

}

AABBTree::~AABBTree()
{
	Clear();
}

void AABBTree::Add(Collider* _collider)
{
	Node* node = new Node();
	
	// Node �� Collider ����
	_collider->SetNode(node);
	node->collider = _collider;

	if (m_root)
	{
		// not first node, insert node to tree
		node->SetLeaf(_collider);
		node->UpdateAABB(m_margin);
		InsertNode(node, &m_root);
	}
	else
	{
		// first node, make root
		m_root = node;
		m_root->SetLeaf(_collider);
		m_root->UpdateAABB(m_margin);
	}
}

void AABBTree::Update()
{
	if (m_root)
	{
		if (m_root->IsLeaf())
		{
			// ��Ʈ ��尡 ���������� ���
			if (!m_root->collider->GetGameObject()->IsAlive())
				Remove(m_root->collider);
			else
				m_root->UpdateAABB(m_margin);

		}
		else
		{
			// grab all invalid nodes
			// ��� ��ȿ���� �ʴ� ��带 �����ɴϴ�
			// ������ ������Ʈ�� �߰����� 
			m_invalidNodes.clear();
			m_removeNodes.clear();
			UpdateNodeHelper(m_root);

			// ���������� ������Ʈ�� Ʈ������ ����
			for (Node* node : m_removeNodes)
			{
				Remove(node->collider);
			}

			// re-insert all invalid nodes
			// ��ȿ���� �ʴ� ��� ��带 �ٽ� ����
			for (Node* node : m_invalidNodes)
			{
				// grab parent link
				// (pointer to the pointer that points to parent)
				// �θ� ��ũ ��� (�θ� ����Ű�� �����͸� ����Ű�� ������)
				Node* parent = node->parent;
				Node* siblibg = node->GetSibling();  
				Node** parentLink = parent->parent 
					? (parent == parent->parent->children[0]
						? &parent->parent->children[0]
						: &parent->parent->children[1])
					: &m_root;

				// replace parent with sibling
				siblibg->parent =
					parent->parent
					? parent->parent
					: nullptr; // root has null parent

				*parentLink = siblibg;
				delete parent;

				// re-insert node 
				// Ʈ���� �ٽ�Ȯ�� 
				node->UpdateAABB(m_margin);
				InsertNode(node, &m_root);
			}
			m_invalidNodes.clear();
			m_removeNodes.clear();
		}

	}
}

void AABBTree::UpdateNodeHelper(Node* _node)
{
	if (_node->IsLeaf())
	{
		GameObject* object = _node->collider->GetGameObject();
		// ���� ������ ������Ʈ
		if (!object->IsAlive())
		{
			m_removeNodes.push_back(_node);
		}
		else if (!_node->aabb.Contains(_node->collider))
		{
			// check if fat AABB dosen't contain the collider's AABB anymore
			// Ȯ���� AABB�ڽ����� �ݶ��̴��� ����� invalidNodes�� �����͸� �߰��Ѵ�
			m_invalidNodes.push_back(_node);
		}
 	}
	else
	{
		UpdateNodeHelper(_node->children[0]);
		UpdateNodeHelper(_node->children[1]);
	}
}


void AABBTree::InsertNode(Node* _node, Node** _parent)
{
	Node* p = *_parent;
	if (p->IsLeaf())
	{
		// parent is leaf, simply split
		// �θ� �������, ������ �и�
		Node* newParent = new Node();
		newParent->parent = p->parent;
		newParent->SetBranch(_node, p); 
		*_parent = newParent;
	}
	else
	{
		// parent is branch, compute volume differences
		// between pre-insert and post-insert��
		// �θ� �귣ġ�̸�, �������� ���� �������̸� ���
		const AABB aabb0 = p->children[0]->aabb;
		const AABB aabb1 = p->children[1]->aabb;

		const float volumeDiff0 = aabb0.Union(_node->aabb).GetArea() - aabb0.GetArea();
		const float volumeDiff1 = aabb1.Union(_node->aabb).GetArea() - aabb1.GetArea();

		// insert to the child that gives less volume increase;
		// ���� ������ ���� �ڽĳ�忡�� �����Ѵ�.
		if (volumeDiff0 < volumeDiff1)
			InsertNode(_node, &p->children[0]);
		else
			InsertNode(_node, &p->children[1]);
	}

	// update parent AABB
	// (propagate back up the recursion stack)
	// �θ� AABB ������Ʈ (������� ȣ��)
	(*_parent)->UpdateAABB(m_margin);
}

void AABBTree::Remove(Collider* _collider)
{
	Node* node = _collider->GetNode();
	     
	// remove two-way link
	node->collider = nullptr;
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

void AABBTree::RemoveNode(Node* _node)
{
	// replace parent with sibling, remove parent node
	Node* parent = _node->parent;
	if (parent) // node is not root
	{
		Node* sibling = _node->GetSibling();
		if (parent->parent)// if there's a grandparent
		{
			// update links 
			sibling->parent = parent->parent;
			(parent == parent->parent->children[0]
				? parent->parent->children[0]
				: parent->parent->children[1]) = sibling;
		}
		else // no grandparent 
		{
			// make sibling root
			m_root = sibling;
			sibling->parent = nullptr;
		}
		delete _node;
		delete parent;
	}
	else // node is root
	{
		m_root = nullptr;
		delete _node;
	}

}

ColliderPairList& AABBTree::ComputePairs()
{
	m_pairs.clear();

	// early out
	if (!m_root || m_root->IsLeaf())
		return m_pairs;

	// clearNode::childrenCrossed flags
	ClearChildrenCrossFlagHelper(m_root);

	// base recursive call
	// ������� ȣ��
	ComputePairsHelper(m_root->children[0], m_root->children[1]);

	return m_pairs;
 }


void AABBTree::ComputePairsHelper(Node* _n0, Node* _n1)
{
	if (_n0->IsLeaf())
	{
		// 2 leaves, check proxies instead of fat AABBs
		if (_n1->IsLeaf())
		{
			// �浹�ϴ� Ÿ������ Ȯ���ϰ�, ������ �浹�ϴ� �� Ȯ���Ѵ�
			if (m_collisionManager->IsCollisionType(_n0->collider, _n1->collider)
				&& _n0->collider->IsActive() && _n1->collider->IsActive()
				&& _n0->collider->Collides(_n1->collider)
				&& _n0->collider->GetGameObject() != _n1->collider->GetGameObject())
			{
				m_pairs.push_back(std::make_pair(_n0->collider, _n1->collider));
			}
		}
		// 1 branch / 1 leaf, 2 cross checks
		else
		{
			CrossChildren(_n1);
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputePairsHelper(_n0, _n1->children[0]);
			ComputePairsHelper(_n0, _n1->children[1]);
		}
	}
	else
	{
		// 1branch / l leaf, 2 cross checks
		if (_n1->IsLeaf())
		{
			CrossChildren(_n0);
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputePairsHelper(_n0->children[0], _n1); 
			ComputePairsHelper(_n0->children[1], _n1);
		}
		// 2 branches, 4 cross check
		else
		{
			CrossChildren(_n0);
			CrossChildren(_n1);
			
			// �ڽĳ��� Ȯ�����Ŀ� ���ΰ� �浹�ϸ� 4���� ���Ѵ�
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputePairsHelper(_n0->children[0], _n1->children[0]);
			ComputePairsHelper(_n0->children[0], _n1->children[1]);
			ComputePairsHelper(_n0->children[1], _n1->children[0]);
			ComputePairsHelper(_n0->children[1], _n1->children[1]);
		} 
	} // end of if (_n0->IsLeaf())
	
}

void AABBTree::ClearChildrenCrossFlagHelper(Node* _node)
{
	_node->childrebCrossed = false;
	if (!_node->IsLeaf())
	{
		ClearChildrenCrossFlagHelper(_node->children[0]);
		ClearChildrenCrossFlagHelper(_node->children[1]);
	}
}

void AABBTree::CrossChildren(Node* _node)
{
	if (!_node->childrebCrossed)
	{
		ComputePairsHelper(_node->children[0], _node->children[1]);
		_node->childrebCrossed = true;
	}
}

void AABBTree::Pick(const Vector2& _point, ColliderVector& _colliderVector)
{
	std::queue<Node*> q;
	
	if (m_root)
		q.push(m_root);

	while (!q.empty())
	{
		Node& node = *q.front();
		q.pop();

		if (node.IsLeaf())
		{
			// ���� �浹�ϴ� ���
			if (node.collider->Collides(_point))
				_colliderVector.push_back(node.collider);
		}
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
}

void AABBTree::Query(const AABB& _aabb, ColliderVector& _output) const
{
	_output.clear();

	std::queue<Node*> q;
	
	if (m_root)
		q.push(m_root);

	while (!q.empty())
	{
		Node& node = *q.front();
		q.pop();

		if (node.IsLeaf())
		{
	
			// AABB �浹
			Vector2 leftMax = node.collider->GetMaxPoint();
			Vector2 leftMin = node.collider->GetMinPoint();

			Vector2 rightMax = _aabb.maxPoint;
			Vector2 rightMin = _aabb.minPoint;

			if (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x
				&& leftMin.y <= rightMax.y && leftMax.y >= rightMin.y)
			{
				_output.push_back(node.collider);
			}
		}
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
	
}

RayCastResult AABBTree::RayCast(const Vector2& _direct
	, const Vector2& _center
	, float _maxDistance /*= 0.f*/) const
{
	/// �̿ϼ�
	RayCastResult result{};
	result.hit = false;
	result.collider = nullptr;
	
	queue<Node*> q;
	if (m_root)
	{
		q.push(m_root);
	}

	while (!q.empty())
	{
		Node* node = q.front();
		q.pop();

		AABB& aabb = node->aabb;
	}
	return result;
}

void AABBTree::Clear()
{
	// BFS �Ҹ� 
	queue<Node*> q;

	if (m_root)
		q.push(m_root);

	while (!q.empty())
	{
		Node* node = q.front();
		q.pop();

		if (node->children[0])
		{
			q.push(node->children[0]);
			q.push(node->children[1]);
		}
		delete node;
	}

	m_root = nullptr;
}

void AABBTree::DebugRender(D2DRenderer* _d2DRenderer)
{
	std::queue<Node*> q;

	_d2DRenderer->SetCameraAffected(true);
	if (m_root)
		q.push(m_root);
	
	while (!q.empty())
	{
		Node* node = q.front();
		q.pop();

		// ������
	
		if (node->IsLeaf())
		{
			_d2DRenderer->DrawRectangle(node->aabb.minPoint, node->aabb.maxPoint
				,D2D1::ColorF::Blue);
		}
		else
		{
			_d2DRenderer->DrawRectangle(node->aabb.minPoint, node->aabb.maxPoint);
			q.push(node->children[0]);
			q.push(node->children[1]);
		}
		
	}

}

