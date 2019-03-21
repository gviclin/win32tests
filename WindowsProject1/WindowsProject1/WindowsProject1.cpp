// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"

#include "TestAutoContext.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWndEditBox;
UINT nMsg123;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

typedef struct tagMYREC
{
	char  s1[80];
	char  s2[80];
	DWORD n;
} MYREC;

enum message_type
{
	msg_init = 0,
	msg_test1 = 1,
	msg_test2 = 2,
	msg_count = 0
};
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      30, 30, 640, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   hWndEditBox = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
	   ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
	   0, 0, 620, 200,
	   hWnd,
	   (HMENU)IDC_EDITBOX_TEXT, hInstance, NULL);


   HWND hWndClearButton = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("Send to application 1"),
	   WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | BS_DEFPUSHBUTTON,
	   200, 250, 200, 20,
	   hWnd,
	   (HMENU)IDC_SEND_BUTTON, hInstance, NULL);



   SetWindowText(hWndEditBox, _T("Appli 1 ready"));

   //Register a custom message string
   nMsg123= RegisterWindowMessage(_T("SendMessage123"));

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   CTestAutoContext context;

   context.SetState(eTOD_DOWN_ABS);





   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDC_SEND_BUTTON:
			case ID_FILE_SENDTO2:
				{
					//MessageBox(NULL, _T("Send info to application 2"), _T("Note"), MB_OK);

					//retreive the other windows
					HWND hwndAppli2 = FindWindow(NULL, _T("WindowsProject2"));
					if (hwndAppli2 == NULL)
					{
						MessageBox(NULL, _T("Application 2 is not launched."), _T("Note"), MB_OK);
						return 0;
					}

					COPYDATASTRUCT MyCDS;
					MYREC MyRec;
					memset(&MyRec, 0, sizeof(MYREC));
					MyRec.n = 20;
					for (int i = 1; i <= MyRec.n; i++)
					{
						MyRec.s1[i-1] = i;
						MyRec.s2[i-1] = MyRec.n+1 -i;
					}

					//
					// Fill the COPYDATA structure
					// 
					message_type msgType = msg_test1;
					MyCDS.dwData = (ULONG_PTR)msgType;		// type de message
					MyCDS.cbData = sizeof(MyRec);		// size of data
					MyCDS.lpData = &MyRec;				// data structure

					PostMessage(hwndAppli2, WM_COPYDATA, (WPARAM) hWnd, (LPARAM)(LPVOID)&MyCDS);


					//SendMessage(hwndAppli2, nMsg123, 0xF0F1F2F3, 0xFFFFFFFF);

					break;
				}
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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

// Message handler for about box.
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
