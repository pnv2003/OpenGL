// Bai3.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "math.h"
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "lab.h"

using namespace std;

namespace Lab2 {

	int		screenWidth = 600;
	int		screenHeight = 300;

	Mesh	tetrahedron;
	Mesh	cube;
	Mesh	cuboid;
	Mesh	cylinder;
	Mesh	cylinderWithHole;
	Mesh	vFrame;
	Mesh	hFrame;
	Mesh	wheel;
	Mesh	slider;

	int		nChoice = 1;

	void drawAxis()
	{
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
		glEnd();
	}
	void myDisplay()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			4.5, 4, 4, 
			//0, 4, 0,
			0, 0, 0, 
			0, 1, 0
		);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, screenWidth / 2, screenHeight);

		drawAxis();

		glColor3f(0, 0, 0);
		if (nChoice == 1)
			tetrahedron.DrawWireframe();
		else if (nChoice == 2)
			cube.DrawWireframe();
		else if (nChoice == 3)
			cuboid.DrawWireframe();
		else if (nChoice == 4)
			cylinder.DrawWireframe();
		else if (nChoice == 5)
			cylinderWithHole.DrawWireframe();
		else if (nChoice == 6)
			vFrame.DrawWireframe();
		else if (nChoice == 7)
			hFrame.DrawWireframe();
		else if (nChoice == 8)
			wheel.DrawWireframe();
		else if (nChoice == 9)
			slider.DrawWireframe();

		glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

		drawAxis();
		if (nChoice == 1)
			tetrahedron.DrawColor();
		else if (nChoice == 2)
			cube.DrawColor();
		else if (nChoice == 3)
			cuboid.DrawColor();
		else if (nChoice == 4)
			cylinder.DrawColor();
		else if (nChoice == 5)
			cylinderWithHole.DrawColor();
		else if (nChoice == 6)
			vFrame.DrawColor();
		else if (nChoice == 7)
			hFrame.DrawColor();
		else if (nChoice == 8)
			wheel.DrawColor();
		else if (nChoice == 9)
			slider.DrawColor();

		//glFlush();
		glutSwapBuffers();
	}

	void myInit()
	{
		float	fHalfSize = 4;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	}

	int main(int argc, char* argv[])
	{
		cout << "1. Tetrahedron" << endl;
		cout << "2. Cube" << endl;
		cout << "3. Cuboid" << endl;
		cout << "4. Cylinder" << endl;
		cout << "5. Cylinder with hole" << endl;
		cout << "6. Vertical frame" << endl;
		cout << "7. Horizontal frame" << endl;
		cout << "8. Wheel" << endl;
		cout << "9. Slider" << endl;
		cout << "Input the choice: " << endl;
		cin >> nChoice;

		//glutInit(&argc, (char**)argv); //initialize the tool kit
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
		glutInitWindowSize(screenWidth, screenHeight); //set window size
		glutInitWindowPosition(100, 100); // set window position on screen
		glutCreateWindow("Lab 2"); // open the screen window

		tetrahedron.CreateTetrahedron();
		cube.CreateCube(1);
		cuboid.CreateCuboid(1, 2, 3);
		cylinder.CreateCylinder(10, 2, 1);
		cylinderWithHole.CreateCylinderWithHole(10, 2, 1, 0.5);
		vFrame.CreateVerticalFrame(1, 2, 4, 1, 1, 2);
		hFrame.CreateHorizontalFrame(1, 2, 4, 1, 2);
		wheel.CreateWheel(0.2, 0.7, 3, 3.5, 5, 0.5, 1, 100);
		slider.CreateSlider(3, 4, 7, 1);

		myInit();
		glutDisplayFunc(myDisplay);

		glutMainLoop();
		return 0;
	}

}

