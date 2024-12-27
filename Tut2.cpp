#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tutorial.h"
using namespace std;

#define PI 3.1415926
#define DEG2RAD(x) (x*PI)/180.0f
#define DEGTORAD	(PI/180.0)

namespace Tut2 {
	int problem = 1;

	void drawArcs() {
		glColor3f(0, 0, 0);
		glLineWidth(1);
		float R = 0.5;
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 90; i++) {
			float x = R * cos(DEG2RAD(i));
			float y = R * sin(DEG2RAD(i));
			glVertex2f(x, y);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (int i = 180; i < 270; i++) {
			float x = R * cos(DEG2RAD(i)) + 1;
			float y = R * sin(DEG2RAD(i)) + 1;
			glVertex2f(x, y);
		}
		glEnd();
	}

	void setCameraVolume(float l, float r, float b, float t) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	}

	void setViewport(int l, int r, int b, int t) {
		glViewport(l, b, r - l, t - b);
	}

	void myInit() {
		// setup 2D view
		glClearColor(1.0, 1.0, 1.0, 0.0);
		setCameraVolume(-10, 10, -10, 10);
	}

	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		
		switch (problem) {
		case 1:
			drawArcs();
			break;
		case 2:
		{
			// use drawArcs on every cell in 10x10 grid
			int windowWidth = 600;
			int windowHeight = 600;
			int tileSize = 50;
			int gridSize = 12;

			srand(static_cast<unsigned int>(time(0)));

			for (int i = 0; i < gridSize; i++) {
				for (int j = 0; j < gridSize; j++) {
					int viewportLeft = i * tileSize;
					int viewportRight = (i + 1) * tileSize;
					int viewportBottom = j * tileSize;
					int viewportTop = (j + 1) * tileSize;

					setViewport(viewportLeft, viewportRight, viewportBottom, viewportTop);
					setCameraVolume(0, 1, 0, 1);

					int angle = (rand() % 4) * 90; // 0, 90, 180, 270

					glPushMatrix();
					glTranslatef(0.5, 0.5, 0);
					glRotatef(angle, 0, 0, 1);
					glTranslatef(-0.5, -0.5, 0);

					drawArcs();
					glPopMatrix();
				}
			}
			break;
		}
		default:
			break;
		}

		glFlush();
	}

	void myKeyboard(unsigned char key, int x, int y) {
		problem = key - '0';
		if (problem < 1 || problem > 2)
			problem = 1;
		glutPostRedisplay();
	}

	void main() {
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(600, 600);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Tut2");
		myInit();
		glutDisplayFunc(myDisplay);
		glutKeyboardFunc(myKeyboard);
		glutMainLoop();
	}













	//-------------------------------------------------
	namespace Star {

		int		nWidth = 600;
		int		nHeight = 600;

		int		nCenterX = nWidth / 2;
		int		nCenterY = nHeight / 2;

		int		nRadius = 200;

		float		vertexArr[10][2];

		float		t = 1;

		bool		bAuto = false;

		float	theta = 0;
		bool	tIncr = false;

		void setWindow(float l, float r, float b, float t)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(l, r, b, t);
		}
		void setViewport(int l, int r, int b, int t)
		{
			glViewport(l, b, r - l, t - b);
		}

		void CalcVertexArrs()
		{
			for (int i = 0; i < 10; i++) {
				float r = (i % 2 == 0) ? nRadius : nRadius / 2.5;
				float angle = i * 36;
				float x = nCenterX + r * cos((angle + 90 + theta) * DEGTORAD);
				float y = nCenterY + r * sin((angle + 90 + theta) * DEGTORAD);
				vertexArr[i][0] = x;
				vertexArr[i][1] = y;
			}
		}

		void DrawFigure(float t)
		{
			float colorArr[10][3] = {
                {t, t, 0 }, { t, 0, 0 }, { 0, 0, t }, { 0, t, 0 }, { 0, 0, 0 },
                {t, t, 0 }, { t, 0, 0 }, { 0, 0, t }, { 0, t, 0 }, { 0, 0, 0 }
			};

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1, 1, 1);
			glVertex2f(nCenterX, nCenterY);
			for (int i = 0; i < 10; i++) {
				glColor3f(colorArr[i][0], colorArr[i][1], colorArr[i][2]);
				float x = vertexArr[i][0];
				float y = vertexArr[i][1];
				glVertex2f(x, y);
			}
			glColor3f(colorArr[0][0], colorArr[0][1], colorArr[0][2]);
			glVertex2f(vertexArr[0][0], vertexArr[0][1]);
			glEnd();
		}

		void OnSpecialKey(int key, int x, int y)
		{
			switch (key)
			{
			case GLUT_KEY_LEFT:
				nCenterX -= 10;
				break;
			case GLUT_KEY_RIGHT:
				nCenterX += 10;
				break;
			case GLUT_KEY_UP:
				nCenterY += 10;
				break;
			case GLUT_KEY_DOWN:
				nCenterY -= 10;
				break;
			case GLUT_KEY_PAGE_UP:
				theta += 5;
				break;
			case GLUT_KEY_PAGE_DOWN:
				theta -= 5;
				break;
			}
			glutPostRedisplay();
		}
		void OnTimer(int value)
		{
			if (bAuto) {
				cout << "t = " << t << endl;
				if (tIncr) {
					t += 0.1;
					if (t >= 1) {
						t = 1;
						tIncr = false;
					}
				}
				else {
					t -= 0.1;
					if (t <= 0) {
						t = 0;
						tIncr = true;
					}
				}
			}
			glutTimerFunc(300, OnTimer, 0);
			glutPostRedisplay();
		}
		void OnKey(unsigned char key, int x, int y)
		{
			switch (key) 
			{
			case 'i':
			case 'I':
				t += 0.1;
				break;
			case 'd':
			case 'D':
				t -= 0.1;
				break;
			case 'a':
			case 'A':
				bAuto = !bAuto;
				break;
			}
			glutPostRedisplay();
		}
		void OnMouseClick(int button, int state, int x, int y)
		{
			// set the center to the clicked position
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				nCenterX = x;
				nCenterY = nHeight - y; // flip the y, because the origin is at the top-left corner
			}
			glutPostRedisplay();
		}

		void OnReshape(int w, int h)
		{
			nWidth = w;
			nHeight = h;
		}

		void OnDisplay()
		{
			CalcVertexArrs();

			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			setViewport(0, nWidth, 0, nHeight);
			setWindow(0, nWidth, 0, nHeight);

			DrawFigure(t);

			glFlush();
		}

		int main(int argc, char** argv)
		{
			cout << "Click mouse to change the Center of the Figure" << endl;
			cout << "Press Left Arrow to move the Figure to the left" << endl;
			cout << "Press Right Arrow to move the Figure to the right" << endl;
			cout << "Press Up Arrow to move the Figure up" << endl;
			cout << "Press Down Arrow to move the Figure down" << endl;
			cout << "Press Page Up to rotate the Figure to the left" << endl;
			cout << "Press Page Down to rotate the Figure to the right" << endl;
			cout << "Press i/I to increase the value of t" << endl;
			cout << "Press d/D to decrease the value of t" << endl;
			cout << "Press a/A to toggle the value of bAuto" << endl;

			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
			glutInitWindowSize(nWidth, nHeight);
			glutInitWindowPosition(20, 20);
			glutCreateWindow("Cau 5 - Tut 2");

			glutSpecialFunc(OnSpecialKey);
			glutKeyboardFunc(OnKey);
			glutReshapeFunc(OnReshape);
			glutMouseFunc(OnMouseClick);
			glutTimerFunc(300, OnTimer, 0);
			glutDisplayFunc(OnDisplay);

			glutMainLoop();
			return 0;
		}
	}
}