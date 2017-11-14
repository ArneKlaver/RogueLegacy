//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "CandleStick.h"
#include "PickUpManager.h"
#include "LevelManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

CandleStick::CandleStick(DOUBLE2 position , int levelNumber) : m_Position(position) , m_LevelNumber(levelNumber)
{
	m_BmpCandleStickPtr = new Bitmap(String("Resources/CandleStick.png"));
	m_ActCandleStickPtr = new PhysicsActor(m_Position + DOUBLE2{25 - (double)m_BmpCandleStickPtr->GetWidth() / 2,  - (double)m_BmpCandleStickPtr->GetHeight()/2 }, 0, BodyType::STATIC);
	m_ActCandleStickPtr->AddBoxFixture(25, 90);
	m_ActCandleStickPtr->SetSensor(true);
}

CandleStick::~CandleStick()
{
	delete m_BmpCandleStickPtr;
	m_BmpCandleStickPtr = nullptr;
	delete m_ActCandleStickPtr;
	m_ActCandleStickPtr = nullptr;
}

void CandleStick::Paint()
{
	GAME_ENGINE->SetWorldMatrix(GetViewMatrix(m_Position));
	GAME_ENGINE->DrawBitmap(m_BmpCandleStickPtr);
	//reset view
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}
void CandleStick::Tick(double deltaTime , PhysicsActor* actWeaponHeroPtr )
{	
	if (m_ActCandleStickPtr->IsOverlapping(actWeaponHeroPtr) && actWeaponHeroPtr->IsActive())
	{
		m_IsDestroyed = true;
	}
}
MATRIX3X2 CandleStick::GetViewMatrix(DOUBLE2 position)
{
	position -= DOUBLE2{ (double)m_BmpCandleStickPtr->GetWidth()/2, (double)m_BmpCandleStickPtr->GetHeight() };
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(position);

	return matCamera;
}
void CandleStick::DrawBitmap(int frameMin, int frameMax)
{
	int frameX = 1;// number of images horizontal
	int frameY = 1;// number of images vertical

	int frameNr = (int)m_FrameNr;
	frameNr = (frameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpCandleStickPtr->GetWidth();
	double height = m_BmpCandleStickPtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpCandleStickPtr,
	{ width / frameX * (frameNr % frameX), height / frameY * (frameNr / frameX) ,  width / frameX + width / frameX * (frameNr % frameX) ,  (height / frameY) + height / frameY * (frameNr / frameX) });
}

bool CandleStick::GetDestroyed()
{
	return m_IsDestroyed;
}

DOUBLE2 CandleStick::GetPosition()
{
	return m_Position;
}

PhysicsActor* CandleStick::GetActor()
{
	return m_ActCandleStickPtr;
}
