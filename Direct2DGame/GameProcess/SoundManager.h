#pragma once
#ifndef _CSOUND_H_
#define _CSOUND_H_
#include <fmod.hpp>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_01 0.1f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

#pragma comment(lib, "fmod_vc.lib")
using namespace FMOD;

enum class SoundType
{
	BGM,
	SFX 
};

class SoundManager
{
public:
	float fVolume;

	void Initialize();
	static SoundManager* GetInstance();
	void Finalize();

	void LoadSound(const wstring& key, const wstring& path, SoundType soundType);

	// ����
	void PlayBackgroundSound(const wstring& key);
	void PlaySFXSound(const wstring& key, int channelNum, int channelIndex);
	void PauseSFXSound(int channelIndex);

	bool isPlayingChannel(int index);
	bool isPlayingChannel2(int index);

	void SetBGMVolume(float sVolume);
	void GetVolume(float* sVolume);

	void SetSFXVolume(float sVolume,int index);
	bool isPlayingBGM();
	//void PauseSFX(int index);
	//void PauseMusic();
	//void ResumeMusic();
	//void BGMPlay();
private:
	static SoundManager* m_instance;

private:
	SoundManager() = default;
	~SoundManager();


private:
	// �̸��������� �ʿ� ������ key : ������Ʈ �̸� value : ������Ʈ ���� Ƚ��
	//map<const string, int> m_nameInfo;
	// ����
	FMOD::System* _system;
	FMOD_SOUND* m_sound;
	//std::shared_ptr<SoundChannel> _backgroundChannel;
	//std::vector<std::shared_ptr<SoundChannel>> _SFXChannels;
	FMOD::Channel* _backgroundChannel;
	FMOD::Channel* _SFXChannels[11];
	FMOD::Channel* _SFXChannels2[11];
	// 
	//vector<FMOD::Channel*>	_SFXChannels;
	FMOD_RESULT s_result; //�߰�

	float m_volume;
	FMOD_BOOL m_bool;

	// map���� ���� key �� ����� �� �ְ�
	map<wstring, FMOD::Sound*>	_backgroundSound;
	map<wstring, FMOD::Sound*>	_SFXSound;
};

#endif