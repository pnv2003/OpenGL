#include <math.h>
#include <iostream>
#include "lab.h"
using namespace std;

#define		PI	3.1415926

namespace LabLighting {

	namespace Exercise1 {

		const int screenWidth = 650;
		const int screenHeight = 650;

		GLfloat	mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat	mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		GLfloat	mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat mat_shininess[] = { 50.0f };

		void init()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
		}
		void setLight()
		{
			GLfloat	lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			GLfloat	lightDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
			GLfloat	lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat light_position[] = { 2, 1, 2, 0.0f };

			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
			glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);

			glShadeModel(GL_SMOOTH);
		}
		void setMaterial()
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		}
		void setCamera()
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(2, 1, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

			glutSolidTeapot(0.5);

			glFlush();
		}

		void myKeyboard(unsigned char key, int x, int y)
		{
			switch (key)
			{
			case '1':
				mat_ambient[0] = 0.0f;
				mat_ambient[1] = 0.0f;
				mat_ambient[2] = 0.0f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.01f;
				mat_diffuse[1] = 0.01f;
				mat_diffuse[2] = 0.01f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.5f;
				mat_specular[1] = 0.5f;
				mat_specular[2] = 0.5f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 32.0f;
				break;
			case '2':
				mat_ambient[0] = 0.329412f;
				mat_ambient[1] = 0.223529f;
				mat_ambient[2] = 0.027451f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.780392f;
				mat_diffuse[1] = 0.568627f;
				mat_diffuse[2] = 0.113725f;

				mat_specular[0] = 0.992157f;
				mat_specular[1] = 0.941176f;
				mat_specular[2] = 0.807843f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 27.8974f;
				break;
			case '3':
				mat_ambient[0] = 0.2125f;
				mat_ambient[1] = 0.1275f;
				mat_ambient[2] = 0.054f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.714f;
				mat_diffuse[1] = 0.4284f;
				mat_diffuse[2] = 0.18144f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.393548f;
				mat_specular[1] = 0.271906f;
				mat_specular[2] = 0.166721f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 25.6f;
				break;
			case '4':
				mat_ambient[0] = 0.25f;
				mat_ambient[1] = 0.25f;
				mat_ambient[2] = 0.25f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.4f;
				mat_diffuse[1] = 0.4f;
				mat_diffuse[2] = 0.4f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.774597f;
				mat_specular[1] = 0.774597f;
				mat_specular[2] = 0.774597f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 76.8f;
				break;
			case '5':
				mat_ambient[0] = 0.19125f;
				mat_ambient[1] = 0.0735f;
				mat_ambient[2] = 0.0225f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.7038f;
				mat_diffuse[1] = 0.27048f;
				mat_diffuse[2] = 0.0828f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.256777f;
				mat_specular[1] = 0.137622f;
				mat_specular[2] = 0.086014f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 12.8f;
				break;
			case '6':
				mat_ambient[0] = 0.24725f;
				mat_ambient[1] = 0.1995f;
				mat_ambient[2] = 0.0745f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.75164f;
				mat_diffuse[1] = 0.60648f;
				mat_diffuse[2] = 0.22648f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.628281f;
				mat_specular[1] = 0.555802f;
				mat_specular[2] = 0.366065f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 51.2f;
				break;
			case '7':
				mat_ambient[0] = 0.105882f;
				mat_ambient[1] = 0.058824f;
				mat_ambient[2] = 0.113725f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.427451f;
				mat_diffuse[1] = 0.470588f;
				mat_diffuse[2] = 0.541176f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.3333f;
				mat_specular[1] = 0.3333f;
				mat_specular[2] = 0.521569f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 9.84615f;
				break;
			case '8':
				mat_ambient[0] = 0.19225f;
				mat_ambient[1] = 0.19225f;
				mat_ambient[2] = 0.19225f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.50754f;
				mat_diffuse[1] = 0.50754f;
				mat_diffuse[2] = 0.50754f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.508273f;
				mat_specular[1] = 0.508273f;
				mat_specular[2] = 0.508273f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 51.2f;
				break;
			case '9':
				mat_ambient[0] = 0.23125f;
				mat_ambient[1] = 0.23125f;
				mat_ambient[2] = 0.23125f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 0.2775f;
				mat_diffuse[1] = 0.2775f;
				mat_diffuse[2] = 0.2775f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 0.773911f;
				mat_specular[1] = 0.773911f;
				mat_specular[2] = 0.773911f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 89.6f;
				break;
			default:
				mat_ambient[0] = 0.2f;
				mat_ambient[1] = 0.2f;
				mat_ambient[2] = 0.2f;
				mat_ambient[3] = 1.0f;

				mat_diffuse[0] = 1.0f;
				mat_diffuse[1] = 0.0f;
				mat_diffuse[2] = 0.0f;
				mat_diffuse[3] = 1.0f;

				mat_specular[0] = 1.0f;
				mat_specular[1] = 1.0f;
				mat_specular[2] = 1.0f;
				mat_specular[3] = 1.0f;

				mat_shininess[0] = 50.0f;
				break;
			}
			glutPostRedisplay();
		}

		int main()
		{
			cout << "0. Default" << endl;
			cout << "1. Black plastic" << endl;
			cout << "2. Brass" << endl;
			cout << "3. Bronze" << endl;
			cout << "4. Chrome" << endl;
			cout << "5. Copper" << endl;
			cout << "6. Gold" << endl;
			cout << "7. Pewter" << endl;
			cout << "8. Silver" << endl;
			cout << "9. Polished silver" << endl;

			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Lighting"); // open the screen window

			glutKeyboardFunc(myKeyboard);
			glutDisplayFunc(display);

			init();
			glEnable(GL_DEPTH_TEST);

			glutMainLoop();
			return 0;
		}
	}

	namespace Exercise2 {

		const int screenWidth = 650;
		const int screenHeight = 650;

		void init()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
		}
		void setLight()
		{
			const GLfloat leftLightDiffColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
			const GLfloat leftLightSpecColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			const GLfloat leftLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
			const GLfloat leftLightPos[] = { -5.0, 0.0, 0.0, 0.0 };

			const GLfloat rightLightDiffColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
			const GLfloat rightLightSpecColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
			const GLfloat rightLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
			const GLfloat rightLightPos[] = { 5.0, 0.0, 0.0, 0.0 };

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_NORMALIZE);

			//set up right light
			glLightfv(GL_LIGHT0, GL_POSITION, rightLightPos);
			glLightfv(GL_LIGHT0, GL_AMBIENT, rightLightAmbColor);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, rightLightDiffColor);
			glLightfv(GL_LIGHT0, GL_SPECULAR, rightLightSpecColor);
			glEnable(GL_LIGHT0);

			//set up left light
			glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
			glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
			glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
			glEnable(GL_LIGHT1);

		}

		void display()
		{
			glClearColor(1.0, 1.0, 1.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			setLight();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

			GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0f };
			GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0f };
			GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0f };
			GLfloat shiness = 100.8;


			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);

			glutSolidSphere(1.0, 100, 100);

			glutSwapBuffers();
			glFlush();

			glFlush();
		}

		int main()
		{
			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Lighting - Bai 2"); // open the screen window

			glutDisplayFunc(display);

			init();
			glEnable(GL_DEPTH_TEST);

			glutMainLoop();
			return 0;
		}
	}

	namespace Exercise3 {

		const int screenWidth = 650;
		const int screenHeight = 650;

		float	m_angle = 0.0;
		GLboolean m_leftlightOn = GL_TRUE;
		GLboolean m_rightlightOn = GL_TRUE;

		GLboolean m_smoothshadeModeOn = GL_FALSE;

		void init()
		{
			glEnable(GL_NORMALIZE);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
		}
		void setLight()
		{
			const GLfloat leftLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat leftLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat leftLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
			const GLfloat leftLightPos[] = { 0.0, 0.0, -1.0, 0.0 };

			const GLfloat rightLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat rightLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const GLfloat rightLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
			const GLfloat rightLightPos[] = { 0.0, 0.0, 1.0, 0.0 };

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_NORMALIZE);

			//set up right light
			glLightfv(GL_LIGHT0, GL_POSITION, rightLightPos);
			glLightfv(GL_LIGHT0, GL_AMBIENT, rightLightAmbColor);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, rightLightDiffColor);
			glLightfv(GL_LIGHT0, GL_SPECULAR, rightLightSpecColor);
			glEnable(GL_LIGHT0);

			//set up left light
			glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
			glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
			glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
			glEnable(GL_LIGHT1);

		}
		void setMaterial(float ar, float ag, float ab,
			float dr, float dg, float db,
			float sr, float sg, float sb)
		{
			GLfloat ambient[4];
			GLfloat diffuse[4];
			GLfloat specular[4];
			GLfloat	shiness = 100.8;

			ambient[0] = ar; ambient[1] = ag; ambient[2] = ab; ambient[3] = 1;
			diffuse[0] = dr; diffuse[1] = dg; diffuse[2] = db; diffuse[3] = 1;
			specular[0] = sr; specular[1] = sg; specular[2] = sb; specular[3] = 1;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
		}

		void display()
		{
			glClearColor(1.0, 1.0, 1.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			setLight();

			if (m_rightlightOn)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);

			if (m_leftlightOn)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);

			if (m_smoothshadeModeOn)
				glShadeModel(GL_SMOOTH);
			else
				glShadeModel(GL_FLAT);


			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(0.0, -4.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

			glRotatef(m_angle, 0.0, 1.0, 0.0);

			glPushMatrix();
			setMaterial(0.1, 0.1, 0.1,
				1.0, 0.0, 0.0,
				1.0, 1.0, 1.0);
			glutSolidSphere(0.2, 20, 20);
			glPopMatrix();


			setMaterial(0.1, 0.1, 0.1,
				0.0, 0.0, 1.0,
				1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(0, 0.5, 0);
			glRotatef(-90, 1, 0, 0);
			glutSolidCone(0.2, 0.4, 20, 30);
			glPopMatrix();

			GLUquadricObj* obj;

			setMaterial(0.1, 0.1, 0.1,
				0.0, 1.0, 0.0,
				1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(-0.4, 0, 0);
			glRotatef(-90, 0, 1, 0);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluCylinder(obj, 0.1, 0.1, 0.6, 30, 10);
			glPopMatrix();

			setMaterial(0.1, 0.1, 0.1,
				1.0, 0.0, 1.0,
				1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(0.4, 0, 0);
			glRotatef(90, 0, 1, 0);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluCylinder(obj, 0.2, 0.06, 0.6, 30, 10);
			glPopMatrix();

			glutSwapBuffers();
			glFlush();
		}

		void myIdle()
		{
			float	dt = 0.05;
			m_angle = m_angle + dt;
			if (m_angle >= 360)
				m_angle = 0;
			display();
		}

		void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
		{
			switch (theKey)
			{
			case 'r':
				m_rightlightOn = !m_rightlightOn;
				break;
			case 'l':
				m_leftlightOn = !m_leftlightOn;
				break;
			case 's':
				m_smoothshadeModeOn = !m_smoothshadeModeOn;
				break;
			default:
				break;
			}
		}

		int main()
		{
			cout << "<r>. Turn on/off right light\n";
			cout << "<l>. Turn on/off left light\n";
			cout << "<s>. Turn on/off smooth shading\n";

			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
			glutInitWindowSize(screenWidth, screenHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Lighting - Bai 3"); // open the screen window

			glutDisplayFunc(display);
			glutIdleFunc(myIdle);
			glutKeyboardFunc(myKeyboard);

			init();
			glEnable(GL_DEPTH_TEST);

			glutMainLoop();
			return 0;

		}
	}

	namespace Exercise4 {
		int		nHeight = 600;
		int		nWidth = 600;

		const GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat lightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		const GLfloat lightPos[] = { 5.0, 0.0, 0.0, 0.0 };

		GLboolean m_lightOn = GL_TRUE;

		GLboolean m_smoothshadeModeOn = GL_TRUE;

		float	m_angle = 0.0;

		void myInit()
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_NORMALIZE);
			glClearColor(0, 0, 0, 1);

			//set up the light
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbColor);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
			glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
		}
		void mySetup(int width, int height)
		{
			glViewport(0, 0, width, height);		// reset the viewport to new dimensions
			glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
			glLoadIdentity();						// reset projection matrix

			// calculate aspect ratio of window
			gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

			glMatrixMode(GL_MODELVIEW);				// set modelview matrix
			glLoadIdentity();						// reset modelview matrix

		}
		void setMaterial(float ar, float ag, float ab,
			float dr, float dg, float db,
			float sr, float sg, float sb)
		{
			GLfloat ambient[4];
			GLfloat diffuse[4];
			GLfloat specular[4];
			GLfloat	shiness = 100.8;

			ambient[0] = ar; ambient[1] = ag; ambient[2] = ab; ambient[3] = 1;
			diffuse[0] = dr; diffuse[1] = dg; diffuse[2] = db; diffuse[3] = 1;
			specular[0] = sr; specular[1] = sg; specular[2] = sb; specular[3] = 1;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
		}

		void myDisplay()
		{
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glLoadIdentity();
			gluLookAt(6.0, 4.0, 6.0, 0.0, 0.0, 2.0, 0.0, 1.0, 0.0);

			glRotatef(m_angle, 0.0, 1.0, 0.0);

			//light
			if (m_lightOn)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);


			if (m_smoothshadeModeOn)
				glShadeModel(GL_SMOOTH);
			else
				glShadeModel(GL_FLAT);

			GLUquadricObj* obj;

			//draw the chest
			setMaterial(0.1, 0.1, 0.1,
				0, 1, 0,
				1, 1, 1);
			glPushMatrix();
			glutSolidSphere(1, 100, 100);
			glPopMatrix();

			//draw the abdomen
			setMaterial(0.1, 0.1, 0.1,
				1, 0, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.0, -1.8, 0.0);
			glutSolidSphere(1.3, 20, 20);
			glPopMatrix();

			//draw the head
			setMaterial(0.1, 0.1, 0.1,
				1, 1, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.0, 1.5, 0.0);
			glutSolidSphere(0.8, 20, 20);
			glPopMatrix();

			//draw nose
			setMaterial(0.1, 0.1, 0.1,
				1, 0, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.0, 1.5, 0.8);
			glutSolidSphere(0.2, 20, 20);
			glPopMatrix();

			//draw left eye
			setMaterial(0.1, 0.1, 0.1,
				0, 1, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(-0.3, 1.7, 0.7);
			glutSolidSphere(0.1, 20, 20);
			glPopMatrix();

			//draw right eye
			setMaterial(0.1, 0.1, 0.1,
				0, 1, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.3, 1.7, 0.7);
			glutSolidSphere(0.1, 20, 20);
			glPopMatrix();

			//draw the hat
			setMaterial(0.1, 0.1, 0.1,
				1, 0, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.0, 2.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			glutSolidCone(0.7, 1.5, 20, 20);
			glPopMatrix();

			//draw left hand
			setMaterial(0.1, 0.1, 0.1,
				1, 0, 1,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.5, 0.4, 0.0);
			glRotated(90, 0.0, 1.0, 0.0);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluCylinder(obj, 0.5, 0.5, 2.5, 30, 10);
			glPopMatrix();
			gluDeleteQuadric(obj);

			//draw right hand
			setMaterial(0.1, 0.1, 0.1,
				1, 0, 1,
				1, 1, 1);
			glPushMatrix();
			glTranslated(-0.5, 0.4, 0.0);
			glRotated(-90, 0.0, 1.0, 0.0);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluCylinder(obj, 0.5, 0.5, 2.5, 30, 10);
			glPopMatrix();
			gluDeleteQuadric(obj);

			//draw noel tree
			setMaterial(0.1, 0.1, 0.1,
				0, 1, 0,
				1, 1, 1);

			glPushMatrix();
			glTranslated(0.0, 0.0, 5.0);
			glTranslated(0.0, -1.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			glutSolidCone(0.8, 2.5, 30, 20);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0.0, 0.0, 5.0);
			glTranslated(0.0, 0.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			glutSolidCone(0.8, 2.5, 30, 20);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0.0, 0.0, 5.0);
			glTranslated(0.0, 1.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			glutSolidCone(0.8, 2.5, 30, 20);
			glPopMatrix();

			setMaterial(0.1, 0.1, 0.1,
				1, 0.5, 0,
				1, 1, 1);
			glPushMatrix();
			glTranslated(0.0, 0.0, 5.0);
			glTranslated(0.0, -3.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluCylinder(obj, 0.4, 0.4, 3, 30, 10);
			glPopMatrix();
			gluDeleteQuadric(obj);

			glutSwapBuffers();
			glFlush();
		}

		void myReshape(int cx, int cy)
		{
			mySetup(cx, cy);
			myDisplay();
		}
		void myIdle()
		{
			float	dt = 0.2;
			m_angle = m_angle + dt;
			if (m_angle >= 360)
				m_angle = 0;
			myDisplay();
		}
		void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
		{
			switch (theKey)
			{
			case 'o':
				m_lightOn = !m_lightOn;
				break;
			case 's':
				m_smoothshadeModeOn = !m_smoothshadeModeOn;
				break;
			default:
				break;
			}
		}
		int main()
		{
			cout << "Press following key to control the program\n\n";
			cout << "<o>. Turn on/off the light\n";
			cout << "<s>. Turn on/off smooth shading\n";

			//glutInit(&argc, (char**)argv); //initialize the tool kit
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
			glutInitWindowSize(nWidth, nHeight); //set window size
			glutInitWindowPosition(0, 0); // set window position on screen
			glutCreateWindow("Lab Lighting - Bai 4"); // open the screen window


			myInit();

			glutReshapeFunc(myReshape);
			glutDisplayFunc(myDisplay);
			glutIdleFunc(myIdle);
			glutKeyboardFunc(myKeyboard);

			glutMainLoop();
			return 0;
		}

	}
}