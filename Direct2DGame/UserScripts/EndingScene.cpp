#include "UserScriptsPCH.h"
#include "EndingScene.h"

#include "SceneManager.h"

// Ŀ���� ������Ʈ
#include "UIComponent.h"
#include "MouseCursor.h"
#include "LightWaver.h"
#include "WalkingChild.h"
#include "InfiniteMap.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Chandlier.h"
#include "EndingParticle.h"
#include "FinalAct.h"

// ���丮 �߰�
#include "Factory.h"

EndingScene::EndingScene()
{
	
}

EndingScene::~EndingScene()
{

}

void EndingScene::Enter()
{


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
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FRONT_DECO);

	///  ============================ ���� �ý��� ===========================================
	const DirectManager* directMgr = GetManagerSet()->GetDirectManager();
	directMgr->EndingScripts();

	///  ============================ ���丮 ���� ===========================================
	Factory factory(GetManagerSet());

	/// ============================= �÷��̾� ==============================================

	// �÷��̾� 
	GameObject* player = factory.CreatePlayer(Vector2(0.f, -390.f));
	
	// �䳢
	GameObject* rabbit = factory.CreateRabbit(Vector2(0.f, 0.f));

	// �÷��̾�� �䳢�� �����Ѵ�. 
	rabbit->GetComponent<RabbitComponent>()->SetMainPlayer(player); // ���� ���� ������Ʈ, ������ �̵�
	player->GetComponent<PlayerComponent>()->SetRabbit(rabbit);
	player->GetComponent<PlayerComponent>()->SetRStop(true);

	AddObject(player);
	AddObject(rabbit);

	/// ============================= ����ý��� Ű�Է� ���� ==================================
	directMgr->SetPlayerInputOn(player->GetComponent<PlayerComponent>()->GetInputOn());
	directMgr->SetRabbitInputOn(rabbit->GetComponent<RabbitComponent>()->GetInputOn());

	/// ī�޶� ����
	GetManagerSet()->GetCameraManager()->SetCameraPos();
	GetManagerSet()->GetCameraManager()->SetOffset(Vector2(750, 400));
	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MAINSCENE);
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);

	///--------------------------------------------------------------------------------------------------------
	///                                 ����Ʈ ��ƼŬ
	///--------------------------------------------------------------------------------------------------------
	GameObject* light = new GameObject("waver", GetManagerSet(), OBJECT_TYPE::PARTICLE);
	light->GetComponent<Transform>()->SetPosition(Vector2(1500, 100));

	ParticleSystem* wp = light->CreateComponent<ParticleSystem>();
	wp->AddDefaultParticle(L"blueLightBall");
	wp->m_shape = EMISSION_SHAPE::SQUARE;
	wp->m_halfWidth = 2000;
	wp->m_halfHeight = 500;
	wp->m_isRepeat = true;
	wp->m_emitInterval = 0.01f;
	wp->m_initScale = { 0.1f, 0.3f, RANDOM_TYPE::LINEAR };
	wp->m_initSpeed = 0.f;
	wp->m_lifeTime = { 2.f, 5.f, RANDOM_TYPE::LINEAR };
	wp->m_initRotation = { 0.f,360.f, RANDOM_TYPE::LINEAR };
	wp->m_maxCount = 50;



	PointLightRenderer* l = wp->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.f); l->SetRGB(0x4dbaff);
	//l->SetScale(Vector2(1.01f, 1.5f));

	wp->GetParticlePrefab(0)->CreateComponent<EndingParticle>();

	wp->Play();
	AddObject(light);

	///--------------------------------------------------------------------------------------------------------
	///                                 ��� ������Ʈ
	///--------------------------------------------------------------------------------------------------------
	for (int i = 0; i < 4; ++i)
	{
		GameObject* background = new GameObject("background", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
		background->GetComponent<Transform>()->SetPosition(Vector2(-260 + 1920.f*0.75f*static_cast<float>(i), 280.f));
		background->CreateComponent<TextureRenderer>()->SetKey(L"���1");
		background->GetComponent<TextureRenderer>()->SetScale(Vector2(0.75f, 0.75f));
		AddObject(background);
	}

	for (int i = 0; i < 7; i++)
	{
		GameObject* pillar = factory.CreateFrontPillar(Vector2( 150 + i * 1500, 455));
		AddObject(pillar);
	}


	// ��
	GameObject* ground = factory.CreateGround(Vector2(0.f, -500.f));
	AddObject(ground);
// 
// 	GameObject* pillars = new GameObject("pillars", GetManagerSet(), OBJECT_TYPE::BACK_UI);
// 	pillars->CreateComponent<InfiniteMap>()->SetUp(OBJ_NAME::PILLAR, Vector2(-600, 455));
// 	AddObject(pillars);

	AddObject(factory.CreateWall(Vector2(0.f, 500.f)));
	AddObject(factory.CreateCeiling(Vector2(0.f, 1050.f)));

	GameObject* mainDoor = new GameObject("mainDoor", GetManagerSet(), OBJECT_TYPE::TILE);
	mainDoor->GetComponent<Transform>()->SetPosition(Vector2(3000.f,-60.f));
	mainDoor->CreateComponent<TextureRenderer>()->SetKey(L"�빮");

	AddObject(mainDoor);

	// ���鸮��
	GameObject* ch = factory.CreateChandelier(Vector2(460.f, 300.f));
	ch->GetComponent<Chandlier>()->LightOn();
	AddObject(ch);

	GameObject* ch2 = factory.CreateChandelier(Vector2(1900.f, 300.f));
	ch2->GetComponent<Chandlier>()->LightOn();
	AddObject(ch2);

	AddObject(factory.CreateActingTrigger(Vector2(1000.f, 0.f), Vector2(500.f, 4000.f), 0));
	AddObject(factory.CreateActingTrigger(Vector2(3000.f, 0.f), Vector2(500.f, 800.f), 3 ));

	/// ���� ������Ʈ 
	GameObject* act = new GameObject("act", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	act->CreateComponent<FinalAct>();
	act->SetCameraAffected(false);
	act->CreateComponent<MouseEvent>();

	AddObject(act);


	/// ==================================== ī�޶� ���� =========================================

    /// ���� �������� ������ �� �۾����� �ʿ��մϴ�.

	float top = 550.f;
	float bottom = 10.f;
	float left = 2000.f;

	Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();

	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MIDNIGHT);
	GetManagerSet()->GetCameraManager()->SetCameraBorder(top, bottom, 500.f, 3000.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(500.f,0.f));
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);
	GetManagerSet()->GetCameraManager()->FadeInCamera(3.f, false);


}
