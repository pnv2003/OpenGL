#include "example.h"
#include "lab.h"
#include <GL/glut.h>

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//Lab1::square();
	//Lab1::animatedSquare();
	//Lab1::tetrahedron();
	//Lab1::animatedTetrahedron();
	//Lab1::fan();

	Lab2::main(argc, argv);

	return 0;
}
