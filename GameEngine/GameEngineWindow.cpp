#include "GameEngineWindow.h"
#include <GameEngineDebug.h>
#include <GameEngineTime.h>
#include "GameEngineInput.h"
#include "GameEngineImageFile.h"
#include "GameEngineImage.h"
#include <GameEngineSoundManager.h>
#include <iostream>

#include "KeyboardClass.h"

// ���� �̱���
// GameEngineWindow GameEngineWindow::Inst;

// �������� �̱���
GameEngineWindow* GameEngineWindow::Inst = new GameEngineWindow();

bool WindowOn = true;

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        // HDC �����쿡 �ȼ��� ������ �ٲܼ� �ִ� �������Դϴ�.
        // ������â�� �׷����� 2���� �迭�� �����Ҽ� �ִ� �����Դϴ�.
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        WindowOn = false;
        break;
    }

    // Ű���� ���(ä�ñ�ɿ�)
    case WM_CHAR:
    {
        unsigned char ch = static_cast<unsigned char>(_wParam);

        // ����ó�� : �ش� Ű���� input�� ����Ͽ� �����
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

        // ���� �Է¿� ���� ť ���
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

        // ����ó�� : �ش� Ű���� input�� ����Ͽ� �����
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
        // �������� ������� �ǰ���.
        // �����찡 �˾Ƽ� ���ٰž�.
        // new => �˾Ƽ� delete �����ٱ�?
        // ����� ����� ��ǻ�� ���л�.
        // ����� ����� ���� ���� ������
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
    wcex.style = CS_HREDRAW | CS_VREDRAW; // ȭ�� �簻�� �ɼ�
    wcex.lpfnWndProc = WndProc; // <= ���� ����
    wcex.cbClsExtra = 0; // �Ű�Ƚᵵ ��
    wcex.cbWndExtra = 0; // �Ű�Ƚᵵ ��.
    wcex.hInstance = _hInstance;
    wcex.hIcon = nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor = nullptr;//LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName = "GameWindow";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // �Ʒ��� �Լ��� ������ 
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

    // �����ڵ带 �������ִ� �Լ� ������ ���⼭�� ���� �ʿ� ������.
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
    // �����츦 �ѹ� ��������.
    UpdateWindow(windowhandle_);


    HDC Devicecontext = ::GetDC(windowhandle_);
    // �̹� ������� DC�� ���ؼ� GameEngineImage�� �����ϴ�
    // �׸��� �� �Լ��� ������ GameEngineWindow���� ����ϰ� ����ڽ��ϴ�.
    // GameEngineWindow�� dc�� Ư���ϰ� ���� �����ϰڽ��ϴ�.
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

    // �����ڵ带 �������ִ� �Լ� ������ ���⼭�� ���� �ʿ� ������.
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
    // �����츦 �ѹ� ��������.
    UpdateWindow(NewWindow->windowhandle_);

    NewWindow->devicecontext_ = ::GetDC(NewWindow->windowhandle_);
    // MainWindow�����̶� ���ָ� �ȵ˴ϴ�.
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
    // ���� �־��� ��Ʈ�� Ÿ��Ʋ�ٿ� �޴����� ����� �� �༮���� ������ּ���.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);

    // 0������ �׳� ���� �⺻�̴�.
    SetWindowPos(windowhandle_, nullptr, _pos.ix(), _pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, 0);
}

void GameEngineWindow::Loop(void(*_loopFunc)()) 
{
    MSG msg;
    while (WindowOn)
    {

        // PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
        // 2��° ���ڿ� �ϳ��� ������ �ڵ��� �־��ָ�
        // PeekMessage �׶����� �� �����츸 ó�����ش�.
        // nullptr�� �־��ָ� ��ϵ� �ڵ� ���θ� ó�����ݴϴ�.
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

            // Window�޼����� �ֵ� ���� ���ư���.
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

    // ����Ϳ����� ���콺 ��ġ
    GetCursorPos(&P);

    // m_WindowHWnd ������ ��������
    ScreenToClient(windowhandle_, &P);

    return { (float)P.x, (float)P.y };
}

bool GameEngineWindow::SetMousePos(int _x, int _y)
{
    return SetCursorPos(_x, _y);
}
