//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Level.h"
#include "Camera.h"
#include "Torch.h"
#include "FirePlace.h"
#include "Candlestick.h"
#include "LevelManager.h"
#include "Platform.h"


#define GAME_ENGINE (GameEngine::GetSingleton())

Level::Level(int LevelNumber , std::vector<doorsPosAngle>DoorPositions, std::vector<DOUBLE2> PosPlatform
	, std::vector<DOUBLE2> torchPositions , std::vector<DOUBLE2> firePlacePositions, std::vector<DOUBLE2> CandleStickPosition)
	: m_LvlNumber(LevelNumber)
{
	m_BmpMapPtr = new Bitmap(String("Resources/Rooms/room") + String(LevelNumber) + String(".png"));

	m_ActFloorPtr = new PhysicsActor(DOUBLE2{ 0,0 }, 0, BodyType::STATIC);
	m_ActFloorPtr->AddSVGFixture(String("Resources/Rooms/Floor") + String(LevelNumber) + String(".svg"), 0 ,0);

	m_ActRoofPtr = new PhysicsActor(DOUBLE2{ 0,0 }, 0, BodyType::STATIC);
	m_ActRoofPtr->AddSVGFixture(String("Resources/Rooms/Roof") + String(LevelNumber) + String(".svg"), 0, 0);

	m_CreateEnemys = true;//create enemys
	CreateDoors(DoorPositions);
	// create Platforms
	for (DOUBLE2 temp : PosPlatform)
	{
		m_ArrPlatformPtr.push_back(new Platform(temp));
	}
	//create torches
	for (DOUBLE2 temp : torchPositions)
	{
		m_ArrTorchesPtr.push_back(new Torch(temp));
	}
	//create fireplace
	for (DOUBLE2 temp : firePlacePositions)
	{
		m_ArrFirePlacesPtr.push_back(new FirePlace(temp));
	}
	//create candleStick
	for (DOUBLE2 temp : CandleStickPosition)
	{
		m_ArrCandleSticksPtr.push_back(new CandleStick(temp , LevelNumber));
	}
}

Level::~Level()
{
	delete m_BmpMapPtr;
	m_BmpMapPtr = nullptr;
	delete m_ActFloorPtr;
	m_ActFloorPtr = nullptr;
	delete m_ActRoofPtr;
	m_ActRoofPtr = nullptr;
	for (PhysicsActor* temp : m_ArrActDoorsPtr)
	{
		delete temp;
		temp = nullptr;
	}
	for (Platform* temp : m_ArrPlatformPtr)
	{
		delete temp;
		temp = nullptr;
	}
	for (Torch* temp : m_ArrTorchesPtr)
	{
		delete temp;
		temp = nullptr;
	}
	for (FirePlace* temp : m_ArrFirePlacesPtr)
	{
		delete temp;
		temp = nullptr;
	}
	for (CandleStick* temp : m_ArrCandleSticksPtr)
	{
		delete temp;
		temp = nullptr;
	}
}

void Level::Tick(double deltaTime , PickUpManager* m_PickUpManager, PhysicsActor* actWeaponHeroPtr , PhysicsActor* actHeroPtr)
{
	m_CreateEnemys = false;
	for (Platform* temp : m_ArrPlatformPtr)
	{
		temp->Tick(actHeroPtr);
	}
	for (Torch* temp : m_ArrTorchesPtr)
	{
		temp->Tick(deltaTime);
	}
	for (FirePlace* temp : m_ArrFirePlacesPtr)
	{
		temp->Tick(deltaTime);
	}
	//delete breakable object if destroyed
	//only execute tick if not nullptr
	for (unsigned int i = 0; i < m_ArrCandleSticksPtr.size(); i++)
	{
		if (m_ArrCandleSticksPtr[i] != nullptr)
		{
			m_ArrCandleSticksPtr[i]->Tick(deltaTime , actWeaponHeroPtr );
			if (m_ArrCandleSticksPtr[i]->GetDestroyed())
			{
				m_PickUpManager->CreateGoldCoin(m_LvlNumber , m_ArrCandleSticksPtr[i]->GetPosition());
				m_ArrCandleSticksPtr[i]->~CandleStick();
				delete m_ArrCandleSticksPtr[i];
				m_ArrCandleSticksPtr[i] = nullptr;
			}
		}
	}
}

void Level::Paint()
{
	GAME_ENGINE->DrawBitmap(m_BmpMapPtr);
	for (Platform* temp : m_ArrPlatformPtr)
	{
		temp->Paint();
	}
	for (Torch* temp : m_ArrTorchesPtr)
	{
		temp->Paint();
	}
	for (FirePlace* temp : m_ArrFirePlacesPtr)
	{
		temp->Paint();
	}
	for (CandleStick* temp : m_ArrCandleSticksPtr)
	{
		if (temp != nullptr)
		{
			temp->Paint();
		}
	}
}
double Level::GetWidth()
{
	return m_BmpMapPtr->GetWidth();
}
double Level::GetHeight()
{
	return m_BmpMapPtr->GetHeight();
}

bool Level::IsOnGround(PhysicsActor* actOtherPtr)
{	
	for (Platform* temp : m_ArrPlatformPtr)
	{
		if (temp->IsOnGround(actOtherPtr) && actOtherPtr->GetLinearVelocity().y >=0)
		{
			return true;
		}
	}
	if (m_ActFloorPtr->IsOverlapping(actOtherPtr))
	{
		return true;
	}
	return false;

}
bool Level::HitWall(PhysicsActor* actOtherPtr)
{
	if (m_ActFloorPtr->IsOverlapping(actOtherPtr))
	{
		return true;
	}
	if (m_ActRoofPtr->IsOverlapping(actOtherPtr))
	{
		return true;
	}
	return false;
}

int Level::IsDoorHit(PhysicsActor* actOtherPtr1)
{
	for (unsigned int i = 0; i < m_ArrActDoorsPtr.size() ; i++)
	{
		if (m_ArrActDoorsPtr[i]->IsOverlapping(actOtherPtr1))
		{
			return i;
		}
	}
   return -1;
}

void Level::CreateDoors(std::vector<doorsPosAngle> doorPositions )
{
	switch (doorPositions.size())
	{
	case 5:
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[0].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[0]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[0]->SetAngle(doorPositions[0].angle);
		m_ArrActDoorsPtr[0]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[1].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[1]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[1]->SetAngle(doorPositions[1].angle);
		m_ArrActDoorsPtr[1]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[2].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[2]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[2]->SetAngle(doorPositions[2].angle);
		m_ArrActDoorsPtr[2]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[3].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[3]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[3]->SetAngle(doorPositions[3].angle);
		m_ArrActDoorsPtr[3]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[3].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[4]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[4]->SetAngle(doorPositions[3].angle);
		m_ArrActDoorsPtr[4]->SetSensor(true);
		break;
	case 4:
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[0].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[0]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[0]->SetAngle(doorPositions[0].angle);
		m_ArrActDoorsPtr[0]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[1].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[1]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[1]->SetAngle(doorPositions[1].angle);
		m_ArrActDoorsPtr[1]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[2].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[2]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[2]->SetAngle(doorPositions[2].angle);
		m_ArrActDoorsPtr[2]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[3].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[3]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[3]->SetAngle(doorPositions[3].angle);
		m_ArrActDoorsPtr[3]->SetSensor(true);
		break;
	case 3:
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[0].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[0]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[0]->SetAngle(doorPositions[0].angle);
		m_ArrActDoorsPtr[0]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[1].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[1]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[1]->SetAngle(doorPositions[1].angle);
		m_ArrActDoorsPtr[1]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[2].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[2]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[2]->SetAngle(doorPositions[2].angle);
		m_ArrActDoorsPtr[2]->SetSensor(true);
		break;
	case 2:
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[0].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[0]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[0]->SetAngle(doorPositions[0].angle);
		m_ArrActDoorsPtr[0]->SetSensor(true);
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[1].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[1]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[1]->SetAngle(doorPositions[1].angle);
		m_ArrActDoorsPtr[1]->SetSensor(true);
		break;
	case 1:
		m_ArrActDoorsPtr.push_back(new PhysicsActor(doorPositions[0].pos, 0, BodyType::STATIC));
		m_ArrActDoorsPtr[0]->AddBoxFixture(20, 200);
		m_ArrActDoorsPtr[0]->SetAngle(doorPositions[0].angle);
		m_ArrActDoorsPtr[0]->SetSensor(true);
	default:
		break;
	}
}

void Level::m_DeactivateActor(bool active)
{
	m_ActFloorPtr->SetActive(active);
	m_ActRoofPtr->SetActive(active);
	for (PhysicsActor* temp : m_ArrActDoorsPtr)
	{
		temp->SetActive(active);
	}
	for (Platform* temp : m_ArrPlatformPtr)
	{
		temp->GetActor()->SetActive(active);
	}
	for (CandleStick* temp : m_ArrCandleSticksPtr)
	{
		if (temp != nullptr)
		{
			temp->GetActor()->SetActive(active);
		}
	}
}

int Level::GetLevelNumber() 
{
	return m_LvlNumber;
}

//Desctructables?

bool Level::GetCreateEnemys()
{
	return m_CreateEnemys;
}