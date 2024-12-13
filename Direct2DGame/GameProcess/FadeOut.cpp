#include "GameProcessPCH.h"
#include "FadeOut.h"
#include "CameraManager.h"


FadeOut::FadeOut(bool _affectUI, const CameraManager* _cameraManager)
	:CameraEffect(CAMERA_EFFECT_TYPE::FADE_OUT, _affectUI,_cameraManager)
	, m_veilColor(ColorF::Black), m_alpha(0.f)
{

}

FadeOut::~FadeOut()
{

}


void FadeOut::Update(float _deltaTime)
{
	// �ð��� ����� ���� ������ �����Ѵ�. 
	float elasepTime = GetElaspedTime();
	
	float duration = GetDuration();

	elasepTime = FMath::Clamp(elasepTime + _deltaTime, 0.f, duration);
	
	// ���İ��� �ִ밡 1.f �̴�.
	m_alpha = elasepTime / duration;
	
	m_veilColor.a = m_alpha;

	SetElaspedTime(elasepTime);
	
	if (elasepTime == duration)
	{
		SetFinish(true);
	}
}

void FadeOut::Render(D2DRenderer* _d2DRenderer)
{
	const CameraManager* cameraMgr = GetCameraManager();
	Vector2 screenSize = cameraMgr->GetScreenSize();

	_d2DRenderer->DrawFillRectangle(Vector2::Zero, screenSize, m_veilColor);
}



