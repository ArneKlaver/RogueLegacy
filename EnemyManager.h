#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "Enemy.h"
class Level;
class IceWizard;

class EnemyManager 
{
public:
	EnemyManager();
	virtual ~EnemyManager( );
	// Make objects non-copEnemyManagerable
	// https://msdn.microsoft.com/en-us/librarEnemyManager/dn457344.aspx 
	EnemyManager( const EnemyManager& ) = delete;
	EnemyManager& operator=( const EnemyManager& ) = delete;

	void Tick(double deltaTime , Level* levelPtr , PhysicsActor* actHeroPtr , PhysicsActor* actWeaponPtr);
	void Paint();
	void CheckIfHit(double deltaTime  , PhysicsActor* actHeroPtr);
	int GetDamage();
	void CreateEnemys(Level* levelPtr);
	void m_DeactivateEnemys(Level* levelPtr);
private: 
	std::vector<Enemy* > m_ArrEnemyPtr;
	std::vector<IceWizard* > m_ArrIceWizardPtr;
	int m_Damage;
	int m_LevelPtr = -1;
	std::vector<int> m_ArrCountLvls;
	bool m_FoundLvl = false;
};
