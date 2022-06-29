#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineMath.h>
#include <GameEngineDebug.h>
#include <GameEngineNameBase.h>
#include <vector>

#pragma comment(lib, "msimg32.lib")

// �츮 �����ӿ�ũ���� API�� ����� 
// ������� ���δ� �� Ŭ������ ���ؼ� ó���� �̴ϴ�.


// �з� : ���ҽ�
// �뵵 : ������
// ���� : �������� �̹����� ���õ� ��� �Լ��� ����� �����Ѵ�.
//         
class GameEngineImage;
class GameEngineWindow;
class GameEngineImageFile : public GameEngineNameBase
{
private:	// member Var
	friend GameEngineImage;
	friend GameEngineWindow;

private:
	// ���� �̹��� ���� �ڵ�
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
	GameEngineImageFile(); // default constructer ����Ʈ ������
	~GameEngineImageFile(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineImageFile(const GameEngineImageFile& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineImageFile(GameEngineImageFile&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineImageFile& operator=(const GameEngineImageFile& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineImageFile& operator=(const GameEngineImageFile&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

