#include "GameProcessPCH.h"
#include "NamingManager.h"

// ������� ���� �ʱ�ȭ 
NamingManager* NamingManager::m_instance = nullptr;

NamingManager* NamingManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new NamingManager();
	}
	return m_instance;
}

void NamingManager::Finalize()
{
	delete this;
}

NamingManager::~NamingManager()
{
}

const string NamingManager::GenerateName(const string& _name)
{
	auto iter = m_nameInfo.find(_name);

	// ó������ ������ �̸�
	if (iter == m_nameInfo.end())
	{
		m_nameInfo.insert(std::make_pair(_name, 1));
		return _name;
	}

	// �̹� �������� �ִ� �̸��̸� ���ڸ� �ٿ��� �����Ѵ�.
	int number = iter->second++;
	const string name = _name + std::to_string(number);

	return name;
}
