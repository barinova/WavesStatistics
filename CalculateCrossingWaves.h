#pragma once
#ifndef CALCULATECROSSINGWAVES_H
#define CALCULATECROSSINGWAVES_H

#include <vector>
#include "Structs.h"
#include <stdlib.h>

class CCalculateCrossingWaves
{
	waveEntity getSingleWave(int i, int j, typeCrossing type);
	float getNullPoint(waveParametres fistPoint, waveParametres secondPoint);
    void amplMin(waveParametres point, waveEntity &wave);
    void amplMax(waveParametres point, waveEntity &wave);
	float significantHeights(std::vector<float> listHeights);
    float heightOneThird(std::vector<float> listHeights);
    float setSigma(std::vector<float> listHeights, float sighificiantHeight);
    void setHeights();
    void setListProbabilities(std::vector<float> listHeights, std::vector<float>listCrestA,
                              std::vector<float> ListThroughA, typeCrossing type);
	size_t sizeX,sizeT;
	std::vector<heights> h;
	std::vector<float> listHeihtsZDC;
    std::vector<float> listHeihtsZUC;
    std::vector<float> listCrestAZDC;
    std::vector<float> listCrestAZUC;
    std::vector<float> listThroughAZDC;
    std::vector<float> listThroughAZUC;
    std::vector<probability> listProbabilitiesZDC;
    std::vector<probability> listProbabilitiesZUC;
public:
	CCalculateCrossingWaves(size_t sizeT, size_t sizeX, waveParametres** arrParametres);
	~CCalculateCrossingWaves(void);
	waveParametres** arrParametres;
    std::vector<waveEntity> calculatingWaves;
};

#endif
