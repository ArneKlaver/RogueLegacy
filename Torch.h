#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------

class Torch 
{
public:
	Torch(DOUBLE2 position);
	virtual ~Torch( );
	// Make objects non-copTorchable
	// https://msdn.microsoft.com/en-us/librarTorch/dn457344.aspx 
	Torch( const Torch& ) = delete;
	Torch& operator=( const Torch& ) = delete;

	void Paint();
	void Tick(double deltaTime);
	MATRIX3X2 GetViewMatrix(DOUBLE2 position);
	void DrawBitmap(int frameMin, int frameMax);
private: 	
	Bitmap* m_BmpTorchPtr = nullptr;

	DOUBLE2 m_Position;
	double m_FrameNr = 0;
};
