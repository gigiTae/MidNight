#include "EnginePCH.h"
#include "GameProcess.h"

GameProcess::GameProcess()
	:m_collisionManager(nullptr)
	, m_sceneManager(nullptr)
	, m_inputManager(nullptr)
	, m_timeManager(nullptr)
	, m_pathManager(nullptr)
	, m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	, m_UIManager(nullptr)
	, m_elapsedTime(0.f)
	, m_gameRunnig(false)
	, m_showDebug(false)
	, m_screenSize{}
	, m_managerSet(nullptr)
	, m_cameraManager(nullptr)
	, m_resourceManager(nullptr)
	, m_directManager(nullptr)
{}

GameProcess::~GameProcess()
{

}

void GameProcess::Initalize(D2DRenderer* _d2DRenderer, HWND _main)
{
	// �ε�ȭ�� 
	m_pathManager = new PathManager();
	m_pathManager->Initalize();

	wstring filePath = m_pathManager->GetRelativPath(); filePath += L"\\Resource\\�ε�ȭ��.png";

	_d2DRenderer->LoadBitmapW(L"�ε�ȭ��", filePath.c_str());

	_d2DRenderer->BeginRender();

	_d2DRenderer->DrawBitmap(L"�ε�ȭ��", Vector2::Zero);
	_d2DRenderer->EndRender();
	

	// ���� ���� Ȱ��ȭ
	m_gameRunnig = true;

	m_d2DRenderer = _d2DRenderer;
	m_hWnd = _main;

	RECT rc{};
	// â Ŭ���̾�Ʈ ���� ��ǥ
	GetClientRect(m_hWnd, &rc);

	m_screenSize = Vector2(static_cast<float>(rc.right - rc.left), static_cast<float>(rc.bottom - rc.top));

	// �Ŵ��� �޸� ���� �Ҵ�
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();
	m_UIManager = new UIManager();
	m_cameraManager = new CameraManager();
	m_resourceManager = new ResourceManager();
	m_directManager = new DirectManager();

	// �Ŵ��� ���� Ŭ����
	m_managerSet = new ManagerSet();

	// �Ŵ����� ����
	m_managerSet->Initalize(m_pathManager, m_inputManager
		, m_timeManager, m_sceneManager, m_UIManager
		, m_collisionManager, m_cameraManager,m_directManager);

	/// ===================== �Ŵ��� �ʱ�ȭ =====================================
	// �Ŵ������� �������踦 Initalize�ܰ迡�� ǥ��
	m_timeManager->Initalize(m_screenSize);
	m_inputManager->Initalize(m_hWnd, m_cameraManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
	m_cameraManager->Initalize(m_d2DRenderer, m_screenSize, m_inputManager);
	m_UIManager->Initalize(m_sceneManager, m_managerSet);
	m_directManager->Initalize(m_screenSize, m_cameraManager);

	SoundManager::GetInstance()->Initialize();

	// ���ҽ� �ҷ����� 
	m_resourceManager->Initalize(m_pathManager, m_d2DRenderer);


	/// ======================== �� ���� ========== =============================

	// ������ �����ϰ� �������̳ʸ� ����� ���Ŵ������� �����Ѵ�.
	map<wstring, Scene*> sceneContainer{};
	 
	//// �� �޸� �Ҵ�
	//Scene* ex1 = new EX1Scene();
	//Scene* ex2 = new EX2Scene();
	//Scene* ex3 = new EX3Scene();
	//Scene* ex4 = new ���Scene();

	// MainScene
	Scene* mainScene = new MainScene();
	mainScene->SetSceneName(L"MainScene");

	// CrewScene
	Scene* crewScene = new CrewScene();
	crewScene->SetSceneName(L"CrewScene");

	// �ƾ�
	Scene* startCutScene = new StartCutScene();
	startCutScene->SetSceneName(L"StartCutScene");

	// MidNightScene
	Scene* stage1 = new Stage1();
	stage1->SetSceneName(L"Stage1");

	Scene* stage2 = new Stage02();
	stage2->SetSceneName(L"Stage2");

	Scene* stage3 = new Stage03();
	stage3->SetSceneName(L"Stage3");

	Scene* ending = new EndingScene();
	ending->SetSceneName(L"Ending");

	// �� ����Ʈ �߰� 
	sceneContainer.insert(make_pair(L"MainScene", mainScene));
	sceneContainer.insert(make_pair(L"CrewScene", crewScene));
	sceneContainer.insert(make_pair(L"StartCutScene", startCutScene));
	sceneContainer.insert(make_pair(L"Ending", ending));

	sceneContainer.insert(make_pair(L"Stage1", stage1));
	sceneContainer.insert(make_pair(L"Stage2", stage2));
	sceneContainer.insert(make_pair(L"Stage3", stage3));

	//sceneContainer.insert(std::make_pair(L"�̱���", ex1));	
	//sceneContainer.insert(std::make_pair(L"�輱��", ex2));
	//sceneContainer.insert(std::make_pair(L"�ռ���", ex3));
	//sceneContainer.insert(std::make_pair(L"�ָ��", ex4));


	// ���Ŵ������� �ʱ�ȭ�������� ����� ���۾��� �����Ѵ�.
	m_sceneManager->Initalize(_d2DRenderer, m_managerSet
		, m_collisionManager, m_directManager, sceneContainer, L"MainScene");

	// deltaTime ���� 
	m_timeManager->Update();

}

void GameProcess::Process()
{
	/// ���ӿ��� ���� �ٽ����� �κ����� 
    /// ��� ������Ʈ�� �Լ� ȣ�� ������ ��Ÿ���� �����̴�.
 
	float deltaTime = static_cast<float>(m_timeManager->Update());
	m_inputManager->Update();


	// ���� �ý��� ������Ʈ
	m_directManager->Update();

	// ==================���� ó��===================
	constexpr float FIXED_DELTA_TIME = 0.02f; // 50������ �ֱ�
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= FIXED_DELTA_TIME)
	{
		m_elapsedTime -= FIXED_DELTA_TIME;
		m_sceneManager->FixedUpdate(FIXED_DELTA_TIME);
	}
	 
	// ========== ���ӿ�����Ʈ ������Ʈ ==============
	m_sceneManager->Update(deltaTime);
	m_sceneManager->LateUpdate(deltaTime);

	//  ======== �浹ó�� ============================
	m_collisionManager->Update();

	// ============= UI �̺�Ʈ ======================	
	m_UIManager->Update();

	// ============== ī�޶� �̵� ===================
	m_cameraManager->Update(deltaTime);

	// ================= ������ ===================
	// �������� BegineRender�� EndRender ���̿� �ؾ��Ѵ�.
	m_d2DRenderer->BeginRender();

	m_sceneManager->Render(m_d2DRenderer);

	// ī�޶� ȿ�� ������ 
	m_cameraManager->Render(m_d2DRenderer);

	// ��������� ������
	if (ShowDubg())
	{
		m_timeManager->DebugRender(m_d2DRenderer);
		//m_collisionManager->DebugRender(m_d2DRenderer); // AABB Tree 
		m_sceneManager->DebugRender(m_d2DRenderer);
		m_directManager->DebugRender(m_d2DRenderer);
		m_cameraManager->DebugRender(m_d2DRenderer);

		/// �ÿ��� Ű
		if (m_inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage1");
		}
		else if (m_inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage2");
		}
		else if (m_inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		{
			m_sceneManager->RegisterNextScene(L"Stage3");
		}
	}

	m_d2DRenderer->EndRender();

	// =============== �ļ�ó�� =================
	// ex) ������Ʈ ����, �߰�, �� ����
	m_sceneManager->ProcessEvent(deltaTime);

	/// ������ ����
	m_gameRunnig = m_sceneManager->IsGameRun();
}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();
	m_UIManager->Finalize();
	m_resourceManager->Finalize();
	m_directManager->Finalize();
	SoundManager::GetInstance()->Finalize();

	NamingManager::GetInstance()->Finalize();

	// �޸� ����
	delete m_managerSet;
	delete m_cameraManager;
	delete m_sceneManager;
	delete m_pathManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;
	delete m_resourceManager;
	delete m_UIManager;
	delete m_directManager;
}

bool GameProcess::ShowDubg()
{
	if (m_inputManager->IsKeyState(KEY::F5, KEY_STATE::TAP))
	{
		m_showDebug = !m_showDebug;
	}

	return m_showDebug;
}
