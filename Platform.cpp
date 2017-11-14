//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Platform.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Platform::Platform( DOUBLE2 posRef)
{
	m_BmpPtr = new Bitmap(String("Resources/Platform.png"));
	m_ActPtr = new PhysicsActor(posRef, 0, BodyType::STATIC);

	m_ActPtr->AddBoxFixture(m_BmpPtr->GetWidth(), m_BmpPtr->GetHeight(), 0, 0);
	m_ActPtr->AddContactListener(this);
}

Platform::~Platform()
{
	delete m_BmpPtr;
	m_BmpPtr = nullptr;

	delete m_ActPtr;
	m_ActPtr = nullptr;
}

void Platform::Paint()
{
	GAME_ENGINE->DrawBitmap(m_BmpPtr, m_ActPtr->GetPosition() - DOUBLE2{m_BmpPtr->GetWidth() / 2.0 , m_BmpPtr->GetHeight() / 2.0 });
}
void Platform::Tick(PhysicsActor* actOtherPtr)
{
	if (!m_ActPtr->IsOverlapping(actOtherPtr))
	{
		m_IsGoingThru = false;
	}
}
bool Platform::IsOnGround(PhysicsActor* actOtherPtr)
{
	if (m_IsGoingThru == true)
	{
		return false;
	}
	double temp1 = actOtherPtr->GetPosition().y + 40;
	double temp2 = m_ActPtr->GetPosition().y - 10;
	if (m_ActPtr->IsOverlapping(actOtherPtr) && m_IsActive )
	{
		return true;
	}
	return false;

}


void Platform::PreSolve(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr, bool & enableContactRef)
{
	//up
	if (actOtherPtr->GetLinearVelocity().y < 0 )
	{
		enableContactRef = false;
	}
	//down
	m_IsActive = true;
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_SPACE) && GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN) )
	{
		m_IsActive = false;
		m_IsGoingThru = true;
		enableContactRef = false;
	}
	if (m_IsGoingThru == true)
	{
		enableContactRef = false;
	}
}

PhysicsActor* Platform::GetActor()
{
	return m_ActPtr;
}