#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:m_currentCount{}
	, m_frequency{}
	, m_prevCount{}
	, m_deltaTime(0.)
{

}

TimeManager::~TimeManager()
{

}
	
void TimeManager::Initalize()
{
	// 1�ʿ� �������� ī��Ʈ�� �� �Ƹ�
	QueryPerformanceFrequency(&m_frequency); // ���μ����� ī���� ���� ��

	//����ī��Ʈ�� �޾ƿ�
	QueryPerformanceCounter(&m_prevCount); // ���� �������� ī���� ��
}

double TimeManager::Update()
{
	QueryPerformanceCounter(&m_currentCount);
	m_deltaTime = (m_currentCount.QuadPart - m_prevCount.QuadPart) / (double)m_frequency.QuadPart;

	m_prevCount = m_currentCount;

	//// TimeManager
	//static double elapsedTime = 0.;
	//elapsedTime += m_deltaTime;
	//static int fpsCount = 0;
	//fpsCount++; 

	//if (elapsedTime >= 1.)
	//{
	//fpsCount->
	//}

	return m_deltaTime;
}