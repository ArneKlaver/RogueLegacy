#pragma once
//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------

class WriteEndFile 
{
public:
	WriteEndFile(double m_GameTimeTotal);
	virtual ~WriteEndFile( );
	// Make objects non-copWriteEndFileable
	// https://msdn.microsoft.com/en-us/librarWriteEndFile/dn457344.aspx 
	WriteEndFile( const WriteEndFile& ) = delete;
	WriteEndFile& operator=( const WriteEndFile& ) = delete;
	void WriteEndFile::GetText();

private: 

};
