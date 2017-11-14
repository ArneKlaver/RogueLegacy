//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "Torch.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Torch::Torch(DOUBLE2 position): m_Position(position)
{
	m_BmpTorchPtr = new Bitmap(String("Resources/Torch.png"));
}

Torch::~Torch()
{
	delete m_BmpTorchPtr;
	m_BmpTorchPtr = nullptr;
}
void Torch::Paint()
{
	GAME_ENGINE->SetWorldMatrix(GetViewMatrix(m_Position));
	DrawBitmap(0, 4);
	//reset view
	GAME_ENGINE->SetWorldMatrix(MATRIX3X2::CreateIdentityMatrix());
}
void Torch::Tick(double deltaTime)
{
	m_FrameNr += deltaTime * 8;
}
MATRIX3X2 Torch::GetViewMatrix(DOUBLE2 position)
{
	MATRIX3X2 matCamera;
	matCamera.SetAsTranslate(position);

	return matCamera;
}

void Torch::DrawBitmap(int frameMin, int frameMax)
{
	int frameX = 4;// number of images horizontal
	int frameY = 1;// number of images vertical

	int frameNr = (int)m_FrameNr;
	frameNr = (frameNr % (frameMax - frameMin)) + frameMin;
	double width = m_BmpTorchPtr->GetWidth();
	double height = m_BmpTorchPtr->GetHeight();
	GAME_ENGINE->DrawBitmap(m_BmpTorchPtr,
	{ width / frameX * (frameNr % frameX), height / frameY * (frameNr / frameX) ,  width / frameX + width / frameX * (frameNr % frameX) ,  (height / frameY) + height / frameY * (frameNr / frameX) });
}