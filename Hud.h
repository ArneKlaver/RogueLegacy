#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------

class Hud 
{
public:
	Hud();
	virtual ~Hud( );
	// Make objects non-copHudable
	// https://msdn.microsoft.com/en-us/librarHud/dn457344.aspx 
	Hud( const Hud& ) = delete;
	Hud& operator=( const Hud& ) = delete;

	void Paint();
	void Tick(int health, int mana);
	void DrawBitmaps();
	void DrawHealth();
	void DrawMana();
	MATRIX3X2 GetViewMatrix(DOUBLE2 position);
private: 
	int m_HealthHero = 0;
	int m_ManaHero = 0;

	Bitmap* m_HealtBarPtr = nullptr;
	Bitmap* m_GoldCoinPtr = nullptr;
	Bitmap* m_HealthPtr = nullptr;
	Bitmap* m_LvlIconPtr = nullptr;
	Bitmap* m_ManaPtr = nullptr;
	Bitmap* m_SkillBarPtr = nullptr;
	Bitmap* m_ManaBarPtr = nullptr;
};
