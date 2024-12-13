#pragma once


struct Vector3
{
public:
	float x, y, z;

	inline Vector3() = default;
	inline explicit constexpr Vector3(float _x, float _y, float _z) 
		: x(_x), y(_y), z(_z){}
	inline explicit constexpr Vector3(Vector2& _vec2, bool _isPoint = true)
		: x(_vec2.x), y(_vec2.y),z(0.f) {z = _isPoint ? 1.f : 0.f;}

	// ������ 
	inline constexpr Vector3 operator-() const;
	inline constexpr Vector3 operator*(float _scale) const;
	inline constexpr Vector3 operator/(float _scale) const;
	inline constexpr Vector3 operator*(const Vector3& _other) const;
	inline constexpr Vector3 operator+(const Vector3& _other) const;
	inline constexpr Vector3 operator-(const Vector3& _other) const;
	inline constexpr Vector3& operator*=(float _scale);
	inline constexpr Vector3& operator/=(float _scale);
	inline constexpr Vector3& operator+=(const Vector3& _other);
	inline constexpr Vector3& operator-=(const Vector3& _other);

	// ��� �Լ�
	inline constexpr float Dot(const Vector3& _other) const;
	inline constexpr Vector2 ToVector2() const;

	std::string ToString() const;
	// ���� ��� ����
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
};

inline constexpr float Vector3::Dot(const Vector3& _other) const
{
	return x * _other.x + y * _other.y + z * _other.z;
}

inline constexpr Vector2 Vector3::ToVector2() const
{
	return Vector2(x, y);
}


inline constexpr Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

inline constexpr Vector3 Vector3::operator*(float _scale) const
{
	return Vector3(x * _scale, y * _scale, z * _scale);
}

inline constexpr Vector3 Vector3::operator/(float _scale) const
{
	return Vector3(x / _scale, y / _scale, z / _scale);
}

inline constexpr Vector3 Vector3::operator*(const Vector3& _other) const
{
	return Vector3(x * _other.x, y * _other.y, z * _other.z);
}

inline constexpr Vector3 Vector3::operator+(const Vector3& _other) const
{
	return Vector3(x + _other.x, y + _other.y, z + _other.z);
}

inline constexpr Vector3 Vector3::operator-(const Vector3& _other) const
{
	return Vector3(x - _other.x, y - _other.y, z - _other.z);
}

inline constexpr Vector3& Vector3::operator*=(float _scale)
{
	x *= _scale;
	y *= _scale;
	z *= _scale;
	return *this;
}

inline constexpr Vector3& Vector3::operator/=(float _scale)
{
	x /= _scale;
	y /= _scale;
	z /= _scale;
	return *this;
}

inline constexpr Vector3& Vector3::operator+=(const Vector3& _other)
{
	x += _other.x;
	y += _other.y;
	z += _other.z;
	return *this;
}

inline constexpr Vector3& Vector3::operator-=(const Vector3& _other)
{
	x -= _other.x;
	y -= _other.y;
	z -= _other.z;
	return *this;
}
