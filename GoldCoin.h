#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------

class GoldCoin 
{
public:
	GoldCoin(int currentLvl, DOUBLE2 position);
	virtual ~GoldCoin( );
	// Make objects non-copGoldCoinable
	// https://msdn.microsoft.com/en-us/librarGoldCoin/dn457344.aspx 
	GoldCoin( const GoldCoin& ) = delete;
	GoldCoin& operator=( const GoldCoin& ) = delete;

	void Tick(double deltaTime, PhysicsActor* actHeroPtr , int currentLvl);
	void Paint();
	bool GetPickedUp();
	MATRIX3X2 GetViewMatrix(DOUBLE2 position);
	void DrawBitmap(int frameMin, int frameMax);
	bool GetDeleted();
private: 
	DOUBLE2 m_Position;
	PhysicsActor* m_ActCoinPtr = nullptr;
	Bitmap* m_BmpCoinPtr = nullptr;
	bool m_IsPickedUp = false;
	double m_FrameNr = 0;
	int m_LevelNumber = 0;
	bool m_IsDeleted = false;
};
