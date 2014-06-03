#include "Main.h"


CMain::CMain(void)
{
}


CMain::~CMain(void)
{
}

bool CMain::LoadFile(const char *file)
{
	CLoadFile loadedFile;
	arrParametres = loadedFile.loadMatFile(file);
	sizeT = loadedFile.getSizeT();
	sizeX = loadedFile.getSizeX();
	return ((arrParametres) ?  true : false);
}

int main(int argc, char* argv[])
{
	const char *file = "GA_LINEAR_001.mat";
	CMain main;
	bool fileLoaded = false;
	fileLoaded = main.LoadFile(file);
	if (fileLoaded)
	{
		int sizeT, sizeX;
		sizeT = main.getSizeT();
		sizeX = main.getSizeX();
		waveParametres** arrParam = main.arrParametres;
		CCalculateCrossingWaves calculateWaves(sizeT, sizeX, arrParam);
		CGraphicsRendering graphicsRender;
		graphicsRender.setSizeT(sizeT);
		graphicsRender.setSizeX(sizeX);
		graphicsRender.setArrParam(arrParam);
		graphicsRender.renderGeneralGraph(NULL, NULL);
	}
	return 0;
}