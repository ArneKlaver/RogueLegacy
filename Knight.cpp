//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Knight.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Knight::Knight(DOUBLE2 position, int levelStart)
	:Enemy( position ,  levelStart)
{
	m_ActEnemyPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActEnemyPtr->AddBoxFixture(50, 90, 0, 1);
	m_ActEnemyPtr->SetFixedRotation(true);
	m_ActWeaponPtr = new PhysicsActor({ 350,300 }, 0, BodyType::KINEMATIC);
	m_ActWeaponPtr->AddBoxFixture(30, 165, 0, 1);
	m_ActWeaponPtr->SetFixedRotation(true);
	m_ActWeaponPtr->SetSensor(true);
	m_ActWeaponPtr->SetActive(false);

	m_BmpEnemyPtr = new Bitmap(String("Resources/Enemy_Knight.png"));
	m_FrameX = 8;// number of images horizontal
	m_FrameY = 8;// number of images vertical
	m_EnemyDamage = 20;
	m_WaitTimeMax = 1;
}

Knight::~Knight()
{
}

void Knight::Tick(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr, PhysicsActor* actWeaponPtr)
{
	if (m_IsActive)
	{
		HitHeroCheck(deltaTime, actHeroPtr);
		if (m_ActionState != ActionState::ATACKING)
		{
			ChangeToAtacking(actHeroPtr);
		}

		WeaponMovement();
		Atacked(deltaTime, actWeaponPtr, levelPtr);
		switch (m_ActionState)
		{
		case Enemy::ActionState::WAITING:
			Waiting(deltaTime, levelPtr);
			m_TimeOutOfAtack += deltaTime;
			break;
		case Enemy::ActionState::MOVING:
			Move(deltaTime, levelPtr);
			m_TimeOutOfAtack += deltaTime;
			break;
		case Enemy::ActionState::ATACKING:
			Atack(deltaTime, levelPtr, actWeaponPtr);
			break;

		default:
			break;
		}
		EnemyDirection(actHeroPtr);
		m_FrameTimeCounter += deltaTime * m_NrFramesPerSec;

		//reset knockback
		Resetknockback(deltaTime, levelPtr);
	}
}

void Knight::Paint()
{
	if (m_IsActive)
	{
		PosFlipBitmap();
		switch (m_ActionState)
		{
		case Enemy::ActionState::WAITING:
			DrawHero(0, 16);
			break;
		case Enemy::ActionState::MOVING:
			DrawHero(17, 36);
			break;
		case Enemy::ActionState::ATACKING:
			DrawHero(37, 52);
			break;
		default:
			break;
		}
	}

	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}
void Knight::Move(double deltaTime, Level* levelPtr)
{
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime > m_MoveTimeMax)
	{
		m_MoveTimeMax = rand() % 1 + 1;
		m_ElapsedTime = 0;
		m_EnemySpeed.x = -m_EnemySpeed.x;
		m_EnemySpeed.y = 100;
		m_ActionState = ActionState::WAITING;
		m_FrameTimeCounter = 0;
		if (m_EnemySpeed.x < 0)
		{
			m_EnemyDirection = Direction::LEFT;
			m_Angle = 140;
			
		}
		else
		{
			m_EnemyDirection = Direction::RIGHT;
			m_Angle = 50;
		}
	}
	if (m_Knockback == false)
	{
		m_ActEnemyPtr->SetLinearVelocity(m_EnemySpeed);
	}
}

void Knight::Atack(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr)
{
	if (m_Knockback == false)
	{
		m_ActEnemyPtr->SetLinearVelocity({ 0,0 });
	}
	m_ActWeaponPtr->SetActive(false);
	m_NrFramesPerSec = 12;
	m_FrameCount += deltaTime*m_NrFramesPerSec;
	if (m_FrameCount >5 && m_FrameCount < 6.2)
	{
		m_ActWeaponPtr->SetActive(true);
		m_Angle -= int(m_EnemyDirection) * 10;
		RotateWeapon();
	}
	if (m_FrameCount > 12)
	{
		//reset weapon
		m_ActWeaponPtr->SetActive(false);
		ResetWeapon();
		//change to moving 
		m_ActionState = ActionState::MOVING;
		//reset FrameCount
		m_FrameCount = 0;
	}
}

void Knight::ChangeToAtacking(PhysicsActor* actHeroPtr)
{
	DOUBLE2 diff = m_ActEnemyPtr->GetPosition() - actHeroPtr->GetPosition();
	diff = DOUBLE2{ abs(diff.x) , abs(diff.y) };
	double length = sqrt(diff.x*diff.x + diff.y*diff.y);
	if (length < m_AtackRadius && m_TimeOutOfAtack > m_AtackSpeed)
	{
		m_TimeOutOfAtack = 0;
		m_ActionState = ActionState::ATACKING;
		m_FrameTimeCounter = 0;
		double diff = m_ActEnemyPtr->GetPosition().x - actHeroPtr->GetPosition().x;
		if (diff > 0)
		{
			m_EnemyDirection = Direction::LEFT;
			m_Angle = 140;
		}
		else
		{
			m_EnemyDirection = Direction::RIGHT;
			m_Angle = 50;
		}
	}
}

void Knight::WeaponMovement()
{
	m_ActWeaponPtr->SetPosition(m_ActEnemyPtr->GetPosition() + m_WeaponOffset);
}

void Knight::RotateWeapon()
{
	m_WeaponOffset.x = (cos(m_Angle* 3.14 / 180) * m_Radius);
	m_WeaponOffset.y = -(sin(m_Angle* 3.14 / 180) * m_Radius);
	m_ActWeaponPtr->SetAngle(-m_Angle*3.14 / 180 + 1.57);
}
void Knight::ResetWeapon()
{
	switch (m_EnemyDirection)
	{
	case Enemy::Direction::LEFT:
		m_Angle = 140;
		break;
	case Enemy::Direction::RIGHT:
		m_Angle = 50;
		break;
	default:
		break;
	}
	m_ActWeaponPtr->SetAngle(m_Angle*3.14 / 180);
	m_WeaponOffset = DOUBLE2{ (cos(m_Angle* 3.14 / 180) * m_Radius) , -sin(m_Angle* 3.14 / 180) * m_Radius };
}

void Knight::Resetknockback(double deltaTime, Level* levelPtr)
{
	if (m_Knockback)
	{
		m_KnockBackCounter += deltaTime * 10;
	}
	if (levelPtr->IsOnGround(m_ActEnemyPtr) && m_KnockBackCounter > 0.5)
	{
		m_KnockBackCounter = 0;
		m_Knockback = false;
	}
}

int Knight::HitHeroCheck(double deltaTime, PhysicsActor* ActHeroPtr)
{
	m_FrameCountHeroEnemy += deltaTime;
	int damage = 0;
	if (m_FrameCountHeroEnemy > 0.5)
	{
		if (m_ActEnemyPtr->IsOverlapping(ActHeroPtr) && m_ActEnemyPtr->IsActive() == true)
		{
			m_FrameCountHeroEnemy = 0;
			damage += 10;
			Hit();
		}
	}

	if (m_HeroDamaged == true)
	{
		m_FrameCountHeroCheck += deltaTime*m_NrFramesPerSec;
		if (m_FrameCountHeroCheck > 11)
		{
			m_FrameCountHeroCheck = 0;
			m_HeroDamaged = false;
		}
	}
	if (m_ActWeaponPtr->IsOverlapping(ActHeroPtr) && m_HeroDamaged == false && m_ActWeaponPtr->IsActive() == true)
	{
		m_HeroDamaged = true;
		return m_EnemyDamage + damage;
	}

	return 0 + damage;
}