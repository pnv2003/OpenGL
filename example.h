#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <random>
#include <ctime>
#include <GL/glut.h>

using namespace std;

namespace Example {
	namespace Sierpinski2D {
		void init() {
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0.0, 50.0, 0.0, 50.0);
			glMatrixMode(GL_MODELVIEW);
		}

		void display() {
			GLfloat vertices[3][2] = {
				{ 0.0, 0.0 },
				{ 25.0, 50.0 },
				{ 50.0, 0.0 }
			};
			int j, k;
			int n = 5000;
			srand(time(nullptr));
			GLfloat p[2] = { 7.5, 5.0 };

			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_POINTS);
			for (k = 0; k < n; k++) {
				j = rand() % 3;
				p[0] = (p[0] + vertices[j][0]) / 2.0;
				p[1] = (p[1] + vertices[j][1]) / 2.0;
				glVertex2fv(p);
			}
			glEnd();
			glFlush();
		}
	}

	namespace Sierpinski2DRecursive {
		void init() {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
			glMatrixMode(GL_MODELVIEW);
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(0.0, 0.0, 0.0);
		}

		void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
			glVertex2fv(a);
			glVertex2fv(b);
			glVertex2fv(c);
		}

		void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m) {
			GLfloat v0[2], v1[2], v2[2];
			int j;
			if (m > 0) {
				for (j = 0; j < 2; j++) {
					v0[j] = (a[j] + b[j]) / 2;
					v1[j] = (a[j] + c[j]) / 2;
					v2[j] = (b[j] + c[j]) / 2;
				}
				divide_triangle(a, v0, v1, m - 1);
				divide_triangle(c, v1, v2, m - 1);
				divide_triangle(b, v2, v0, m - 1);
			}
			else {
				triangle(a, b, c);
			}
		}

		void display() {
			GLfloat v[3][2] = {
				{ -1.0, -0.58 },
				{ 1.0, -0.58 },
				{ 0.0, 1.15 }
			};
			int n = 4;

			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);
			divide_triangle(v[0], v[1], v[2], n);
			glEnd();
			glFlush();
		}
	}

	namespace Sierpinski3D {
		GLfloat colors[4][3] = {
			{ 1, 1, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 },
			{ 1, 0, 0 }
		};
		int n{};

		void init(int n = 4) {
			Sierpinski3D::n = n;

			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glEnable(GL_DEPTH_TEST);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 1000.0);
		}

		void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
			glVertex3fv(a);
			glVertex3fv(b);
			glVertex3fv(c);
		}

		void tetra(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d) {
			glColor3fv(colors[0]);
			triangle(b, d, c);
			glColor3fv(colors[1]);
			triangle(a, b, c);
			glColor3fv(colors[2]);
			triangle(a, c, d);
			glColor3fv(colors[3]);
			triangle(a, d, b);
		}

		void divide_tetra(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m) {
			GLfloat mid[6][3];
			int j;
			if (m > 0) {
				for (j = 0; j < 3; j++) {
					mid[0][j] = (a[j] + b[j]) / 2;
					mid[1][j] = (b[j] + c[j]) / 2;
					mid[2][j] = (c[j] + a[j]) / 2;
					mid[3][j] = (a[j] + d[j]) / 2;
					mid[4][j] = (b[j] + d[j]) / 2;
					mid[5][j] = (c[j] + d[j]) / 2;
				}
				divide_tetra(a, mid[0], mid[2], mid[3], m - 1);
				divide_tetra(b, mid[0], mid[1], mid[4], m - 1);
				divide_tetra(c, mid[1], mid[2], mid[5], m - 1);
				divide_tetra(d, mid[3], mid[4], mid[5], m - 1);

			}
			else {
				tetra(a, b, c, d);
			}
		}

		void display() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			GLfloat a[3] = { 0, 0, 0 };
			GLfloat b[3] = { 1, 0, 0 };
			GLfloat c[3] = { 0, 1, 0 };
			GLfloat d[3] = { 0, 0, 1 };

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(-1, -1, -1, 0, 0, 0, 0, 1, 0);

			glBegin(GL_TRIANGLES);
			divide_tetra(a, b, c, d, n);
			glEnd();

			glFlush();
		}
	}
}

#endif