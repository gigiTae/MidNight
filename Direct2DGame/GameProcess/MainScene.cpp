#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "FileManager.h"
#include "GameObject.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "TextureRenderer.h"

MainScene::MainScene()
{
}    

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	/// ���ҽ� �ε�
	LoadSceneResources(L"MainScene");

}
