#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define BLACK 0, 0, 0
#define M_PI 3.1415923

/****************************************************************
/Function Prototype
*****************************************************************/
void drawTable();
void drawChandelier();
void drawGlobe();
void drawGlobeStand();
void drawTableThings();
void drawPlate();
void drawCandle();
void drawBowl();
void drawWall();
void drawMirror();
void drawScreen();
void drawTowel();
void drawShowCase();
void showCaseBar();
void showCaseDoor();
void showCaseRack();
void showCaseDrawer();
void drawerNob();
void doorNob();
void drawShowCaseThings();
void showCasePlate();
void showCaseGlass();
void screenSegment();
void drawSideChair();
void sideChairLeg();
void sideChairBackLeg();
void sideChairSeat();
void sideChairAdditionalPart();
void drawAllSideChairs();
void drawHostChair();
void hostChairSeat();
void hostChairBack();
void hostChairBackLeg();
void hostChairHandle();
void drawAllHostChair();
void drawFloor();
void drawGrid();
void glutCircle(float cx, float cy, float r, int num_segments);
void glutSolidCircle(float r, int num_segments);
void glutSolidCylinder(float r, float height, int nothing, int num_segments);
void glutWireCylinder(float r, float height, int slices, int num_segments);

/****************************************************************
/Global Variables
*****************************************************************/

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;
int stopCamera=1;
int changeLookAt;

double cameraHeight;	
double cameraRadius;

double globeAngle; //in degree

double cameraAxisAngle;			//in radian
double cameraLookAtHeight;

int canDrawGrid;


double cameraX;
double cameraY;

double lookAtX;
double lookAtY;

float mirrorCylinder[50];

/****************************************************************
/main functions openGL
*****************************************************************/

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
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
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
	//gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	//gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	
	cameraX=cameraRadius*cos(cameraAngle);
	cameraY=cameraRadius*sin(cameraAngle);
	
	if(changeLookAt==1){
		lookAtX=cameraRadius*cos(cameraAxisAngle)+cameraX;
		lookAtY=cameraRadius*sin(cameraAxisAngle)+cameraY;
		changeLookAt=0;
	}
	//cameraRadius*cos(cameraAxisAngle)+cameraX,cameraRadius*sin(cameraAxisAngle)+cameraY
	//camera Axis Rotation
	gluLookAt(cameraX, cameraY, cameraHeight,	lookAtX,lookAtY,cameraLookAtHeight,	0,0,1);
	
	
	//gluLookAt(cameraX, cameraY, cameraHeight,	0,0,0,	0,0,1);

	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	drawGrid();
	/****************************
	/ Add your objects from here
	****************************/
	
	
	drawTable();
	drawChandelier();
	drawGlobe();
	drawGlobeStand();
	glPushMatrix();{
		glTranslatef(0,0,0.2);
		drawTableThings();
	}glPopMatrix();
	drawWall();
	drawMirror();
	drawScreen();
	drawTowel();
	glPushMatrix();{
		glTranslatef(-88+.2,-20,0);
		glScalef(.6,1.2,1);
		drawShowCase();
	}glPopMatrix();
	
	drawAllSideChairs();
	
	drawAllHostChair();
	glPushMatrix();{
		glTranslatef(.4,0,0);
		drawShowCaseThings();
	}glPopMatrix();

	drawFloor();
	
	


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Camera
	if(stopCamera==0){
		cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!
	}

	globeAngle+=1;
	if(globeAngle==360){
		globeAngle=0;
	}

	//codes for any changes in Models
	
	//rectAngle -= 1;

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
			cameraAngleDelta = -cameraAngleDelta;
			break;

		case '2':	//increase rotation of camera by 10%
			cameraAngleDelta *= 1.1;
			break;

		case '3':	//decrease rotation
			cameraAngleDelta /= 1.1;
			break;

		case '8':	//toggle grids
			canDrawGrid = 1 - canDrawGrid;
			break;

		case 27:	//ESCAPE KEY -- simply exit
			exit(0);
			break;

		case 'w':
			cameraLookAtHeight+=10;
			break;
		case 's':
			cameraLookAtHeight-=10;
			break;
		case 'a':
			changeLookAt=1;
			cameraAxisAngle+=.1;
			break;
		case 'd':
			changeLookAt=1;
			cameraAxisAngle-=.1;
			break;
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight += 10;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight -= 10;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle -= .05;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle += .05;
			break;

		case GLUT_KEY_PAGE_UP:
			cameraRadius += 10;
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(cameraRadius > 10)
				cameraRadius -= 10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				cameraAngleDelta = -cameraAngleDelta;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				stopCamera=1-stopCamera;
			}
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void init(){
	//codes for initialization
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	globeAngle=0;
	canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;

	for(int i=0;i<50;i++){
		mirrorCylinder[i]=rand()%5+10;
	}

	//clear the screen
	glClearColor(BLACK, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

void drawFloor(){
	glColor3f(0.75,0.65,0.46);
	glPushMatrix();{
		glTranslatef(0,0,-3.2);
		glScalef(210, 210, 6);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(0,0,-.1);
		glBegin(GL_QUADS);{
			glVertex3f(-100,-100,0);glColor3f(0.75,0.65,0.46);
			glVertex3f(-100,100,0);glColor3f(0.75,0.65,0.46);
			glVertex3f(100,100,0);glColor3f(0.55,0.65,0.46);
			glVertex3f(100,-100,0);glColor3f(0.9,0.9,0.9);
		}glEnd();
	}glPopMatrix();
	/*
	glColor3f(0.1,0.1,0.1);
	glPushMatrix();{
		glTranslatef(0,0,.25);
		glScalef(150, 130,-.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	*/
}


void drawTable(){
	
	glColor3f(0.2,0.25,0.2);
	glPushMatrix();{
		glTranslatef(0,0,34);
		glScalef(90, 50, 2);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0,0,35.1);
		glColor3f(0.8,0.5,0.5);
		glBegin(GL_QUADS);{
			glVertex3f(-45,-25,0);glColor3f(0.26,0.14,0.1);
			glVertex3f(-45,25,0);glColor3f(0.26,0.14,0.1);
			glVertex3f(45,25,0);glColor3f(0.2,0.2,0.15);
			glVertex3f(45,-25,0);glColor3f(0.2,0.2,0.15);
		}glEnd();
	}glPopMatrix();
	
	glColor3f(0.18,0.15,0.15);
	glPushMatrix();{	//table under top
		glTranslatef(0,0,31.5);
		glScalef(75, 40, 3);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glColor3f(0.25,0.2,0.2);
	//right leg
	glPushMatrix();{	//table leg
		glTranslatef(28,0,29.5);
		glScalef(5, 30, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,0,0.5);
		glScalef(5, 30, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,14.5,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,-14.5,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glColor3f(0.24,0.24,0.24);
	glPushMatrix();{	//table leg
		glTranslatef(28,0,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glColor3f(0.27,0.27,0.27);
	glPushMatrix();{	//table leg
		glTranslatef(28,0,22.5);
		glScalef(5, 20, 1.5);	
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,0,7.5);
		glScalef(5, 20, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,9.5,15);
		glScalef(5, 1.5, 15);	//20
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,-9.5,15);
		glScalef(5, 1.5, 15);	//20
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glColor3f(0.22,0.22,0.22);
	glPushMatrix();{	//table leg
		glTranslatef(28,0,17.5);
		glScalef(5, 10, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,0,12.5);
		glScalef(5, 10, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,4.5,15);
		glScalef(5, 1.5, 5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(28,-4.5,15);
		glScalef(5, 1.5, 5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();


	//left leg
	glColor3f(0.25,0.2,0.2);
	glPushMatrix();{	//table leg
		glTranslatef(-28,0,29.5);
		glScalef(5, 30, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,0,0.5);
		glScalef(5, 30, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,14.5,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,-14.5,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glColor3f(0.24,0.24,0.24);
	glPushMatrix();{	//table leg
		glTranslatef(-28,0,15);
		glScalef(5, 1.5, 30);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glColor3f(0.27,0.27,0.27);
	glPushMatrix();{	//table leg
		glTranslatef(-28,0,22.5);
		glScalef(5, 20, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,0,7.5);
		glScalef(5, 20, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,9.5,15);
		glScalef(5, 1.5, 15);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,-9.5,15);
		glScalef(5, 1.5, 15);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glColor3f(0.22,0.22,0.22);
	glPushMatrix();{	//table leg
		glTranslatef(-28,0,17.5);
		glScalef(5, 10, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,0,12.5);
		glScalef(5, 10, 1.5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,4.5,15);
		glScalef(5, 1.5, 5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();

	glPushMatrix();{	//table leg
		glTranslatef(-28,-4.5,15);
		glScalef(5, 1.5, 5);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
}

void drawChandelier(){

	double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = 80;//80

	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane
	
	glColor3f(1,1,1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glTranslatef(12,0,70);
			//glScalef(3, 1, 10);
			glutWireCone(8, 100, 150, 200);
			glColor3f(0.3,0.3,0.3);
			glutSolidTorus(0.3,8,20,20);
			glTranslatef(0,0,9.7);
			glutSolidTorus(0.3,7.5,20,20);
			glPushMatrix();{
				glTranslatef(7.5,0,0.5);
				glRotatef(-5,0,1,0);
				glScalef(0.2,0.5,20);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix();{
				glTranslatef(-7.5,0,0.5);
				glRotatef(5,0,1,0);
				glScalef(0.2,0.5,20);
				glutSolidCube(1);
			}glPopMatrix();
		}glPopMatrix();

		glColor3f(1,1,1);
		glPushMatrix();{
			glTranslatef(-12,0,70);
			//glScalef(3, 1, 10);
			glutWireCone(8, 100, 150, 200);
			glColor3f(0.3,0.3,0.3);
			glutSolidTorus(0.3,8,20,20);
			glTranslatef(0,0,9.7);
			glutSolidTorus(0.3,7.5,20,20);
			glPushMatrix();{
				glTranslatef(7.5,0,0.5);
				glRotatef(-5,0,1,0);
				glScalef(0.2,0.5,20);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix();{
				glTranslatef(-7.5,0,0.5);
				glRotatef(5,0,1,0);
				glScalef(0.2,0.5,20);
				glutSolidCube(1);
			}glPopMatrix();
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	
	glColor3f(1,1,1);
	glPushMatrix();{	//chandelier circle
		glTranslatef(12,0,79.5);
		glutSolidCircle(7,100);
	}glPopMatrix();

	glPushMatrix();{	//chandelier circle
		glTranslatef(-12,0,79.5);
		glutSolidCircle(7,100);
	}glPopMatrix();
	
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();{	
		glTranslatef(-12,0,79);
		glutSolidCylinder(.5,4,0,10);
	}glPopMatrix();
	
	glPushMatrix();{	
		glTranslatef(12,0,79);
		glutSolidCylinder(.5,4,0,10);
	}glPopMatrix();

	glPushMatrix();{	//chandelier stick
		glTranslatef(0,0,82);
		glScalef(24,1,1);
		glutSolidCube(1);	//use solid
	}glPopMatrix();
	
	glPushMatrix();{	//top stick
		glTranslatef(0,0,82);
		glutSolidCylinder(.5,40,0,20);
	}glPopMatrix();

	glPushMatrix();{	//top stick bottom
		glTranslatef(0,0,81);
		glutSolidCylinder(1,2,0,40);
	}glPopMatrix();
	glPushMatrix();{	//top stick bottom
		glTranslatef(0,0,80);
		glutSolidCylinder(.5,2,0,40);
	}glPopMatrix();

	glPushMatrix();{	//top stick bottom
		glTranslatef(0,0,78);
		glutSolidCylinder(.2,5,0,10);
	}glPopMatrix();
}

void drawGlobe(){
	
	glColor3f(0.5, 0.4, 0.2);
	glPushMatrix();{

		glTranslatef(30,85,55);
		glScalef(.8,.8,.8);


		glPushMatrix();{
			glRotatef(90,0,1,0);
			glRotatef(globeAngle,0,0,1);
			glutWireSphere(10,30,30);
		}glPopMatrix();

		double equ[4];

		equ[0] = 0;	//0.x
		equ[1] = 0;	//0.y
		equ[2] = -1;//-1.z
		equ[3] = 0;//80

		glClipPlane(GL_CLIP_PLANE0,equ);

		glColor3f(0.24, 0.2, 0.2);
		glEnable(GL_CLIP_PLANE0);{
			glPushMatrix();{
				glRotatef(90,1,0,0);
				glutSolidTorus(.4, 11, 10, 20);
			}glPopMatrix();	
		}glDisable(GL_CLIP_PLANE0);


		glPushMatrix();{
			glTranslatef(0,0,-16);
			glutSolidCylinder(.5,5,20,20);
		}glPopMatrix();
		
		glPushMatrix();{
			glTranslatef(0,0,-16.1 );
			glScalef(7,3,.2);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(0,0,-16.45);
			glScalef(8,4,.5);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(0,0,-17.2);
			glScalef(10,6,1);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(9.5,0,-17.2+17);
			//glScalef(10,6,1);
			glRotatef(90,0,1,0);
			glutSolidCylinder(.5,2,0,50);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(-11.5,0,-17.2+17);
			//glScalef(10,6,1);
			glRotatef(90,0,1,0);
			glutSolidCylinder(.5,2,0,50);
		}glPopMatrix();

	}glPopMatrix();
}


void drawGlobeStand(){
	
	glColor3f(.2,.2,.2);
	
	glPushMatrix();{
		glTranslatef(30,96,0);
		glScalef(0.8,1,0.9);

		double equ[4];

		equ[0] = 0;	//0.x
		equ[1] = -1;//-1.y
		equ[2] = 0;//-0.z
		equ[3] = 0;//0

		glClipPlane(GL_CLIP_PLANE0,equ);


		glEnable(GL_CLIP_PLANE0);{
			glColor3f(0.11,0.11,0.11);
			glPushMatrix();{
				glPushMatrix();{
					glTranslatef(0,0,12.5+20+12.5);
					glScalef(30,41,0.5);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix();{
					glTranslatef(15,0,20+25);
					glutSolidCylinder(20.5,0.5,50,50);
				}glPopMatrix();
				glPushMatrix();{
					glTranslatef(-15,0,20+25);
					glutSolidCylinder(20.5,0.5,50,50);
				}glPopMatrix();
			}glPopMatrix();


			glColor3f(.25,.25,.25);
			glPushMatrix();{
				glTranslatef(0,0,12.5+20);
				glScalef(30,40,25);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix();{
				glTranslatef(15,0,20);
				glutSolidCylinder(20,25,50,50);
			}glPopMatrix();
			glPushMatrix();{
				glTranslatef(-15,0,20);
				glutSolidCylinder(20,25,50,50);
			}glPopMatrix();
		}glDisable(GL_CLIP_PLANE0);
		
		glColor3f(0.1,0.1,0.1);
		glPushMatrix();{
			glTranslatef(-18,-10,20);
			for(int i=0;i<14;i++){
				glPushMatrix();{
					glTranslatef(2.8*i,-10,0);
					glutSolidCylinder(.5,24,50,50);	
				}glPopMatrix();
			}
		
		}glPopMatrix();

		float xpos,ypos,angle=0;
		//glColor3f(0.9,0.1,0.1);
		for(int i=0;i<8;i++){
			glPushMatrix();{			
				xpos=20*cos(angle*(3.141592/180));
				ypos=20*sin(angle*(3.141592/180));
				glTranslatef(15+xpos,ypos,20);
				glutSolidCylinder(.5,24,50,50);
			}glPopMatrix();
			angle-=10;
		}
		angle=180;
		glPushMatrix();{
			for(int i=0;i<8;i++){
				glPushMatrix();{			
					xpos=20*cos(angle*(M_PI/180));
					ypos=20*sin(angle*(M_PI/180));
					//glTranslatef(-20,-10,20);
					//glTranslatef(-3,-9,0);
					glTranslatef(-15+xpos,ypos,20);
					glutSolidCylinder(.5,24,50,50);
				}glPopMatrix();
				angle+=10;
			}
		}glPopMatrix();
		

		glPushMatrix();{
			glTranslatef(14.5,-19.5,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-14.5,-19.5,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(14.5,0,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-14.5,0,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(34.5,0,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-34.5,0,10);
			glScalef(1,1,20);
			glutSolidCube(1);
		}glPopMatrix();
	}glPopMatrix();
}


void drawTableThings(){
	
	glColor3f(.2,.5,.9);
	glPushMatrix();{
		glTranslatef(20,0,35);
		drawCandle();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-20,0,35);
		drawCandle();
	}glPopMatrix();
	
	//end candle
	glPushMatrix();{
		glTranslatef(10,0,35);
		drawPlate();
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(-70,0,35);
		drawPlate();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,0,35+7.5);
		glScalef(0.7,0.7,0.7);
		drawBowl();
	}glPopMatrix();
}

void drawBowl(){
	double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;//-1.y
	equ[2] = -1;//-0.z
	equ[3] = 0;//0

	glClipPlane(GL_CLIP_PLANE0,equ);
	glColor3f(.91,.91,.91);
	glEnable(GL_CLIP_PLANE0);{
	glPushMatrix();{
		glutWireSphere(10,80,80);
		glColor3f(.3,.3,.3);
	}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glPushMatrix();{
		glTranslatef(0,0,.1);
		glutCircle(0,0,10,50);
		glutCircle(0,0,9.8,50);
	}glPopMatrix();
	glColor3f(0.88,0.88,0.88);
	glPushMatrix();{
		glTranslatef(0,0,0);
		glScalef(0.95,0.95,1);
		glPushMatrix();{
			glTranslatef(0,0,-10);
			float j=5;
			for(int i=0;i<30;i++){
				glPushMatrix();{
					//glutSolidCylinder(.5,7,0,20);
					glTranslatef(0,0,i/10.0);
					//glutSolidCylinder(j+.5,1,0,20);
					glutCircle(0,0,j+.5,20);
				}glPopMatrix();
				j=j+i/200.0;
			}
		}glPopMatrix();
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(0,0,-10.5);
		glScalef(0.4,0.4,0.4);
		showCasePlate();
	}glPopMatrix();
	glColor3f(0.96,0.93,0.56);
	glPushMatrix();{
		glTranslatef(4,0,-1);
		//glScalef(0.4,0.4,0.4);
		glutWireSphere(4.5,30,30);
	}glPopMatrix();
	glColor3f(0.96,0.84,0.45);
	glPushMatrix();{
		glTranslatef(-4,0,-1);
		//glScalef(0.4,0.4,0.4);
		glutWireSphere(4,30,30);
	}glPopMatrix();
}

void drawCandle(){
	glPushMatrix();{
		//glTranslatef(0,0,35);
		//candle
		glColor3f(.25,.2,.2);
		glPushMatrix();{
			glTranslatef(0,0,0);
			glutSolidCylinder(2.25,4,0,50);
		}glPopMatrix();
		glColor3f(.9,.9,.9);
		glPushMatrix();{
			glTranslatef(0,0,4);
			glutWireCylinder(2,12,10,10);
		}glPopMatrix();
		glColor3f(.25,.2,.2);
		glPushMatrix();{
			glTranslatef(0,0,16);
			glutSolidCylinder(2.25,.5,0,50);
		}glPopMatrix();
		
		glColor3f(1,1,1);
		glPushMatrix();{   //candle
			glTranslatef(0,0,4);
			glutSolidCylinder(1.2,5,0,50);
		}glPopMatrix();
		
		glPushMatrix();{   //candle head
			glTranslatef(0,0,9);
			glutSolidCone(1.2,1,50,50);
		}glPopMatrix();
		
		glPushMatrix();{   //candle-fire
			glTranslatef(0,0,10);
			glutSolidCylinder(.05,.5,0,10);
		}glPopMatrix();
	
	}glPopMatrix();
}

void drawPlate(){
	//plate
	glPushMatrix();{	//plate
		glColor3f(.1,.2,.25);
		glBegin(GL_QUADS);{
			glVertex3f(35,5,0);glColor3f(.1,.2,.15);
			glVertex3f(35,-5,0);glColor3f(.26,.3,.45);
			glVertex3f(25,-5,0);glColor3f(.1,.2,.15);
			glVertex3f(25,5,0);glColor3f(.26,.3,.45);
		}glEnd();

		glColor3f(.15,.22,.2);

		glBegin(GL_QUADS);{
			glVertex3f(35,5,0);glColor3f(.1,.2,.15);
			glVertex3f(35,-5,0);glColor3f(.26,.3,.45);
			glVertex3f(35+2,-5-2,1.5);glColor3f(.26,.3,.45);
			glVertex3f(35+2,5+2,1.5);glColor3f(.1,.2,.15);
		}glEnd();

		glBegin(GL_QUADS);{
			glVertex3f(25,5,0);glColor3f(.1,.2,.15);
			glVertex3f(25,-5,0);glColor3f(.26,.3,.45);
			glVertex3f(25-2,-5-2,1.5);glColor3f(.26,.3,.45);
			glVertex3f(25-2,5+2,1.5);glColor3f(.1,.2,.15);
		}glEnd();

		glBegin(GL_QUADS);{
			glVertex3f(25,5,0);glColor3f(.1,.2,.15);
			glVertex3f(35,5,0);glColor3f(.26,.3,.45);
			glVertex3f(35+2,5+2,1.5);glColor3f(.26,.3,.45);
			glVertex3f(25-2,5+2,1.5);glColor3f(.1,.2,.15);
		}glEnd();

		glBegin(GL_QUADS);{
			glVertex3f(25,-5,0);glColor3f(.1,.2,.15);
			glVertex3f(35,-5,0);glColor3f(.26,.3,.45);
			glVertex3f(35+2,-5-2,1.5);glColor3f(.26,.3,.45);
			glVertex3f(25-2,-5-2,1.5);glColor3f(.1,.2,.15);
		}glEnd();

	}glPopMatrix();
	//end plate

	glPushMatrix();{ //glass on plate
		glColor3f(.9,.9,.9);
		glTranslatef(30,0,0);
		double equ[4];

		equ[0] = 0;	//0.x
		equ[1] = 0;//-1.y
		equ[2] = 1;//-0.z
		equ[3] = 0;//0

		glClipPlane(GL_CLIP_PLANE0,equ);
		glColor3f(.25,.38,.45);
		glEnable(GL_CLIP_PLANE0);{
			glPushMatrix();{
				glutSolidSphere(2,20,20);
			}glPopMatrix();
		}glDisable(GL_CLIP_PLANE0);
				
		glColor3f(.9,.9,.9);
		glPushMatrix();{
			glRotatef(180,1,0,0);
			glTranslatef(0,0,-6);
			glutSolidCone(3.5,5,20,20);
		}glPopMatrix();
		glColor3f(.5,.6,.5);
		glPushMatrix();{
			glRotatef(180,1,0,0);
			glTranslatef(0,0,-6);
			glutCircle(0,0,3.5,20);
			glutCircle(0,0,3.4,20);
			glTranslatef(0,0,.1);
			glutCircle(0,0,3.5,20);
		}glPopMatrix();
	}glPopMatrix();
}

void drawWall(){
	glColor3f(.6,.6,.6);
	glPushMatrix();{
		glTranslatef(-60,100,50);
		glScalef(80,6,100);
		glutSolidCube(1);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(-60,100-3.2,0);
		glBegin(GL_QUADS);{
			glVertex3f(-40,0,0);glColor3f(.9,.9,.9);
			glVertex3f(40,0,0);glColor3f(.7,.7,.7);
			glVertex3f(40,0,100);glColor3f(.7,.7,.7);
			glVertex3f(-40,0,100);glColor3f(.9,.9,.9);
		}glEnd();
	}glPopMatrix();
	
	
	glColor3f(.8,.8,.75);
	glPushMatrix();{
		glTranslatef(35,100,95);
		glScalef(110,6,10);
		glutSolidCube(1);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(35,100-3.2,90);
		glBegin(GL_QUADS);{
			glVertex3f(-55,0,0);glColor3f(.9,.9,.9);
			glVertex3f(55,0,0);glColor3f(.9,.9,.9);
			glVertex3f(55,0,10);glColor3f(.7,.7,.7);
			glVertex3f(-55,0,10);glColor3f(.9,.9,.9);
		}glEnd();
	}glPopMatrix();
	
	
	glColor3f(.8,.8,.8);
	glPushMatrix();{
		glTranslatef(95,100,50);
		glScalef(10,6,100);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(95,100-3.2,0);
		glBegin(GL_QUADS);{
			glVertex3f(-5,0,0);glColor3f(.7,.7,.7);
			glVertex3f(5,0,0);glColor3f(.9,.9,.9);
			glVertex3f(5,0,100);glColor3f(.9,.9,.9);
			glVertex3f(-5,0,100);glColor3f(.5,.5,.5);
		}glEnd();
	}glPopMatrix();

	glColor3f(.55,.55,.55);
	glPushMatrix();{
		glTranslatef(-100+3,37.5,15);
		glScalef(6,125,30);
		glutSolidCube(1);
	}glPopMatrix();

	glColor3f(.55,.55,.55);
	glPushMatrix();{
		glTranslatef(-100+3,-62.5,50);
		glScalef(6,75,100);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-100+3+3.2,37.5,0);
		glBegin(GL_QUADS);{
			glVertex3f(0,-62.5,0);glColor3f(.6,.6,.6);
			glVertex3f(0,62.5,0);glColor3f(.7,.7,.7);
			glVertex3f(0,62.5,30);glColor3f(.9,.9,.9);
			glVertex3f(0,-62.5,30);glColor3f(.1,.1,.1);
		}glEnd();
	}glPopMatrix();
	glColor3f(.95,.95,.95);
	glPushMatrix();{
		glTranslatef(-100+3+3.2,-62.5,0);
		//glRotatef(180,1,0,0);
		//glTranslatef(0,0,-100);
		glBegin(GL_QUADS);{
			glVertex3f(0,-37.5,0);glColor3f(.7,.7,.7);
			glVertex3f(0,37.5,0);glColor3f(.5,.5,.5);
			glVertex3f(0,37.5,100);glColor3f(.6,.6,.6);
			glVertex3f(0,-37.5,100);glColor3f(.5,.5,.5);
		}glEnd();
	}glPopMatrix();

	glColor3f(.55,.55,.55);
	glPushMatrix();{
		glTranslatef(-100+3,-1,95);
		glScalef(6,198,10);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-100+3+3.2,37.5,90);
		glBegin(GL_QUADS);{
			glVertex3f(0,-62.5,0);glColor3f(.6,.6,.6);
			glVertex3f(0,62.5,0);glColor3f(.7,.7,.7);
			glVertex3f(0,62.5,10);glColor3f(.9,.9,.9);
			glVertex3f(0,-62.5,10);glColor3f(.1,.1,.1);
		}glEnd();
	}glPopMatrix();
	
}


void drawMirror(){
	glColor3f(.9,.9,.9);

	glPushMatrix();{
		glTranslatef(-40,96,50);
		glRotatef(90,1,0,0);
		glPushMatrix();{
			glutSolidCylinder(5,.4,20,50);
			glColor3f(.35,.35,.35);
			glScalef(1,1,2);
			glutSolidTorus(.5,5.5,20,20);
		}glPopMatrix();

		glColor3f(.4,.3,.5);
		int segments=30;
		float theta=360/segments;
		for(int i=0;i<segments;i++){
			glPushMatrix();{
				glRotatef(i*theta,0,0,1);
				glRotatef(90,1,0,0);
				glutSolidCylinder(.25,mirrorCylinder[i],20,50);
			}glPopMatrix();
		}
	}glPopMatrix();
}

void drawScreen(){
	glPushMatrix();{
		glTranslatef(-17.5,102,-1);
		for(int i=0;i<110;i=i+5){
			glPushMatrix();{
				glColor3f(0.98,1.00,0.68);
				if(i%2==0){
					glColor3f(0.99,0.98,0.77);
				}
				glTranslatef(i,0,0);
				glRotatef(30,0,0,1);
				glBegin(GL_QUADS);{
					glVertex3f(3,0,0);glColor3f(0.5,0.5,0.5);
					glVertex3f(3,0,90);glColor3f(0.98,1.00,0.6);
					glVertex3f(-3,0,90);glColor3f(0.98,0.9,0.5);
					glVertex3f(-3,0,0);glColor3f(0.5,0.5,0.5);
				}glEnd();
			}glPopMatrix();
		}
	}glPopMatrix();
	
	glColor3f(0.98,1.00,0.68);
	glPushMatrix();{
		glTranslatef(-100+1,56.5,30);
		screenSegment();
	}glPopMatrix();
	
	glColor3f(0.99,0.99,0.72);
	glPushMatrix();{
		glTranslatef(-100+1,16,30);
		screenSegment();
	}glPopMatrix();
	
	glColor3f(0.98,1.00,0.68);
	glPushMatrix();{	
		glTranslatef(-100+1,-24.5,30);
		screenSegment();
	}glPopMatrix();
}

void screenSegment(){
	glPushMatrix();{
		for(float i=0;i<=40;i=i+1){
			glBegin(GL_LINES);{
				glVertex3f(0,i,0);
				glVertex3f(0,i,60);
			}glEnd();
		}

		for(i=0;i<=60;i=i+.5){
			glBegin(GL_LINES);{
				glVertex3f(0,0,i);
				glVertex3f(0,40,i);
			}glEnd();
		}
		
	}glPopMatrix();
}

void drawTowel(){
	glColor3f(.3,.3,.3);
	glPushMatrix();{
		
		glTranslatef(-60,88.8,80);

		glPushMatrix();{
			glScalef(1,15,1);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(0,7.5,2);
			glRotatef(90,1,0,0);
			glutSolidCylinder(.3,15,20,20);
		}glPopMatrix();
		
		double equ[4];

		equ[0] = -1;	//0.x
		equ[1] = 0;//-1.y
		equ[2] = 0;//-0.z
		equ[3] = 1.5;//0

		double equ1[4];

		equ1[0] = 0;	//0.x
		equ1[1] = 0;//-1.y
		equ1[2] = 1;//-0.z
		equ1[3] = 2.2;//0
		
		double equ2[4];

		equ2[0] = 0;	//0.x
		equ2[1] = 0;//-1.y
		equ2[2] = -1;//-0.z
		equ2[3] = 2.2;//0

		glClipPlane(GL_CLIP_PLANE0,equ);
		glClipPlane(GL_CLIP_PLANE1,equ1);
		glClipPlane(GL_CLIP_PLANE2,equ2);
		
		glEnable(GL_CLIP_PLANE2);{
		glEnable(GL_CLIP_PLANE1);{
		glEnable(GL_CLIP_PLANE0);{
			glPushMatrix();{
				glTranslatef(0,7.5,0);
				glRotatef(90,1,0,0);
				glutSolidCircle(2.5,20);
			}glPopMatrix();
			glPushMatrix();{
				glTranslatef(0,-7.5,0);
				glRotatef(90,1,0,0);
				glutSolidCircle(2.5,20);
			}glPopMatrix();	
		}glDisable(GL_CLIP_PLANE0);
		}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE2);
		

		glColor3f(0.85,0.82,0.74);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glVertex3f(-.5,7.4,0);glColor3f(0.4,0.4,0.4);
				glVertex3f(-.5,7.4,-60);glColor3f(0.4,0.4,0.4);
				glVertex3f(-.5,-7.4,-60);glColor3f(0.85,0.82,0.74);
				glVertex3f(-.5,-7.4,0);glColor3f(0.85,0.82,0.74);
			}glEnd();
		}glPopMatrix();
		glColor3f(0.8,0.8,0.7);
		glPushMatrix();{
			glBegin(GL_QUADS);{
				glVertex3f(.5,7.4,0);glColor3f(0.6,0.6,0.6);
				glVertex3f(.5,7.4,-10);glColor3f(0.6,0.6,0.6);
				glVertex3f(.5,-7.4,-10);glColor3f(0.85,0.82,0.74);
				glVertex3f(.5,-7.4,0);glColor3f(0.85,0.82,0.74);
			}glEnd();
		}glPopMatrix();



	}glPopMatrix();


}

void drawShowCase(){
	glColor3f(.3,.3,.3);
	glPushMatrix();{	//bottom-leg
		glTranslatef(-.5,0,0);
		glScalef(19,50,1.5);
		glutSolidCube(1);
	}glPopMatrix();
	glColor3f(.2,.2,.2);
	glPushMatrix();{	//bottom
		glTranslatef(0,0,1.25);
		glScalef(20,50,1);
		glutSolidCube(1);
	}glPopMatrix();
	
	glColor3f(.2,.2,.2);
	glPushMatrix();{	//middle
		glTranslatef(0,0,24+1+.75+.5);
		glScalef(20,50,1);
		glutSolidCube(1);
	}glPopMatrix();
	glColor3f(.2,.2,.2);
	/*glPushMatrix();{	//top
		glTranslatef(0,0,27.75+40+.75);
		glScalef(20,50,1.5);
		glutSolidCube(1);
	}glPopMatrix();
	*/
	glColor3f(.3,.3,.3);
	glPushMatrix();{	//top-most
		glTranslatef(0,0,27.75+40+1.5+.5);
		glScalef(20,50,1);
		glutSolidCube(1);
	}glPopMatrix();
	//bar
	glColor3f(.35,.35,.35);
	//glColor3f(.1,.1,.1);
	glPushMatrix();{
		glTranslatef(0,15.5,0);
		showCaseBar();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,-15.5,0);
		showCaseBar();
	}glPopMatrix();

	//glColor3f(.28,.28,.28);
	glPushMatrix();{
		glTranslatef(0,-24.5,0);
		showCaseBar();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,24.5,0);
		showCaseBar();
	}glPopMatrix();

	//back-board
	glColor3f(.45,.45,.45);
	glPushMatrix();{
		glTranslatef(-9.5,0,27.75+20.75);
		glScalef(1,30,41.5);
		glutSolidCube(1);
	}glPopMatrix();
	
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(-8.8,0,27.75);
		glBegin(GL_QUADS);{
			glVertex3f(0,-15,0);glColor3f(.6,.6,.6);
			glVertex3f(0,15,0);glColor3f(.7,.7,.7);
			glVertex3f(0,15,41.5);glColor3f(.5,.5,.5);
			glVertex3f(0,-15,41.5);glColor3f(.1,.1,.1);
		}glEnd();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-9.5,0,13.75);
		glScalef(1,50,24);
		glutSolidCube(1);
	}glPopMatrix();


	//door
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(9.8,16.5,27.75+20);
		showCaseDoor();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(9.8,-16.5-7,27.75+20);
		showCaseDoor();
	}glPopMatrix();
	
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(-10,16.5,27.75+20);
		showCaseDoor();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-9.8,-16.5-7,27.75+20);
		showCaseDoor();
	}glPopMatrix();
	//door up bos
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(0,20,27.75+40.75);
		glScalef(20,8,1.5);
		glutSolidCube(1);
	}glPopMatrix();
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(0,-20,27.75+40.75);
		glScalef(20,8,1.5);
		glutSolidCube(1);
	}glPopMatrix();

	//door down
	glColor3f(.35,.35,.35);
	glPushMatrix();{
		glTranslatef(0,20,27.25);
		glScalef(19,10,1);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,-20,27.25);
		glScalef(19,10,1);
		glutSolidCube(1);
	}glPopMatrix();
	//rack
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(0,0,27.75+14);
		showCaseRack();	
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,0,27.75+28);
		showCaseRack();	
	}glPopMatrix();
	//top-2
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(0,0,27.75+40.75);
		glScalef(1,1,1.5);
		showCaseRack();	
	}glPopMatrix();
	glColor3f(.2,.2,.2);
	//middle-rack
	//glColor3f(.35,.35,.35);
	glPushMatrix();{
		glTranslatef(0,0,27.25);
		showCaseRack();	
	}glPopMatrix();
	glColor3f(.35,.35,.35);
	//side rack
	//glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(0,20,27.75+28);
		glScalef(20,9,.5);
		glutSolidCube(1);	
	}glPopMatrix();
		glPushMatrix();{
		glTranslatef(0,20,27.75+14);
		glScalef(20,9,.5);
		glutSolidCube(1);	
	}glPopMatrix();
		glPushMatrix();{
		glTranslatef(0,-20,27.75+28);
		glScalef(20,9,.5);
		glutSolidCube(1);	
	}glPopMatrix();
		glPushMatrix();{
		glTranslatef(0,-20,27.75+14);
		glScalef(20,9,.5);
		glutSolidCube(1);	
	}glPopMatrix();

	//bottom side 
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(.5,24.5,13.75);
		glScalef(19,1,24);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(.5,-24.5,13.75);
		glScalef(19,1,24);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(.5,15.5,13.75);
		glScalef(19,1,24);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(.5,-15.5,13.75);
		glScalef(19,1,24);
		glutSolidCube(1);
	}glPopMatrix();

	//bottom-door
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(9.5,20,13.75);
		glScalef(1,8,24);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(9.5,-20,13.75);
		glScalef(1,8,24);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		showCaseDrawer();
	}glPopMatrix();
	
	glPushMatrix();{
		drawerNob();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,-18,12);
		glScalef(0.7,0.7,0.7);
		doorNob();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,18,12);
		glScalef(0.7,0.7,0.7);
		doorNob();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,-17,45);
		glScalef(0.7,0.7,0.7);
		doorNob();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,17,45);
		glScalef(0.7,0.7,0.7);
		doorNob();
	}glPopMatrix();
}

void showCaseDrawer(){
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(0,0,5.75);
		glScalef(1,1,7.6);
		showCaseRack();
	}glPopMatrix();
	glColor3f(.2,.2,.2);
	glPushMatrix();{
		glTranslatef(0,0,13.75);
		glScalef(1,1,7.6);
		showCaseRack();
	}glPopMatrix();
	glColor3f(.25,.25,.25);
	glPushMatrix();{
		glTranslatef(0,0,21.75);
		glScalef(1,1,7.6);
		showCaseRack();
	}glPopMatrix();
}

void drawerNob(){
	glColor3f(0.8,0.8,0.8);
	glPushMatrix();{
		glTranslatef(10.5,-11,21.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,11,21.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,-11,13.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,11,13.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,-11,5.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(10.5,11,5.75);
		glRotatef(90,0,1,0);
		glutSolidCylinder(1,1,0,20);
	}glPopMatrix();
}

void doorNob(){
	glPushMatrix();{
		glTranslatef(-2,0,4);
		glRotatef(90,0,1,0);
		glutSolidCylinder(.5,3,0,20);
	}glPopMatrix();
	glPushMatrix();{
		glScalef(2,1,1);
		glutSolidCone(.5,5,20,20);
	}glPopMatrix();

}
void showCaseRack(){

	glTranslatef(1,0,0);
	double equ[4];

	equ[0] = -1;	//0.x
	equ[1] = -1;	//0.y
	equ[2] = 0;//-1.z
	equ[3] = 24;//80

	double equ1[4];

	equ1[0] = -1;	//0.x
	equ1[1] = 1;	//0.y
	equ1[2] = 0;//-1.z
	equ1[3] = 24;//80

	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glScalef(20,30,1);
			glutSolidCube(1);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	//corner
	glPushMatrix();{
		glTranslatef(9,14,-.5);
		glutSolidCylinder(1,1,0,10);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(9,-14,-.5);
		glutSolidCylinder(1,1,0,10);
	}glPopMatrix();
}

void showCaseDoor(){
	glPushMatrix();{
		glScalef(.5,1,40);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,7,0);
		glScalef(.5,1,40);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,3.5,-19.5);
		glScalef(.5,8,1);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,3.5,19.5);
		glScalef(.5,8,1);
		glutSolidCube(1);
	}glPopMatrix();



}

void showCaseBar(){
	glPushMatrix();{	//bar
		glTranslatef(9,0,27.75+20.75);
		glScalef(2,1,41.5);
		glutSolidCube(1);
	}glPopMatrix();
	//glColor3f(.3,.3,.3);
	glPushMatrix();{	//bar
		glTranslatef(-9,0,27.75+20.75);
		glScalef(2,1,41.5);
		glutSolidCube(1);
	}glPopMatrix();
	//glColor3f(.3,.3,.3);
	glPushMatrix();{	//bar
		glTranslatef(0,0,27.75+39.5);
		glScalef(20,1,4);
		glutSolidCube(1);
	}glPopMatrix();
	//glColor3f(.3,.3,.3);
	glPushMatrix();{	//bar
		glTranslatef(0,0,27.75+1);
		glScalef(20,1,2);
		glutSolidCube(1);
	}glPopMatrix();
}

void drawShowCaseThings(){
	//box
	glPushMatrix();{
		glTranslatef(-89,-20,28);
		glScalef(.4,2,1.2);

		for(int i=0;i<6;i++){
			glPushMatrix();{
				if(i%2==0)
					glColor3f(0.5,0.5,0.5);
				else
					glColor3f(0.7,0.5,0.2);
				glTranslatef(0,0,i/(2*1.0));
				glScalef(20,10,.5);
				glutSolidCube(1);
			}glPopMatrix();
		}

		glPushMatrix();{
			glColor3f(0.3,0.8,0.8);
			glTranslatef(0,0,3);
			glScalef(20,10,1);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glColor3f(0.35,0.2,0.2);
			glTranslatef(0,0,3.75);
			glScalef(20,10,.5);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix();{
			glColor3f(0.7,0.7,0.7);
			glTranslatef(0,0,4.5);
			glScalef(20,10,1);
			glutSolidCube(1);
		}glPopMatrix();
		for(i=0;i<4;i++){
			glPushMatrix();{
				if(i%2==0)
					glColor3f(0.5,0.5,0.5);
				else
					glColor3f(0.7,0.5,0.2);
				glTranslatef(0,0,5+i/(2*1.0));
				glScalef(20,10,.5);
				glutSolidCube(1);
			}glPopMatrix();
		}
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-93,-20,47.5);
		glRotatef(90,0,1,0);
		glRotatef(-5,0,1,0);
		glScalef(.2,.2,.2);
		showCasePlate();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-93,-20,47.5+14);
		glRotatef(90,0,1,0);
		glRotatef(-5,0,1,0);
		glScalef(.2,.2,.2);
		showCasePlate();
	}glPopMatrix();
	
	//first rack
	glColor3f(0.15,0.12,0.3);
	glPushMatrix();{
		glTranslatef(-87,-15,47.5+9);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-87,-25,47.5+9);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-90,-5,47.5+9);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-90,-35,47.5+9);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();

	//second rack
	glPushMatrix();{
		glTranslatef(-87,-12,42.5);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-87,-25,42.5);
		glScalef(.4,.4,.4);
		showCaseGlass();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-90,-5,42.5);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-90,-35,42.5);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();

	//3rd rack
	glPushMatrix();{
		glTranslatef(-90,-5,28);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-90,-35,28);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();

	//side 3rd rack
	glColor3f(0.87,0.47,0.01);
	glPushMatrix();{
		glTranslatef(-90,4,28);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-90,-44,28);
		glScalef(.4,.4,.7);
		showCaseGlass();
	}glPopMatrix();

	//slim glass 1st rack
	glColor3f(0.5,0.1,0.2);
	glPushMatrix();{
		glTranslatef(-85,-20,47.5+9);
		glScalef(.6,.6,.6);
		glPushMatrix();{
			//glTranslatef(-90,-44,28);
			//glScalef(.4,.4,.7);
			glTranslatef(0,0,10);
			glRotatef(180,1,0,0);
			glutSolidCone(4,5,20,20);
		}glPopMatrix();
		glPushMatrix();{
			//glTranslatef(-90,-44,28);
			//glScalef(.4,.4,.7);
			//glRotatef(180,1,0,0);
			glutSolidCylinder(.5,7,0,20);
			glutSolidCylinder(1,1,0,20);
		}glPopMatrix();
	}glPopMatrix();
	
	//2nd rack long
	glColor3f(0.16,0.14,0.65);
	glPushMatrix();{
		glTranslatef(-85,-20,42);
		glScalef(0.5,0.5,0.5);
		glScalef(0.7,0.7,1.6);
		showCaseGlass();
		glPushMatrix();{
			glTranslatef(0,0,10);
			float j=5;
			for(int i=0;i<30;i++){
				glPushMatrix();{
					//glutSolidCylinder(.5,7,0,20);
					glTranslatef(0,0,i/10.0);
					//glutSolidCylinder(j+.5,1,0,20);
					glutCircle(0,0,j+.5,20);
				}glPopMatrix();
				j=j+i/200.0;
			}
		}glPopMatrix();
	}glPopMatrix();
}	

void showCasePlate(){
	double equ[4];
	equ[0]=0;
	equ[1]=0;
	equ[2]=1;
	equ[3]=0;

	double equ1[4];
	equ1[0]=0;
	equ1[1]=0;
	equ1[2]=-1;
	equ1[3]=5;


	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glColor3f(0.3,0.2,0.2);
			glTranslatef(0,0,47);
			glutSolidSphere(50,50,50);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glColor3f(0.6,0.4,0.4);
	glPushMatrix();{
		glutSolidCircle(17.06,50);
	}glPopMatrix();
}

void showCaseGlass(){
	double equ[4];
	equ[0]=0;
	equ[1]=0;
	equ[2]=-1;
	equ[3]=10;
	glClipPlane(GL_CLIP_PLANE0,equ);
	//glColor3f(0.2,0.1,0.9);

	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			//glTranslatef(0,0,60);
			glutSolidCylinder(4,10,0,50);
		}glPopMatrix();
		glPushMatrix();{
			//glColor3f(0.9,0.3,0.3);
			glTranslatef(0,0,15);  //67
			glScalef(1,1,10);
			glutSolidTorus(1.5,4,50,50);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
}

void drawAllSideChairs(){
	glPushMatrix();{
		glTranslatef(-14,22,15.5);
		glRotatef(90,0,0,1);
		//glScalef(.9,.9,.9);
		drawSideChair();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(14,22,15.5);
		glRotatef(90,0,0,1);
		//glScalef(.9,.9,.9);
		drawSideChair();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(14,-27,15.5);
		glRotatef(-90,0,0,1);
		//glScalef(.9,.9,.9);
		drawSideChair();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-14,-27,15.5);
		glRotatef(-90,0,0,1);
		//glScalef(.9,.9,.9);
		drawSideChair();
	}glPopMatrix();
}

void drawSideChair(){

	glColor3f(.4,.4,.4);
	
	double equ[4];

	equ[0] = -1;	//0.x
	equ[1] = -1;	//0.y
	equ[2] = 0;//-1.z
	equ[3] = 12;//80

	double equ1[4];

	equ1[0] = -1;	//0.x
	equ1[1] = 1;	//0.y
	equ1[2] = 0;//-1.z
	equ1[3] = 12;//80
	
	glColor3f(.18,.18,.18);

	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glScalef(20,20,2);
			glutSolidCube(1);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);

	double equ2[4];

	equ2[0] = -1;	//0.x
	equ2[1] = 0;	//0.y
	equ2[2] = 0;//-1.z
	equ2[3] = -10;//80

	glClipPlane(GL_CLIP_PLANE2,equ2);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE2);{
		glPushMatrix();{
			glTranslatef(39,0,-1);
			glutSolidCylinder(50,2,0,100);
		}glPopMatrix();

	}glDisable(GL_CLIP_PLANE2);

	glPushMatrix();{
		glTranslatef(1,1.,-1);
		glutSolidCylinder(9,2,0,100);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(1,-1.,-1);
		glutSolidCylinder(9,2,0,100);
	}glPopMatrix();


	//chair back
	double equ4[4];

	equ4[0] = 1;	//0.x
	equ4[1] = 0;	//0.y
	equ4[2] = 0;//-1.z
	equ4[3] = -7;//80
	
	glColor3f(.18,.18,.18);
	glClipPlane(GL_CLIP_PLANE4,equ4);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE4);{
		glPushMatrix();{
			glTranslatef(-2,0,20);
			glScalef(1,1,5);
			glutSolidTorus(1,15,20,20);
		}glPopMatrix();	
	}
	glDisable(GL_CLIP_PLANE4);
	
	//back additional parts
	sideChairAdditionalPart();
	
	//legs
	glPushMatrix();{
		glTranslatef(-11,11,-15);
		glRotatef(10,1,1,0);
		sideChairLeg();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-11,-11,-15);
		glRotatef(10,-1,1,0);
		sideChairLeg();
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(11,7,16);
		glPushMatrix();{
			//glTranslatef(50,50,50);
			sideChairBackLeg();
		}glPopMatrix();
		glPushMatrix();{
			//glTranslatef(48,50,22);
			glTranslatef(-2,0,-28);
			glRotatef(180,1,0,0);
			glRotatef(180,0,0,1);
			glRotatef(-10,0,1,0);
			sideChairBackLeg();
		}glPopMatrix();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(11,-7,16);
		glPushMatrix();{
			//glTranslatef(50,50,50);
			sideChairBackLeg();
		}glPopMatrix();
		glPushMatrix();{
			//glTranslatef(48,50,22);
			glTranslatef(-2,0,-28);
			glRotatef(180,1,0,0);
			glRotatef(180,0,0,1);
			glRotatef(-10,0,1,0);
			sideChairBackLeg();
		}glPopMatrix();
	}glPopMatrix();
	glPushMatrix();{
		sideChairSeat();
	}glPopMatrix();
}

void sideChairAdditionalPart(){
	double equ5[4];

	equ5[0] = 1;	//0.x
	equ5[1] = 0;	//0.y
	equ5[2] = 0;//-1.z
	equ5[3] = -7;//80

	double equ3[4];

	equ3[0] = 0;	//0.x
	equ3[1] = 1;	//0.y
	equ3[2] = 0;//-1.z
	equ3[3] = -6.8;//80

	double equ2[4];

	equ2[0] = 0;	//0.x
	equ2[1] = -1;	//0.y
	equ2[2] = 0;//-1.z
	equ2[3] = -6.8;//80

	glClipPlane(GL_CLIP_PLANE5,equ5);
	glClipPlane(GL_CLIP_PLANE3,equ3);
	glClipPlane(GL_CLIP_PLANE2,equ2);

	glColor3f(.18,.18,.18);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE5);{
		glEnable(GL_CLIP_PLANE3);{	
			glPushMatrix();{
				glTranslatef(-2,0,17);
				glScalef(1,1,7);
				glutSolidTorus(1,15,20,20);
			}glPopMatrix();	
		}glDisable(GL_CLIP_PLANE3);
		glEnable(GL_CLIP_PLANE2);{	
			glPushMatrix();{
				glTranslatef(-2,0,17);
				glScalef(1,1,7);
				glutSolidTorus(1,15,20,20);
			}glPopMatrix();	
		}glDisable(GL_CLIP_PLANE2);
	}glDisable(GL_CLIP_PLANE5);
}

void sideChairSeat(){
	double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -1;//80

	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE0);{
		glColor3f(.9,.9,.9);
		glPushMatrix();{
			glTranslatef(3,3,-7);
			glutSolidSphere(10,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(3,-3,-7);
			glutSolidSphere(10,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(3.5,0,-9);
			glutWireSphere(12,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(0,0,-4);
			glScalef(.95,.95,.55);
			glutSolidSphere(14,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-3.7,-3,-1.5);
			glScalef(1,1,.5);
			glutSolidSphere(8,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-3.7,3,-1.5);
			glScalef(1,1,.5);
			glutSolidSphere(8,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-4.3,3,-1.5);
			glScalef(1,1,.5);
			glutSolidSphere(8,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-4.3,-3,-1.5);
			glScalef(1,1,.5);
			glutSolidSphere(8,20,20);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-4,0,-2);
			glScalef(3,1,.5);
			glRotatef(90,0,1,0);
			glutSolidTorus(2,10,20,20);
		}glPopMatrix();
	}
	glDisable(GL_CLIP_PLANE0);

	
}

void sideChairBackLeg(){
	glPushMatrix();{
		glScalef(1,1,7);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-.2,0,-5.5);
		glRotatef(5,0,1,0);
		glScalef(1,1,4);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-.3,0,-7);
		glRotatef(180,-1,1,0);
		glRotatef(15,-1,0,0);
		glScalef(1,1,.5);
		sideChairLeg();
	}glPopMatrix();
	
}

void sideChairLeg(){
	glPushMatrix();{
		glTranslatef(-.5,-.5,0);
		glBegin(GL_QUADS);{
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
			glVertex3f(1,1,0);
			glVertex3f(1,0,0);
		}glEnd();
		glBegin(GL_QUADS);{
			glVertex3f(-.5,-.5,15);
			glVertex3f(-.5,1.5,15);
			glVertex3f(1.5,1.5,15);
			glVertex3f(1.5,-.5,15);
		}glEnd();
		glBegin(GL_QUADS);{
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);
			glVertex3f(1.5,-.5,15);
			glVertex3f(-.5,-.5,15);
		}glEnd();
		glBegin(GL_QUADS);{
			glVertex3f(1,0,0);
			glVertex3f(1,1,0);
			glVertex3f(1.5,1.5,15);
			glVertex3f(1.5,-.5,15);
		}glEnd();
		glBegin(GL_QUADS);{
			glVertex3f(0,1,0);
			glVertex3f(1,1,0);
			glVertex3f(1.5,1.5,15);
			glVertex3f(-.5,1.5,10);
		}glEnd();
		glBegin(GL_QUADS);{
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
			glVertex3f(-.5,1.5,15);
			glVertex3f(-.5,-.5,15);
		}glEnd();
	}glPopMatrix();
}

void drawAllHostChair(){
	
	glPushMatrix();{
		glTranslatef(80,5,0);
		glRotatef(110,0,0,1);
		glScalef(0.9,0.9,0.8);
		drawHostChair();
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-75,0,0);
		glRotatef(-90,0,0,1);
		glScalef(0.9,0.9,0.8);
		drawHostChair();
	}glPopMatrix();
	
	//drawHostChair();
}

void drawHostChair(){
	glPushMatrix();{
		glTranslatef(0,0,27);
		//back-side 
		glColor3f(0.95,0.95,0.95);
		glPushMatrix();{
			glTranslatef(0,14.5,7);
			glRotatef(7,1,0,0);
			glScalef(30,1,40);
			glutSolidCube(1);
		}glPopMatrix();
		glColor3f(0.95,0.95,0.95);
		glPushMatrix();{
			glScalef(1.5,1,1);
			glRotatef(10,1,0,0);
			hostChairBack();
		}glPopMatrix();
		//handles
		glColor3f(0.94,0.94,0.94);
		glPushMatrix();{
			glTranslatef(55,25,-20);
			glRotatef(90,0,0,1);
			glRotatef(-2,1,0,0);
			hostChairHandle();
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-55,35,-20);
			glRotatef(90,0,0,-1);
			glRotatef(-2,1,0,0);
			hostChairHandle();
		}glPopMatrix();
		
		glColor3f(0.8,0.8,0.8);
		glPushMatrix();{
			hostChairSeat();
		}glPopMatrix();

		//front legs
		glColor3f(0.25,0.25,0.2);
		glPushMatrix();{
			glTranslatef(16,43.5,-27.5);
			sideChairLeg();
		}glPopMatrix();
		
		glPushMatrix();{
			glTranslatef(-16,43.5,-27.5);
			sideChairLeg();
		}glPopMatrix();
		
		glColor3f(0.25,0.25,0.2);
		glPushMatrix();{
			glTranslatef(-13,16,-24);
			glScalef(1.5,1.5,1);
			glRotatef(-90,0,0,1);
			glRotatef(170,0,1,0);
			hostChairBackLeg();
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(13,16,-24);  //change for backside
			glScalef(1.5,1.5,1);
			glRotatef(-90,0,0,1);
			glRotatef(170,0,1,0);
			hostChairBackLeg();
		}glPopMatrix();

		//chair-handle curve		
		glColor3f(0.94,0.94,0.94);
		glPushMatrix();{
			glTranslatef(15,29,2.5);
			glRotatef(-90,0,0,1);
			glRotatef(55,0,1,0);
			//glScalef(2,1,1);
			glRotatef(8,1,0,0);
			glutSolidCylinder(2,15,50,50);
		}glPopMatrix();

		//glColor3f(0.93,0.93,0.93);
		glPushMatrix();{
			glTranslatef(-15,29,2.5);
			glRotatef(90,0,0,1);
			glRotatef(-55,0,1,0);
			//glScalef(2,1,1);
			glRotatef(8,1,0,0);
			glutSolidCylinder(2,15,50,50);
		}glPopMatrix();
	}glPopMatrix();
}

void hostChairBackLeg(){
	glPushMatrix();{
		glScalef(1,1,7);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-.2,0,-5.5);
		glRotatef(5,0,1,0);
		glScalef(1,1,4);
		glutSolidCube(1);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-.3,0,-7);
		glRotatef(180,-1,1,0);
		glRotatef(7,-1,0,0);
		glScalef(1,1,.5);
		sideChairLeg();
	}glPopMatrix();
	
}

void hostChairSeat(){
	glPushMatrix();{
		glTranslatef(0,31,-10);
		glScalef(30,26,4);
		glutSolidCube(1);
	}glPopMatrix();
	glColor3f(0.85,0.85,0.85);
	glPushMatrix();{
		glTranslatef(0,30,-7);
		glScalef(30,23,4);
		glutSolidCube(1);
	}glPopMatrix();
	glColor3f(0.85,0.85,0.85);
	glPushMatrix();{
		glTranslatef(-15,41,-7.9);
		glRotatef(90,0,1,0);
		glutSolidCylinder(3,30,50,50);
	}glPopMatrix();
}

void hostChairHandle(){
	glTranslatef(5,0,0);
	double equ[4];
	double equ1[4];
	double equ2[4];
	double equ3[4];
	double equ4[4];
	double equ5[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -10;//80

	equ1[0] = -1;	//0.x
	equ1[1] = 0;	//0.y
	equ1[2] = 0;//-1.z
	equ1[3] = 14.5;//80
	
	equ2[0] = 1;	//0.x
	equ2[1] = 0;	//0.y
	equ2[2] = 0;//-1.z
	equ2[3] = 14.5;//80

	equ3[0] = 0;	//0.x
	equ3[1] = 1;	//0.y
	equ3[2] = 0;//-1.z
	equ3[3] = 0;//80

	equ4[0] = -1;	//0.x
	equ4[1] = 0;	//0.y
	equ4[2] = -1;//-1.z
	equ4[3] = 43;//80

	equ5[0] = 1;	//0.x
	equ5[1] = 0;	//0.y
	equ5[2] = -1;//-1.z
	equ5[3] = 43;//80

	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);
	glClipPlane(GL_CLIP_PLANE2,equ2);
	glClipPlane(GL_CLIP_PLANE3,equ3);
	glClipPlane(GL_CLIP_PLANE4,equ4);
	glClipPlane(GL_CLIP_PLANE5,equ5);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE5);
	glEnable(GL_CLIP_PLANE4);
	glEnable(GL_CLIP_PLANE3);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glScalef(1,1,15);
			glutSolidTorus(2,20+50,50,50);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(14.4,17.5+50*1.03,0);
			glRotatef(90,0,1,0);
			glScalef(15,1.3,1);
			glutSolidCircle(2,50);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-14.4,17.5+50*1.03,0);
			glRotatef(90,0,1,0);
			glScalef(15,1.3,1);
			glutSolidCircle(2,50);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);
	glDisable(GL_CLIP_PLANE4);
	glDisable(GL_CLIP_PLANE5);

	

}

void hostChairBack(){
	
	double equ[4];
	double equ1[4];
	double equ2[4];
	double equ3[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = 10;//80

	equ1[0] = -1;	//0.x
	equ1[1] = 0;	//0.y
	equ1[2] = 0;//-1.z
	equ1[3] = 10.1;//80
	
	equ2[0] = 1;	//0.x
	equ2[1] = 0;	//0.y
	equ2[2] = 0;//-1.z
	equ2[3] = 10.1;//80

	equ3[0] = 0;	//0.x
	equ3[1] = 1;	//0.y
	equ3[2] = 0;//-1.z
	equ3[3] = 0;//80

	glClipPlane(GL_CLIP_PLANE0,equ);
	glClipPlane(GL_CLIP_PLANE1,equ1);
	glClipPlane(GL_CLIP_PLANE2,equ2);
	glClipPlane(GL_CLIP_PLANE3,equ3);

	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE3);
	glEnable(GL_CLIP_PLANE2);
	glEnable(GL_CLIP_PLANE1);
	glEnable(GL_CLIP_PLANE0);{
		glPushMatrix();{
			glScalef(1,1,15);
			glutSolidTorus(2,20,50,50);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(10,17.5,0);
			glRotatef(90,0,1,0);
			glScalef(15,1.3,1);
			glutSolidCircle(2,50);
		}glPopMatrix();
		glPushMatrix();{
			glTranslatef(-10,17.5,0);
			glRotatef(90,0,1,0);
			glScalef(15,1.3,1);
			glutSolidCircle(2,50);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE3);

}


void drawGrid(){
	int i;

	//WILL draw grid IF the "canDrawGrid" is true:

	if(canDrawGrid == 1){
		glColor3f(0.3, 0.3, 0.3);	//grey
		glBegin(GL_LINES);{
			for(i=-10;i<=10;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);

			}
		}glEnd();
		// draw the two AXES
		//glColor3f(1, 1, 1);	//100% white
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_LINES);{
			//Y axis
			glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
			glVertex3f(0,  150, 0);

			//X axis
			glVertex3f(-150, 0, 0);
			glVertex3f( 150, 0, 0);
		}glEnd();
	}

	
}

void glutCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)   {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void glutSolidCircle(float r, int num_segments) {
    int i=0;
	float theta=(i*2*M_PI)/num_segments;
	float x1=r*cos(theta);
	float y1=r*sin(theta);
	for(i=1;i<=num_segments;i++){
		theta=(i*2*M_PI)/num_segments;
		float x2=r*cos(theta);
		float y2=r*sin(theta);
		
		glBegin(GL_TRIANGLES);{
			glVertex3f(0,0,0);
			glVertex3f(x1,y1,0);
			glVertex3f(x2,y2,0);
		}glEnd();
		
		x1=x2;
		y1=y2;

	}
}

void glutSolidCylinder(float r, float height, int nothing, int num_segments) {
    int i=0;
	float theta=(i*2*M_PI)/num_segments;
	float x1=r*cos(theta);
	float y1=r*sin(theta);
	for(i=1;i<=num_segments;i++){
		theta=(i*2*M_PI)/num_segments;
		float x2=r*cos(theta);
		float y2=r*sin(theta);
		
		glBegin(GL_TRIANGLES);{
			glVertex3f(0,0,0);
			glVertex3f(x1,y1,0);
			glVertex3f(x2,y2,0);
		}glEnd();


		glBegin(GL_TRIANGLES);{
			glVertex3f(0,0,height);
			glVertex3f(x1,y1,height);
			glVertex3f(x2,y2,height);
		}glEnd();
		
		glBegin(GL_QUADS);{
			glVertex3f(x1,y1,0);
			glVertex3f(x2,y2,0);
			glVertex3f(x2,y2,height);
			glVertex3f(x1,y1,height);
		}glEnd();


		x1=x2;
		y1=y2;

	}
}

void glutWireCylinder(float r, float height, int slices, int num_segments) {
    int i=0;
	float theta=(i*2*M_PI)/num_segments;
	float x1=r*cos(theta);
	float y1=r*sin(theta);
	for(i=1;i<=num_segments;i++){
		theta=(i*2*M_PI)/num_segments;
		float x2=r*cos(theta);
		float y2=r*sin(theta);
		
		/*glBegin(GL_TRIANGLES);{
			glVertex3f(0,0,0);
			glVertex3f(x1,y1,0);
			glVertex3f(x2,y2,0);
		}glEnd();


		glBegin(GL_TRIANGLES);{
			glVertex3f(0,0,height);
			glVertex3f(x1,y1,height);
			glVertex3f(x2,y2,height);
		}glEnd();
		*/
		float slice_height=height/(slices*1.0);
		float h=0;
		for(int j=0;j<=slices;j++){
			
			glBegin(GL_LINES);{
				glVertex3f(x1,y1,h);
				glVertex3f(x2,y2,h);
			}glEnd();
			h+=slice_height;
		}


		
		glBegin(GL_LINES);{
			glVertex3f(x1,y1,0);
			glVertex3f(x1,y1,height);
		}glEnd();


		glBegin(GL_LINES);{
			glVertex3f(x2,y2,0);
			glVertex3f(x2,y2,height);
		}glEnd();

		x1=x2;
		y1=y2;

	}
}