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
	Vector3		facenorm;

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
	void CalculateFacesNorm();
	void Draw();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius);
	void CreateCone(int nSegment, float height, float radius);
	void CreateHollowCube(int nSegment, float size, float radius);

	// scotch yoke components
	void CreateVerticalFrame(
		float bodyX, float bodyY, float bodyZ, 
		float feetLength,
		float feetHeight,
		float feetDistance
	);
	void CreateHorizontalFrame(
		float bodyX, float bodyY, float bodyZ,
		float feetLength,
		float feetDistance
	);
	void CreateWheel(
		float inR1, float inR2,
		float outR1, float outR2,
		int nSpoke, float spokeWidth,
		float thickness, int nSegment
	);
	void CreateSlider(
		float x, float y, float z, 
		float thickness
	);

	// tile patterns
	void CreateGrayPattern(
		float tileSize,
		float diagPos,
		float diagWidth,
		float snowflakeRadius,
		float snowflakeBorderWidth,
		float snowflakePadding
	);
	void CreateBrownPattern(
		float tileSize,
		float straightPos,
		float straightWidth,
		float curveRadius,
		float snowflakeRadius,
		int nSegment
	);
};

#endif