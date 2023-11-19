#include <Windows.h>

HINSTANCE hInst;
HWND hWndMain;
HWND hWndChild1;
HWND hWndChild1_1; // Второй уровень дочернего окна

HBRUSH hBrushChild1 = CreateSolidBrush(RGB(255, 225, 0)); // Красный цвет
HBRUSH hBrushChild1_1 = CreateSolidBrush(RGB(206, 206, 206)); // Синий цвет

ATOM MyRegisterClass(HINSTANCE hInstance, LPCWSTR className) {
    WNDCLASSEX wcex;
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 150, 40));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    return RegisterClassEx(&wcex);
}

void CenterWindow(HWND hWnd) {
    RECT rcClient, rcDesktop;
    GetWindowRect(hWnd, &rcClient);
    GetWindowRect(GetDesktopWindow(), &rcDesktop);

    int nWidth = rcClient.right - rcClient.left;
    int nHeight = rcClient.bottom - rcClient.top;

    int nX = (rcDesktop.right - rcDesktop.left - nWidth) / 2;
    int nY = (rcDesktop.bottom - rcDesktop.top - nHeight) / 2;

    SetWindowPos(hWnd, NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    // Создание главного окна
    hWndMain = CreateWindow(L"MyWindowClass", L"Main Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWndMain) {
        return FALSE;
    }
    CenterWindow(hWndMain);

    // Показать главное окно
    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);

    // Создание первого дочернего окна
    hWndChild1 = CreateWindow(L"STATIC", L"Child Window 1",
      WS_CHILD, 280, 100, 600, 350, hWndMain, NULL, hInstance, NULL);

    if (!hWndChild1) {
        return FALSE;
    }

    //CenterWindow(hWndChild1);
    // Создание второго уровня дочернего окна для первого дочернего окна
    hWndChild1_1 = CreateWindow(L"STATIC", L"Child Window 1.1",
        WS_CHILD, 140, 60, 300, 150, hWndChild1, NULL, hInstance, NULL);
    // Показать и обновить дочерние окна
    if (!hWndChild1) {
        return FALSE;
    }

    ShowWindow(hWndChild1, nCmdShow);
    UpdateWindow(hWndChild1);

    ShowWindow(hWndChild1_1, nCmdShow);
    UpdateWindow(hWndChild1_1);

    SetWindowText(hWndChild1, L"");
    SetWindowText(hWndChild1_1, L"");

    return TRUE;
}

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Регистрация классов для главного окна и дочерних окон
    if (!MyRegisterClass(hInstance, L"MyWindowClass")) {
        return FALSE;
    }

    // Инициализация и создание окон
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    // Главный цикл сообщений
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }

    case WM_CTLCOLORSTATIC: {
        // Изменяем цвет фона для дочерних окон
        if (GetDlgItem(hWndMain, GetDlgCtrlID((HWND)lParam)) == hWndChild1) {
            SetBkColor((HDC)wParam, RGB(255, 225, 0));
            return (LRESULT)hBrushChild1;
        }
        else if (GetDlgItem(hWndMain, GetDlgCtrlID((HWND)lParam)) == hWndChild1_1) {
            SetBkColor((HDC)wParam, RGB(163, 159, 159));
            return (LRESULT)hBrushChild1_1;
        }
        break;
    }


    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}
