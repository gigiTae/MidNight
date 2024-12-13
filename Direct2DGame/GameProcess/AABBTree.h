#pragma once

#include "Broadphase.h"
#include "AABB.h"
#include "Collider.h"
struct Node;
class CollisionManager;

/// <summary>
/// �浹 üũ �˰��� AABBTree
/// ������ �ݶ��̴��� AABB�簢������ Ȯ���ϰ�
/// Ȯ���� �簢���� m_margin��ŭ Ȯ�����Ŀ� 
/// ���������� Tree�� �����ϰ� �����Ѵ�
/// 
/// </summary>
class AABBTree :
    public Broadphase
{
public:
    AABBTree(float _margin, CollisionManager* _collisionManager);
    ~AABBTree();

    void Add(Collider* _collider) override;
    void Remove(Collider* _collider) override;
    void Update() override;
    ColliderPairList& ComputePairs() override;
    
    // ���� �浹�ϴ� �浹ü�� ��ȯ
    void Pick(const Vector2& _point, ColliderVector& _colliderVector) override;

    // �簢�� ���ο� �浹�ϴ�  Collider ��ȯ
    void Query(const AABB& _aabb, ColliderVector& _output) const override;
    
	RayCastResult RayCast(const Vector2& _direct
        , const Vector2& _center, float _maxDistance = 0.f) const override;


    // Ʈ���� �ʱ�ȭ�Ѵ�.
    void Clear();

    void DebugRender(D2DRenderer* _d2DRenderer);
private:
    typedef std::vector<Node*> NodeVector;
    void UpdateNodeHelper(Node* _node);
    void InsertNode(Node* _node, Node** _parent);
    void RemoveNode(Node* _node);
    void ComputePairsHelper(Node* _n0, Node* _n1);
    void ClearChildrenCrossFlagHelper(Node* _node);
    void CrossChildren(Node* _node);

private:
    Node* m_root; 
    ColliderPairList m_pairs;
    const float m_margin;

    CollisionManager* m_collisionManager; 
    NodeVector m_invalidNodes;
    NodeVector m_removeNodes;
};

struct Node
{
    Node() :parent(nullptr)
        , collider(nullptr)
        , children{ nullptr,nullptr } 
        , childrebCrossed(false)
        , aabb()
    {}
    
    bool IsLeaf()const
    {
        return children[0] == nullptr;
    }

    // �ڽĳ�忡 �߰�
    void SetBranch(Node* _n0, Node* _n1)
    {
        _n0->parent = this;
        _n1->parent = this;

        children[0] = _n0;
        children[1] = _n1;
    }

    // Leaf���� �����
    void SetLeaf(Collider* _collider)
    {
        this->collider = _collider;
 
        children[0] = nullptr;
        children[1] = nullptr;
    }

    void UpdateAABB(float _margin)
    {
        if (IsLeaf())
        {
            // make fat AABB
            // Ȯ���� AABB����
            const Vector2 marginVec(_margin, _margin);
            aabb.minPoint = collider->GetMinPoint() - marginVec;
            aabb.maxPoint = collider->GetMaxPoint() + marginVec;
        }
        else
        {
            // make union of child AABBs of child nodes;
            // �ڽĳ�带 �����ؼ� AABB�����
            aabb = children[0]->aabb.Union(children[1]->aabb);
        }
    }

    // ���� ��ȯ
    Node* GetSibling() const
    {
        assert(parent);
        return this == parent->children[0] ? parent->children[1] : parent->children[0];
    }


    Node* parent;
    Node* children[2];

    bool childrebCrossed;
    AABB aabb;
    Collider* collider;
}; 