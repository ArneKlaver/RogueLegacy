#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "Level.h"
#include "Torch.h"
#include "FirePlace.h"

class LevelManager 
{
public:
	
	LevelManager( );
	virtual ~LevelManager( );
	// Make objects non-copLevelManagerable
	// https://msdn.microsoft.com/en-us/librarLevelManager/dn457344.aspx 
	LevelManager( const LevelManager& ) = delete;
	LevelManager& operator=( const LevelManager& ) = delete;

	void paint();
	void Tick(double deltaTime, PickUpManager* m_PickUpManager, PhysicsActor* actOtherPtr , PhysicsActor* actWeaponHeroPtr );
	Level* GetCurrentLevel();
	void CreateNextLevel();
	void RespawnHero(DOUBLE2 position , PhysicsActor* actOtherPtr);
	int FindNextLevel(int doorNumber);
	int GetCurentLevelNumber();
	std::vector<doorsPosAngle> CreateDoors();

	std::vector<DOUBLE2> CreateTorches();
	std::vector<DOUBLE2> CreateFireplaces();
	std::vector<DOUBLE2> CreateCandleSticks();
	std::vector<DOUBLE2> CreatePlatforms();
private: 
	//rooms
	std::vector<Level* > m_ArrLevelsPtr;
	DOUBLE2 m_RespawnPosition;
	int m_CurrentLvl = 0;

};
