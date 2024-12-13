//#include "GameProcessPCH.h"
//#include "MyContactListener.h"
//#include "GameObject.h"
//
//void MyContactListener::BeginContact(b2Contact* contact)
//{
//	//�浹�ߤ��� �� ���� Fixture�� ������
//	b2Fixture* fixtureA = contact->GetFixtureA();
//	b2Fixture* fixtureB = contact->GetFixtureB();
//
//	//���ӿ�����Ʈ�� �����ͼ� �浹 ������ �Ѱ��ش�.
//	GameObject* gameObjectA = reinterpret_cast<GameObject*>(fixtureA->GetUserData().pointer);
//	GameObject* gameObjectB = reinterpret_cast<GameObject*>(fixtureB->GetUserData().pointer);
//
//	gameObjectA->OnBox2dCollisionEnter(gameObjectB); 
//	gameObjectB->OnBox2dCollisionEnter(gameObjectA);
//}
//
//void MyContactListener::EndContact(b2Contact* contact)
//{
//	//�浹�ߤ��� �� ���� Fixture�� ������ 
//	b2Fixture* fixtureA = contact->GetFixtureA();
//	b2Fixture* fixtureB = contact->GetFixtureB();
//
//	//���ӿ�����Ʈ�� �����ͼ� �浹 ������ �Ѱ��ش�.
//	GameObject* gameObjectA = reinterpret_cast<GameObject*>(fixtureA->GetUserData().pointer);
//	GameObject* gameObjectB = reinterpret_cast<GameObject*>(fixtureB->GetUserData().pointer);
//
//	gameObjectA->OnBox2dCollisionExit(gameObjectB);
//	gameObjectB->OnBox2dCollisionExit(gameObjectA);
//}
//
//void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
//{
//
//}
//
//
//void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
//{
//// 	//�浹�ߤ��� �� ���� Fixture�� ������
//// 	b2Fixture* fixtureA = contact->GetFixtureA();
//// 	b2Fixture* fixtureB = contact->GetFixtureB();
//// 
//// 	//���ӿ�����Ʈ�� �����ͼ� �浹 ������ �Ѱ��ش�.
//// 	GameObject* gameObjectA = reinterpret_cast<GameObject*>(fixtureA->GetUserData().pointer);
//// 	GameObject* gameObjectB = reinterpret_cast<GameObject*>(fixtureB->GetUserData().pointer);
//// 
//// 	gameObjectA->OnBox2dCollisionStay(gameObjectB);
//// 	gameObjectB->OnBox2dCollisionStay(gameObjectA);
//}
