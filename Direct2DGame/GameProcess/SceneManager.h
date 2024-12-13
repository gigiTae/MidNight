#pragma once

class GameObject;
class InputManager;
class CollisionManager;
class ManagerSet;
class Scene;
class DirectManager;

/// <summary>
/// ���� �������ִ� �Ŵ��� 
///   
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initalize(D2DRenderer* _d2DRenderer
		, ManagerSet* _managerSet
		, CollisionManager* _collisionManager
		, DirectManager* _directManager
	    , map<wstring,Scene*> _sceneContainer
		, const wstring& _startScene);

	void Finalize();

	/// �̺�Ʈ ����
	void FixedUpdate(float _fiexedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void ProcessEvent(float _deltaTime);

	Scene* GetCurrentScene()const { return m_currentScene; }
	void ChangeScene(const wstring& _sceneName);

	void RegisterObject(GameObject* _object, float _delayTime =0.f) const;
	void RegisterNextScene(const wstring& _sceneName)const;

	bool IsGameRun() { return m_gameRun; }
	void EndGame() const{ m_gameRun = false; }

	bool IsPause() const { return m_isPause; }
	void SetPause(bool _isPause)const{ m_isPause = _isPause; }
private:
	CollisionManager* m_collisionManager;
	DirectManager* m_directManager;
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;
	mutable bool m_gameRun;
	mutable bool m_isPause; 

	// ���� �̸��� �Բ� ����ִ´�.
	map<wstring, Scene*> m_sceneCotainer;
	// ��� ������ ����
	Scene* m_currentScene;
};

