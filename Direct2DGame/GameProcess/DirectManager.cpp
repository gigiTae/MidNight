#include "GameProcessPCH.h"
#include "DirectManager.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "Actor.h"
#include "Letterbox.h"

DirectManager::DirectManager()
	:m_actorContainer()
	, m_currentActingOrder(0)
	, m_isStartedActing(false)
	, m_rabbitInputOn(nullptr)
	, m_playerInputOn(nullptr)
	,m_camera(nullptr)
{

}

DirectManager::~DirectManager()
{

}

void DirectManager::Initalize(Vector2 _screenSize, CameraManager* _camera)
{
	m_screenSize = _screenSize;

	m_camera = _camera;
}

void DirectManager::Finalize()
{

}

void DirectManager::Update()
{
	if (m_actingVector.empty())
		return;

	// ���� ������ �����Ѵ�.
	if (!m_isStartedActing &&   m_currentActingOrder < m_actingVector.size())
	{
		DiretActing();
	}	

	if (m_actingVector[m_currentActingOrder].type == ACTION_TYPE::OFF_INPUT
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::ON_INTPUT
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::LETTERBOX_OFF
		|| m_actingVector[m_currentActingOrder].type == ACTION_TYPE::CAMERA_EFFECT_ON)
	{
		m_currentActingOrder++;
		m_isStartedActing = false;
	}
}

void DirectManager::DebugRender(D2DRenderer* _renderer)
{
	// ������ ���� �� 
	if (m_actingVector.empty())
		return;

	wstring str = L"���� ���� ���� : " + std::to_wstring(m_currentActingOrder) + L"\nŸ�� : ";
	
	switch (m_actingVector[m_currentActingOrder].type)
	{
		case ACTION_TYPE::OBJECT_MOVE:
			str += L"������Ʈ �̵�";
			break;
		case ACTION_TYPE::OBJECT_TALK:
		{
			// ���� ���ڿ��� ������ wstring�� �����մϴ�.
			wstring name;

			// ���ڵ� ��ȯ�⸦ �����մϴ�.
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

			// std::string�� std::wstring���� ��ȯ�մϴ�.
			name = converter.from_bytes(m_actingVector[m_currentActingOrder].actorName);

			str += L" ���\n" + name + L" : " + m_actingVector[m_currentActingOrder].talkingInfo.text;
		}	
			break;
		case ACTION_TYPE::CAMERA_MOVE:
			str += L" ī�޶� �̵�";
			break;
		case ACTION_TYPE::CAMERA_EFFECT_ON:
			str += L"ī�޶� ȿ�� �߰�";
			break;
		case ACTION_TYPE::LETTERBOX_OFF:
			str += L"ī�޶� ȿ�� ����";
			break;
		case ACTION_TYPE::WAIT_TRIGGER:
			str += L"���� �̺�Ʈ �����";
			break;
		case ACTION_TYPE::OFF_INPUT:
			str += L"Ű �Է� ��Ȱ��ȭ";
			break;
		case ACTION_TYPE::ON_INTPUT:
			str += L"Ű �Է� Ȱ��ȭ";
			break;
		default:
			break;
	}

	Vector2 leftTop{ -m_screenSize.x * 0.5f, m_screenSize.y * 0.5f - 100.f }, rightBottom{ 0.f,0.f };

	_renderer->SetCameraAffected(false);
	_renderer->DrawTextW(str, leftTop, rightBottom, D2D1::ColorF::Gold);
}

void DirectManager::Reset()
{
	m_actingVector.clear();
	m_currentActingOrder = 0;
	m_actorContainer.clear();
	m_isStartedActing = false;
	m_playerInputOn = nullptr;
	m_rabbitInputOn = nullptr;

}

void DirectManager::AddActor(GameObject* _actor)const
{
	// ���� �ε����� �پ��ִ� �̸��� �����´�
	string name =_actor->GetDebugName();
	 
	assert(m_actorContainer.find(name) == m_actorContainer.end()
	 || L"���� ��츦 �ι��̳� �߰��߽��ϴ�");

	// ��츮��Ʈ�� �߰��Ѵ�.
	m_actorContainer.insert(make_pair(name, _actor));
}

void DirectManager::FinishActing(int _actingOrder) const
{
	assert(m_currentActingOrder == _actingOrder
	|| L" ���� ��ȣ�� ��ġ���� �ʽ��ϴ�. ");

	++m_currentActingOrder; // ���� ������ �����Ų��. 
	m_isStartedActing = false;

	assert(m_currentActingOrder != m_actingVector.size()
		|| !L"���� ������ �����ϴ�.");
		
}

void DirectManager::DiretActing()
{
	ActionInfomation& info = m_actingVector[m_currentActingOrder];

	switch (info.type)
	{
		case ACTION_TYPE::OBJECT_MOVE:
			break;
		case ACTION_TYPE::OBJECT_TALK:
		{
			// �ش��ϴ� ������Ʈ���� ��縦 �����Ѵ�.
			auto iter= m_actorContainer.find(info.actorName);
			Actor* actor = iter->second->GetComponent<Actor>();
			actor->DirectTalking(info.talkingInfo, m_currentActingOrder);
		}
			break;
		case ACTION_TYPE::CAMERA_MOVE:
			break;
		case ACTION_TYPE::CAMERA_EFFECT_ON:
		{
			m_camera->LetterboxCamera(100.f, 50.f);
		}
			break;
		case ACTION_TYPE::LETTERBOX_OFF:
		{
			Letterbox* letterbox = dynamic_cast<Letterbox*>(m_camera->GetCurrentCameraEffect());
			assert(letterbox);
			letterbox->Close();
		}
			break;
		case ACTION_TYPE::OFF_INPUT:
		{
			// Ű�Է� ��Ȱ��ȭ
			*m_playerInputOn = false;
			*m_rabbitInputOn = false;
		}
			break;
		case ACTION_TYPE::ON_INTPUT:
		{
			// Ű�Է� Ȱ��ȭ
			*m_playerInputOn = true;
			*m_rabbitInputOn = true;
		}
			break;
		default:
			break;
	}

	m_isStartedActing = true;
}

void DirectManager::AddTalkingAction(const string& _actorName
	, const wstring& _imageKey, const wstring& _text
	, ColorF _color /*= ColorF::Black*/, float _outTempo /*= 0.1f*/) const
{
	ActionInfomation act{}; 
	act.type = ACTION_TYPE::OBJECT_TALK;
	act.actorName = _actorName;
	act.talkingInfo.imageKey = _imageKey;
	act.talkingInfo.outputTempo = _outTempo;
	act.talkingInfo.text = _text;
	act.talkingInfo.textColor = _color;

	PushBackActionInfomation(act);
}

void DirectManager::AddMovingAction(const string& _actorName, Vector2 _distance, float _moveSpeed)
{

}

void DirectManager::PushBackActionInfomation(ActionInfomation _info) const
{
	 int actingOrder = static_cast<int>(m_actingVector.size());
	 _info.actingOrder = m_currentActingOrder;

	 m_actingVector.push_back(_info);
}

void DirectManager::WaitNextTrigger()const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::WAIT_TRIGGER;

	PushBackActionInfomation(act);
}


void DirectManager::OnLetterBox() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::CAMERA_EFFECT_ON;
	act.cameraEffectType = CAMERA_EFFECT_TYPE::LETTERBOX;
	
	PushBackActionInfomation(act);
}

void DirectManager::OffLetterBox() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::LETTERBOX_OFF;

	PushBackActionInfomation(act);
}

void DirectManager::OffInput() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::OFF_INPUT;

	PushBackActionInfomation(act);
}

void DirectManager::OnInput() const
{
	ActionInfomation act{};
	act.type = ACTION_TYPE::ON_INTPUT;

	PushBackActionInfomation(act);
}

void DirectManager::StartStage1Scripts() const 
{	
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	OffInput(); // 0

	// �Ϲ� ���� 1�� 
	AddTalkingAction("rabbit", L"bubble (20)", L"������ �����ϰ� ��� \n����� ����!",rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"����!",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"�׷��� ���� �ʹ�\n ��� ����...",playerColor);
	AddTalkingAction("player", L"bubble (3)", L"[�Ȱ�] �����ΰ�?",playerColor);
	AddTalkingAction("rabbit", L"bubble (18)", L"����� ã�ƺ���!",rabbitColor);

	OnInput();

	WaitNextTrigger(); // 7

	// ù��° ��ȣ�ۿ� ����
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("player", L"bubble (5)", L"[Ŀư]�� ġ�ϱ� \n[�Ȱ�]�� �������", playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"��� [Ŀư]�� ���\n [�Ȱ�]�� ������!", rabbitColor);

	WaitNextTrigger(); // 11

	OffInput();

	// �Ϲ� ���� 2�� 
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"������ ���Ⱑ ������\n �� ����",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"Ŀư�� ���ϱ� �ξ� ����",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"2������ ����������!",rabbitColor);

	WaitNextTrigger(); // �������� Ŭ���� 17

	// �̹��� ����
}

void DirectManager::StartStage2Scripts() const
{

	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	// �Ϲ� ���� 3�� - 2�� ��������(2��) ������ �� 
	OffInput();
	AddTalkingAction("player", L"bubble (3)", L"(���� ����)", playerColor);
	AddTalkingAction("player", L"bubble (4)", L"��.. ����� �߿�", playerColor);
	AddTalkingAction("rabbit", L"bubble (17)", L"���� ��!", rabbitColor);
	AddTalkingAction("rabbit", L"bubble (18)", L"[��帧]�̾�!",rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"[��帧]�� ������ \n�ʹ� �����ڴ�",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[��帧]�� ���� �����\n ������?",rabbitColor);
	OnInput();

	WaitNextTrigger(); // 8

	// ù��° ��ȣ�ۿ� ����
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("player", L"bubble (5)", L"[�к�]�� �Ѵϱ�\n ��帧�� ��ҳ�", playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[�к�]�� �Ѽ� ���⸦ \n�����ϰ� ������!", rabbitColor);

	WaitNextTrigger(); // 12

	OffInput();
	// �Ϲ� ���� 4�� - 2�� ��������(2��) ���� ��
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("player", L"bubble (3)", L"���� ���� �ʾ�",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"������ ����������",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"���� ��帧 ������\n ���������� �ʰ�!",rabbitColor);
	AddTalkingAction("player", L"bubble (1)", L":)",playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"1������ ����������!",rabbitColor);

	WaitNextTrigger(); // �������� Ŭ���� 20
}

void DirectManager::StartStage3Scripts() const
{
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);

	OffInput();

	// �Ϲ� ���� 5�� - 3��������(1��) ������ ��
	AddTalkingAction("rabbit", L"bubble (18)", L"���� 1���̴�!",rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"�ʹ� ��ο���\n �� �Ⱥ���",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"�κ� �̷���\n ��ο�����!",rabbitColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"���� �Ѿ� �� �� ������?",rabbitColor);
	AddTalkingAction("player", L"bubble (4)", L"���� [���鸮��]�� �־�!",playerColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[���鸮��]�� �ѷ���\n ��� �ұ�?",rabbitColor);

	OnInput();

	WaitNextTrigger(); // 8

	// ù��° ��ȣ�ۿ� ����
	AddTalkingAction("player", L"bubble (1)", L"!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"[���鸮��]�� ������", rabbitColor);
	AddTalkingAction("rabbit", L"bubble (20)", L"[��ư]���� [���鸮��]��\n Ű��!", rabbitColor);

	WaitNextTrigger();

	OffInput(); //13

	// �Ϲ� ���� 6�� - 3��������(1��) ���� ��
	AddTalkingAction("player", L"bubble (1)", L"!",playerColor);
	AddTalkingAction("rabbit", L"bubble (17)", L"�������!",rabbitColor);
	AddTalkingAction("player", L"bubble (3)", L"���� �� ����",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"������ �̷��� �а�\n ���� ���̾�����",playerColor);
	AddTalkingAction("player", L"bubble (5)", L"�̷��� �� �ѷ��� �� \n������ ó���̾�",playerColor);
	AddTalkingAction("rabbit", L"bubble (16)", L":)",rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"����",playerColor);

	WaitNextTrigger(); //21

	
}

void DirectManager::EndingScripts() const
{
	ColorF playerColor(225.f / 255.f, 162.f / 255.f, 66.f / 255.f);
	ColorF rabbitColor(237.f / 255.f, 104.f / 255.f, 185.f / 255.f);
	WaitNextTrigger();
	AddTalkingAction("player", L"bubble (3)", L"���� �����ߴ�!", playerColor);
	AddTalkingAction("player", L"bubble (3)", L"���� ��! ���̾�!", playerColor);
	WaitNextTrigger();
	OffInput(); 
	AddTalkingAction("rabbit", L"bubble (20)", L"���� �ٱ� ������\n�� �� �ְھ�!", rabbitColor);
	AddTalkingAction("player", L"bubble (2)", L"����!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"���� ����־���. ��ġ?", rabbitColor);
	AddTalkingAction("player", L"bubble (5)", L"��! �̷��� ��� ��\n ó���̾�!", playerColor);
	AddTalkingAction("player", L"bubble (4)", L"���õ� ����������!", playerColor);
	AddTalkingAction("player", L"bubble (3)", L"�䳢�� ����!", playerColor);
	AddTalkingAction("rabbit", L"bubble (19)", L"�ƴϾ�! �װ� �� �ž�!", rabbitColor);
	WaitNextTrigger();

}

