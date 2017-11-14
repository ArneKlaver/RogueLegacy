//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "PickUpManager.h"
#include "GoldCoin.h"

//#define GAME_ENGINE (GameEngine::GetSingleton())

PickUpManager::PickUpManager()
{
}

PickUpManager::~PickUpManager()
{
	for (GoldCoin* temp : m_ArrGoldCoinsPtr)
	{
		delete temp;
		temp = nullptr;
	}
}

void PickUpManager::Tick(double deltaTime , PhysicsActor* actHeroPtr , int currentLvl)
{
	for (unsigned int i = 0; i < m_ArrGoldCoinsPtr.size(); i++)
	{
		if (m_ArrGoldCoinsPtr[i] != nullptr)
		{
			m_ArrGoldCoinsPtr[i]->Tick(deltaTime, actHeroPtr , currentLvl);
			if (m_ArrGoldCoinsPtr[i]->GetPickedUp())
			{
				m_Gold++;
				m_ArrGoldCoinsPtr[i]->~GoldCoin();
				delete m_ArrGoldCoinsPtr[i];
				m_ArrGoldCoinsPtr[i] = nullptr;
			}
			else if (m_ArrGoldCoinsPtr[i]->GetDeleted())
			{
				m_ArrGoldCoinsPtr[i]->~GoldCoin();
				delete m_ArrGoldCoinsPtr[i];
				m_ArrGoldCoinsPtr[i] = nullptr;
			}
		}
	}
}
void PickUpManager::Paint()
{
	for (unsigned int i = 0; i < m_ArrGoldCoinsPtr.size(); i++)
	{
		if (m_ArrGoldCoinsPtr[i] != nullptr)
		{
			m_ArrGoldCoinsPtr[i]->Paint();
		}
	}
}

void PickUpManager::CreateGoldCoin(int currentLvlStart, DOUBLE2 position)
{
	m_ArrGoldCoinsPtr.push_back(new GoldCoin(currentLvlStart, position + DOUBLE2{0,-50}));
}