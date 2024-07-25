#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <glut.h>





int windowwidth = 800;
int windowheight = 700;
int nooflanes = 6;
float parts;
bool ran = false;
float *xbridges = new float[nooflanes];
float *xcenterbridge = new float[nooflanes];
float *ycenterbridge = new float[nooflanes];
float *ycenterbridgeinverted = new float[nooflanes];
double timonx ;
double timony;
double goalx = 0;
double goaly = 0;
double coinx = 0;
double coiny = 0;
double timonposx;
double timonposy;
double goalposx;
double goalposy;
float laneborderwidth;
float *centerwidthlane = new float[nooflanes];
float timonscale;
int noofcoins = 6;
double rot ;
float coinscale;
float powerupscale;
double powerup1posx = windowwidth+1000;
double powerup1posy = windowheight + 1000;
double powerup2posx = windowwidth + 1000;
double powerup2posy = windowheight + 1000;
float *coinslocx = new float[noofcoins];
float *coinslocy = new float[noofcoins];
bool rancoins = false;
int timonspeed = 4;
int score = 0;
bool gameend = false;
bool timerup = false;
int gametime = 100;  //edit here to change the time
float goalscale;

int len(float arr[])
{
	return nooflanes;
}


void tri(float x1, float y1, float x2, float y2, float x3, float y3, float r,float g,float b) {
	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	glVertex3f(x1, y1, 1);
	glVertex3f(x2, y2, 1);
	glVertex3f(x3, y3, 1);
	glEnd();
}

void quad(float x1,float y1,float x2,float y2,float x3, float y3,float x4, float y4, float r,float g,float b){
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(x1, y1, 1);
	glVertex3f(x2, y2, 1);
	glVertex3f(x3, y3, 1);
	glVertex3f(x4, y4, 1);
	glEnd();
}

void circle(float centerx, float centery,float ra, float r, float g, float b) {
	glPushMatrix();
	glTranslatef(centerx, centery, 0.0f); 
	glColor3f(r, g, b);
	GLUquadric* quad = gluNewQuadric();
	gluDisk(quad, 0, ra, 50, 50); 
	glPopMatrix();



}

void drawtimon(float scx,float scy,float x,float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scx, scy, 1);
	
	glPushMatrix();
	glTranslatef(-350, -450, 0);
	
	glPushMatrix();
	circle(420.0f, 550.0f, 15, 0.3f, 0.2f, 0.0f);
	circle(280.0f, 550.0f, 15, 0.3f, 0.2f, 0.0f);

	tri(250.0f, 550.0f, 450.0f, 550.0f, 350.0f, 650.0f, 0.8f, 0.5f, 0.3f);
	quad(290.0f, 550.0f, 410.0f, 550.0f, 400.0f, 570.0f, 300.0f, 570.0f, 0.9f, 0.7f, 0.5f);


	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(330, 565, 1);
	glVertex3f(340, 560, 1);
	glVertex3f(360, 560, 1);
	glVertex3f(370, 565, 1);
	glEnd();

	glColor3f(0.8f, 0.5f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(300, 520, 1);
	glVertex3f(280, 500, 1);
	glVertex3f(280, 300, 1);
	glVertex3f(300, 280, 1);
	glVertex3f(400, 280, 1);
	glVertex3f(420, 300, 1);
	glVertex3f(420, 500, 1);
	glVertex3f(400, 520, 1);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(370.0f, 615.0f, 1.0f);
	glVertex3f(380.0f, 615.0f, 1.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(320.0f, 615.0f, 1.0f);
	glVertex3f(330.0f, 615.0f, 1.0f);
	glEnd();

	quad(330.0f, 550.0f, 330.0f, 280.0f, 370.0f, 280.0f, 370.0f, 550.0f, 0.9f, 0.7f, 0.5f);

	quad(280.0f, 500.0f, 280.0f, 480.0f, 230.0f, 450.0f, 230.0f, 470.0f, 0.8f, 0.5f, 0.3f);
	quad(230.0f, 470.0f, 230.0f, 450.0f, 200.0f, 480.0f, 200.0f, 500.0f, 0.8f, 0.5f, 0.3f);

	quad(420.0f, 500.0f, 420.0f, 480.0f, 470.0f, 450.0f, 470.0f, 470.0f, 0.8f, 0.5f, 0.3f);
	quad(470.0f, 470.0f, 470.0f, 450.0f, 500.0f, 480.0f, 500.0f, 500.0f, 0.8f, 0.5f, 0.3f);

	quad(300.0f, 280.0f, 300.0f, 230.0f, 320.0f, 230.0f, 320.0f, 480.0f, 0.8f, 0.5f, 0.3f);
	quad(400.0f, 280.0f, 400.0f, 230.0f, 380.0f, 230.0f, 380.0f, 280.0f, 0.8f, 0.5f, 0.3f);

	tri(200.0f, 500.0f, 200.0f, 480.0f, 180.0f, 490.0f, 0.3f, 0.2f, 0.0f);

	tri(500.0f, 500.0f, 500.0f, 480.0f, 520.0f, 490.0f, 0.3f, 0.2f, 0.0f);

	tri(300.0f, 230.0f, 320.0f, 230.0f, 310.0f, 210.0f, 0.3f, 0.2f, 0.0f);

	tri(400.0f, 230.0f, 380.0f, 230.0f, 390.0f, 210.0f, 0.3f, 0.2f, 0.0f);

	glPushMatrix();
	glTranslatef(260, 490, 0);
	glScalef(0.25, 0.25, 1);
	tri(250.0f, 550.0f, 450.0f, 550.0f, 350.0f, 650.0f, 0.6f, 0.1f, 0.0f);
	glPopMatrix();


	tri(280.0f, 400.0f, 280.0f, 380.0f, 300.0f, 390.0f, 0.3f, 0.2f, 0.0f);
	tri(280.0f, 450.0f, 280.0f, 430.0f, 300.0f, 440.0f, 0.3f, 0.2f, 0.0f);
	tri(280.0f, 350.0f, 280.0f, 330.0f, 300.0f, 340.0f, 0.3f, 0.2f, 0.0f);

	tri(420.0f, 400.0f, 420.0f, 380.0f, 400.0f, 390.0f, 0.3f, 0.2f, 0.0f);
	tri(420.0f, 450.0f, 420.0f, 430.0f, 400.0f, 440.0f, 0.3f, 0.2f, 0.0f);
	tri(420.0f, 350.0f, 420.0f, 330.0f, 400.0f, 340.0f, 0.3f, 0.2f, 0.0f);





	circle(350.0f, 590.0f, 15, 0.3f, 0.2f, 0.0f);
	circle(380.0f, 600.0f, 10, 1.0f, 1.0f, 1.0f);
	circle(320.0f, 600.0f, 10, 1.0f, 1.0f, 1.0f);
	circle(380.0f, 600.0f, 5, 0.0f, 0.0f, 0.0f);
	circle(320.0f, 600.0f, 5, 0.0f, 0.0f, 0.0f);
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawcoin(float scx, float scy, float x, float y) {
	glPushMatrix();
	glTranslated(x, y, 0);
   glRotated(rot, 0, 0, 1);
   glTranslated(-x, -y, 0);
	glTranslatef(x, y, 0);
	glScalef(scx, scy, 1);

	glPushMatrix();
	glTranslated(-380, -600, 0);
	circle(380.0f, 600.0f, 50, 0.9f, 0.9f, 0.9f);
	circle(380.0f, 600.0f, 35, 0.9f, 0.7f, 0.3f);


	glPushMatrix();

	glScalef(0.5, 0.5, 1);
	glTranslatef(390.0f, 565.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_STRIP);
	glVertex3f(330.0f, 640.0f, 0.0f);
	glVertex3f(330.0f, 650.0f, 0.0f);
	glVertex3f(340.0f, 660.0f, 0.0f);
	glVertex3f(370.0f, 680.0f, 0.0f);
	glVertex3f(400.0f, 660.0f, 0.0f);
	glVertex3f(420.0f, 630.0f, 0.0f);
	glVertex3f(380.0f, 600.0f, 0.0f);
	glVertex3f(340.0f, 620.0f, 0.0f);
	glVertex3f(340.0f, 630.0f, 0.0f);
	glVertex3f(390.0f, 630.0f, 0.0f);
	glVertex3f(390.0f, 620.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glVertex3f(370.0f, 650.0f, 0.0f);
	glVertex3f(370.0f, 590.0f, 0.0f);
	glEnd();



	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	

}
void drawgoal(float scx, float scy, float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scx, scy, 1);
	glPushMatrix();
	glTranslated(-225, -150, 0);
	glPushMatrix();
	tri(150, 150, 200, 150, 175, 175, 1, 0.5, 0.3);
	tri(200, 150, 250, 150, 225, 175, 1, 0.5, 0.3);
	tri(250, 150, 300, 150, 275, 175, 1, 0.5, 0.3);
	tri(300, 150, 350, 150, 325, 175, 1, 0.5, 0.3);
	tri(150, 150, 200, 150, 175, 125, 0.9, 0.4, 0.3);
	tri(200, 150, 250, 150, 225, 125, 0.9, 0.4, 0.3);
	tri(250, 150, 300, 150, 275, 125, 0.9, 0.4, 0.3);
	tri(300, 150, 350, 150, 325, 125, 0.9, 0.4, 0.3);
	circle(125, 150, 25, 1, 0.5, 0.3);
	circle(135.0f, 145.0f, 5, 0.0f, 0.0f, 0.0f);
	circle(115.0f, 145.0f, 5, 0.0f, 0.0f, 0.0f);

	glColor3f(1, 0.5, 0.3);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 116, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawpowerup1(float scx, float scy, float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scx, scy, 1);
	glPushMatrix();
	glTranslatef(-350, -315, 0);
	glPushMatrix();
	glTranslated(390, 370, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(430, 380, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(390, 190, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(419, 200, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(510, 370, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(467, 380, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(510, 190, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(480, 200, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.1, 0.3, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	circle(350, 450, 30, 0.1, 0.3, 0);
	quad(350, 420, 450, 370, 350, 150, 250, 370, 0, 1, 0);

	glColor3f(0.1, 0.3, 0);

	glBegin(GL_LINES);
	glVertex3f(350, 480, 0);
	glVertex3f(390, 560, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(350, 480, 0);
	glVertex3f(310, 560, 0);
	glEnd();

	glPopMatrix();
	glPopMatrix();

}

void drawpowerup2(float scx, float scy, float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scx, scy, 1);
	glPushMatrix();
	glTranslatef(-350, -315, 0);
	glPushMatrix();
	glTranslated(390, 370, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(430, 380, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(390, 190, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(419, 200, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(135, 126, 0);
	glVertex3f(140, 121, 0);
	glVertex3f(135, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(510, 370, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(467, 380, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 116, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(510, 190, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(480, 200, 0);
	glPushMatrix();
	glScaled(10, 10, 1);
	glTranslated(-135, -116, 0);
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.2);
	glBegin(GL_LINE_STRIP);
	glVertex3f(115, 126, 0);
	glVertex3f(110, 121, 0);
	glVertex3f(115, 110, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	circle(350, 450, 30, 0.9, 0.4, 0.2);
	quad(350, 420, 450, 370, 350, 150, 250, 370, 0.7, 0.1, 0);

	glColor3f(0.9, 0.4, 0.2);

	glBegin(GL_LINES);
	glVertex3f(350, 480, 0);
	glVertex3f(390, 560, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(350, 480, 0);
	glVertex3f(310, 560, 0);
	glEnd();

	glPopMatrix();
	glPopMatrix();

}

void buildborders() {
	int xborder = 0;
	int yborder = 0;



	while (xborder < windowwidth) {
		quad(xborder, 0, xborder, 30, xborder + 30, 30, xborder + 30, 0, 0.1, 0.2, 0);
		quad(xborder, windowheight - 30, xborder, windowheight, xborder + 30, windowheight, xborder + 30, windowheight - 30, 0.1, 0.2, 0);
		tri(xborder, 15, xborder + 30, 15, xborder + 15, 30, 1, 0, 0);
		tri(xborder, 15, xborder + 30, 15, xborder + 15, 0, 1, 0, 0);
		tri(xborder, windowheight - 15, xborder + 30, windowheight - 15, xborder + 15, windowheight, 1, 0, 0);
		tri(xborder, windowheight - 15, xborder + 30, windowheight - 15, xborder + 15, windowheight - 30, 1, 0, 0);
		circle(xborder + 15, 15, 5, 0.9, 1, 0);
		circle(xborder + 15, windowheight - 15, 5, 0.9, 1, 0);
		xborder = xborder + 30;
	}

	while (yborder < windowheight) {
		quad(0, yborder, 0, yborder + 30, 30, yborder + 30, 30, yborder, 0.1, 0.2, 0);
		quad(windowwidth - 30, yborder, windowwidth - 30, yborder + 30, windowwidth, yborder + 30, windowwidth, yborder, 0.1, 0.2, 0);
		tri(0, yborder + 15, 30, yborder + 15, 15, yborder + 30, 1, 0, 0);
		tri(0, yborder + 15, 30, yborder + 15, 15, yborder, 1, 0, 0);
		tri(windowwidth - 30, yborder + 15, windowwidth, yborder + 15, windowwidth - 15, yborder + 30, 1, 0, 0);
		tri(windowwidth - 30, yborder + 15, windowwidth, yborder + 15, windowwidth - 15, yborder, 1, 0, 0);
		circle(15, yborder + 15, 5, 0.9, 1, 0);
		circle(windowwidth - 15, yborder + 15, 5, 0.9, 1, 0);
		yborder = yborder + 30;
	}

}

void generatelanes(int nooflanes) {
	int xborder = 0;
	int y = 30;
	int playablearea = windowheight - 60;
	parts = playablearea / (nooflanes + 1);
	laneborderwidth = parts / (nooflanes - 1);
	for (int i = 0; i < nooflanes-1; i++) {
			while (xborder < windowwidth) {
				quad(xborder, y + parts, xborder, y + parts + laneborderwidth, xborder + 20, y + parts + laneborderwidth, xborder + 20, y + parts, 0.1, 0.2, 0);
				tri(xborder, y +parts+ (laneborderwidth/2), xborder + 20, y+parts + (laneborderwidth / 2), xborder + 10 , y +parts + laneborderwidth, 1, 0, 0);
				tri(xborder, y +parts+ (laneborderwidth/2), xborder + 20, y+parts + (laneborderwidth / 2), xborder + 10, y+parts, 1, 0, 0);
				circle(xborder + 10, y +parts + (laneborderwidth / 2), 2, 0.9, 1, 0);
				xborder = xborder + 20;
			}
			xborder = 0;
		y = y + parts + laneborderwidth;
	}
}
void buildbridge(int nooflanes,float timonwidth) {
	int y = 30;
	int lanewidth = timonwidth;
	int playablearea = windowheight - 60;
	 parts = playablearea / (nooflanes + 1);
	 laneborderwidth = parts / (nooflanes - 1);
	if (ran == true) {
		for (int i = 0; i < nooflanes-1; i++) {
			quad(xbridges[i], y + parts, xbridges[i], y + parts + laneborderwidth, xbridges[i] + timonwidth, y + parts + laneborderwidth, xbridges[i] + timonwidth, y + parts, 0.5, 0.3, 0.2);
			y = y + parts + laneborderwidth;
		}	
	}
	else {
		for (int i = 0; i < nooflanes-1; i++) {
			float x = rand() % (windowwidth - 62 - lanewidth)+32;
			quad(x, y + parts, x, y + parts + laneborderwidth, x + timonwidth, y + parts + laneborderwidth, x + timonwidth, y + parts, 0.5, 0.3, 0.2);
			xbridges[i] = x;
			xcenterbridge[i] = x + (lanewidth/2); 
			y = y + parts + laneborderwidth;
			ycenterbridge[i] = y - laneborderwidth - (parts / 2)+3;
			ycenterbridgeinverted[i] = y + (parts / 2) - 3; ;
			centerwidthlane[i] = y;

			
			
		}
		
		ran = true;
	}
}
void spe(int key,int x,int y) {
	if (key == GLUT_KEY_RIGHT) {
		for (int i = 0; i < len(xcenterbridge); i++) {
			if (timonposy<centerwidthlane[i]+20 && timonposy>(centerwidthlane[i] - laneborderwidth-20))
				return;
		}
		if (timonposx < (windowwidth - (38 + (timonscale * 150)))) 
			timonx += timonspeed;
		
	}
	if (key == GLUT_KEY_LEFT) {
		for (int i = 0; i < len(xcenterbridge); i++) {
			if (timonposy<centerwidthlane[i] + 20 && timonposy>(centerwidthlane[i] - laneborderwidth - 20))
				return;
		}
		if(timonposx > 35+(timonscale*150))
		timonx -= timonspeed;
	}
	if (key == GLUT_KEY_UP) {
		for (int i = 0; i < len(xcenterbridge); i++) {
			if (xcenterbridge[i] - 7 < timonposx && timonposx < xcenterbridge[i] + 7 && timonposy < ycenterbridgeinverted[i] && (ycenterbridge[i] - timonposy) < (2 * parts) && timonposy < windowheight - 30 + (parts / 2)) 
				timony += timonspeed;
		}
	}
	if (key == GLUT_KEY_DOWN) {
		for (int i = 0; i < len(xcenterbridge); i++) {
			if (xcenterbridge[i] - 7 < timonposx && timonposx < xcenterbridge[i] + 7) {
				if (timonposy > ycenterbridge[i] && (timonposy - ycenterbridge[i]) < (2 * parts) && timonposy > 30 + (parts / 2))
					timony -= timonspeed;
			}
		}
	}
	glutPostRedisplay();
}

void Anim() {
		rot += 2;
	glutPostRedisplay();
}

void generatecoinsloc() {
	int y = 30;
	float* lanesavailable = new float[nooflanes];
	if (rancoins == false) {
		for (int i = 0; i < len(lanesavailable); i++) {
			lanesavailable[i] = y + (parts / 2);
			y = y + parts + laneborderwidth;
			//std::cout << lanesavailable[i] << " , ";
		}
		for (int i = 0; i < noofcoins; i++) {
			float x = rand() % (windowwidth - 200) + 150;
			coinslocx[i] = x;
			int n = rand() % (nooflanes);
			coinslocy[i] = lanesavailable[n];
			if (i > 0) {
			for (int y = 0; y < i; y++) {
				while ((coinslocx[i] > coinslocx[y] - 300 && coinslocx[i] < coinslocx[y]  + 200 && coinslocy[y] == coinslocy[i]) || (coinslocx[i] > windowwidth - 200 && coinslocy[i]>goalposy-50 && coinslocy[i]<goalposy+50)) {
					float x = rand() % (windowwidth - 350 ) + 150;
					coinslocx[i] = x;
					int n = rand() % (nooflanes);
					coinslocy[i] = lanesavailable[n];
				}
			}
		}
			//std::cout << coinslocx[i] << ",";
		}
	}
	rancoins = true;
}

void bridgetimer(int val) {
	bool in = false;
	for(int i = 0; i < len(ycenterbridge); i++) {
		if (timonposy > ycenterbridge[i] + parts/2-25 && timonposy < ycenterbridge[i] + parts/2 + laneborderwidth+25) {
			in = true;
			}
	}
	if (in == false) {
	int lanewidth = (timonscale * 300) + 10;
	for (int i = 0; i < len(xcenterbridge); i++) {
		float x = rand() % (windowwidth - 62 - lanewidth) + 32;
		xbridges[i] = x;
		xcenterbridge[i] = x + (lanewidth / 2);
		glutPostRedisplay();
		

	}
	}
	//std::cout << xcenterbridge[5] << "," << timonposx << ",";

	glutTimerFunc(5000, bridgetimer, val);
}

void powerup1timer(int val) {
	int y = 30;
	int powerupwidth = powerupscale * 150;
	if (powerup1posx == windowwidth + 1000 && powerup1posy == windowheight + 1000) {
		float* lanesavailable = new float[nooflanes];
		for (int i = 0; i < len(lanesavailable); i++) {
			lanesavailable[i] = y + (parts / 2);
			y = y + parts + laneborderwidth;
			//std::cout << lanesavailable[i] << " , ";
		}
		powerup1posx = rand() % (windowwidth - 100 - powerupwidth) + 40;
		int n = rand() % (nooflanes - 2)+1;
		powerup1posy = lanesavailable[n] - 5;
		for (int i = 0; i < noofcoins ; i++) {
			while (powerup1posx > coinslocx[i] - 150 && powerup1posx < coinslocx[i] + 150 && powerup1posy > coinslocy[i] - 50 && powerup1posy < coinslocy[i] + 50 || powerup1posy > windowwidth - 200 && powerup1posy > goalposy -60 && powerup1posy < goalposy + 50) {
				powerup1posx = rand() % (windowwidth - 100 - powerupwidth) + 32;
				int n = rand() % (nooflanes - 2) +1;
				powerup1posy = lanesavailable[n] - 5;
			}
		}
		

	}

	//std::cout << powerup1posx << "," << powerup1posy << ",";
	glutPostRedisplay();

}
void powerup2timer(int value) {
	int y = 30;
	int powerupwidth = powerupscale * 150;
	if (powerup2posx == windowwidth + 1000 && powerup2posy == windowheight + 1000) {
		float* lanesavailable = new float[nooflanes];
		for (int i = 0; i < len(lanesavailable); i++) {
			lanesavailable[i] = y + (parts / 2);
			y = y + parts + laneborderwidth;
			//std::cout << lanesavailable[i] << " , ";
		}
		powerup2posx = rand() % (windowwidth - 100 - powerupwidth) + 32;
		int n = rand() % (nooflanes - 1);
		powerup2posy = lanesavailable[n] - 5;
		for (int i = 0; i < noofcoins; i++) {
			while (powerup2posx > coinslocx[i] - 150 && powerup2posx < coinslocx[i] + 150 && powerup2posy > coinslocy[i] - 50 && powerup1posy < coinslocy[i] + 50 || powerup2posy > windowwidth - 200 && powerup2posy > goalposy - 80 && powerup2posy < goalposy + 80 || powerup1posx == powerup2posx && powerup1posy == powerup2posy) {
				powerup2posx = rand() % (windowwidth - 100 -  powerupwidth) + 40;
				int n = rand() % (nooflanes - 1);
				powerup2posy = lanesavailable[n] - 5;
			}
		}

	}
}
void powerupdurationtimer(int ts) {
	timonspeed -= 1;
}
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void endgame() {
	exit(0);
}

void gamewin(int val) {
	endgame();
}

void gametimer(int val) {
	if (gameend == false) {
		gameend = true;
		timerup = true;
	}
	glutPostRedisplay();
}

void countdown(int val) {
	gametime -= 1;
	glutPostRedisplay();
	glutTimerFunc(1000, countdown, 0);
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (gameend == false) {
		glPushMatrix();
		quad(0, 0, 0, windowheight, windowwidth, windowheight, windowwidth, 0, 0.9, 0.8, 0.4);
		glPopMatrix();
		generatelanes(nooflanes);
		buildborders();
		timonscale = parts / 440;
		powerupscale = parts / 450;
		timonposx = 35 + (timonscale * 150);
		timonposy = windowheight - (30 + (parts / 2));
		goalscale = (parts / 150) - 0.2;
		float goalpos = 30 + (goalscale * 125) + 5;
		coinscale = parts / 100;
		buildbridge(nooflanes, (timonscale * 300) + 10);
		glPushMatrix();
		glTranslated(timonx, timony, 0);
		drawtimon(timonscale - 0.01, timonscale - 0.01, timonposx, windowheight - (30 + (parts / 2)));
		timonposx = timonposx + timonx;
		timonposy = timonposy + timony;
		glPopMatrix();
		float goalposx = windowwidth - (goalscale * 250);
		float goalposy = 30 + parts / 2;
		glPushMatrix();
		glTranslated(goalx, goaly, 0);
		drawgoal(goalscale, goalscale, windowwidth - goalpos, 30 + (parts / 2));
		if (timonposx < goalposx + 10 && timonposx > goalposx - 10 && timonposy > goalposy - 10 && timonposy < goalposy + 10) {
			goalx = windowwidth + 1000;
			goaly = windowheight + 1000;
			gameend = true;
			glutPostRedisplay();
		}
		glPopMatrix();
		glPushMatrix();
		generatecoinsloc();
		for (int i = 0; i < noofcoins; i++) {
			glPushMatrix();
			drawcoin(coinscale - 0.2, coinscale - 0.2, coinslocx[i], coinslocy[i]);
			if (timonposx < coinslocx[i] + 10 && timonposx > coinslocx[i] - 10 && timonposy > coinslocy[i] - 10 && timonposy < coinslocy[i] + 10) {
				coinslocx[i] = windowwidth + 1000;
				coinslocy[i] = windowheight + 1000;
				PlaySound(TEXT("sounds/coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
				score = score + 10;
			}
			glutPostRedisplay();
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		drawpowerup1(powerupscale - 0.01, powerupscale - 0.01, powerup1posx, powerup1posy);
		if (timonposx < powerup1posx + 10 && timonposx > powerup1posx - 10 && timonposy > powerup1posy - 15 && timonposy < powerup1posy + 15) {
			powerup1posx = windowwidth + 1000;
			powerup1posy = windowheight + 1000;
			for (int i = 0; i < len(xcenterbridge); i++) {
				if (timonposy > ycenterbridge[i] && (timonposy - ycenterbridge[i]) < (2 * parts)) {
					xbridges[i] = timonposx - timonscale * 150;
					xcenterbridge[i] = timonposx;
					glutPostRedisplay();
				}
			}
			PlaySound(TEXT("sounds/powerup1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutTimerFunc(10000, powerup1timer, 0);
		}
		glPopMatrix();
		glPushMatrix();
		drawpowerup2(powerupscale - 0.01, powerupscale - 0.01, powerup2posx, powerup2posy);
		if (timonposx < powerup2posx + 10 && timonposx > powerup2posx - 10 && timonposy > powerup2posy - 15 && timonposy < powerup2posy + 15) {
			powerup2posx = windowwidth + 1000;
			powerup2posy = windowheight + 1000;
			timonspeed += 2;
			PlaySound(TEXT("sounds/powerup2.wav"), NULL, SND_FILENAME | SND_ASYNC);
			glutTimerFunc(2000, powerupdurationtimer, 0); // bosts timon speed by 1 for 2 secs
			glutTimerFunc(15000, powerup2timer, 0);
		}
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(10, windowheight - 20, (char*)p0s);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		char* pos[20];
		sprintf((char*)pos, "Time: %d", gametime);
		print(windowwidth - 200, windowheight - 20, (char*)pos);
		glPopMatrix();
		glutSpecialFunc(spe);
		glFlush();
	}
	else if (gameend && !timerup){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		quad(0, 0, 0, windowheight, windowwidth, windowheight, windowwidth, 0, 0.9, 0.8, 0.4);
		glPopMatrix();
		buildborders();
		glPushMatrix();
		glColor3f(0, 0, 0);
		char* pos[20];
		sprintf((char*)pos, "you won! Score: %d", score+20);
		print(windowwidth/2-100,windowheight/2, (char*)pos);
		glPopMatrix();
		glFlush();
		glutTimerFunc(8000, gamewin, 0);
		PlaySound(TEXT("sounds/win.wav"), NULL, SND_FILENAME);
		PlaySound(TEXT("sounds/win2.wav"), NULL, SND_FILENAME);
		


	}
	if (timerup) {
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		quad(0, 0, 0, windowheight, windowwidth, windowheight, windowwidth, 0, 0.9, 0.8, 0.4);
		glPopMatrix();
		buildborders();
		glPushMatrix();
		glColor3f(0, 0, 0);
		char* pos[20];
		sprintf((char*)pos, "Time's up! try again, Score: %d", score);
		print(windowwidth / 2 - 100, windowheight / 2, (char*)pos);
		glPopMatrix();
		glFlush();
		glutTimerFunc(5000, gamewin, 0);
		PlaySound(TEXT("sounds/lose.wav"), NULL, SND_FILENAME);
		
		
	}
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(windowwidth, windowheight);
	glutInitWindowPosition(int(windowwidth/2), int(windowheight/2));

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutTimerFunc(5000, bridgetimer, 0);
	glutTimerFunc(10000, powerup1timer, 0);
	glutTimerFunc(15000, powerup2timer, 0);
	glutTimerFunc(gametime * 1000, gametimer, 0);
	glutTimerFunc(1000, countdown, 0);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0, windowwidth,0, windowheight);

	glutMainLoop();
}
