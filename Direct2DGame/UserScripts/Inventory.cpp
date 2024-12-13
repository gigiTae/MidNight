#include "UserScriptsPCH.h"
#include "Inventory.h"

Inventory::Inventory()
	:MonoBehaviour(typeid(this).name())
	,m_itemList{}
	,m_active(false)
{

}

Inventory::~Inventory()
{

}

Component* Inventory::Clone()
{
	Inventory* clone = new Inventory();
	clone->m_itemList = m_itemList;

	return clone;
}

bool Inventory::UseItem(ITEM_TYPE _type)
{
	auto iter = m_itemList.begin();

	// �����۸���Ʈ�� ��ȸ�Ѵ�. 
	while (iter != m_itemList.end())
	{
		// ���� ������ Ÿ�����̸� ����Ѵ�. 
		if (*iter == _type)
		{
			m_itemList.erase(iter);
			return true; 
		}
		++iter;
	}

	// ������ ��� ����
	return false;
}

void Inventory::PusBack(ITEM_TYPE _type)
{
	m_itemList.push_back(_type);
}

void Inventory::PassItemList(list<ITEM_TYPE>& _passed)
{
	_passed.clear();

	_passed = m_itemList;

	m_itemList.clear();
}
