
#include "EnginePCH.h"
#include "D2DEngine.h"
#include "GameProcess.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

D2DEngine::D2DEngine()
	:m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	, m_hInstance(nullptr)
	, m_gameProcess(nullptr)
{
}

D2DEngine::~D2DEngine()
{
}

void D2DEngine::Initalize(HINSTANCE _hInstance, int _nCmdShow)
{
	// ������ â �ʱ�ȭ, ���������� �ڵ� ����
	WindowInitalize(_hInstance, _nCmdShow);


	// D2D ������ �ʱ�ȭ
	m_d2DRenderer = new D2DRenderer();
	m_d2DRenderer->Initalize(m_hWnd);

	// GameProcess �ʱ�ȭ
	m_gameProcess = new GameProcess();
	m_gameProcess->Initalize(m_d2DRenderer, m_hWnd);

	// ���콺 Ŀ�� �����
	ShowCursor(FALSE);
}

void D2DEngine::Process()
{
	MSG msg;

	while (m_gameProcess->IsGameRunning())
	{
		// �ȸ޼��� �Լ��� ����ؼ� �޼����� �����Ѵ�.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			// ���� ���μ��� ����
			m_gameProcess->Process();
		};
	}
}

void D2DEngine::Finalize()
{
	m_gameProcess->Finalize();
	m_d2DRenderer->Finalize();

	delete m_gameProcess;
	delete m_d2DRenderer;
}

void D2DEngine::WindowInitalize(HINSTANCE _hInstance, int _nCmdShow)
{
	constexpr wchar_t title[] = L"MidNight";

	WNDCLASS wndclass{};
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = _hInstance;
	wndclass.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = title;

	// ������ Ŭ���� ���
	RegisterClass(&wndclass);
	
	// ������ â ������ǥ (�»�� ����)
	constexpr int left = 0;
	constexpr int top = 0;
	

	DWORD dwStyle = WS_OVERLAPPEDWINDOW; // �⺻ ������ ��Ÿ��
	DWORD dwExStyle = 0; // �⺻ Ȯ�� ������ ��Ÿ��

	// õü ȭ�� ���� ����
	dwStyle = WS_POPUP; // �˾� ��Ÿ��
	dwExStyle = WS_EX_TOPMOST; // �ֻ��� ������ ��Ÿ��

	m_hWnd = CreateWindow(title, title
		, dwStyle | dwExStyle // ��Ÿ�ϰ� Ȯ�� ��Ÿ���� �����Ͽ� ���
		, left, top, m_screenWidth, m_screenHeight
		, NULL, NULL, _hInstance, NULL);

	//// ������ â ����
	//m_hWnd = CreateWindow(title, title
	//	, WS_OVERLAPPEDWINDOW // â�� ��ħ
	//	, left, top, m_screenWidth, m_screenHeight
	//	, NULL, NULL, _hInstance, NULL);

	// ������ڵ�
	assert(m_hWnd);

	ShowWindow(m_hWnd, _nCmdShow);
	UpdateWindow(m_hWnd);

	//// ȭ���ػ󵵿� �°� window ��ǥ�踦 �����Ѵ�
	//RECT rt = { 0, 0,(long)m_screenWidth, (long)m_screenHeight };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // window ������Ÿ�Ͽ� �´� rt���� ��ȯ���ش�.
	//SetWindowPos(m_hWnd, nullptr, left, top, rt.right - rt.left, rt.bottom - rt.top, 0);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
