#pragma once


/// <summary>
/// ���� ��θ� �޾ƿ��� �Ŵ��� 
/// static�� ����ϱ� �ߴµ� 
/// ���� �޸𸮰����� ��ü�� �Ҵ��ؾ��ұ�?
/// �𸣰ڴ�....
/// 
/// �ٽú��� �ʹ� �������°� ���� 
/// </summary>
class PathManager 
{
public:
	PathManager();
	~PathManager();

	void Initalize();
	void Finalize();
	const wchar_t* GetRelativPath() const;

private:
	wchar_t m_relativePath[256];
};

