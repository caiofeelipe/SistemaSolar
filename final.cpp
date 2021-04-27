#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "imageloader.h"

static float sunAngle = 0;
static float mercuryAngle = 0;
static float venusAngle = 0;
static float earthAngle = 0;
static float marsAngle = 0;
static float jupiterAngle = 0;
static float saturnAngle = 0;
static float uranusAngle = 0;
static float neptuneAngle = 0;
static float angle=0.0,deltaAngle = 0.0,ratio;
static float x=0.0f,y=0.0f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=0.0f;
static float px=0.0f,py=0.0f,pz=0.0f;
static int deltaMove=0;
bool press = false;

GLuint textureSun, textureMercury, textureVenus, textureEarth, textureMars, textureJupiter, textureSaturn,
   textureSaturnRing, textureUranus, textureNeptune;
GLUquadric *sunQuadric, *mercuryQuadric, *venusQuadric, *earthQuadric, *marsQuadric, *jupiterQuadric,
   *saturnQuadric, *saturnRingQuadric, *uranusQuadric, *neptuneQuadric;

GLuint loadTexture(Image* image)
{
   GLuint textureId;
   glGenTextures(1, &textureId);
   glBindTexture(GL_TEXTURE_2D, textureId);

   glTexImage2D(GL_TEXTURE_2D,
      0,
      GL_RGB,
      image->width, image->height,
      0,
      GL_RGB,
      GL_UNSIGNED_BYTE,
      image->pixels);

   return textureId;
}

void init(void) {
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   GLfloat ambientLight[] = { 0, 0, 0, 1.0 };
   GLfloat diffuseLight[] = { 0, 0, 0, 1.0 };
   GLfloat specularLight[] = { 0, 0, 0, 1.0 };
   GLfloat shininess[] = { 128.0f };
   
   GLfloat lightPosition[] = { 0.1, 0.1, 10.0, 1.0 };
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

   glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

   sunQuadric = gluNewQuadric();
   ImageLoader loader;
   Image* imageSun = loader.loadBMP("textures/sun.bmp");
   textureSun = loadTexture(imageSun);
   delete imageSun;

   mercuryQuadric = gluNewQuadric();
   Image* imageMerc = loader.loadBMP("textures/mercury.bmp");
   textureMercury = loadTexture(imageMerc);
   delete imageMerc;

   venusQuadric = gluNewQuadric();
   Image* imageVenus = loader.loadBMP("textures/venus.bmp");
   textureVenus = loadTexture(imageVenus);
   //delete imageVenus;

   earthQuadric = gluNewQuadric();
   Image* imageEarth = loader.loadBMP("textures/earth.bmp");
   textureEarth = loadTexture(imageEarth);
   delete imageEarth;

   marsQuadric = gluNewQuadric();
   Image* imageMars = loader.loadBMP("textures/mars.bmp");
   textureMars = loadTexture(imageMars);
   delete imageMars;

   jupiterQuadric = gluNewQuadric();
   Image* imageJupiter = loader.loadBMP("textures/jupiter.bmp");
   textureJupiter = loadTexture(imageJupiter);
   delete imageJupiter;

   saturnQuadric = gluNewQuadric();
   Image* imageSaturn = loader.loadBMP("textures/saturn.bmp");
   textureSaturn = loadTexture(imageSaturn);
   delete imageSaturn;

   saturnRingQuadric = gluNewQuadric();
   Image* imageSaturnRing = loader.loadBMP("textures/saturn-ring.bmp");
   textureSaturnRing = loadTexture(imageSaturnRing);
   delete imageSaturnRing;

   uranusQuadric = gluNewQuadric();
   Image* imageUranus = loader.loadBMP("textures/uranus.bmp");
   textureUranus = loadTexture(imageUranus);
   delete imageUranus;

   neptuneQuadric = gluNewQuadric();
   Image* imageNeptune = loader.loadBMP("textures/neptune.bmp");
   textureNeptune = loadTexture(imageNeptune);
   delete imageNeptune;
}

void sun(void)
{
   glPushMatrix();
   glTranslatef(0.0f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureSun);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   gluQuadricTexture(sunQuadric, true);

   // Rotation
   glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluSphere(sunQuadric, 2.3, 90, 90);

   glPopMatrix();
}

void mercury(void)
{
   glPushMatrix();
   
   glRotatef(mercuryAngle, 0, 1, 0);
   glTranslatef(3.0f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureMercury);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(mercuryQuadric, true);
   gluSphere(mercuryQuadric, 0.3, 20, 20);

   glPopMatrix();
}

void venus(void)
{
   glPushMatrix();
   
   glRotatef(venusAngle, 0, 1, 0);
   glTranslatef(4.2f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureVenus);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-187.74, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(venusQuadric, true);
   gluSphere(venusQuadric, 0.4, 20, 20);

   glPopMatrix();
}

void earth(void)
{
   glPushMatrix();
   
   glRotatef(earthAngle, 0, 1, 0);
   glTranslatef(5.8f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureEarth);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-66.56, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(earthQuadric, true);
   gluSphere(earthQuadric, 0.5, 20, 20);

   glPopMatrix();
}

void mars(void)
{
   glPushMatrix();
   
   glRotatef(marsAngle, 0, 1, 0);
   glTranslatef(8.0f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureMars);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-64.8, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(marsQuadric, true);
   gluSphere(marsQuadric, 0.35, 20, 20);

   glPopMatrix();
}

void jupiter(void)
{
   glPushMatrix();
   
   glRotatef(jupiterAngle, 0, 1, 0);
   glTranslatef(10.5f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureJupiter);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-86.9, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(jupiterQuadric, true);
   gluSphere(jupiterQuadric, 1, 20, 20);

   glPopMatrix();
}

void saturn(void)
{
   glPushMatrix();
   
   glRotatef(saturnAngle, 0, 1, 0);
   glTranslatef(14.5f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureSaturn);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-63.3, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(saturnQuadric, true);
   gluSphere(saturnQuadric, 0.83, 20, 20);

   glPopMatrix();
}

void saturnRing(void)
{
   glPushMatrix();

   glRotatef(saturnAngle, 0, 1, 0);
   glTranslatef(14.5f, 0.0f, 0.0f);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureSaturnRing);

   // Rotation
   glRotatef(-63.3, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(saturnRingQuadric, true);
   gluDisk(saturnRingQuadric, 1.2, 1.6, 60, 60);

   glPopMatrix();
}

void uranus(void) 
{
   glPushMatrix();
   
   glRotatef(uranusAngle, 0, 1, 0);
   glTranslatef(18.0f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureUranus);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-97.8, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(uranusQuadric, true);
   gluSphere(uranusQuadric, 0.36, 20, 20);

   glPopMatrix();
}

void neptune(void) 
{
   glPushMatrix();
   
   glRotatef(neptuneAngle, 0, 1, 0);
   glTranslatef(20.0f, 0.0f, 0.0f);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureNeptune);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Rotation
   glRotatef(-61.7, 1.0f, 0.0f, 0.0f);
   glRotatef(sunAngle, 0.0f, 0.0f, 1.0f);

   gluQuadricTexture(neptuneQuadric, true);
   gluSphere(neptuneQuadric, 0.36, 20, 20);

   glPopMatrix();
}

void moveme(){
   
   glLoadIdentity();
   gluLookAt (px+x, py+y, z+lz, x+lx, y+ly, lz, 0.0f, 1.0f, 0.0f); //(posicao x, posicao y, posicao z; olha x, olha y, olha z, vupx,vupy,vupz)
   
}

void orienteme(){

}

void keyboard(unsigned char key, int x, int y){
   switch (key) {
      case 's':
	 press = true;
         lz = (lz + 0.3);
         break;
      case 'S':
         press = true;
         lz = (lz + 0.3);
      case 'w':
         press = true;
         lz = (lz - 0.3);
         break;
      case 'W':
         press = true;
         lz = (lz - 0.3);
         break;
      case 'i':  /*  e key rotates at elbow  */
         press = true;
         ly = (ly + 0.3);
         break;
      case 'I':
         press = true;
         ly = (ly + 0.3);
         break;

      case 'k':  /*  e key rotates at elbow  */
         press = true;
         ly = (ly - 0.3);
         break;
      case 'K':
         press = true;
         ly = (ly - 0.3);
         break;

      case 't':  /*  e key rotates at elbow  */
         press = true;
         py = (py - 0.3);
         break;
      case 'T':
         press = true;
         py = (py - 0.3);
         break;

      case 'g':  /*  e key rotates at elbow  */
         press = true;
         py = (py + 0.3);
         break;
      case 'G':
         press = true;
         py = (ly + 0.3);
         break;


      case 'j':  /*  e key rotates at elbow  */
         press = true;
         lx = (lx - 0.1);
         break;
      case 'J':
         press = true;
         lx = (lx - 0.1);
         break;

      case 'l':  /*  e key rotates at elbow  */
         press = true;
         lx = (lx + 0.1);
         break;
      case 'L':
         press = true;
         lx = (lx + 0.1);
         break;

      case 'a':  /*  e key rotates at elbow  */
         press = true;
         px = (px + 0.1);
         break;
      case 'A':
         press = true;
         px = (px + 0.1);
         break;

      case 'd':  /*  e key rotates at elbow  */
         press = true;
         px = (px - 0.1);
         break;
      case 'D':
         press = true;
         px = (px - 0.1);
         break;


      case 'h':  /*  e key rotates at elbow  */
         press = true;
         ly = (ly + 3);
         break;
      case 'H':
         press = true;
         ly = (ly + 3);
         break;

      case 'n':  /*  e key rotates at elbow  */
         press = true;
         ly = (ly - 3);
         break;
      case 'N':
         press = true;
         ly = (ly - 3);
         break;

      case 'f':  /*  e key rotates at elbow  */
         press = true;
         py = (py - 3);
         break;
      case 'F':
         press = true;
         py = (py - 3);
         break;

      case 'v':  /*  e key rotates at elbow  */
         press = true;
         py = (py + 3);
         break;
      case 'V':
         press = true;
         py = (ly + 3);
         break;







      default:
         break;
   }
}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW); //qual matriz vai sofre as próximas operações
   glLoadIdentity(); // inica matriz identidade
   moveme();
   orienteme();
   glTranslatef(0.0f, 0.0f, -30.0f); //translação da matriz

   sun(); //"desenha sol"
   mercury(); //"desenha mercurio"
   venus();//"desenha venus"
   earth();//"desenha terra"
   mars();//"desenha marte"
   jupiter();//"desenha jupter"
   saturn(); //"desenha saturno"
   saturnRing(); //"desenha anel de saturno"
   uranus();//"desenha urano"
   neptune();//"desenha netuno"
   moveme();//"movimentação da camera"
   glutSwapBuffers();//transição smooth
}

void reshape (int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void update(int value)
{
   sunAngle += 2.0f;
   if (sunAngle > 360.0f)
      sunAngle -= 360.0f;

   mercuryAngle += 1.0f;
   if (mercuryAngle > 360.0f)
      mercuryAngle -= 360.0f;
   
   venusAngle += 0.74f;
   if (venusAngle > 360.0f)
      venusAngle -= 360.0f;

   earthAngle += 0.63f;
   if (earthAngle > 360.0f)
      earthAngle -= 360.0f;

   marsAngle += 0.51f;
   if (marsAngle > 360.0f)
      marsAngle -= 360.0f;

   jupiterAngle += 0.28f;
   if (jupiterAngle > 360.0f)
      jupiterAngle -= 360.0f;

   saturnAngle += 0.20f;
   if (saturnAngle > 360.0f)
      saturnAngle -= 360.0f;

   uranusAngle += 0.14f;
   if (uranusAngle > 360.0f)
      uranusAngle -= 360.0f;

   neptuneAngle += 0.11f;
   if (neptuneAngle > 360.0f)
      neptuneAngle -= 360.0f;

   glutPostRedisplay();

   glutTimerFunc(25, update, 2);


}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1500, 800); 
   glutInitWindowPosition (100, 100);

   glutCreateWindow ("Sistema Solar");
   init ();

   glutTimerFunc(25, update, 0);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
