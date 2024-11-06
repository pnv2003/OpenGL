#ifndef LAB_H
#define LAB_H

#include <GL/glut.h>

namespace Lab1 {
	// sample programs
	void square();
	void animatedSquare();
	void tetrahedron();
	void animatedTetrahedron();

	// exercises
	void fan();
}

namespace Lab2 {
	int main(int argc, char* argv[]);
}

namespace LabMesh {
	int main(int argc, char* argv[]);
}

namespace LabTransformation {
	namespace Exercise1 {
		int main(int argc, char* argv[]);
	}

	namespace Exercise2 {
		int main(int argc, char* argv[]);
	}
}

namespace LabCamera {
	int main1(int argc, char* argv[]);
	int main2(int argc, char* argv[]);
	int main3(int argc, char* argv[]);
}

#endif
