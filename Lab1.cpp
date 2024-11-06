#include <cmath>
#include "lab.h"
#define DEG2RAD (3.14159/180.0)
using namespace std;

namespace Lab1 {
	//-----------------------------------------------------
	void square() {
		glutCreateWindow("square");
		glutDisplayFunc([]() {
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex2f(-0.5, -0.5);
			glVertex2f(-0.5, 0.5);
			glVertex2f(0.5, 0.5);
			glVertex2f(0.5, -0.5);
			glEnd();
			glFlush();
		});
		glutMainLoop();
	}

	//-----------------------------------------------------
	GLfloat angle = 0.0;

	void processTimer(int value) {
		angle += static_cast<GLfloat>(value);
		if (angle > 360)
			angle -= 360.0;
		glutTimerFunc(100, processTimer, 10);
		glutPostRedisplay();
	}

	void animatedSquare() {
		
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutCreateWindow("animated square");
		glutDisplayFunc([]() {
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0f, 0.0f, 0.0f);

			GLfloat cx, cy;
			cx = 0.5 * cos(angle * DEG2RAD);
			cy = 0.5 * sin(angle * DEG2RAD);

			glBegin(GL_POLYGON);
			glVertex2f(cx - 0.5, cy - 0.5);
			glVertex2f(cx - 0.5, cy + 0.5);
			glVertex2f(cx + 0.5, cy + 0.5);
			glVertex2f(cx + 0.5, cy - 0.5);
			glEnd();
			glFlush();
			glutSwapBuffers();
		});
		glutTimerFunc(100, processTimer, 10);
		glutMainLoop();
	}

	//-----------------------------------------------------
	float tetra_vertices[4][3] = {
		{ 0.0, 0.0, 1.0 },
		{ 0.0, 0.942809, -0.33333 },
		{ -0.816497, -0.471405, -0.333333 },
		{ 0.816497, -0.471405, -0.333333 }
	};

	void tetrahedron() {

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutCreateWindow("tetrahedron");

		// init
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(
			-1, 1, 
			-1, 1, 
			2, 10
		);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.1, 0.7, 0.7, 1.0);

		glutDisplayFunc([]() {
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(
				1.5, 1.5, 1.5,
				0, 0, 0,
				0, 1, 0
			);
			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_TRIANGLES);

			glColor3f(1.0, 0.0, 0.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[2]);
			glVertex3fv(tetra_vertices[1]);

			glColor3f(0.0, 1.0, 0.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[1]);
			glVertex3fv(tetra_vertices[3]);

			glColor3f(0.0, 0.0, 1.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[3]);
			glVertex3fv(tetra_vertices[2]);

			glColor3f(1.0, 0.0, 0.0);
			glVertex3fv(tetra_vertices[3]);
			glVertex3fv(tetra_vertices[1]);
			glVertex3fv(tetra_vertices[2]);

			glEnd();
			glFlush();
			glutSwapBuffers();
		});

		glutReshapeFunc([](int w, int h) {
			int sz = w < h ? w : h;
			glViewport(0, 0, sz, sz);
		});

		glutMainLoop();
	}

	//-----------------------------------------------------
	void animatedTetrahedron() {
		angle = 0.0;
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("animated tetrahedron");

		// init
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(
			-2, 2, 
			-2, 2, 
			2, 10
		);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);

		glutDisplayFunc([]() {
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(
				1.5 * cos(angle * DEG2RAD), 1.5 * sin(angle * DEG2RAD), 3.5,
				0, 0, 0,
				0, 1, 0
			);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_TRIANGLES);

			glColor3f(1.0, 0.0, 0.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[2]);
			glVertex3fv(tetra_vertices[1]);

			glColor3f(0.0, 1.0, 0.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[1]);
			glVertex3fv(tetra_vertices[3]);

			glColor3f(0.0, 0.0, 1.0);
			glVertex3fv(tetra_vertices[0]);
			glVertex3fv(tetra_vertices[3]);
			glVertex3fv(tetra_vertices[2]);

			glColor3f(1.0, 0.0, 0.0);
			glVertex3fv(tetra_vertices[3]);
			glVertex3fv(tetra_vertices[1]);
			glVertex3fv(tetra_vertices[2]);

			glEnd();
			glFlush();
			glutSwapBuffers();
		});

		glutReshapeFunc([](int w, int h) {
			int sz = w < h ? w : h;
			glViewport(0, 0, sz, sz);
		});

		glutTimerFunc(100, processTimer, 10);
		glutMainLoop();
	}

	//-----------------------------------------------------
	void fan() {
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutCreateWindow("fan");

		// init
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
		glClearColor(1.0, 1.0, 1.0, 1.0);

		glutDisplayFunc([]() {
			glClear(GL_COLOR_BUFFER_BIT);

			glColor3d(0.0, 0.0, 0.0);
			glPointSize(5.0);
			glBegin(GL_LINE_LOOP);
			for (int a = 0; a < 360; a += 10) {
				glVertex2d(
					cos(a * DEG2RAD),
					sin(a * DEG2RAD)
				);
			}
			glEnd();

			glBegin(GL_LINES);
			for (int a = 0; a < 360; a += 10) {
				
				glVertex2d(0.0, 0.0);
				glVertex2d(
					cos(a * DEG2RAD),
					sin(a * DEG2RAD)
				);
			}
			glEnd();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			GLdouble fanColors[3][3] = {
				{ 1.0, 0.0, 0.0 },
				{ 0.0, 1.0, 0.0 },
				{ 0.0, 0.0, 1.0 }
			};
			glBegin(GL_TRIANGLES);
			for (int a = 0; a < 360; a += 120) {
				glColor3dv(fanColors[a / 120]);
				glVertex2d(
					cos((a + angle) * DEG2RAD),
					sin((a + angle) * DEG2RAD)
				);
				glVertex2d(
					cos((a + angle + 10) * DEG2RAD),
					sin((a + angle + 10) * DEG2RAD)
				);
				glVertex2d(0, 0);
			}
			glEnd();

			glutSwapBuffers();
		});

		glutTimerFunc(100, processTimer, 10);

		glutMainLoop();
	}
}