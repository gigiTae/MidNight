#include "UserScriptsPCH.h"
#include "LoadFactory.h"
#include "Factory.h"

LoadFactory::LoadFactory(const ManagerSet* _managerSet)
	:m_managerSet(_managerSet)
	,m_player(nullptr)
	,m_rabbit(nullptr)
{

}

LoadFactory::~LoadFactory()
{

}

void LoadFactory::Load(const wstring& _filePath)
{
	std::wifstream file(_filePath);
	if (!file.is_open())	
	{
		assert(nullptr);
	}

	wstring line;
	while (std::getline(file, line))
	{
		std::wistringstream iss(line);
		int index;
		float x, y;
		static int clickedImageIndex = -1;

		if (iss >> index >> x >> y)
		{
			CreateObject(index, Vector2(x, y));
		}
	}
	file.close();
}

void LoadFactory::CreateObject(int _index, Vector2 _position)
{
	GameObject* object = nullptr;
	
	// ���丮 ����
	Factory factory(m_managerSet);
	factory.m_player = m_player;
	factory.m_rabbit = m_rabbit;
	factory.m_PlayerLife = m_hp;
	factory.m_clearCheck = m_clearCheck;

	Vector2 position = m_managerSet->GetCameraManager()->ScreenToCamera(_position);

	if (_index == 0) // ���ȭ�� ����
	{
		return;
	}
	else if (_index == 1)// �÷��̾�
	{
		m_player->GetComponent<Transform>()->SetPosition(position);
	
		return;
	}
	else if (_index == 2) // �߸� ����
	{
		object =  factory.CreateStamp(position);
	}
	else if (_index == 3)// ��������
	{
		object = factory.CreateBranch(position);
	}
	else if (_index == 4)// ������
	{
		object = factory.CreateLeaf(position);
	}
	else if (_index == 5)// ����
	{
		object = factory.CreateMushroom(position);
	}
	else if (_index == 6) // �Ȱ� Ŀư â��
	{
		vector<GameObject*> fogWindow = factory.CreateFogWindow(position);
		for (int i = 0; i < static_cast<int>(fogWindow.size()); ++i)
		{
			m_objectContainer.push_back(fogWindow[i]);
			
		}
		return;
	}
 	else if (_index == 7) // �ϳ�
 	{
 		object = factory.CreateChaser(position);
 	}
	else if (_index == 8) // ����
	{
		object = factory.CreateFeather(position);
	}
	else if (_index == 9) // �Ϲ� ���� ���� 
	{
		object = factory.CreateNomalPlatform(position, false);
	}
	else if (_index == 10) // ������ ���� ����
	{
		object = factory.CreateNomalPlatform(position, true);
	}
	else if (_index == 11)
	{
		object = factory.CreateNomalPassPlatform(position);
	}
	else if (_index == 12) // �ٻ�� ����
	{
		object = factory.CreateLeafDummy(position);
	}
	else if (_index == 13) // ����
	{
		object = factory.CreateCandle(position);
	}
	else if (_index == 14) // ����
	{
		object = factory.CreateSlideTile(position);
	}
	else if (_index == 15) // ��帧
	{
		object = factory.CreateIcicle(position, false);
	}
	else if (_index == 16) // ����帧
	{
		object = factory.CreateIcicle(position, true);
	}
	else if (_index == 17) // ū ��帧
	{
		object = factory.CreateBigIcicle(position, false);
	}
	else if (_index == 18) // �� ū ��帧
	{
		object = factory.CreateBigIcicle(position, true);
	}
	else if (_index == 19) // å
	{
		object = factory.CreateBook(position);
	}
	else if (_index == 20)  //���
	{
		object = factory.CreateCushion(position);
	}
	else if (_index == 21) // Ź��
	{
		object = factory.CreateTable(position);
	}
	else if (_index == 22) // ��
	{
		vector<GameObject*> fogWindow = factory.CreateThread(position);
		for (int i = 0; i < static_cast<int>(fogWindow.size()); ++i)
		{
			m_objectContainer.push_back(fogWindow[i]);
		}
		return;
	}
	else if (_index == 23) // �ݵ�����
	{
		object = factory.CreateFireFly(position);
	}
	else if (_index == 24) //â��Ʋ
	{
		object = factory.CreateWindowFrame(position);
	}
	else if (_index == 25) //â��
	{
		object = factory.CreateDecoWindow(position);
	}
	else if (_index == 26) //�䳢��
	{
		object = factory.CreateRabbitTunnel(position);
	}
	else if (_index == 27) //����
	{
		object = factory.CreateChair(position);
	}
	else if (_index == 28) //�Ҹ��漮
	{
		object = factory.CreateSoundCushion(position);
	}
	else if (_index == 29) //inverse chaser
	{
		object = factory.CreateInverseChaser(position);
	}
	else if (_index == 30) // ���鸮��
	{
		object = factory.CreateChandelier(position);
	}
	else if (_index == 31) // ����Ʈ
	{
		object = factory.CreateStandLight(position);
	}
	else if (_index == 32) // ����Ʈ ����ġ ����
	{
		object = factory.CreateStandLightFootSwitch(position);
	}
	else if (_index == 33) // �ƹ��͵� ���� ���ĵ�
	{
		object = factory.CreateNomalStandLight(position);
	}
	else if (_index == 34) // �׳� ���̴� ���鸮�� ����ġ
	{
		object = factory.CreateChandelierSwitch(position);
	}
	else if (_index == 35) //�빮
	{
		object = factory.CreateMainDoor(position);
	}

	if (object != nullptr)
		m_objectContainer.push_back(object);
}
