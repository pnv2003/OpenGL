#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID* vert;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3* pt;

	int		numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void SetColor(int colorIdx);

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius);
	void CreateCone(int nSegment, float height, float radius);
	void CreateHollowCube(int nSegment, float size, float radius);

	// scotch yoke components
	void CreateVerticalFrame(
		double bodyX, double bodyY, double bodyZ, 
		double feetLength,
		double feetHeight,
		double feetDistance
	);
	void CreateHorizontalFrame(
		double bodyX, double bodyY, double bodyZ,
		double feetLength,
		double feetDistance
	);
	void CreateWheel(
		double inR1, double inR2,
		double outR1, double outR2,
		int nSpoke, double spokeWidth,
		double thickness, int nSegment
	);
	void CreateSlider(
		double x, double y, double z, 
		double thickness
	);

};

#endif