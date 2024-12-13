#pragma once

class CameraManager;
/// <summary>
/// Actor, Camera���� ������ ������ ����ϴ� �Ŵ����̴�. 
/// 
/// 
/// 2023.8.9 16:32 gitae
/// </summary>
class DirectManager
{
public:
	DirectManager();
	~DirectManager();

	void Initalize(Vector2 _screenSize, CameraManager* _camera);
	void Finalize();
	void Update();
	void DebugRender(D2DRenderer* _renderer);

	// ������� ȣ��
	void Reset();

public:
	void AddActor(GameObject* _actor)const ;
	
	// �Ŵ������� �ڽ��� ������ �������� �˸���.
	void FinishActing(int _actingOrder) const;

	int GetCurrentActingOrder() const { return m_currentActingOrder; }

public:
	// Stage1�� ���� ��ũ��Ʈ
	void StartStage1Scripts() const;
	void StartStage2Scripts() const;
	void StartStage3Scripts() const;
	void EndingScripts() const;

	// �÷��̾��� Ű�Է� ������ �޴´�
	void SetPlayerInputOn(bool* _playerInputOn) const { m_playerInputOn = _playerInputOn; }
	// �䳢�� Ű�Է� ������ �޴´�. 
	void SetRabbitInputOn(bool* _rabbitInputOn) const { m_rabbitInputOn = _rabbitInputOn; }

private:
	void DiretActing();
	void AddTalkingAction(const string& _actorName
		, const wstring& _imageKey, const wstring& _text
		, ColorF _color = ColorF::Black, float _outTempo = 0.1f) const;
	void AddMovingAction(const string& _actorName, Vector2 _distance, float _moveSpeed);

	void PushBackActionInfomation(ActionInfomation _info) const;
	void WaitNextTrigger()const;

	void OnLetterBox()const;
	void OffLetterBox()const;
	void OffInput()const;
	void OnInput()const;

private:
	CameraManager* m_camera;

	// �÷��̾�� �䳢�� Key�Է��� OnOff�Ѵ�.
	mutable bool* m_playerInputOn;
	mutable bool* m_rabbitInputOn;

	Vector2 m_screenSize;

	mutable vector<ActionInfomation> m_actingVector;
	mutable int m_currentActingOrder; // ���� ���� ��ȣ
	mutable bool m_isStartedActing; // ���� ������ ��������   
	mutable map<string, GameObject*> m_actorContainer; // ���⿡ �ʿ��� ���ӿ�����Ʈ�� 
};

