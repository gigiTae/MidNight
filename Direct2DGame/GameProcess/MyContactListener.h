//#pragma once
////#include "b2_world_callbacks.h"
//
//
///// <summary>
///// box2d�� �浹 �ݹ��� ����
///// </summary>
//class MyContactListener : public b2ContactListener
//{
//public:
//	void BeginContact(b2Contact* contact) override;
//	void EndContact(b2Contact* contact) override;
//
//	/*
//	* �浹 ���� ��� ���� ȣ���
//	//����(Trigger?)�� ���ؼ��� ȣ����� �ʴ´�
//	awake body�� ���ؼ��� ȣ��ȴ�.
//	contact points�� 0�� ��쿡�� ȣ��ȴ�(????)
//	contact points�� 0���� ������ ��� end contact�� ȣ����� �ʴ´�.
//	������ ���� step���� begin contact�� ȣ��ȴ�(���?)
//	Manifold�� �浹 ����, ����, ħ�� ���� ���� ������ ����ִ�.
//	*/
//	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
//
//
//	/*
//	* �浹 ���� ��� �Ŀ� ȣ���.
//	solver�� �۾��� ������ �� ȣ��ȴ�. impulse�� Ȯ���� �� ����ϸ� ����.
//	contact�� touching, solid, awake �� ��쿡�� ȣ��ȴ�. 
//	*/
//	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
//};
//
