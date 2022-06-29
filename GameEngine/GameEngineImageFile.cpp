#include "GameEngineImageFile.h"
#include <GameEngineDebug.h>

// �ٸ� ���̺귯�� �ڵ带 ����ϴ� �Լ�
// �̹� �����찡 �������ֱ� ������ ���� ��μ����� �����ʿ䰡 ���� �ٷ� ����� �����ϴ�.


// Static Var
// Static Func

// constructer destructer
GameEngineImageFile::GameEngineImageFile()
{
}

GameEngineImageFile::~GameEngineImageFile()
{
}

GameEngineImageFile::GameEngineImageFile(GameEngineImageFile&& _other) noexcept
{
}

void GameEngineImageFile::Cut(const float4 _Cut) 
{
	if (0.0f >= _Cut.x)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	if (0.0f >= _Cut.y)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	size_t XCount = static_cast<size_t>(GetSize().x / _Cut.x);
	size_t YCount = static_cast<size_t>(GetSize().y / _Cut.y);

	cutimagepos_.reserve(XCount * YCount);
	cutimagesize_.reserve(XCount * YCount);

	float4 StartImagePos = float4::ZERO;
	float4 StartImageSize = _Cut;

	for (size_t i = 0; i < YCount; i++)
	{
		for (size_t i = 0; i < XCount; i++)
		{
			// 0,0
			cutimagepos_.push_back(StartImagePos);
			// 128, 128
			cutimagesize_.push_back(StartImageSize);

			// 0             +  128
			StartImagePos.x += StartImageSize.x;
		}

		StartImagePos.x = 0.0f;
		StartImagePos.y += StartImageSize.y;
	}

}

bool GameEngineImageFile::Create(HDC _dc, const float4& _size) 
{
	// ���� �� ��Ʈ���� ����� ����.
	// DC�� �ϳ� �ʿ��ѵ�
	// �� ���α׷����� �̳༮�� �������� DC�� �޶�� �ϴ� �̴ϴ�.

	// 
	imagehandle_ = CreateCompatibleBitmap(_dc, _size.ix(), _size.iy());

	imagedc_ = CreateCompatibleDC(nullptr);
	HANDLE oldhandle = SelectObject(imagedc_, static_cast<HGDIOBJ>(imagehandle_));
	oldHandle_ = static_cast<HBITMAP>(oldhandle);

	BitMapImageInfoCheck();

	return true;
}

bool GameEngineImageFile::Create(HDC _dc)
{
	if (nullptr == _dc)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	imagedc_ = _dc;

	BitMapImageInfoCheck();
	return true;
}

//member Func

bool GameEngineImageFile::Load(std::string _Path)
{
	// ������ �ִ��� �������� 
	// ���⿡�� ���ϵǴ°� DC�� �ƴϴ�.
	// ���״�� 2���� �迭�� �������� �������̰�
	// �� 2���� �迭�� ������ �����Ϸ���
	// DC�� ���ؼ� �����ؾ� �ϴµ�.

	HANDLE LoadHandle = nullptr;
	// ���������� �ε��Ҽ� �־��.
	LoadHandle = LoadImageA(nullptr, _Path.c_str()
		, IMAGE_BITMAP
		, 0, 0
		, LR_LOADFROMFILE);

	// HBITMAP
	imagehandle_ = static_cast<HBITMAP>(LoadHandle);

	if (nullptr == imagehandle_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	// �����迭�� �޸𸮱���
	// HANDLE imagehandle_

	// �ü������ ����������
	// ������������������ ���� �������ּ���.

	// DC�� ��¥ ��������°�.
	imagedc_ = CreateCompatibleDC(nullptr);
	HANDLE oldhandle = SelectObject(imagedc_, static_cast<HGDIOBJ>(imagehandle_));
	oldHandle_ = static_cast<HBITMAP>(oldhandle);

	BitMapImageInfoCheck();

	return true;
}

void GameEngineImageFile::ClearImage()
{
	PatBlt(imagedc_, 0, 0, imageinfo_.bmWidth, imageinfo_.bmHeight, BLACKNESS);
}

void GameEngineImageFile::BitMapImageInfoCheck() 
{
	if (nullptr == imagedc_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// ������� �Դٸ� �̹��� �ڵ��� �̹� �����ϴ� �����̾�� �Ѵ�.
	// imagehandle_�� ���ؼ� �׳� �ᵵ �ȴ�.

	HBITMAP CheckBitMap = static_cast<HBITMAP>(GetCurrentObject(imagedc_, OBJ_BITMAP));
	GetObjectA(CheckBitMap, sizeof(BITMAP), &imageinfo_);
}

// �����ʿ����� ����Ʈ ���ڸ� �־��ټ� �����ϴ�.
void GameEngineImageFile::BitCopyToImageSize(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _ImagePos /*= float4::ZERO*/)
{
	BitCopy(_CopyImage, _LeftTopPos, _CopyImage->GetSize(), _ImagePos);
}

void GameEngineImageFile::BitCopyToImageSizeToBot(GameEngineImageFile* _CopyImage, const float4& _Pos, const float4& _ImagePos /*= float4::ZERO*/) 
{
	float4 Center = _CopyImage->GetSize().halffloat4();
	Center.y = _CopyImage->GetSize().y;
	BitCopy(_CopyImage, _Pos - Center, _CopyImage->GetSize(), _ImagePos);
}

void GameEngineImageFile::BitCopyToImageSizeToCenter(GameEngineImageFile* _CopyImage, const float4& _Pos, const float4& _ImagePos /*= float4::ZERO*/)
{
	BitCopy(_CopyImage, _Pos - _CopyImage->GetSize().halffloat4(), _CopyImage->GetSize(), _ImagePos);
}

void GameEngineImageFile::BitCopy(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos/*= float4::ZERO*/)
{
	if (nullptr == _CopyImage)
	{
		GameEngineDebug::MsgBoxError("Image Setting Error");
		return;
	}

	BitBlt(imagedc_,
		_LeftTopPos.ix(),
		_LeftTopPos.iy(),
		_Size.ix(),
		_Size.iy(),
		_CopyImage->imagedc_,
		_ImagePos.ix(),
		_ImagePos.iy(),
		SRCCOPY);
}



void GameEngineImageFile::TransCopy(GameEngineImageFile* _CopyImage, const float4& _LeftTopPos, const float4& _RenderSize, const float4& _ImagePos, const float4& _ImageSize, int _transcolor)
{
	if (nullptr == _CopyImage)
	{
		GameEngineDebug::MsgBoxError("Image Setting Error");
		return;
	}

	// �����е��� Ư�� ������ �����ϰ� ���������Ҽ� �ֽ��ϴ�.
	// ũ�������� ������� �Ҽ� �ֽ��ϴ�.
	// ������ ũ�⸦ ������� �ٲ۴ٴ� => ũ�⸦ �ٲٴ� ������ �ϱ� ������
	// ������ ���������ɼ��� �����Ƿ�
	// ũ��� �ظ��ϸ� �ٲ��� ����.
	TransparentBlt(
		imagedc_,
		_LeftTopPos.ix(),
		_LeftTopPos.iy(),
		_RenderSize.ix(),
		_RenderSize.iy(),
		_CopyImage->imagedc_,
		_ImagePos.ix(),
		_ImagePos.iy(),
		_ImageSize.ix(),
		_ImageSize.iy(),
		_transcolor // <=�� ������ �������ݴϴ�.
	);
}

DWORD GameEngineImageFile::GetColor4Byte(int _x, int _y)
{
	return GetPixel(imagedc_, _x, _y);
}

float4 GameEngineImageFile::GetColorfloat4(int _x, int _y) 
{
	COLORREF ColorValue = GetPixel(imagedc_, _x, _y);

	unsigned char* Ptr = reinterpret_cast<unsigned char*>(&ColorValue);
	
	float4 Colorfloat4;
	// 0~255
	Colorfloat4.r = Ptr[0] / 255.0f; // r
	Colorfloat4.g = Ptr[1] / 255.0f; // g
	Colorfloat4.b = Ptr[2] / 255.0f; // b
	Colorfloat4.a = Ptr[3] / 255.0f; // a
	return Colorfloat4;
}

void GameEngineImageFile::AlphaCopy(GameEngineImageFile* _CopyImage, 
	const int _Alpha, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos, const float4& _ImageSize)
{
	BLENDFUNCTION Bland;

	Bland.BlendOp = AC_SRC_OVER;
	Bland.BlendFlags = 0;
	Bland.SourceConstantAlpha = _Alpha;
	Bland.AlphaFormat = AC_SRC_ALPHA;

	//BYTE   BlendOp;
	//BYTE   BlendFlags;
	//BYTE   SourceConstantAlpha;
	//BYTE   AlphaFormat;

	AlphaBlend(
		imagedc_,
		_LeftTopPos.ix(),
		_LeftTopPos.iy(),
		_Size.ix(),
		_Size.iy(),
		_CopyImage->imagedc_,
		_ImagePos.ix(),
		_ImagePos.iy(),
		_ImageSize.ix(),
		_ImageSize.iy(),
		Bland
	);

}

void GameEngineImageFile::PlgCopy(GameEngineImageFile* _CopyImage, GameEngineImageFile* _MaskImage, float _Angle, const float4& _LeftTopPos, const float4& _Size, const float4& _ImagePos, const float4& _ImageSize)
{
	if (nullptr == _CopyImage)
	{
		GameEngineDebug::MsgBoxError("Image Setting Error");
		return;
	}

	Figure fi = { float4::ZERO, _Size };

	float4 Arrfloat4[3];

	Arrfloat4[0] = fi.LeftTopfloat4();
	Arrfloat4[1] = fi.RightTopfloat4();
	Arrfloat4[2] = fi.LeftBotfloat4();

	Arrfloat4[0] = float4::DegreeToRotatefloat2(Arrfloat4[0], _Angle);
	Arrfloat4[1] = float4::DegreeToRotatefloat2(Arrfloat4[1], _Angle);
	Arrfloat4[2] = float4::DegreeToRotatefloat2(Arrfloat4[2], _Angle);


	POINT Arr[3];
	Arr[0] = { Arrfloat4[0].ix() + _LeftTopPos.ix(),Arrfloat4[0].iy() + _LeftTopPos.iy() };
	Arr[1] = { Arrfloat4[1].ix() + _LeftTopPos.ix(),Arrfloat4[1].iy() + _LeftTopPos.iy() };
	Arr[2] = { Arrfloat4[2].ix() + _LeftTopPos.ix(),Arrfloat4[2].iy() + _LeftTopPos.iy() };


	// _MaskImage->imagehandle_,�� HBITMAP�� �־���� �Ѵ�.

	if (nullptr != _MaskImage)
	{
		PlgBlt(imagedc_,
			Arr,
			_CopyImage->imagedc_,
			_ImagePos.ix(),
			_ImagePos.iy(),
			_ImageSize.iy(),
			_ImageSize.ix(),
			_MaskImage->imagehandle_,
			_ImagePos.ix(),
			_ImagePos.iy()
		);
	}
	else 
	{
		PlgBlt(imagedc_,
			Arr,
			_CopyImage->imagedc_,
			_ImagePos.ix(),
			_ImagePos.iy(),
			_ImageSize.iy(),
			_ImageSize.ix(),
			nullptr,
			_ImagePos.ix(),
			_ImagePos.iy()
		);
	}

}