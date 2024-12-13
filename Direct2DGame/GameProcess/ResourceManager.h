#pragma once

class PathManager;

/// <summary>
/// �̹���, ���带 �ε��ϴ� �Ŵ��� 
/// ������ ���ҽ� �Ŵ����� ���������� ���ҽ����� �������� �ʴ´�.
/// 
/// </summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Initalize(PathManager* _pathManager, D2DRenderer* _d2DRenderer);	
	void Finalize();
private:
	// �̹����� �ε��Ѵ�.
	void LoadImageResources(D2DRenderer* _d2DRenderer, const wstring& _filePath);

	// ���带 �ε��Ѵ�. 
	void LoadSoundResources(const wstring& _filePath, const wstring& _filePathSFX);

private:
	
};

