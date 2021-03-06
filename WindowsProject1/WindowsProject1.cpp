// WindowsProject1.cpp : Definiert den Einstiegspunkt der Anwendung.
//

#include "stdafx.h"
#include "Commctrl.h"
#include "Mmsystem.h"
#include "Windows.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100
#define IDC_BUTTON1                 3456
#define IDC_BUTTON2                 7890

// Globale Variablen:
HINSTANCE hInst;                                // Aktuelle Instanz
WCHAR szTitle[MAX_LOADSTRING];                  // Titelleistentext
WCHAR szWindowClass[MAX_LOADSTRING];            // Klassenname des Hauptfensters

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DialogMain(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Button1dialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Button2dialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Hier Code einfügen.

    // Globale Zeichenfolgen initialisieren
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    // Anwendungsinitialisierung ausführen:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Hauptnachrichtenschleife:
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


/*
//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
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
*/



//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   HWND hWnd = CreateDialogW(hInstance, MAKEINTRESOURCE(IDD_DIALOGMAIN), nullptr, DialogMain);
   
   
   CreateWindow(L"BUTTON", L"button1", WS_CHILD | WS_VISIBLE, 70, 70, 80, 25, hWnd, (HMENU)IDC_BUTTON1, hInst, 0);
   CreateWindow(L"BUTTON", L"button2", WS_CHILD | WS_VISIBLE, 70, 120, 80, 25, hWnd, (HMENU)IDC_BUTTON2, hInst, 0);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/*
//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs
//  WM_PAINT    - Darstellen des Hauptfensters
//  WM_DESTROY  - Ausgeben einer Beendenmeldung und zurückkehren
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Menüauswahl bearbeiten:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_HALLO:
				SetWindowText(hWnd, L"Hallo");
				break;
			case IDC_BUTTON1:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Button1dialog);
				break;

			case IDC_BUTTON2:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Button2dialog);
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
            //TODO: Zeichencode, der hdc verwendet, hier einfügen...
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
*/


//
//  FUNKTION: DialogMain(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster-Dialog.
//
//  WM_INITDIALOG - Startevent
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs und buttons
//  WM_HSCROLL  - Verarbeiten von Slider Controls
//
INT_PTR CALLBACK DialogMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message)
	{
		case WM_INITDIALOG:
			if (joySetCapture(hWnd, JOYSTICKID1, NULL, TRUE))
			{
				MessageBeep(MB_ICONEXCLAMATION);
				MessageBox(hWnd, L"Couldn't capture the joystick.", NULL, MB_OK | MB_ICONEXCLAMATION);
				

			}
			else
			{
				HWND mytext = GetDlgItem(hWnd, IDC_STATIC4);
				//JOYINFO *joyinfo = new JOYINFO;
				
				//joyGetPos(JOYSTICKID1, joyinfo);
				//wchar_t buf[16];
				//wsprintf(buf, L"%ld:%2d", joyinfo->wYpos, joyinfo->wXpos);
				//MessageBoxW(NULL, buf, L"joystick1 detected", MB_OK);
				//SetWindowText(mytext,buf );
				SetWindowText(mytext, L"joystick1 detected");
			}
			return (INT_PTR)TRUE;
			//break;

		case (MM_JOY1BUTTONDOWN):
		{
			//MessageBoxW(NULL, L"hi", L"joystick1 button event", MB_OK);
			
			HWND mybutton = GetDlgItem(hWnd, IDC_RADIOBUTTON1);
			HWND mytext = GetDlgItem(hWnd, IDC_STATIC5);

			wchar_t strDataToSend[32];
			wsprintf(strDataToSend, L"%d", wParam); 
			//MessageBoxW(NULL,  strDataToSend, L"wParam value", MB_OK);
			SetWindowText(mytext, strDataToSend);

			if (wParam == 0x0101) // this is button 1 on my test joystick...
			{
				//set radiobutton state to checked
				SendMessage(mybutton, BM_SETCHECK, BST_CHECKED, 1);
			}
			return (INT_PTR)TRUE;
		}

		case MM_JOY1BUTTONUP:
		{
			//MessageBoxW(NULL, L"hi", L"joystick1 button event", MB_OK);
			HWND mybutton = GetDlgItem(hWnd, IDC_RADIOBUTTON1);

			if (wParam == JOY_BUTTON1CHG)
			{
				//set radiobutton state to unchecked
				SendMessage(mybutton, BM_SETCHECK, BST_UNCHECKED, 1);

			}
			
			return (INT_PTR)TRUE; 
		}

		case MM_JOY1MOVE:
		{
			HWND mytext = GetDlgItem(hWnd, IDC_STATIC3);
			int x = LOWORD(lParam) >> 12;
			int y = HIWORD(lParam) >> 12;

			wchar_t buf[16];
			wsprintf(buf, L"%ld : %2d", x, y);


			HWND mySlider = GetDlgItem(hWnd, IDC_SLIDER1);
			HWND mytext2 = GetDlgItem(hWnd, IDC_STATIC2);

			int pos = SendMessageW(mySlider, TBM_GETPOS, 0, 0);
			
			if (x > 7)
			{
				SendMessageW(mySlider, TBM_SETPOS, TRUE, pos + (x-7));
			}
			else if (x < 7)
			{
				SendMessageW(mySlider, TBM_SETPOS, TRUE, pos - (8-x));
			}
			
			wchar_t buf2[4];
			wsprintf(buf2, L"%1d", pos);
			SetWindowText(mytext2, buf2);

			SetWindowText(mytext, buf);
			return (INT_PTR)TRUE;
		}
		

		case WM_COMMAND:
			{
			int wmId = LOWORD(wParam);
			
			// Menüauswahl bearbeiten:
			switch (wmId)
				{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					return (INT_PTR)TRUE;
				
				case IDM_EXIT:
					EndDialog(hWnd, LOWORD(wParam));
					PostQuitMessage(0);
					return (INT_PTR)TRUE;
				
				case IDM_HALLO:
					SetWindowText(hWnd, L"Hallo");
					return (INT_PTR)TRUE;
				
				case IDC_BUTTON1:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Button1dialog);
					return (INT_PTR)TRUE;

				case IDC_BUTTON2:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Button2dialog);
					return (INT_PTR)TRUE;

				

				case WM_DESTROY:
					EndDialog(hWnd, LOWORD(wParam));
					PostQuitMessage(0);
					return (INT_PTR)TRUE;

				}

			break;
			}
		case  WM_HSCROLL:
		{
			HWND mytext2 = GetDlgItem(hWnd, IDC_STATIC2);
			HWND mySlider = GetDlgItem(hWnd, IDC_SLIDER1);


			if (mySlider == (HWND)lParam)
			{

				LRESULT pos = SendMessageW(mySlider, TBM_GETPOS, 0, 0);
				wchar_t buf[4];
				wsprintfW(buf, L"%ld", pos);

				SetWindowText(mytext2, buf);

				
			}




			return (INT_PTR)TRUE;

		}
		/*case WM_SYSCOMMAND:
		{
			//61696 is type ALT value and 115 is  ASCII value of "s", so the accelerator is "ALT+S"
			if (LOWORD(wParam) == 61696 && LOWORD(lParam) == 115)
			{ }
			return (INT_PTR)TRUE;
		}*/


		
	}
	return (INT_PTR)FALSE;
	
}





// Meldungshandler für Dialog1
INT_PTR CALLBACK Button1dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		//break;
	}
	return (INT_PTR)FALSE;
}

// Meldungshandler für Dialog2
INT_PTR CALLBACK Button2dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			HWND mytext = GetDlgItem(hDlg, IDC_STATIC1);
			SetWindowText(mytext, L"cancel was pressed");
			Sleep(1000);
			EndDialog(hDlg, LOWORD(wParam));
			//PostQuitMessage(0);
			return (INT_PTR)TRUE;
		}
		
		
	}
	return (INT_PTR)FALSE;
}

// Meldungshandler für Infofeld.
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