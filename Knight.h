#pragma once
//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "Enemy.h"

class Knight : public Enemy
{
public:
	Knight(DOUBLE2 position, int levelStart);
	virtual ~Knight( );
	// Make objects non-copKnightable
	// https://msdn.microsoft.com/en-us/librarKnight/dn457344.aspx 
	Knight( const Knight& ) = delete;
	Knight& operator=( const Knight& ) = delete;

	void Tick(double deltaTime, Level* levelPtr, PhysicsActor* m_ActHeroPtr, PhysicsActor* m_ActWeaponPtr);
	void Paint();
	int HitHeroCheck(double deltaTime, PhysicsActor* m_ActHeroPtr);
	void Move(double deltaTime, Level* levelPtr);
	void Atack(double deltaTime, Level* levelPtr, PhysicsActor* m_ActHeroPtr);
	void ChangeToAtacking(PhysicsActor* m_ActHeroPtr);

	//weapon functions
	void WeaponMovement();
	void RotateWeapon();
	void ResetWeapon();
	void Resetknockback(double deltaTime, Level* levelPtr);

private: 
	int m_AtackSpeed = 1;
	int m_AtackRadius = 200;
	DOUBLE2 m_EnemySpeed = { 150, 0 };

	double m_MoveTimeMax;

	//weapon
	int m_Angle = 140;
	int m_Radius = 75;
	DOUBLE2 m_WeaponOffset = { (cos(m_Angle*3.14 / 180)* m_Radius),-(sin(m_Angle*3.14 / 180) * m_Radius) };

	//counters
	double m_KnockBackCounter = 0;
	double m_TimeOutOfAtack = 0;
	double m_FrameCount = 0;

};
