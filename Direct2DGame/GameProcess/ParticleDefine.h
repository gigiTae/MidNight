#pragma once

///��ƼŬ �ý��� ���ӽ����̽�
namespace ps
{
	// ���� ��� ���
	enum class RANDOM_TYPE
	{
		NONE,		// ���� ��� X
		LINEAR,		// ����
		NORMAL,		// ���Ժ���
		DISCRETE	// �̻���׺���
	};


	// ��ȭ�� ���� ��� (�� or ����)
	enum class VARIANCE_TYPE
	{
		VALUE,				// ��
		PERCENT,			// ����
		//LIFETIME,			// �ð��� ��� (min -> max)
		//INVERSE_LIFETIME	// �ð��� �ݺ�� (max - > min)
		//,USER_DEFINE //����� ���� �Լ�
	};


	// ���� ����
	enum class EMISSION_SHAPE
	{
		SQUARE, // halfWidth, halfHeight
		CIRCLE,	// radius
		CONE,	// minAngle, maxAngle, radius
	};


	enum class END_ACTION
	 {
	 	SLEEP,
	 	DESTROY,
	 	//CALLBACK
	 };

	enum class TRIGGER
	{
		NONE,
		BIRTH,
		DEATH,
		COLLISION,
		TIME
	};


	// ��ƼŬ ��
	struct ParticleValue
	{
		float mininum;				// �ּҰ�
		float maximum;				// �ִ밪
		RANDOM_TYPE randomType;		// ���� ���

	public:
		ParticleValue()
			:mininum(1), maximum(1), randomType(RANDOM_TYPE::NONE)
		{
		}

		ParticleValue(float _min)
			: mininum(_min), maximum(_min), randomType(RANDOM_TYPE::NONE)
		{
		}

		ParticleValue(float _min, float _max, RANDOM_TYPE _type)
			: mininum(_min), maximum(_max), randomType(_type)
		{
		}
	};

	// ��ƼŬ ��ȭ�� ��
	struct VarianceValue
	{
		float mininum;				// �ּҰ�
		float maximum;				// �ִ밪
		RANDOM_TYPE randomType;		// ���� ���
		VARIANCE_TYPE varianceType; // ���� ���

	public:
		VarianceValue()
			:mininum(0), maximum(0), randomType(RANDOM_TYPE::NONE), varianceType(VARIANCE_TYPE::VALUE)
		{
		}

		VarianceValue(float _min)
			: mininum(_min), maximum(_min), randomType(RANDOM_TYPE::NONE), varianceType(VARIANCE_TYPE::VALUE)
		{
		}

		VarianceValue(float _min, float _max, RANDOM_TYPE _randomType, VARIANCE_TYPE _varType)
			:mininum(_min), maximum(_max), randomType(_randomType), varianceType(_varType)
		{
		}
	};


}