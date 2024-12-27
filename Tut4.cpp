#include <iostream>
#include "tutorial.h"
using namespace std;

#define PI 3.1415926
#define DEG2RAD(x) (x*PI)/180.0f

namespace Tut4 {
	int problem = 4;

	void printMatrix(float* m) {
		cout << "Matrix:" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << m[i + j * 4] << " ";
			}
			cout << endl;
		}
	}

	void myInit() {
		glClearColor(1.0, 1.0, 1.0, 0.0);
		
		switch (problem) {
		case 4:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(
				4, 4, 4,
				8, 8, 8,
				1, 0, -1
			);
			// check the matrix
			float m[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, m);
			printMatrix(m);

			// check the default orthographic projection matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-10, 10, -10, 10, -10, 10);
			glGetFloatv(GL_PROJECTION_MATRIX, m);
			printMatrix(m);
			break;
		default:
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60, 1, 1, 100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
			break;
		}
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

	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT);

		switch (problem) {
		case 4:
			drawAxis();
			break;
		default:
			drawAxis();
			break;
		}
	}

	void myKeyboard(unsigned char key, int x, int y) {
		problem = key - '0';
		myInit();
		glutPostRedisplay();
	}

	void main() {
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutCreateWindow("Tut4");
		myInit();
		glutDisplayFunc(myDisplay);
		glutKeyboardFunc(myKeyboard);
		glutMainLoop();
	}
}