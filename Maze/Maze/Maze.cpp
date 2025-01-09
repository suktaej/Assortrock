#include "Maze.h"

FMaze::FMaze()
{
}

FMaze::~FMaze()
{
	if (nullptr != m_MazeArray)
	{
		for (int i = 0;i < m_Ysize;i++)
		{
			delete[] m_MazeArray[i];
		}
		delete[] m_MazeArray;
	}

	if (nullptr != m_Buffer)
		delete[] m_Buffer;
}

bool FMaze::Init()
{
	FILE* File = nullptr;

	fopen_s(&File, "Maze1.txt", "rt");
	
	if (!File)
		return false;

	char Line[64] = {};

	fgets(Line, 64, File);
	
	char* YString = nullptr;
	char* XString = strtok_s(Line, ", ", &YString);

	m_Ysize = atoi(YString);
	m_Xsize = atoi(XString);

	m_MazeArray = new ETileType * [m_Ysize];
	m_Buffer = new char[(m_Xsize + 1) * m_Ysize + 1];
	memset(m_Buffer, 0, sizeof(char) * ((m_Xsize + 1) * m_Ysize + 1));

	for (int i = 0;i < m_Ysize;i++)
	{
		m_MazeArray[i] = new ETileType[m_Xsize];
		fgets(Line, 64, File);

		for (int j = 0;j < m_Xsize;j++)
			m_MazeArray[i][j] = (ETileType)(Line[j] - '0');
	}

	fclose(File);
	return true;
}


void FMaze::Run()
{
	Reset();
	system("cls");
	std::cout << m_Buffer;
}

void FMaze::Reset()
{
	memset(m_Buffer, 0, sizeof(char) * ((m_Xsize + 1) * m_Ysize + 1));

	for (int i = 0;i < m_Ysize;i++)
	{
		for (int j = 0;j < m_Xsize;j++)
		{
			int BufferIndex = i * (m_Xsize + 1) + j;

			switch (m_MazeArray[i][j])
			{
			case ETileType::Road:
				m_Buffer[BufferIndex] = ' ';
				break;
			case ETileType::Wall:
				m_Buffer[BufferIndex] = '#';
				break;
			case ETileType::Start:
				m_StartPos.X = j;
				m_StartPos.Y = i;
				m_Buffer[BufferIndex] = 'S';
				break;
			case ETileType::Goal:
				m_EndPos.X = j;
				m_EndPos.Y = i;
				m_Buffer[BufferIndex] = 'G';
				break;
			case ETileType::Item:
				break;
			case ETileType::Pitfall:
				break;
			case ETileType::HP:
				break;
			}
		}
		int BufferIndex = i * (m_Xsize + 1) + m_Xsize;
		m_Buffer[BufferIndex] = '\n';
	}
}
