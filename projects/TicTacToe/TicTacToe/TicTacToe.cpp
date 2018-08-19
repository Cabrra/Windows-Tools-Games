// TicTacToe.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "TicTacToe.h"
#include <iostream>

#include <Mmsystem.h>
using namespace std;

#include <fstream>



#define MAX_LOADSTRING 100

class Game
{
public:
	bool AILevel;
	int xwins, owins, ties;
	bool isXturn;
	unsigned int board[3][3]; // 1-X 2-O 0-B, enum{XMARK,OMARK,BLANK} 'X' 'O' ' '

	bool music;
	unsigned int turn, redo;
	unsigned int undoBoard[3][3];
	unsigned int redoBoard[3][3];

	Game()
	{
		music = true;
		xwins = 0;
		owins = 0;
		ties = 0;
		turn = 1;
		redo = 1;
		isXturn = true;
		AILevel = false;
		board[0][0] = 0;
	}

	int WhoWon(){
		int countH = 1; //horizontal
		int countV = 1; //vertical

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				countH *= board[i][j];
				countV *= board[j][i];
			}
			if (countH == 1 || countV == 1)
				return 1;
			if (countH == 8 || countV == 8)
				return 2;
			countH = 1;
			countV = 1;
		}

		if ((board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) || (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1))
			return 1; // Cross check
		if ((board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) || (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2))
			return 2; // Cross check

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (board[i][j] == 0)
					return -1;
			}
		}
		return 0;

	}
};

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

TCHAR szNewGame[MAX_LOADSTRING];
TCHAR szLoadGame[MAX_LOADSTRING];
TCHAR szAIOn[MAX_LOADSTRING];
TCHAR szInstruction[MAX_LOADSTRING];
TCHAR szCredits[MAX_LOADSTRING];
TCHAR szExit[MAX_LOADSTRING];
TCHAR szXwins[MAX_LOADSTRING];
TCHAR szOwins[MAX_LOADSTRING];
TCHAR szTies[MAX_LOADSTRING];

//static DWORD dwSpanish =
//MAKELCID(MAKELANGID(LANG_SPANISH, SUBLANG_DEFAULT));
//
//static DWORD dwEnglish =
//MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT));


//POINT ptMouse;
Game myGame;

short rowWins = 0;
bool english = true;
D2D1_RECT_F hollow = D2D1::RectF(0, 0, 150, 150);

//menu items
//300, 0, 500, 50);
D2D1_RECT_F NewGameRect = D2D1::RectF(200, 60, 400, 110);
D2D1_RECT_F LoadGameRect = D2D1::RectF(200, 120, 400, 170);
D2D1_RECT_F AIOnOffRect = D2D1::RectF(200, 180, 400, 230);
D2D1_RECT_F InstructionRect = D2D1::RectF(200, 240, 400, 290);
D2D1_RECT_F CreditsRect = D2D1::RectF(200, 300, 400, 350);
D2D1_RECT_F ExitRect = D2D1::RectF(200, 360, 400, 410);

int win = -2;


// Direct2D
HRESULT CreateGraphics(HWND hWnd);
void DestroyGraphics();

ID2D1Factory* pD2DFactory = NULL;
ID2D1HwndRenderTarget* pRT = NULL;
ID2D1SolidColorBrush *pBrush = NULL;

IDWriteFactory* pDWFactory = NULL;
IDWriteTextFormat* pTF = NULL;

D2D1_RECT_F rect = D2D1::RectF(0, 0, 100, 100);


D2D1_COLOR_F bkgndColor = D2D1::ColorF(D2D1::ColorF::White);
D2D1_COLOR_F gridLinesColor = D2D1::ColorF(D2D1::ColorF::Black);
D2D1_COLOR_F playerOneColor = D2D1::ColorF(D2D1::ColorF::Black);
D2D1_COLOR_F playerTwoColor = D2D1::ColorF(D2D1::ColorF::Black);
D2D1_COLOR_F scoreBoardColor = D2D1::ColorF(D2D1::ColorF::Black);
D2D1_COLOR_F winnerLineColor = D2D1::ColorF(D2D1::ColorF::Green);
D2D1_COLOR_F gradientColor1 = D2D1::ColorF(D2D1::ColorF::BurlyWood);
D2D1_COLOR_F gradientColor2 = D2D1::ColorF(D2D1::ColorF::Yellow);

bool AION = true;

bool myMenuTitle = true;
//bool myGameTicTac;

unsigned char achievements = 0;


HCURSOR myCursor;

FLOAT gridLinesWidth = 5.0F;
FLOAT scoreBoardLinesWidth = 5.0F;
FLOAT playerOneLinesWidth = 5.0F;
FLOAT playerTwoLinesWidth = 5.0F;

D2D1_POINT_2F ptMouse;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	Instruction(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Credits(HWND, UINT, WPARAM, LPARAM);


void ContacInfo(HWND);
void OnPaint(HWND);
void OnLButtonDown(HWND, LPARAM);
void OnFileNew(HWND);
void OnClose(HWND);
void AITurn(HWND);
void OnSize(HWND hWnd, LPARAM lParam);

D2D1_COLOR_F OnOptionsColor(HWND, D2D1_COLOR_F);
void OnRandomColor(HWND);
void OnHollowEnter(HWND);

void OnSelectFont(HWND);
void OnCursorChange(HWND);

void CheckWinner(HWND);

FLOAT OnWidthThin(HWND, FLOAT);
FLOAT OnWidthMedium(HWND, FLOAT);
FLOAT OnWidthLarge(HWND, FLOAT);

void OnRedo(HWND);
void OnUndo(HWND);

void ClearRedo();
void OnKeyDown(HWND);
void OnMouseWheel(HWND, WPARAM);

void OnSave(HWND);
void OnLoad(HWND);

void OnUntitledExit(HWND);
void OnFontSelect(HWND);

void OnRepeatCheat(HWND);
void OnXWinCheat(HWND);
void OnOWinCheat(HWND);
void OnSwapMarkCheat(HWND);

void OnMusicOnOff(HWND);
void OnEnglishChange(HWND);
void OnSpanishChange(HWND);

// The Game Class


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;


	// Initialize COM
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr))
	{
		return FALSE;
	}

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);

	LoadString(hInstance, IDS_NEWGAME, szNewGame, MAX_LOADSTRING);
	LoadString(hInstance, IDS_LOADGAME, szLoadGame, MAX_LOADSTRING);
	LoadString(hInstance, IDS_AIONOFF, szAIOn, MAX_LOADSTRING);
	LoadString(hInstance, IDS_INSTRUC, szInstruction, MAX_LOADSTRING);
	LoadString(hInstance, IDS_CREDITS, szCredits, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EXIT, szExit, MAX_LOADSTRING);
	LoadString(hInstance, IDS_XWIN, szXwins, MAX_LOADSTRING);
	LoadString(hInstance, IDS_OWIN, szOwins, MAX_LOADSTRING);
	LoadString(hInstance, IDS_TIES, szTies, MAX_LOADSTRING);

	MyRegisterClass(hInstance);
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			myGame.board[i][j] = 0;
		}
	}
	myGame.undoBoard[0][0] = { 0 };
	myGame.redoBoard[0][0] = { 0 };
	myGame.turn = 1;
	myGame.redo = 1;

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	// Uninit COM
	CoUninitialize();

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	(myGame.isXturn)? wcex.hCursor = SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(MY_CURSOR))) : 	wcex.hCursor = SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(MY_CURSORO)));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_TICTACTOE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(MY_ICON));

	return RegisterClassEx(&wcex);


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

	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SetWindowText(hWnd, _T("Tic Tac Toe"));
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int wmId, wmEvent;

	switch (message)
	{
	case WM_CREATE:
		CreateGraphics(hWnd);
		//LoadIcon()
		break;
	case WM_SETCURSOR:
		MyRegisterClass(hInst);
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel(hWnd, wParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(hWnd);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_NEW:
			OnFileNew(hWnd);
			break;
		case ID_COLORS_BACKGROUND:
			bkgndColor = OnOptionsColor(hWnd, bkgndColor);
			break;
		case ID_COLORS_GRIDLINES:
			gridLinesColor = OnOptionsColor(hWnd, gridLinesColor);
			break;
		case ID_COLORS_PLAYERONE:
			playerOneColor = OnOptionsColor(hWnd, playerOneColor);
			break;
		case ID_COLORS_PLAYERTWO:
			playerTwoColor = OnOptionsColor(hWnd, playerTwoColor);
			break;
		case ID_COLORS_SCOREBOARD:
			scoreBoardColor = OnOptionsColor(hWnd, scoreBoardColor);
			break;
		case ID_COLORS_WINNERLINE:
			winnerLineColor = OnOptionsColor(hWnd, winnerLineColor);
			break;
		case ID_COLORS_RANDOMCOLORS:
			OnRandomColor(hWnd);
			break;
		case ID_EDIT_UNDO:
			OnUndo(hWnd);
			break;
		case ID_EDIT_REDO:
			OnRedo(hWnd);
			break;
		case ID_EXTRAS_MUSICON:
			OnMusicOnOff(hWnd);
			break;
		case ID_REPEAT_TURN_CHEAT:
			OnRepeatCheat(hWnd);
			break;
		case ID_INSTANT_O_WIN:
			OnOWinCheat(hWnd);
			break;
		case ID_INSTANT_X_WIN:
			OnXWinCheat(hWnd);
			break;
		case ID_SWAP_MARK_CHEAT:
			OnSwapMarkCheat(hWnd);
			break;
		case ID_FILE_SAVE:
			OnSave(hWnd);
			break;
		case ID_FILE_LOAD:
			OnLoad(hWnd);
			break;
		case ID_OPTIONS_FONTSELECTION:
			OnFontSelect(hWnd);
			break;
		case ID_AILEVEL_RANDOM:
		{
								  if (AION){
									  if (!myGame.AILevel){
										  myGame.AILevel = true;
										  MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
										  mii.fMask = MIIM_STATE;
										  GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
										  mii.fState = !MFS_CHECKED;
										  SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
										  mii.fState = MFS_CHECKED;
										  SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);
									  }
									  else{
										  myGame.AILevel = false;

										  MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
										  mii.fMask = MIIM_STATE;
										  GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
										  mii.fState = MFS_CHECKED;
										  SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
										  mii.fState = !MFS_CHECKED;
										  SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);
									  }
								  }
								  break;
		}
		case ID_AILEVEL_STRATEGIC:
		{
									 if (AION){
										 if (!myGame.AILevel){
											 myGame.AILevel = true;
											 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
											 mii.fMask = MIIM_STATE;
											 GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);
											 mii.fState = MFS_CHECKED;
											 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);
											 mii.fState = !MFS_CHECKED;
											 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
										 }
										 else{
											 myGame.AILevel = false;

											 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
											 mii.fMask = MIIM_STATE;
											 GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
											 mii.fState = MFS_CHECKED;
											 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
											 mii.fState = !MFS_CHECKED;
											 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);
										 }
									 }
									 break;
		}
		case ID_AILEVEL_ONOFF:
		{
								 if (AION){
									 AION = false;
									 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									 mii.fMask = MIIM_STATE;
									 GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
									 mii.fState = !MFS_CHECKED;
									 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
									 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
									 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);

								 }
								 else{
									 AION = true;
									 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									 mii.fMask = MIIM_STATE;
									 GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
									 mii.fState = MFS_CHECKED;
									 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
									 SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
								 }

								 break;
		}
		case ID_GRID_THIN:
		{
							 gridLinesWidth = OnWidthThin(hWnd, gridLinesWidth);
							 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
							 mii.fMask = MIIM_STATE;
							 GetMenuItemInfo(GetMenu(hWnd), ID_GRID_THIN, FALSE, &mii);
							 mii.fState = MFS_CHECKED;
							 SetMenuItemInfo(GetMenu(hWnd), ID_GRID_THIN, FALSE, &mii);
							 mii.fState = !MFS_CHECKED;
							 SetMenuItemInfo(GetMenu(hWnd), ID_GRID_MEDIUM, FALSE, &mii);
							 SetMenuItemInfo(GetMenu(hWnd), ID_GRID_LARGE, FALSE, &mii);
							 break;
		}
		case ID_GRID_MEDIUM:{
								gridLinesWidth = OnWidthMedium(hWnd, gridLinesWidth);
								MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								mii.fMask = MIIM_STATE;
								GetMenuItemInfo(GetMenu(hWnd), ID_GRID_MEDIUM, FALSE, &mii);
								mii.fState = MFS_CHECKED;
								SetMenuItemInfo(GetMenu(hWnd), ID_GRID_MEDIUM, FALSE, &mii);
								mii.fState = !MFS_CHECKED;
								SetMenuItemInfo(GetMenu(hWnd), ID_GRID_THIN, FALSE, &mii);
								SetMenuItemInfo(GetMenu(hWnd), ID_GRID_LARGE, FALSE, &mii);
								break;
		}
		case ID_GRID_LARGE:{
							   gridLinesWidth = OnWidthLarge(hWnd, gridLinesWidth);
							   MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
							   mii.fMask = MIIM_STATE;
							   GetMenuItemInfo(GetMenu(hWnd), ID_GRID_LARGE, FALSE, &mii);
							   mii.fState = MFS_CHECKED;
							   SetMenuItemInfo(GetMenu(hWnd), ID_GRID_LARGE, FALSE, &mii);
							   mii.fState = !MFS_CHECKED;
							   SetMenuItemInfo(GetMenu(hWnd), ID_GRID_THIN, FALSE, &mii);
							   SetMenuItemInfo(GetMenu(hWnd), ID_GRID_MEDIUM, FALSE, &mii);
							   break;
		}
		case ID_SCOREBOARD_THIN:
		{
								   scoreBoardLinesWidth = OnWidthThin(hWnd, scoreBoardLinesWidth);
								   MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								   mii.fMask = MIIM_STATE;
								   GetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_THIN, FALSE, &mii);
								   mii.fState = MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_THIN, FALSE, &mii);
								   mii.fState = !MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_MEDIUM, FALSE, &mii);
								   SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_LARGE, FALSE, &mii);
								   break;
		}
		case ID_SCOREBOARD_MEDIUM:
		{
									 scoreBoardLinesWidth = OnWidthMedium(hWnd, scoreBoardLinesWidth);
									 MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									 mii.fMask = MIIM_STATE;
									 GetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_MEDIUM, FALSE, &mii);
									 mii.fState = MFS_CHECKED;
									 SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_MEDIUM, FALSE, &mii);
									 mii.fState = !MFS_CHECKED;
									 SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_THIN, FALSE, &mii);
									 SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_LARGE, FALSE, &mii);
									 break;
		}
		case ID_SCOREBOARD_LARGE:
		{
									scoreBoardLinesWidth = OnWidthLarge(hWnd, scoreBoardLinesWidth);
									MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									mii.fMask = MIIM_STATE;
									GetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_LARGE, FALSE, &mii);
									mii.fState = MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_LARGE, FALSE, &mii);
									mii.fState = !MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_THIN, FALSE, &mii);
									SetMenuItemInfo(GetMenu(hWnd), ID_SCOREBOARD_MEDIUM, FALSE, &mii);
									break;
		}
		case ID_PLAYERONE_THIN:
		{
								  playerOneLinesWidth = OnWidthThin(hWnd, playerOneLinesWidth);
								  MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								  mii.fMask = MIIM_STATE;
								  GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_THIN, FALSE, &mii);
								  mii.fState = MFS_CHECKED;
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_THIN, FALSE, &mii);
								  mii.fState = !MFS_CHECKED;
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_MEDIUM, FALSE, &mii);
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_LARGE, FALSE, &mii);
								  break;
		}
		case ID_PLAYERONE_MEDIUM:
		{
									playerOneLinesWidth = OnWidthMedium(hWnd, playerOneLinesWidth);
									MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									mii.fMask = MIIM_STATE;
									GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_MEDIUM, FALSE, &mii);
									mii.fState = MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_MEDIUM, FALSE, &mii);
									mii.fState = !MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_THIN, FALSE, &mii);
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_LARGE, FALSE, &mii);
									break;
		}
		case ID_PLAYERONE_LARGE:
		{
								   playerOneLinesWidth = OnWidthLarge(hWnd, playerOneLinesWidth);
								   MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								   mii.fMask = MIIM_STATE;
								   GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_LARGE, FALSE, &mii);
								   mii.fState = MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_LARGE, FALSE, &mii);
								   mii.fState = !MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_THIN, FALSE, &mii);
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERONE_MEDIUM, FALSE, &mii);
								   break;
		}
		case ID_PLAYERTWO_THIN:
		{
								  playerTwoLinesWidth = OnWidthThin(hWnd, playerTwoLinesWidth);
								  MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								  mii.fMask = MIIM_STATE;
								  GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_THIN, FALSE, &mii);
								  mii.fState = MFS_CHECKED;
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_THIN, FALSE, &mii);
								  mii.fState = !MFS_CHECKED;
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_MEDIUM, FALSE, &mii);
								  SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_LARGE, FALSE, &mii);
								  break;
		}
		case ID_PLAYERTWO_MEDIUM:
		{
									playerTwoLinesWidth = OnWidthMedium(hWnd, playerTwoLinesWidth);
									MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
									mii.fMask = MIIM_STATE;
									GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_MEDIUM, FALSE, &mii);
									mii.fState = MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_MEDIUM, FALSE, &mii);
									mii.fState = !MFS_CHECKED;
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_THIN, FALSE, &mii);
									SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_LARGE, FALSE, &mii);
									break;
		}
		case ID_PLAYERTWO_LARGE:
		{
								   playerTwoLinesWidth = OnWidthLarge(hWnd, playerTwoLinesWidth);
								   MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
								   mii.fMask = MIIM_STATE;
								   GetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_LARGE, FALSE, &mii);
								   mii.fState = MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_LARGE, FALSE, &mii);
								   mii.fState = !MFS_CHECKED;
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_THIN, FALSE, &mii);
								   SetMenuItemInfo(GetMenu(hWnd), ID_PLAYERTWO_MEDIUM, FALSE, &mii);
								   break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_HELP_INSTRUCTIONS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_INSTRUCTION), hWnd, Instruction);
			break;
		case ID_HELP_CONTACTINFO:
			ContacInfo(hWnd);
			break;
		case IDM_EXIT:
			OnClose(hWnd);
			break;
		case ID_LANGUAGES_SPANISH:
			OnSpanishChange(hWnd);
			break;
		case ID_LANGUAGES_ENGLISH:
			OnEnglishChange(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CLOSE:
		OnClose(hWnd);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(hWnd, lParam);
		break;
	case WM_ERASEBKGND:
		// Do nothing!
		break;
	case WM_LBUTTONUP:
		if (!myMenuTitle)
			AITurn(hWnd);
		break;
	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
	case WM_DESTROY:
		DestroyGraphics();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void OnPaint(HWND hWnd)
{
	pRT->BeginDraw();
	pRT->Clear(bkgndColor);

	if (myMenuTitle){
		D2D1_RECT_F rect = D2D1::RectF(300, 0, 500, 50);

		pBrush->SetColor(scoreBoardColor);
		pRT->DrawRectangle(rect, pBrush, scoreBoardLinesWidth);

		std::wostringstream title;
		title << szTitle;
		pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		pRT->DrawText(title.str().c_str(), title.str().length(), pTF, rect, pBrush);

		std::wostringstream newGame;
		newGame << szNewGame;
		pRT->DrawRectangle(NewGameRect, pBrush, scoreBoardLinesWidth);

		pRT->DrawText(newGame.str().c_str(), newGame.str().length(), pTF, NewGameRect, pBrush);

		std::wostringstream loadGame;
		loadGame << szLoadGame;
		pRT->DrawRectangle(LoadGameRect, pBrush, scoreBoardLinesWidth);

		pRT->DrawText(loadGame.str().c_str(), loadGame.str().length(), pTF, LoadGameRect, pBrush);

		std::wostringstream AIonoff;
		AIonoff << szAIOn;

		
		if (AION)
			pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
		else
			pBrush->SetColor(scoreBoardColor);
			
		pRT->DrawRectangle(AIOnOffRect, pBrush, scoreBoardLinesWidth);

		pBrush->SetColor(scoreBoardColor);
		pRT->DrawText(AIonoff.str().c_str(), AIonoff.str().length(), pTF, AIOnOffRect, pBrush);

		std::wostringstream instrucText;
		instrucText << szInstruction;
		pRT->DrawRectangle(InstructionRect, pBrush, scoreBoardLinesWidth);

		pRT->DrawText(instrucText.str().c_str(), instrucText.str().length(), pTF, InstructionRect, pBrush);

		std::wostringstream creditsText;
		creditsText << szCredits;
		pRT->DrawRectangle(CreditsRect, pBrush, scoreBoardLinesWidth);

		pRT->DrawText(creditsText.str().c_str(), creditsText.str().length(), pTF, CreditsRect, pBrush);

		std::wostringstream exitText;
		exitText << szExit;
		pRT->DrawRectangle(ExitRect, pBrush, scoreBoardLinesWidth);

		pRT->DrawText(exitText.str().c_str(), exitText.str().length(), pTF, ExitRect, pBrush);

		HRESULT hr = pRT->EndDraw();


		if (hr == D2DERR_RECREATE_TARGET)
		{
			DestroyGraphics();
			CreateGraphics(hWnd);
		}

		ValidateRect(hWnd, NULL);
	}
	else{


		// lines
		pBrush->SetColor(gridLinesColor);
		pRT->DrawLine(D2D1::Point2F(0, 150), D2D1::Point2F(450, 150), pBrush, gridLinesWidth);
		pRT->DrawLine(D2D1::Point2F(0, 300), D2D1::Point2F(450, 300), pBrush, gridLinesWidth);
		pRT->DrawLine(D2D1::Point2F(150, 0), D2D1::Point2F(150, 450), pBrush, gridLinesWidth);
		pRT->DrawLine(D2D1::Point2F(300, 0), D2D1::Point2F(300, 450), pBrush, gridLinesWidth);

		//draw stuff

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (myGame.board[i][j] == 1){
					pBrush->SetColor(playerOneColor);
					pRT->DrawLine(D2D1::Point2F(i * 150.0F + 35.0F, j * 150.0F + 35.0F), D2D1::Point2F((i * 150.0F) + 115.0F, (j * 150.0F) + 115.0F), pBrush, playerOneLinesWidth);
					pRT->DrawLine(D2D1::Point2F(i * 150.0F + 35.0F, (j * 150.0F) + 115.0F), D2D1::Point2F((i * 150.0F) + 115.0F, j * 150.0F + 35.0F), pBrush, playerOneLinesWidth);
				}
				if (myGame.board[i][j] == 2){
					ID2D1GradientStopCollection *pGradientStops = NULL;
					ID2D1RadialGradientBrush *m_pRadialGradientBrush;

					D2D1_GRADIENT_STOP gradientStops[2];
					gradientStops[0].color = gradientColor1;
					gradientStops[0].position = 0.0f;
					gradientStops[1].color = gradientColor2;
					gradientStops[1].position = 1.0f;
					// Create the ID2D1GradientStopCollection from a previously
					// declared array of D2D1_GRADIENT_STOP structs.
					HRESULT hr = pRT->CreateGradientStopCollection(
						gradientStops,
						2,
						D2D1_GAMMA_2_2,
						D2D1_EXTEND_MODE_CLAMP,
						&pGradientStops
						);
					hr = pRT->CreateRadialGradientBrush(
						D2D1::RadialGradientBrushProperties(
						D2D1::Point2F(i * 150.0F + 50, j * 150.0F + 50),
						D2D1::Point2F(i * 150.0F, j * 150.0F ),
						75,
						75),
						pGradientStops,
						&m_pRadialGradientBrush
						);

					pBrush->SetColor(playerTwoColor);
					D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F((i * 150.0F) + 75.0F, (j * 150.0F) + 75.0F), 50.0F, 50.0F);
					pRT->FillEllipse(ellipse, m_pRadialGradientBrush);
					pRT->DrawEllipse(ellipse, pBrush, playerTwoLinesWidth);
					
				}
			}
		}


		pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
		pBrush->SetOpacity(0.5F);
		pRT->DrawRectangle(hollow, pBrush, gridLinesWidth);

		pBrush->SetOpacity(1.0F);

		pBrush->SetColor(winnerLineColor);
		int countH, countV;
		countH = countV = 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				countV *= myGame.board[i][j];
				countH *= myGame.board[j][i];
			}
			if (countH == 1 || countH == 8)
				pRT->DrawLine(D2D1::Point2F(10.0F, i * 150.0F + 75.0F), D2D1::Point2F(440.0F, i * 150.0F + 75.0F), pBrush, 8.0F);
			if (countV == 1 || countV == 8)
				pRT->DrawLine(D2D1::Point2F(i * 150.0F + 75.0F, 10.0F), D2D1::Point2F(i * 150.0F + 75.0F, 440.0F), pBrush, 8.0F);

			countH = 1;
			countV = 1;
		}
		if ((myGame.board[0][0] == 1 && myGame.board[1][1] == 1 && myGame.board[2][2] == 1) || (myGame.board[0][0] == 2 && myGame.board[1][1] == 2 && myGame.board[2][2] == 2))
			pRT->DrawLine(D2D1::Point2F(10.0F, 10.0F), D2D1::Point2F(440.0F, 440.0F), pBrush, 8.0F);

		if ((myGame.board[0][2] == 1 && myGame.board[1][1] == 1 && myGame.board[2][0] == 1) || (myGame.board[0][2] == 2 && myGame.board[1][1] == 2 && myGame.board[2][0] == 2))
			pRT->DrawLine(D2D1::Point2F(440.0F, 10.0F), D2D1::Point2F(10.0F, 440.0F), pBrush, 8.0F);

		D2D1_RECT_F rect = D2D1::RectF(600, 150, 900, 300);

		pBrush->SetColor(scoreBoardColor);
		pRT->DrawRectangle(rect, pBrush, scoreBoardLinesWidth);

		// scoreboard
		std::wostringstream wos;
		wos << szXwins << myGame.xwins << ", " << szOwins << myGame.owins << ", " << szTies << myGame.ties;

		pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		pBrush->SetColor(scoreBoardColor);
		pRT->DrawText(wos.str().c_str(), wos.str().length(), pTF, rect, pBrush);

		HRESULT hr = pRT->EndDraw();


		if (hr == D2DERR_RECREATE_TARGET)
		{
			DestroyGraphics();
			CreateGraphics(hWnd);
		}

		ValidateRect(hWnd, NULL);
	}

}

void OnHollowEnter(HWND hWnd){

	int indexX = (int)hollow.left / 150;
	int indexY = (int)hollow.top / 150;

	if (myGame.board[indexX][indexY] == 0){

		if (myGame.isXturn){
			myGame.board[indexX][indexY] = 1;
			myGame.undoBoard[indexX][indexY] = myGame.turn;
			myGame.isXturn = false;
		}
		else{
			myGame.board[indexX][indexY] = 2;
			myGame.undoBoard[indexX][indexY] = myGame.turn;
			myGame.isXturn = true;
		}
		myGame.turn++;
		CheckWinner(hWnd);
	}
}

void OnLButtonDown(HWND hWnd, LPARAM lParam)
{
	if (myMenuTitle){

		int mouseInputX = GET_X_LPARAM(lParam);
		int mouseInputY = GET_Y_LPARAM(lParam);

		RECT rect;
		GetClientRect(hWnd, &rect);

		mouseInputX = (int)(mouseInputX * (pRT->GetSize().width / rect.right));
		mouseInputY = (int)(mouseInputY * (pRT->GetSize().height / rect.bottom));

		if (mouseInputX >= NewGameRect.left && mouseInputX <= NewGameRect.right && mouseInputY >= NewGameRect.top && mouseInputY <= NewGameRect.bottom){
			MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
			mii.fMask = MIIM_STATE;
			GetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
			mii.fState = MFS_ENABLED;
			SetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
			myMenuTitle = false;
		}
		if (mouseInputX >= LoadGameRect.left && mouseInputX <= LoadGameRect.right && mouseInputY >= LoadGameRect.top && mouseInputY <= LoadGameRect.bottom){
			OnLoad(hWnd);

		}
		if (mouseInputX >= AIOnOffRect.left && mouseInputX <= AIOnOffRect.right && mouseInputY >= AIOnOffRect.top && mouseInputY <= AIOnOffRect.bottom){
			if (AION){
				AION = false;
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
				mii.fState = !MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
				SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
				SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_STRATEGIC, FALSE, &mii);

			}
			else{
				AION = true;
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
				mii.fState = MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_ONOFF, FALSE, &mii);
				SetMenuItemInfo(GetMenu(hWnd), ID_AILEVEL_RANDOM, FALSE, &mii);
			}
		}
		if (mouseInputX >= InstructionRect.left && mouseInputX <= InstructionRect.right && mouseInputY >= InstructionRect.top && mouseInputY <= InstructionRect.bottom)
			DialogBox(hInst, MAKEINTRESOURCE(IDD_INSTRUCTION), hWnd, Instruction);
		if (mouseInputX >= CreditsRect.left && mouseInputX <= CreditsRect.right && mouseInputY >= CreditsRect.top && mouseInputY <= CreditsRect.bottom)
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CREDITS), hWnd, Credits);
		if (mouseInputX >= ExitRect.left && mouseInputX <= ExitRect.right && mouseInputY >= ExitRect.top && mouseInputY <= ExitRect.bottom)
			OnClose(hWnd);

		/*if (myGame.music)
			Media::SystemSounds::Asterisk->Play();*/

		InvalidateRect(hWnd, NULL, TRUE);
	}
	else{
		int indexX = GET_X_LPARAM(lParam) / 150;
		int indexY = GET_Y_LPARAM(lParam) / 150;

		RECT rect;
		GetClientRect(hWnd, &rect);

		indexX = (int)(indexX * (pRT->GetSize().width / rect.right));
		indexY = (int)(indexY * (pRT->GetSize().height / rect.bottom));

		if (myGame.board[indexX][indexY] == 0 && GET_X_LPARAM(lParam) <= 450 && GET_Y_LPARAM(lParam) <= 450){
			if (myGame.isXturn){
				myGame.board[indexX][indexY] = 1;
				myGame.undoBoard[indexX][indexY] = myGame.turn;

				myGame.isXturn = false;
			}
			else{
				myGame.board[indexX][indexY] = 2;
				myGame.undoBoard[indexX][indexY] = myGame.turn;
				myGame.isXturn = true;
			}
			myGame.turn++;
			ClearRedo();
			InvalidateRect(hWnd, NULL, TRUE);
			CheckWinner(hWnd);

			
		}
	}
}

//AI TURN
void AITurn(HWND hWnd){
	if (AION){
		if (!myGame.isXturn){
			if (!myGame.AILevel){
				// RANDOM AI
				int k, l;
				do{
					k = rand() % 3;
					l = rand() % 3;

				} while (myGame.board[k][l] != 0);
				myGame.board[k][l] = 2;
				myGame.undoBoard[k][l] = myGame.turn;

			}
			else{
				if (myGame.board[1][1] == 0){ // this is the best moves to win
					myGame.board[1][1] = 2;
					myGame.undoBoard[1][1] = myGame.turn;

				}
				else{
					//win

					if (myGame.board[0][0] == 0 && ((myGame.board[0][2] == 2 && myGame.board[0][2] == myGame.board[0][1]) || (myGame.board[2][0] == 2 && myGame.board[2][0] == myGame.board[1][0]) || (myGame.board[2][2] == 2 && myGame.board[2][2] == myGame.board[1][1]))){
						myGame.board[0][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[0][1] == 0 && ((myGame.board[0][2] == 2 && myGame.board[0][2] == myGame.board[0][0]) || (myGame.board[2][1] == 2 && myGame.board[2][1] == myGame.board[1][1]))){
						myGame.board[0][1] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[0][2] == 0 && ((myGame.board[0][0] == 2 && myGame.board[0][0] == myGame.board[0][1]) || (myGame.board[2][2] == 2 && myGame.board[2][2] == myGame.board[1][2]) || (myGame.board[0][2] == 2 && myGame.board[0][2] == myGame.board[1][1]))){
						myGame.board[0][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[1][0] == 0 && ((myGame.board[1][2] == 2 && myGame.board[1][2] == myGame.board[1][1]) || (myGame.board[2][0] == 2 && myGame.board[2][0] == myGame.board[0][0]))){
						myGame.board[1][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					// I don't need to check the [1][1] position because it would be the first move.
					else if (myGame.board[1][2] == 0 && ((myGame.board[2][2] == 2 && myGame.board[2][2] == myGame.board[0][2]) || (myGame.board[1][1] == 2 && myGame.board[1][1] == myGame.board[1][0]))){
						myGame.board[1][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][0] == 0 && ((myGame.board[1][0] == 2 && myGame.board[1][0] == myGame.board[0][0]) || (myGame.board[2][2] == 2 && myGame.board[2][2] == myGame.board[2][1]) || (myGame.board[0][2] == 2 && myGame.board[0][2] == myGame.board[1][1]))){
						myGame.board[2][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][1] == 0 && ((myGame.board[0][1] == 2 && myGame.board[0][1] == myGame.board[1][1]) || (myGame.board[2][2] == 2 && myGame.board[2][2] == myGame.board[2][0]))){
						myGame.board[2][1] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][2] == 0 && ((myGame.board[2][1] == 2 && myGame.board[2][1] == myGame.board[2][0]) || (myGame.board[1][2] == 2 && myGame.board[1][2] == myGame.board[0][2]) || (myGame.board[0][0] == 2 && myGame.board[0][0] == myGame.board[1][1]))){
						myGame.board[2][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					//block
					else if (myGame.board[0][0] == 0 && ((myGame.board[0][2] != 0 && myGame.board[0][2] == myGame.board[0][1]) || (myGame.board[2][0] != 0 && myGame.board[2][0] == myGame.board[1][0]) || (myGame.board[2][2] != 0 && myGame.board[2][2] == myGame.board[1][1]))){
						myGame.board[0][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[0][1] == 0 && ((myGame.board[0][2] != 0 && myGame.board[0][2] == myGame.board[0][0]) || (myGame.board[2][1] != 0 && myGame.board[2][1] == myGame.board[1][1]))){
						myGame.board[0][1] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[0][2] == 0 && ((myGame.board[0][0] != 0 && myGame.board[0][0] == myGame.board[0][1]) || (myGame.board[2][2] != 0 && myGame.board[2][2] == myGame.board[1][2]) || (myGame.board[0][2] != 0 && myGame.board[0][2] == myGame.board[1][1]))){
						myGame.board[0][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[1][0] == 0 && ((myGame.board[1][2] != 0 && myGame.board[1][2] == myGame.board[1][1]) || (myGame.board[2][0] != 0 && myGame.board[2][0] == myGame.board[0][0]))){
						myGame.board[1][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					// I don't need to check the [1][1] position because it would be the first move.
					else if (myGame.board[1][2] == 0 && ((myGame.board[2][2] != 0 && myGame.board[2][2] == myGame.board[0][2]) || (myGame.board[1][1] != 0 && myGame.board[1][1] == myGame.board[1][0]))){
						myGame.board[1][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][0] == 0 && ((myGame.board[1][0] != 0 && myGame.board[1][0] == myGame.board[0][0]) || (myGame.board[2][2] != 0 && myGame.board[2][2] == myGame.board[2][1]) || (myGame.board[0][2] != 0 && myGame.board[0][2] == myGame.board[1][1]))){
						myGame.board[2][0] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][1] == 0 && ((myGame.board[0][1] != 0 && myGame.board[0][1] == myGame.board[1][1]) || (myGame.board[2][2] != 0 && myGame.board[2][2] == myGame.board[2][0]))){
						myGame.board[2][1] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else if (myGame.board[2][2] == 0 && ((myGame.board[2][1] != 0 && myGame.board[2][1] == myGame.board[2][0]) || (myGame.board[1][2] != 0 && myGame.board[1][2] == myGame.board[0][2]) || (myGame.board[0][0] != 0 && myGame.board[0][0] == myGame.board[1][1]))){
						myGame.board[2][2] = 2;
						myGame.undoBoard[0][0] = myGame.turn;
					}
					else{
						int k, l;
						do{
							k = rand() % 3;
							l = rand() % 3;

						} while (myGame.board[k][l] != 0);
						myGame.board[k][l] = 2;
						myGame.undoBoard[k][l] = myGame.turn;

					}
				}
			}
		}

		myGame.isXturn = true;
		myGame.turn++;
		ClearRedo();

		InvalidateRect(hWnd, NULL, TRUE);
		CheckWinner(hWnd);
	}
}

// Menu Message Handlers
void OnFileNew(HWND hWnd)
{
	OnUntitledExit(hWnd);

	ptMouse.x = 0;
	ptMouse.y = 0;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			myGame.board[i][j] = 0;
		}
	}
	hollow.top = 0;
	hollow.right = 150;
	hollow.left = 0;
	hollow.bottom = 150;

	myGame.turn = 1;
	ClearRedo();
	myGame.undoBoard[0][0] = { 0 };

	InvalidateRect(hWnd, NULL, TRUE);
	rowWins = 0;
	SetWindowText(hWnd, _T("Untitled"));
}

void OnClose(HWND hWnd)
{
	OnUntitledExit(hWnd);
	if (IDYES == MessageBox(hWnd, L"Do you want to quit?", L"Close...", MB_YESNO | MB_ICONQUESTION))
	{
		if (myGame.music){

			PlaySound(NULL, NULL, NULL);
			PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
		}

		DestroyWindow(hWnd);
	}
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

INT_PTR CALLBACK Credits(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

INT_PTR CALLBACK Instruction(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

void ContacInfo(HWND hWnd)
{
	if (IDYES == MessageBox(hWnd, L"Author: Jagoba \"Jake\" Marcos\nEmail: jag_141@hotmail.com", L"Contact Info...", MB_OK)){

	}
}

void OnSize(HWND hWnd, LPARAM lParam)
{
	hWnd;
	// Resize the Render Target based upon the new client.
	D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));

	// I know how to resize the client area but I can't hangle the input right
	pRT->Resize(size);
	InvalidateRect(hWnd, NULL, TRUE);
}

// Direct2D CreateGraphics and DestroyGraphics
HRESULT CreateGraphics(HWND hWnd)
{
	// Initialize the Direct2D Factory.
	HRESULT hr;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the Direct2D Factory."),
			_T("Direct2D Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	// Get the dimensions of the client.
	RECT rc;
	GetClientRect(hWnd, &rc);

	// Initialize a Direct2D Size Structure.
	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

	// Create the Direct2D Render Target.
	hr = pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size), &pRT);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the Direct2D Render Target."),
			_T("Direct2D Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	pRT->SetDpi(96.0f, 96.0f);

	// Create the Direct2D Solid Color Brush.
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(0x0), &pBrush);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the Direct2D Solid Color Brush."),
			_T("Direct2D Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	// Initialize the DirectWrite Factory.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		(IUnknown**)&pDWFactory);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the DirectWrite Factory."),
			_T("DirectWrite Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	// Create the DirectWrite Text Format.

	hr = pDWFactory->CreateTextFormat(_T("Veranda"), NULL,
		DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		24, _T(""), &pTF);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the DirectWrite Text Format."),
			_T("DirectWrite Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	pTF->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);


	return S_OK;
}

void DestroyGraphics()
{
	// Release the DirectWrite Text Format.
	if (pTF)
	{
		pTF->Release();
		pTF = nullptr;
	}

	// Release the DirectWrite Factory.
	if (pDWFactory)
	{
		pDWFactory->Release();
		pDWFactory = nullptr;
	}

	// Release the Direct2D Solid Color Brush.
	if (pBrush)
	{
		pBrush->Release();
		pBrush = NULL;
	}

	// Release the Hwnd Render Target
	if (pRT)
	{
		pRT->Release();
		pRT = nullptr;
	}


	// Release the Direct2D Factroy
	if (pD2DFactory)
	{
		pD2DFactory->Release();
		pD2DFactory = nullptr;
	}
}

D2D1_COLOR_F OnOptionsColor(HWND hWnd, D2D1_COLOR_F store)
{
	// Array of COLORREFs used to store the custom colors.
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

	bkgndColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	gridLinesColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	playerOneColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	playerTwoColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	scoreBoardColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	winnerLineColor = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	gradientColor1 = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));
	gradientColor2 = D2D1::ColorF((rand() % 255 + 1) << 16 | (rand() % 255 + 1) << 8 | (rand() % 255 + 1));

	InvalidateRect(hWnd, NULL, TRUE);
}

FLOAT OnWidthThin(HWND hWnd, FLOAT change){

	InvalidateRect(hWnd, NULL, TRUE);
	change = 2.0F;
	return change;
}

FLOAT OnWidthMedium(HWND hWnd, FLOAT change){

	InvalidateRect(hWnd, NULL, TRUE);
	change = 6.0F;
	return change;
}

FLOAT OnWidthLarge(HWND hWnd, FLOAT change){

	InvalidateRect(hWnd, NULL, TRUE);
	change = 11.0F;
	return change;
}

void CheckWinner(HWND hWnd){

	win = myGame.WhoWon();
	if (win == 1){

		if (myGame.music){

			PlaySound(NULL, NULL, NULL);
			PlaySound(TEXT("Music//Success.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}

		if (IDYES == MessageBox(hWnd, L"PLAYER ONE WON!!\n\nDo you want to play again?", L"Repeat...", MB_YESNO | MB_ICONQUESTION))
		{

			if (AION && myGame.AILevel){
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_STRATEGIC, FALSE, &mii);
				mii.fState = MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_STRATEGIC, FALSE, &mii);
			}
			MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
			mii.fMask = MIIM_STATE;
			GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_FIRSTWIN, FALSE, &mii);
			mii.fState = MFS_CHECKED;
			SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_FIRSTWIN, FALSE, &mii);

			rowWins++;
			if (rowWins == 3){
				MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
				mii.fMask = MIIM_STATE;
				GetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_ONFIRE, FALSE, &mii);
				mii.fState = MFS_CHECKED;
				SetMenuItemInfo(GetMenu(hWnd), ID_ACHIEVEMENTS_ONFIRE, FALSE, &mii);
			}
			myGame.xwins++;
			OnFileNew(hWnd);
			myGame.turn = 1;
			if (!myGame.isXturn)
				AITurn(hWnd);
		}
		else{
			if (myGame.music){

				PlaySound(NULL, NULL, NULL);
				PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
			}
			DestroyWindow(hWnd);
		}
	}

	if (win == 2){

		if (myGame.music){
			if (AION){

				PlaySound(NULL, NULL, NULL);
				PlaySound(TEXT("Music//LOSE.wav"), NULL, SND_FILENAME | SND_ASYNC);

			}
			else{
				PlaySound(NULL, NULL, NULL);
				PlaySound(TEXT("Music//Success.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

		}

		if (IDYES == MessageBox(hWnd, L"PLAYER TWO WON!!\n\nDo you want to play again?", L"Repeat...", MB_YESNO | MB_ICONQUESTION))
		{
			myGame.owins++;
			OnFileNew(hWnd);
			myGame.turn = 1;
			if (!myGame.isXturn)
				AITurn(hWnd);

			rowWins = 0;
		}
		else{
			if (myGame.music){

				PlaySound(NULL, NULL, NULL);
				PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
			}
			DestroyWindow(hWnd);
		}
	}

	else if (win == 0){

		if (IDYES == MessageBox(hWnd, L"IT WAS A TIE!!\n\nDo you want to play again?", L"Repeat...", MB_YESNO | MB_ICONQUESTION))
		{
			myGame.ties++;
			OnFileNew(hWnd);
			myGame.turn = 1;
			if (!myGame.isXturn)
				AITurn(hWnd);
		}
		else{
			if (myGame.music){

				PlaySound(NULL, NULL, NULL);
				PlaySound(TEXT("Music//game_over.wav"), NULL, SND_FILENAME | SND_SYNC);
			}
			DestroyWindow(hWnd);
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void OnRedo(HWND hWnd){
	if (myGame.redo > 1){
		myGame.redo--;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (myGame.redoBoard[i][j] == myGame.redo){
					myGame.redoBoard[i][j] = 0;
					if (myGame.isXturn){
						myGame.board[i][j] = 1;
						myGame.isXturn = false;
					}
					else{
						myGame.isXturn = true;
						myGame.board[i][j] = 2;
					}
					myGame.undoBoard[i][j] = myGame.turn;
					myGame.turn++;
					break;
				}
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		if (!myGame.isXturn)
			AITurn(hWnd);
	}
}

void OnUndo(HWND hWnd){
	if (myGame.turn > 1){
		myGame.turn--;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (myGame.undoBoard[i][j] == myGame.turn){
					myGame.undoBoard[i][j] = 0;
					myGame.board[i][j] = 0;

					if (myGame.isXturn)
						myGame.isXturn = false;
					else
						myGame.isXturn = true;
					myGame.redoBoard[i][j] = myGame.redo;
					myGame.redo++;
				}
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		if (!myGame.isXturn)
			AITurn(hWnd);
	}
}

void ClearRedo(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			myGame.redoBoard[i][j] = 0;
		}
	}
	myGame.redo = 1;

}

void OnKeyDown(HWND hWnd){
	if (GetKeyState(VK_UP) & 0x8000) {
		if (hollow.top == 0){
			hollow.top = 300;
			hollow.bottom = 450;
		}
		else{
			hollow.bottom -= 150;
			hollow.top -= 150;
		}

		InvalidateRect(hWnd, NULL, TRUE);

	}
	if (GetKeyState(VK_DOWN) & 0x8000) {
		if (hollow.bottom == 450){
			hollow.top = 0;
			hollow.bottom = 150;
		}
		else{
			hollow.bottom += 150;
			hollow.top += 150;
		}

		InvalidateRect(hWnd, NULL, TRUE);

	}
	if (GetKeyState(VK_LEFT) & 0x8000) {
		if (hollow.left == 0){
			hollow.left = 300;
			hollow.right = 450;
		}
		else{
			hollow.left -= 150;
			hollow.right -= 150;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000) {
		if (hollow.right == 450){
			hollow.left = 0;
			hollow.right = 150;
		}
		else{
			hollow.left += 150;
			hollow.right += 150;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
	if (GetKeyState(VK_RETURN) & 0x8000) {

		OnHollowEnter(hWnd);
		if (AION)
			AITurn(hWnd);
	}
	if (GetKeyState(VK_NUMPAD1) & 0x8000) {
		if (myGame.board[0][2] == 0){
			if (myGame.isXturn){
				myGame.board[0][2] = 1;
				myGame.undoBoard[0][2] = myGame.turn;
				ClearRedo();
				myGame.turn++;
				myGame.isXturn = false;
			}
			else{
				myGame.board[0][2] = 2;
				myGame.undoBoard[0][2] = myGame.turn;
				ClearRedo();
				myGame.turn++;
				myGame.isXturn = true;
			}
		}

		if (AION)
			AITurn(hWnd);
		CheckWinner(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	if (GetKeyState(VK_NUMPAD2) & 0x8000) {
		if (myGame.board[1][2] == 0){
			if (myGame.isXturn){
				myGame.board[1][2] = 1;
				myGame.undoBoard[1][2] = myGame.turn;
				ClearRedo();
				myGame.turn++;
				myGame.isXturn = false;
			}
			else{
				myGame.board[1][2] = 2;
				myGame.undoBoard[1][2] = myGame.turn;
				ClearRedo();
				myGame.turn++;
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD3) & 0x8000) {
		if (myGame.board[2][2] == 0){
			if (myGame.isXturn){
				myGame.board[2][2] = 1;
				myGame.undoBoard[2][2] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[2][2] = 2;
				myGame.undoBoard[2][2] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD4) & 0x8000) {
		if (myGame.board[0][1] == 0){
			if (myGame.isXturn){
				myGame.board[0][1] = 1;
				myGame.undoBoard[0][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[0][1] = 2;
				myGame.undoBoard[0][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD5) & 0x8000) {
		if (myGame.board[1][1] == 0){
			if (myGame.isXturn){
				myGame.board[1][1] = 1;
				myGame.undoBoard[1][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[1][1] = 2;
				myGame.undoBoard[1][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD6) & 0x8000) {
		if (myGame.board[2][1] == 0){
			if (myGame.isXturn){
				myGame.board[2][1] = 1;
				myGame.undoBoard[2][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[2][1] = 2;
				myGame.undoBoard[2][1] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD7) & 0x8000) {
		if (myGame.board[0][0] == 0){
			if (myGame.isXturn){
				myGame.board[0][0] = 1;
				myGame.undoBoard[0][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[0][0] = 2;
				myGame.undoBoard[0][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD8) & 0x8000) {
		if (myGame.board[1][0] == 0){
			if (myGame.isXturn){
				myGame.board[1][0] = 1;
				myGame.undoBoard[1][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[1][0] = 2;
				myGame.undoBoard[1][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if (GetKeyState(VK_NUMPAD9) & 0x8000) {
		if (myGame.board[2][0] == 0){
			if (myGame.isXturn){
				myGame.board[2][0] = 1;
				myGame.undoBoard[2][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = false;
			}
			else{
				myGame.board[2][0] = 2;
				myGame.undoBoard[2][0] = myGame.turn;
				myGame.turn++;
				ClearRedo();
				myGame.isXturn = true;
			}

			if (AION)
				AITurn(hWnd);
			CheckWinner(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}

}

void OnMouseWheel(HWND hWnd, WPARAM wParam){
	
	int distance = GET_WHEEL_DELTA_WPARAM(wParam);

	RECT rect = RECT();
	GetWindowRect(hWnd, &rect);

	D2D1_POINT_2F center;
	center.x = (FLOAT)(((rect.right - rect.left) / 2) + rect.left);
	center.y =  (FLOAT)(((rect.bottom - rect.top) / 2) + rect.top);

	if (distance > 0)
	{
		// Positive
		rect.right = rect.right + 10;
		rect.bottom = rect.bottom + 10;
	}
	else
	{
		rect.right = rect.right - 10;
		rect.bottom = rect.bottom - 10;
	}

	MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
}

void OnRepeatCheat(HWND hWnd){
	if (myGame.isXturn)
		myGame.isXturn = false;
	else
		myGame.isXturn = true;
	if (AION)
		AITurn(hWnd);

	MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
	mii.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_EXTRATURN, FALSE, &mii);
	mii.fState = MFS_ENABLED;
	SetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_EXTRATURN, FALSE, &mii);
}

void OnXWinCheat(HWND hWnd){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			myGame.board[i][j] = 1;
		}
	}
	MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
	mii.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_INSTANTWINPLAYER1, FALSE, &mii);
	mii.fState = MFS_ENABLED;
	SetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_INSTANTWINPLAYER1, FALSE, &mii);

	InvalidateRect(hWnd, NULL, TRUE);
	CheckWinner(hWnd);
}
void OnOWinCheat(HWND hWnd){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			myGame.board[i][j] = 2;
		}
	}
	MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
	mii.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_INSTANTWINPLAYER2, FALSE, &mii);
	mii.fState = MFS_ENABLED;
	SetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_INSTANTWINPLAYER2, FALSE, &mii);

	InvalidateRect(hWnd, NULL, TRUE);
	CheckWinner(hWnd);
}

void OnSwapMarkCheat(HWND hWnd){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (myGame.board[i][j] == 2)
				myGame.board[i][j] = 1;
			else if (myGame.board[i][j] == 1)
				myGame.board[i][j] = 2;
		}
	}
	MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
	mii.fMask = MIIM_STATE;
	GetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_SWAPMARKS, FALSE, &mii);
	mii.fState = MFS_ENABLED;
	SetMenuItemInfo(GetMenu(hWnd), ID_CHEATS_SWAPMARKS, FALSE, &mii);

	InvalidateRect(hWnd, NULL, TRUE);

}

void OnSave(HWND hWnd){

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
			fin << myGame.isXturn << " ";
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){

					if (myGame.board[i][j] == 0)
						fin << "B ";
					else if (myGame.board[i][j] == 1)
						fin << "X ";
					else if (myGame.board[i][j] == 2)
						fin << "O ";
				}
			}

			fin.close();
		}

		SetWindowText(hWnd, szFilePathName);
		
	}
}

void OnLoad(HWND hWnd){

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
			char charact;
			fout >> charact;
			if (charact == '1')
				myGame.isXturn = true;
			else
				myGame.isXturn = false;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					fout >> charact;
					if (charact == 'B')
						myGame.board[i][j] = 0;
					else if (charact == 'X')
						myGame.board[i][j] = 1;
					else if (charact == 'O')
						myGame.board[i][j] = 2;
				}
			}

			fout.close();
		}

		SetWindowText(hWnd, szFilePathName);

		myMenuTitle = false;

		MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
		mii.fMask = MIIM_STATE;
		GetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
		mii.fState = MFS_ENABLED;
		SetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
		myMenuTitle = false;
	}

}

void OnUntitledExit(HWND hWnd){
	wchar_t  szName[MAX_PATH];
	GetWindowText(hWnd, szName, MAX_PATH);
	wchar_t  compare[MAX_PATH] = _T("Untitled");
	if (wcscmp(szName, compare) == 0 && !myMenuTitle){
		if (IDYES == MessageBox(hWnd, L"Do you want to save changes to Untitled?", L"Last chance saving...", MB_YESNOCANCEL | MB_ICONQUESTION)){
			OnSave(hWnd);
		}
	}
}

void OnFontSelect(HWND hWnd){
	CHOOSEFONT cf = { sizeof(CHOOSEFONT) };
	LOGFONT lf;

	cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
	cf.hwndOwner = hWnd;
	cf.lpLogFont = &lf;
	cf.rgbColors = RGB(0, 0, 0);

	if (ChooseFont(&cf))
	{
		HFONT hf = CreateFontIndirect(&lf);
		if (hf)
		{
			HRESULT hr;
			hr = pDWFactory->CreateTextFormat(cf.lpLogFont->lfFaceName, NULL,
				DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
				24, _T(""), &pTF);
			if (FAILED(hr))
			{
				MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create the DirectWrite Text Format."),
					_T("DirectWrite Error"), MB_OK | MB_ICONERROR);
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
		{
			MessageBox(hWnd, _T("Font creation failed!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		}

	}
}

void OnMusicOnOff(HWND hWnd){

	if (myGame.music){
		myGame.music = false;
		PlaySound(NULL, NULL, NULL);

	}
	else{
		myGame.music = true;

		MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
		mii.fMask = MIIM_STATE;
		GetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
		mii.fState = MFS_ENABLED;
		SetMenuItemInfo(GetMenu(hWnd), ID_FILE_SAVE, FALSE, &mii);
		myMenuTitle = false;
	}
}

void OnEnglishChange(HWND hWnd){

	if (!english){
		english = true;
		MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
		mii.fMask = MIIM_STATE;
		GetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_ENGLISH, FALSE, &mii);
		SetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_SPANISH, FALSE, &mii);
		mii.fState = MFS_CHECKED;
		SetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_ENGLISH, FALSE, &mii);

		//SetThreadLocale(dwEnglish, SORT_DEFAULT);

		LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInst, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);

		LoadString(hInst, IDS_NEWGAME, szNewGame, MAX_LOADSTRING);
		LoadString(hInst, IDS_LOADGAME, szLoadGame, MAX_LOADSTRING);
		LoadString(hInst, IDS_AIONOFF, szAIOn, MAX_LOADSTRING);
		LoadString(hInst, IDS_INSTRUC, szInstruction, MAX_LOADSTRING);
		LoadString(hInst, IDS_CREDITS, szCredits, MAX_LOADSTRING);
		LoadString(hInst, IDS_EXIT, szExit, MAX_LOADSTRING);
		LoadString(hInst, IDS_XWIN, szXwins, MAX_LOADSTRING);
		LoadString(hInst, IDS_OWIN, szOwins, MAX_LOADSTRING);
		LoadString(hInst, IDS_TIES, szTies, MAX_LOADSTRING);

		InvalidateRect(hWnd, NULL, TRUE);
	}
}
void OnSpanishChange(HWND hWnd){
	
	if (english){
		english = false;
		MENUITEMINFO mii = { sizeof(MENUITEMINFO) };
		mii.fMask = MIIM_STATE;
		GetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_SPANISH, FALSE, &mii);
		SetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_ENGLISH, FALSE, &mii);
		mii.fState = MFS_CHECKED;
		SetMenuItemInfo(GetMenu(hWnd), ID_LANGUAGES_SPANISH, FALSE, &mii);

		//SetThreadLocale(dwSpanish, SORT_DEFAULT);
		
		LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInst, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);

		LoadString(hInst, IDS_NEWGAME, szNewGame, MAX_LOADSTRING);
		LoadString(hInst, IDS_LOADGAME, szLoadGame, MAX_LOADSTRING);
		LoadString(hInst, IDS_AIONOFF, szAIOn, MAX_LOADSTRING);
		LoadString(hInst, IDS_INSTRUC, szInstruction, MAX_LOADSTRING);
		LoadString(hInst, IDS_CREDITS, szCredits, MAX_LOADSTRING);
		LoadString(hInst, IDS_EXIT, szExit, MAX_LOADSTRING);
		LoadString(hInst, IDS_XWIN, szXwins, MAX_LOADSTRING);
		LoadString(hInst, IDS_OWIN, szOwins, MAX_LOADSTRING);
		LoadString(hInst, IDS_TIES, szTies, MAX_LOADSTRING);

		InvalidateRect(hWnd, NULL, TRUE);
	}
}