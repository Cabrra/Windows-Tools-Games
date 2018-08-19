#pragma once

#include <Windows.h> // Include the Win32 API
#include <tchar.h> // Include support for UNICODE
#include <sstream> // Include wostringstream support
using std::wostringstream;



#include <d2d1.h> // Include the Direct2D API.
#pragma comment(lib, "d2d1.lib") // Connect to the Direct2D Import Library.

#include <dwrite.h> // Include the DirectWrite API.
#pragma comment(lib, "dwrite.lib") // Connect to the DirectWrite Import Library.

#include <mmsystem.h> // Include the Multimedia header file.
#pragma comment(lib, "winmm.lib") // Connect to the Multimedia import library.

// WIC Stuff
#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")
#include <string>
using namespace std;
#include <thread>

#include <Windows.h>
#include <Strsafe.h>
#define M_PI 3.14159265358979323846
#include<cmath>
#define NUM_PARTICLES 50
#define NUM_DUSTPARTICLES 30
#define MAX_LOADSTRING 100


class Game
{
	// Window Handle:
	HWND hWnd;

	// DirectX Helper Functions

	// The SafeRelease Pattern
	template <class T> void SafeRelease(T **ppT)
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}

	// Programmer defined macro to make using the known colors easier.
	#define D2DColor(clr) D2D1::ColorF(D2D1::ColorF::clr)

	HRESULT CreateGraphics(HWND hWnd);
	void DestroyGraphics(void);

	// DirectX Interfaces:
	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRT;
	ID2D1SolidColorBrush *pBrush;

	D2D1_COLOR_F custom;
	D2D1_POINT_2F ptmouse;

	// WIC Interfaces
	IWICImagingFactory* pWICFactory;
	ID2D1Bitmap* background1;
	float fBackPosX1;
	ID2D1Bitmap* background2;
	float fBackPosX2;
	ID2D1Bitmap* background3;
	float fBackPosX3;
	ID2D1Bitmap* background4;
	float fBackPosX4;
	ID2D1Bitmap* background5;
	float fBackPosX5;

	ID2D1Bitmap* RightSprite;
	ID2D1Bitmap* LeftSprite;
	ID2D1Bitmap* Ball;
	ID2D1Bitmap* Ball2;

	ID2D1Bitmap* P1;
	ID2D1Bitmap* P2;
	ID2D1Bitmap* Numbers[10];
	ID2D1Bitmap* letters[26];
	ID2D1Bitmap* fire;
	ID2D1Bitmap* dust;
	ID2D1Bitmap* instruc;


	//character select
	ID2D1Bitmap* selectFox;
	ID2D1Bitmap* selectHippo;
	ID2D1Bitmap* selectMonkey;
	ID2D1Bitmap* selectTigger;

	ID2D1Bitmap* tittleScreen;
	

	//ID2D1Bitmap* particle;

	// DirectWrite Interfaces:
	IDWriteFactory* pDWFactory;
	IDWriteTextFormat* pTF;

	// Game Components:
	D2D1_RECT_F ballpos;
	D2D1_SIZE_F ballvec;
	D2D1_RECT_F ball2pos;
	D2D1_SIZE_F ball2vec;

	D2D1_RECT_F paddlepos;
	D2D1_SIZE_F paddlevec;

	D2D1_RECT_F Lpaddlepos;
	D2D1_SIZE_F Lpaddlevec;

	// Player 1 Sprite variables
	float fSpriteHeight;
	float fSpriteWidth;
	float fSpacing;
	int nFrame;
	float fPosX;
	float fSpriteFrameWidth;
	DWORD dwTime;

	// Player 2 Sprite variables
	float fSpriteHeight2;
	float fSpriteWidth2;
	float fSpacing2;
	int nFrame2;
	float fPosX2;
	float fSpriteFrameWidth2;
	DWORD dwTime2;

	// Ball Sprite variables
	float fBallHeight;
	float fBallWidth;
	float fBallSpacing;
	int nBallFrame;
	float fBallPosX;
	float fBallPos2X;
	float fBallFrameWidth;
	DWORD dwBallTime;

	// Particles
	D2D1_POINT_2F firePos[NUM_PARTICLES];
	D2D1_SIZE_F fireVel[NUM_PARTICLES];
	float fireLife[NUM_PARTICLES];

	D2D1_POINT_2F dustPos[NUM_PARTICLES];
	D2D1_SIZE_F dustVel[NUM_PARTICLES];
	float dustLife[NUM_PARTICLES];

	// Variables used to calculate frames per second:
	DWORD dwFrames;
	DWORD dwCurrentTime;
	DWORD dwLastUpdateTime;
	DWORD dwElapsedTime;
	std::wstring szFPS;

	//Other global variables
	bool AI1;
	bool AI2;
	bool fps;

	int P1Score;
	int P2Score;

	int maxScore;
	bool nPause;
	char* p1Name;
	char* p2Name;

	int p1Power;
	int p2Power;

	bool nStart;
	bool charSelect;
	bool instructions;

	int winner;
	int rowwins;

	wchar_t szOnePlayer[MAX_LOADSTRING];
	TCHAR szTwoPlayer[MAX_LOADSTRING];
	TCHAR szDemoMode[MAX_LOADSTRING];
	TCHAR szCharacterSelect[MAX_LOADSTRING];
	TCHAR szBack[MAX_LOADSTRING];
	TCHAR szStart[MAX_LOADSTRING];
	TCHAR szBoss[MAX_LOADSTRING];
	TCHAR szSelect[MAX_LOADSTRING];
	TCHAR szInstruction[MAX_LOADSTRING];
	TCHAR szExit[MAX_LOADSTRING];

	D2D1_COLOR_F gradientColor1;
	D2D1_COLOR_F gradientColor2;

	string leftName;
	string rightName;

	POINT mouseL, mouseR;
	bool numBall;
public:
	BOOL bRunning;		// Is the game running?
	HANDLE hGameThread; // Handle to the GameMain thread.
	BYTE keys[256];		// Current state of the keyboard.

	bool GetFPS() const { return fps; }
	void SetFPS(bool newFps) { fps = newFps; }
	int GetP1Score()const { return P1Score; }
	int GetP2Score()const { return P2Score; }
	void SetP1Score(int newScore) { P1Score = newScore; }
	void SetP2Score(int newScore) { P2Score = newScore; }

	bool GetPause()const { return nPause; }
	void SetPause(bool isPause) { nPause = isPause; };
	//void SetPlayer1Name(string newName) { p1Name = newName; }
	//void SetPlayer2Name(string newName) { p2Name = newName; }
	bool GetStart()const { return nStart; }

	int GetP1Power()const { return p1Power; }
	int GetP2Power()const { return p2Power; }
	void SetP1Power(int newPower) { p1Power = newPower; }
	void SetP2Power(int newPower) { p2Power = newPower; }


	D2D1_COLOR_F GetGradient1()const { return gradientColor1; }
	void SetGradient1(D2D1_COLOR_F one){ gradientColor1 = one; }
	D2D1_COLOR_F GetGradient2()const { return gradientColor2; }
	void SetGradient2(D2D1_COLOR_F two){ gradientColor2 = two; }

	void SetMaxScore(int newScore) { maxScore = newScore; }


	Game(void);
	virtual ~Game(void);

	void Reset();
	void Startup(void);
	void Shutdown(void);
	void Input(void);
	void AI(void);
	void Simulate(void);
	void Render(void);
	void TittleScreen();

	void SetHwnd(HWND _hWnd) {hWnd = _hWnd;}
	HRESULT LoadBitmapFromFile(LPCTSTR strFileName, ID2D1Bitmap** ppBitmap);

	HRESULT SetLeftPaddle(string left);
	HRESULT SetRightPaddle(string right);

	string GetLeftPaddlePath() const { return leftName; }
	string GetRightPaddlePath() const { return rightName; }
	int GetPlayers()const;
	void SetPlayers(int players);

	void SetMouseL(POINT newMouse) { mouseL = newMouse; };
	void SetMouseR(POINT newMouse) { mouseR = newMouse; };

	int GetWinner()const { return winner; }
	void SetWinner(int newWinner){ winner = newWinner; }

	int GetWins()const { return rowwins; }
	void SetWins(int newWins)  { rowwins = newWins; }
	bool GetAI2()const { return (AI2) ? true : false; }
	void GameExit(){ PostMessage(hWnd, WM_CLOSE, 0, 0); }

	D2D1_SIZE_F Normalize(D2D1_SIZE_F v1);

	void SetBalls(bool ball) { numBall = ball; }

	//load string table

	//void SetOnePlayer(string  name) { strcpy(szOnePlayer, name); }
	//void SetTwoPlayer(TCHAR  name) { wcscpy(szOnePlayer, name); }
	//void SetDemoMode(TCHAR  name) { _tcscpy(szOnePlayer, name); }
	//void SetCharacterSelect(TCHAR  name) { _tcscpy(szOnePlayer, name); }
	//void SetBack(TCHAR  name) { _tcscpy(szOnePlayer, name); }
	//void SetStart(TCHAR  name) { _tcscpy(szStart, name); }
	//void SetBoss(TCHAR  name) { _tcscpy(szBoss, name); }
	//void SetSelect(TCHAR  name) { _tcscpy(szSelect, name); }
	//void SetInstruction(TCHAR  name) { _tcscpy(szInstruction, name); }
	//void SetExit(TCHAR  name) { _tcscpy(szExit, name); }
};
