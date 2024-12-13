#pragma once


/// <summary>
/// �ν��Ͻ��� �������� �ʰ� ���ӽ����̽��� �����ϴ� �Ŵ����̴�
///
/// ���� : ���Ͽ� �����͸� �д� ����� �����Ѵ�. 
/// </summary>
namespace FileManager
{
	/// <summary>
	/// ���ϰ�� ���ο� ��� ������ ��θ� ���Ϳ� ��ȯ 
	/// </summary>
	/// <param name="_files">�����̸��� ������ ����</param>
	/// <param name="_filePath">���ϰ��</param>
	/// <param name="_allDirectories">���� �����丮�� �ִ� ���ϱ��� �д���</param>
	void GetFileMemberPath(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories);
	
	/// <summary>
	///  ���� ��� ���ο� ��� ������ �̸��� ���Ϳ� ��ȯ
	/// </summary>
	/// <param name="_files"></param>
	/// <param name="_filePath"></param>
	/// <param name="_allDirectories"></param>
	void GetFileMemberName(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories);
};

