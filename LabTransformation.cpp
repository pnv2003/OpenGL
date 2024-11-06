#include "math.h"
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "lab.h"
using namespace std;

#define	WINDOW_LEFT		-10
#define	WINDOW_RIGHT	 10
#define	WINDOW_BOTTOM	-10
#define	WINDOW_TOP		 10

namespace LabTransformation {
	void myInit() {
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
	}
	void drawGrid() {
		glColor3f(0.6f, 0.6f, 0.6f);
		glLineWidth(1.0);

		glBegin(GL_LINES);
		for (int i = WINDOW_LEFT; i <= WINDOW_RIGHT; i++) {
			glVertex2i(i, WINDOW_BOTTOM);
			glVertex2i(i, WINDOW_TOP);
		}
		for (int i = WINDOW_BOTTOM; i < WINDOW_TOP; i++) {
			//Code here 1
			///////////////
			glVertex2i(WINDOW_LEFT, i);
			glVertex2i(WINDOW_RIGHT, i);	
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(5.0);

		glBegin(GL_LINES);
		glVertex2i(WINDOW_LEFT, 0);
		glVertex2i(WINDOW_RIGHT, 0);
		glVertex2i(0, WINDOW_BOTTOM);
		glVertex2i(0, WINDOW_TOP);
		glEnd();
	}
	void drawHouse() {
		glLineWidth(3.0);
		//Code here 2

		glBegin(GL_LINE_LOOP);
		glVertex2i(0, 0);
		glVertex2i(0, 2);
		glVertex2i(2, 4);
		glVertex2i(4, 2);
		glVertex2i(4, 0);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(0.5f, 2.5f);
		glVertex2f(0.5f, 4.0f);
		glVertex2f(1.5f, 4.0f);
		glVertex2f(1.5f, 3.5f);
		glEnd();
	}
	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT);
		drawGrid();

		// red house
		glColor3f(1, 0, 0);
		drawHouse();

		// blue house
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(4, 3, 0);
		drawHouse();
		glPopMatrix();

		// purple house
		glPushMatrix();
		glColor3f(1, 0, 1);
		glScalef(1, 1.5, 0);
		glTranslatef(2, -3, 0);
		drawHouse();
		glPopMatrix();

		// cyan house
		glPushMatrix();
		glColor3f(0, 1, 1);
		glRotatef(90, 0, 0, 1);
		glTranslatef(2, 0, 0);
		drawHouse();
		glPopMatrix();

		// black house
		glPushMatrix();
		glColor3f(0, 0, 0);
		glScalef(-1.5, -1.5, 0);
		drawHouse();
		glPopMatrix();

		glFlush();
	}

	int main1(int argc, char* argv[]) {
		//glutInit(&argc, (char**)argv); //initialize the tool kit
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //set the display mode
		glutInitWindowSize(650, 650); //set window size
		glutInitWindowPosition(0, 0); // set window position on screen
		glutCreateWindow("LAB-Transformation");//open the screen window

		glutDisplayFunc(myDisplay);
		myInit();
		glutMainLoop();
		return 0;
	}

	// -----------------------------------------------------------------------
	const int screenWidth = 700;
	const int screenHeight = 700;
	int nChoice = 0;

	void init() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
	}
	void setLight() {
		GLfloat	lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat light_position[] = { 10, 10, 20.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
	}
	void setMaterial() {
		GLfloat	mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat	mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		GLfloat	mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat mat_shininess[] = { 50.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
	void setCamera() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(10, 6, 10, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
	}
	void drawAxis() {
		float	xmax = 1.5, ymax = 1.5, zmax = 1.5;
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(-xmax, 0, 0);
		glVertex3f(xmax, 0, 0);
		glVertex3f(0, -ymax, 0);
		glVertex3f(0, ymax, 0);
		glVertex3f(0, 0, -zmax);
		glVertex3f(0, 0, zmax);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		void* font = GLUT_BITMAP_TIMES_ROMAN_24;

		glRasterPos3f(1.5, 0, 0);
		glutBitmapCharacter(font, 'X');

		glRasterPos3f(0, 1.5, 0);
		glutBitmapCharacter(font, 'Y');

		glRasterPos3f(0, 0, 1.5);
		glutBitmapCharacter(font, 'Z');
	}
	void display() {
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setCamera();
		drawAxis();
		setLight();

		setMaterial();

		switch (nChoice) {
		case 1:
		{
			glPushMatrix();
			glTranslatef(1, 0, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();
			break;
		}
		case 2:
		{
			glPushMatrix();
			glTranslatef(0.25, 0.75, 0.65);
			glutSolidTeapot(0.25);
			glPopMatrix();
			break;
		}
		case 3:
		{
			glPushMatrix();
			glTranslatef(0, 0, 1);
			glutSolidTeapot(0.25);
			glPopMatrix();
			break;
		}
		case 4:
		{
			glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			glTranslatef(0, 1, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();
			break;
		}
		case 5:
		{
			// x+
			glPushMatrix();
			glTranslatef(1, 0, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();

			// x-
			glPushMatrix();
			glTranslatef(-1, 0, 0);
			glRotatef(180, 0, 1, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();

			// z+
			glPushMatrix();
			glTranslatef(0, 0, 1);
			glRotatef(-90, 0, 1, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();

			// z-
			glPushMatrix();
			glTranslatef(0, 0, -1);
			glRotatef(90, 0, 1, 0);
			glutSolidTeapot(0.25);
			glPopMatrix();
			break;
		}
		case 6:
		{
			
			for (int i = 0; i < 5; i++) {
				glPushMatrix();
				glTranslatef(0, 0.3*i, 0);
				glScalef(powf(0.8, i), powf(0.8, i), powf(0.8, i));
				glutSolidTeapot(0.25);
				glPopMatrix();
			}
			
			break;
		}
		case 7:
		{

			for (int c = 5; c >= 1; c--) {
				glPushMatrix();
				glTranslatef(0, 0.3 * (5 - c), 0);
				for (int i = 0; i < c; i++) {
					glutSolidCube(0.25);
					glTranslatef(0.3, 0, 0);
				}
				glPopMatrix();
			}

			for (int c = 5; c >= 1; c--) {
				glPushMatrix();
				glTranslatef(0, 0, 0.3 * (5 - c));
				for (int i = 0; i < c; i++) {
					glutSolidCube(0.25);
					glTranslatef(0.3, 0, 0);
				}
				glPopMatrix();
			}

			break;
		}
		case 8:
		{
			float offset = 0;
			for (int i = 0; i < 5; i++) {
				glPushMatrix();
				glTranslatef(offset, 0, 0);
				if (i % 2 != 0)
					glRotatef(45, 1, 0, 0);
				glScalef(powf(0.8, i), powf(0.8, i), powf(0.8, i));
				glutSolidCube(0.25);
				glPopMatrix();
				offset += 0.25 / 2 * powf(0.8, i) * 1.8;
			}

			offset = 0;
			for (int i = 0; i < 5; i++) {
				glPushMatrix();
				glTranslatef(0, offset, 0);
				if (i % 2 != 0)
					glRotatef(45, 0, 1, 0);
				glScalef(powf(0.8, i), powf(0.8, i), powf(0.8, i));
				glutSolidCube(0.25);
				glPopMatrix();
				offset += 0.25 / 2 * powf(0.8, i) * 1.8;
			}

			offset = 0;
			for (int i = 0; i < 5; i++) {
				glPushMatrix();
				glTranslatef(0, 0, offset);
				if (i % 2 != 0)
					glRotatef(45, 0, 0, 1);
				glScalef(powf(0.8, i), powf(0.8, i), powf(0.8, i));
				glutSolidCube(0.25);
				glPopMatrix();
				offset += 0.25 / 2 * powf(0.8, i) * 1.8;
			}

			break;
		}
		default:
			glutSolidTeapot(0.25);
		}

		glFlush();
	}

	void myKeyboard(unsigned char key, int x, int y) {
		nChoice = key - '0';
		glutPostRedisplay();
	}

	int main2(int argc, char* argv[]) {
		cout << "0. Original" << endl;
		cout << "1. Problem 1" << endl;
		cout << "2. Problem 2" << endl;
		cout << "3. Problem 3" << endl;
		cout << "4. Problem 4" << endl;
		cout << "5. Problem 5" << endl;
		cout << "6. Problem 6" << endl;
		cout << "7. Problem 7" << endl;
		cout << "8. Problem 8" << endl;

		//glutInit(&argc, (char**)argv); //initialize the tool kit
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(screenWidth, screenHeight); //set window size
		glutInitWindowPosition(0, 0); // set window position on screen
		glutCreateWindow("Lab-Transformation"); // open the screen window

		glutKeyboardFunc(myKeyboard);
		glutDisplayFunc(display);

		init();
		glEnable(GL_DEPTH_TEST);

		glutMainLoop();
		return 0;
	}
}
