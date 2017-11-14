//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "FirePlace.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

FirePlace::FirePlace(DOUBLE2 position) : m_Position(position)
{
	m_BmpFirePlacePtr = new Bitmap(String("Resources/FirePlace.png"));
}

FirePlace::~FirePlace()
{
	delete m_BmpFirePlacePtr;
	m_BmpFirePlacePtr = nullptr;
}

void FirePlace::Paint()
{
	GAME_ENGINE->SetWorldMatrix(GetViewMatrix(m_Position));
	DrawFireplace(0, 4);
	
	//reset view
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}
void FirePlace::Tick(double deltaTime)
{
	m_FrameNr += deltaTime * 8;
}
MATRIX3X2 FirePlace::GetViewMatrix(DOUBLE2 position)
{
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(position);

	return matCamera;
}

void FirePlace::DrawFireplace(int frameMin, int frameMax)
{
	int frameX = 4;// number of images horizontal
	int frameY = 1;// number of images vertical

	int frameNr = (int)m_FrameNr;
	frameNr = (frameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpFirePlacePtr->GetWidth();
	double height = m_BmpFirePlacePtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpFirePlacePtr,
	{ width / frameX * (frameNr % frameX), height / frameY * (frameNr / frameX) ,  width / frameX + width / frameX * (frameNr % frameX) ,  (height / frameY) + height / frameY * (frameNr / frameX) });
}

