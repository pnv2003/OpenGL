#include <GL/glut.h>

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -2.0, 2.0);
}

void test() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.0, 1.0, 0.0);
	
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, 1.0);
	glVertex2f(0.5, 1.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(-0.5, -1.0);
	glVertex2f(0.5, -1.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL - First window demo");
	glutDisplayFunc(test);

	init();
	glutMainLoop();
}
