#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "ContactListener.h"

class Platform : public ContactListener
{
public:
	Platform( DOUBLE2 posRef);
	virtual ~Platform();
	// Make objects non-copyable
	// https://msdn.microsoft.com/en-us/library/dn457344.aspx 
	Platform(const Platform&) = delete;
	Platform& operator=(const Platform&) = delete;

	void Tick(PhysicsActor* actOtherPtr);
	void Paint();
	bool IsOnGround(PhysicsActor* actOtherPtr);
	void PreSolve(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr, bool & enableContactRef);
	PhysicsActor* GetActor();
private:
	PhysicsActor* m_ActPtr = nullptr;
	Bitmap* m_BmpPtr = nullptr;
	bool m_IsActive = true;
	bool m_IsGoingThru = false;

};