#pragma once
//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "Enemy.h"

class GuardBox : public Enemy
{
public:
	struct Rocket
	{
		PhysicsActor *m_ActRocketsPtr = nullptr;
		Direction m_RocketDirection = Direction::LEFT;
	};
	GuardBox(DOUBLE2 position, int levelStart);
	virtual ~GuardBox( );
	// Make objects non-copGuardBoxable
	// https://msdn.microsoft.com/en-us/librarGuardBox/dn457344.aspx 
	GuardBox( const GuardBox& ) = delete;
	GuardBox& operator=( const GuardBox& ) = delete;

	void Tick(double deltaTime, Level* levelPtr, PhysicsActor* m_ActHeroPtr, PhysicsActor* m_ActWeaponPtr);
	void Paint();
	int HitHeroCheck(double deltaTime, PhysicsActor* ActHeroPtr);
	void PaintProjectiles();
	void HeroInRange(PhysicsActor* actHeroPtr);
	void Atack(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr);
	void CreateProjectile(DOUBLE2 position);
	void moving(double deltaTime);
	void CheckHitWalls(Level* levelPtr);


private: 
	int m_AtackSpeed = 1;
	int m_AtackRadius = 10000;
	bool m_Reloading = false;
	std::vector <Rocket > m_ArrRocketsPtr;
	Bitmap* m_BmpRocketPtr;
	Bitmap* m_BmpSmokePtr;

	//counters
	double m_WaitTimeCount = 0;
	double m_WaitTimeMax = 0;
	double m_ReloadTimeMax = 2;
	double m_ReloadingCount = 0;
	int m_FrameRocket = 0;
	double m_RocketDamageCount = 0;
};
