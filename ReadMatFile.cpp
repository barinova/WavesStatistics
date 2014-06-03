#include "ReadMatFile.h"

static MATFile		*pmat;
static const char	**dir;
static mxArray		*_t, *_s, *_x;
static int			ndir;
static int			i;
static double		*prT, *prX, *prS;

CReadMatFile::CReadMatFile(static const char *file)
{
	printf("Reading file %s...\n\n", file);
	pmat = matOpen(file, "r");
	if (pmat == NULL) {
		printf("Error opening file %s\n", file);
		return;
	}

	dir = (const char **)matGetDir(pmat, &ndir); 
	if (dir == NULL) {
		printf("Error reading directory of file %s\n", file);
		return;
	} else {
		printf("Directory of %s:\n", file);
		for (i=0; i < ndir; i++)
			printf("%s\n",dir[i]);
	}

	if (strcmp(dir[0],"t") != 0 && strcmp(dir[1],"x") != 0  && strcmp(dir[2],"s") != 0) {
		printf("%s contains %s, %s, %s, but not %s\n", file, dir[0], dir[1], dir[2], "t || x || s");
	} else {
		printf("Found vector: %s\n", "t || x || s");
	}

	
	_t = matGetVariable(pmat, "t");
	_x = matGetVariable(pmat, "x");
	_s = matGetVariable(pmat,"s");
	if (_t == NULL || _s == NULL || _x == NULL) {
		printf("Error reading %s, %s, %s in %s\n", dir[0], dir[1], dir[2], file);
		return;
    }
	
	numToReadT = mxGetNumberOfElements(_t);
	numToReadX = mxGetNumberOfElements(_x);
	prT = mxGetPr(_t);
	prX =  mxGetPr(_x);
	prS = mxGetPr(_s);

	printf("According to its contents, array %s has %d elements\n", dir[0], numToReadT);

	for (i = 0; i < numToReadT; i++) 
	{
		printf("%f\n", prT[i]);
		t.push_back(prT[i]);
	}

	for (i = 0; i < numToReadX; i++) 
	{
		printf("%f\n", prX[i]);
		x.push_back(prX[i]);
	}

	//cause the matrix need to transpose
	//mb parse there???
	std::vector<double> tmp;
	for (i = 0; i < numToReadX; i++) 
	{
		int k = numToReadX;
		tmp.clear();
		for (int j(0); j < numToReadT; j++) 
		{
			//printf("%f\n", prS[i]);
			tmp.push_back(prS[i+k*j]);
		}
		s.push_back(tmp);
	}

	mxFree(dir);
	mxDestroyArray(_t);
	mxDestroyArray(_s);
	mxDestroyArray(_x);


	if (matClose(pmat) != 0) 
	{
		printf("Error closing file %s\n",file);
	}
}


CReadMatFile::~CReadMatFile(void)
{
}
