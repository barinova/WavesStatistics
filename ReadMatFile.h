#include <vector>
#include <mat.h>

#pragma once
class CReadMatFile
{
public:
	public:
	std::vector<double> t, x;
	std::vector<std::vector<double>> s;
	int	numToReadT, numToReadX;

	CReadMatFile(static const char *file);
	~CReadMatFile(void);
};

