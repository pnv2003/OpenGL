//#include "stdafx.h"
#include <math.h>
#include <vector>
#include <stdexcept>
#include "Mesh.h"
using namespace std;

#define PI			3.1415926
#define DEG2RAD		(3.14159/180.0)
#define	COLORNUM	14


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
								{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };
	
void grid(vector<vector<int>>& lad, const vector<int>& v1, const vector<int>& v2) {
	if (v1.size() != v2.size())
		throw runtime_error("Imbalance grid");
	
	for (int i = 0; i < v1.size(); ++i) {
		if (i < v1.size() - 1) {
			vector<int> face{ v1[i], v1[i + 1], v2[i + 1], v2[i]};
			lad.push_back(face);
		}
		else {
			vector<int> face{ v1[i], v1[0], v2[0], v2[i] };
			lad.push_back(face);
		}
	}
}

void ladder(vector<vector<int>>& lad, const vector<int>& v1, const vector<int>& v2) {
	if (v1.size() != v2.size())
		throw runtime_error("Imbalance ladder");

	for (int i = 0; i < v1.size(); i += 2) {
		if (i == v1.size() - 1) 
			break;

		vector<int> face{ v1[i], v1[i + 1], v2[i + 1], v2[i] };
		lad.push_back(face);
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ) {
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius)
{
	numVerts = nSegment * 4;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	for (i = 0; i < nSegment; i++)
	{
		x = fORadius * cos(fAngle * i);
		z = fORadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	for (i = 0; i < nSegment; i++)
	{
		x = fIRadius * cos(fAngle * i);
		z = fIRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 2 * nSegment].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 3 * nSegment].set(x, y, z);
	}

	numFaces = nSegment * 4;
	face = new Face[numFaces];

	idx = 0;

	/////////////// Outside /////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;

		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	/////////////// Inside ///////////////////////
	for (i = 2 * nSegment; i < 3 * nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if (i < 3 * nSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 2 * nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}
	////////////////  Top ////////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if (i < nSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 0;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}
	//////////////// Bottom ////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + nSegment;

		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + nSegment + 1;
		else
			face[idx].vert[1].vertIndex = nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}

}

void Mesh::CreateCone(int nSegment, float height, float radius) {
	int i;

	numVerts = nSegment + 2;
	pt = new Point3[numVerts];

	float angle = 2 * PI / nSegment;
	
	pt[0].set(0, height, 0);
	pt[1].set(0, 0, 0);

	for (i = 0; i < nSegment; i++) {
		float x = radius * cos(angle * i);
		float y = radius * sin(angle * i);
		pt[i + 2].set(y, 0, x);
	}

	numFaces = nSegment * 2;
	face = new Face[numFaces];

	int idx = 0;

	// side faces
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = (i < nSegment - 1) ? i + 3 : 2;
		idx++;
	}

	// bottom faces
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = (i < nSegment - 1) ? i + 3 : 2;
		face[idx].vert[2].vertIndex = i + 2;
		idx++;
	}
}

void Mesh::CreateHollowCube(int nSegment, float size, float radius) {

	if (nSegment % 8 != 0) {
		throw std::runtime_error("Segment count must be divisible by 8!");
	}
	// note: nSegment must be divisible by 8
	int i;

	numVerts = nSegment * 4;
	pt = new Point3[numVerts];

	float angle = 2 * PI / nSegment;
	float hTop = size / 2;
	float hBot = -size / 2;

	for (i = 0; i < nSegment; i++) {
		float x = radius * cos(angle * i);
		float y = radius * sin(angle * i);
		pt[i].set(y, hTop, x);
		pt[i + nSegment].set(y, hBot, x);
	}

	int nSideSegment = nSegment / 4;
	float segmentSize = size / nSideSegment;
	int idx = nSegment * 2;

	float x = size / 2;
	float y = 0;
	// x, y is now: size/2, 0
	for (i = 0; i < nSideSegment / 2; i++) {
		pt[idx].set(y, hTop, x);
		pt[idx + nSegment].set(y, hBot, x);
		y += segmentSize;
		idx++;
	}

	// x, y is now: size/2, size/2
	for (i = 0; i < nSideSegment; i++) {
		pt[idx].set(y, hTop, x);
		pt[idx + nSegment].set(y, hBot, x);
		x -= segmentSize;
		idx++;
	}

	// x, y is now: -size/2, size/2
	for (i = 0; i < nSideSegment; i++) {
		pt[idx].set(y, hTop, x);
		pt[idx + nSegment].set(y, hBot, x);
		y -= segmentSize;
		idx++;
	}

	// x, y is now: -size/2, -size/2
	for (i = 0; i < nSideSegment; i++) {
		pt[idx].set(y, hTop, x);
		pt[idx + nSegment].set(y, hBot, x);
		x += segmentSize;
		idx++;
	}

	// x, y is now: size/2, -size/2
	for (i = 0; i < nSideSegment / 2; i++) {
		pt[idx].set(y, hTop, x);
		pt[idx + nSegment].set(y, hBot, x);
		y += segmentSize;
		idx++;
	}

	// x, y is now: size/2, 0 (done)


	numFaces = nSegment * 4;
	face = new Face[numFaces];

	vector<int> ptCircleTop;
	vector<int> ptCircleBot;
	vector<int> ptCubeTop;
	vector<int> ptCubeBot;

	for (i = 0; i < nSegment; i++) {
		ptCircleTop.push_back(i);
		ptCircleBot.push_back(i + nSegment);
		ptCubeTop.push_back(i + nSegment * 2);
		ptCubeBot.push_back(i + nSegment * 3);
	}

	vector<vector<int>> faces{};

	grid(faces, ptCircleTop, ptCircleBot);
	grid(faces, ptCircleTop, ptCubeTop);
	grid(faces, ptCubeTop, ptCubeBot);
	grid(faces, ptCircleBot, ptCubeBot);

	for (i = 0; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		for (int j = 0; j < 4; j++) {
			face[i].vert[j].vertIndex = faces[i][j];
		}
	}
}

void Mesh::CreateVerticalFrame(
	double bodyX, double bodyY, double bodyZ,
	double feetLength,
	double feetHeight,
	double feetDistance
) {
	int i;

	numVerts = 16;
	pt = new Point3[numVerts];

	double hTotal = bodyZ + feetDistance + feetHeight;
	double bodyX2 = bodyX / 2;
	double bodyY2 = bodyY / 2;
	double feetX2 = (bodyX + feetLength) / 2;
	double feetY2 = (bodyY + feetLength) / 2;

	double hTop = hTotal / 2;
	double hMid1 = -hTotal / 2 + feetHeight + feetDistance;
	double hMid2 = -hTotal / 2 + feetHeight;
	double hBot = -hTotal / 2;

    pt[0].set(-bodyY2, hTop, bodyX2);
    pt[1].set(-bodyY2, hTop, -bodyX2);
    pt[2].set(bodyY2, hTop, -bodyX2);
    pt[3].set(bodyY2, hTop, bodyX2);

    pt[4].set(-bodyY2, hMid1, bodyX2);
    pt[5].set(-bodyY2, hMid1, -bodyX2);
    pt[6].set(bodyY2, hMid1, -bodyX2);
    pt[7].set(bodyY2, hMid1, bodyX2);

    pt[8].set(-feetY2, hMid2, feetX2);
    pt[9].set(-feetY2, hMid2, -feetX2);
    pt[10].set(feetY2, hMid2, -feetX2);
    pt[11].set(feetY2, hMid2, feetX2);

    pt[12].set(-feetY2, hBot, feetX2);
    pt[13].set(-feetY2, hBot, -feetX2);
    pt[14].set(feetY2, hBot, -feetX2);
    pt[15].set(feetY2, hBot, feetX2);

	numFaces = 14;
	face = new Face[numFaces];

	int faces[14][4] = {
		// top
		{0, 1, 2, 3},

		// side1
		{0, 1, 5, 4},
		{1, 2, 6, 5},
		{2, 3, 7, 6},
		{3, 0, 4, 7},

		// side2
		{4, 5, 9, 8},
		{5, 6, 10, 9},
		{6, 7, 11, 10},
		{7, 4, 8, 11},

		//side3
		{8, 9, 13, 12},
		{9, 10, 14, 13},
		{10, 11, 15, 14},
		{11, 8, 12, 15},

		// bottom
		{12, 13, 14, 15}
	};

	for (i = 0; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		for (int j = 0; j < 4; j++) {
			face[i].vert[j].vertIndex = faces[i][j];
		}
	}
}

void Mesh::CreateHorizontalFrame(
	double bodyX, double bodyY, double bodyZ,
	double feetLength,
	double feetDistance
) {
	int i;

	numVerts = 12;
	pt = new Point3[numVerts];

	double hTotal = bodyZ + feetDistance;
	double bodyX2 = bodyX / 2;
	double bodyY2 = bodyY / 2;
	double feetX2 = bodyX / 2;
	double feetY2 = (bodyY + feetLength) / 2;

	double hTop = hTotal / 2;
	double hMid = -hTotal / 2 + feetDistance;
	double hBot = -hTotal / 2;

    pt[0].set(-bodyY2, hTop, bodyX2);
    pt[1].set(-bodyY2, hTop, -bodyX2);
    pt[2].set(bodyY2, hTop, -bodyX2);
    pt[3].set(bodyY2, hTop, bodyX2);

    pt[4].set(-bodyY2, hMid, bodyX2);
    pt[5].set(-bodyY2, hMid, -bodyX2);
    pt[6].set(bodyY2, hMid, -bodyX2);
    pt[7].set(bodyY2, hMid, bodyX2);

    pt[8].set(-feetY2, hBot, feetX2);
    pt[9].set(-feetY2, hBot, -feetX2);
    pt[10].set(feetY2, hBot, -feetX2);
    pt[11].set(feetY2, hBot, feetX2);

	numFaces = 10;
	face = new Face[numFaces];

	int faces[10][4] = {
		// top
		{0, 1, 2, 3},

		// side1
		{0, 1, 5, 4},
		{1, 2, 6, 5},
		{2, 3, 7, 6},
		{3, 0, 4, 7},

		//side2
		{4, 5, 9, 8},
		{5, 6, 10, 9},
		{6, 7, 11, 10},
		{7, 4, 8, 11},

		// bottom
		{8, 9, 10, 11}
	};

	for (i = 0; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		for (int j = 0; j < 4; j++) {
			face[i].vert[j].vertIndex = faces[i][j];
		}
	}
}

void Mesh::CreateWheel(
	double inR1, double inR2,
	double outR1, double outR2,
	int nSpoke, double spokeWidth,
	double thickness, int nSegment
) {
	numVerts = nSegment * 8 + nSpoke * 8;
	pt = new Point3[numVerts];

	int	i;
	int	idx;
	double angle = 2 * PI / nSegment;
	double x, y, z;

	double hTop = thickness / 2;
	double hBot = -thickness / 2;

	// circles
	// 0 -> nseg*2: inR1
	// nseg*2 -> nseg*4: inR2
	// nseg*4 -> nseg*6: outR1
	// nseg*6 -> nseg*8: outR2
	// 1st half: top, 2nd half: bot
	vector<int> ptIndex{ 0, nSegment * 2, nSegment * 4, nSegment * 6 };
	vector<double> rad{ inR1, inR2, outR1, outR2 };

	for (int j = 0; j < 4; ++j) {
		idx = ptIndex[j];
		double radius = rad[j];

		for (i = 0; i < nSegment; i++)
		{
			x = radius * cos(angle * i);
			y = radius * sin(angle * i);
			z = hTop;
			pt[idx + i].set(x, y, z);

			z = hBot;
			pt[idx + i + nSegment].set(x, y, z);
		}
	}

	// spokes
	// nseg*8 -> nseg*8 + nspoke*4: inR2
	// nseg*8 + nspoke*4 -> nseg*8 + nspoke*8: outR1
	// 1st half: top, 2nd half: bot (each half has 2*nspoke points)
	ptIndex = { 
		nSegment * 8, 
		nSegment * 8 + nSpoke * 4 
	};
	rad = { inR2, outR1 };
	angle = 2 * PI / nSpoke;
	for (i = 0; i < 2; ++i) {
		double theta = asin(spokeWidth / 2 / rad[i]);
		idx = ptIndex[i];
		double radius = rad[i];

		for (int s = 0; s < nSpoke; ++s) {
			x = radius * cos(angle * s - theta);
			y = radius * sin(angle * s - theta);
			z = hTop;
			pt[idx + s*2].set(x, y, z);
			z = hBot;
			pt[idx + s*2 + nSpoke*2].set(x, y, z);

			x = radius * cos(angle * s + theta);
			y = radius * sin(angle * s + theta);
			z = hTop;
			pt[idx + s*2 + 1].set(x, y, z);
			z = hBot;
			pt[idx + s*2 + nSpoke*2 + 1].set(x, y, z);
		}
	}

	numFaces = nSegment * 8 + nSpoke * 4;
	face = new Face[numFaces];

	vector<int> v1{};
	vector<int> v2{};
	vector<int> v3{};
	vector<int> v4{};
	vector<int> v5{};
	vector<int> v6{};
	vector<int> v7{};
	vector<int> v8{};

	vector<int> vs1{};
	vector<int> vs2{};
	vector<int> vs3{};
	vector<int> vs4{};
	vector<int> vs5{};
	vector<int> vs6{};

	for (i = 0; i < nSegment; ++i) {
		v1.push_back(i);
		v2.push_back(i + nSegment);
		v3.push_back(i + nSegment * 2);
		v4.push_back(i + nSegment * 3);
		v5.push_back(i + nSegment * 4);
		v6.push_back(i + nSegment * 5);
		v7.push_back(i + nSegment * 6);
		v8.push_back(i + nSegment * 7);
	}

	for (i = 0; i < nSpoke*2; ++i) {
		vs1.push_back(i + nSegment * 8); // inR2 top
		vs2.push_back(i + nSegment * 8 + nSpoke * 2); // inR2 bot
		vs3.push_back(i + nSegment * 8 + nSpoke * 4); // outR1 top
		vs4.push_back(i + nSegment * 8 + nSpoke * 6); // outR1 bot
	}

	for (i = 0; i < nSpoke * 2; ++i) {
		// inR2 vertical
		vs5.push_back(i + nSegment * 8);
		vs5.push_back(i + nSegment * 8 + nSpoke * 2);

		// outR1 vertical
		vs6.push_back(i + nSegment * 8 + nSpoke * 4);
		vs6.push_back(i + nSegment * 8 + nSpoke * 6);
	}

	vector<vector<int>> faces{};

	// 1-3		5-7
	// | |		| |
	// 2-4		6-8
	grid(faces, v1, v2);
	grid(faces, v2, v4);
	grid(faces, v4, v3);
	grid(faces, v3, v1);

	grid(faces, v5, v6);
	grid(faces, v6, v8);
	grid(faces, v8, v7);
	grid(faces, v7, v5);

	ladder(faces, vs1, vs3);
	ladder(faces, vs2, vs4);
	ladder(faces, vs5, vs6);

	if (faces.size() != numFaces)
		throw runtime_error("nooooo");

	for (i = 0; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		for (int j = 0; j < 4; j++) {
			face[i].vert[j].vertIndex = faces[i][j];
		}
	}
}

void Mesh::CreateSlider(
	double x, double y, double z, 
	double thickness
) {
	int i;

	numVerts = 16;
	pt = new Point3[numVerts];

	double hTop1 = z / 2;
	double hBot1 = -z / 2;
	double hTop2 = (z - thickness) / 2;
	double hBot2 = -(z - thickness) / 2;;

	double xOut = x / 2;
	double yOut = y / 2;
	double xIn = x / 2;
	double yIn = (y - thickness * 2) / 2;

    pt[0].set(-yOut, hTop1, xOut);
    pt[1].set(-yOut, hTop1, -xOut);
    pt[2].set(yOut, hTop1, -xOut);
    pt[3].set(yOut, hTop1, xOut);

    pt[4].set(-yIn, hTop2, xIn);
    pt[5].set(-yIn, hTop2, -xIn);
    pt[6].set(yIn, hTop2, -xIn);
    pt[7].set(yIn, hTop2, xIn);

    pt[8].set(-yIn, hBot2, xIn);
    pt[9].set(-yIn, hBot2, -xIn);
    pt[10].set(yIn, hBot2, -xIn);
    pt[11].set(yIn, hBot2, xIn);

    pt[12].set(-yOut, hBot1, xOut);
    pt[13].set(-yOut, hBot1, -xOut);
    pt[14].set(yOut, hBot1, -xOut);
    pt[15].set(yOut, hBot1, xOut);

	numFaces = 16;
	face = new Face[numFaces];

	int faces[16][4] = {
		// top
		{ 0, 1, 2, 3 },
		{ 0, 3, 7, 4 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 },

		// side1
		{ 0, 1, 13, 12 },
		{ 0, 4, 8, 12 },
		{ 1, 5, 9, 13 },
		{ 4, 5, 9, 8 },

		// side2
		{ 2, 3, 15, 14 },
		{ 2, 6, 10, 14 },
		{ 3, 7, 11, 15 },
		{ 6, 7, 11, 10 },

		// bot
		{ 8, 9, 10, 11 },
		{ 8, 11, 15, 12 },
		{ 9, 10, 14, 13 },
		{ 12, 13, 14, 15 }
	};

	for (i = 0; i < numFaces; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		for (int j = 0; j < 4; j++) {
			face[i].vert[j].vertIndex = faces[i][j];
		}
	}
}