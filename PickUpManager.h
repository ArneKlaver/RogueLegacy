#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "GoldCoin.h"

class PickUpManager 
{
public:
	PickUpManager( );
	virtual ~PickUpManager( );
	// Make objects non-copPickUpManagerable
	// https://msdn.microsoft.com/en-us/librarPickUpManager/dn457344.aspx 
	PickUpManager( const PickUpManager& ) = delete;
	PickUpManager& operator=( const PickUpManager& ) = delete;

	void Tick(double deltaTime , PhysicsActor* actHeroPtr , int currentLvl);
	void Paint();

	void CreateGoldCoin(int m_CurentLevel , DOUBLE2 position);
private: 
	std::vector<GoldCoin* > m_ArrGoldCoinsPtr;
	int m_Gold = 0;
};
