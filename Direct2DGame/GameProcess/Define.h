#pragma once

class GameObject;
class Collider;

/// ===================== ������Ʈ ==============================

/// <summary>
/// ������Ʈ�� Ÿ���� ��ȣ�� �������� ��� �̺�Ʈ����
/// �켱������ ������, �ٸ��ǹ̷� ū ��ȣ�� ���� ���� ��ܿ�
/// �������Ѵ�.
/// </summary>
enum class OBJECT_TYPE
{
	BACKGROUND, // ���ȭ��

	BACKGROUND_LIGHT, // ��� ����Ʈ 

	TILE, // Ÿ�� 
	INTERACTIVE_ITEM, // ��ȣ�ۿ� ������ 
	CHASER_BLOCKER, // ���� �������� ������
	RABBIT_TUNNEL, //
	BACK_PARTICLE, //�÷��̾� �ڿ� �׷��� ��ƼŬ
	CHASER, // ����
	MIDDLE_LIGHT, // �߰� ����Ʈ
	PLAYER, // �÷��̾�

	FOG, // �Ȱ� 
	PARTICLE, // ��ƼŬ
	FINAL_LIGHT, // ������ ����Ʈ

	/* ĳ���� ���� ��µ� ��� ������Ʈ
	* TODO : �� ������Ʈ Ÿ���� ���� ������Ʈ�� ĳ���Ͱ� �������� ������������ �Ѵ�. 
	*/
	FRONT_DECO, 

	/// �Ʒ��� ������Ʈ Ÿ�Ժ��ʹ� ���콺 �̺�Ʈ�� �߻���
	BACK_UI,	/// �׻� FRONT UI���� �ڿ� �׷�����
	FRONT_UI,
	MOUSE,
	END = 32,
};


enum class OBJECT_STATE	
{
	ALIVE,
	TO_BE_DESTORYED,
	DESTORY,
};

/// <summary>
/// ������Ʈ�� ȣ�� ������ �����
/// ���� �����ϼ��� �ڷᱸ�� �ʿ��� ���ʿ� ���ĵǾ�
/// ���ӿ�����Ʈ�� ������Ʈ���� �׻� ���� ���� ������Ʈ�� ȣ���Ѵ�.
/// </summary>
enum class CALL_ORDER
{
	CAMERA_AFFECTED_LAYER,
	RIGID_BODY,
	MONO_BEHAVIOUR,
	RENDERER,
	ANIMATOR,
	TEXT,
	TRANSFORMM,
	COLLIDER,
	BOX2D_COLLIDER,
	PARTICLE_SYSTEM,
	LIGHT,
	UI
};

/// ============================= ������ ���� ====================================
enum class RENDERING_MODE
{
	PRE_RENDER,
	RENDER, 
	POST_RENDER,
};


/// =================================== ������Ʈ ���� ==============================
enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};

// ���� �⺻���� Ʈ������ ������Ʈ�� ������ �����Ѵ�.
struct TransformInfo
{
	TransformInfo() = default;
	TransformInfo(Vector2 _position, Vector2 _scale, float _rotation = 0.f)
		:position(_position), scale(_scale), rotation(_rotation)
	{}

	Vector2 position = Vector2::Zero;
	Vector2 scale = Vector2::One;
	float rotation = 0.f;
};

struct BoxColliderInfo
{
	BoxColliderInfo(Vector2 _offset = Vector2::Zero, Vector2 _scale =Vector2::Zero
		, bool _rotatable = false, bool _isTrigger = false)
		: offsetPosition(_offset),scale(_scale),rotatable(_rotatable)
		, isTrigger(_isTrigger)
	{}

	Vector2 offsetPosition;
	Vector2 scale;
	bool isTrigger; 
	bool rotatable;
};

struct CircleInfo
{
	CircleInfo(Vector2 _offset, float _radius, bool _isTrigger = false)
		:radius(_radius), positionOffset(_offset)
		,isTrigger(_isTrigger)
	{}

	bool isTrigger;
	Vector2 positionOffset = Vector2::Zero;
	float radius = 0.f;
};

// BarUI�� ����µ� �ʿ��� ������
struct BarUIInfo
{
	Vector2 positionOffset; // object�� ������ �Ÿ�
	Vector2 innerBarOffset; // ���ιٿ� �����ڸ� ���� ������
	Vector2 barScale; // ���� ũ�� 
	float barLength; // ���� ���� ���� 0.f~ 1.f
	
	D2D1::ColorF innerFillBarColor = D2D1::ColorF(ColorF::Black);  // ���θ� ä��� ���� ��
	D2D1::ColorF innerEmptyBarColor = D2D1::ColorF(ColorF::Red); // ���κ���� ���� ��
	D2D1::ColorF edgeColor = D2D1::ColorF(ColorF::White);// �ܺ� ���� ��
};

/// =================== ī�޶� ���� =========================

enum class CAMERA_EFFECT_TYPE
{
	FADE_IN,
	FADE_OUT,
	LETTERBOX,
	END,
};


// ���� Ÿ�� 
enum class ACTION_TYPE
{
	OBJECT_MOVE, // ������Ʈ �̵� ����
	OBJECT_TALK, // ������Ʈ ��� ���� 
	CAMERA_MOVE, // ī�޶� �̵� ����
	CAMERA_EFFECT_ON, // ī�޶� ����Ʈ ����
	LETTERBOX_OFF,
	WAIT_TRIGGER, // Ʈ���� ��� ����
	OFF_INPUT, // Ű�Է��� ��Ȱ��ȭ�Ѵ�.
	ON_INTPUT, // Ű�Է��� Ȱ��ȭ�Ѵ�.
};

// Actor�� ��� ����
struct TalkingInfomation
{
	wstring text; // ���
	ColorF textColor = ColorF::Black; // ��� ����
	wstring imageKey; // ��ǳ���̹��� Ű��
	float outputTempo = 0.1f; // ��� ����
};

struct MovingInfomation
{
	Vector2 distance; // �̵��Ÿ�
	float moveSpeed; // �̵� �ӵ�
	wstring playAnimationName; // ����� �ִϸ��̼� �̸� 
	
}; 


struct ActionInfomation
{
	ACTION_TYPE type; // ���� Ÿ��
	int actingOrder; // ��� ����

	string actorName; // ������Ʈ �̸� 
	TalkingInfomation talkingInfo; // ��� ����
	MovingInfomation movingInfo; // �̵� ����
	CAMERA_EFFECT_TYPE cameraEffectType =CAMERA_EFFECT_TYPE::END; // ī�޶� ȿ��

	bool isStraightAction = false; // ���ӵǴ� ��������
};
 

/// ========================= �浹 ���� =========================================

// BOX �� BOX �� �浹������ ����
enum class COLLISION_DIRECT
{
	NONE, // ������ �ٵ��̱⿡�� ����Ѵ�.
	UP, // �ڽ� �������� ���
	DOWN, //  �ڽ� �������� �ϴ�
	LEFT, // �ڽ� �������� ����
	RIGHT, // �ڽ� �������� ������
};


// �浹���� 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;
	Collider* myCollider;

	mutable COLLISION_DIRECT direct;
};

// struct Box2DCollision
// {
// 	GameObject* otherObject;
// 	
// 
// };




///  ================================== Ű�Է°��� =================================
enum class KEY_STATE
{
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,
	F1, F2, F3, F4, F5,

	LAST, //enum�� ��
};


