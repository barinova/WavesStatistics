#include "Structs.h"
#include <glut.h> 
#include "Dist\FreeImage.h"

#pragma once
class CGraphicsRendering
{
	size_t sizeT, sizeX;
	waveParametres** arrParam;
	static CGraphicsRendering* currentInstance;

	static void drawCallback()
	{
		currentInstance->Draw();
	}

public:
	void setSizeT(size_t T) {sizeT = T;};
	void setSizeX(size_t X) {sizeX = X;};
	void setArrParam(waveParametres** arrParam) {this->arrParam = arrParam;};
	CGraphicsRendering(void);
	~CGraphicsRendering(void);
	void renderGeneralGraph(int argc, char* argv[]);
	void Draw();
	void SaveImage();
};

