#pragma once

class GameObject;
class InputManager;
class PathManager;
class SceneManager;
class TimeManager;
class UIManager;
class CollisionManager;
class CameraManager;
class ManagerSet;
class SoundManager;
class DirectManager;
class PhysicsManager;

/// <summary>
/// �������� �⺻���� �θ� Ŭ�����̴�
/// 
/// </summary>
class Component
{
public:
	Component();
	Component(CALL_ORDER _callOrder, string _name);

	virtual Component* Clone() = 0;
	virtual ~Component();

public:
	/// ���� ������Ʈ�� �߰� ������ �ѹ��� ȣ���ϴ� �Լ�
	virtual void Start() {};
	virtual void Finalize() {};
	/// �⺻���� �̺�Ʈ �Լ�
	virtual void FixedUpdate(float _fixedDeltaTime) {};
	virtual void Update(float _deltaTime) {};
	virtual void LateUpdate(float _deltaTime) {};

	/// ������Ʈ ������ ���� �Լ� 
	virtual void PreRender(D2DRenderer* _d2DRenderer) {};
	virtual void Render(D2DRenderer* _d2DRenderer) {};
	virtual void PostRender(D2DRenderer* _d2DRenderer) {};
	virtual void DebugRender(D2DRenderer* _d2DRenderer) {};

	/// �浹 ���� �Լ�
	virtual void OnCollisionStay(const Collision& _collision) {};
	virtual void OnCollisionEnter(const Collision& _collision) {};
	virtual void OnCollisionExit(const Collision& _collision) {};

	virtual void OnTriggerExit(const Collision& _collision) {};
	virtual void OnTriggerStay(const Collision& _collision) {};
	virtual void OnTriggerEnter(const Collision& _collision) {};




public:
	const ManagerSet* GetManagerSet() const;

	/// �Ŵ��� �����Լ�
	const CameraManager* GetCameraManager() const;
	const PathManager* GetPathManager() const;
	const InputManager* GetInputManager() const;
	const TimeManager* GetTimeManager() const;
	const SceneManager* GetSceneManager() const;
	const UIManager* GetUIManager() const;
	const CollisionManager* GetCollisionManager() const;
	const DirectManager* GetDirectManager() const;
	const PhysicsManager* GetPhysicsManager() const;

public:
	void SetGameObject(GameObject* _gameObject) { m_gameObject = _gameObject; }
	GameObject* GetGameObject() { return m_gameObject; }
	const string& GetName() { return m_name; }
	CALL_ORDER GetCallOrder() { return m_callOrder; }

public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

private:
	/// ������Ʈ ȣ�� ����
	const CALL_ORDER m_callOrder;
	/// ������Ʈ Ŭ������
	const string m_name;
	GameObject* m_gameObject;
};


template <typename T>
T* Component::CreateComponent()
{
	if (m_gameObject != nullptr)
	{
		return m_gameObject->template CreateComponent<T>();
	}
	return nullptr;
}

template <typename T>
T* Component::GetComponent()
{
	if (m_gameObject != nullptr)
	{
		return m_gameObject->template GetComponent<T>();
	}

	return nullptr;
}

