#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <GL/glut.h>

namespace Tut1 {
	void drawLine(float x1, float y1, float len, float angle, float& x2, float& y2);
	void drawTriangle(float x1, float y1, float len, float angle);
	void drawSquare(float x1, float y1, float len, float angle);
	void drawDecagon(float x1, float y1, float len, float angle);

	void main();
}

namespace Tut2 {
	void drawArcs();

	void main();

	namespace Star {
		int main(int argc, char** argv);
	}
}

namespace Tut3 {
	void drawPolygon();
	void rotatePolygon(float angle);
	void cuboid();

	void main();
}

namespace Tut4 {
	void main();
}

#endif
