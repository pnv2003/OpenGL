#include "math.h"
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "lab.h"

using namespace std;

namespace LabMesh {
	int		screenWidth = 1000;
	int		screenHeight = 500;

	float	angle = 0;

	int		nChoice = 0;

	Mesh    cube;
	Mesh	shape1;
	Mesh    shape2;

	void drawAxis()
	{
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);//x - red
		glVertex3f(4, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y - green
		glVertex3f(0, 4, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);//z - blue
		glVertex3f(0, 0, 4);
		glEnd();
	}
	void myDisplay()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(4.5, 4, 4, 0, 0, 0, 0, 1, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		////////////////////////////////////////////////////
		glViewport(0, 0, screenWidth / 2, screenHeight);

		glPushMatrix();
		drawAxis();

		glRotatef(angle, 0, 1, 0);

		glColor3f(0, 0, 0);
		if (nChoice == 0)
			cube.DrawWireframe();
		else if (nChoice == 1)
			shape1.DrawWireframe();
		else if (nChoice == 2)
			shape2.DrawWireframe();

		/////////////////////////////////////////////////////////////
		glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

		glPopMatrix();
		drawAxis();
		glRotatef(angle, 0, 1, 0);

		if (nChoice == 0)
			cube.DrawColor();
		else if (nChoice == 1)
			shape1.DrawColor();
		else if (nChoice == 2)
			shape2.DrawColor();

		glFlush();
		glutSwapBuffers();
	}
	void mySpecialFunc(int key, int x, int y)
	{
		if (key == GLUT_KEY_LEFT)
			angle = angle + 5;
		else if (key == GLUT_KEY_RIGHT)
			angle = angle - 5;
		glutPostRedisplay();
	}
	void myKeyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case '0':
			nChoice = 0;
			break;
		case '1':
			nChoice = 1;
			break;
		case '2':
			nChoice = 2;
			break;
		}
		glutPostRedisplay();
	}
	void myInit()
	{
		float	fHalfSize = 5;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	}


	int main(int argc, char* argv[])
	{
		cout << "Press -> or <- to rotate" << endl;

		cout << "0. Cube" << endl;
		cout << "1. Shape 1 (cone)" << endl;
		cout << "2. Shape 2 (hollow cube)" << endl;

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
		glutInitWindowSize(screenWidth, screenHeight); //set window size
		glutInitWindowPosition(100, 100); // set window position on screen
		glutCreateWindow("Lab Mesh"); // open the screen window

		myInit();
		glutKeyboardFunc(myKeyboard);
		glutDisplayFunc(myDisplay);
		glutSpecialFunc(mySpecialFunc);

		cube.CreateCube(2);
		shape1.CreateCone(10, 4, 1);
		shape2.CreateHollowCube(32, 5, 1);

		glutMainLoop();
		return 0;
	}

}