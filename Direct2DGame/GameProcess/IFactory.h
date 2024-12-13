#pragma once


class GameObject;
class ManagerSet;

/// <summary>
/// ���丮�� �������̽��̴� 
/// �������̽��� ��ӹ޾Ƽ� �������� ��ü���� �ڽ� Ŭ������ �����Ѵ�.
/// 
/// �������̽��� �Լ����� �ڽ���Ŭ������ ������ �����ش�. 
/// </summary>
class IFactory 
{
public:
	IFactory() = default;
	~IFactory();

public:
	// ����⺻���� ���ӿ�����Ʈ�� �����Ѵ� ��� ���ӿ�����Ʈ�� Trasform�� ������.
	GameObject* CreateGameObject(const string& _name, const ManagerSet* _managerSet
		, OBJECT_TYPE _type, const TransformInfo& _info); 

	// �������� zero�� ��� Ʈ�������� scale ���� �޾ƿ´�.
	void CreateBoxCollider(GameObject* _object, BoxColliderInfo _info);
	
	// ���� �ݶ��̴��� �߰�
	void CreateCircleColldier(GameObject* _object, CircleInfo _intfo);

	// ������ �ٵ� �߰� 
	void CreateRigidBody(GameObject* _object, float _mass = 1.f);
	
	// �ؽ�ó �������� �߰�
	void CreateTextureRenderer(GameObject* _object
		, const wstring& _key
		, Vector2 _offset = Vector2::Zero);
	
	// UI ������Ʈ �߰�
	void CreateUI(GameObject* _object);


};

