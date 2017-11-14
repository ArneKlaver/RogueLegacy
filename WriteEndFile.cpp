//-----------------------------------------------------------------
// Student data
// Name: Klaver Arne
// Group: 1DAE15
//-----------------------------------------------------------------
#include "stdafx.h"		
#include "WriteEndFile.h"
#include <iostream>
#include <fstream>
#include <ctime>

//#define GAME_ENGINE (GameEngine::GetSingleton())

WriteEndFile::WriteEndFile(double m_GameTimeTotal)
{
	//getting time
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	localtime_s(&nowLocal, &now);

	//open file
	std::ofstream filestream;
	filestream.open("Resources/TextFiles/GameSessions.txt" , std::ios::app);

	//write to fille
	filestream << "<Sesion>" << std::endl;
		filestream << "\t<Start>" << std::endl;
			filestream << "\t\t<Date>" << std::setfill('0') << std::setw(4) << 1900 + nowLocal.tm_year << ":"
									   << std::setfill('0') << std::setw(2) << 1 + nowLocal.tm_mon << ":" 
									   << std::setfill('0') << std::setw(2) << nowLocal.tm_mday << "</Date>" << std::endl;
			filestream <<" \t\t<Time>" << std::setfill('0') << std::setw(2) << nowLocal.tm_hour << ":" 
									   << std::setfill('0') << std::setw(2) << nowLocal.tm_min << ":" 
									   << std::setfill('0') << std::setw(2) << nowLocal.tm_sec << "</Time>" << std::endl;
			filestream << " \t\t<Health>" << "" << "</Health>" << std::endl;
		filestream << "\t</Start>" << std::endl;

		filestream.close();
}

WriteEndFile::~WriteEndFile()
{
	//getting time
	time_t now;
	struct tm nowLocal;
	now = time(NULL);
	localtime_s(&nowLocal, &now);

	//open file
	std::ofstream filestream;
	filestream.open("Resources/TextFiles/GameSessions.txt", std::ios::app);

	filestream << "\t<End>" << std::endl;
	filestream << "\t\t<Date>" << std::setfill('0') << std::setw(4) << 1900 + nowLocal.tm_year << ":"
		<< std::setfill('0') << std::setw(2) << 1 + nowLocal.tm_mon << ":"
		<< std::setfill('0') << std::setw(2) << nowLocal.tm_mday << "</Date>" << std::endl;
	filestream << " \t\t<Time>" << std::setfill('0') << std::setw(2) << nowLocal.tm_hour << ":"
		<< std::setfill('0') << std::setw(2) << nowLocal.tm_min << ":"
		<< std::setfill('0') << std::setw(2) << nowLocal.tm_sec << "</Time>" << std::endl;
	filestream << " \t\t<Health>" << "" << "</Health>" << std::endl;
	filestream << "\t</End>" << std::endl;
	filestream << "</Sesion>" << std::endl;

	filestream.close();
}

void WriteEndFile::GetText()
{
	//open file
	std::ifstream filestream;
	filestream.open("Resources/TextFiles/GameSessions.txt");

	std::string readLine;
	std::getline(filestream, readLine);
	std::size_t idxFrom = readLine.find("<date>");
	idxFrom += 6;

	std::size_t idTill = readLine.find("<\date>");

	std::string test ;
	test = readLine.substr(idxFrom, idTill - idxFrom);
	
}