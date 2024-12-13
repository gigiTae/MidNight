#include "GameProcessPCH.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "FileManager.h"
#include "SoundManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Initalize(PathManager* _pathManager, D2DRenderer* _d2DRenderer)
{
	PathManager* pathManager = _pathManager;

	wstring parentFilePath = pathManager->GetRelativPath();

	const wstring imageFilePath = parentFilePath + L"\\Resource\\Texture";
	const wstring soundFilePathBGM = parentFilePath + L"\\Resource\\Sound";
	const wstring soundFilePathSFX = parentFilePath + L"\\Resource\\Sound\\SFX";

	// �̹����� �ε� 
	LoadImageResources(_d2DRenderer, imageFilePath);

	// ���带 �ε�
	LoadSoundResources(soundFilePathBGM, soundFilePathSFX);
}


void ResourceManager::Finalize()
{
	// ���ҽ� �Ŵ����� ���������� ���Ҹ� ��������ʴ´�.
}

void ResourceManager::LoadImageResources(D2DRenderer* _d2DRenderer, const wstring& _filePath)
{
	/// ���ҽ� ���Ϸ� ��θ� �����Ѵ�
	vector<wstring> filesPath{}, fileName{};

	/// ���ϳ����� �̸��� ��ΰ����� ���͸� ä���
	FileManager::GetFileMemberPath(filesPath, _filePath, true);
	FileManager::GetFileMemberName(fileName, _filePath, true);

	assert(filesPath.size() == fileName.size());

	/// Ȯ���ڸ� �����ϰ� Key������ �����  ex) apple.png -> apple
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();

			if (tmp == L'.') break;

			/// Ȯ���ڸ��� Ȯ���ؾ��� �ʿ䰡 ������
			assert(fileName.size() != 0 || !L"������ Ȯ���� Ű���尡 �����ϴ�.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// ���� �̸��� key������ ����Ѵ�
		_d2DRenderer->LoadBitmap(fileName[i], filesPath[i].c_str());
	}
}


void ResourceManager::LoadSoundResources(const wstring& _filePath, const wstring& _filePathSFX)
{
	/// ����������� ����ؼ� ���鸦 �ε��ϴ� ����

	/// ���ҽ� ���Ϸ� ��θ� �����Ѵ�
	vector<wstring> filesPath{}, fileName{};//bgm
	vector<wstring> filesPathSFX{}, fileNameSFX{};//sfx

	/// ���ϳ����� �̸��� ��ΰ����� ���͸� ä���
	FileManager::GetFileMemberPath(filesPath, _filePath, true);	//bgm
	FileManager::GetFileMemberName(fileName, _filePath, true);	//bgm
	
	FileManager::GetFileMemberPath(filesPathSFX, _filePathSFX, true);	//sfx
	FileManager::GetFileMemberName(fileNameSFX, _filePathSFX, true);	//sfx

	assert(filesPath.size() == fileName.size());
	assert(filesPathSFX.size() == fileNameSFX.size());

	/// Ȯ���ڸ� �����ϰ� Key������ �����  ex) apple.png -> apple
	/// BGM-----------------------------------------------------
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();

			if (tmp == L'.') break;

			/// Ȯ���ڸ��� Ȯ���ؾ��� �ʿ䰡 ������
			assert(fileName.size() != 0 || !L"������ Ȯ���� Ű���尡 �����ϴ�.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// ���� �̸��� key������ ����Ѵ�
		SoundManager::GetInstance()->LoadSound(fileName[i], filesPath[i], SoundType::BGM);

	}
	/// --------------------------------------------------------

	/// SFX-----------------------------------------------------
	for (int i = 0; i < static_cast<int>(fileNameSFX.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileNameSFX[i].back();
			fileNameSFX[i].pop_back();

			if (tmp == L'.') break;

			/// Ȯ���ڸ��� Ȯ���ؾ��� �ʿ䰡 ������
			assert(fileNameSFX.size() != 0 || !L"������ Ȯ���� Ű���尡 �����ϴ�.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileNameSFX.size()); ++i)
	{
		/// ���� �̸��� key������ ����Ѵ�
		SoundManager::GetInstance()->LoadSound(fileNameSFX[i], filesPathSFX[i], SoundType::SFX);
	}
	/// --------------------------------------------------------
}
