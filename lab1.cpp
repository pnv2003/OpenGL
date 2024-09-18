#include <cmath>
#include "lab.h"
#define DEG2RAD (3.14159/180.0)
using namespace std;

namespace Lab1 {
	//-----------------------------------------------------
	void staticSquare() {
		glutCreateWindow("static square");
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

	void dynamicSquare() {
		
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutCreateWindow("dynamic square");
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
	void movingTetrahedron() {
		angle = 0.0;
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("tetrahedron with camera angles");

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
}