#include "math.h"
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#include "lab.h"
#include <GL/glut.h>

#define PI			3.1415926
#define	DEG2RAD(x)	(x*PI)/180.0f

using namespace std;

namespace Assignment {

	int		screenWidth = 1200;
	int		screenHeight = 600;

	Mesh	base;
	Mesh	pin;
	Mesh	vFrameLeft, vFrameRight;
	Mesh	hFrameLeft, hFrameRight;
	Mesh	wheel;
	Mesh	center;
	Mesh	slider;
	Mesh	rodLeft, rodRight;
	Mesh	holderLeft, holderRight;
	Mesh	holderPadLeft, holderPadRight;

	float camera_angle;
	float camera_height;
	float camera_dis;
	float camera_X, camera_Y, camera_Z;
	float lookAt_X, lookAt_Y, lookAt_Z;
	bool color_mode = true;
	bool _2D_mode = false;

	float CAMERA_SPEED = 5;
	float WHEEL_SPEED = 5;

	// model parameters
	GLfloat BASE_H = 0.5;
	GLfloat BASE_L = 7;
	GLfloat BASE_W = 2;
	int BASE_COLOR = 1;// 14;

	GLfloat VFRAME_FOOT_H = 0.3;
	GLfloat VFRAME_FOOT_L = 0.5;
	GLfloat VFRAME_KNEE_H = 0.5;
	GLfloat VFRAME_BODY_H = 5;
	GLfloat VFRAME_BODY_L = 1;
	GLfloat VFRAME_BODY_W = 0.75;
	int VFRAME_COLOR = 2;// 15;

	GLfloat HFRAME_BODY_H = 4;
	GLfloat HFRAME_BODY_L = 0.75;
	GLfloat HFRAME_BODY_W = 1;
	GLfloat HFRAME_KNEE_H = BASE_L * 3 / 4 - VFRAME_BODY_L / 2 - HFRAME_BODY_H;
	GLfloat HFRAME_FOOT_L = 0.5;
	int HFRAME_COLOR = 3;// 15;

	GLfloat WHEEL_RADIUS_CENTER_INNER = 0.5;
	GLfloat WHEEL_RADIUS_CENTER_OUTER = 1;
	GLfloat WHEEL_RADIUS_BORDER_INNER = 2.5;
	GLfloat WHEEL_RADIUS_BORDER_OUTER = 3;
	GLfloat WHEEL_NSPOKE = 5;
	GLfloat WHEEL_WSPOKE = 1;
	GLfloat WHEEL_THICKNESS = 0.5;
	GLfloat WHEEL_SEGMENT = 100;
	int WHEEL_COLOR = 5;// 18;

	GLfloat PIN_RADIUS = 0.1;
	GLfloat PIN_HEIGHT = 0.5;
	int PIN_COLOR = 4;// 15;
	int CENTER_COLOR = 7;// 17;

	GLfloat SLIDER_H = 6;
	GLfloat SLIDER_L = 0.5;
	GLfloat SLIDER_THICKNESS = 0.2;
	GLfloat SLIDER_W = SLIDER_THICKNESS * 2 + PIN_RADIUS * 2;
	int SLIDER_COLOR = 0;// 19;

	GLfloat HOLDER_RADIUS = 0.2;
	GLfloat HOLDER_SIZE = 0.75;
	GLfloat HOLDER_SEGMENT = 16;
	int HOLDER_COLOR = 1;// 16;

	GLfloat ROD_RADIUS = HOLDER_RADIUS;
	GLfloat ROD_LENGTH = 8;
	GLfloat ROD_SEGMENT = HOLDER_SEGMENT;
	int ROD_COLOR = 4;// 19;

	GLfloat TILE_SIZE = 10;
	GLfloat TILE_LIMIT = 50;
	GLfloat DIAG_LINE_POS = 2;
	GLfloat DIAG_LINE_WIDTH = 0.3;
	GLfloat STRAIGHT_LINE_WIDTH = 0.5;
	GLfloat CURVE_RADIUS = DIAG_LINE_POS + DIAG_LINE_WIDTH - STRAIGHT_LINE_WIDTH - 0.2;
	GLfloat SNOWFLAKE_RADIUS = 1.5;
	GLfloat SNOWFLAKE_BORDER_WIDTH = 0.2;
	GLfloat SNOWFLAKE_PADDING = 0.05;
	GLfloat TILE_SEGMENT = 10;

	// state variables
	GLfloat pin_angle = 270;
	GLfloat rotate_direction = 1; // 1 means rotate counter clockwise, -1 means rotate clockwise
	bool auto_rotate = false;
	GLfloat PIN_CENTER_DIST = WHEEL_RADIUS_BORDER_INNER + (WHEEL_RADIUS_BORDER_OUTER - WHEEL_RADIUS_BORDER_INNER) / 2;

	void mySetupCameraVolume()
	{
		if (_2D_mode) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-10, 10, -10, 10, -100, 100);
		} 
		else 
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0f, 1000.0f);
		}
	}

	void changeCameraPos()
	{
		camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
		camera_Y = camera_height;
		camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;

		glutPostRedisplay();
	}

	void setLight() 
	{
		const GLfloat leftLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat leftLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat leftLightAmbColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		const GLfloat leftLightPos[] = { 6.0, 6.0, 6.0, 0.0 };

		const GLfloat rightLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat rightLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const GLfloat rightLightAmbColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		const GLfloat rightLightPos[] = { -6.0, 6.0, -6.0, 0.0 };

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		//set up right light
		glLightfv(GL_LIGHT0, GL_POSITION, rightLightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, rightLightAmbColor);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, rightLightDiffColor);
		glLightfv(GL_LIGHT0, GL_SPECULAR, rightLightSpecColor);
		glEnable(GL_LIGHT0);

		//set up left light
		glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
		glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
		glEnable(GL_LIGHT1);
	}

	void setMaterial(float ambient[], float diffuse[], float specular[], float shininess)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}

	void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
	{
		//code here
		switch (theKey)
		{
		case GLUT_KEY_UP:
			camera_height += 0.1 * CAMERA_SPEED;
			changeCameraPos();
			break;
		case GLUT_KEY_DOWN:
			camera_height -= 0.1 * CAMERA_SPEED;
			changeCameraPos();
			break;
		case GLUT_KEY_LEFT:
			camera_angle += CAMERA_SPEED;
			changeCameraPos();
			break;
		case GLUT_KEY_RIGHT:
			camera_angle -= CAMERA_SPEED;
			changeCameraPos();
			break;
		}
	}

	void myInit()
	{
		float	fHalfSize = 3;

		camera_angle = 0.0;
		camera_height = 2.0;
		camera_dis = 11;
		camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
		camera_Y = camera_height;
		camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	}

	void drawAxis()
	{
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
		glEnd();
	}
	void drawShape(Mesh& mesh, int colorIdx = -1)
	{
		if (color_mode)
		{
			mesh.Draw();
		}
		else
			mesh.DrawWireframe();
	}
	void drawQuartile()
	{
		// only draw a quarter of the tile

		// material properties
		GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // to be set later
		GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat mat_shininess = 200.0f;

		mat_diffuse[0] = 164.0f / 255;
		mat_diffuse[1] = 164.0f / 255;
		mat_diffuse[2] = 164.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		//glNormal3f(0, 1, 0);
		Mesh grayPattern;
		grayPattern.CreateGrayPattern(
			TILE_SIZE,
			DIAG_LINE_POS,
			DIAG_LINE_WIDTH,
			SNOWFLAKE_RADIUS,
			SNOWFLAKE_BORDER_WIDTH,
			SNOWFLAKE_PADDING
		);
		grayPattern.CalculateFacesNorm();
		drawShape(grayPattern);

		mat_diffuse[0] = 105.0f / 255;
		mat_diffuse[1] = 57.0f / 255;
		mat_diffuse[2] = 47.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		Mesh brownPattern;
		brownPattern.CreateBrownPattern(
			TILE_SIZE,
			DIAG_LINE_POS + DIAG_LINE_WIDTH,
			STRAIGHT_LINE_WIDTH,
			CURVE_RADIUS,
			SNOWFLAKE_RADIUS,
			TILE_SEGMENT
		);
		brownPattern.CalculateFacesNorm();
		drawShape(brownPattern);

	/*	glColor3f(1.0f, 0.0f, 0.0f);
		glNormal3f(1, 0, 1);
		glBegin(GL_QUADS);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glVertex3f(3, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(0, 0, 4);
		glVertex3f(0, 0, 3);
		glEnd();*/
	}
	void drawTile(int x, int y)
	{
		// draw a tile at position x, y
		// draw 4 quartiles

		glPushMatrix();
		glTranslatef(x, 0, y);

		drawQuartile();
		glRotatef(90, 0, 1, 0);
		drawQuartile();
		glRotatef(90, 0, 1, 0);
		drawQuartile();
		glRotatef(90, 0, 1, 0);
		drawQuartile();

		glPopMatrix();
	}
    void myDisplay()
    {
		mySetupCameraVolume();

		if (_2D_mode) {
			glViewport(0, -screenHeight / 2, screenWidth, screenHeight * 2);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(
				0.0, BASE_H + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2, camera_dis,
				0.0, BASE_H + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2, 0.0,
				0.0, 1.0, 0.0
			);

			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		else {
			glViewport(0, 0, screenWidth, screenHeight);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(
				camera_X, camera_Y, camera_Z,
				0.0, BASE_H + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2, 0.0,
				0.0, 1.0, 0.0
			);

			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		//drawAxis();
		setLight();

		//glColor3f(0, 0, 0);

		// formula for lighting:
		// IR = Iar 	Par + Idr 	Pdr Lambert + Isr 	Psr phong^f
		// IG = Iag 	Pag + Idg 	Pdg Lambert + Isg 	Psg phong^f
		// IB = Iab 	Pab + Idb 	Pdb Lambert + Isb 	Psb phong^f
		// Iar, Iag, Iab = ambient light intensity
		// Idr, Idg, Idb = diffuse light intensity
		// Isr, Isg, Isb = specular light intensity
		// Par, Pag, Pab = ambient light properties
		// Pdr, Pdg, Pdb = diffuse light properties
		// Psr, Psg, Psb = specular light properties
		// f = shininess constant
		// Lambert = N.L
		// Phong = R.V

		// material properties
		GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // to be set later
		GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat mat_shininess = 50.0f;

		//--------------------------------------------------------------------------------
		// draw base
		// rgb(231, 141, 96)
		mat_diffuse[0] = 231.0f / 255;
		mat_diffuse[1] = 141.0f / 255;
		mat_diffuse[2] = 96.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		base.CreateCuboid(BASE_L, BASE_H, BASE_W);
		base.CalculateFacesNorm();
		glTranslatef(0, BASE_H, 0);		
		drawShape(base, BASE_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw vertical frame 
		// rgb(231, 51, 51)
		mat_diffuse[0] = 231.0f / 255;
		mat_diffuse[1] = 51.0f / 255;
		mat_diffuse[2] = 51.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		vFrameLeft.CreateVerticalFrame(
			VFRAME_BODY_W,
			VFRAME_BODY_L,
			VFRAME_BODY_H,
			VFRAME_FOOT_L,
			VFRAME_FOOT_H,
			VFRAME_KNEE_H
		);
		vFrameLeft.CalculateFacesNorm();
		// put the frame on the base
		glTranslatef(
			-BASE_L * 3 / 4,
			(VFRAME_BODY_H + VFRAME_FOOT_H + VFRAME_KNEE_H) / 2 + BASE_H * 2,
			0
		);

		drawShape(vFrameLeft, VFRAME_COLOR);
		glPopMatrix();

		glPushMatrix();
		vFrameRight.CreateVerticalFrame(
			VFRAME_BODY_W,
			VFRAME_BODY_L,
			VFRAME_BODY_H,
			VFRAME_FOOT_L,
			VFRAME_FOOT_H,
			VFRAME_KNEE_H
		);
		vFrameRight.CalculateFacesNorm();
		// put the frame on the base
		glTranslatef(
			BASE_L * 3 / 4,
			(VFRAME_BODY_H + VFRAME_FOOT_H + VFRAME_KNEE_H) / 2 + BASE_H * 2,
			0
		);
		drawShape(vFrameRight, VFRAME_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw holder
		// rgb(141, 51, 51)
		mat_diffuse[0] = 141.0f / 255;
		mat_diffuse[1] = 51.0f / 255;
		mat_diffuse[2] = 51.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		holderLeft.CreateHollowCube(HOLDER_SEGMENT, HOLDER_SIZE, HOLDER_RADIUS);
		holderLeft.CalculateFacesNorm();
		// put the holder on the vframe
		glTranslatef(
			-BASE_L * 3 / 4,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS + HOLDER_SIZE / 2
		);
		glRotatef(90, 0, 0, 1);
		drawShape(holderLeft, HOLDER_COLOR);
		glPopMatrix();

		glPushMatrix();
		holderRight.CreateHollowCube(HOLDER_SEGMENT, HOLDER_SIZE, HOLDER_RADIUS);
		holderRight.CalculateFacesNorm();
		// put the holder on the vframe
		glTranslatef(
			BASE_L * 3 / 4,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS + HOLDER_SIZE / 2
		);
		glRotatef(90, 0, 0, 1);
		drawShape(holderRight, HOLDER_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw holder pad

		glPushMatrix();
		holderPadLeft.CreateCuboid(HOLDER_SIZE / 2, HOLDER_SIZE / 2, WHEEL_THICKNESS / 2);
		holderPadLeft.CalculateFacesNorm();
		// put the holder pad between the vframe and the holder
		glTranslatef(
			-BASE_L * 3 / 4,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS / 2
		);
		drawShape(holderPadLeft, HOLDER_COLOR);
		glPopMatrix();

		glPushMatrix();
		holderPadRight.CreateCuboid(HOLDER_SIZE / 2, HOLDER_SIZE / 2, WHEEL_THICKNESS / 2);
		holderPadRight.CalculateFacesNorm();
		// put the holder pad between the vframe and the holder
		glTranslatef(
			BASE_L * 3 / 4,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS / 2
		);
		drawShape(holderPadRight, HOLDER_COLOR);
		glPopMatrix();
					
		//--------------------------------------------------------------------------------
		// draw horizontal frame
		// rgb(231, 51, 51)
		mat_diffuse[0] = 231.0f / 255;
		mat_diffuse[1] = 51.0f / 255;
		mat_diffuse[2] = 51.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		hFrameLeft.CreateHorizontalFrame(
			HFRAME_BODY_L,
			HFRAME_BODY_W,
			HFRAME_BODY_H,
			HFRAME_FOOT_L,
			HFRAME_KNEE_H
		);
		hFrameLeft.CalculateFacesNorm();
		// put the frame on the vframe side
		glTranslatef(
			-(HFRAME_BODY_H + HFRAME_KNEE_H) / 2,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			0
		);
		glRotatef(-90, 0, 0, 1);
		drawShape(hFrameLeft, HFRAME_COLOR);
		glPopMatrix();

		glPushMatrix();
		hFrameRight.CreateHorizontalFrame(
			HFRAME_BODY_L,
			HFRAME_BODY_W,
			HFRAME_BODY_H,
			HFRAME_FOOT_L,
			HFRAME_KNEE_H
		);
		hFrameRight.CalculateFacesNorm();
		// put the frame on the vframe side
		glTranslatef(
			(HFRAME_BODY_H + HFRAME_KNEE_H) / 2,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			0
		);
		glRotatef(90, 0, 0, 1);
		drawShape(hFrameRight, HFRAME_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw wheel center
		// rgb(87, 87, 87)
		mat_diffuse[0] = 87.0f / 255;
		mat_diffuse[1] = 87.0f / 255;
		mat_diffuse[2] = 87.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		center.CreateCylinder(100, WHEEL_THICKNESS, WHEEL_RADIUS_CENTER_OUTER - WHEEL_RADIUS_CENTER_INNER);
		center.CalculateFacesNorm();
		// put the wheel on the hframe
		glTranslatef(
			0,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			HFRAME_BODY_L
		);
		// make the center vertical
		glRotatef(90, 1, 0, 0);
		drawShape(center, CENTER_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw wheel
		// rgb(51, 51, 231)
		mat_diffuse[0] = 51.0f / 255;
		mat_diffuse[1] = 51.0f / 255;
		mat_diffuse[2] = 231.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		wheel.CreateWheel(
			WHEEL_RADIUS_CENTER_INNER,
			WHEEL_RADIUS_CENTER_OUTER,
			WHEEL_RADIUS_BORDER_INNER,
			WHEEL_RADIUS_BORDER_OUTER,
			WHEEL_NSPOKE,
			WHEEL_WSPOKE,
			WHEEL_THICKNESS,
			WHEEL_SEGMENT
		);
		wheel.CalculateFacesNorm();
		// put the wheel on the hframe
		glTranslatef(
			0,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			HFRAME_BODY_L
		);
		glRotatef(pin_angle - 270, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		drawShape(wheel, WHEEL_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw pin
		// rgb(231, 51, 51)
		mat_diffuse[0] = 231.0f / 255;
		mat_diffuse[1] = 51.0f / 255;
		mat_diffuse[2] = 51.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		pin.CreateCylinder(10, PIN_HEIGHT, PIN_RADIUS);
		pin.CalculateFacesNorm();
		// put the pin on the wheel
		glTranslatef(
			0,
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2 - WHEEL_RADIUS_BORDER_INNER - (WHEEL_RADIUS_BORDER_OUTER - WHEEL_RADIUS_BORDER_INNER) / 2,
			HFRAME_BODY_L + PIN_HEIGHT / 2 + WHEEL_THICKNESS / 2
		);
		glTranslatef(0, PIN_CENTER_DIST, 0);
		glRotatef(pin_angle - 270, 0, 0, 1);
		glTranslatef(0, -PIN_CENTER_DIST, 0);
		glRotatef(90, 1, 0, 0);
		drawShape(pin, PIN_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw slider
		// rgb(51, 231, 51)
		mat_diffuse[0] = 51.0f / 255;
		mat_diffuse[1] = 231.0f / 255;
		mat_diffuse[2] = 51.0f / 255;
		setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);

		glPushMatrix();
		slider.CreateSlider(
			SLIDER_L,
			SLIDER_W,
			SLIDER_H,
			SLIDER_THICKNESS
		);
		slider.CalculateFacesNorm();

		// put the slider on the pin
		glTranslatef(
			PIN_CENTER_DIST * cos(DEG2RAD(pin_angle)),
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			HFRAME_BODY_L + WHEEL_THICKNESS / 2 + SLIDER_L / 2
		);
		drawShape(slider, SLIDER_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw rod

		glPushMatrix();
		rodLeft.CreateCylinder(ROD_SEGMENT, ROD_LENGTH, ROD_RADIUS);
		rodLeft.CalculateFacesNorm();
		// put the rod on the slider, through the holder
		glTranslatef(
			-ROD_LENGTH / 2 - SLIDER_W / 2 + PIN_CENTER_DIST * cos(DEG2RAD(pin_angle)),
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS + HOLDER_SIZE / 2
		);
		// make the rod horizontal
		glRotatef(90, 0, 0, 1);
		drawShape(rodLeft, ROD_COLOR);
		glPopMatrix();

		glPushMatrix();
		rodRight.CreateCylinder(10, ROD_LENGTH, ROD_RADIUS);
		rodRight.CalculateFacesNorm();
		// put the rod on the slider, through the holder
		glTranslatef(
			ROD_LENGTH / 2 + SLIDER_W / 2 + PIN_CENTER_DIST * cos(DEG2RAD(pin_angle)),
			BASE_H * 2 + VFRAME_FOOT_H + VFRAME_KNEE_H + VFRAME_BODY_H / 2,
			VFRAME_BODY_W / 2 + WHEEL_THICKNESS + HOLDER_SIZE / 2
		);
		// make the rod horizontal
		glRotatef(90, 0, 0, 1);
		drawShape(rodRight, ROD_COLOR);
		glPopMatrix();

		//--------------------------------------------------------------------------------
		// draw floor tiles

		for (float x = -TILE_LIMIT; x <= TILE_LIMIT; x += TILE_SIZE)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(x, 0, TILE_LIMIT);
			glVertex3f(x, 0, -TILE_LIMIT);
			glEnd();

			for (float z = -TILE_LIMIT; z <= TILE_LIMIT; z += TILE_SIZE)
			{
				drawTile(x, z);
			}
		}
		for (float z = -TILE_LIMIT; z <= TILE_LIMIT; z += TILE_SIZE)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(TILE_LIMIT, 0, z);
			glVertex3f(-TILE_LIMIT, 0, z);
			glEnd();

			for (float x = -TILE_LIMIT; x <= TILE_LIMIT; x += TILE_SIZE)
			{
				drawTile(x, z);
			}
		}

		glFlush();
		glutSwapBuffers();
    }

	void rotate()
	{
		pin_angle += WHEEL_SPEED * rotate_direction;
		if (pin_angle >= 360)
			pin_angle -= 360;
		else if (pin_angle < 0)
			pin_angle += 360;
	}

	//void myIdle()
	//{
	//	rotate(); // slow down bruh, it's too fast
	//	cout << pin_angle << endl;
	//	myDisplay();
	//}

	void processTimer(int value)
	{
		if (auto_rotate)
		{
			rotate();
			myDisplay();
			glutTimerFunc(1000 / 60, processTimer, value);
		}
	}

	void myKeyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case '+':
			camera_dis += 0.1 * CAMERA_SPEED;
			changeCameraPos();
			break;
		case '-':
			camera_dis -= 0.1 * CAMERA_SPEED;
			changeCameraPos();
			break;
		case 'w':
		case 'W':
			color_mode = !color_mode;
			break;
		case '1':
			rotate_direction = 1;
			rotate();
			break;
		case '2':
			rotate_direction = -1;
			rotate();
			break;
		case 'a':
		case 'A':
			if (auto_rotate)
			{
				auto_rotate = false;
				//glutIdleFunc(NULL);
				processTimer(0);
			}
			else
			{
				auto_rotate = true;
				//glutIdleFunc(myIdle);
				processTimer(1);
			}
			break;
		case 'b':
		case 'B':
			rotate_direction = -rotate_direction;
			break;
		case 'v':
		case 'V':
			_2D_mode = !_2D_mode;
			break;
		}
		myDisplay();
	}

	int main()
	{
		cout << "+   : to increase camera distance." << endl;
		cout << "-   : to decrease camera distance." << endl;
		cout << "up arrow  : to increase camera height." << endl;
		cout << "down arrow: to decrease camera height." << endl;
		cout << "<-        : to rotate camera clockwise." << endl;
		cout << "->        : to rotate camera counterclockwise." << endl;
		cout << "w/W       : to toggle color mode." << endl;
		cout << "1         : to rotate the wheel counterclockwise." << endl;
		cout << "2         : to rotate the wheel clockwise." << endl;
		cout << "a/A       : to toggle auto rotate." << endl;
		cout << "b/B       : to toggle rotate direction." << endl;

		//glutInit(&argc, (char**)argv); //initialize the tool kit
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
		glutInitWindowSize(screenWidth, screenHeight); //set window size
		glutInitWindowPosition(100, 100); // set window position on screen
		glutCreateWindow("Ngo Van Phuong - 2112070"); // open the screen window

		myInit();
		glutKeyboardFunc(myKeyboard);
		glutDisplayFunc(myDisplay);
		glutSpecialFunc(mySpecialKeyboard);

		glutMainLoop();
		return 0;
	}

}

