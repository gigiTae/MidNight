#pragma once
#include "MonoBehaviour.h"

class UIComponent : public MonoBehaviour
{
public:
	UIComponent();
	~UIComponent();
	Component* Clone() override;

	/// ������Ʈ�� ���� �������� ȣ���ϴ� �Լ�
	void Start() override;
	/// ���� �⺻���� ������Ʈ 
	void Update(float _deltaTime) override;
	/// ���� �⺻���� ������ �̺�Ʈ
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// ����� ���� ������ �Լ� F5�� �¿���
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnMouse() override;
	void OnMouseClicked() override;

	void UIFadeOut(string m_myObjectName);


private:
	string m_myObjectName; // ���콺 ���� �̺�Ʈ�� ������ ��ư�� ã�� �̸�

	// ������ ������Ʈ
	MouseEvent* m_mouseEvent;
	TextureRenderer* m_textureRenderer;
	Transform* m_transform;
	Animator* m_animator;
	// �Ŵ���
	const SceneManager* m_mySceneManager;
	const InputManager* m_myInputManager;
	const CameraManager* m_myCameraManager;
	Scene* m_scene;
	// fadeout
	bool isSwitchOn;
	float fadeAlpha;
	float m_deltaTime;

	const wchar_t* gameStartOnMouse = L"gameStartOnMouse";
	const wchar_t* crewOnMouse = L"crewOnmouse";
	const wchar_t* gameExitOnMouse = L"gameExitOnMouse";
};

