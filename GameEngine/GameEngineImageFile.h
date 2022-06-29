#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineMath.h>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <vector>

#pragma comment(lib, "msimg32.lib")

// 우리 프레임워크에서 API에 사용할 
// 내용들은 전부다 이 클래스를 통해서 처리할 겁니다.


// 분류 : 리소스
// 용도 : 랜더링
// 설명 : 랜더링과 이미지에 관련된 모든 함수와 기능을 제공한다.
//         
class GameEngineImage;
class GameEngineWindow;
class GameEngineImageFile : public GameEngineNameBase
{
private:	// member Var
	friend GameEngineImage;
	friend GameEngineWindow;

private:
	// 순수 이미지 정보 핸들
	HBITMAP imagehandle_;
	HBITMAP oldHandle_;
	BITMAP imageinfo_;
	HDC imagedc_;

public:
	std::vector<float4> cutimagepos_;
	std::vector<float4> cutimagesize_;

public:
	bool IsCut() {
		return cutimagepos_.size() != 0;
	}

	float4 GetCutPos(size_t _Index) 
	{
		if (_Index >= cutimagepos_.size())
		{
			GameEngineDebug::AssertFalse();
			return float4::ZERO;
		}

		return cutimagepos_[_Index];
	}
	float4 GetCutSize(size_t _Index) 
	{
		if (_Index >= cutimagesize_.size())
		{
			GameEngineDebug::AssertFalse();
			return float4::ZERO;
		}
		return cutimagesize_[_Index];
	}


	HDC GetDC() 
	{
		return imagedc_;
	}

	float4 GetSize() 
	{
		return { static_cast<float>(imageinfo_.bmWidth), static_cast<float>(imageinfo_.bmHeight) };
	}

private:		
	GameEngineImageFile(); // default constructer 디폴트 생성자
	~GameEngineImageFile(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineImageFile(const GameEngineImageFile& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineImageFile(GameEngineImageFile&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineImageFile& operator=(const GameEngineImageFile& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineImageFile& operator=(const GameEngineImageFile&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Cut(const float4 _Cut);

public:		//member Func
	bool Create(HDC _dc);
	bool Create(HDC _dc, const float4& _size);
	bool Load(std::string _Path);

	void ClearImage();
	// Rendering Copy Func

private:
	void BitMapImageInfoCheck();

public:
	// BitBlt
	void BitCopy(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos = float4::ZERO);
	void BitCopyToImageSize(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _ImagePos = float4::ZERO);
	void BitCopyToImageSizeToCenter(GameEngineImageFile* _CopyImage, const float4& _Pos, const float4& _ImagePos = float4::ZERO);
	void BitCopyToImageSizeToBot(GameEngineImageFile* _CopyImage, const float4& _Pos, const float4& _ImagePos = float4::ZERO);


public:
	// Trans
	void TransCopy(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos, const float4& _ImageSize, int _transcolor);

	void AlphaCopy(GameEngineImageFile* _CopyImage, const int _Alpha, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos, const float4& _ImageSize);

public: // plg
	void PlgCopy(GameEngineImageFile* _CopyImage, GameEngineImageFile* _MaskImage, float _Angle, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos, const float4& _ImageSize);

	DWORD GetColor4Byte(int _x, int _y);
	float4 GetColorfloat4(int _x, int _y);
};

