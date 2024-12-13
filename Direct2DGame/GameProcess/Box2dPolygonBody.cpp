//#include "GameProcessPCH.h"
//#include "Box2dPolygonBody.h"
//#include "GameObject.h"
//#include "ManagerSet.h"
//#include "PhysicsManager.h"
//#include "Transform.h"
//#include "CollisionManager.h"
//
////b2FrictionJoint
//
//float Box2dPolygonBody::m_simulationScale = 0.025f;
//float Box2dPolygonBody::m_simulationInvScale = 40.f;
//
//Box2dPolygonBody::Box2dPolygonBody()
//	:Component(CALL_ORDER::BOX2D_COLLIDER, typeid(this).name())
//	,m_currentCollision(0), m_isActive(true), m_body(nullptr)
//{	
//	/// BodyDef �ʱ�ȭ
//	m_bodyDef.type = b2_dynamicBody; // ��ü�� ���� (����, ���� ��)
//	m_bodyDef.position.Set(0.f,0.f); // �ʱ� ��ġ ���� (���� ����)
//	m_bodyDef.angle = 0.0f; // �ʱ� ���� ���� (���� ����)
//	m_bodyDef.linearVelocity.Set(0.0f, 0.0f); // �ʱ� ���ӵ� ���� (����/�� ����)
//	m_bodyDef.angularVelocity = 0.0f; // �ʱ� ���ӵ� ���� (����/�� ����)
//	m_bodyDef.linearDamping = 1.f; // ���ӵ� ���ӷ�
//	m_bodyDef.angularDamping = 0.0f; // ���ӵ� ���ӷ�
//	m_bodyDef.fixedRotation = true; // ȸ�� ���� ����
//	m_bodyDef.bullet = false; // ���� �̵�ü ó�� ����
//	//m_bodyDef.userData = static_cast<void*>(GetGameObject()); // ����� ���� ������ (��: ��ü �ĺ���
//
//
//	/// ��� �ʱ�ȭ
//	m_box.SetAsBox(m_halfScale.x * m_simulationScale
//		, m_halfScale.y * m_simulationScale); //�ʺ�����, ���� ����
//
//	/// FixtureDef �ʱ�ȭ
//	m_fixtureDef.shape = &m_box; // ��ü�� ������ ��Ÿ���� b2Shape ��ü
//	m_fixtureDef.density = 1.0f; // �е� ����
//	m_fixtureDef.friction = 0.2f; // ������ ����
//	m_fixtureDef.restitution = 0.f; // �ݹ߷�(ź��) ���� (0:���� ��ź�� �浹, 1 : ���� ź���浹)
//	m_fixtureDef.isSensor = false; // ���� ���� ����
//	
// 
//}
//
//
//
//void Box2dPolygonBody::CreateBody()
//{
//	/// �浹 ����ũ ���� <TODO>
//	SetMask();
//
//	///�浹 �ݹ��� �ޱ����� ���ӿ�����Ʈ ����
//	m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(GetGameObject());
//	
//	/// ���� �ʱ�ȭ
//	m_box.ComputeMass(&m_massData, m_fixtureDef.density);
//	
//	///body ����
//	m_body = GetManagerSet()->GetPhysicsManager()->InstanceBody(m_bodyDef);
//	m_body->CreateFixture(&m_fixtureDef);
//
//	//������ ����
//	//m_body->
//}
//
//
//
//Box2dPolygonBody::~Box2dPolygonBody()
//{
//	
//}
//
//
//
//Component* Box2dPolygonBody::Clone()
//{
//	///TODO
//	return nullptr;
//}
//
//
//
//void Box2dPolygonBody::SetUp(Vector2 _scale, b2BodyType _type, bool _isTrigger, Vector2 _offset)
//{
//	m_offset = _offset;
//	///TODO offset����ϱ�
//
//	// ��ġ �ʱ�ȭ
//	m_position = GetComponent<Transform>()->GetPosition();
//	m_bodyDef.position.Set(m_position.x * m_simulationScale
//		, m_position.y * m_simulationScale);
//	
//	// ũ�� �ʱ�ȭ
//	m_halfScale = _scale * 0.5;
//	m_box.SetAsBox(m_halfScale.x * m_simulationScale
//		, m_halfScale.y * m_simulationScale);
//
//	m_bodyDef.type = _type;
//	m_fixtureDef.isSensor = _isTrigger;
//}
//
//void Box2dPolygonBody::DebugRender(D2DRenderer* _d2DRenderer)
//{
//	Vector2 centerPos = GetComponent<Transform>()->GetPosition();
//
//	Vector2 leftTop = Vector2(centerPos.x - m_halfScale.x, centerPos.y + m_halfScale.y);
//	Vector2 rightBottom = Vector2(centerPos.x +  m_halfScale.x, centerPos.y - m_halfScale.y);
//
//	if(m_currentCollision == 0)
//		_d2DRenderer->DrawRectangle(leftTop,rightBottom,D2D1::ColorF::PaleGreen);
//	else
//		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
//}
//
//
//void Box2dPolygonBody::Finalize()
//{
//	GetManagerSet()->GetPhysicsManager()->DeleteBody(m_body);
//}
//
//void Box2dPolygonBody::FixedUpdate(float _fixedDeltaTime)
//{
//	assert(m_body != nullptr || !L"\n�� ���� �� CreateBody�� ���ּ���!! �ݴ� ������ �ȵ�");
//
//	//body postion -> transform 
//	Vector2 centerPos;
//	centerPos.x = m_body->GetPosition().x * m_simulationInvScale;
//	centerPos.y = m_body->GetPosition().y * m_simulationInvScale;
//
//	GetComponent<Transform>()->SetPosition(centerPos);
//
//
//	//���ӿ�����Ʈ�� �浹������ �˸�
//	for (auto obj : m_collidingObjs)
//	{
//		GetGameObject()->OnBox2dCollisionStay(obj);
//	}
//
//	// 	///�׽�Ʈ��
//	// 	if (GetGameObject()->GetName() == "ground")
//	// 	{
//	// 		Vector2 pos = GetComponent<Transform>()->GetPosition();
//	// 		pos += Vector2(200, 0) * _deltaTime;
//	// 		SetPositionOnSimulating(pos);
//	// 	}
//}
//
//void Box2dPolygonBody::SetLinearXVelocity(float _velocity)
//{
//	b2Vec2 velocity = m_body->GetLinearVelocity();
//	velocity.x = _velocity;
//	m_body->SetLinearVelocity(b2Vec2(velocity.x * m_simulationScale, velocity.y));
//}
//
//void Box2dPolygonBody::SetLinearYVelocity(float _velocity)
//{
//	b2Vec2 velocity = m_body->GetLinearVelocity();
//	velocity.y = _velocity;
//	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y * m_simulationScale));
//}
//
//void Box2dPolygonBody::OnBox2dCollisionEnter(GameObject* _otherObj)
//{
//	m_currentCollision++;
//	m_collidingObjs.push_back(_otherObj);
//}
//
//void Box2dPolygonBody::OnBox2dCollisionStay(GameObject* _otherObj)
//{
//	
//}
//
//void Box2dPolygonBody::OnBox2dCollisionExit(GameObject* _otherObj)
//{
//	m_currentCollision--;
//	remove(m_collidingObjs.begin(), m_collidingObjs.end(), _otherObj);
//}
//
//void Box2dPolygonBody::SetMask()
//{
//	OBJECT_TYPE type = GetGameObject()->GetObjectType();
//	unsigned int bits = 1 << (static_cast<int>(type));
//	unsigned int maskBits = GetCollisionManager()->GetCheckType(type);
//
//	m_fixtureDef.filter.categoryBits = bits; // �浹 ���� ���� ����
//	m_fixtureDef.filter.maskBits = maskBits; // �浹 ���� ����ũ ����
//	m_fixtureDef.filter.groupIndex = 0; // �浹 �׷� ����
//}
