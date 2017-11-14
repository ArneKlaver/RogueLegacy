//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "GuardBox.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

GuardBox::GuardBox(DOUBLE2 position, int levelStart)
	:Enemy(position, levelStart)
{
	m_ActEnemyPtr = new PhysicsActor(position, 0, BodyType::STATIC);
	m_ActEnemyPtr->AddBoxFixture(80, 60, 0, 1);
	m_ActEnemyPtr->SetFixedRotation(true);
	m_ActEnemyPtr->SetGravityScale(0);

	m_BmpRocketPtr = new Bitmap(String("Resources/Rocket.png"));
	m_BmpEnemyPtr = new Bitmap(String("Resources/GuardBox.png"));

	m_FrameX = 1;// number of images horizontal
	m_FrameY = 9;// number of images vertical
	m_EnemyDamage = 20;
	m_WaitTimeMax = 2;
}

GuardBox::~GuardBox()
{
	delete m_BmpRocketPtr;
	m_BmpRocketPtr = nullptr;
	delete m_BmpSmokePtr;
	m_BmpSmokePtr = nullptr;
	for (int i = 0; i < m_ArrRocketsPtr.size() ; i++)
	{
		delete m_ArrRocketsPtr[i].m_ActRocketsPtr;
		m_ArrRocketsPtr[i].m_ActRocketsPtr = nullptr;
	}
}
void GuardBox::Tick(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr, PhysicsActor* actWeaponPtr)
{
	if (m_IsActive)
	{
		//stuurt damage naar Hero if hit
		HitHeroCheck(deltaTime, actHeroPtr);
		//
		if (m_ActionState != ActionState::ATACKING)
		{
			HeroInRange(actHeroPtr);
		}
		Atacked(deltaTime, actWeaponPtr, levelPtr);
		switch (m_ActionState)
		{
		case Enemy::ActionState::WAITING:
			Waiting(deltaTime, levelPtr);
			break;
		case Enemy::ActionState::MOVING:
			m_Reloading = true;
			moving(deltaTime);
			break;
		case Enemy::ActionState::ATACKING:
			Atack(deltaTime, levelPtr, actWeaponPtr);
			m_Reloading = false;
			break;
		default:
			break;
		}
	}
	//stop met animatie als reloading true is
	if (!m_Reloading)
	{
		m_FrameTimeCounter += deltaTime * m_NrFramesPerSec;
	}
	CheckHitWalls(levelPtr);
}

void GuardBox::moving(double deltaTime)
{
	m_WaitTimeCount += deltaTime;
	if (m_WaitTimeCount > m_WaitTimeMax)
	{
		m_ActionState = ActionState::ATACKING;
	}
}
void GuardBox::Atack(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr)
{
	m_ActEnemyPtr->SetLinearVelocity({ 0,0 });
	if (m_Reloading)
	{
		CreateProjectile(m_ActEnemyPtr->GetPosition() + DOUBLE2{ 0,0 });
		m_Reloading = false;
	}

	if (m_FrameNr == 7)
	{
		m_WaitTimeCount = 0;
		m_ActionState = ActionState::MOVING;
		m_FrameTimeCounter++; //volgende frame
		m_FrameNr = 0;
	}
}
void GuardBox::Paint()
{
	PaintProjectiles();
	if (m_IsActive)
	{
		PosFlipBitmap();
		switch (m_ActionState)
		{
		case Enemy::ActionState::MOVING:
			DrawHero(0, 8);
			break;
		case Enemy::ActionState::ATACKING:
			DrawHero(0, 8);
			break;
		default: 
			break;
		}
	}
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

int GuardBox::HitHeroCheck(double deltaTime, PhysicsActor* ActHeroPtr)
{
	m_FrameCountHeroEnemy += deltaTime;
	int damage = 0;
	if (m_FrameCountHeroEnemy > 0.5)
	{
		if (m_ActEnemyPtr->IsOverlapping(ActHeroPtr) && m_ActEnemyPtr->IsActive() == true)
		{
			m_FrameCountHeroEnemy = 0;
			damage += m_EnemyDamage;
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
	
	// check Rocket hit
	for (unsigned int i = 0; i < m_ArrRocketsPtr.size(); i++)
	{
		if (m_ArrRocketsPtr[i].m_ActRocketsPtr != nullptr)
		{
			if (ActHeroPtr->IsOverlapping(m_ArrRocketsPtr[i].m_ActRocketsPtr))
			{
				damage += m_EnemyDamage;
				delete m_ArrRocketsPtr[i].m_ActRocketsPtr;
				m_ArrRocketsPtr[i].m_ActRocketsPtr = nullptr;
			}
		}
	}
	return damage;
}

void GuardBox::HeroInRange(PhysicsActor* actHeroPtr)
{
	//afstand bepalen van enemy naar hero
	DOUBLE2 diff = m_ActEnemyPtr->GetPosition() - actHeroPtr->GetPosition();
	diff = DOUBLE2{ abs(diff.x) , abs(diff.y) };
	double length = sqrt(diff.x*diff.x + diff.y*diff.y);
	//richting van enemy bepalen
	
		m_FrameTimeCounter = 0;
		double dif = m_ActEnemyPtr->GetPosition().x - actHeroPtr->GetPosition().x;
		if (dif > 0)
		{
			m_EnemyDirection = Direction::RIGHT;
		}
		else
		{
			m_EnemyDirection = Direction::LEFT;
		}
}

void GuardBox::CreateProjectile(DOUBLE2 spawnPos)
{
	int projectileSpeed = 200;
	int afstand = 50;
	double angle = 0;
	Rocket temp;
	temp.m_ActRocketsPtr = new PhysicsActor(spawnPos + DOUBLE2{0,0} , 0 , BodyType::DYNAMIC);
	temp.m_RocketDirection = m_EnemyDirection;
	m_ArrRocketsPtr.push_back(temp);
	
	m_ArrRocketsPtr[m_ArrRocketsPtr.size() - 1].m_ActRocketsPtr->AddBoxFixture(30, 15, 0);
	m_ArrRocketsPtr[m_ArrRocketsPtr.size() - 1].m_ActRocketsPtr->SetGravityScale(0);

	m_ArrRocketsPtr[m_ArrRocketsPtr.size() - 1].m_ActRocketsPtr->SetLinearVelocity({ projectileSpeed * -(double)m_EnemyDirection,
			0.0 });

}

void GuardBox::CheckHitWalls(Level* levelPtr)
{
	for (unsigned int i = 0; i < m_ArrRocketsPtr.size(); i++)
	{
		if (m_ArrRocketsPtr[i].m_ActRocketsPtr != nullptr)
		{
			if (levelPtr->HitWall(m_ArrRocketsPtr[i].m_ActRocketsPtr))
			{
				delete m_ArrRocketsPtr[i].m_ActRocketsPtr;
				m_ArrRocketsPtr[i].m_ActRocketsPtr = nullptr;
			}
		}
	}
}

void GuardBox::PaintProjectiles()
{
	for (int i = 0; i < m_ArrRocketsPtr.size(); i++)
	{
		if (m_ArrRocketsPtr[i].m_ActRocketsPtr != nullptr)
		{
			if (m_ArrRocketsPtr[i].m_RocketDirection == Direction::LEFT)
			{
				DOUBLE2 positon = m_ArrRocketsPtr[i].m_ActRocketsPtr->GetPosition();

				MATRIX3X2 matPivot, matTranslate;
				MATRIX3X2 matFlip, matWorld;

				matTranslate.SetAsTranslate(positon);
				matFlip.SetAsScale(1, 1);

				//middle to center

				double frameWidth = m_BmpRocketPtr->GetWidth() / 8.0;
				double frameHeight = m_BmpRocketPtr->GetHeight() / 8.0;

				matPivot.SetAsTranslate(-(frameWidth / 1.5), -(frameHeight / 1.3));

				matWorld = matPivot * matFlip * matTranslate;

				GAME_ENGINE->SetWorldMatrix(matWorld);
			}
			else
			{
				DOUBLE2 positon = m_ArrRocketsPtr[i].m_ActRocketsPtr->GetPosition();

				MATRIX3X2 matPivot, matTranslate;
				MATRIX3X2 matFlip, matWorld;

				matTranslate.SetAsTranslate(positon);
				matFlip.SetAsScale(-1, 1);

				//middle to center

				double frameWidth = m_BmpRocketPtr->GetWidth() / 8.0;
				double frameHeight = m_BmpRocketPtr->GetHeight() / 8.0;

				matPivot.SetAsTranslate(-(frameWidth / 1.5), -(frameHeight / 1.3));

				matWorld = matPivot * matFlip * matTranslate;

				GAME_ENGINE->SetWorldMatrix(matWorld);
			}
		
				int frameMax = 2;
				int frameMin = 1;
				int m_FrameX = 2;
				int m_FrameY = 1;
				m_FrameRocket = (int)m_FrameTimeCounter;
				m_FrameRocket = (m_FrameRocket % (frameMax - frameMin)) + frameMin;
				double width = m_BmpRocketPtr->GetWidth();
				double height = m_BmpRocketPtr->GetHeight();
				GAME_ENGINE->DrawBitmap(m_BmpRocketPtr,
				{ width / m_FrameX * (m_FrameRocket % m_FrameX), height / m_FrameY * (m_FrameRocket / m_FrameX) ,  width / m_FrameX + width / m_FrameX * (m_FrameRocket % m_FrameX) ,  (height / m_FrameY) + height / m_FrameY * (m_FrameRocket / m_FrameX) });
		}
		//reset view
		GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
	}
}