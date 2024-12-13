#include "UserScriptsPCH.h"
#include "Stage02.h"
#include "Factory.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Chaser.h"
#include "LoadFactory.h"
#include "FireFly.h"
#include "Achievement2.h"

Stage02::Stage02()
{

}

Stage02::~Stage02()
{

}

void Stage02::Enter()
{
	const float OFFSET = 535.f;

	/// �浹 Ÿ�� ����		
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::RABBIT_TUNNEL);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FINAL_LIGHT);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::CHASER_BLOCKER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::PARTICLE);

	GetManagerSet()->GetCollisionManager()->OffCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);

	///  ============================ ���� �ý��� ===========================================
	const DirectManager* directMgr = GetManagerSet()->GetDirectManager();
	directMgr->StartStage2Scripts();   

	///  ============================ ���丮 ���� ===========================================
	Factory factory(GetManagerSet());

	/// ============================= Ŭ���� ���� üũ =======================================
	GameObject* clearCheck = factory.CreateClearCheck(6); // �к� 6�� �ѱ�
	AddObject(clearCheck);

	/// ============================= ü�¹� ==============================================
	GameObject* hp = factory.CreatePlayerLife();
	AddObject(hp);


	/// ============================= �÷��̾� ==============================================

	// �÷��̾� 
	GameObject* player = factory.CreatePlayer(Vector2(0.f, 0.f));
	// �䳢
	GameObject* rabbit = factory.CreateRabbit(Vector2(0.f, 0.f));

	// �÷��̾�� �䳢�� �����Ѵ�. 
	rabbit->GetComponent<RabbitComponent>()->SetMainPlayer(player); // ���� ���� ������Ʈ, ������ �̵�
	player->GetComponent<PlayerComponent>()->SetRabbit(rabbit);

	AddObject(player);
	AddObject(rabbit);

	/// ============================= ����ý��� Ű�Է� ���� ==================================
	directMgr->SetPlayerInputOn(player->GetComponent<PlayerComponent>()->GetInputOn());
	directMgr->SetRabbitInputOn(rabbit->GetComponent<RabbitComponent>()->GetInputOn());

	// ��
	GameObject* ground = factory.CreateGround(Vector2(0.f, -2125.f + OFFSET));
	AddObject(ground);

	// õ��
	GameObject* ceiling = factory.CreateCeiling(Vector2(0.f, -25.f + OFFSET));
	AddObject(ceiling);

	//���� ��
	GameObject* leftWall = factory.CreateWall(Vector2(-1000.f, -500.f));
	AddObject(leftWall);

	//������ ��
	GameObject* rightWall = factory.CreateWall(Vector2(14400.f, -500.f));
	AddObject(rightWall);

	/// =================================== �������� ���丮 ���� =============================
	LoadFactory loadFactory(GetManagerSet());
	loadFactory.SetPlayer(player);
	loadFactory.SetRabbit(rabbit);
	loadFactory.SetHp(hp);
	loadFactory.SetClearCheck(clearCheck);

	wstring filePath = GetManagerSet()->GetPathManager()->GetRelativPath();
	filePath += L"\\Resource\\SceneMap\\floor2 ver1.4.txt"; // �ε��� �ؽ�Ʈ ��θ� �ִ´�
	loadFactory.Load(filePath);

	vector<GameObject*>& m_container = loadFactory.GetContainer();

	for (auto object : m_container)
	{
		AddObject(object);
	}


	/// =================================== ���ȭ�� �߰� =========================================
	for (int i = 0; i < 8; ++i)
	{
		wstring key = L"floor2_BG" + std::to_wstring(i / 4 + 1);

		GameObject* background = new GameObject("background", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
		background->GetComponent<Transform>()->SetPosition(Vector2(1920.f * static_cast<float>(i)-1.f*i, 6 - 1080.f + OFFSET));
		background->CreateComponent<TextureRenderer>()->SetKey(key);
		AddObject(background);
	}

	/// ==================================== ī�޶� ���� =========================================

	/// ���� �������� ������ �� �۾����� �ʿ��մϴ�.

	float top = -550.f + OFFSET;
	float bottom = 550.f + OFFSET - 2160.f;
	float left = 0.f;

	Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();

	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MIDNIGHT);
	GetManagerSet()->GetCameraManager()->SetCameraBorder(top, bottom, 0.f, 13400.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f, -1060.f));
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);
	GetManagerSet()->GetCameraManager()->FadeInCamera(3.f, false);

	/// ====================================== UI ================================================
	GameObject* popupWindow = factory.CreatePopupWindow();
	AddObject(popupWindow);

	/// ====================================== DECO ================================================
	GameObject* fog = factory.CreateFogSystem(Vector2(1000, -1570), OBJECT_TYPE::FRONT_DECO);
	AddObject(fog);

	/// ====================================== ACHIVEMENT ================================================ 
	GameObject* achievement = new GameObject("ach2", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	achievement->SetCameraAffected(false);
	achievement->GetComponent<Transform>()->SetPosition(Vector2(0, 580));
	achievement->CreateComponent<Achievement2>();
	AddObject(achievement);

	GameObject* layer = new GameObject("layer", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);
	layer->GetComponent<Transform>()->SetPosition(Vector2(10570.f, -560.f));
	layer->SetSortingLayer(2);
	layer->CreateComponent<TextureRenderer>()->SetKey(L"���");
	AddObject(layer);


}
