#pragma once
#include <string>
#include "ReadMatFile.h"
#include "Structs.h"


class CLoadFile
{
	unsigned int numT;
	unsigned int numX;
	void printLoadedData(waveParametres **arrParam);
public:
	CLoadFile(void);
	~CLoadFile(void);
	waveParametres** loadMatFile(std::string str);
	size_t getSizeT(){return numT;}
	size_t getSizeX(){return numX;}
};

