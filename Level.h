#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "Torch.h"
#include "FirePlace.h"
#include "Candlestick.h"
#include "Platform.h"
struct doorsPosAngle
{
	DOUBLE2 pos;
	double angle = 0;
};
class Level 
{
public:
	Level(int LevelNumber
			, std::vector<doorsPosAngle> DoorPositions , std::vector<DOUBLE2> CreateDoors
			, std::vector<DOUBLE2> torchPositions , std::vector<DOUBLE2> firePlacePositions , std::vector<DOUBLE2> CandleStickPosition);
	virtual ~Level( );
	// Make objects non-copLevelable
	// https://msdn.microsoft.com/en-us/librarLevel/dn457344.aspx 
	Level( const Level& ) = delete;
	Level& operator=( const Level& ) = delete;

	void Tick(double deltaTime , PickUpManager* m_PickUpManager, PhysicsActor* actWeaponHeroPtr , PhysicsActor* actHeroPtr);
	void Paint();
	double GetWidth();
	double GetHeight();
	bool IsOnGround(PhysicsActor* actOtherPtr);
	bool HitWall(PhysicsActor* actOtherPtr);
	void m_DeactivateActor(bool active);
	int IsDoorHit(PhysicsActor* actOtherPtr1);

	void CreateDoors(std::vector<doorsPosAngle> DoorPositions);
	int GetLevelNumber();
	bool GetCreateEnemys();
private: 
	int m_LvlNumber = 0;
	bool m_CreateEnemys = false;
	Bitmap* m_BmpMapPtr = nullptr;
	PhysicsActor* m_ActFloorPtr = nullptr;
	PhysicsActor* m_ActRoofPtr = nullptr;
	std::vector<PhysicsActor* > m_ArrActDoorsPtr;
	std::vector<Platform* > m_ArrPlatformPtr;
	std::vector<Torch* > m_ArrTorchesPtr;
	std::vector<FirePlace* > m_ArrFirePlacesPtr;
	std::vector<CandleStick* > m_ArrCandleSticksPtr;

};
