#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include"Level.h"

class Enemy 
{
public:
	enum class ActionState
	{
		WAITING,
		MOVING,
		ATACKING
	};
	enum class Direction
	{
		LEFT = -1,
		RIGHT = 1
	};
	Enemy(DOUBLE2 position , int levelStart);
	virtual ~Enemy( );
	// Make objects non-copEnemyable
	// https://msdn.microsoft.com/en-us/librarEnemy/dn457344.aspx 
	Enemy( const Enemy& ) = delete;
	Enemy& operator=( const Enemy& ) = delete;

	virtual void Tick(double deltaTime , Level* levelPtr , PhysicsActor* m_ActHeroPtr , PhysicsActor* m_ActWeaponPtr) = 0;
	virtual void Paint() = 0;
	virtual int HitHeroCheck(double deltaTime, PhysicsActor* m_ActHeroPtr) = 0;
	MATRIX3X2 GetViewMatrix(DOUBLE2 position, double angle = 0);
	void Move(double deltaTime , Level* levelPtr);
	void DrawHero(int frameMin, int frameMax);
	void Atack( double deltaTime , Level* levelPtr , PhysicsActor* ActHeroPtr);
	void Waiting(double deltaTime , Level* levelPtr);
	void Hit();
	void PosFlipBitmap();
	
	void Atacked(double deltaTime, PhysicsActor* m_ActWeaponPtr, Level* levelPtr);
	bool m_Knockback = false;
	bool GetAlive();
	void EnemyDirection(PhysicsActor* actHeroPtr);
	void m_DeactivateEnemy(bool active);
	int GetLevelStart();

private: 
	int m_LevelStart = 0;
	
	bool m_IsDamaged = false;
	bool m_IsAlive = true;


	//counters
	double m_FrameCounterAtacked = 0;


protected:
	Direction m_EnemyDirection = Direction::LEFT;
	ActionState m_ActionState = ActionState::WAITING;
	Bitmap* m_BmpEnemyPtr = nullptr;
	PhysicsActor* m_ActEnemyPtr = nullptr;
	PhysicsActor* m_ActWeaponPtr = nullptr;

	bool m_IsActive = true;
	double m_ElapsedTime;
	double m_FrameTimeCounter = 0;
	int m_NrFramesPerSec = 10;
	int m_EnemyDamage = 20;
	int m_Health = 100;
	int m_HeroDamage = 50;
	bool m_HeroDamaged = false;

	//frame
	int m_WaitTimeMax = 0;
	int m_FrameX = 8;// number of images horizontal
	int m_FrameY = 8;// number of images vertical
	int m_FrameNr = 0;

	//counter
	double m_FrameCountHeroEnemy = 0;
	double m_FrameCountHeroCheck = 0;

};
