//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Hero.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Hero::Hero(const DOUBLE2 & centerRef)
{
	m_ActHeroPtr = new PhysicsActor(centerRef , 0 , BodyType::DYNAMIC);
	m_ActHeroPtr->AddBoxFixture(50, 90, 0 ,1);
	m_ActHeroPtr->SetFixedRotation(true);
	 
	m_ActWeaponPtr = new PhysicsActor(centerRef, 0, BodyType::KINEMATIC);
	m_ActWeaponPtr->AddBoxFixture(25, 90, 0, 1);
	m_ActWeaponPtr->SetFixedRotation(true);
	m_ActWeaponPtr->SetSensor(true);
	m_ActWeaponPtr->SetActive(false);
	m_BmpHeroPtr = new Bitmap(String("Resources/Knight.png"));
}

Hero::~Hero()
{
	delete m_ActHeroPtr;
	m_ActHeroPtr = nullptr;
	delete m_BmpHeroPtr;
	m_BmpHeroPtr = nullptr;
	delete m_ActWeaponPtr;
	m_ActWeaponPtr = nullptr;
}

void Hero::Paint()
{
	PosFlipBitmap();
	switch (m_ActionState)
	{
	case Hero::ActionState::WAITING:
		DrawHero(0, 20);
		break;
	case Hero::ActionState::MOVING:
		DrawHero(21, 38);
		break;
	case Hero::ActionState::ATACKING:
		DrawHero(39, 51);
		break;
	case Hero::ActionState::JUMPING:
		if (m_ActHeroPtr->GetLinearVelocity().y < 0)//als actor naar BOVEN gaat
		{
			DrawHero(59, 68);
		}
		else//als actor naar BENEDEN gaat
		{
			DrawHero(69, 77);
		}
		break;
	case Hero::ActionState::DEAD:
		DrawHero(78, 95);
	default:
		break;
	}
	//Reset world matrix
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void Hero::Tick(double deltaTime, Level* levelPtr , EnemyManager* EnemyManager)
{
	Atacked(deltaTime, EnemyManager);
	MoveHero(levelPtr);
	WeaponMovement();
	switch (m_ActionState)
	{
	case Hero::ActionState::WAITING:
		Waiting(levelPtr);
		break;
	case Hero::ActionState::MOVING:
		Moving(levelPtr);
		break;
	case Hero::ActionState::ATACKING:
		Atacking(levelPtr , deltaTime);
		break;
	case Hero::ActionState::JUMPING:
		Jumping(levelPtr);
		m_CountJumpingTime += deltaTime;
		break;
	default:
		break;
	}
	m_FrameHero += deltaTime * m_NrFramesPerSec;
	m_NrFramesPerSec = 10;
	//reset 
	if (levelPtr->IsOnGround(m_ActHeroPtr))
	{
		m_JumpStacks = 0;
	}
	Resetknockback(deltaTime, levelPtr);
}

// ------------- change states ---------------
void Hero::Waiting(Level* levelPtr)
{
	if (m_Knockback == false)
	{
		m_ActHeroPtr->SetLinearVelocity({ 0,0 });
	}
	//change to MOVING		if hero is on ground and a key is pressed
	if (!levelPtr->IsOnGround(m_ActHeroPtr) || GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT) || GAME_ENGINE->IsKeyboardKeyDown(VK_UP) || GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		m_ActionState = ActionState::MOVING;
		m_FrameHero = 0;
	}

	//change to ATACKING	if key A is pressed
	if (GAME_ENGINE->IsKeyboardKeyPressed('A'))
	{
		m_ActionState = ActionState::ATACKING;
		m_FrameHero = 0;
	}
	
}
void Hero::Moving(Level* levelPtr)
{

	// change to WAITING if nothing happens and avatar is on ground
	if (levelPtr->IsOnGround(m_ActHeroPtr) && !GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT) && !GAME_ENGINE->IsKeyboardKeyDown(VK_UP) && !GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		m_ActionState = ActionState::WAITING;
		m_FrameHero = 0;
	}	
	//change to ATACKING	if key A is pressed
	if (GAME_ENGINE->IsKeyboardKeyPressed('A'))
	{
		m_ActionState = ActionState::ATACKING;
		m_FrameHero = 0;
	}
	//change to Jumping if actor is in the air
	if ( GAME_ENGINE->IsKeyboardKeyDown(VK_UP) && m_JumpStacks <= m_JumpStacksMax)
	{
		m_ActionState = ActionState::JUMPING;
		m_FrameHero = 0;
	}
}
void Hero::Atacking(Level* levelPtr , double deltaTime)
{
	
	m_NrFramesPerSec = 15;
	m_FrameCount += deltaTime*m_NrFramesPerSec;
	if (levelPtr->IsOnGround(m_ActHeroPtr) && !GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT) && !GAME_ENGINE->IsKeyboardKeyDown(VK_UP) && !GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		if (m_Knockback == false)
		{
			m_ActHeroPtr->SetLinearVelocity({ 0,0 });
		}
	}
	if (m_FrameCount >5 && m_FrameCount < 7 )
	{
		m_ActWeaponPtr->SetActive(true);
		m_Angle -= int(m_HeroDirection) * 10 ;
		RotateWeapon();
	}
	if (m_FrameCount > 10)
	{
		//reset weapon
		m_ActWeaponPtr->SetActive(false);
		ResetWeapon();
		//change to WAITING
		if (levelPtr->IsOnGround(m_ActHeroPtr) && !GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT) && !GAME_ENGINE->IsKeyboardKeyDown(VK_UP) && !GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_ActionState = ActionState::WAITING;
			m_FrameHero = 0;
		}
		//change to MOVING		if hero is on ground and a key is pressed
		if ( (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT) || GAME_ENGINE->IsKeyboardKeyDown(VK_UP) || GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT)))
		{
			m_ActionState = ActionState::MOVING;
			m_FrameHero = 0;
		}
		//change to Jumping if actor is in the air
		if (!levelPtr->IsOnGround(m_ActHeroPtr))
		{
			m_ActionState = ActionState::JUMPING;
			m_FrameHero = 0;
		}
		m_FrameCount = 0;
	}
}

void Hero::Jumping(Level* levelPtr)
{
	// change to MOVING 
	if (levelPtr->IsOnGround(m_ActHeroPtr) && m_CountJumpingTime > 0.2)
	{
		m_ActionState = ActionState::MOVING;
		m_FrameHero = 0;
		m_CountJumpingTime = 0;
	}

	//change to ATACKING	if key A is pressed
	if (GAME_ENGINE->IsKeyboardKeyPressed('A') )
	{
		m_ActionState = ActionState::ATACKING;
		m_FrameHero = 0;
		m_CountJumpingTime = 0;
	}

}

// functions
void Hero::DrawHero(int frameMin , int frameMax)
{
	int frameX = 10;// number of images horizontal
	int frameY = 10;// number of images vertical

	int frameNr = (int)m_FrameHero;
	frameNr = (frameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpHeroPtr->GetWidth();
	double height = m_BmpHeroPtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpHeroPtr, /*m_ActHeroPtr->GetPosition() - DOUBLE2{ (width / frameX) /3 , (height / frameY) /1.5},*/
	{ width / frameX * (frameNr % frameX), height / frameY * (frameNr / frameX) ,  width / frameX + width / frameX * (frameNr % frameX) ,  (height / frameY) + height / frameY * (frameNr / frameX) });
}
RECT2 Hero::GetRect()
{
	RECT2 reRect;

	reRect.left = m_ActHeroPtr->GetPosition().x - m_WidthActor / 2;
	reRect.right = reRect.left + m_WidthActor;

	reRect.top = m_ActHeroPtr->GetPosition().y - m_HeightActor / 2;
	reRect.bottom = reRect.top + m_HeightActor;

	return reRect;
}
DOUBLE2 Hero::GetPosition()
{
	return m_ActHeroPtr->GetPosition();
}
PhysicsActor* Hero::GetActor()
{
	return m_ActHeroPtr;
}
PhysicsActor* Hero::GetWeaponActor()
{
	return m_ActWeaponPtr;
}
void Hero::MoveHero(Level* levelPtr)
{
	switch (m_ActionState)
	{
	case Hero::ActionState::MOVING:
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_HeroDirection = Direction::LEFT;
			m_Angle = 140;
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ -m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_HeroDirection = Direction::RIGHT;
			m_Angle = 50;
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}
		if (!levelPtr->IsOnGround(m_ActHeroPtr) )
		{
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_ActHeroPtr->GetLinearVelocity().x, 500 });
			}
		}
		
		break;
	case Hero::ActionState::ATACKING:
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ -m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}


		if (m_JumpStacks <= m_JumpStacksMax && GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
		{
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_ActHeroPtr->GetLinearVelocity().x , -m_JumpSpeed });
			}
			m_JumpStacks++;
		}
		break;
	case Hero::ActionState::JUMPING:
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
		{
			m_HeroDirection = Direction::LEFT;
			m_Angle = 140;
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ -m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}
		if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
		{
			m_HeroDirection = Direction::RIGHT;
			m_Angle = 50;
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_HorSpeed , m_ActHeroPtr->GetLinearVelocity().y });
			}
		}


		if (m_JumpStacks <= m_JumpStacksMax && GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
		{
			if (m_Knockback == false)
			{
				m_ActHeroPtr->SetLinearVelocity({ m_ActHeroPtr->GetLinearVelocity().x , -m_JumpSpeed });
			}
			m_JumpStacks++;
		}
		break;
	default:
		break;
	}

}

void Hero::WeaponMovement()
{
	m_ActWeaponPtr->SetPosition(m_ActHeroPtr->GetPosition() + m_WeaponOffset);
}

void Hero::RotateWeapon()
{
	m_WeaponOffset.x = (cos(m_Angle* 3.14 / 180) * m_Radius);
	m_WeaponOffset.y = -(sin(m_Angle* 3.14 / 180) * m_Radius);
	m_ActWeaponPtr->SetAngle(-m_Angle*3.14 / 180 + 1.57);
}

void Hero::ResetWeapon()
{
	switch (m_HeroDirection)
	{
	case Hero::Direction::LEFT:
		m_Angle = 140;		
		break;
	case Hero::Direction::RIGHT:
		m_Angle = 50;
		break;
	default:
		break;
	}
	m_ActWeaponPtr->SetAngle(m_Angle*3.14 / 180);
	m_WeaponOffset = DOUBLE2{ (cos(m_Angle* 3.14 / 180) * m_Radius) , -sin(m_Angle* 3.14 / 180) * m_Radius };
}

void Hero::Atacked(double deltaTime, EnemyManager* EnemyManager)
{
	int damage = EnemyManager->GetDamage();
	if (damage !=0)
	{
		if (damage == 10)
		{
			m_Knockback = true;
			m_ActHeroPtr->ApplyLinearImpulse({ -15000.0 * (int)m_HeroDirection , -15000.0 });
		}
		else
		{
			m_Knockback = true;
			m_ActHeroPtr->ApplyLinearImpulse({ -15000.0 * (int)m_HeroDirection , -15000.0 });
		}

		m_Health -= damage;
	}
	if (m_Health <= 0)
	{
		m_ActionState = ActionState::DEAD;
		m_EndGame = true;
	}
}

int Hero::GetHealth()
{
	return m_Health;
}
int Hero::GetMana()
{
	return m_Mana;
}

void Hero::PosFlipBitmap()
{
	if (m_HeroDirection == Direction::LEFT)
	{
		DOUBLE2 positon = m_ActHeroPtr->GetPosition();

		MATRIX3X2 matPivot, matTranslate;
		MATRIX3X2 matFlip, matWorld;

		matTranslate.SetAsTranslate(positon);
		matFlip.SetAsScale(-1, 1);

		//middle to center

		double frameWidth = m_BmpHeroPtr->GetWidth() / 10.0;
		double frameHeight = m_BmpHeroPtr->GetHeight() / 10.0;

		matPivot.SetAsTranslate(-(frameWidth / 3), -(frameHeight / 1.5));

		matWorld = matPivot * matFlip * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorld);
	}
	else
	{
		DOUBLE2 positon = m_ActHeroPtr->GetPosition();

		MATRIX3X2 matPivot, matTranslate;
		MATRIX3X2 matFlip, matWorld;

		matTranslate.SetAsTranslate(positon);
		matFlip.SetAsScale(1, 1);

		//middle to center

		double frameWidth = m_BmpHeroPtr->GetWidth() / 10.0;
		double frameHeight = m_BmpHeroPtr->GetHeight() / 10.0;

		matPivot.SetAsTranslate(-(frameWidth / 3), -(frameHeight / 1.5));

		matWorld = matPivot * matFlip * matTranslate;

		GAME_ENGINE->SetWorldMatrix(matWorld);
	}
}

void Hero::Resetknockback(double deltaTime , Level* levelPtr)
{
	if (m_Knockback)
	{
		m_KnockBackCounter += deltaTime * 10;
	}
	if (levelPtr->IsOnGround(m_ActHeroPtr) && m_KnockBackCounter > 0.5)
	{
		m_KnockBackCounter = 0;
		m_Knockback = false;
	}
}

bool Hero::GetEndGame()
{
	return m_EndGame;
}
