#include "GameEngineImageFile.h"
#include <GameEngineDebug.h>

// 다른 라이브러리 코드를 사용하는 함수
// 이미 윈도우가 지원해주기 때문에 따로 경로설정도 해줄필요가 없이 바로 사용이 가능하다.


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
	// 먼저 빈 비트맵을 만들어 낸다.
	// DC가 하나 필요한데
	// 이 프로그램에서 이녀석을 랜더링할 DC를 달라고 하는 겁니다.

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
	// 파일이 있는지 없는지는 
	// 여기에서 리턴되는건 DC가 아니다.
	// 말그대로 2차원 배열의 정보만을 가진것이고
	// 이 2차원 배열의 정보를 조작하려면
	// DC를 통해서 접근해야 하는데.

	HANDLE LoadHandle = nullptr;
	// 여러가지를 로드할수 있어요.
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

	// 차원배열의 메모리까지
	// HANDLE imagehandle_

	// 운영체제에서 얻어왔을때는
	// 꼬오오오오오오오옥 직접 정리해주세요.

	// DC가 진짜 만들어지는곳.
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

	// 여기까지 왔다면 이미지 핸들이 이미 존재하는 시점이어야 한다.
	// imagehandle_을 통해서 그냥 써도 된다.

	HBITMAP CheckBitMap = static_cast<HBITMAP>(GetCurrentObject(imagedc_, OBJ_BITMAP));
	GetObjectA(CheckBitMap, sizeof(BITMAP), &imageinfo_);
}

// 구현쪽에서는 디폴트 인자를 넣어줄수 없습니다.
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

	// 여러분들은 특정 색깔을 제외하고 랜더링을할수 있습니다.
	// 크기조정을 마음대로 할수 있습니다.
	// 하지만 크기를 마음대로 바꾼다는 => 크기를 바꾸는 연산을 하기 때문에
	// 굉장히 느려질가능성이 높으므로
	// 크기는 왠만하면 바꾸지 마라.
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
		_transcolor // <=들어간 색깔을 제거해줍니다.
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


	// _MaskImage->imagehandle_,에 HBITMAP을 넣어줘야 한다.

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