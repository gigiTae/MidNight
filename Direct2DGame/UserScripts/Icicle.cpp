#include "UserScriptsPCH.h"
#include "Icicle.h"
#include "Candle.h"

Icicle::Icicle()
	:MonoBehaviour(typeid(this).name()), m_isMelt(false), m_texture(nullptr), m_isWorkingDone(false)
	, m_targetCount(0), m_currentCount(0), m_isInverseGravity(false)
{

}

Icicle::~Icicle()
{
}

void Icicle::Start()
{
	m_texture = GetComponent<TextureRenderer>();

	//��ó�� ���� ã��
	const vector<GameObject*>& objs = GetSceneManager()->GetCurrentScene()->GetGroupObject(OBJECT_TYPE::INTERACTIVE_ITEM);

	//�ݶ��̴��� 4�� �糡�� ����
	vector<Vector2> vertices; //�»��, ���ϴ�, ����, ���ϴ�
	Vector2 pos = GetComponent<Transform>()->GetPosition();
	Vector2 scale = GetComponent<BoxCollider>()->GetScale() * 0.5;
	vertices.push_back(Vector2(pos.x - scale.x, pos.y + scale.y));
	vertices.push_back(Vector2(pos.x - scale.x, pos.y - scale.y));
	vertices.push_back(Vector2(pos.x + scale.x, pos.y + scale.y));
	vertices.push_back(Vector2(pos.x + scale.x, pos.y - scale.y));

	for (auto obj : objs)
	{
		if (obj->GetName() == "candle")
		{
			//�Ÿ� ��� (���� ������ ���簢���� �Ÿ��� �ּ� ���� [500]���� ������ Ȯ��)
			Vector2 candlePos = obj->GetComponent<Transform>()->GetPosition();
			if (IsAffected(candlePos, vertices, 1000)) m_targetCount++;
		}
	}
}

void Icicle::Update(float _deltaTime)
{
	if (m_isMelt && !m_isWorkingDone)
	{
		float alpha = m_texture->GetAlpha();
		alpha = FMath::Lerp(alpha, 0.f, _deltaTime * 3);

		if (alpha < 0.01f)
		{
			alpha = 0.f;
			m_isWorkingDone = true;
		}

		m_texture->SetAlpha(alpha);
	}
}


void Icicle::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "candle")
	{
		// �� �ݶ��̴��� �ڽ��ݶ��̴���� �Һ��� �������� Ȯ����
		if (_collision.myCollider->GetColliderType() == COLLIDER_TYPE::BOX)
		{
			m_currentCount++;
			if (m_currentCount == m_targetCount)
			{
				m_isMelt = true;
				GetComponent<BoxCollider>()->SetActive(false);
				GetGameObject()->Destory(2.f);
				if(GetComponent<ParticleSystem>() != nullptr)
					GetComponent<ParticleSystem>()->Play();
			}
		}
	}
}

void Icicle::DebugRender(D2DRenderer* _d2DRenderer)
{
	_d2DRenderer->SetCameraAffected(true);
	std::wstringstream wss;
	wss << m_targetCount;
	wstring c = L"��ǥ : ";
	c += wss.str();
	c += L"\n���� : ";
	std::wstringstream wss2;
	wss2 << m_currentCount;
	c += wss2.str();

	_d2DRenderer->DrawTextW(c, GetComponent<Transform>()->GetPosition()
		, GetComponent<Transform>()->GetPosition() + Vector2(300, 40));
}

bool Icicle::IsAffected(Vector2 candlePos, const vector<Vector2>& vertices, float distance)
{
	//�»��, ���ϴ�, ����, ���ϴ�
// x ���� ���� ���� ��,
	if (vertices[0].x <= candlePos.x && candlePos.x <= vertices[2].x)
	{
		if (abs(vertices[0].y - candlePos.y) <= distance)		return true;
		else if (abs(vertices[1].y - candlePos.y) <= distance)	return true;
		else													return false;
	}

	// y���� ���� ���� ��
	else if (vertices[0].y <= candlePos.y && candlePos.y <= vertices[1].y)
	{
		if (abs(vertices[0].x - candlePos.x) <= distance)		return true;
		else if (abs(vertices[2].x - candlePos.x) <= distance)	return true;
		else													return false;
	}
	else
	{
		//��� �𼭸� ��
		for (auto point : vertices)
		{
			if (Vector2::Distance(candlePos, point) <= distance)
				return true;
		}
	}

	return false;
}