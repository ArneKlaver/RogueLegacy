#pragma once
//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "Enemy.h"

class IceWizard : public Enemy 
{
public:
	IceWizard(DOUBLE2 position, int levelStart);
	virtual ~IceWizard( );
	// Make objects non-copIceWizardable
	// https://msdn.microsoft.com/en-us/librarIceWizard/dn457344.aspx 
	IceWizard( const IceWizard& ) = delete;
	IceWizard& operator=( const IceWizard& ) = delete;


	void Tick(double deltaTime, Level* levelPtr, PhysicsActor* m_ActHeroPtr, PhysicsActor* m_ActWeaponPtr);
	void Paint();
	void PaintProjectiles();
	void PaintAtacking();
	void PaintChargeCrystal();

	void Move(double deltaTime, Level* levelPtr , PhysicsActor* actHeroPtr);
	void Atack(double deltaTime, Level* levelPtr, PhysicsActor* m_ActHeroPtr);
	void HeroInRange(PhysicsActor* m_ActHeroPtr);
	void CheckHitHero(double deltaTime , PhysicsActor* ActHeroPtr);
	int HitHeroCheck(double deltaTime, PhysicsActor* ActHeroPtr);

	void Resetknockback(double deltaTime, Level* levelPtr);
	void Projectiles(Level* levelPtr);
	void CheckHitWalls(Level* levelPtr);
	void CreateProjectile(DOUBLE2 spawnPos);
	void DrawBreakeIce(PhysicsActor* IceCrystal);

private: 
	int m_AtackSpeed = 1;
	int m_AtackRadius = 200;
	DOUBLE2 m_EnemySpeed = { 150, 0 };
	double m_MoveTimeMax;
	bool m_Charging = false;
	bool m_Crystals = false ;
	std::vector <PhysicsActor *> m_IceProjectiles;
	Bitmap* m_BmpIceCrystalPtr;
	Bitmap* m_BmpChargeCrystalPtr;
	Bitmap* m_BmpIceCrystalBrokenPtr;
	//counters
	double m_KnockBackCounter = 0;
	double m_TimeMoving = 0;
	double m_FrameCount = 0;
	double m_ChargeTime = 0;
	double m_ChargeMaxTime = 2;
	int m_FrameNrChargingCrystal = 0;
	double m_FrameNrCharingCrystal = 0;
};
