#include "CalculateCrossingWaves.h"

int compare(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

CCalculateCrossingWaves::CCalculateCrossingWaves(size_t sizeT, size_t sizeX, waveParametres** arrParam)
{
	waveParametres first, second;
	waveEntity newWave;
	arrParametres = arrParam;
	this->sizeX = sizeX;
	this->sizeT = sizeT;
	for(int i(0); i < this->sizeT; i++)
	{
		for(int j(0); j < this->sizeX; j++)
		{
			first = arrParametres[i][j];
			second = arrParametres[i][j+1];
			if(first.shift * second.shift < 0)
				{
					typeCrossing type;
					if(first.shift > 0)
					{
						type = ZDC;
					}
					else
					{
						type = ZUC;
					}

					newWave = getSingleWave(i, j, type);
					if(newWave.totalHeight == NULL)
					{
						setHeights();
						return;
					}
					calculatingWaves.push_back(newWave);
					printf("%f %f\n", newWave.amplMin, newWave.amplMax);
				}
		}
	}
}


CCalculateCrossingWaves::~CCalculateCrossingWaves(void)
{
}

waveEntity CCalculateCrossingWaves::getSingleWave(int i, int j, typeCrossing type)
{
	int k = 0;
    waveParametres currentPoint;
    waveEntity wave;
    wave.type = type;

	wave.nullPoint[k] = getNullPoint(arrParametres[i][j], arrParametres[i][j+1]);
    wave.amplMax = 0;
    wave.amplMin = 0;
    currentPoint.sec = wave.nullPoint[k++];
    currentPoint.shift = 0;

	 while(k < 3)
    {
        amplMax(currentPoint, wave);
        amplMin(currentPoint, wave);

		if( j < this->sizeX && (currentPoint.shift * arrParametres[i][j+1].shift < 0))
        {
            wave.nullPoint[k++] = getNullPoint(currentPoint, arrParametres[i][j+1]);
        }
        if(++j >= sizeX && k != 3)
            return waveEntity();
        currentPoint =  arrParametres[i][j];
	 }

	wave.verticalAsummetry = fabs(wave.amplMax / wave.amplMin);
    wave.horizontalAsymmetry = (wave.nullPoint[1] - wave.nullPoint[0])/ (wave.nullPoint[2] - wave.nullPoint[1]);
    wave.totalHeight = fabs(wave.amplMax) + fabs(wave.amplMin);

    if(wave.type == ZDC)
    {
        //in new func
		listHeihtsZDC.push_back(wave.totalHeight);
        listCrestAZDC.push_back(wave.amplMax);
        listThroughAZDC.push_back( - wave.amplMin);
    }
    else
    {
        //in new func
        listHeihtsZUC.push_back(wave.totalHeight);
        listCrestAZUC.push_back(wave.amplMax);
        listThroughAZUC.push_back( - wave.amplMin);
    }

    return wave;
}

float CCalculateCrossingWaves::getNullPoint(waveParametres firstPoint, waveParametres secondPoint)
{
    return ((secondPoint.sec * firstPoint.shift - firstPoint.sec * secondPoint.shift)/(firstPoint.shift - secondPoint.shift));
}

void CCalculateCrossingWaves::amplMax(waveParametres point, waveEntity &wave)
{
    if(point.shift > wave.amplMax)
    {
        wave.amplMax = point.shift;
        wave.ridge = point.sec;
    }
}

void CCalculateCrossingWaves::amplMin(waveParametres point, waveEntity &wave)
{
    if(point.shift < wave.amplMin)
    {
        wave.amplMin = point.shift;
        wave.trough = point.sec;
    }
}

void CCalculateCrossingWaves::setHeights()
{
    heights zuc, zdc;
    zdc.type = ZDC;
    zdc.significantHeight = significantHeights(listHeihtsZDC);
    zdc.heightOneThird = heightOneThird(listHeihtsZDC);
    zdc.sigma = setSigma(listHeihtsZDC, zdc.heightOneThird);
	h.push_back(zdc);

    zuc.type = ZUC;
    zuc.significantHeight = significantHeights(listHeihtsZUC);
    zuc.heightOneThird = heightOneThird(listHeihtsZUC);
    zuc.sigma = setSigma(listHeihtsZUC, zuc.heightOneThird);
    h.push_back(zuc);
}

float CCalculateCrossingWaves::significantHeights(std::vector<float> listHeights)
{
    //wtf
    float tmp = listHeights.size();
	float tmpHeight = 0;
    float heightSignificant = 0;
    for(int i(0); i < listHeights.size(); i++)
    {
		tmpHeight = listHeights.at(i);
        heightSignificant += tmpHeight;
    }

    tmp = heightSignificant/listHeights.size();
    return sqrt(4.04*heightSignificant/listHeights.size());
}

float CCalculateCrossingWaves::heightOneThird(std::vector<float> listHeights)
{
    int size = 0;
    float heightSignificant = 0;
    size = 2 * (listHeights.size()/3);
    float tmp = listHeights.size() - size;
	qsort(&listHeights[0], listHeights.size(), sizeof(float), compare);
    for(int i(size); i < listHeights.size(); i++)
    {
        heightSignificant += listHeights.at(i);
    }
    return (heightSignificant/(listHeights.size() - size));
}

float CCalculateCrossingWaves::setSigma(std::vector<float> listHeights, float sighificiantHeight)
{
    //float tmp = listHeights.count();
    float sigma = 0;
    //if sign heights != 0
    for(int i(0); i < listHeights.size(); i++)
    {
        sigma += sqrt(pow(listHeights.at(i) - sighificiantHeight, 2));
    }
    return (sigma/listHeights.size());
}
