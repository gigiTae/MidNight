//#pragma once
//#include "MyContactListener.h"
///// <summary>
///// box2d�� �ѹ� ���մ�.
///// 2023.08.15
///// </summary>
// 
//
/////���� ������ ����ϴ� Ŭ����. 
//class PhysicsManager
//{
/////�����ڿ� �Ҹ���
//public:
//	PhysicsManager();
//	~PhysicsManager();
//
//	void Initialize();
//
//	void Update(float _deltaTime);
//	void DebugRender(D2DRenderer* _d2dRenderer);
//	void Finalize();
//
//
/////�ɹ� �Լ�
//public:
//	//b2World* GetWorld() { return m_world; }
//	b2Body* InstanceBody(const b2BodyDef& _bodydef) const;
//	void DeleteBody(b2Body* _body) const { m_world->DestroyBody(_body); }
//
//
/////�ɹ� ����
//private:
//	b2Vec2 m_gravity; // �߷�
//	b2World* m_world;  // rigid body ������ �Ͼ�� ��.
//	MyContactListener m_listener; // �浹 �ݹ� �Լ��� ���� ��ü
//	const float m_timeStep = 1.0f / 50.f; // ���� ������ ����( 60hz ���� ) 
//	const int32 m_velocityIterations = 6;  // �ӵ� ����� ���� �ݺ� Ƚ��
//	const int32 m_positionIterations = 2;  // ��ġ ����� ���� �ݺ� Ƚ��
//};
//
