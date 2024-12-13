//#pragma once
//#include "Component.h"
//
////
////enum class Box2D_CATEGORY
////{
////	DEFAULT =			0b0000'0000'0000'0001, //1
////	PLAYER =			0b0000'0000'0000'0010, //2
////	TILE =				0b0000'0000'0000'0100, //4
////	INTERACTOVE_ITEM =  0b0000'0000'0000'1000, //8
////	CHASER =			0b0000'0000'0001'0000, //16
////	//CHASER_BLOCKER,
////};
////
////enum class Box2D_MASK
////{
////	DEFAULT =			0b1111'1111'1111'1111, 
////	PLAYER =			0b0000'0000'0001'1101, 
////	TILE =				0b0000'0000'0000'0010,   
////	INTERACTOVE_ITEM =	0b0000'0000'0000'0010,
////	CHASER =			0b0000'0000'0000'0010,
////	//CHASER_BLOCKER,
////};
//
//
///// <summary>
///// Box2d���� ���Ǵ� body�� ���� Collider
///// </summary>
//class Box2dPolygonBody : public Component
//{
//// �����ڿ� �Ҹ��� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//public:
//	Box2dPolygonBody();
//	~Box2dPolygonBody();
//	Component* Clone() override;
//
//	void SetUp(Vector2 _scale, b2BodyType _type, bool _isTrigger, Vector2 _offset = Vector2());
//
///// �ɹ� �Լ� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//public:
//	void DebugRender(D2DRenderer* _d2DRenderer) override;
//	void Finalize() override;
//	void FixedUpdate(float _fixedDeltaTime) override;
//
//	//���� ���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	b2Body* getBody() { return m_body; }
//
//	Vector2 GetPosition() { m_body->GetPosition(); }
//
//	void SetOffset(Vector2 _offset) { m_offset = _offset; }
//	Vector2 GetOffset() { return m_offset; }
//	
//	void SetScale(Vector2 _scale) {};
//	void SetFixedRotation(bool _arg) { m_bodyDef.fixedRotation = _arg; }
//	void SetDensity(float _density) { m_fixtureDef.density = _density; }
//	void SetFriction(float _friction) { m_fixtureDef.friction = _friction; }
//	void SetRestitution(float _restitution) { m_fixtureDef.restitution = _restitution; }
//	void SetGravityScale(float _arg) { m_bodyDef.gravityScale = _arg; }
//
//	void CreateBody();
//	
//	/*
//	b2_staticBody : �������� ���� ��ü
//	b2_kinematicBody : ������ ������ ���� �ʰ� ���� ���α׷��� �� ��ü
//	b2_dynamicBody : ������ ������ �޴� ��ü
//	*/
//	void SetType(b2BodyType _type) { m_bodyDef.type = _type; };
//	void SetTrigger(bool _isTrigger) { m_fixtureDef.isSensor = _isTrigger; }
//	bool IsTrigger() const { return m_fixtureDef.isSensor; }
//
//	bool IsActive() const { return m_isActive; }
//	void SetActive(bool _isActive) { m_isActive = _isActive; }
//
//	//���� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	void SetPositionOnSimulating(Vector2 _pos) { m_body->SetTransform(b2Vec2(_pos.x * m_simulationScale, _pos.y * m_simulationScale), 0.f); }
//	void SetLinearVelocity(Vector2 _vector) { m_body->SetLinearVelocity(b2Vec2(_vector.x * m_simulationScale, _vector.y * m_simulationScale)); }
//	void SetLinearXVelocity(float _velocity);
//	void SetLinearYVelocity(float _velocity);
//	void ApplyForceToCenter(Vector2 _force)	{ m_body->ApplyForceToCenter(b2Vec2(_force.x * m_simulationScale, _force.y * m_simulationScale), true); }
//	void ApplyLinearImpulseToCenter(Vector2 _impulse)	{m_body->ApplyLinearImpulseToCenter(b2Vec2(_impulse.x * m_simulationScale, _impulse.y * m_simulationScale), true);}
//
//
//	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	///Box2d �浹 ���� �Լ�
//	void OnBox2dCollisionEnter(GameObject* _otherObj) override;
//	void OnBox2dCollisionStay(GameObject* _otherObj) override;
//	void OnBox2dCollisionExit(GameObject* _otherObj) override;
//
//private:
//	void SetMask();
//
///// �ɹ� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//private:
//	int m_currentCollision; // ���� �浹���� ����
//	vector<GameObject*> m_collidingObjs;
//
//	Vector2 m_offset;		// ��ġ ������
//	Vector2 m_position;		// ��ġ
//
//	bool m_isActive;		// �ݶ��̴��� Ȱ��ȭ ���� ����
//
//	b2Body* m_body;
//	b2BodyDef m_bodyDef;
//	b2FixtureDef m_fixtureDef;
//	
//	b2PolygonShape m_box;
//	b2MassData m_massData;
//
//	static float m_simulationScale;
//	static float m_simulationInvScale;
//
////������ ����?
//	Vector2 m_halfScale = Vector2(100,100);
//};
//
