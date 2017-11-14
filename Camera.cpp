//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Camera.h"
#include "Hero.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Camera::Camera(double width, double height): m_WidthCamera(width), m_HeightCamera(height)
{
}

Camera::~Camera()
{
}

void Camera::Paint(Level* levelPtr, Hero* heroPtr)
{
	DOUBLE2 cameraPos;
	TrackHero(cameraPos, heroPtr);
	ClampToLevel(cameraPos, levelPtr);

	RECT2 cameraBounds;
	cameraBounds.bottom = cameraPos.y + (m_HeightCamera / 2);
	cameraBounds.left = cameraPos.x - (m_WidthCamera / 2);
	cameraBounds.right = cameraPos.x + (m_WidthCamera / 2);
	cameraBounds.top = cameraPos.y - (m_HeightCamera / 2);

	GAME_ENGINE->SetColor(COLOR(0, 0, 255));
	GAME_ENGINE->DrawRect(cameraBounds, 2);
}

void Camera::ClampToLevel(DOUBLE2& posRef, Level* levelPtr)
{
	//left
	if (posRef.x < GAME_ENGINE->GetWidth()/2)
	{
		posRef.x = GAME_ENGINE->GetWidth() / 2;
	}
	//right
	if (posRef.x > levelPtr->GetWidth() - GAME_ENGINE->GetWidth() / 2)
	{
		posRef.x = levelPtr->GetWidth() - GAME_ENGINE->GetWidth() / 2;
	}
	//top
	if (posRef.y < GAME_ENGINE->GetHeight()/2)
	{
		posRef.y = GAME_ENGINE->GetHeight() / 2;
	}
	//bot
	if (posRef.y > levelPtr->GetHeight() - GAME_ENGINE->GetHeight()/2)
	{
		posRef.y = levelPtr->GetHeight() - GAME_ENGINE->GetHeight() / 2;
	}
}

void Camera::TrackHero(DOUBLE2& posRef, Hero* heroPtr)
{
	posRef = heroPtr->GetPosition();
}

MATRIX3X2 Camera::GetViewMatrix(Level* levelPtr, Hero* heroPtr)
{
	DOUBLE2 cameraPos;
	TrackHero(cameraPos, heroPtr);
	ClampToLevel(cameraPos, levelPtr);
	cameraPos.x -= m_WidthCamera / 2;
	cameraPos.y -= m_HeightCamera / 2;
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(cameraPos);
	
	return matCamera.Inverse();
}