#include "GraphicsRendering.h"


CGraphicsRendering::CGraphicsRendering(void)
{

}


CGraphicsRendering::~CGraphicsRendering(void)
{
}

void CGraphicsRendering::renderGeneralGraph(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(640,480);
    glutCreateWindow("GRD");
	glutDisplayFunc(CGraphicsRendering::drawCallback);
}


void CGraphicsRendering::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	for (int i(0); i < 1; i++)
    {
        for (int j(0); j < sizeX; j++)
        {
			glColor3ub(200, 20, 0);
			glBegin(GL_POINTS);
			glVertex2f(arrParam[i][j].sec,arrParam[i][j].shift);
			glEnd();
		}
	  }
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
	SaveImage();

}

void CGraphicsRendering::SaveImage()
{
	int width(1024), height(840);
	BYTE* pixels = new BYTE[ 3 * width * height];;
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
	FreeImage_Save(FIF_BMP, image, "C:/GRD.bmp", 0);

	FreeImage_Unload(image);
	delete [] pixels;
}