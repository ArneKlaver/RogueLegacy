//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "EnemyManager.h"
#include "IceWizard.h"
#include "Knight.h"
#include "GuardBox.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (Enemy* temp : m_ArrEnemyPtr)
	{
		delete temp;
		temp = nullptr;
	}
	for (IceWizard* temp: m_ArrIceWizardPtr)
	{
		delete temp;
		temp = nullptr;
	}
}

void EnemyManager::Tick(double deltaTime , Level* levelPtr , PhysicsActor* actHeroPtr ,  PhysicsActor* actWeaponPtr)
{
	m_DeactivateEnemys( levelPtr);	//Deactivates and activate enemys
	m_FoundLvl = false;
	m_LevelPtr = levelPtr->GetLevelNumber();

	for (int temp : m_ArrCountLvls)
	{
		if (temp == m_LevelPtr)
		{
			m_FoundLvl = true;
		}
	}
	if (m_FoundLvl == false)
	{
		CreateEnemys(levelPtr);
		m_ArrCountLvls.push_back(levelPtr->GetLevelNumber());
	}
	//loop to check all the enemies for damage and if alive
	for (unsigned int i = 0; i < m_ArrEnemyPtr.size() ; i++)
	{
		if (m_ArrEnemyPtr[i] != nullptr)
		{
			CheckIfHit(deltaTime, actHeroPtr);
			m_ArrEnemyPtr[i]->Tick(deltaTime, levelPtr, actHeroPtr, actWeaponPtr);
			if (m_ArrEnemyPtr[i]->GetAlive() == false)
			{
				m_ArrEnemyPtr[i]->~Enemy();
				delete m_ArrEnemyPtr[i];
				m_ArrEnemyPtr[i] = nullptr;
			}
		}

	
	}	
}
void EnemyManager::Paint()
{
	for (Enemy* temp : m_ArrEnemyPtr)
	{
		if (temp != nullptr)
		{
			temp->Paint();
		}
	}
	
}

void EnemyManager::CheckIfHit(double deltaTime , PhysicsActor* actHeroPtr)
{
	for (Enemy* temp : m_ArrEnemyPtr)
	{
		m_Damage += temp->HitHeroCheck(deltaTime, actHeroPtr);
	}
}

int EnemyManager::GetDamage()
{
	int damage = m_Damage;
	m_Damage = 0;
	return damage;
}

void EnemyManager::CreateEnemys(Level* levelPtr)
{
	//locatie van Enemy
	std::vector<DOUBLE2> posEnemys;
	switch (levelPtr->GetLevelNumber())
	{
	case 0:

	default:
		break;
	}

	// crearen van Enemy 
	for (DOUBLE2 temp: posEnemys)
	{
		m_ArrEnemyPtr.push_back(new GuardBox(temp, levelPtr->GetLevelNumber()));
	}
}

void EnemyManager::m_DeactivateEnemys(Level* levelPtr)
{
	for (unsigned int i = 0; i < m_ArrEnemyPtr.size(); i++)
	{
		if (m_ArrEnemyPtr[i] != nullptr)
		{
			if (m_ArrEnemyPtr[i]->GetLevelStart() != levelPtr->GetLevelNumber())//this is current level
			{
				m_ArrEnemyPtr[i]->m_DeactivateEnemy(false);
			}
			else
			{
				m_ArrEnemyPtr[i]->m_DeactivateEnemy(true);
			}
		}
	}
}