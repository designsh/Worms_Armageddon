#include "GameEngineWindow.h"
#include <GameEngineDebug.h>
#include <GameEngineTime.h>
#include "GameEngineInput.h"
#include "GameEngineImageFile.h"
#include "GameEngineImage.h"
#include <GameEngineSoundManager.h>
#include <iostream>

#include "KeyboardClass.h"

// 값형 싱글톤
// GameEngineWindow GameEngineWindow::Inst;

// 포인터형 싱글톤
GameEngineWindow* GameEngineWindow::Inst = new GameEngineWindow();

bool WindowOn = true;

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        // HDC 윈도우에 픽셀에 색깔을 바꿀수 있는 권한이입니다.
        // 윈도우창이 그려지는 2차원 배열에 접근할수 있는 권한입니다.
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        WindowOn = false;
        break;
    }

    // 키보드 등록(채팅기능용)
    case WM_CHAR:
    {
        unsigned char ch = static_cast<unsigned char>(_wParam);

        // 예외처리 : 해당 키들은 input에 등록하여 사용함
        if (ch == '\b') // BackSpace Key Down
        {
            int a = 0;

            break;
        }
        else if (ch == '\r') // Enter Key Down
        {
            break;
        }
        else if (ch == ' ') // Space Key Down
        {
            break;
        }

        // 문자 입력에 의한 큐 등록
        if (KeyboardClass::GetInst().IsCharsAutoRepeat())
        {
            KeyboardClass::GetInst().OnChar(ch);
        }
        else
        {
            const bool wasPressed = _lParam & 0x40000000;
            if (!wasPressed)
            {
                KeyboardClass::GetInst().OnChar(ch);
            }
        }
        return 0;
    }
    case WM_KEYDOWN:
    {
        unsigned char keycode = static_cast<unsigned char>(_wParam);

        // 예외처리 : 해당 키들은 input에 등록하여 사용함
        if (keycode == '\b') // BackSpace Key Down
        {
            break;
        }
        else if (keycode == '\r') // Enter Key Down
        {
            break;
        }
        else if (keycode == ' ') // Space Key Down
        {
            break;
        }

        if (KeyboardClass::GetInst().IsKeysAutoRepeat())
        {
            KeyboardClass::GetInst().OnKeyPressed(keycode);
        }
        else
        {
            const bool wasPressed = _lParam & 0x40000000;
            if (!wasPressed)
            {
                KeyboardClass::GetInst().OnKeyPressed(keycode);
            }
        }

        return 0;
    }
    case WM_KEYUP:
    {
        unsigned char keycode = static_cast<unsigned char>(_wParam);
        KeyboardClass::GetInst().OnKeyReleased(keycode);

        return 0;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow() 
    : className_("")
    , windowTitle_("")
    , windowhandle_(nullptr)
    , hInstance_(nullptr)
    , windowimage_(nullptr)
    , backBufferImage_(nullptr)
    , devicecontext_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
    // Keyboard Class Destory
    KeyboardClass::Destroy();

    if (nullptr != windowimage_)
    {
        delete windowimage_;
        windowimage_ = nullptr;
    }

    if (nullptr != backBufferImage_)
    {
        delete backBufferImage_;
        backBufferImage_ = nullptr;
    }

    if (nullptr != windowhandle_)
    {
        // 생각없이 안해줘야 되겠지.
        // 윈도우가 알아서 해줄거야.
        // new => 알아서 delete 안해줄까?
        // 방법이 없어요 컴퓨터 공학상.
        // 언어의 설계상 답이 없기 때문에
        DestroyWindow(windowhandle_);
        windowhandle_ = nullptr;
        // CloseHandle(windowhandle_);
    }
}

// constructer destructer
//member Func
void GameEngineWindow::CreateMainWindowClass(HINSTANCE _hInstance, std::string _className)
{
    if (nullptr == _hInstance)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    if ("" == _className)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    hInstance_ = _hInstance;
    className_ = _className;

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW; // 화면 재갱신 옵션
    wcex.lpfnWndProc = WndProc; // <= 내일 설명
    wcex.cbClsExtra = 0; // 신경안써도 됨
    wcex.cbWndExtra = 0; // 신경안써도 됨.
    wcex.hInstance = _hInstance;
    wcex.hIcon = nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor = nullptr;//LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName = "GameWindow";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 아래의 함수의 내용이 
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos)
{
    if (nullptr == hInstance_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    if ("" == className_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    // 국가코드를 변경해주는 함수 하지만 여기서는 굳이 필요 없었다.
    // char* PrevLocal = setlocale(LC_ALL, "Kor");

    windowTitle_ = _titlename;
    windowhandle_ = nullptr;
    windowhandle_ = CreateWindowA(className_.c_str(), "TEST", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance_, nullptr);

    if (0 == windowhandle_)
    {
        GameEngineDebug::AssertFalse();
        return;
    }

    SetWindowTextA(windowhandle_, windowTitle_.c_str());

    ShowWindow(windowhandle_, SW_SHOW);
    SetSizeAndPos(_size, _pos);
    // 윈도우를 한번 갱신해줘.
    UpdateWindow(windowhandle_);


    HDC Devicecontext = ::GetDC(windowhandle_);
    // 이미 만들어진 DC를 통해서 GameEngineImage를 생성하는
    // 그리고 이 함수는 오로지 GameEngineWindow만이 사용하게 만들겠습니다.
    // GameEngineWindow의 dc는 특별하게 따로 보관하겠습니다.
    GameEngineImage::GetInst().InitializeWindowImage(Devicecontext);

    return;
}

GameEngineWindow* GameEngineWindow::CreateSubWindow(const std::string& _titlename, const float4& _size, const float4& _pos)
{
    

    if (nullptr == GameEngineWindow::GetInst().hInstance_)
    {
        GameEngineDebug::AssertFalse();
        return nullptr;
    }

    if ("" == GameEngineWindow::GetInst().className_)
    {
        GameEngineDebug::AssertFalse();
        return nullptr;
    }

    // 국가코드를 변경해주는 함수 하지만 여기서는 굳이 필요 없었다.
    // char* PrevLocal = setlocale(LC_ALL, "Kor");

    GameEngineWindow* NewWindow = new GameEngineWindow();

    NewWindow->windowTitle_ = _titlename;
    NewWindow->windowhandle_ = nullptr;
    NewWindow->windowhandle_ = CreateWindowA(GameEngineWindow::GetInst().className_.c_str(), "TEST", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, GameEngineWindow::GetInst().hInstance_, nullptr);

    if (0 == NewWindow->windowhandle_)
    {
        delete NewWindow;
        GameEngineDebug::AssertFalse();
        return nullptr;
    }

    SetWindowTextA(NewWindow->windowhandle_, NewWindow->windowTitle_.c_str());

    ShowWindow(NewWindow->windowhandle_, SW_SHOW);
    NewWindow->SetSizeAndPos(_size, _pos);
    // 윈도우를 한번 갱신해줘.
    UpdateWindow(NewWindow->windowhandle_);

    NewWindow->devicecontext_ = ::GetDC(NewWindow->windowhandle_);
    // MainWindow전용이라 해주면 안됩니다.
    // GameEngineImage::GetInst().InitializeWindowImage(Devicecontext);

    NewWindow->backBufferImage_ = new GameEngineImageFile();
    NewWindow->backBufferImage_->Create(NewWindow->devicecontext_, GameEngineWindow::GetInst().GetSize());

    NewWindow->windowimage_ = new GameEngineImageFile();
    NewWindow->windowimage_->Create(NewWindow->devicecontext_);

    

    return NewWindow;
}

void GameEngineWindow::SetSizeAndPos(const float4& _size, const float4& _pos)
{
    size_ = _size;
    pos_ = _pos;

    //          1920          
    RECT Rc = { 0, 0, _size.ix(), _size.iy() };
    // 내가 넣어준 렉트에 타이틀바와 메뉴등의 사이즈가 들어간 녀석으로 만들어주세요.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);

    // 0넣으면 그냥 보통 기본이다.
    SetWindowPos(windowhandle_, nullptr, _pos.ix(), _pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, 0);
}

void GameEngineWindow::Loop(void(*_loopFunc)()) 
{
    MSG msg;
    while (WindowOn)
    {

        // PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
        // 2번째 인자에 하나의 윈도우 핸들을 넣어주면
        // PeekMessage 그때부터 그 윈도우만 처리해준다.
        // nullptr을 넣어주면 등록된 핸들 전부를 처리해줍니다.
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            GameEngineTime::GetInst().TimeCheck();
            GameEngineInput::GetInst().Update();
            //GameEngineSound::GetInst().SoundUpdate();

            if (nullptr == _loopFunc)
            {
                GameEngineDebug::AssertFalse();
                return;
            }

            _loopFunc();

            // Window메세지가 있든 없든 돌아간다.
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); // WNDPROC
            }


        }
        else 
        {
            GameEngineTime::GetInst().TimeCheck();
            GameEngineInput::GetInst().Update();
            //GameEngineSound::GetInst().SoundUpdate();
            GameEngineSoundManager::GetInstance().Update();

            if (nullptr == _loopFunc)
            {
                GameEngineDebug::AssertFalse();
                return;
            }

            _loopFunc();
        }
    }
}

float4 GameEngineWindow::GetMousePos()
{
    POINT P;

    // 모니터에서의 마우스 위치
    GetCursorPos(&P);

    // m_WindowHWnd 윈도우 기준으로
    ScreenToClient(windowhandle_, &P);

    return { (float)P.x, (float)P.y };
}

bool GameEngineWindow::SetMousePos(int _x, int _y)
{
    return SetCursorPos(_x, _y);
}
