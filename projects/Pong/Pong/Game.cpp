#include "Game.h"

Game::Game(void)
{
	bRunning = TRUE;
	hWnd = NULL;
	ZeroMemory(keys, sizeof(keys));

	pD2DFactory = NULL;
	pRT = NULL;
	pBrush = NULL;
	pDWFactory = NULL;
	pTF = NULL;

	mouseL = POINT();
	mouseR = POINT();
	AI1 = false;
	AI2 = true;
	fps = false;
	charSelect = false;
	nPause = false;
	p1Name = "ONE";
	p2Name = "DUE";
	nStart = false;
	instructions = false;
	rowwins = 0;
	numBall = false;

	maxScore = 5;

	gradientColor1 = D2DColor(Red);
	gradientColor2 = D2DColor(Blue);

	P1Score = 0;
	P2Score = 0;

	// Zero out the frames per second variables:
	dwFrames = 0;
	dwCurrentTime = 0;
	dwLastUpdateTime = 0;
	dwElapsedTime = 0;
	szFPS = _T("");
}

Game::~Game(void)
{
}

void Game::Startup(void)
{
	//TODO: Create Back Buffer

	// Initialize DirectX.
	HRESULT hr = CreateGraphics(hWnd);
	if (FAILED(hr))
	{
		return; // Return -1 to abort Window Creation.
	}

	//TODO: Load Bitmaps/Brushes/Pens/Fonts

	//TODO: Initialize Game Components
	//Init background speed

	fBackPosX1 = 0.0F;
	fBackPosX2 = 0.0F;
	fBackPosX3 = 0.0F;
	fBackPosX4 = 0.0F;
	fBackPosX5 = 0.0F;

	// Init Player 1 Sprite variables
	fSpriteHeight = RightSprite->GetSize().height;
	fSpriteWidth = RightSprite->GetSize().width;
	fSpacing = 0.0f;
	nFrame = 0;
	fPosX = 0.0f;
	fSpriteFrameWidth = fSpriteWidth / 3;
	dwTime = GetTickCount() + 100;

	// Init Player 2 Sprite variables
	fSpriteHeight2 = LeftSprite->GetSize().height;
	fSpriteWidth2 = LeftSprite->GetSize().width;
	fSpacing2 = 0.0f;
	nFrame2 = 0;
	fPosX2 = 0.0f;
	fSpriteFrameWidth2 = fSpriteWidth2 / 3;
	dwTime2 = GetTickCount() + 100;

	// Init Ball Sprite variables
	fBallHeight = Ball->GetSize().height;
	fBallWidth = Ball->GetSize().width;
	fBallSpacing = 1.0f;
	nBallFrame = 0;
	fBallPosX = 0.0f;
	fBallPos2X = 0.0f;
	fBallFrameWidth = fBallWidth / 12;
	dwBallTime = GetTickCount() + 100;

	// ball
	ballpos = D2D1::RectF(pRT->GetSize().width / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

	ballvec = D2D1::SizeF(2, 2);

	ball2pos = D2D1::RectF(pRT->GetSize().width / 2 + (pRT->GetSize().width / 2) / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

	ball2vec = D2D1::SizeF(-2, 2);

	//player 1
	paddlepos = D2D1::RectF(pRT->GetSize().width - (fSpriteFrameWidth * 2), 300,
		pRT->GetSize().width - 5, 300 + fSpriteHeight * 2);
	paddlevec = D2D1::SizeF(1, 3);

	//player 2
	Lpaddlepos = D2D1::RectF(0, 300,
		fSpriteFrameWidth2 + 5, 300 + fSpriteHeight2 * 2);
	Lpaddlevec = D2D1::SizeF(1, 3);

}

void Game::Shutdown(void)
{
	//TODO: Unload Bitmaps/Brushes/Pens/Fonts

	//TODO: Destroy Back Buffer

	// Shutdown DirectX.
	DestroyGraphics();
}

void Game::Input(void)
{
	if (!AI1){
		//TODO: Read User Input
		if (keys[VK_ESCAPE] & 0x80)
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}

		// Check if the W Key is pressed:
		if (keys['O'] & 0x80)
		{
			// TODO: W Key down action.
			ballpos = D2D1::RectF(pRT->GetSize().width / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

			ballvec = D2D1::SizeF(2, 2);
			ball2pos = D2D1::RectF(pRT->GetSize().width / 2 + (pRT->GetSize().width / 2) / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

			ball2vec = D2D1::SizeF(-2, 2);
		}

		if (keys[VK_UP] & 0x80)
		{
			// TODO: Up Arrow Key down action.
			if (paddlepos.top > 0){
				paddlepos.top -= paddlevec.height;
				paddlepos.bottom -= paddlevec.height;
			}
		}
		if (keys[VK_DOWN] & 0x80)
		{
			// TODO: Up Arrow Key down action.
			if (paddlepos.top + fSpriteHeight * 2 <= pRT->GetSize().height){
				paddlepos.top += paddlevec.height;
				paddlepos.bottom += paddlevec.height;
			}
		}
	}
	else{
		if (ballvec.width > 0){ //Only when the ball is coming
			if (paddlepos.top + (fSpriteHeight / 2) > ballpos.bottom){ // UP
				paddlepos.top -= paddlevec.height;
				paddlepos.bottom -= paddlevec.height;
			}
			if (paddlepos.bottom - (fSpriteHeight2 / 2) < ballpos.top){ //Down
				paddlepos.top += paddlevec.height;
				paddlepos.bottom += paddlevec.height;
			}
		}
		if (ball2vec.width > 0){ //Only when the ball is coming
			if (paddlepos.top + (fSpriteHeight / 2) > ball2pos.bottom){ // UP
				paddlepos.top -= paddlevec.height;
				paddlepos.bottom -= paddlevec.height;
			}
			if (paddlepos.bottom - (fSpriteHeight2 / 2) < ball2pos.top){ //Down
				paddlepos.top += paddlevec.height;
				paddlepos.bottom += paddlevec.height;
			}
		}
	}
}

void Game::AI(void)
{
	if (!AI2){
		//TODO: Read User Input
		if (keys[VK_ESCAPE] & 0x80)
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}

		// Check if the W Key is pressed:
		if (keys['O'] & 0x80)
		{
			// TODO: W Key down action.
			ballpos = D2D1::RectF(pRT->GetSize().width / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

			ballvec = D2D1::SizeF(2, 2);
			ball2pos = D2D1::RectF(pRT->GetSize().width / 2 + (pRT->GetSize().width / 2) / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

			ball2vec = D2D1::SizeF(-2, 2);
		}

		if (keys['W'] & 0x80)
		{
			// TODO: Up Arrow Key down action.
			if (Lpaddlepos.top > 0){
				Lpaddlepos.top -= Lpaddlevec.height;
				Lpaddlepos.bottom -= Lpaddlevec.height;
			}
		}
		if (keys['S'] & 0x80)
		{
			// TODO: Up Arrow Key down action.
			if (Lpaddlepos.top + fSpriteHeight2 * 2 <= pRT->GetSize().height){
				Lpaddlepos.top += Lpaddlevec.height;
				Lpaddlepos.bottom += Lpaddlevec.height;
			}
		}
	}
	else{

		// EASY

		if (ballvec.width < 0){ //Only when the ball is coming
			if (Lpaddlepos.top + (fSpriteHeight2 / 2) > ballpos.bottom){ // UP
				Lpaddlepos.top -= Lpaddlevec.height;
				Lpaddlepos.bottom -= Lpaddlevec.height;
			}
			else if (Lpaddlepos.bottom - (fSpriteHeight2 / 2) < ballpos.top){ //Down
				Lpaddlepos.top += Lpaddlevec.height;
				Lpaddlepos.bottom += Lpaddlevec.height;
			}
			if (numBall){
				if (ball2vec.width < 0){
					if (Lpaddlepos.top + (fSpriteHeight2 / 2) > ball2pos.bottom){ // UP
						Lpaddlepos.top -= Lpaddlevec.height;
						Lpaddlepos.bottom -= Lpaddlevec.height;
					}


					if (Lpaddlepos.bottom - (fSpriteHeight2 / 2) < ball2pos.top){ //Down
						Lpaddlepos.top += Lpaddlevec.height;
						Lpaddlepos.bottom += Lpaddlevec.height;
					}
				}
			}
			//Lpaddlevec.width += 0.5F;

			// HARD
			//if (ballvec.width < 0){ //Only when the ball is coming
			//if (ballpos.left < 35){
			//Lpaddlepos.top = ballpos.top + (fBallHeight/2);
		}
	}
}

void Game::Simulate(void)
{
	//TODO: Simulate AI

	//TODO: Simulate Physics

	ballpos.left += ballvec.width;
	ballpos.top += ballvec.height;
	ballpos.right += ballvec.width;
	ballpos.bottom += ballvec.height;

	if (numBall){
		ball2pos.left += ball2vec.width;
		ball2pos.top += ball2vec.height;
		ball2pos.right += ball2vec.width;
		ball2pos.bottom += ball2vec.height;

	}
	fBackPosX1++;
	fBackPosX2++;
	fBackPosX3++;
	fBackPosX4++;
	fBackPosX5++;

	//TODO: Simulate Collision Detection & Response

	if (ballpos.bottom > pRT->GetSize().height)
	{
		ballvec.height = -ballvec.height;
	}
	if (ballpos.top < 0)
	{
		ballvec.height = (-1) * ballvec.height;
	}
	if (numBall){
		if (ball2pos.bottom > pRT->GetSize().height)
		{
			ball2vec.height = -ball2vec.height;
		}
		if (ball2pos.top < 0)
		{
			ball2vec.height = (-1) * ball2vec.height;
		}
	}

	if (ballpos.right < 0 || ball2pos.right < 0)
	{
		P1Score++;
		if (maxScore == P1Score){
			winner = 1;
		}
		ballpos = D2D1::RectF(pRT->GetSize().width / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));
		ballvec = D2D1::SizeF(2, 2);
		if (numBall){
			ball2pos = D2D1::RectF(pRT->GetSize().width / 2 + (pRT->GetSize().width / 2) / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));
			ball2vec = D2D1::SizeF(-2, 2);
		}

	}

	if (ballpos.left > pRT->GetSize().width || ball2pos.left > pRT->GetSize().width){
		P2Score++;
		if (maxScore == P2Score){
			winner = 2;
		}
		ballpos = D2D1::RectF(pRT->GetSize().width / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));
		ballvec = D2D1::SizeF(2, 2);
		if (numBall){
			ball2pos = D2D1::RectF(pRT->GetSize().width / 2 + (pRT->GetSize().width / 2) / 2, pRT->GetSize().height / 2, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (fBallFrameWidth * 2), (pRT->GetSize().height / 2) + (fBallHeight * 2));

			ball2vec = D2D1::SizeF(-2, 2);
		}
	}


	// Rectangle to Rectangle Intersection:
	RECT rIntersect;
	RECT lIntersect;
	RECT rBall = { (LONG)ballpos.left, (LONG)ballpos.top, (LONG)ballpos.right, (LONG)ballpos.bottom };
	RECT lBall = { (LONG)ball2pos.left, (LONG)ball2pos.top, (LONG)ball2pos.right, (LONG)ball2pos.bottom };
	RECT rPaddle = { (LONG)paddlepos.left, (LONG)paddlepos.top, (LONG)paddlepos.right, (LONG)paddlepos.bottom };
	RECT lPaddle = { (LONG)Lpaddlepos.left, (LONG)Lpaddlepos.top, (LONG)Lpaddlepos.right, (LONG)Lpaddlepos.bottom };

	if (IntersectRect(&rIntersect, &rBall, &rPaddle))
	{
		ballvec.width = -ballvec.width;
		ballvec.height = -ballvec.height;
		//D2D1_SIZE_F normal1;
		//normal1 = Normalize(ballvec);

		////float angle = 1 - 2 * ((ballpos.left ) - rPaddle.left) / fSpriteFrameWidth;
		//float angle = atan2((ballpos.top + fBallHeight / 2) - (rPaddle.top + fSpriteHeight / 2), (ballpos.left + fBallFrameWidth / 2) - (rPaddle.left + fSpriteFrameWidth / 2));
		//
		////angle = (FLOAT)(angle * 180 / M_PI);
		//ballvec.width = (FLOAT)normal1.width * angle;
		//ballvec.height = (FLOAT)normal1.height *angle;

		if (p1Power < 100)
			p1Power += 2;
	}


	if (IntersectRect(&lIntersect, &rBall, &lPaddle)){

		ballvec.width = -ballvec.width;

		//D2D1_SIZE_F normal1;
		//normal1 = Normalize(ballvec);
		////float angle = 1 - 2 * ((ballpos.left ) - lPaddle.left) / fSpriteFrameWidth;
		//float angle = atan2((ballpos.top + fBallHeight / 2) - (lPaddle.top + fSpriteHeight2 / 2), (ballpos.left + fBallFrameWidth / 2) - (lPaddle.left + fSpriteFrameWidth2 / 2));
		////angle = (FLOAT)(angle * 180 / M_PI);
		//ballvec.width = (FLOAT)normal1.width * angle;
		//ballvec.height = (FLOAT)normal1.width *-angle;
		if (p2Power < 100)
			p2Power += 2;

	}
	if (numBall){
		if (IntersectRect(&lIntersect, &lBall, &rPaddle))
		{
			ball2vec.width = -ball2vec.width;

			//D2D1_SIZE_F normal1;
			//normal1 = Normalize(ballvec);
			////float angle = (1 - 2 * ((ball2pos.left ) - rPaddle.left) / fSpriteFrameWidth) ;
			//float angle = atan2((ball2pos.top + fBallHeight / 2) - (rPaddle.top + fSpriteHeight / 2), (ball2pos.left + fBallFrameWidth / 2) - (rPaddle.left + fSpriteFrameWidth / 2));
			////angle = (FLOAT)(angle * 180 / M_PI);
			//ball2vec.width = (FLOAT)normal1.width * angle;
			//ball2vec.height = (FLOAT)normal1.height *angle;
			if (p1Power < 100)
				p1Power += 2;
		}
		if (IntersectRect(&lIntersect, &lBall, &lPaddle)){
			ball2vec.width = -ball2vec.width;


			//D2D1_SIZE_F normal1;
			//normal1 = Normalize(ballvec);
			//float angle = 1 - 2 * ((ball2pos.left ) - lPaddle.left) / fSpriteFrameWidth;
			//float angle = atan2((ball2pos.top + fBallHeight / 2) - (lPaddle.top + fSpriteHeight2 / 2), (ball2pos.left + fBallFrameWidth / 2) - (lPaddle.left + fSpriteFrameWidth2 / 2));
			//angle = (FLOAT)(angle * 180 / M_PI);
			//ball2vec.width = (FLOAT)(-1) * normal1.width * angle;
			//ball2vec.height = (FLOAT)normal1.height *angle;
			if (p2Power < 100)
				p2Power += 2;

		}

		if (IntersectRect(&rIntersect, &lBall, &rBall)){

			ballvec.width = -ballvec.width;


			ball2vec.width = -ball2vec.width;

			/*D2D1_SIZE_F normal1, normal2;
			normal1 = Normalize(ballvec);
			normal2 = Normalize(ball2vec);
			float angle = 1 - 2 * ((ballpos.left) - ball2pos.left) / fBallFrameWidth;
			float angle = atan2((ballpos.top + fBallHeight / 2) - (ball2pos.top + fBallHeight / 2), (ballpos.left + fBallFrameWidth / 2) - (ball2pos.left + fBallFrameWidth / 2));
			angle = (FLOAT)(angle * 180 / M_PI);
			ballvec.width = (FLOAT) normal1.width * -sin(angle);
			ballvec.height = (FLOAT) normal1.height * cos(angle);

			angle = 1 - 2 * ((ball2pos.left) - ballpos.left) / fBallFrameWidth;
			ball2vec.width = (FLOAT)-normal2.width * -sin(angle);
			ball2vec.height = (FLOAT)normal2.height * cos(angle);
			*/
		}
	}
	// Update BALL sprite data
	if (GetTickCount() > dwBallTime)
	{
		nBallFrame++;
		dwBallTime = GetTickCount() + 100;
	}

	if (nBallFrame == 12)
	{
		nBallFrame = 0;
	}

	fBallPosX += 4.0f;
	if (fBallPosX > pRT->GetSize().width)
	{
		fBallPosX = -fBallFrameWidth;
	}
	if (numBall){
		fBallPos2X += 4.0f;

		if (fBallPos2X > pRT->GetSize().width)
		{
			fBallPos2X = -fBallFrameWidth;
		}
	}

	// Update Player 1 sprite data
	if (GetTickCount() > dwTime)
	{
		nFrame++;
		dwTime = GetTickCount() + 100;
	}

	if (nFrame == 3)
	{
		nFrame = 0;
	}

	fPosX += 4.0f;
	if (fPosX > pRT->GetSize().width)
	{
		fPosX = -fSpriteFrameWidth;
	}

	// Update Player 2 sprite data
	if (GetTickCount() > dwTime2)
	{
		nFrame2++;
		dwTime2 = GetTickCount() + 100;
	}

	if (nFrame2 == 3)
	{
		nFrame2 = 0;
	}

	fPosX2 += 4.0f;
	if (fPosX2 > pRT->GetSize().width)
	{
		fPosX2 = -fSpriteFrameWidth2;
	}
}

void Game::Render(void)
{
	pRT->BeginDraw();

	//TODO: Clear Back Buffer

	//pRT->Clear(D2DColor(CornflowerBlue));
	// Render Background

	//1
	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX1, 0));
	pRT->DrawBitmap(background1, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX1 - pRT->GetSize().width, 0));
	pRT->DrawBitmap(background1, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	fBackPosX1 -= 2.0F;
	if (fBackPosX1 < 0) fBackPosX1 = pRT->GetSize().width;

	//2
	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX2, 0));
	pRT->DrawBitmap(background2, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX2 - pRT->GetSize().width, 0));
	pRT->DrawBitmap(background2, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	fBackPosX2 += 0.25F;
	if (fBackPosX2 > pRT->GetSize().width) fBackPosX2 = 0.0f;

	//3
	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX3, 0));
	pRT->DrawBitmap(background3, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX3 - pRT->GetSize().width, 0));
	pRT->DrawBitmap(background3, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	fBackPosX3 += 0.8F;
	if (fBackPosX3 > pRT->GetSize().width) fBackPosX3 = 0.0F;

	//4
	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX4, 0));
	pRT->DrawBitmap(background4, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX4 - pRT->GetSize().width, 0));
	pRT->DrawBitmap(background4, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	fBackPosX4 += 0.80F;
	if (fBackPosX4 > pRT->GetSize().width) fBackPosX4 = 0.0f;


	// TEST
	/*
	D2D1_ELLIPSE circle;
	circle.point.x = (ballpos.left+ballpos.right)/2;
	circle.point.y = (ballpos.top+ballpos.bottom)/2;
	circle.radiusX = (ballpos.right-ballpos.left)/2;
	circle.radiusY = (ballpos.bottom-ballpos.top)/2;
	pBrush->SetColor(D2DColor(Chartreuse));
	pRT->FillEllipse(circle, pBrush);


	// Render the Right Paddle.
	pBrush->SetColor(D2DColor(Green));
	pRT->FillRectangle(paddlepos, pBrush);

	pBrush->SetColor(D2DColor(Green));
	pRT->FillRectangle(Lpaddlepos, pBrush);

	*/

	//Score
	//pRT->DrawBitmap(Numbers[1], D2D1::RectF((pRT->GetSize().width / 2) + (Numbers[1]->GetSize().width ), 3, (pRT->GetSize().width / 2) + (Numbers[1]->GetSize().width ) + Numbers[1]->GetSize().width, Numbers[1]->GetSize().height + 3));

	std::wostringstream NameP1;
	NameP1 << p1Name;
	std::wstring tempN = NameP1.str();
	for (unsigned int i = 0; i < tempN.length(); i++){
		pRT->DrawBitmap(letters[tempN[i] - 65], D2D1::RectF((pRT->GetSize().width / 2) + (letters[tempN[i] - 65]->GetSize().width * i), 3, (pRT->GetSize().width / 2) + (letters[tempN[i] - 65]->GetSize().width * i) + letters[tempN[i] - 65]->GetSize().width, letters[tempN[i] - 65]->GetSize().height + 3));
	}

	std::wostringstream strP1;
	strP1 << P1Score;
	std::wstring temp = strP1.str();
	for (unsigned int i = 0; i < temp.length(); i++){
		pRT->DrawBitmap(Numbers[temp[i] - 48], D2D1::RectF((pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (Numbers[temp[i] - 48]->GetSize().width * i), 3, (pRT->GetSize().width / 2) + (pRT->GetSize().width / 2) / 2 + (Numbers[temp[i] - 48]->GetSize().width * i) + Numbers[temp[i] - 48]->GetSize().width, Numbers[temp[i] - 48]->GetSize().height + 3));
	}

	temp.clear();
	tempN.clear();

	std::wostringstream NameP2;
	NameP2 << p2Name;
	tempN = NameP2.str();
	for (unsigned int i = 0; i < tempN.length(); i++){
		pRT->DrawBitmap(letters[tempN[i] - 65], D2D1::RectF((letters[tempN[i] - 65]->GetSize().width * i), 3, (letters[tempN[i] - 65]->GetSize().width * i) + letters[tempN[i] - 65]->GetSize().width, letters[tempN[i] - 65]->GetSize().height + 3));
	}

	std::wostringstream strP2;
	strP2 << P2Score;
	temp = strP2.str();

	for (unsigned int i = 0; i < temp.length(); i++){
		pRT->DrawBitmap(Numbers[temp[i] - 48], D2D1::RectF((pRT->GetSize().width / 2) / 2 + (Numbers[temp[i] - 48]->GetSize().width * i), 3, (pRT->GetSize().width / 2) / 2 + (Numbers[temp[i] - 48]->GetSize().width * i) + Numbers[temp[i] - 48]->GetSize().width, Numbers[temp[i] - 48]->GetSize().height + 3));
	}

	//p1 power metter
	if (!AI1){
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
			D2D1::Point2F(pRT->GetSize().width / 2 + 225, pRT->GetSize().height - 25),
			D2D1::Point2F(0, 0),
			150,
			25),
			pGradientStops,
			&m_pRadialGradientBrush
			);

		pBrush->SetColor(D2DColor(Black));
		D2D1_RECT_F gradRect = D2D1::RectF(pRT->GetSize().width / 2 + 150, pRT->GetSize().height - 45, pRT->GetSize().width / 2 + 300, pRT->GetSize().height - 20);
		D2D1_RECT_F FgradRect = D2D1::RectF(pRT->GetSize().width / 2 + 150, pRT->GetSize().height - 45, pRT->GetSize().width / 2 + 150 + p1Power, pRT->GetSize().height - 20);
		pRT->FillRectangle(FgradRect, m_pRadialGradientBrush);
		pRT->DrawRectangle(gradRect, pBrush);

	}


	//p2 power meter
	if (!AI2){
		ID2D1GradientStopCollection *pGradientStops = NULL;
		ID2D1RadialGradientBrush *m_pRadialGradientBrush;

		D2D1_GRADIENT_STOP gradientStops[2];
		gradientStops[0].color = D2DColor(Red);
		gradientStops[0].position = 0.0f;
		gradientStops[1].color = D2DColor(Blue);
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
			D2D1::Point2F(75, pRT->GetSize().height - 25),
			D2D1::Point2F(0, 0),
			150,
			25),
			pGradientStops,
			&m_pRadialGradientBrush
			);

		pBrush->SetColor(D2DColor(Black));
		D2D1_RECT_F gradRect = D2D1::RectF(15, pRT->GetSize().height - 50, 165, pRT->GetSize().height - 20);
		D2D1_RECT_F FgradRect = D2D1::RectF(pRT->GetSize().width / 2 + 150, pRT->GetSize().height - 45, pRT->GetSize().width / 2 + 150 + p1Power, pRT->GetSize().height - 20);
		pRT->FillRectangle(FgradRect, m_pRadialGradientBrush);
		pRT->DrawRectangle(gradRect, pBrush);
	}

	// Ball

	D2D1_RECT_F BalldestRect;
	D2D1_RECT_F Ball2destRect;
	D2D1_RECT_F BallsrcRect;

	BallsrcRect.left = nBallFrame * fBallFrameWidth;
	BallsrcRect.top = 0;
	BallsrcRect.right = BallsrcRect.left + fBallFrameWidth;
	BallsrcRect.bottom = BallsrcRect.top + fBallHeight;

	BalldestRect.left = ballpos.left;
	BalldestRect.top = ballpos.top;
	BalldestRect.right = ballpos.left + (fBallFrameWidth * 2);
	BalldestRect.bottom = ballpos.top + (fBallHeight * 2);

	if (numBall){
		Ball2destRect.left = ball2pos.left;
		Ball2destRect.top = ball2pos.top;
		Ball2destRect.right = ball2pos.left + (fBallFrameWidth * 2);
		Ball2destRect.bottom = ball2pos.top + (fBallHeight * 2);
	}

	// Render particles
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		// Render
		pRT->DrawBitmap(fire,
			D2D1::RectF(firePos[i].x - 20.0f, firePos[i].y - 20.0f, firePos[i].x + 20.0f, firePos[i].y + 20.0f),
			fireLife[i] / 100.0f);


		// Update particles position
		firePos[i].x += fireVel[i].width;
		firePos[i].y += fireVel[i].height;

		// Update particle life
		fireLife[i]--;

		// Respawn particles
		if (fireLife[i] <= 0)
		{
			firePos[i] = D2D1::Point2F(ballpos.left + fBallFrameWidth / 2, ballpos.bottom - fBallHeight / 2);
			fireVel[i] = D2D1::SizeF((FLOAT)(rand() % 9) - 4.0f, (FLOAT)(rand() % 3) - 3.0f);
			fireLife[i] = float(rand() % 30) + 30.0f;
		}
	}

	pRT->DrawBitmap(Ball, BalldestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, BallsrcRect);

	if (numBall){
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			// Render
			pRT->DrawBitmap(fire,
				D2D1::RectF(firePos[i].x - 20.0f, firePos[i].y - 20.0f, firePos[i].x + 20.0f, firePos[i].y + 20.0f),
				fireLife[i] / 100.0f);


			// Update particles position
			firePos[i].x += fireVel[i].width;
			firePos[i].y += fireVel[i].height;

			// Update particle life
			fireLife[i]--;

			// Respawn particles
			if (fireLife[i] <= 0)
			{
				firePos[i] = D2D1::Point2F(ball2pos.left + fBallFrameWidth / 2, ball2pos.bottom - fBallHeight / 2);
				fireVel[i] = D2D1::SizeF((FLOAT)(rand() % 9) - 4.0f, (FLOAT)(rand() % 3) - 3.0f);
				fireLife[i] = float(rand() % 30) + 30.0f;
			}
		}

		pRT->DrawBitmap(Ball2, Ball2destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, BallsrcRect);
		// if statement
	}

	// Player 1

	D2D1_RECT_F RdestRect;
	D2D1_RECT_F RsrcRect;
	RsrcRect.left = nFrame * fSpriteFrameWidth;
	RsrcRect.top = 0;
	RsrcRect.right = RsrcRect.left + fSpriteFrameWidth;
	RsrcRect.bottom = RsrcRect.top + fSpriteHeight;

	RdestRect.left = paddlepos.left;
	RdestRect.top = paddlepos.top;
	RdestRect.right = paddlepos.left + (fSpriteFrameWidth * 2);
	RdestRect.bottom = paddlepos.top + (fSpriteHeight * 2);

	//shadow
	pRT->SetTransform(D2D1::Matrix3x2F::Skew(45.0f, 10.0f,
		D2D1::Point2F(paddlepos.left + fSpriteFrameWidth / 2,
		paddlepos.top + (8 * fSpriteHeight))));

	pBrush->SetColor(D2D1::ColorF(0x000000, 0.4f));

	// Antialias mode must be changed for FillOpacityMask to work
	pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	// Render using the brush
	RdestRect.left += 240;
	RdestRect.top -= 50;
	RdestRect.bottom -= 50;
	RdestRect.right += 240;
	pRT->FillOpacityMask(RightSprite, pBrush,
		D2D1_OPACITY_MASK_CONTENT_GRAPHICS, RdestRect, RsrcRect);

	// Set antialias mode back to default
	pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	// Set the transform back to the identity matrix
	pRT->SetTransform(D2D1::Matrix3x2F::Identity());

	//paddle 1
	RsrcRect.left = nFrame * fSpriteFrameWidth;
	RsrcRect.top = 0;
	RsrcRect.right = RsrcRect.left + fSpriteFrameWidth;
	RsrcRect.bottom = RsrcRect.top + fSpriteHeight;

	RdestRect.left = paddlepos.left;
	RdestRect.top = paddlepos.top;
	RdestRect.right = paddlepos.left + (fSpriteFrameWidth * 2);
	RdestRect.bottom = paddlepos.top + (fSpriteHeight * 2);

	pRT->DrawBitmap(RightSprite, RdestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RsrcRect);

	for (int i = 0; i < NUM_DUSTPARTICLES; i++)
	{
		// Render
		pRT->DrawBitmap(dust,
			D2D1::RectF(dustPos[i].x - 5.0f, dustPos[i].y - 5.0f, dustPos[i].x + 5.0f, dustPos[i].y + 5.0f),
			dustLife[i] / 20.0f);


		// Update particles position
		dustPos[i].x += dustVel[i].width;
		dustPos[i].y += dustVel[i].height;

		// Update particle life
		dustLife[i]--;

		// Respawn particles
		if (dustLife[i] <= 0)
		{
			dustPos[i] = D2D1::Point2F(paddlepos.left, paddlepos.bottom - fSpriteHeight / 2);
			dustVel[i] = D2D1::SizeF((FLOAT)(rand() % 9) - 4.0f, (FLOAT)(rand() % 3) - 3.0f);
			dustLife[i] = float(rand() % 30) + 30.0f;
		}
	}

	// Player 2

	D2D1_RECT_F LdestRect;
	D2D1_RECT_F LsrcRect;
	LsrcRect.left = nFrame * fSpriteFrameWidth2;
	LsrcRect.top = 0;
	LsrcRect.right = LsrcRect.left + fSpriteFrameWidth2;
	LsrcRect.bottom = LsrcRect.top + fSpriteHeight2;

	LdestRect.left = Lpaddlepos.left;
	LdestRect.top = Lpaddlepos.top;
	LdestRect.right = Lpaddlepos.left + (fSpriteFrameWidth2 * 2);
	LdestRect.bottom = Lpaddlepos.top + (fSpriteHeight2 * 2);

	//shadow
	pRT->SetTransform(D2D1::Matrix3x2F::Skew(-45.0f, 10.0f,
		D2D1::Point2F(Lpaddlepos.left + fSpriteFrameWidth2 / 2,
		Lpaddlepos.top + (8 * fSpriteHeight2))));

	pBrush->SetColor(D2D1::ColorF(0x000000, 0.4f));

	// Antialias mode must be changed for FillOpacityMask to work
	pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	// Render using the brush
	LdestRect.left -= 200;
	RdestRect.top += 30;
	RdestRect.bottom += 30;
	LdestRect.right -= 200;
	pRT->FillOpacityMask(LeftSprite, pBrush,
		D2D1_OPACITY_MASK_CONTENT_GRAPHICS, LdestRect, LsrcRect);

	// Set antialias mode back to default
	pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	// Set the transform back to the identity matrix
	pRT->SetTransform(D2D1::Matrix3x2F::Identity());

	//paddle2

	LsrcRect.left = nFrame * fSpriteFrameWidth2;
	LsrcRect.top = 0;
	LsrcRect.right = LsrcRect.left + fSpriteFrameWidth2;
	LsrcRect.bottom = LsrcRect.top + fSpriteHeight2;

	LdestRect.left = Lpaddlepos.left;
	LdestRect.top = Lpaddlepos.top;
	LdestRect.right = Lpaddlepos.left + (fSpriteFrameWidth2 * 2);
	LdestRect.bottom = Lpaddlepos.top + (fSpriteHeight2 * 2);

	pRT->DrawBitmap(LeftSprite, LdestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, LsrcRect);

	for (int i = 0; i < NUM_DUSTPARTICLES; i++)
	{
		// Render
		pRT->DrawBitmap(dust,
			D2D1::RectF(dustPos[i].x - 5.0f, dustPos[i].y - 5.0f, dustPos[i].x + 5.0f, dustPos[i].y + 5.0f),
			dustLife[i] / 20.0f);


		// Update particles position
		dustPos[i].x += dustVel[i].width;
		dustPos[i].y += dustVel[i].height;

		// Update particle life
		dustLife[i]--;

		// Respawn particles
		if (dustLife[i] <= 0)
		{
			dustPos[i] = D2D1::Point2F(Lpaddlepos.left, Lpaddlepos.bottom - fSpriteHeight2 / 2);
			dustVel[i] = D2D1::SizeF((FLOAT)(rand() % 9) - 4.0f, (FLOAT)(rand() % 3) - 3.0f);
			dustLife[i] = float(rand() % 30) + 30.0f;
		}
	}

	//5

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX5, 0));
	pRT->DrawBitmap(background5, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	pRT->SetTransform(D2D1::Matrix3x2F::Translation(fBackPosX5 - pRT->GetSize().width, 0));
	pRT->DrawBitmap(background5, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));
	pRT->SetTransform(D2D1::IdentityMatrix());

	fBackPosX5 += 1.5F;
	if (fBackPosX5 > pRT->GetSize().width) fBackPosX5 = 0.0f;

	// Frames Per Second
	dwFrames++;
	dwCurrentTime = GetTickCount();
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
	if (dwElapsedTime > 1000)
	{
		wostringstream wos;
		wos << L"FPS: " << dwFrames;
		szFPS = wos.str();
		dwFrames = 0;
		dwLastUpdateTime = dwCurrentTime;
	}
	if (fps){
		pBrush->SetColor(D2DColor(Yellow));
		pRT->DrawText(szFPS.c_str(), szFPS.length(), pTF, D2D1::RectF(0, pRT->GetSize().height - 30, 200, pRT->GetSize().height), pBrush);
	}


	//TODO: Present Back Buffer

	HRESULT hr = pRT->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		//TODO: Destroy Direct2D.
		DestroyGraphics();
		//TODO: Recreate Direct2D.
		CreateGraphics(hWnd);
	}
}


HRESULT Game::CreateGraphics(HWND hWnd)
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
	//pTF->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
	//pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	//pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// Create the COM imaging factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pWICFactory)
		);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Create WIC Interface."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	// Load Bitmaps

	//Parallax background

	hr = LoadBitmapFromFile(L"Background//Parallax//1.png", &background1);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load background 1."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Background//Parallax//2.png", &background2);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load background 2."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Background//Parallax//3.png", &background3);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load background 3."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Background//Parallax//4.png", &background4);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load background 4."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Background//Parallax//5.png", &background5);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load background 5."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}


	hr = LoadBitmapFromFile(L"Background//TITTLE.jpg", &tittleScreen);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load tittle screen."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"Using//RFox.png", &RightSprite);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load RFox.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"Using//LHippo.png", &LeftSprite);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load Hippo.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"Using//Pork.png", &Ball);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load Pork.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"Using//Pork.png", &Ball2);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load Pork.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"Using//selectFox.png", &selectFox);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load selectFox.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Using//selectHippo.png", &selectHippo);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load selectHippo.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Using//selectMonkey.png", &selectMonkey);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load selectMonkey.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Using//selectTigger.png", &selectTigger);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load selectTigger.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = LoadBitmapFromFile(L"Background//instructions.jpg", &instruc);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load instructions.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	for (int i = 0; i < 10; i++){
		std::wostringstream number;
		number << "Background\\Numbers\\" << i << ".png";
		hr = LoadBitmapFromFile(number.str().c_str(), &Numbers[i]);
		if (FAILED(hr))
		{
			MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load numbers array."),
				_T("WIC Error"), MB_OK | MB_ICONERROR);
			return hr;
		}
		number.clear();
	}

	char count = 'A';
	for (int i = 0; i < 26; i++){
		std::wostringstream let;
		let << "Background\\Letters\\" << count << ".png";
		hr = LoadBitmapFromFile(let.str().c_str(), &letters[i]);
		if (FAILED(hr))
		{
			MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load letters array."),
				_T("WIC Error"), MB_OK | MB_ICONERROR);
			return hr;
		}
		let.clear();
		count++;
	}



	//particles

	hr = LoadBitmapFromFile(L"particles//fire.png", &fire);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load fire.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	hr = LoadBitmapFromFile(L"particles//dust.png", &dust);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load fire.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}


	return S_OK; // Success!
}

void Game::DestroyGraphics(void)
{
	// WIC
	SafeRelease(&instruc);
	SafeRelease(&RightSprite);
	SafeRelease(&LeftSprite);
	SafeRelease(&Ball);
	SafeRelease(&Ball2);
	SafeRelease(&fire);
	SafeRelease(&dust);
	SafeRelease(&background1);
	SafeRelease(&background2);
	SafeRelease(&background3);
	SafeRelease(&background4);
	SafeRelease(&background5);
	SafeRelease(&pWICFactory);

	for (int i = 0; i < 10; i++)
		SafeRelease(&Numbers[i]);

	SafeRelease(&pTF);
	SafeRelease(&pDWFactory);
	SafeRelease(&pBrush);
	SafeRelease(&pRT);
	// Release the Direct2D Factory.
	SafeRelease(&pD2DFactory);
}

HRESULT Game::LoadBitmapFromFile(LPCTSTR strFileName, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr;

	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICFormatConverter *pConverter = NULL;


	hr = pWICFactory->CreateDecoderFromFilename(
		strFileName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRT->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pConverter);

	return hr;
}

void Game::Reset(){
	P1Score = 0;
	P2Score = 0;
	p1Power = 0;
	p2Power = 0;
	ballvec = D2D1::SizeF(3, 3);
	ball2vec = D2D1::SizeF(3, 3);

}

void Game::TittleScreen(){

	while (!nStart){
		pRT->BeginDraw();
		pRT->DrawBitmap(tittleScreen, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));

		pTF->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
		pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		std::wstring myStr = L"START";

		D2D1_RECT_F sta = D2D1::RectF(125, pRT->GetSize().height / 2 - 100, 250, pRT->GetSize().height / 2 - 50);

		pRT->DrawText(myStr.c_str(), myStr.length(), pTF, sta, pBrush);

		myStr = L"INSTRUCTIONS";

		D2D1_RECT_F instru = D2D1::RectF(125, pRT->GetSize().height / 2 -20, 250, pRT->GetSize().height / 2 + 10);

		pRT->DrawText(myStr.c_str(), myStr.length(), pTF, instru, pBrush);

		myStr = L"CHARACTER SELECT";

		D2D1_RECT_F sele = D2D1::RectF(125, pRT->GetSize().height / 2 + 40, 250, pRT->GetSize().height / 2 + 90);

		pRT->DrawText(myStr.c_str(), myStr.length(), pTF, sele, pBrush);

		myStr = L"EXIT";

		D2D1_RECT_F exit = D2D1::RectF(125, pRT->GetSize().height / 2 + 120, 250, pRT->GetSize().height / 2 + 170);

		pRT->DrawText(myStr.c_str(), myStr.length(), pTF, exit, pBrush);

		RECT *start = new RECT();
		start->bottom = (LONG)sta.bottom;
		start->left = (LONG)sta.left;
		start->right = (LONG)sta.right;
		start->top = (LONG)sta.top;

		RECT *instr = new RECT();
		instr->bottom = (LONG)instru.bottom;
		instr->left = (LONG)instru.left;
		instr->right = (LONG)instru.right;
		instr->top = (LONG)instru.top;

		RECT *selec = new RECT();
		selec->bottom = (LONG)sele.bottom;
		selec->left = (LONG)sele.left;
		selec->right = (LONG)sele.right;
		selec->top = (LONG)sele.top;

		RECT *exits = new RECT();
		exits->bottom = (LONG)exit.bottom;
		exits->left = (LONG)exit.left;
		exits->right = (LONG)exit.right;
		exits->top = (LONG)exit.top;

		if (PtInRect(start, mouseL)){
			nStart = true;
			mouseL.x = 0;
			mouseL.y = 0;
		}if (PtInRect(instr, mouseL)){
			instructions = true;
			mouseL.x = 0;
			mouseL.y = 0;
		}if (PtInRect(selec, mouseL)){
			charSelect = true;
			mouseL.x = 0;
			mouseL.y = 0;
		}if (PtInRect(exits, mouseL)){
			TerminateThread(hGameThread, 0);
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}


		if (instructions){
			pRT->DrawBitmap(instruc, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));


			pTF->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			std::wstring myStr = L"BACK";

			D2D1_RECT_F backu = D2D1::RectF((pRT->GetSize().width / 2) , (pRT->GetSize().height / 2) + 100, (pRT->GetSize().width / 2)+ 100, (pRT->GetSize().height / 2) + 150);

			pRT->DrawText(myStr.c_str(), myStr.length(), pTF, backu, pBrush);



			RECT *auxi = new RECT();

			auxi->bottom = (LONG)backu.bottom;
			auxi->left = (LONG)backu.left;
			auxi->right = (LONG)backu.right;
			auxi->top = (LONG)backu.top;



			if (PtInRect(auxi, mouseL)){
				instructions = false;
				mouseL.x = 0;
				mouseL.y = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}

		}

		if (charSelect){
			pRT->DrawBitmap(tittleScreen, D2D1::RectF(0, 0, pRT->GetSize().width, pRT->GetSize().height));

			pTF->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			pTF->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			pTF->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			std::wstring myStr = L"Character Select";

			pRT->DrawText(myStr.c_str(), myStr.length(), pTF, D2D1::RectF((pRT->GetSize().width / 2) + 75, (pRT->GetSize().height / 2) / 2 + 50, (pRT->GetSize().width / 2) + 75, (pRT->GetSize().height / 2) / 2), pBrush);

			D2D1_RECT_F one = D2D1::RectF((pRT->GetSize().width / 2), (pRT->GetSize().height / 2) / 2 + 50, (pRT->GetSize().width / 2) + (selectFox->GetSize().width) * 2, (pRT->GetSize().height / 2) / 2 + 50 + (selectFox->GetSize().height) * 2);
			D2D1_RECT_F two = D2D1::RectF((pRT->GetSize().width / 2), (pRT->GetSize().height / 2) / 2 + 150, (pRT->GetSize().width / 2) + (selectFox->GetSize().width) * 2, (pRT->GetSize().height / 2) / 2 + 150 + (selectFox->GetSize().height) * 2);
			D2D1_RECT_F three = D2D1::RectF((pRT->GetSize().width / 2) + 100, (pRT->GetSize().height / 2) / 2 + 50, (pRT->GetSize().width / 2) + 100 + (selectFox->GetSize().width) * 2, (pRT->GetSize().height / 2) / 2 + 50 + (selectFox->GetSize().height) * 2);
			D2D1_RECT_F four = D2D1::RectF((pRT->GetSize().width / 2) + 100, (pRT->GetSize().height / 2) / 2 + 150, (pRT->GetSize().width / 2) + 100 + (selectFox->GetSize().width) * 2, (pRT->GetSize().height / 2) / 2 + 150 + (selectFox->GetSize().height) * 2);

			pRT->DrawBitmap(selectFox, one);
			pRT->DrawBitmap(selectHippo, two);
			pRT->DrawBitmap(selectMonkey, three);
			pRT->DrawBitmap(selectTigger, four);

			RECT *aux1 = new RECT();

			aux1->bottom = (LONG)one.bottom;
			aux1->left = (LONG)one.left;
			aux1->right = (LONG)one.right;
			aux1->top = (LONG)one.top;

			RECT *aux2 = new RECT();

			aux2->bottom = (LONG)two.bottom;
			aux2->left = (LONG)two.left;
			aux2->right = (LONG)two.right;
			aux2->top = (LONG)two.top;

			RECT *aux3 = new RECT();

			aux3->bottom = (LONG)three.bottom;
			aux3->left = (LONG)three.left;
			aux3->right = (LONG)three.right;
			aux3->top = (LONG)three.top;

			RECT *aux4 = new RECT();

			aux4->bottom = (LONG)four.bottom;
			aux4->left = (LONG)four.left;
			aux4->right = (LONG)four.right;
			aux4->top = (LONG)four.top;

			myStr = L"BACK";

			D2D1_RECT_F bac = D2D1::RectF(100, pRT->GetSize().height - 400, 200, pRT->GetSize().height - 150);

			pRT->DrawText(myStr.c_str(), myStr.length(), pTF, bac, pBrush);



			RECT *back = new RECT();

			back->bottom = (LONG)bac.bottom;
			back->left = (LONG)bac.left;
			back->right = (LONG)bac.right;
			back->top = (LONG)bac.top;



			if (PtInRect(back, mouseL)){
				charSelect = false;
				mouseL.x = 0;
				mouseL.y = 0;
			}



			if (PtInRect(aux1, mouseR)){
				pBrush->SetColor(D2DColor(Yellow));
				pRT->DrawRectangle(one, pBrush);
				SetRightPaddle("Using//RFox.png");
			}
			if (PtInRect(aux2, mouseR)){
				pBrush->SetColor(D2DColor(Yellow));
				pRT->DrawRectangle(two, pBrush);
				SetRightPaddle("Using//RHippo.png");
			}
			if (PtInRect(aux3, mouseR)){
				pBrush->SetColor(D2DColor(Yellow));
				pRT->DrawRectangle(three, pBrush);
				SetRightPaddle("Using//RMonkey.png");
			}
			if (PtInRect(aux4, mouseR)){
				pBrush->SetColor(D2DColor(Green));
				pRT->DrawRectangle(four, pBrush);
				SetRightPaddle("Using//RTigger.png");
			}
			if (PtInRect(aux1, mouseL)){
				pBrush->SetColor(D2DColor(Blue));
				pRT->DrawRectangle(one, pBrush);
				SetLeftPaddle("Using//LFox.png");
			}
			if (PtInRect(aux2, mouseL)){
				pBrush->SetColor(D2DColor(Blue));
				pRT->DrawRectangle(two, pBrush);
				SetLeftPaddle("Using//LHippo.png");
			}
			if (PtInRect(aux3, mouseL)){
				pBrush->SetColor(D2DColor(Blue));
				pRT->DrawRectangle(three, pBrush);
				SetLeftPaddle("Using//LMonkey.png");
			}
			if (PtInRect(aux4, mouseL)){
				pBrush->SetColor(D2DColor(Blue));
				pRT->DrawRectangle(four, pBrush);
				SetLeftPaddle("Using//LTigger.png");
			}
			pBrush->SetColor(D2DColor(Black));
		}

		HRESULT hr = pRT->EndDraw();
		if (hr == D2DERR_RECREATE_TARGET)
		{
			//TODO: Destroy Direct2D.
			DestroyGraphics();
			//TODO: Recreate Direct2D.
			CreateGraphics(hWnd);
		}
	}
}


HRESULT Game::SetLeftPaddle(string left){
	HRESULT hr;
	leftName = left;


	std::wstring stemp = std::wstring(left.begin(), left.end());
	LPCWSTR lp = stemp.c_str();

	hr = LoadBitmapFromFile(lp, &LeftSprite);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load Hippo.png."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}

	return S_OK;
}
HRESULT Game::SetRightPaddle(string right){
	HRESULT hr;
	rightName = right;

	std::wstring stemp = std::wstring(right.begin(), right.end());
	LPCWSTR rp = stemp.c_str();


	hr = LoadBitmapFromFile(rp, &RightSprite);
	if (FAILED(hr))
	{
		MessageBox(HWND_DESKTOP, _T("ERROR: Failed to Load right sprite."),
			_T("WIC Error"), MB_OK | MB_ICONERROR);
		return hr;
	}
	return S_OK;
}

int Game::GetPlayers()const{
	if (!AI1 && !AI2)
		return 2;
	if (!AI1)
		return 1;
	else
		return 0;
}
void Game::SetPlayers(int players){
	if (players == 2){
		AI1 = false;
		AI2 = false;
	}
	else if (players == 1){
		AI2 = true;
		AI1 = false;
	}
	else if (players == 0){
		AI2 = true;
		AI1 = true;
	}
}

D2D1_SIZE_F Game::Normalize(D2D1_SIZE_F v1){

	float square = v1.width*v1.width + v1.height*v1.height;
	float temp = sqrtf(square);
	if (temp != 0){
		v1.width = v1.width / temp;
		v1.height = v1.height / temp;
	}
	else{
		v1.width = v1.height = 0;
	}

	return v1;
}