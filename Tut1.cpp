#include <cmath>
#include <iostream>
#include "tutorial.h"
using namespace std;

#define PI 3.1415926
#define DEG2RAD(x) (x*PI)/180.0f

namespace Tut1 {
	int problem = 2;

	void drawLine(float x1, float y1, float len, float angle, float& x2, float& y2) {
		glColor3f(1.0, 0.0, 0.0);
		x2 = x1 + len * cos(DEG2RAD(angle));
		y2 = y1 + len * sin(DEG2RAD(angle));
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
	}

	void drawTriangle(float x1, float y1, float len, float angle) {
		float x = x1, y = y1;
		drawLine(x, y, len, angle, x, y);
		drawLine(x, y, len, angle + 120, x, y);
		drawLine(x, y, len, angle + 240, x, y);
	}

	void drawSquare(float x1, float y1, float len, float angle) {
		float x = x1, y = y1;
		drawLine(x, y, len, angle, x, y);
		drawLine(x, y, len, angle + 90, x, y);
		drawLine(x, y, len, angle + 180, x, y);
		drawLine(x, y, len, angle + 270, x, y);
	}

	void drawDecagon(float x1, float y1, float len, float angle) {
		float x = x1, y = y1;
		for (int i = 0; i < 10; i++) {
			drawLine(x, y, len, angle + i * 36, x, y);
		}
	}

	void myInit() {
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-10, 10, -10, 10);
	}

	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);

		glLineWidth(2);
		switch (problem) {
		case 2: {
			float x2, y2;
			drawLine(0, 0, 3.5, 30, x2, y2);
			break;
		}
		case 3: {
			drawTriangle(0, 0, 3.5, 30);
			break;
		}
		case 4: {
			for (int i = 0; i < 5; i++) {
				drawTriangle(0, 0, 3.5, i * 70);
				drawTriangle(0, 0, 3.5, 180 + i * 70);
			}
			break;
		}
		case 5: {
			for (int i = 0; i < 12; i++) {
				drawSquare(0, 0, 3.5, i * 30);
			}
			break;
		}
		case 6: {
			for (int i = 0; i < 12; i++) {
				drawDecagon(0, 0, 3.5, i * 30);
			}
		}
		case 7: {
			// Vietnamese flag
			// TODO
			break;
		}
		case 8: {
			// optical illusion

			// 19x19 black-white grid
			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					if ((i + j) % 2 == 0) {
						glColor3f(0, 0, 0);
					}
					else {
						glColor3f(1, 1, 1);
					}
					glBegin(GL_QUADS);
					glVertex2f(-10 + i, -10 + j);
					glVertex2f(-10 + i + 1, -10 + j);
					glVertex2f(-10 + i + 1, -10 + j + 1);
					glVertex2f(-10 + i, -10 + j + 1);
					glEnd();
				}
			}

			// dots
			glColor3f(1, 1, 1);
			// TODO
		}

		default:
			break;
		}

		glFlush();
	}

	void myKeyboard(unsigned char key, int x, int y) {
		problem = key - '0';
		if (problem < 2 || problem > 8)
			problem = 2;
		glutPostRedisplay();
	}

	void main() {
		cout << "Select a problem to display:\n";
		cout << "2. Problem 2\n";
		cout << "3. Problem 3\n";
		cout << "4. Problem 4\n";
		cout << "5. Problem 5.1\n";
		cout << "6. Problem 5.2\n";
		cout << "7. Problem 6\n";
		cout << "8. Problem 7\n";

		// setup for 2D display
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(600, 600);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Tut1");

		myInit();
		glutDisplayFunc(myDisplay);
		glutKeyboardFunc(myKeyboard);

		glutMainLoop();
	}
}