#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "PickUpManager.h"

class LevelManager;
class CandleStick 
{
public:
	CandleStick(DOUBLE2 position , int levelNumber);
	virtual ~CandleStick( );
	// Make objects non-copCandleStickable
	// https://msdn.microsoft.com/en-us/librarCandleStick/dn457344.aspx 
	CandleStick( const CandleStick& ) = delete;
	CandleStick& operator=( const CandleStick& ) = delete;

	void Paint();
	void Tick(double deltaTime , PhysicsActor* actWeaponHeroPtr );
	MATRIX3X2 GetViewMatrix(DOUBLE2 position);
	void DrawBitmap(int frameMin, int frameMax);
	bool GetDestroyed();
	DOUBLE2 GetPosition();
	PhysicsActor* GetActor();
private:
	Bitmap* m_BmpCandleStickPtr = nullptr;
	PhysicsActor* m_ActCandleStickPtr = nullptr;
	DOUBLE2 m_Position;
	double m_FrameNr = 0;
	bool m_IsDestroyed = false;
	int m_LevelNumber = 0;
};
