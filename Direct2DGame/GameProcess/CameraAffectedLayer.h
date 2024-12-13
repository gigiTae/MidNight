#pragma once
class D2DCamera;
class Transform;


/// <summary>
/// 
/// 2023 08 12 �ռ���
/// </summary>

///ī�޶�(����)�� ������ �޾� ��ġ���� �������ִ� ������Ʈ
#include "Component.h"
class CameraAffectedLayer : public Component
{
/// �����ڿ� �Ҹ���  ===================================================================
public:
	CameraAffectedLayer();
	~CameraAffectedLayer();

	Component* Clone() override;

	void Start() override;

///�ɹ� �Լ�  =========================================================================
public:
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	void DebugRender(D2DRenderer* _d2DRendere) override;

	void SetDepth(float _depth) { m_depth = _depth; }
	float getDepth() { return m_depth; }


///�ɹ� ����  =========================================================================
private:
	D2DCamera* m_camera;
	const CameraManager* m_cameraManager;
	Transform* m_transform;
	float m_depth; //ī�޶� ������ �޴� ���� ( 0 : ������ ���� ����, 1 : ī�޶�� ���� ������)

	bool m_isReady;
	float m_timer;
};

