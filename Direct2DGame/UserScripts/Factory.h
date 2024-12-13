#pragma once


/// <summary>
/// �ϼ��� ���ӿ�����Ʈ�� ��ȯ�Ѵ�.
/// 
/// 
/// 
/// // 2023.8.8 22:11 gitae
/// </summary>
class Factory
{
public:
	Factory(const ManagerSet* _managerSet);
	~Factory();

public:
	GameObject* CreateGameObject(FACTORY_OBJECT _object, Vector2 _position);
	
public:
	GameObject* CreateClearCheck(int _targetIndex); // Ŭ���� ������ 

	GameObject* CreatePlayerLife();
	GameObject* CreateRabbit(Vector2 _position);
	GameObject* CreatePlayer(Vector2 _position);
	GameObject* CreateChaser(Vector2 _position);
	GameObject* CreateInverseChaser(Vector2 _position);

	GameObject* CreateKey(Vector2 _position);
	GameObject* CreateDoor(Vector2 _position);
	GameObject* CreateGround(Vector2 _position);
	GameObject* CreateCeiling(Vector2 _position);
	GameObject* CreateChaserBlocker(Vector2 _position, Vector2 _scale);
	GameObject* CreateActingTrigger(Vector2 _position, Vector2 _scale ,int _actingOrder);
	GameObject* CreateCheckPoint(Vector2 _psition, int _order);
	GameObject* CreateMovingCube(Vector2 _position);
	GameObject* CreatePassPlatform(Vector2 _position, Vector2 _boxScale);

	/// ============================= Share =============================
	GameObject* CreateFogSystem(Vector2 _position, OBJECT_TYPE _layerType);
	GameObject* CreateWall(Vector2 _position);
	GameObject* CreateInterativeParticle(Vector2 _scale, Vector2 _offset, UINT _maxCount);

	/// ============================= MAIN ==============================
	GameObject* CreateFrontPillar(Vector2 _position);
	GameObject* CreateMainBackground(Vector2 _position);
	GameObject* CreateEndingBackground(Vector2 _position);

	/// ============================= STAGE 01 =============================
	// �߸� ���� 2.png
	GameObject* CreateStamp(Vector2 _position);
	// �������� 3.png
	GameObject* CreateBranch(Vector2 _position);
	// ������ 4. png
	GameObject* CreateLeaf(Vector2 _position);
	// ���� 5.png
	GameObject* CreateMushroom(Vector2 _position);
	// �Ȱ� â�� 6.png
	vector<GameObject*> CreateFogWindow(Vector2 _position);

	// 8�� ����
	GameObject* CreateFeather(Vector2 _position);

	// 9�� ����  10�� ����
	GameObject* CreateNomalPlatform(Vector2 _position, bool _isFlip);

	// 11�� ���� 
	GameObject* CreateNomalPassPlatform(Vector2 _position);

	// 12�� �����ٴ���
	GameObject* CreateLeafDummy(Vector2 _position);

	GameObject* CreateFireFly(Vector2 _position);

	// â��Ʋ
	GameObject* CreateWindowFrame(Vector2 _position);

	//â��
	GameObject* CreateDecoWindow(Vector2 _position);

	//����
	GameObject* CreateChair(Vector2 _position);

	//�빮
	GameObject* CreateMainDoor(Vector2 _position);
	/// ============================= STAGE 02 =============================
	GameObject* CreateSlideTile(Vector2 _position); //���� ����
	GameObject* CreateCandle(Vector2 _position);    //�к�
	GameObject* CreateIcicle(Vector2 _position, bool _isInverse);    //��帧
	GameObject* CreateBigIcicle(Vector2 _position, bool _isInverse); //ū ��帧
	GameObject* CreateBook(Vector2 _position);
	GameObject* CreateCushion(Vector2 _position);
	GameObject* CreateTable(Vector2 _position);
	GameObject* CreateSoundCushion(Vector2 _position);

	/// ============================= STAGE 03 =============================
	vector<GameObject*> CreateThread(Vector2 _position);
	GameObject* CreateRabbitTunnel(Vector2 _position);

	GameObject* CreateChandelierSwitch(Vector2 _position);
	GameObject* CreateChandelier(Vector2 _position); // ���鸮��
	GameObject* CreateStandLight(Vector2 _position); // ���ĵ�
	GameObject* CreateStandLightFootSwitch(Vector2 _position); // ���ĵ� ����ġ
	GameObject* CreateNomalStandLight(Vector2 _position);

	/// ============================ UI ====================================
	GameObject* CreatePopupWindow();
	
	
public:
	const ManagerSet* m_managerSet;

	GameObject* m_clearCheck; // Ŭ���� ���� Ȯ��

	GameObject* m_player;
	GameObject* m_rabbit;
	GameObject* m_PlayerLife;
};

