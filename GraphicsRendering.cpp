#include "GraphicsRendering.h"

size_t sizeT, sizeX;
waveParametres** generalGraphicValues;

CGraphicsRendering::CGraphicsRendering(int sX, int sT, waveParametres** generalGraphicParam)
{
	sizeT = sT;
	sizeX = sX;
	generalGraphicValues = generalGraphicParam;
}


CGraphicsRendering::~CGraphicsRendering(void)
{
}

void SaveImage()
{
	int width(1024), height(840);
	BYTE* pixels = new BYTE[ 3 * width * height];;
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
	FreeImage_Save(FIF_BMP, image, "GRD.bmp", 0);

	FreeImage_Unload(image);
	delete [] pixels;
}

void printString(float X, float Y, char* str)
{
	glRasterPos2f(X,Y);
	glColor3f(0.0f, 0.0f, 1.0f);
	while (*str)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*str);
			str++;
		}
} 

void drawAxis(int xMin, int xMax, int xMid, int yMin, int yMax, int yMid, int dx, int dy)
{
	int a, b, c, d;
	char signatureX[20], signatureY[20];
	glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)xMax,0.0,(GLdouble)yMax);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

	//x
    //glVertex2i(xMid,yMax);
    //glVertex2i(xMid,yMin);

	//y
    //glVertex2i(xMin,yMid);
    //glVertex2i(xMax,yMid);

	//dx
	for (int i(0); i < xMax; i += dx)
	{
		//glVertex2i(i + 2, yMid + 1);
		//glVertex2i(i + 2, yMid - 1);

		//signature
		itoa(i, signatureX, 10);
		printString(i + 3, xMid + 3, (char*)signatureX);
	}

	//dy
	for (int i(0); i < yMax; i += dy)
	{
		//glVertex2i(xMid + 1, i + 2);
		//glVertex2i(xMid - 1, i + 2);	

		//signature
		itoa(i, signatureY, 10);
		printString(i + 3, yMid + 3, (char*)signatureY);
	}

    glEnd();
    glFlush();
}


void drawGeneralGraphic()
{
	if (generalGraphicValues!= NULL)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 0.0);
		for (int i(0); i < 1; i++)
		{
			for (int j(0); j < 20; j++)
			{
				printf("%f %f\n", generalGraphicValues[i][j].sec, generalGraphicValues[i][j].shift);
				glVertex2f(generalGraphicValues[i][j].sec, generalGraphicValues[i][j].shift);
			}
		}
		glEnd();
		glFlush();
		SaveImage();
	}
}


void drawCallback()
{
	drawAxis(0, 400, 200, 0, 300, 150, 2, 2);
	//drawGeneralGraphic();
}


void CGraphicsRendering::renderWindow(int argc, char* argv[])
{	
	glutInit(&argc, argv);//инициализация glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //установка дисплея GLUT_SINGLE означает что мы будем использовать 1 буфер (для 2D графики) а GLUT_RGB означает что мы будем использовать RGB цвета
    glutInitWindowSize(800, 600);//устанавливаем размер окна 
    glutInitWindowPosition(200, 200);//устанавливаем положение окна при запуске
    glutCreateWindow("Wave Statistic");//создаем окно с названием "First program"
    glClearColor(1.0, 1.0, 1.0, 1.0);//очищаем окно в белый цвет
    glMatrixMode(GL_PROJECTION);//устанавливаем матрицу проекции
    glLoadIdentity();//сбрасываем матрицу (устанавливаем нулевую)
    //glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);//устанавливаем ортогональный вид (или как он там называется в скобках значения)
	glutDisplayFunc(drawCallback);
	glutMainLoop();
}

void CGraphicsRendering::drawAllGraphics()
{
	/*glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	drawGeneralGraphic();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
	SaveImage();*/
}