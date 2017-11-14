#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------

class FirePlace 
{
public:
	FirePlace(DOUBLE2 position);
	virtual ~FirePlace( );
	// Make objects non-copFirePlaceable
	// https://msdn.microsoft.com/en-us/librarFirePlace/dn457344.aspx 
	FirePlace( const FirePlace& ) = delete;
	FirePlace& operator=( const FirePlace& ) = delete;

	void Paint();
	void Tick(double deltaTime);
	MATRIX3X2 GetViewMatrix(DOUBLE2 position);
	void DrawFireplace(int frameMin, int frameMax);
private: 
	Bitmap* m_BmpFirePlacePtr;

	DOUBLE2 m_Position;
	double m_FrameNr = 0;
};
