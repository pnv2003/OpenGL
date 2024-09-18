#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glut.h>

void drawPoint(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2) {
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

#endif