//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Enemy.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Enemy::Enemy(DOUBLE2 position , int levelStart): m_LevelStart(levelStart)
{
	
}

Enemy::~Enemy()
{
	delete m_BmpEnemyPtr;
	m_BmpEnemyPtr = nullptr;
	delete m_ActEnemyPtr;
	m_ActEnemyPtr = nullptr;
	delete m_ActWeaponPtr;
	m_ActWeaponPtr = nullptr;
}

void Enemy::DrawHero(int frameMin, int frameMax )
{
	m_FrameNr = (int)m_FrameTimeCounter;
	m_FrameNr = (m_FrameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpEnemyPtr->GetWidth();
	double height = m_BmpEnemyPtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr,
	{ width / m_FrameX * (m_FrameNr % m_FrameX), height / m_FrameY * (m_FrameNr / m_FrameX) ,  width / m_FrameX + width / m_FrameX * (m_FrameNr % m_FrameX) ,  (height / m_FrameY) + height / m_FrameY * (m_FrameNr / m_FrameX) });
}

void Enemy::Waiting(double deltaTime , Level* levelPtr)
{
	m_ActEnemyPtr->SetLinearVelocity({ 0,0 });
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime > m_WaitTimeMax)
	{
		m_ActionState = ActionState::MOVING;
		m_ElapsedTime = 0;
		m_FrameNr = 0;
	}
}

void Enemy::Atacked(double deltaTime , PhysicsActor* actWeaponPtr , Level* levelPtr)
{
	if (m_IsDamaged == true)
	{
		m_FrameCounterAtacked += deltaTime*m_NrFramesPerSec;
		if (m_FrameCounterAtacked > 11)
		{
			m_FrameCounterAtacked = 0;
			m_IsDamaged = false;
		}
	}
	if (m_ActEnemyPtr->IsOverlapping(actWeaponPtr) && actWeaponPtr->IsActive() && m_IsDamaged == false)
	{
		Hit();
		m_Health -= m_HeroDamage;
		m_IsDamaged = true;
		if (m_Health <= 0)
		{
			m_IsAlive = false;
		}
	}
}

bool Enemy::GetAlive()
{
	return m_IsAlive;
}

void Enemy::PosFlipBitmap()
{
	if (m_EnemyDirection == Direction::LEFT)
	{
		DOUBLE2 positon = m_ActEnemyPtr->GetPosition();

		MATRIX3X2 matPivot, matTranslate;
		MATRIX3X2 matFlip, matWorld;

		matTranslate.SetAsTranslate(positon);
		matFlip.SetAsScale(1, 1);

		//middle to center

		double frameWidth = m_BmpEnemyPtr->GetWidth() / 8.0;
		double frameHeight = m_BmpEnemyPtr->GetHeight() / 8.0;

		matPivot.SetAsTranslate(-(frameWidth / 1.5), -(frameHeight / 1.3));

		matWorld = matPivot * matFlip * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorld);
	}
	else
	{
		DOUBLE2 positon = m_ActEnemyPtr->GetPosition();

		MATRIX3X2 matPivot, matTranslate;
		MATRIX3X2 matFlip, matWorld;

		matTranslate.SetAsTranslate(positon);
		matFlip.SetAsScale(-1, 1);

		//middle to center

		double frameWidth = m_BmpEnemyPtr->GetWidth() / 8.0;
		double frameHeight = m_BmpEnemyPtr->GetHeight() / 8.0;

		matPivot.SetAsTranslate(-(frameWidth / 1.5), -(frameHeight / 1.3));

		matWorld = matPivot * matFlip * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorld);
	}
}

void Enemy::EnemyDirection(PhysicsActor* actHeroPtr)
{
	double diff = m_ActEnemyPtr->GetPosition().x - actHeroPtr->GetPosition().x;
	if (diff > 0)
	{
		m_EnemyDirection = Direction::LEFT;
	}
	else
	{
		m_EnemyDirection = Direction::RIGHT;
	}
}

void Enemy::Hit()
{
	m_Knockback = true;
	m_ActEnemyPtr->ApplyLinearImpulse({ -10000.0 * (int)m_EnemyDirection , -10000.0 });
}

void Enemy::m_DeactivateEnemy(bool active)
{
	m_IsActive = active;
	m_ActEnemyPtr->SetActive(active);
}

int Enemy::GetLevelStart()
{
	return m_LevelStart;
}

MATRIX3X2  Enemy::GetViewMatrix(DOUBLE2 position, double angle)
{
	MATRIX3X2 matTranslate;
	MATRIX3X2 matRotate;
	MATRIX3X2 matCamera;

	matTranslate.SetAsTranslate(position);
	matRotate.SetAsRotate(angle);
	matCamera = matRotate * matTranslate;
	return matCamera;
}

