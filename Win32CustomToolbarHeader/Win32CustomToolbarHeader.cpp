// Win32CustomToolbarHeader.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "Win32CustomToolbarHeader.h"

#define MAX_LOADSTRING 100

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    // Initialise les chaînes globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CONDUCTIVITYTESTBENCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONDUCTIVITYTESTBENCH));

    MSG msg;

    // Boucle de messages principale :
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONDUCTIVITYTESTBENCH));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONDUCTIVITYTESTBENCH);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Stocke le handle d'instance dans la variable globale

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analyse les sélections de menu :
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_CONNECTMODE:
            MessageBox(0, L"Connecter", 0, 0);
            break;
        case IDC_NEW:
            MessageBox(0, L"Nouveau", 0, 0);
            break;
        case IDC_LOAD:
            MessageBox(0, L"Charger", 0, 0);
            break;
        case IDC_SAVE:
            MessageBox(0, L"Sauvegarder", 0, 0);
            break;
        case IDC_EXPERTMODE:
            MessageBox(0, L"Oscilloscope", 0, 0);
            break;

        case IDM_EXIT:
            if (MessageBox(hWnd, TEXT("Close the program?"), TEXT("Close"),
                MB_ICONQUESTION | MB_YESNO) == IDYES)
            {
                DestroyWindow(hWnd);
            }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_INITDIALOG:
    {
        OnInitDlg(hWnd);
    }
    break;
    case WM_CREATE:
    {
        OnCreate(hWnd);
    }
    break;
    case WM_SIZE:
    {
        OnSize(hWnd);
    }
    break;
    case WM_PAINT:
    {
        OnDraw(hWnd);
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void OnInitDlg(HWND hwnd)
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCtrls.dwICC = ICC_STANDARD_CLASSES;
    BOOL bInit = InitCommonControlsEx(&InitCtrls);
}



void OnCreate(HWND hwnd)
{
    /**************************************************
    *
    * StatusBar
    *
    */
    HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
        hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
    SetWindowText(hStatus, L"Connect your instrument first");
    /**************************************************
    *
    * Toolbar
    *
    */
    CreateCustomToolbar(hwnd);
}

void OnSize(HWND hwnd)
{
    // Size status bar and get height

    HWND hStatus = GetDlgItem(hwnd, IDC_MAIN_STATUS);
    SendMessage(hStatus, WM_SIZE, 0, 0);
    CreateCustomToolbar(hwnd);
}
void OnDraw(HWND hwnd)
{
    /////////////////////////////////////
    //////// Draw the logo on top
    /////////////////////////////////////
    RECT clientarea;
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &clientarea);

    /***********************************************
    *
    * Dessine le logo ARaymond
    */

    HBITMAP hBmp;
    BITMAP bm;
    hBmp = LoadBitmap(GetModuleHandle(0), L"ARAYMONDLOGO");
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBmp);
    GetObject(hBmp, sizeof(bm), &bm);
    if (clientarea.right > bm.bmWidth && clientarea.bottom > bm.bmHeight)
    {
        StretchBlt(hdc, (clientarea.right / 2) - bm.bmWidth / 2, (clientarea.bottom / 2) - bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    }
    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
    DeleteObject(hBmp);

    EndPaint(hwnd, &ps);




}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
