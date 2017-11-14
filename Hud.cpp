//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Hud.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Hud::Hud()
{
	m_HealtBarPtr = new Bitmap(String("Resources/HUD/health_Bar.png"));
	m_GoldCoinPtr = new Bitmap(String("Resources/HUD/gold_coin.png"));
	m_HealthPtr = new Bitmap(String("Resources/HUD/health.png"));
	m_LvlIconPtr = new Bitmap(String("Resources/HUD/Lvl_Text.png"));
	m_ManaPtr = new Bitmap(String("Resources/HUD/mana.png"));
	m_SkillBarPtr = new Bitmap(String("Resources/HUD/skillbar.png"));
	m_ManaBarPtr = new Bitmap(String("Resources/HUD/manaBar.png"));
}

Hud::~Hud()
{
	delete m_HealtBarPtr;
	m_HealtBarPtr = nullptr;
	delete m_GoldCoinPtr;
	m_GoldCoinPtr = nullptr;
	delete m_HealthPtr;
	m_HealthPtr = nullptr;
	delete m_LvlIconPtr;
	m_LvlIconPtr = nullptr;
	delete m_ManaPtr;
	m_ManaPtr = nullptr;
	delete m_SkillBarPtr;
	m_SkillBarPtr = nullptr;
	delete m_ManaBarPtr;
	m_ManaBarPtr = nullptr;
}

void Hud::Paint()
{
	DrawHealth();
	DrawMana();
	DrawBitmaps();

	//reset view
	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
}

void Hud::Tick(int health, int mana)
{
	m_HealthHero = health;
	m_ManaHero = mana;
}

MATRIX3X2 Hud::GetViewMatrix(DOUBLE2 position)
{
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(position);

	return matCamera;
}

void Hud::DrawBitmaps()
{
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 30,20 }));
	GAME_ENGINE->DrawBitmap(m_LvlIconPtr);
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 30,40 }));
	GAME_ENGINE->DrawBitmap(m_HealtBarPtr);
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 30,75 }));
	GAME_ENGINE->DrawBitmap(m_ManaBarPtr);
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 30,105 }));
	GAME_ENGINE->DrawBitmap(m_GoldCoinPtr);
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 30,140 }));
	GAME_ENGINE->DrawBitmap(m_SkillBarPtr);
	GAME_ENGINE->SetViewMatrix(GetViewMatrix({ 80,140 }));
	GAME_ENGINE->DrawBitmap(m_SkillBarPtr);
}
void Hud::DrawHealth()
{
	double yoffset = 45;
	double xOffset = 30;
	int bitmapWidth = 8;

	switch (m_HealthHero / 10)
	{
	case 10:
		xOffset = 35 + (9 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 9:
		xOffset = 35 + (8 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 8:
		xOffset = 35 + (7 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 7:
		xOffset = 35 + (6 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 6:
		xOffset = 35 + (5 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 5:
		xOffset = 35 + (4 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 4:
		xOffset = 35 + (3 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 3:
		xOffset = 35 + (2 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 2:
		xOffset = 35 + (1 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	case 1:
		xOffset = 35 + (0 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_HealthPtr);
	default:
		break;
	}

}
void Hud::DrawMana()
{
	double yoffset = 80;
	double xOffset = 30;
	int bitmapWidth = 8;
	switch (m_ManaHero / 10)
	{
	case 10:
		xOffset = 35 + (9 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 9:
		xOffset = 35 + (8 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 8:
		xOffset = 35 + (7 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 7:
		xOffset = 35 + (6 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 6:
		xOffset = 35 + (5* bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 5:
		xOffset = 35 + (4 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 4:
		xOffset = 35 + (3 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 3:
		xOffset = 35 + (2 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 2:
		xOffset = 35 + (1 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	case 1:
		xOffset = 35 + (0 * bitmapWidth);
		GAME_ENGINE->SetViewMatrix(GetViewMatrix({ xOffset,yoffset }));
		GAME_ENGINE->DrawBitmap(m_ManaPtr);
	default:
		break;
	}
	
}