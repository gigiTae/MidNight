#pragma once

struct Vector2
{
public:
	float x;
	float y;
	
	inline constexpr Vector2():x(0.f),y(0.f){}
	inline explicit constexpr Vector2(int _x, int _y);
	inline explicit constexpr Vector2(float _x, float _y);

	/// ������
	inline constexpr Vector2 operator-() const;
	inline constexpr Vector2 operator*(float _scalar) const;
	inline constexpr Vector2 operator/(float _scalar) const;
	inline constexpr Vector2 operator*(const Vector2& _other) const;
	inline constexpr Vector2 operator+(const Vector2& _other) const;
	inline constexpr Vector2 operator-(const Vector2& _other) const;
	inline constexpr Vector2& operator*=(float _scale);
	inline constexpr Vector2& operator/=(float _scale);
	inline constexpr Vector2& operator+=(const Vector2& _other);
	inline constexpr Vector2& operator-=(const Vector2& _other);
	inline constexpr bool operator==(const Vector2& _other);
	inline constexpr bool operator!=(const Vector2& _other);


	// ��Ʈ ������ (����)
	inline float Length() const;

	// ������ ��ȯ
	inline constexpr float LengthSquared() const;

	// ���� ����ȭ
	void Normalize();

	// [[nodiscard]] : ��ȯ���� ���� ������ ���
	[[nodiscard]] Vector2 GetNormalize() const;

	// ��ȯ���� �����Դϴ�!!
	inline float Angle() const;

	// ���� ��ǥ�� -> ����ǥ�� ��ȯ
	inline Vector2 ToPolarCoordinate() const;

	// ����ǥ�� -> ������ǥ�� ��ȯ
	inline Vector2 ToCartesianCoordinate() const;

	inline Vector2 ChangeYSign ( );

	// ��������
	inline constexpr float Dot(const Vector2& _other) const;
	// ���� ����
	inline constexpr float Cross ( const Vector2& _other ) const;
	
	std::string ToString() const;
	
	inline D2D1_POINT_2F ToPoint2F();

	// �������� �������� point�� radian��ŭ ȸ���� ���͸� ��ȯ
	static Vector2 RotateRadian(const Vector2& _point, const Vector2& _center, float _radian);

	// ���а� �������� �ִܰ�θ� ��ȯ
	static float PointToLineSegment ( const Vector2& point , const Vector2& line1 ,const  Vector2& line2 );

	// �� �����̿� �ִ� Ư�� ������ ���� ��ȯ
	static Vector2 Lerp ( const Vector2& v1 , const Vector2& v2 , float ratio );

	// �� ���� �Ÿ�
	static float Distance ( const Vector2& v1 , const Vector2& v2 );

	// �����������
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;
	static const Vector2 Zero;
};


inline Vector2 Vector2::ChangeYSign ( )
{
	return Vector2 ( x , -y );
}

inline D2D1_POINT_2F Vector2::ToPoint2F()
{
	D2D1_POINT_2F point{};
	point.x = x;
	point.y = y;
	return point;
}

inline Vector2 Vector2::RotateRadian(const Vector2& _point, const Vector2& _center, float _radian)
{
	float cosTheta = std::cos(_radian);
	float sinTheta = std::sin(_radian);

	Vector2 relative = _point - _center;
	Vector2 rotated{};
	rotated.x = _center.x + relative.x * cosTheta - relative.y * sinTheta;
	rotated.y = _center.y + relative.x * sinTheta + relative.y * cosTheta;

	return rotated;
}


inline constexpr Vector2::Vector2(int _x, int _y)
	:x((float)_x)
	, y((float)_y)
{}

inline constexpr Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{}

inline constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline constexpr Vector2 Vector2::operator*(float _scalar) const
{
	return Vector2(x * _scalar, y * _scalar);
}

inline constexpr Vector2 Vector2::operator/(float _scalar) const
{
	return Vector2(x / _scalar, y / _scalar);
}

inline constexpr Vector2 Vector2::operator*(const Vector2& _other) const
{
	return Vector2(x * _other.x, y * _other.y);
}

inline constexpr Vector2 Vector2::operator+(const Vector2& _other) const
{
	return Vector2(x + _other.x, y + _other.y);
}

inline constexpr Vector2 Vector2::operator-(const Vector2& _other) const
{

	return Vector2(x - _other.x, y - _other.y);
}

inline constexpr Vector2& Vector2::operator*=(float _scale)
{
	x *= _scale;
	y *= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator/=(float _scale)
{
	x /= _scale;
	y /= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator+=(const Vector2& _other)
{
	x += _other.x;
	y += _other.y;

	return *this;
}

inline constexpr Vector2& Vector2::operator-=(const Vector2& _other)
{
	x -= _other.x;
	y -= _other.y;

	return *this;
}

inline constexpr bool Vector2::operator==(const Vector2& _other)
{
	return (x == _other.x && y == _other.y);
}

inline constexpr bool Vector2::operator!=(const Vector2& _other)
{
	return (x != _other.x || y != _other.y);
}

inline float Vector2::Length() const
{
	return sqrtf(LengthSquared());
}

inline constexpr float Vector2::LengthSquared() const
{
	return x * x + y * y;
}

inline float Vector2::Angle() const
{
	return atan2f(y, x);
}


inline Vector2 Vector2::ToPolarCoordinate() const
{
	return Vector2(Length(), Angle());
}

inline Vector2 Vector2::ToCartesianCoordinate() const
{
	// ����ǥ�迡���� x�� ������ y�� ��(rad)���� Ȱ��
	float sinValue = sinf(y);
	float cosValue = cosf(y);

	return Vector2(x * sinValue, x * cosValue);
}

inline constexpr float Vector2::Dot(const Vector2& _other) const
{
	return x* _other.x + y * _other.y;
}

inline constexpr float Vector2::Cross ( const Vector2& _other )const
{
	return x * _other.y - y * _other.x;
}
