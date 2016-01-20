#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

/***************** uc *****************/
#include <iostream>
#include <vector>
using namespace std;

bool isDrawPolygon = true;
bool isDrawPoints = true;
bool isDrawAxes = true;

void drawPolygon(vector <pair<double, double> > &points, double r = 0.0, double g = 0.0, double b = 0.0) {
	if (isDrawPolygon) {
		int n = points.size();
		glColor3f(r, g, b);
		glBegin(GL_LINES); {
			for (int i = 0; i < n; i++) {
				glVertex3f(points[i].first, points[i].second, 0.0);
				glVertex3f(points[(i+1)%n].first, points[(i+1)%n].second, 0.0);
			}
		} glEnd();
	}
}

void drawPoints(vector < pair < pair<double, double>, pair<double, double> > > &points, double r = 0.0, double g = 0.0, double b = 1.0) {
	if (isDrawPoints) {
		glColor3f(r, g, b);
		glPointSize(3);
		glBegin(GL_LINES); {
			for (int i = 0; i < int(points.size()); i++) {
				glVertex3f(points[i].first.first, points[i].first.second, 0);
				glVertex3f(points[i].second.first, points[i].second.second, 0);
			}
		} glEnd();
	}
}

vector <pair<double, double> > polygon;
vector < pair < pair<double, double>, pair<double, double> > > points;
void drawAxes(double r = 0.0, double g = 0.0, double b = 0.0, double halfLength = 200.0)
{
	if (isDrawAxes) {
		glColor3f(r, g, b);
		glBegin(GL_LINES); {
			glVertex3f(halfLength,0,0);
			glVertex3f(-halfLength,0,0);
		} glEnd();
		glBegin(GL_LINES); {
			glVertex3f( 0,halfLength,0);
			glVertex3f(0,-halfLength,0);
		} glEnd();
	}
}
/***************** uc *****************/

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:
			break;
		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){	
			}
			break;
		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(0,1,50, 0,0,0, 0,0,1);
	//gluLookAt(100*cos(cameraAngle), 100*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,-1,150,	0,0,0,	0,0,1);
	
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	
	drawAxes(0.8, 0.8, 0.8, 200.0);
	drawPoints(points, 0, 0, 1);
	drawPolygon(polygon, 0.5, 0.5, 0.5);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate() {
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(1,1,1,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitWindowSize(2000, 2000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Convex Hull");

	init();
	freopen("out.txt", "r", stdin);
	int n;
	cin >> n;
	points.clear();
	for (int i = 0; i < n; i++) {
		double x, y, p, q;
		cin >> x >> y >> p >> q;
		points.push_back(make_pair(make_pair(x, y), make_pair(p, q)));
//		cerr << points.back().first << " " << points.back().second << endl;
	}
	int m;
	cin >> m;
	polygon.clear();
	for (int i = 0; i < m; i++) {
		double x, y;
		cin >> x >> y;
		polygon.push_back(pair<double, double>(x, y));
	}
//	fclose(stdin);

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
