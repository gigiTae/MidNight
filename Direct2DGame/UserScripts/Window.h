#pragma once
#include "MonoBehaviour.h"

class Window : public MonoBehaviour
{
public:
	Window();
	~Window();

	Component* Clone() override;

	/// 오브젝트가 씬에 들어가기전에 호출하는 함수
	void Start() override;
	/// 가장 기본적인 업데이트 
	void Update(float _deltaTime) override;
	/// 가장 기본적인 랜더링 이벤트
	void Render(D2DRenderer* _d2DRenderer) override;

	void PostRender(D2DRenderer* _d2DRenderer) override;
	/// 디버그 전용 랜더링 함수 F5를 온오프
	void DebugRender(D2DRenderer* _d2DRenderer) override;

	void OnCollisionStay(const Collision& _collision) override;

	void SetSwitchOn(bool val) { m_isSwitchOn = val; }
	bool GetSwitchOn()const { return m_isSwitchOn; }
	bool IsOpen() { return m_isOpen; }
	void SetClearCheck(GameObject* val) { m_clearCheck = val; }
private:
	GameObject* m_clearCheck;

	const InputManager* m_myButtonInputManager;

	// 받아온 컴포넌트
	BoxCollider* m_boxCollider;
	TextureRenderer* m_textureRenderer;

	bool m_isInputOn; // 키입력을 받는 상태 
	bool m_isSwitchOn; 
	bool m_isOpen;
};

