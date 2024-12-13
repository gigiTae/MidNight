#pragma once
#include "IGameProcess.h"

/// <summary>
/// ���� ������ ����ϴ� Ŭ�����̴� 
/// GameProcess ������Ʈ�� ������ �����Ѵ�. 
///
/// </summary>
class GameProcess :
	public IGameProcess
{
public:
	GameProcess();
	~GameProcess();

	void Initalize(D2DRenderer* _d2DRenderer, HWND _main) override;
	void Process() override;
	void Finalize() override;

	bool IsGameRunning() override { return m_gameRunnig; }
	void EndGame() { m_gameRunnig = false; }

private:
	bool ShowDubg();

private:
	/// ���� ���� ���μ����� �����Ǵ�
	bool m_gameRunnig;


	bool m_showDebug;	/// �̹� �����ӿ� ����� ������ ǥ���ϴ���
	float m_elapsedTime;

	HWND m_hWnd;	// ���� ������ �ڵ� 
	D2DRenderer* m_d2DRenderer;	// ������

	Vector2 m_screenSize;

	// �Ŵ��� ����
	ManagerSet* m_managerSet;

	// �Ŵ��� 
	CameraManager* m_cameraManager;
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;
	PathManager* m_pathManager;
	UIManager* m_UIManager;
	ResourceManager* m_resourceManager;
	DirectManager* m_directManager;
};
