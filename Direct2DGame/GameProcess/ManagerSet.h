#pragma once

// ���漱��
class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class CameraManager;
class UIManager;
class DirectManager;
class PhysicsManager;

/// <summary>
/// �������μ��� �Ŵ������� �����ͷ� 
/// ������ �ִ� Ŭ�����̴� 
/// ��ȯ�� �׻� const�� �ϱ⶧���� 
/// const �Լ��� �ƴ� �Ŵ����Լ��� ������ �Ұ����ϰ� ����
/// </summary>
class ManagerSet
{
public:
	ManagerSet() = default;
	~ManagerSet();

	void Initalize(PathManager* _pathManager,
		InputManager* _inputManager,
		TimeManager* _timeManager,
		SceneManager* _sceneManager,
		UIManager* _UIManager,
		CollisionManager* _collisionManager,
		CameraManager* _cameraManager,
		DirectManager* _directManager
		);

	const PathManager* GetPathManager()const { return m_pathManager; }
	const InputManager* GetInputManager()const { return m_inputManager; }
	const TimeManager* GetTimeManager()const {return m_timeManager;}
	const SceneManager* GetSceneManager()const { return m_sceneManager; }
	const UIManager* GetUIManager()const { return m_UIManager; }
	const CollisionManager* GetCollisionManager()const { return m_collisionManager; }
	const CameraManager* GetCameraManager()const { return m_cameraManager; }
	const DirectManager* GetDirectManager()const { return m_directManager; }
	const PhysicsManager* GetPhysicsManager()const { return m_physicsManager; }

private:
	CameraManager* m_cameraManager;
	PathManager* m_pathManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	SceneManager* m_sceneManager;
	UIManager* m_UIManager;
	CollisionManager* m_collisionManager;
	DirectManager* m_directManager;
	PhysicsManager* m_physicsManager;
};
