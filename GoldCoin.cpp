//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "GoldCoin.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

GoldCoin::GoldCoin(int currentLvlStart, DOUBLE2 position ): m_Position(position) , m_LevelNumber(currentLvlStart)
{
	m_ActCoinPtr = new PhysicsActor(position + DOUBLE2{10 , 20 }, 0, BodyType::STATIC);
	m_ActCoinPtr->AddCircleFixture(10);
	m_ActCoinPtr->SetSensor(true);
	m_BmpCoinPtr = new Bitmap(String("Resources/GoldCoin.png"));
}

GoldCoin::~GoldCoin()
{
	delete m_BmpCoinPtr;
	m_BmpCoinPtr = nullptr;
	delete m_ActCoinPtr;
	m_ActCoinPtr = nullptr;
}

void GoldCoin::Tick(double deltaTime , PhysicsActor* actHeroPtr , int currentLvl)
{
	m_FrameNr += deltaTime * 8;
	if (m_ActCoinPtr->IsOverlapping(actHeroPtr))
	{
		m_IsPickedUp = true;
	}
	if (m_LevelNumber != currentLvl )
	{
		m_IsDeleted = true;
	}
}
void GoldCoin::Paint()
{
	GAME_ENGINE->SetWorldMatrix(GetViewMatrix(m_Position));
	DrawBitmap(0, 6);

	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

bool GoldCoin::GetPickedUp()
{
	return m_IsPickedUp;
}

MATRIX3X2 GoldCoin::GetViewMatrix(DOUBLE2 position)
{
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(position);

	return matCamera;
}

void GoldCoin::DrawBitmap(int frameMin, int frameMax)
{
	int frameX = 6;// number of images horizontal
	int frameY = 1;// number of images vertical

	int frameNr = (int)m_FrameNr;
	frameNr = (frameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpCoinPtr->GetWidth();
	double height = m_BmpCoinPtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpCoinPtr,
	{ width / frameX * (frameNr % frameX), height / frameY * (frameNr / frameX) ,  width / frameX + width / frameX * (frameNr % frameX) ,  (height / frameY) + height / frameY * (frameNr / frameX) });
}

bool GoldCoin::GetDeleted()
{
	return m_IsDeleted;
}