#include <math.h>
#include <iostream>
#include "lab.h"
using namespace std;

#define PI		3.1415926
#define	DEG2RAD(x) (x*PI)/180.0f

namespace LabCamera {

	namespace Exercise1 {

		const int screenWidth = 650;
		const int screenHeight = 650;
		int nChoice = 1;

		void init()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
		}
		void setLight()
		{
			GLfloat	lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			GLfloat light_position[] = { 10, 10, 20.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

			GLfloat light_position1[] = { 10, 10, -20.0f, 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

			GLfloat light_position2[] = { 0, -10, 0.0f, 0.0f };
			glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			//glEnable(GL_LIGHT2);
			glShadeModel(GL_SMOOTH);
		}
		void setMaterial()
		{
			GLfloat	mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			GLfloat	mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
			GLfloat	mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat mat_shininess[] = { 50.0f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		}
		void setCamera()
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			switch (nChoice) {
			case 1:
				gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
				break;
			case 2:
				gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
				break;
			case 3:
				gluLookAt(10, 0, 0, 0, 0, 0, 0, 1, 0);
				break;
			case 4:
				gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, 1);
				break;
			case 5:
				gluLookAt(0, 10, 0, 0, 0, 0, 1, 0, 0);
				break;
			case 6:
				gluLookAt(0, -10, 0, 0, 0, 0, -1, 0, 0);
				break;
			case 7:
				gluLookAt(10, 5, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				break;
			case 8:
				gluLookAt(-10, 5, -10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				break;
			case 9:
				gluLookAt(10, -5, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				break;
			case 0:
				gluLookAt(10, -5, 10, 0.0, -0.5, 0.0, 0.0, 1.0, 0.0);
				break;
			default:
				gluLookAt(10, 5, 10, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
			}
		}
		void drawAxis()
		{
			glDisable(GL_LIGHTING);

			float	xmax = 1.0, ymax = 1.0, zmax = 1.0;
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

			glRasterPos3f(1.0, 0, 0);
			glutBitmapCharacter(font, 'X');

			glRasterPos3f(0, 1.0, 0);
			glutBitmapCharacter(font, 'Y');

			glRasterPos3f(0, 0, 1.0);
			glutBitmapCharacter(font, 'Z');
		}
		void display()
		{
			glClearColor(1.0, 1.0, 1.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			setCamera();
			drawAxis();
			setLight();

			setMaterial();

			glutSolidTeapot(0.25);

			glFlush();
		}

		void myKeyboard(unsigned char key, int x, int y) {
			nChoice = key - '0';
			glutPostRedisplay();
		}

		int main()
		{
			cout << "1. View 1" << endl;
			cout << "2. View 2" << endl;
			cout << "3. View 3" << endl;
			cout << "4. View 4" << endl;
			cout << "5. View 5" << endl;
			cout << "6. View 6" << endl;
			cout << "7. View 7" << endl;
			cout << "8. View 8" << endl;
			cout << "9. View 9" << endl;
			cout << "0. View 10" << endl;

			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Camera"); // open the screen window

			glutKeyboardFunc(myKeyboard);
			glutDisplayFunc(display);

			init();
			glEnable(GL_DEPTH_TEST);

			glutMainLoop();
			return 0;
		}
	}

	// -----------------------------------------------------------------------------------------------
	namespace Exercise2 {

		const int screenWidth = 820;
		const int screenHeight = 400;

		void display()
		{
			glClearColor(1.0, 1.0, 1.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//VIEWPORT 1
			glViewport(0, 0, 400, 400);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			float fSize = 2;
			glOrtho(-fSize, fSize, -fSize, fSize, -10, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(2, 4, 3, 0, 0, 0, 0, 1, 0);

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			for (float x = -10; x <= 10; x += 0.15)
			{
				glVertex3f(x, 0, 100);
				glVertex3f(x, 0, -100);
			}
			//Code here - Hoan thien ve duong luoi
			for (float z = -10; z <= 10; z += 0.15)
			{
				glVertex3f(100, 0, z);
				glVertex3f(-100, 0, z);
			}
			glEnd();
			////////////////////////////////////////////
			//VIEWPORT 2
			glViewport(420, 0, 400, 400);
			//Code here - Ve hinh anh o khung nhin 2
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60, 1, 1, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(2, 4, 3, 0, 0, 0, 0, 1, 0);

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			for (float x = -10; x <= 10; x += 0.15)
			{
				glVertex3f(x, 0, 100);
				glVertex3f(x, 0, -100);
			}
			for (float z = -10; z <= 10; z += 0.15)
			{
				glVertex3f(100, 0, z);
				glVertex3f(-100, 0, z);
			}
			glEnd();

			glFlush();
		}

		int main()
		{
			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Camera"); // open the screen window

			glutDisplayFunc(display);

			glEnable(GL_DEPTH_TEST);

			glutMainLoop();
			return 0;
		}
	}

	// -----------------------------------------------------------------------------------------------
	namespace Exercise3 {
		void myDisplay();

		int		screenWidth = 600;
		int		screenHeight = 600;

		float camera_angle;
		float camera_height;
		float camera_dis;
		float camera_X, camera_Y, camera_Z;
		float lookAt_X, lookAt_Y, lookAt_Z;

		bool	b4View = false;

		void mySetupCameraVolume(int nType)
		{
			if (nType == 4)
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();


				gluPerspective(60.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0f, 1000.0f);
			}
			else if (nType == 1)
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-5, 5, -5, 5, -1000, 1000);
			}
			else if (nType == 2)
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-5, 5, -5, 5, -1000, 1000);
			}
			else if (nType == 3)
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-5, 5, -5, 5, -1000, 1000);
			}
		}

		void changeCameraPos()
		{
			camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
			camera_Y = camera_height;
			camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;

			myDisplay();
		}


		void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
		{
			//code here
			switch (theKey)
			{
			case GLUT_KEY_UP:
				camera_height += 0.1;
				changeCameraPos();
				break;
			case GLUT_KEY_DOWN:
				camera_height -= 0.1;
				changeCameraPos();
				break;
			case GLUT_KEY_LEFT:
				camera_angle += 1;
				changeCameraPos();
				break;
			case GLUT_KEY_RIGHT:
				camera_angle -= 1;
				changeCameraPos();
				break;
			}
		}

		void myKeyboard(unsigned char key, int x, int y)
		{
			switch (key)
			{
				//Code here
			case 'V':
			case 'v':
				b4View = !b4View;
				break;
			case '+':
				camera_dis += 0.1;
				changeCameraPos();
				break;
			case '-':
				camera_dis -= 0.1;
				changeCameraPos();
				break;
			}
			glutPostRedisplay();
		}

		void DisplayOneView(int nType, int left, int right, int top, int bottom)
		{
			mySetupCameraVolume(nType);
			glViewport(left, top, right - left, bottom - top);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//code here
			if (nType == 1)
				gluLookAt(0, camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
			else if (nType == 2)
				gluLookAt(0, 0.0, camera_dis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			else if (nType == 3)
				gluLookAt(camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			else
				gluLookAt(camera_X, camera_Y, camera_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			//

			glColor3f(0, 0, 1);
			glutSolidTeapot(2);
		}

		void myDisplay()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (b4View == false)
			{
				DisplayOneView(4, 0, screenWidth, 0, screenHeight);
			}
			else
			{
				//code here
				DisplayOneView(1, 0, screenWidth / 2, 0, screenHeight / 2);
				DisplayOneView(2, 0, screenWidth / 2, screenHeight / 2, screenHeight);
				DisplayOneView(3, screenWidth / 2, screenWidth, screenHeight / 2, screenHeight);
				DisplayOneView(4, screenWidth / 2, screenWidth, 0, screenHeight / 2);
				//
			}

			glFlush();
			glutSwapBuffers();
		}

		void myInit()
		{
			float	fHalfSize = 3;

			camera_angle = 0.0;
			camera_height = 2.0;
			camera_dis = 11;
			camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
			camera_Y = camera_height;
			camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		void setLight()
		{
			GLfloat	lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			GLfloat light_position[] = { 10, 10, 20.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

			GLfloat light_position1[] = { 10, 10, -20.0f, 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

			GLfloat light_position2[] = { 0, -10, 0.0f, 0.0f };
			glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);

			glShadeModel(GL_SMOOTH);
		}
		void setMaterial()
		{
			GLfloat	mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			GLfloat	mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
			GLfloat	mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat mat_shininess[] = { 50.0f };

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		}

		int main()
		{
			cout << "V, v: to switch between 1 and 4 views." << endl;
			cout << "+   : to increase camera distance." << endl;
			cout << "-   : to decrease camera distance." << endl;
			cout << "up arrow  : to increase camera height." << endl;
			cout << "down arrow: to decrease camera height." << endl;
			cout << "<-        : to rotate camera clockwise." << endl;
			cout << "->        : to rotate camera counterclockwise." << endl;

			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(100, 100);
			glutCreateWindow("Lab Camera"); // open the screen window

			glEnable(GL_DEPTH_TEST);
			myInit();
			setLight();
			setMaterial();

			glutKeyboardFunc(myKeyboard);
			glutDisplayFunc(myDisplay);
			glutSpecialFunc(mySpecialKeyboard);

			glutMainLoop();
			return 0;
		}

	}
}