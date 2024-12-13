#pragma once
#include "MonoBehaviour.h"
#include "ParticleDefine.h"

class Transform;
class ParticleSystem;
class TextureRenderer;
using namespace ps;

class Particle : public MonoBehaviour
{
friend class ParticleSystem;

///�����ڿ� �Ҹ��� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	Particle();
	~Particle();

	Component* Clone() override;

	void SetTextureKey(wstring key) { m_textureKey = key; }
	void Setup(ParticleSystem* system
		, Vector2 initPos, float scale, float rotation
		, float speed, Vector2 direction, float gravityFactor, float lifeTime
		, float dSpeed, float dScale, float dRotation
		, float alpha, float dAlpha);

	void SetSubEmit(TRIGGER subEmitTrigger, float subEmitTime);

///�ɹ� �Լ� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
public:
	void Update(float _deltaTime) override;
	void Render(D2DRenderer* _d2DRenderer) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;
	void OnTriggerEnter(const Collision& _collision) override;
	void Play() { m_isAwake = true; }


	void SetAlpha(float alpha) { m_alpha = alpha; }
	float GetAlpha() { return m_alpha; }
	float GetTimer() { return m_timer; }
	float GetLifeTime() { return m_lifeTime; }


private:
	void Variance(float& arg, const float& var, const VARIANCE_TYPE& type, const float& dt);
	void VarianceByValue(float& arg, const float& var, const float& dt);
	void VarianceByRatio(float& arg, const float& var, const float& dt);


///�ɹ� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
private:
	ParticleSystem* m_system;
	Transform* m_transform; // position, scale, rotation

	wstring m_textureKey;

	bool m_isAwake;

	float m_speed;
	Vector2 m_direction;
	float m_gravityFactor;
	float m_gravityAcceleration;

	float m_timer;
	float m_subEmitTimer;
	
	float m_lifeTime;
	float m_dSpeed;
	float m_dScale;
	float m_dRotation;

	float m_alpha;
	float m_dAlpha;

	VARIANCE_TYPE m_scaleVarType;
	VARIANCE_TYPE m_rotationVarType;
	VARIANCE_TYPE m_speedVarType;
	VARIANCE_TYPE m_alphaVarType;
	
	bool m_subEmit;
	TRIGGER m_subEmitTrigger;
	float m_subEmitTime;

	//�������, �����ɶ�, �ð�������, �浹 ��ƼŬ�ý��ۿ� �ݹ�? -> subemitters
};

