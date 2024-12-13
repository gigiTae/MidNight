#include "UserScriptsPCH.h"
#include "Stage1.h"
#include "Factory.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Chaser.h"
#include "LoadFactory.h"
#include "FireFly.h"
#include "TutorialKey.h"
#include "Achievement1.h"

Stage1::Stage1()
{

}

Stage1::~Stage1()
{

}

void Stage1::Enter()
{
	const float OFFSET = 535.f;

	/// �浹 Ÿ�� ����		
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FINAL_LIGHT);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::CHASER_BLOCKER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::PARTICLE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::RABBIT_TUNNEL);

	///  ============================ ���� �ý��� ===========================================
	const DirectManager* directMgr = GetManagerSet()->GetDirectManager();
	directMgr->StartStage1Scripts();


	///  ============================ ���丮 ���� ===========================================
	Factory factory(GetManagerSet());

	/// ============================= Ŭ���� ���� üũ =======================================
	GameObject* clearCheck = factory.CreateClearCheck(4); // â�� 4�� ����
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
	GameObject* ground = factory.CreateGround(Vector2(0.f,-2125.f+ OFFSET));
	AddObject(ground);

	// õ��
	GameObject* ceiling = factory.CreateCeiling(Vector2(0.f, -25.f+ OFFSET));
	AddObject(ceiling);

	//���� ��
	GameObject* leftWall = factory.CreateWall(Vector2(-1000.f, -500.f));
	AddObject(leftWall);

	//������ ��
	GameObject* rightWall = factory.CreateWall(Vector2(11520.f, -500.f));
	AddObject(rightWall);
	
	/// =================================== �������� ���丮 ���� =============================
	LoadFactory loadFactory(GetManagerSet());
	loadFactory.SetPlayer(player);
	loadFactory.SetRabbit(rabbit);
	loadFactory.SetHp(hp);
	loadFactory.SetClearCheck(clearCheck);

	wstring filePath = GetManagerSet()->GetPathManager()->GetRelativPath();
	filePath += L"\\Resource\\SceneMap\\floor3 ver1.4.txt"; /// �ε��� �ؽ�Ʈ ��θ� �ִ´�
	loadFactory.Load(filePath);

	vector<GameObject*>& m_container = loadFactory.GetContainer();

	for (auto object : m_container)
	{
		AddObject(object);
	}


	/// =================================== ���ȭ�� �߰� =========================================
	for (int i = 0; i < 8; ++i)
	{
		wstring key = L"background" + std::to_wstring(i/4+1);
		
		GameObject* background = new GameObject("background", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
		background->GetComponent<Transform>()->SetPosition(Vector2(1920.f*static_cast<float>(i) - 1.f * i,6 -1080.f+ OFFSET));
		background->CreateComponent<TextureRenderer>()->SetKey(key);
		AddObject(background);
	}

	/// ==================================== ī�޶� ���� =========================================

	/// ���� �������� ������ �� �۾����� �ʿ��մϴ�.

	float top = -550.f + OFFSET;
	float bottom = 550.f + OFFSET -2160.f;
	float left = 0.f;

	Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();

	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MIDNIGHT);
	GetManagerSet()->GetCameraManager()->SetCameraBorder(top, bottom, 0.f, 10480.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f,-1060.f));
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);
	GetManagerSet()->GetCameraManager()->FadeInCamera(3.f, false);

	/// ====================================== UI ================================================
	GameObject* popupWindow =  factory.CreatePopupWindow();
	AddObject(popupWindow);


	/// ====================================== DECO ================================================
	GameObject* fog = factory.CreateFogSystem(Vector2(1000,-1570), OBJECT_TYPE::FRONT_DECO);
	AddObject(fog);



	/// ==================================== Ʃ�丮�� ==============================================
	GameObject* moveBtn = new GameObject("MoveBtn", GetManagerSet(), OBJECT_TYPE::MIDDLE_LIGHT);
	moveBtn->GetComponent<Transform>()->SetPosition(Vector2(0.f, -1200.f));
	moveBtn->CreateComponent<TextureRenderer>()->SetKey(L"�̵�");
	moveBtn->CreateComponent<TutorialKey>()->SetPlayer(player);
	AddObject(moveBtn);

	GameObject* spaceBtn = new GameObject("spaceBtn", GetManagerSet(), OBJECT_TYPE::MIDDLE_LIGHT);
	spaceBtn->GetComponent<Transform>()->SetPosition(Vector2(990.f, -1200.f));
	spaceBtn->CreateComponent<TextureRenderer>()->SetKey(L"����");
	spaceBtn->CreateComponent<TutorialKey>()->SetPlayer(player);
	AddObject(spaceBtn);

	GameObject* upDownbtn = new GameObject("updownBtn", GetManagerSet(), OBJECT_TYPE::MIDDLE_LIGHT);
	upDownbtn->GetComponent<Transform>()->SetPosition(Vector2(2000.f, -1200.f));
	upDownbtn->CreateComponent<TextureRenderer>()->SetKey(L"�ȱ� ����");
	upDownbtn->CreateComponent<TutorialKey>()->SetPlayer(player);
	AddObject(upDownbtn);


	GameObject* rBtn = new GameObject("reverseBtn", GetManagerSet(), OBJECT_TYPE::MIDDLE_LIGHT);
	rBtn->GetComponent<Transform>()->SetPosition(Vector2(3550.f, -1000.f));
	rBtn->CreateComponent<TextureRenderer>()->SetKey(L"���߷�");
	rBtn->CreateComponent<TutorialKey>()->SetPlayer(player);
	AddObject(rBtn);

	GameObject* eBtn = new GameObject("eBtn", GetManagerSet(), OBJECT_TYPE::MIDDLE_LIGHT);
	eBtn->GetComponent<Transform>()->SetPosition(Vector2(4600.f, -600.f));
	eBtn->CreateComponent<TextureRenderer>()->SetKey(L"��ȣ�ۿ�");
	eBtn->CreateComponent<TutorialKey>()->SetPlayer(player);
	AddObject(eBtn);

	/// ====================================== ACHIVEMENT ================================================ 
	GameObject* achievement = new GameObject("ach1", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	achievement->SetCameraAffected(false);
	achievement->GetComponent<Transform>()->SetPosition(Vector2(0, 580));
	achievement->CreateComponent<Achievement1>();
	AddObject(achievement);
}
