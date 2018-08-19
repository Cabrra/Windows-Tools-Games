
#include <Windows.h> // Include the Windows API (Win32 Application Programming Interface)
#include <tchar.h> // Include UNICODE support
#include <sstream> // Include ostringstream support
#include <fstream>
using namespace std;
#include <iostream>
#include <ctime>

#include <commdlg.h> // Include the Common Dialogs.
#include <process.h> // Include Multi-Threading functions.
#include "resource.h" // Include the resource script IDs.
#include "Game.h" // Include the Game Class.

using std::wostringstream;

#define MAX_LOADSTRING 100

Game pong; // The Game Instance (only global temporarily).


// Foward Declarations:
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnPaint(HWND hWnd);
void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

void OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnUntitledExit(HWND hWnd);
void OnLoad(HWND hWnd);
void OnSave(HWND hWnd);
void ContacInfo(HWND);
int CaptureScreen(HWND);
void OnPause(HWND);
D2D1_COLOR_F OnOptionsColor(HWND);

void OnRandomColor(HWND);
void OnWinner(HWND);


void ToggleFullscreenMode(HWND hWnd, BOOL bFullScreen);


TCHAR szOnePlayer[MAX_LOADSTRING];
TCHAR szTwoPlayer[MAX_LOADSTRING];
TCHAR szDemoMode[MAX_LOADSTRING];
TCHAR szCharacterSelect[MAX_LOADSTRING];
TCHAR szBack[MAX_LOADSTRING];
TCHAR szStart[MAX_LOADSTRING];
TCHAR szBoss[MAX_LOADSTRING];
TCHAR szSelect[MAX_LOADSTRING];
TCHAR szInstruction[MAX_LOADSTRING];
TCHAR szLoad[MAX_LOADSTRING];
TCHAR szExit[MAX_LOADSTRING];

// Entry point function for the game:
unsigned int WINAPI GameMain(void* lpvArgList);


// The Entry Point function
int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, // Always NULL
	LPTSTR	lpCmdLine,
	int		iCmdShow)
{
	lpCmdLine;
	hPrevInstance;
	// Initialize the COM Library.
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);


	// Step 1: Initialize the Window Class.
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(MY_CURSOR)));
	wcex.hInstance = hInstance;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc; // Function to send Windows Message to for processing.
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_REALTIME);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(MY_ICON));
	wcex.hCursor = LoadCursor(wcex.hInstance, MAKEINTRESOURCE(MY_CURSOR));
	wcex.lpszClassName = _T("REALTIMEWND"); // Name to identify this Window Class.
	RegisterClassEx(&wcex);



	// Step 2: Create the Main Window.
	HWND hWnd = CreateWindow(wcex.lpszClassName,
		_T("Real-Time Skeleton"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		816, 642,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
		//DWORD err = GetLastError();
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to create main window!"),
			_T("Program Name"), MB_OK | MB_ICONERROR);
		return -1;
	}

	SetWindowText(hWnd, _T("Psycho Pong"));

	// Attach game instance
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)&pong);

	// Step 2.5: Create the Game thread:
	pong.hGameThread = (HANDLE)_beginthreadex(NULL, 0,
		GameMain, (void*)hWnd, 0, NULL);
#ifdef _DEBUG
	Sleep(1);  // Sleep after thread creation for debugging to work properly.
#endif

	// Load strings

	LoadString(hInstance, IDS_ONEPLAYER, szOnePlayer, MAX_LOADSTRING);
	LoadString(hInstance, IDS_TWOPLAYER, szTwoPlayer, MAX_LOADSTRING);

	LoadString(hInstance, IDS_DEMOMODE, szDemoMode, MAX_LOADSTRING);
	LoadString(hInstance, IDS_BACK, szBack, MAX_LOADSTRING);
	LoadString(hInstance, IDS_START, szStart, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EXIT, szExit, MAX_LOADSTRING);
	LoadString(hInstance, IDS_BOSS, szBoss, MAX_LOADSTRING);
	LoadString(hInstance, IDS_SELECTT, szSelect, MAX_LOADSTRING);
	LoadString(hInstance, IDS_CHARSELECT, szCharacterSelect, MAX_LOADSTRING);
	LoadString(hInstance, IDS_CHARSELECT, szInstruction, MAX_LOADSTRING);
	LoadString(hInstance, IDS_LOAD, szLoad, MAX_LOADSTRING);


	// Step 3: Show the Main Window.
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);


	HACCEL hAccelTable;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_REALTIME));

	// Step 4: Enter the Main Message Loop.
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) // Getting WM_QUIT makes GetMessage return FALSE.
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}




	// Initialize COM
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr))
	{
		return FALSE;
	}

	// Initialize global strings
	/*LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);

	LoadString(hInstance, IDS_NEWGAME, szNewGame, MAX_LOADSTRING);
	LoadString(hInstance, IDS_LOADGAME, szLoadGame, MAX_LOADSTRING);
	LoadString(hInstance, IDS_AIONOFF, szAIOn, MAX_LOADSTRING);
	LoadString(hInstance, IDS_INSTRUC, szInstruction, MAX_LOADSTRING);
	LoadString(hInstance, IDS_CREDITS, szCredits, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EXIT, szExit, MAX_LOADSTRING);
	LoadString(hInstance, IDS_XWIN, szXwins, MAX_LOADSTRING);
	LoadString(hInstance, IDS_OWIN, szOwins, MAX_LOADSTRING);
	LoadString(hInstance, IDS_TIES, szTies, MAX_LOADSTRING);*/


	// Uninit COM
	CoUninitialize();

	// Destroy the Game Thread:
	CloseHandle(pong.hGameThread);


	return msg.wParam;
}


// Entry point function for the game:
unsigned int WINAPI GameMain(void* lpvArgList)
{
	// Initialize the COM Library.
	CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);

	// Increase the accuracy/precision of the Windows timer:
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);


	// Get the HWND value out of the ArgList parameter.
	HWND hWnd = (HWND)lpvArgList;

	//Get pong from window data

	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	pong->SetHwnd(hWnd);
	pong->Startup();
	pong->TittleScreen();
		

	while (pong->bRunning)
	{
		pong->Input();
		pong->AI();
		pong->Simulate();
		pong->Render();
		if (pong->GetWinner())
			OnWinner(hWnd);
			// 1 Frame == 1 iteration of Input, Simulate, & Render
	}

	pong->Shutdown();


	// Restore the accuracy/precision of the Windows timer:
	timeEndPeriod(tc.wPeriodMin);

	// Uninitialize the COM Library.
	CoUninitialize();

	return 0;
}


// Step 5: Write the Window Procedure
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	switch (uMsg)
	{
		// Handle Window Creation:
	case WM_CREATE:
		break;

		// Handle Close Button [X] Pressed:
	case WM_CLOSE:
	{
					 //Get pong from window data

					 Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
					 // Begin GameMain shutdown.
					 pong->bRunning = FALSE;

					 // Wait until Game Thread terminates.
					 WaitForSingleObject(pong->hGameThread, INFINITE);

					 // Begin WinMain shutdown.
					 DestroyWindow(hWnd);
					 break;

	}
		// Handle Window Destruction:
	case WM_DESTROY:
		PostQuitMessage(0); // Put the WM_QUIT message in the message queue.
		break;


		// Handle Window Rendering:
	case WM_PAINT: //(output)
		OnPaint(hWnd);
		break;

		// Handle Left Mouse Button Clicked:
	case WM_LBUTTONDOWN: //(input)
		OnLButtonDown(hWnd, wParam, lParam);
		break;

	case WM_RBUTTONDOWN: //(input)
		OnRButtonDown(hWnd, wParam, lParam);
		break;

		// Handle keyboard input:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
						//Get pong from window data

						Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						GetKeyboardState(pong->keys);
						DefWindowProc(hWnd, uMsg, wParam, lParam);
						break;
	}
		// Handle window activation:
	case WM_ACTIVATE:
	{
						//Get pong from window data

						Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						if (LOWORD(wParam) != WA_INACTIVE)
							GetKeyboardState(pong->keys);
						else
							ZeroMemory(pong->keys, 256);
						break;
	}


		//case WM_SIZE:
		//	{
		//		// Resize the Render Target based upon the new client.
		//		D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));
		//		pRT->Resize(size);
		//	}
		//	break;

		// Handle Menu Items:
	case WM_COMMAND:
		OnCommand(hWnd, wParam, lParam);
		break;

	default:
		// Allow Windows to perform default processing.
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void OnPaint(HWND hWnd)
{
	ValidateRect(hWnd, NULL); // VERY IMPORTANT - Clear the Invalid flag
}

void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	wParam;
	RECT rc;
	GetClientRect(hWnd, &rc);

	POINT ptMouse;


	ptMouse.x = LOWORD(lParam); // Bits 0-15 contain the X Axis position
	ptMouse.y = HIWORD(lParam); // Bits 16-31 contain the Y Axis position

	pong->SetMouseL(ptMouse);


	InvalidateRect(hWnd, NULL, TRUE);
}

void OnRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	wParam;
	RECT rc;
	GetClientRect(hWnd, &rc);

	POINT ptMouse;


	ptMouse.x = LOWORD(lParam); // Bits 0-15 contain the X Axis position
	ptMouse.y = HIWORD(lParam); // Bits 16-31 contain the Y Axis position

	pong->SetMouseR(ptMouse);


	InvalidateRect(hWnd, NULL, TRUE);
}


void OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	lParam;
	int menuid = LOWORD(wParam);
	switch (menuid)
	{
	case ID_PAUSE:
		OnPause(hWnd);
		break;
	case IDM_FILE_NEW:{
						  Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						  OnUntitledExit(hWnd);
						  pong->Reset();
						  break;
	}
	case ID_COLORSELECT_GRADIENT1:
	{
									 Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
									 SuspendThread(pong->hGameThread);
									 D2D1_COLOR_F one;

									 one = OnOptionsColor(hWnd);
									 pong->SetGradient1(one);
									 ResumeThread(pong->hGameThread);
									 InvalidateRect(hWnd, NULL, TRUE);
									 break;
	}
	case ID_COLORSELECT_GRADIENT2:
	{
									 Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
									 SuspendThread(pong->hGameThread);
									 D2D1_COLOR_F two;

									 two = OnOptionsColor(hWnd);
									 pong->SetGradient2(two);
									 ResumeThread(pong->hGameThread);
									 InvalidateRect(hWnd, NULL, TRUE);
									 break;
	}
	case ID_COLORSELECT_RANDOM:
	{
								  Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
								  SuspendThread(pong->hGameThread);
								  OnRandomColor(hWnd);

								  ResumeThread(pong->hGameThread);
								  InvalidateRect(hWnd, NULL, TRUE);
								  break;
	}
	case ID_BALLS_TWO:
	{
						 Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
						 mii.fMask = MIIM_STATE;
						 GetMenuItemInfo(GetMenu(hWnd), ID_BALLS_TWO, FALSE, &mii);
						 if (mii.fState == MFS_CHECKED){
							 mii.fState = MFS_UNCHECKED;
							 SetMenuItemInfo(GetMenu(hWnd), ID_BALLS_TWO, FALSE, &mii);
							 pong->SetBalls(false);
						 }
						 else{
							 mii.fState = MFS_CHECKED;
							 SetMenuItemInfo(GetMenu(hWnd), ID_AI_AI2ON, FALSE, &mii);
							 pong->SetBalls(true);
						 }


						 break;
	}
	case ID_AI_AI2ON:
	{
						Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
						mii.fMask = MIIM_STATE;
						GetMenuItemInfo(GetMenu(hWnd), ID_AI_AI2ON, FALSE, &mii);
						if (mii.fState == MFS_CHECKED){
							mii.fState = MFS_UNCHECKED;
							SetMenuItemInfo(GetMenu(hWnd), ID_AI_AI2ON, FALSE, &mii);
							pong->SetPlayers(2);
						}
						else{
							mii.fState = MFS_CHECKED;
							SetMenuItemInfo(GetMenu(hWnd), ID_AI_AI2ON, FALSE, &mii);
							pong->SetPlayers(1);
						}


						break;
	}
	case ID_AI_DEMO:
	{
						Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
						mii.fMask = MIIM_STATE;
						GetMenuItemInfo(GetMenu(hWnd), ID_AI_DEMO, FALSE, &mii);
						if (mii.fState == MFS_CHECKED){
							mii.fState = MFS_UNCHECKED;
							SetMenuItemInfo(GetMenu(hWnd), ID_AI_DEMO, FALSE, &mii);
							pong->SetPlayers(1);
						}
						else{
							mii.fState = MFS_CHECKED;
							SetMenuItemInfo(GetMenu(hWnd), ID_AI_DEMO, FALSE, &mii);
							pong->SetPlayers(0);
						}


						break;
	}
	case ID_OPTIONS_FPS:
	{
						   Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
						   MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
						   mii.fMask = MIIM_STATE;
						   GetMenuItemInfo(GetMenu(hWnd), ID_OPTIONS_FPS, FALSE, &mii);
						   if (mii.fState == MFS_CHECKED){
							   mii.fState = MFS_UNCHECKED;
							   SetMenuItemInfo(GetMenu(hWnd), ID_OPTIONS_FPS, FALSE, &mii);
							   pong->SetFPS(true);
						   }
						   else{
							   mii.fState = MFS_CHECKED;
							   SetMenuItemInfo(GetMenu(hWnd), ID_OPTIONS_FPS, FALSE, &mii);
							   pong->SetFPS(false);
						   }


						   break;
	}
	case ID_OPTIONS_TOGGLEFULLSCREEN:
		ToggleFullscreenMode(hWnd, TRUE);
		break;
	case ID_HELP_CONTACTINFO:
		ContacInfo(hWnd);
		break;
	case ID_FILE_SAVEAS:
		OnSave(hWnd);
		break;
	case ID_FILE_LOAD:
		OnLoad(hWnd);
		break;
	case ID_SCREENSHOOT:
		CaptureScreen(hWnd);
		break;
	case IDM_FILE_EXIT:
		PlaySound(NULL, NULL, NULL);
		PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
		
		PostMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	}
}


// Function that toggles a window between fullscreen and windowed mode:
void ToggleFullscreenMode(HWND hWnd, BOOL bFullScreen)
{
	static WINDOWPLACEMENT wp = { 0 };
	static HMENU hMenu = NULL;

	if (bFullScreen)
	{
		// Remember the window position.
		wp.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(hWnd, &wp);

		// Remove the window's title bar.
		SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP);

		// Put the changes to the window into effect.
		SetWindowPos(hWnd, 0, 0, 0, 0, 0,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

		// Remember the menu, then remove it.
		hMenu = GetMenu(hWnd);
		SetMenu(hWnd, NULL);

		// Switch to the requested display mode.
		//SetDisplayMode(iWidth, iHeight, iBpp, iRefreshRate);

		// Position the window to cover the entire screen.
		SetWindowPos(hWnd, HWND_TOPMOST,
			0, 0,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_SHOWWINDOW);

		// Remove the cursor.
		ShowCursor(FALSE);
	}
	else
	{
		// Restore the window's title bar.
		SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// Put the changes to the window into effect.
		SetWindowPos(hWnd, 0, 0, 0, 0, 0,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

		// Restore the window's menu.
		SetMenu(hWnd, hMenu);

		// Restore the display mode.
		//SetDisplayMode(0, 0, 0, 0);

		// Restore the window's original position.
		SetWindowPlacement(hWnd, &wp);

		// Restore the cursor.
		ShowCursor(TRUE);
	}
}


void OnSave(HWND hWnd){

	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	SuspendThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);

	WCHAR szFilters[MAX_PATH] = _T("Text Files (*.txt)\0*.txt\0\0");
	TCHAR szFilePathName[_MAX_PATH] = _T("");
	OPENFILENAME saveFileDialog = { 0 };
	saveFileDialog.lStructSize = sizeof(OPENFILENAME);
	saveFileDialog.hwndOwner = hWnd;
	saveFileDialog.lpstrFilter = szFilters;
	saveFileDialog.lpstrFile = szFilePathName;  // This will hold the file name
	saveFileDialog.lpstrDefExt = _T("txt");
	saveFileDialog.nMaxFile = _MAX_PATH;
	saveFileDialog.lpstrTitle = _T("Save File");
	saveFileDialog.Flags = OFN_OVERWRITEPROMPT;

	// Open the file save dialog, and choose the file name
	if (GetSaveFileName(&saveFileDialog)){

		ofstream fin;
		fin.open(szFilePathName);

		if (fin.is_open()){

			fin << pong->GetPlayers() << '\n';
			fin << pong->GetP1Score() << '\n';
			fin << pong->GetP2Score() << '\n';

			fin << pong->GetP1Power() << '\n';
			fin << pong->GetP2Power() << '\n';

			fin << pong->GetRightPaddlePath() << '\n';
			fin << pong->GetLeftPaddlePath() << '\n';
		}
		fin.close();
	}

	SetWindowText(hWnd, szFilePathName);
	ResumeThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);
}

void OnLoad(HWND hWnd){
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	SuspendThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);

	OnUntitledExit(hWnd);
	WCHAR szFilters[MAX_PATH] = _T("Text Files (*.txt)\0*.txt\0\0");
	TCHAR szFilePathName[_MAX_PATH] = _T("");
	OPENFILENAME openFileDialog = { 0 };
	//WCHAR szFileName[MAX_PATH];
	ZeroMemory(&openFileDialog, sizeof(openFileDialog));
	openFileDialog.lStructSize = sizeof(openFileDialog);
	openFileDialog.hwndOwner = hWnd;
	openFileDialog.lpstrFilter = szFilters;
	openFileDialog.lpstrFile = szFilePathName;
	openFileDialog.nMaxFile = MAX_PATH;
	openFileDialog.lpstrTitle = _T("Load File");
	openFileDialog.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	openFileDialog.lpstrDefExt = _T("txt");

	if (GetOpenFileName(&openFileDialog)){
		ifstream fout;
		fout.open(szFilePathName);

		if (fout.is_open()){
			int power1, power2, score1, score2, players;
			string path1, path2;

			fout >> players;
			fout >> score1;
			fout >> score2;
			fout >> power1;
			fout >> power2;
			getline(fout, path1, '\n');
			getline(fout, path2, '\n');


			pong->SetPlayers(players);
			pong->SetP1Score(score1);
			pong->SetP2Score(score2);
			pong->SetP1Power(power1);
			pong->SetP2Power(power2);

			pong->SetRightPaddle(path1);
			pong->SetLeftPaddle(path2);

		}
		fout.close();
	}

	SetWindowText(hWnd, szFilePathName);
	ResumeThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);
}


void OnUntitledExit(HWND hWnd){
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	SuspendThread(pong->hGameThread);

	wchar_t  szName[MAX_PATH];
	GetWindowText(hWnd, szName, MAX_PATH);
	wchar_t  compare[MAX_PATH] = _T("Untitled");
	if (wcscmp(szName, compare) == 0){
		if (IDYES == MessageBox(hWnd, L"Do you want to save changes to Untitled?", L"Last chance saving...", MB_YESNOCANCEL | MB_ICONQUESTION)){
			OnSave(hWnd);
		}
	}
	ResumeThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);
}

void ContacInfo(HWND hWnd)
{
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	SuspendThread(pong->hGameThread);
	if (IDYES == MessageBox(hWnd, L"Author: Jagoba \"Jake\" Marcos\nEmail: jag_141@hotmail.com", L"Contact Info...", MB_OK)){
		ResumeThread(pong->hGameThread);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}

int CaptureScreen(HWND hWnd)
{
	HDC hdcScreen;
	HDC hdcWindow;
	HDC hdcMemDC = NULL;
	HBITMAP hbmScreen = NULL;
	BITMAP bmpScreen;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL);
	hdcWindow = GetDC(hWnd);

	// Create a compatible DC which is used in a BitBlt from the window DC
	hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!hdcMemDC)
	{
		MessageBox(hWnd, L"CreateCompatibleDC has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the client area for size calculation
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	//This is the best stretch mode
	SetStretchBltMode(hdcWindow, HALFTONE);

	//The source DC is the entire screen and the destination DC is the current window (HWND)
	if (!StretchBlt(hdcWindow,
		0, 0,
		rcClient.right, rcClient.bottom,
		hdcScreen,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY))
	{
		MessageBox(hWnd, L"StretchBlt has failed", L"Failed", MB_OK);
		goto done;
	}

	// Create a compatible bitmap from the Window DC
	hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

	if (!hbmScreen)
	{
		MessageBox(hWnd, L"CreateCompatibleBitmap Failed", L"Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(hdcMemDC,
		0, 0,
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		hdcWindow,
		0, 0,
		SRCCOPY))
	{
		MessageBox(hWnd, L"BitBlt has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the BITMAP from the HBITMAP
	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	GetDIBits(hdcWindow, hbmScreen, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile(L"ScreenShot.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	//Clean up
done:
	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

	return 0;
}

void OnPause(HWND hWnd){

	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (pong->GetPause()){
		pong->SetPause(false);
		ResumeThread(pong->hGameThread);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	else{
		pong->SetPause(true);
		pong->Render();
		InvalidateRect(hWnd, NULL, TRUE);
		SuspendThread(pong->hGameThread);
	}
}

D2D1_COLOR_F OnOptionsColor(HWND hWnd)
{
	// Array of COLORREFs used to store the custom colors.
	D2D1_COLOR_F store = D2DColor(Red);
	static COLORREF clrarrCustom[16] =
	{
		RGB(0, 0, 0), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
		RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255),
		RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255),
		RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255),
	};

	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;
	cc.Flags = CC_RGBINIT;
	cc.lpCustColors = clrarrCustom;

	// Convert from D2D1_COLOR_F to COLORREF
	cc.rgbResult = RGB(store.r * 255.0f, store.g * 255.0f, store.b * 255.0f);

	// Invoke the Color Selection dialog.
	if (ChooseColor(&cc))
	{
		// NOTE: The selected color is stored in the cc.rgbResult variable.
		// Convert from COLORREF to D2D1_COLOR_F
		store.r = (FLOAT)GetRValue(cc.rgbResult) / 255.0f;
		store.g = (FLOAT)GetGValue(cc.rgbResult) / 255.0f;
		store.b = (FLOAT)GetBValue(cc.rgbResult) / 255.0f;

		// Repaint the screen.
		InvalidateRect(hWnd, NULL, TRUE);
	}
	return store;
}

void OnRandomColor(HWND hWnd){

	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	D2D1_COLOR_F gradientColor1 = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	D2D1_COLOR_F gradientColor2 = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));

	pong->SetGradient1(gradientColor1);
	pong->SetGradient2(gradientColor2);
}

void OnWinner(HWND hWnd){
	Game* pong = (Game*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	//SuspendThread(pong->hGameThread);
	int win = pong->GetWinner();
	if (win == 1){
		PlaySound(NULL, NULL, NULL);
		PlaySound(TEXT("Music//Success.wav"), NULL, SND_FILENAME | SND_ASYNC);

		int rowWins = pong->GetWins();
		rowWins++;
		pong->SetWins(rowWins);
		InvalidateRect(hWnd, NULL, TRUE);
		if (IDYES == MessageBox(hWnd, L"PLAYER ONE WON!!\n\nDo you want to play again?", L"Repeat...", MB_YESNO | MB_ICONQUESTION))
		{

			if (pong->GetP2Score() == 0){
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_DOMINATION, FALSE, &mii);
				mii.fState = MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_DOMINATION, FALSE, &mii);
			}
			MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
			mii.fMask = MIIM_STATE;
			GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_FIRSTBLOOD, FALSE, &mii);
			mii.fState = MFS_CHECKED;
			SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_FIRSTBLOOD, FALSE, &mii);


			if (rowWins == 3){
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_ONFIRE, FALSE, &mii);
				mii.fState = MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_ONFIRE, FALSE, &mii);
			}

			pong->Reset();
			pong->SetWinner(0);
		}
		else{
			pong->GameExit();
			TerminateThread(pong->hGameThread, 0);
			
			PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
			DestroyWindow(hWnd);
		}
	}
	if (win == 2){
		InvalidateRect(hWnd, NULL, TRUE);
		if (IDYES == MessageBox(hWnd, L"PLAYER TWO WON!!\n\nDo you want to play again?", L"Repeat...", MB_YESNO | MB_ICONQUESTION))
		{

			pong->Reset();
			pong->SetWins(0);
			pong->SetWinner(0);
		}
		else{
			pong->GameExit();
			TerminateThread(pong->hGameThread, 0);
			
			PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
			DestroyWindow(hWnd);
		}

	}
	//ResumeThread(pong->hGameThread);
	InvalidateRect(hWnd, NULL, TRUE);
}