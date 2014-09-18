#include "Structs.h"
#include "freeglut.h"
#include "FreeImage.h"
#include <stdio.h>
#include <cstdlib>

#pragma once
class CGraphicsRendering
{
public:
	CGraphicsRendering* currentInstance;
	CGraphicsRendering(int sizeX, int sizeT, waveParametres** generalGraphicValues);
	~CGraphicsRendering();
	void renderWindow(int argc, char* argv[]);
	void drawAllGraphics();
	void display();
};

