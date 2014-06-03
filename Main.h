#pragma once
#include <mat.h>
#include "LoadFile.h"
#include "CalculateCrossingWaves.h"
#include "Structs.h"
#include "GraphicsRendering.h"

class CMain
{
	size_t sizeT, sizeX;
public:
	CMain(void);
	~CMain(void);
	bool LoadFile(const char *file);
	size_t getSizeT(){return sizeT;}
	size_t getSizeX(){return sizeX;}
	waveParametres ** arrParametres;
};

