//-----------------------------------------------------------------
// Student data
// Name:
// Group: 1DAE..
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "IceWizard.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

IceWizard::IceWizard(DOUBLE2 position, int levelStart)
	:Enemy(position, levelStart)
{
	m_ActEnemyPtr = new PhysicsActor(position, 0, BodyType::DYNAMIC);
	m_ActEnemyPtr->AddBoxFixture(50, 90, 0, 1);
	m_ActEnemyPtr->SetFixedRotation(true);
	m_ActEnemyPtr->SetGravityScale(0);
	m_ActWeaponPtr = new PhysicsActor({ 350,300 }, 0, BodyType::KINEMATIC);
	m_ActWeaponPtr->AddBoxFixture(30, 165, 0, 1);
	m_ActWeaponPtr->SetFixedRotation(true);
	m_ActWeaponPtr->SetSensor(true);
	m_ActWeaponPtr->SetActive(false);

	m_BmpIceCrystalPtr = new Bitmap(String("Resources/IceCrystal.png"));
	m_BmpEnemyPtr = new Bitmap(String("Resources/Enemy_IceWizard.png"));
	m_BmpChargeCrystalPtr = new Bitmap(String("Resources/ChargeCrystal.png"));
	m_FrameX = 5;// number of images horizontal
	m_FrameY = 5;// number of images vertical
	m_EnemyDamage = 20;
	m_WaitTimeMax = 0;
	m_MoveTimeMax = 3;
}

IceWizard::~IceWizard()
{
	delete m_BmpChargeCrystalPtr;
	m_BmpChargeCrystalPtr = nullptr;
	delete m_BmpIceCrystalPtr;
	m_BmpIceCrystalPtr = nullptr;
	for (PhysicsActor* temp : m_IceProjectiles)
	{
		delete temp;
		temp = nullptr;
	}
}

void IceWizard::Tick(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr, PhysicsActor* actWeaponPtr)
{
	if (m_IsActive)
	{
		HitHeroCheck(deltaTime, actHeroPtr);
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
			Move(deltaTime, levelPtr , actHeroPtr);
			m_TimeMoving += deltaTime;
			break;
		case Enemy::ActionState::ATACKING:
			Atack(deltaTime, levelPtr, actWeaponPtr);
			break;

		default:
			break;
		}
		EnemyDirection(actHeroPtr);
		

		//reset knockback
		Resetknockback(deltaTime, levelPtr);
	}

	//stop met animatie als m_Charging aan is
	if (!m_Charging)
	{
		m_FrameTimeCounter += deltaTime * m_NrFramesPerSec;
	}
	
	//reset m_Charging
	if (m_Charging)
	{
		m_FrameNrCharingCrystal += deltaTime * 15;
		m_ChargeTime += deltaTime *2.4;
		if (m_ChargeTime >= m_ChargeMaxTime)
		{
			m_FrameNrCharingCrystal = 0;
			m_Charging = false;
			m_FrameTimeCounter++; //volgende frame
			m_ChargeTime = 0;
			m_Crystals = true;
		}
	}
	Projectiles(levelPtr);
}

void IceWizard::Paint()
{
	PaintProjectiles();
	PaintChargeCrystal();
	if (m_IsActive)
	{
		PosFlipBitmap();
		switch (m_ActionState)
		{
		case Enemy::ActionState::WAITING:
			DrawHero(0, 11);
			break;
		case Enemy::ActionState::MOVING:
			DrawHero(0, 11);
			break;
		case Enemy::ActionState::ATACKING:
			PaintAtacking();
			break;
		default:
			break;
		}
	}
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}
void IceWizard::PaintProjectiles()
{
	for (PhysicsActor* temp : m_IceProjectiles)
	{
		if (temp != nullptr)
		{
			GAME_ENGINE->SetWorldMatrix(GetViewMatrix(temp->GetPosition(), temp->GetAngle()));
			GAME_ENGINE->DrawBitmap(m_BmpIceCrystalPtr);
		}
	}
	//reset view
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void IceWizard::PaintChargeCrystal()
{
	
	if (m_Charging)
	{
		int m_FrameX = 14;// number of images horizontal
		int m_FrameY = 1;// number of images vertical
		GAME_ENGINE->SetWorldMatrix(GetViewMatrix(m_ActEnemyPtr->GetPosition() + DOUBLE2{ -10,-100 },-1.57));

		{
		m_FrameNr = (int)m_FrameNrCharingCrystal;
		m_FrameNr = (m_FrameNr % (0 - 13)) + 0;
		double width = m_BmpChargeCrystalPtr->GetWidth();
		double height = m_BmpChargeCrystalPtr->GetHeight();
		GAME_ENGINE->DrawBitmap(m_BmpChargeCrystalPtr,
		{ width / m_FrameX * (m_FrameNr % m_FrameX), height / m_FrameY * (m_FrameNr / m_FrameX) ,  width / m_FrameX + width / m_FrameX * (m_FrameNr % m_FrameX) ,  (height / m_FrameY) + height / m_FrameY * (m_FrameNr / m_FrameX) });
		}
		
		//reset view
		GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
	}
}


void IceWizard::Move(double deltaTime, Level* levelPtr , PhysicsActor* actHeroPtr)
{
	if (!m_Knockback)
	{
		DOUBLE2 velocity;
		//enemy vliegt naar hero
		velocity = actHeroPtr->GetPosition() - m_ActEnemyPtr->GetPosition();
		m_ActEnemyPtr->SetLinearVelocity(velocity);
	}
	//change naar atacking na MoveTimeMax
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime > m_MoveTimeMax)
	{
		m_ElapsedTime = 0;
		m_ActionState = ActionState::ATACKING;
		m_FrameTimeCounter = 0;
	}
}

void IceWizard::Atack(double deltaTime, Level* levelPtr, PhysicsActor* actHeroPtr)
{
	m_ActEnemyPtr->SetLinearVelocity({0,0});
	if (m_Crystals)
	{
		CreateProjectile(m_ActEnemyPtr->GetPosition() + DOUBLE2{0,-50});
		m_Crystals = false;
	}

	if (m_FrameNr == 23)
	{
		m_ActionState = ActionState::MOVING;
		m_FrameNr = 0;
	}
}

void IceWizard::HeroInRange(PhysicsActor* actHeroPtr)
{
	//afstand bepalen van enemy naar hero
	DOUBLE2 diff = m_ActEnemyPtr->GetPosition() - actHeroPtr->GetPosition();
	diff = DOUBLE2{ abs(diff.x) , abs(diff.y) };
	double length = sqrt(diff.x*diff.x + diff.y*diff.y);
	//richting van enemy bepalen
	if (length < m_AtackRadius && m_TimeMoving > m_AtackSpeed)
	{
		m_TimeMoving = 0;
		m_ActionState = ActionState::MOVING;
		m_FrameTimeCounter = 0;
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
}

void IceWizard::Resetknockback(double deltaTime, Level* levelPtr)
{
	if (m_Knockback)
	{
		m_KnockBackCounter += deltaTime ;
	}
	if ( m_KnockBackCounter > 2)
	{
		m_KnockBackCounter = 0;
		m_Knockback = false;
		m_ActionState = ActionState::ATACKING;
		m_FrameNr = 0;
	}
}

void IceWizard::PaintAtacking()
{
	DrawHero(12, 24);
	if (!m_Charging)
	{
		if (m_FrameNr == 17)
		{
			m_Charging = true;
		}
	}
}

void IceWizard::Projectiles(Level* levelPtr)
{
	CheckHitWalls(levelPtr);
}
void IceWizard::CheckHitWalls(Level* levelPtr)
{
	for (unsigned int i = 0; i < m_IceProjectiles.size(); i++)
	{
			if (m_IceProjectiles[i] != nullptr)
			{
				if (levelPtr->HitWall(m_IceProjectiles[i]))
				{
					delete m_IceProjectiles[i];
					m_IceProjectiles[i] = nullptr;
				}
			}
	}
}
int IceWizard::HitHeroCheck(double deltaTime, PhysicsActor* ActHeroPtr)
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
	// check ice hit
	for (unsigned int i = 0; i < m_IceProjectiles.size(); i++)
	{
		if (m_IceProjectiles[i] != nullptr)
		{
			if (ActHeroPtr->IsOverlapping(m_IceProjectiles[i]))
			{
				delete m_IceProjectiles[i];
				m_IceProjectiles[i] = nullptr;
				damage += m_EnemyDamage;
			}
		}
	}
	return damage;
}

void IceWizard::CreateProjectile(DOUBLE2 spawnPos)
{
	int projectileSpeed = 200;
	int afstand = 50;
	double angle = (360.0 / 7) / 180*3.14;
	for (int i = 0; i < 7; i++)
	{
		m_IceProjectiles.push_back(new PhysicsActor({spawnPos.x + afstand*cos(angle*i),
			spawnPos.y + afstand*sin(angle * i)} , -1.57 + angle * i, BodyType::DYNAMIC));
		m_IceProjectiles[m_IceProjectiles.size() - 1]->AddBoxFixture(15, 30 ,0);	
		m_IceProjectiles[m_IceProjectiles.size() - 1]->SetGravityScale(0);

		m_IceProjectiles[m_IceProjectiles.size() - 1]->SetLinearVelocity({ projectileSpeed*cos(angle*i),
		projectileSpeed*sin(angle * i) });
	}
}
