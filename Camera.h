#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
class Level;
class Hero;
class Camera 
{
public:

	Camera(double width, double height);
	virtual ~Camera( );
	// Make objects non-copCameraable
	// https://msdn.microsoft.com/en-us/librarCamera/dn457344.aspx 
	Camera( const Camera& ) = delete;
	Camera& operator=( const Camera& ) = delete;

	void Paint(Level* levelPtr, Hero* avatarPtr);
	MATRIX3X2 GetViewMatrix(Level* levelPtr, Hero* HeroPtr);

private:

	void ClampToLevel(DOUBLE2& posRef, Level* levelptr);
	void TrackHero(DOUBLE2& posRef, Hero* avatarPtr);

	double m_WidthCamera;
	double m_HeightCamera;

};
