
#ifndef STRUCTS_H
#define STRUCTS_H

enum typeCrossing { ZDC, ZUC};

struct probability
{
    float H;
    float experP;
    float teorP;
    float crestP;
    float troughP;
};

struct waveEntity
{
    typeCrossing type;
    float amplMax;
    float amplMin;
    float totalHeight;
    float sec;
    float verticalAsummetry;
    float horizontalAsymmetry;
    float nullPoint[3];
    float trough;
    float ridge;
};

struct heights
{
    typeCrossing type;
    float significantHeight;
    float heightOneThird;
    float sigma;
};

struct waveParametres
{
    float sec;
    float shift;
};

#endif