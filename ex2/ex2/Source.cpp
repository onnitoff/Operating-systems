#include <Windows.h>
#define IDM_MODAL_DIALOG        101
#define IDM_SYSTEM_MODAL_DIALOG 102
#define IDM_NON_MODAL_DIALOG    103
#define IDM_STANDARD_DIALOG     104
#define IDD_DIALOG              105
#define IDD_OPTIONS_DIALOG       106
// ���������� ����������
HINSTANCE hInst;
HWND hMainWindow, hButton, hEdit, hList;
HMENU hMenu;
HWND hwndOwner;

RECT rc, rcDlg, rcOwner;
// ��������� �������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;

    // ����������� ������ ����
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"MyAppClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(nullptr, L"�� ������� ���������������� ����� ����.", L"������", MB_ICONERROR | MB_OK);
        return 1;
    }

    // �������� �������� ����
    hMainWindow = CreateWindow(L"MyAppClass", L"������ ����������", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, nullptr, nullptr, hInstance, nullptr);

    if (!hMainWindow) {
        MessageBox(nullptr, L"�� ������� ������� ������� ����.", L"������", MB_ICONERROR | MB_OK);
        return 1;
    }

    // �������� ������
    hButton = CreateWindow(L"BUTTON", L"����� ����", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 120, 30, hMainWindow, nullptr, hInstance, nullptr);

    // �������� ���� ��� �����
    hEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        10, 50, 200, 30, hMainWindow, nullptr, hInstance, nullptr);

    // �������� ������
    hList = CreateWindow(L"LISTBOX", L"", WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY,
        10, 90, 200, 120, hMainWindow, nullptr, hInstance, nullptr);

    // ���������� ��������� � ������
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"������� 1");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"������� 2");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"������� 3");

    // �������� ����
    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, IDM_MODAL_DIALOG, L"��������� ������");
    AppendMenu(hMenu, MF_STRING, IDM_SYSTEM_MODAL_DIALOG, L"��������� ��������� ������");
    AppendMenu(hMenu, MF_STRING, IDM_NON_MODAL_DIALOG, L"����������� ������");
    AppendMenu(hMenu, MF_STRING, IDM_STANDARD_DIALOG, L"����������� ������");
    SetMenu(hMainWindow, hMenu);

    // ����������� � ���������� �������� ����
    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

    // ������� ���� ���������
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ���������� ��������� ��� �������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDM_MODAL_DIALOG:
            MessageBox(hWnd, L"��� ��������� ������", L"����������", MB_OK | MB_ICONINFORMATION);
            break;
        case IDM_SYSTEM_MODAL_DIALOG:
            MessageBox(nullptr, L"��� ��������� ��������� ������", L"����������", MB_SYSTEMMODAL | MB_OK | MB_ICONINFORMATION);
            break;
        case IDM_NON_MODAL_DIALOG:
            DialogBox(hInst, (LPCTSTR)IDD_OPTIONS_DIALOG, hMainWindow, DialogProc);
            break;
        case IDM_STANDARD_DIALOG:
            OPENFILENAME ofn;
            wchar_t szFileName[MAX_PATH] = L"";
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = L"��������� ����� (*.txt)\0*.txt\0��� ����� (*.*)\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = L"txt";
            if (GetOpenFileName(&ofn)) {
                MessageBox(hWnd, szFileName, L"��������� ����", MB_OK | MB_ICONINFORMATION);
            }
            break;
        }
        break;

 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���������� ��������� ��� ������������ �������
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        if ((hwndOwner = GetParent(hDlg)) == NULL)
        {
            hwndOwner = GetDesktopWindow();
        }
        GetWindowRect(hwndOwner, &rcOwner);
        GetWindowRect(hDlg, &rcDlg);
        CopyRect(&rc, &rcOwner);

        OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
        OffsetRect(&rc, -rc.left, -rc.top);
        OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);
        SetWindowPos(hDlg,
            HWND_TOP,
            rcOwner.left + (rc.right / 2),
            rcOwner.top + (rc.bottom / 2),
            0, 0, // ignores size arguments
            SWP_NOSIZE);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
