#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "Level.h"
#include "Camera.h"
#include "EnemyManager.h"

class Hero 
{
public:
	enum class ActionState
	{
		WAITING,
		MOVING,
		ATACKING,
		JUMPING,
		DEAD
	};
	enum class Direction
	{
		LEFT = -1 ,
		RIGHT = 1
	};

	Hero( const DOUBLE2 & centerRef );
	virtual ~Hero( );
	// Make objects non-copHeroable
	// https://msdn.microsoft.com/en-us/librarHero/dn457344.aspx 
	Hero( const Hero& ) = delete;
	Hero& operator=( const Hero& ) = delete;

	void Tick(double deltaTime, Level* levelPtr , EnemyManager* EnemyManager);
	void Paint();
	void Waiting(Level* levelPtr);
	void Moving(Level* levelPtr);
	void Atacking(Level* levelPtr, double deltaTime);
	void MoveHero(Level* levelPtr);
	void Jumping(Level* levelPtr);
	PhysicsActor* GetActor();
	PhysicsActor* GetWeaponActor();
	RECT2 GetRect();
	DOUBLE2 GetPosition();
	void DrawHero(int frameMin, int frameMax);
	void WeaponMovement();
	void RotateWeapon();
	void ResetWeapon();
	void Dead();
	void Atacked(double deltaTime, EnemyManager* EnemyManager);
	int GetHealth();
	int GetMana();
	void PosFlipBitmap();
	void Resetknockback(double deltaTime , Level* levelPtr);
	bool GetEndGame();
private: 
	Direction m_HeroDirection = Direction::LEFT;
	int m_Health = 100;
	int m_Mana = 100;
	const int m_HeightActor = 97;
	const int m_WidthActor = 36;
	const int m_JumpStacksMax = 1;
	int m_JumpStacks = 0;
	PhysicsActor* m_ActHeroPtr = nullptr;

	ActionState m_ActionState = ActionState::MOVING;
	 double m_HorSpeed = 400.0;
	 double m_JumpSpeed = 700.0;
	Bitmap* m_BmpHeroPtr = nullptr;

	double m_FrameHero = 0;
	DOUBLE2 m_HeroPostition;
	Level* m_LevelPtr;

	int m_NrFramesPerSec = 10;	
	double m_CountJumpingTime;
	//avatar

	//weapon
	PhysicsActor* m_ActWeaponPtr = nullptr;
	int m_Angle = 50;
	int m_Radius = 70;
	DOUBLE2 m_WeaponOffset = { cos(m_Angle*3.14 / 180 )* m_Radius, -(sin(m_Angle*3.14 / 180) * m_Radius) };

	//damage
	bool m_IsDamaged = false;
	bool m_IsAlive = true;
	bool m_Knockback = false;

	//Counters
	double m_KnockBackCounter = 0;
	double m_FrameCount = 0;


	bool m_EndGame = false;
};
