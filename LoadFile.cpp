#include "LoadFile.h"


CLoadFile::CLoadFile(void) : numT(0), numX(0)
{
}


CLoadFile::~CLoadFile(void)
{
}

waveParametres** CLoadFile::loadMatFile(std::string pathToFile)
{
	waveParametres *parametres;
	waveParametres param;
	CReadMatFile *matFile = new CReadMatFile(pathToFile.c_str());
	numT = matFile->numToReadT;
	numX = matFile->numToReadX;
	waveParametres **arrParam = new waveParametres*[numX];

	if (!matFile->t.empty() && !matFile->s.empty() && !matFile->x.empty())
	{
		for(int i(0); i < numT; i++)//matFile->numToReadT
		{
			arrParam[i] = new waveParametres[matFile->numToReadX];
			for(int j(0); j < numX; j++)//matFile->numToReadX; j ++)
			{
				param.sec= matFile->x[j];
				param.shift = matFile->s[i][j];
				arrParam[i][j] = param;
			}
		}
	}
	//printLoadedData(arrParam);
	return arrParam;
}

void CLoadFile::printLoadedData(waveParametres **arrParam)
{
	for(int i(0); i < numT; i ++)//matFile->numToReadT
	{
		for(int j(0); j < numX; j ++)//matFile->numToReadX; j ++)
		{
			printf("%f %f\n", arrParam[i][j].sec, arrParam[i][j].shift);
		}
	}
}
