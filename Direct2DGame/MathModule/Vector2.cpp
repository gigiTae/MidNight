#include "MathModulePCH.h"
#include "Vector2.h"
#include "Vector3.h"

const Vector2 Vector2::UnitX{ 1.f,0.f };
const Vector2 Vector2::UnitY{ 0.f, 1.f };
const Vector2 Vector2::One{ 1.f, 1.f };
const Vector2 Vector2::Zero{ 0.f,0.f };



std::string Vector2::ToString() const
{              
	char result[64];
	std::snprintf(result, sizeof(result), "(%.3f, %.3f)", x, y);
	return result;
}


void Vector2::Normalize()
{
	*this = GetNormalize();
}

Vector2 Vector2::GetNormalize() const
{
	float squarSum = LengthSquared();
	if (squarSum == 1.f)
	{
		return *this;
	}
	else if (squarSum == 0.f)
	{
		return Vector2::Zero;
	}

	// ��� �� ������ ������ ����ϸ� ���� ���� ����

	float invLength = 1 / sqrtf(squarSum);

	return Vector2(x, y) * invLength;
}

float Vector2::PointToLineSegment ( const Vector2& point ,const Vector2& line1 , const Vector2& line2 )
{
	// ���� �븻 ����
	Vector2 u = ( line2 - line1 ).GetNormalize ( );
	Vector2 line1ToPoint = point - line1;

	// L1�� L2 ����
	float L1ToL2 = ( line1 - line2 ).Length ( );
	// ������ ����
	float dist = u.Dot ( line1ToPoint );

	if ( dist < 0 )
	{
		return line1ToPoint.Length ( );
	}
	else if ( dist <= L1ToL2 )
	{
		return std::sqrt ( line1ToPoint.LengthSquared ( ) - dist * dist );
	}
	else
	{
		return ( line2 - point ).Length ( );
	}


	return 0.0f;
}


Vector2 Vector2::Lerp ( const Vector2& v1 , const Vector2& v2 , float ratio )
{
	if ( ratio < 0 ) ratio = 0;
	else if ( 1 < ratio ) ratio = 1;

	return v1 * (1 - ratio) + v2 * ratio ;
}

float Vector2::Distance ( const Vector2& v1 , const Vector2& v2 )
{
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return std::sqrt ( dx * dx + dy * dy );
}
