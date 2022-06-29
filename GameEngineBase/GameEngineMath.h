#pragma once
#include <math.h>
#include <random>
#include <string>

class GameEngineMath 
{
public:
	static const float PI;
	static const float PI2;
	static const float DegreeToRadian;
	static const float RadianToDegree;

public:
	// 나중에 떼어내기 좋습니다.
	// 이녀석은 좀 다른게.
	// 기본적으로 제공해주는 난수를 곧바로 이용하고 싶다면
	// 싱글톤처럼 이용하면 되고.
	// 내가 직접 만들수도 있게 할겁니다.
	class Random 
	{
		// 시드역할을 담당하는 클래스
	private:
		// 시드 생성기
		// std::random_device rng_;
		// 랜덤값 생성기
		std::mt19937_64 mt_;

		// 생성 범위 제한기
		// std::uniform_int_distribution<int> Dis(_min, _max);

	public:
		int RandomInt(int _min, int _max)
		{
			// 보통 대부분의 난수 알고리즘이
			// 마지막 제한을 할때 % 사용하므로
			// 보통 _max -1까지 나온다는것을 항상 염두해 둬야 합니다.
			std::uniform_int_distribution<int> Dis(_min, _max);
			return Dis(mt_);
		}

		float RandomFloat(float _min, float _max)
		{
			// 보통 대부분의 난수 알고리즘이
			// 마지막 제한을 할때 % 사용하므로
			// 보통 _max -1까지 나온다는것을 항상 염두해 둬야 합니다.
			std::uniform_real_distribution<float> Dis(_min, _max);
			return Dis(mt_);
		}

	public:
		Random()
			: mt_()
		{
			std::random_device rng_;
			mt_.seed(rng_());
		}


		Random(__int64 _Seed)
			: mt_(_Seed)
		{

		}
		~Random() 
		{

		}
	};

};


class float4;
typedef class float4 FRect;
class float4 
{
public:
	static const float4 ZERO;

	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;


public:
	static float4 DegreeToRotatefloat2(float4 _OriginVector, float _Degree)
	{
		return RadianToRotatefloat2(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RadianToRotatefloat2(float4 _OriginVector, float _Radian)
	{
		float4 NextVector;

		NextVector.x = _OriginVector.x * cosf(_Radian) - _OriginVector.y * sinf(_Radian);
		NextVector.y = _OriginVector.x * sinf(_Radian) + _OriginVector.y * cosf(_Radian);

		return NextVector;
	}

	static float4 DegreeTofloat2(float _Degree)
	{
		return RadianTofloat2(_Degree * GameEngineMath::DegreeToRadian);
	}

	// 0도일때의 벡터를 회전시키는 공식인겁니다.
	static float4 RadianTofloat2(float _Radian)
	{
		return float4(cosf(_Radian), sinf(_Radian));
	}

	static float4 RadianTofloat2(float4 Vector, float _Radian)
	{

		return float4(cosf(_Radian), sinf(_Radian));
	}

	//Normalize를 리턴함
	static float4 NormalizeReturn2D(float4 Vector)
	{
		float Dist = sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
		float4 RetVector = { Vector.x / Dist, Vector.y / Dist };

		return RetVector;
	}

	static float Dist2D(float4 Vector)
	{
		return sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
	}

	static float RadianToDegree(float rad)
	{
		return 180.0f / GameEngineMath::PI * rad;
	}

	__forceinline float DistanceTo(const float4& other) {
		return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	// Clock wise dgree from -y axis
	__forceinline float GetDegreeFromNegativeYAxisClockWise() {
		return (float)(((x < 0) ? 360.0f * GameEngineMath::DegreeToRadian : 0.0f) + (acos(-y) * ((x < 0) ? -1 : 1))) * GameEngineMath::RadianToDegree;
	}

public:
	// unnamed union을 선언하면 
	// 내부의 메모리를 구조를 union 방식으로 구성해준다.
	union 
	{
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float left;
			float top;
			float right;
			float bottom;
		};
		// 실수는 기본적으로 00000000 00000000 00000000 00000000
	};

	// 자신이 Normalize됨
	void Normalize2D()
	{
		float Dist = sqrtf(x * x + y * y);
		x /= Dist;
		y /= Dist;
	}

	float4 operator+(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x + _other.x;
		ReturnValue.y = this->y + _other.y;
		ReturnValue.z = this->z + _other.z;
		ReturnValue.w = this->w + _other.w;
		return ReturnValue;
	}

	float4 operator+(float _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x + _other;
		ReturnValue.y = this->y + _other;
		ReturnValue.z = this->z + _other;
		ReturnValue.w = this->w + _other;
		return ReturnValue;
	}

	float4 operator-(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x - _other.x;
		ReturnValue.y = this->y - _other.y;
		ReturnValue.z = this->z - _other.z;
		ReturnValue.w = this->w - _other.w;
		return ReturnValue;
	}

	float4 operator*(const float _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x * _other;
		ReturnValue.y = this->y * _other;
		ReturnValue.z = this->z * _other;
		ReturnValue.w = this->w * _other;
		return ReturnValue;
	}

	float4 operator*(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x * _other.x;
		ReturnValue.y = this->y * _other.y;
		ReturnValue.z = this->z * _other.z;
		ReturnValue.w = this->w * _other.w;
		return ReturnValue;
	}

	float4 operator/(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x / _other.x;
		ReturnValue.y = this->y / _other.y;
		ReturnValue.z = this->z / _other.z;
		ReturnValue.w = this->w / _other.w;
		return ReturnValue;
	}


	float4& operator+=(const float4 _other)
	{
		this->x += _other.x;
		this->y += _other.y;
		this->z += _other.z;
		this->w += _other.w;
		return *this;
	}

	float4& operator-=(const float4 _other) 
	{
		this->x -= _other.x;
		this->y -= _other.y;
		this->z -= _other.z;
		this->w -= _other.w;
		return *this;
	}

	float4& operator*=(const float4 _other)
	{
		this->x *= _other.x;
		this->y *= _other.y;
		this->z *= _other.z;
		this->w *= _other.w;
		return *this;
	}

	float4& operator*=(const float _other)
	{
		this->x *= _other;
		this->y *= _other;
		this->z *= _other;
		this->w *= _other;
		return *this;
	}

	float4& operator/=(const float4 _other) 
	{
		this->x /= _other.x;
		this->y /= _other.y;
		this->z /= _other.z;
		this->w /= _other.w;
		return *this;
	}

	// 대입연산자
	float4& operator=(const float4& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;

		return *this;
	}

	bool operator!=(const float4& _other) const
	{
		return x != _other.x || y != _other.y || z != _other.z || w != _other.w;
	}

	bool operator==(const float4& _other) const
	{
		return x == _other.x && y == _other.y && z == _other.z && w == _other.w;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float4 halffloat4() const
	{
		return {hx(), hy(), hz()};
	}

	int ihx() const
	{
		return static_cast<int>(hx());
	}

	int ihy() const
	{
		return static_cast<int>(hy());
	}

	int ihz() const
	{
		return static_cast<int>(hz());
	}


public:
	float4() 
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{
	}

	// 디폴트 파라미터
	// 가장 우측에 있는 인자에 상수값을 넣어서
	// 만약 인자를 넣어주지 않았을때는 
	float4(float _x, float _y, float _z, float _w = 1.0f)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	~float4() {

	}

public:		// delete constructer
	float4(const float4& _other) 
		: x(_other.x), y(_other.y), z(_other.z), w(_other.w)
	{

	}

};

class int4 
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			__int64 HighValue;
			__int64 LowValue;
		};
	};
};


class Figure
{
public:
	float4 pos_;
	float4 size_;

public:
	float Left()
	{
		return pos_.x - size_.hx();
	}

	float Right()
	{
		return pos_.x + size_.hx();
	}

	float Top()
	{
		return pos_.y - size_.hy();
	}

	float Bot()
	{
		return pos_.y + size_.hx();
	}

	int iLeft() 
	{
		return pos_.ix() - size_.ihx();
	}

	int iRight()
	{
		return pos_.ix() + size_.ihx();
	}

	int iTop()
	{
		return pos_.iy() - size_.ihy();
	}

	int iBot()
	{
		return pos_.iy() + size_.ihy();
	}

	float4 LeftTopfloat4()
	{
		return { Left(), Top() };
	}

	float4 RightTopfloat4()
	{
		return { Right(), Top() };
	}

	float4 LeftBotfloat4()
	{
		return { Left(), Bot() };
	}

	float4 RightBotfloat4()
	{
		return { Right(), Bot() };
	}


public:
	Figure(float4 _Pos, float4 _Size) 
		: pos_(_Pos), size_(_Size)
	{

	}
};