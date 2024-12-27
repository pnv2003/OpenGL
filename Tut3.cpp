#include <cmath>
#include <iostream>
#include <ctime>
#include "tutorial.h"
using namespace std;

#define PI 3.1415926
#define DEG2RAD(x) (x*PI)/180.0f

#define CUBOID_HEIGHT 0.10

namespace Tut3 {
	int problem = 1;

	void myInit() {
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-10, 10, -10, 10);
	}

	void myInit3D() {
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 1, 1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	}

	void drawAxis() {
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

	void drawPolygon() {
		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		//glVertex3f()
		glEnd();
	}

	void rotatePolygon(float angle) {

	}

	void cuboid() {
		float vertices[8][3] = {
			{ 0, 0, 0 },
			{ 2, 0, 0 },
			{ 2, 0, 2 },
			{ 0, 0, 2 },
			{ 0, CUBOID_HEIGHT, 0 },
			{ 2, CUBOID_HEIGHT, 0 },
			{ 2, CUBOID_HEIGHT, 2 },
			{ 0, CUBOID_HEIGHT, 2 }
		};
		float line[12][2] = {
			{0, 1}, {1, 2}, {2, 3}, {3, 0},
			{4, 5}, {5, 6}, {6, 7}, {7, 4}
		};
		int i, p1, p2;
		glBegin(GL_LINES);
		for (i = 0; i < 12; i++) {
			p1 = line[i][0];
			p2 = line[i][1];
			glVertex3f(vertices[p1][0], vertices[p1][1], vertices[p1][2]);
			glVertex3f(vertices[p2][0], vertices[p2][1], vertices[p2][2]);
		}
		glEnd();
	}

	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT);

		switch (problem) {
		case 3: {
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glTranslatef(3, 2, 1);
			glScalef(3, 3, 4);
			glRotatef(60, 0, 0, 1);
			glRotatef(30, 0, 1, 0);

			// check the matrix
			float m[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, m);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cout << m[i * 4 + j] << " ";
				}
				cout << endl;
			}

			glBegin(GL_TRIANGLES);
			glVertex3f(-1, 0, 1);
			glVertex3f(1, 0, -1);
			glVertex3f(0, 0, 1);
			glEnd();
			break;
		}
		case 4: {

		}
		case 5: {

		}
		case 6: {
			drawAxis();

			float ROTATE_ANGLE = 10;
			float SCALE_RATIO = 0.8;

			cuboid();
			break;
		}
		default:
			break;
		}

		glFlush();
	}

	void myKeyboard(unsigned char key, int x, int y) {
		problem = key - '0';
		if (problem == 3)
			myInit();
		else
			myInit3D();
		glutPostRedisplay();
	}

	void main() {
		cout << "Select a problem to display:\n";
		cout << "3. Problem 3\n";
		cout << "4. Problem 4\n";
		cout << "5. Problem 5\n";
		cout << "6. Problem 6\n";

		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(600, 600);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Tut3");
		myInit();
		glutDisplayFunc(myDisplay);
		glutKeyboardFunc(myKeyboard);
		glutMainLoop();
	}
}