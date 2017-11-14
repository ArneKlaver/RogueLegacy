//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "LevelManager.h"
#include "Torch.h"
#include "FirePlace.h"



//#define GAME_ENGINE (GameEngine::GetSingleton())

LevelManager::LevelManager()
{
	CreateNextLevel();
}

LevelManager::~LevelManager()
{
	for (Level* temp : m_ArrLevelsPtr)
	{
		delete temp;
		temp = nullptr;
	}
}

void LevelManager::Tick(double deltaTime , PickUpManager* m_PickUpManager , PhysicsActor* actHeroPtr , PhysicsActor* actWeaponHeroPtr )
{
	m_ArrLevelsPtr[m_CurrentLvl]->Tick(deltaTime , m_PickUpManager ,  actWeaponHeroPtr , actHeroPtr);
	int temp = m_ArrLevelsPtr[m_CurrentLvl]->IsDoorHit(actHeroPtr);
	if (temp >= 0)
	{
		m_ArrLevelsPtr[m_CurrentLvl]->m_DeactivateActor(false); 		//Deactivate door actors in other level
		int tempNextLevel = FindNextLevel(temp);
		for (unsigned int i = 0; i < m_ArrLevelsPtr.size(); i++)
		{
			if (m_ArrLevelsPtr[i] != nullptr && (unsigned)tempNextLevel < m_ArrLevelsPtr.size())
			{
				m_ArrLevelsPtr[tempNextLevel]->m_DeactivateActor(true); 	//activate actors in level
				m_CurrentLvl = tempNextLevel;
				RespawnHero(m_RespawnPosition, actHeroPtr);
				return;
			}
		}
		m_CurrentLvl = tempNextLevel;
		CreateNextLevel();
		RespawnHero(m_RespawnPosition , actHeroPtr);
	}
}
void LevelManager::paint()
{
	m_ArrLevelsPtr[m_CurrentLvl]->Paint();
}

Level* LevelManager::GetCurrentLevel()
{
	return m_ArrLevelsPtr[m_CurrentLvl];
}

int LevelManager::GetCurentLevelNumber()
{
	return m_CurrentLvl;
}

void LevelManager::CreateNextLevel()
{
	for (int i = 0; i < m_CurrentLvl; i++)
	{
		if (m_ArrLevelsPtr.size() < m_CurrentLvl)
		{
			m_ArrLevelsPtr.push_back(nullptr);
		}
	}	
	m_ArrLevelsPtr.push_back(new Level(m_CurrentLvl, CreateDoors(), CreatePlatforms(), CreateTorches(), CreateFireplaces(), CreateCandleSticks()));
}

void LevelManager::RespawnHero(DOUBLE2 position , PhysicsActor* actOtherPtr)
{
	actOtherPtr->SetPosition(position);
}

int LevelManager::FindNextLevel(int doorNumber)
{
	//return waarde is volgend level
	switch (m_CurrentLvl)
	{
	case 0:
		m_RespawnPosition = DOUBLE2{ 80, 270 };//DOUBLE2{ 50, 270 };
		return 1;//1
		break;
	case 1:
			switch (doorNumber)
			{
			case 0:
				m_RespawnPosition = DOUBLE2{ 2050, 300 };
				return 0;
				break;
			case 1:
				m_RespawnPosition = DOUBLE2{ 80, 880 };
				return 2;
				break;	
			}
			break;
	case 2:
			switch (doorNumber)
			{
			case 0:
				m_RespawnPosition = DOUBLE2{ 990, 300 };
				return 1;
				break;
			case 1:
				m_RespawnPosition = DOUBLE2{ 2666, 500 };
				return 6;
				break;
			case 2:
				m_RespawnPosition = DOUBLE2{60, 870 }; 
				return 3; 
				break;
			case 3:
				m_RespawnPosition = DOUBLE2{ 535, 80 };
				return 18;
				break;
			}
		break;
	case 3:
			switch (doorNumber)
			{
			case 0:
				m_RespawnPosition = DOUBLE2{ 960, 885 };
				return 2;
				break;
			case 1:
				m_RespawnPosition = DOUBLE2{ 560, 510 };
				return 14;
				break;
			case 2:
				m_RespawnPosition = DOUBLE2{ 80, 275 };
				return 17;
				break;
			case 3:
				m_RespawnPosition = DOUBLE2{ 530, 80 };
				return 20;
				break;
			}
		break;
	case 6:
			switch (doorNumber)
			{
			case 0:
				m_RespawnPosition = DOUBLE2{ 530, 450 };
				return 7;
				break;
			case 1:
				m_RespawnPosition = DOUBLE2{ 530, 1060 };
				return 10;
				break;
			case 2:
				m_RespawnPosition = DOUBLE2{ 540, 80 };
				return 2;
				break;
			case 3:
				m_RespawnPosition = DOUBLE2{ 2665, 80 };
				return 8;
		break;
		}
	case 7:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 530, 530 };
			return 6;
			break;
		}
		break;
	case 8:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 530, 530 };
			return 6;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 80, 270 };
			return 9;
			break;
		}
		break;
	case 9:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 3150, 270 };
			return 8;
			break;
		}
		break;
	case 10:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 530, 530 };
			return 11;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 80, 530 };
			return 12;
			break;
		case 2:
			m_RespawnPosition = DOUBLE2{ 530, 80 };
			return 14;
			break;
		case 3:
			m_RespawnPosition = DOUBLE2{ 2670, 80 };
			return 6;
			break;
		}
		break;
	case 11:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1310, 350 };
			return 11;
			break;
		}
		break;
	case 12:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 2080, 530 };
			return 11;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 80, 270 };
			return 13;
			break;
		}
		break;
	case 13:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1025, 270 };
			return 12;
			break;
		}
		break;
	case 14:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1600, 1070 };
			return 10;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 680, 80 };
			return 14;
			break;
		}
		break;
	case 15:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 80, 275 };
			return 16;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 2050, 80 };
			return 3;
			break;
		}
		break;
	case 16:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1030, 275 };
			return 15;
			break;
		}
		break;
	case 17:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 2680, 350 };
			return 3;
			break;
		}
		break;
	case 18:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 540, 1140 };
			return 2;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 80, 275 };
			return 19;
			break;
		}
		break;
	case 19:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1025, 270 };
			return 18;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 80, 270 };
			return 3;
			break;
		}
		break;
	case 20:
		switch (doorNumber)
		{
		case 0:
			m_RespawnPosition = DOUBLE2{ 1000, 270 };
			return 19;
			break;
		case 1:
			m_RespawnPosition = DOUBLE2{ 2050, 1350 };
			return 3;
			break;
		}
		break;

	}
}

std::vector<doorsPosAngle> LevelManager::CreateDoors()
{
	std::vector<doorsPosAngle> posDoors;
	
	switch (m_CurrentLvl)
	{
	case 0:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 2130, 300 };
		break;
	case 1:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 280 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 1060, 280 };	
		break;
	case 2:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 870 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 535, 0 };
		posDoors[1].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[2].pos = DOUBLE2{ 1070, 870 };
		posDoors.push_back(doorsPosAngle());
		posDoors[3].pos = DOUBLE2{ 536, 1175 };
		posDoors[3].angle = 1.57;
		break;
	case 3:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 855 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 540, 0 };
		posDoors[1].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[2].pos = DOUBLE2{ 1600, 0 };
		posDoors[2].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[3].pos = DOUBLE2{ 2140, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[4].pos = DOUBLE2{ 1600, 1150 };
		posDoors[4].angle = 1.57;
		break;
	case 6:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 532, 0 };
		posDoors[0].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 2665, 0 };
		posDoors[1].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[2].pos = DOUBLE2{ 2665, 600 };
		posDoors[2].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[3].pos = DOUBLE2{ 532, 600 };
		posDoors[3].angle = 1.57;
		break;
	case 7:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 540, 600 };
		posDoors[0].angle = 1.57;
		break;
	case 8:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 2670, 0 };
		posDoors[0].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 3200, 270 };
		break;
	case 9:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 280 };
		break;
	case 10:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 2140, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[2].pos = DOUBLE2{ 1605, 1180 };
		posDoors[2].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[3].pos = DOUBLE2{ 535,1180 };
		posDoors[3].angle = 1.57;
		break;
	case 11:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 1370, 350 };
		break;
	case 12:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 1065, 275 };
		break;
	case 13:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		break;
	case 14:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 540, 0 };
		posDoors[0].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 540, 600 };
		posDoors[0].angle = 1.57;
		break;
	case 15:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 1065, 265 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 535, 600 };
		posDoors[1].angle = 1.57;
		break;
	case 16:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 1065, 275 };
		break;
	case 17:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		break;
	case 18:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 530, 0 };
		posDoors[0].angle = 1.57;
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 1070, 280 };
		break;
	case 19:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 1070, 275 };
		break;
	case 20:
		posDoors.push_back(doorsPosAngle());
		posDoors[0].pos = DOUBLE2{ 0, 275 };
		posDoors.push_back(doorsPosAngle());
		posDoors[1].pos = DOUBLE2{ 0, 530 };
		posDoors[1].angle = 1.57;
		break;
	default:
		break;
	}
	return posDoors;
}

std::vector<DOUBLE2> LevelManager::CreatePlatforms()
{
	std::vector<DOUBLE2> PosPlatform;
	switch (m_CurrentLvl)
	{
	case 2:
		PosPlatform.push_back({ 535,1135 });
		PosPlatform.push_back({ 860,748 });
		PosPlatform.push_back({ 553,207 });
		break;
	case 3:
		PosPlatform.push_back({ 535,160 });
		PosPlatform.push_back({ 1605,160 });
		PosPlatform.push_back({ 1605,935 });
		PosPlatform.push_back({ 1605,1135 });
		PosPlatform.push_back({ 1362,549 });
		PosPlatform.push_back({ 1070,695 });
		PosPlatform.push_back({ 777,549 });
		break;
	case 6:
		PosPlatform.push_back({ 2665,549 });
		PosPlatform.push_back({ 2665,403 });
		PosPlatform.push_back({ 2665,209 });
		PosPlatform.push_back({ 532,549 });
		PosPlatform.push_back({ 532,403 });
		PosPlatform.push_back({ 532,209 });
		break;
	case 7:
		PosPlatform.push_back({ 540,550 });
		break;
	case 8:
		PosPlatform.push_back({ 2670,260 });
		PosPlatform.push_back({ 1460,260 });
		PosPlatform.push_back({ 2670,260 });
		PosPlatform.push_back({ 1460,260 });
		break;
	case 9:
		PosPlatform.push_back({ 390,306 });
		PosPlatform.push_back({ 680,306 });
		break;
	case 10:
		PosPlatform.push_back({ 535,1130 });
		PosPlatform.push_back({ 1605,1130 });
		PosPlatform.push_back({ 553,210 });
		PosPlatform.push_back({ 1605,210 });
		PosPlatform.push_back({ 230,355 });
		PosPlatform.push_back({ 230,550 });
		PosPlatform.push_back({ 230,274307 });
		PosPlatform.push_back({ 230,936 });
		PosPlatform.push_back({ 1890,355 });
		PosPlatform.push_back({ 1890,743 });
		PosPlatform.push_back({ 1890,936 });

		PosPlatform.push_back({ 830,791 });
		PosPlatform.push_back({ 1035,791 });
		PosPlatform.push_back({ 1240,791 });
		PosPlatform.push_back({ 830,453 });
		PosPlatform.push_back({ 1035,453 });
		PosPlatform.push_back({ 1240,453 });
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		PosPlatform.push_back({ 210,440 });
		PosPlatform.push_back({ 210,650 });
		break;
	case 14:
		break;
	case 15:
		PosPlatform.push_back({ 1065,265 });
		PosPlatform.push_back({ 535,600 });
		break;
	case 16:
		break;
	case 17:	
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		break;
	}

	return PosPlatform;
}

std::vector<DOUBLE2> LevelManager::CreateTorches()
{
	std::vector<DOUBLE2> posTorch;

	switch (m_CurrentLvl)
	{
	case 0:
		posTorch.push_back({ 560,235 });

		posTorch.push_back({ 855,155 });
		posTorch.push_back({ 855,235 });
		posTorch.push_back({ 855,320 });

		posTorch.push_back({ 1240,155 });
		posTorch.push_back({ 1240,235 });
		posTorch.push_back({ 1240,320 });

		posTorch.push_back({ 1530,235 });
		break;
	case 1:
		posTorch.push_back({ 410,373 });
		posTorch.push_back({ 603,373 });
		posTorch.push_back({ 200,225 });
		posTorch.push_back({ 830,225 });
		break;
	case 2:
		posTorch.push_back({ 270,130 });
		posTorch.push_back({ 270,620 });
		posTorch.push_back({ 810,130 });
		posTorch.push_back({ 810,620 });
		posTorch.push_back({ 810,370 });
		posTorch.push_back({ 810,850 });
		break;
	case 6:
		posTorch.push_back({ 700,130 });
		posTorch.push_back({ 1225,130 });
		posTorch.push_back({ 1815,130 });
		posTorch.push_back({ 2395,130 });
		break;
	case 9:
		posTorch.push_back({ 166,320 });
		posTorch.push_back({ 850,320 });
		break;
	case 10:
		posTorch.push_back({ 310,420 });
		posTorch.push_back({ 310,805 });
		posTorch.push_back({ 1770,420 });
		posTorch.push_back({ 1770,805 });
		posTorch.push_back({ 800,273 });
		posTorch.push_back({ 800,610 });
		posTorch.push_back({ 800,905 });
		posTorch.push_back({ 1281,273 });
		posTorch.push_back({ 1281,610 });
		posTorch.push_back({ 1281,905 });
		posTorch.push_back({ 1040,220 });
		posTorch.push_back({ 1040,565 });
		break;
	case 12:
		posTorch.push_back({ 215,127 });
		posTorch.push_back({ 795,127 });
		break;
	case 13:
		posTorch.push_back({ 505,275 });
		break;
	case 14:
		posTorch.push_back({ 265,225 });
		posTorch.push_back({ 750,225 });
		break;
	case 16:
		posTorch.push_back({ 505,275 });
		posTorch.push_back({ 165,80 });
		posTorch.push_back({ 850,80 });
		break;
	case 17:
		posTorch.push_back({ 285,220 });
		posTorch.push_back({ 625,220 });
		break;
	case 18:
		posTorch.push_back({ 227,127 });
		posTorch.push_back({ 227,321 });
		posTorch.push_back({ 850,321 });
		break;
	default:
		break;
	}
	
	return posTorch;
}
std::vector<DOUBLE2> LevelManager::CreateFireplaces()
{
	std::vector<DOUBLE2> posFirePlace;
	switch (m_CurrentLvl)
	{
	case 0:
		posFirePlace.push_back({ 1485,410 });
		break;
	case 2:
		posFirePlace.push_back({ 418,750 });
		break;
	case 6:
		posFirePlace.push_back({ 2300,455 });
		break;
	case 10:
		posFirePlace.push_back({ 1035,995 });
		break;
	case 12:
		posFirePlace.push_back({ 463,165 });
		break;
	case 13:
		posFirePlace.push_back({ 265,460 });
		posFirePlace.push_back({ 660,460 });
		break;
	case 14:
		posFirePlace.push_back({ 826,458 });
		break;
	case 16:
		posFirePlace.push_back({ 265,455 });
		posFirePlace.push_back({ 655,455 });
		break;
	case 17:
		posFirePlace.push_back({ 412 , 458 });
		break;
	default:
		break;
	} 

	return posFirePlace;
}
std::vector<DOUBLE2> LevelManager::CreateCandleSticks()
{
	//positie midden vanonder
	std::vector<DOUBLE2> posCandleSticks;
	switch (m_CurrentLvl)
	{
	case 0:
		posCandleSticks.push_back({ 790,495 });
		posCandleSticks.push_back({ 945,395 });
		posCandleSticks.push_back({ 1200,395 });
		posCandleSticks.push_back({ 1360,495 });
		break;
	}
	return posCandleSticks;
}



