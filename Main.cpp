 
//
//  CG project 'Four seasons'


#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif

#include <iostream>
#include <vector>

using namespace std;

GLint win_width = 600,
win_hight = 600;

GLdouble PI = 3.14159265359;
std::vector<GLfloat> objectX;
std::vector<GLfloat> objectY;
std::vector<GLfloat> targetX;
std::vector<GLfloat> targetY;
GLdouble xOffset = 0.0;
GLdouble yOffset = 0.0;
int flags; // to translate the scenes
int toRain; // rain's down 
int rainbowAp; // rainbow appiers
float cloadPs1 = 0.5; // the initial postion of first cloud
float cloadPs2 = -0.5; // the initial postion of second cloud
float cloadSpeed = 0.0002f;// the speed of clouds movement
float transValue; // the snow translating var
float wtrans; //transition for sea waves
float  wavescale; // scaling for sea waves

float amplitude = 0.02f; // Amplitude of the waves
float wavelength = 0.1f; // Wavelength of the waves
float phase = 0.0f; // Phase shift of the waves
float waveSpeed = 0.003f; // Speed of the waves

int waveSegments = 100; // Number of segments to approximate the wave

//--------/////////////////////////////////////---------// 

float leaf_fall_speed = -0.001f;  // Speed at which the leaves fall 
float currentTime = 0.0f;        // Current time in the animation 
//------------------------------------------------------//


///////////////////// --- sharable functions for most scense --- ////////////////////////





/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *    x (GLFloat) - the x position of the center point of the circle
 *    y (GLFloat) - the y position of the center point of the circle
 *    radius (GLFloat) - the radius that the painted circle will have
 *    function Source: https://gist.github.com/linusthe3rd/803118
 */
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 45; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    // glLineWidth(1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}


//Half circle
void drawHalfCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 109; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 1.0f * PI;
    glLineWidth(12.0f);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

//Half circle -upsidedown-
void HalfCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 50; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = -1.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}


/*
 * Function that handles the drawing of a circle using the line loop
 * method. This will create a hollow circle.
 *
 * Params:
 *    x (GLFloat) - the x position of the center point of the circle
 *    y (GLFloat) - the y position of the center point of the circle
 *    radius (GLFloat) - the radius that the painted circle will have
 *    function Source: https://gist.github.com/linusthe3rd/803118
 */
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 150; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}


void drawFilledCircleww(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI + 40;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

///////////////////////      text methods      ////////////////////


void textq() {
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 0.4);
    glVertex2f(-0.98, 0.97);
    glVertex2f(-0.98, 0.8);
    glVertex2f(-0.1, 0.8);
    glVertex2f(-0.1, 0.97);
    glEnd();
}

/*
* the function that display text on the screen
* it took the sentence as an array of chars
* and print them using for loop
* the method fromat: glutBitmapCharacter(front, the char)
* function Source: https://youtube.com/watch?v=hisoR2MvQaM&t=277s
*/
//text methods
void textm() {
    /*GLUT_BITMAP_9_BY_15
    GLUT_BITMAP_TIMES_ROMAN_24
    GLUT_BITMAP_HELVETICA_10
    GLUT_BITMAP_HELVETICA_12
    GLUT_BITMAP_HELVETICA_18*/
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.3, -0.3, 0.0);
    glScalef(1.3, 3, 1.0);
    textq();
    glPopMatrix();

    glColor3f(1, 1, 1);
    //glRasterPos3f(-0.98, 0.92, 0); 
    glRasterPos3f(-0.96, 0.855, 0);
    char scene1[] = "Dear, do you know who am i?";
    for (int i = 0; i < strlen(scene1); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene1[i]);
    }
    //glRasterPos3f(-0.98, 0.85, 0);
    //char scene12[] = "I am the moon, I am going to take you on";
    //for (int i = 0; i < strlen(scene12); i++)
    //{
    //    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene12[i]);
    //}
    //glRasterPos3f(-0.98, 0.78, 0);
    //char scene13[] = "a journy to meet the four seacons";
    //for (int i = 0; i < strlen(scene13); i++)
    //{
    //    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene13[i]);
    //}
    ////glColor3f(0, 0, 0);
    //glRasterPos3f(-0.98, 0.71, 0);
    //char scene14[] = "Aumtumn   Wenter";
    //for (int i = 0; i < strlen(scene14); i++)
    //{
    //    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene14[i]);
    //}
    //glRasterPos3f(-0.98, 0.64, 0);
    //char scene15[] = "Spring   Summer";
    //for (int i = 0; i < strlen(scene15); i++)
    //{
    //    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene15[i]);
    //}
}
void texta1() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.2, 0, 0);
    glScalef(1.35, 1, 1);
    textq();
    glColor4f(1, 1, 1, 1);
    glPopMatrix();


    glColor3f(0.3, 0, 0.1);
    glRasterPos3f(-0.97, 0.9, 0);
    char scene2[] = "This is Autumn, the season when the";
    for (int i = 0; i < strlen(scene2); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene2[i]);
    }
    glRasterPos3f(-0.97, 0.8, 0);
    char scene21[] = "wind keeps blowing faster and faster.";
    for (int i = 0; i < strlen(scene21); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene21[i]);
    }

}
void texta2() {
    textq();

    glColor3f(0, 0, 0.3);
    glRasterPos3f(-0.97, 0.88, 0);
    char scene3[] = "And clouds gather in the sky.";
    for (int i = 0; i < strlen(scene3); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene3[i]);
    }
}
void texta3() {
    textq();
    glColor3f(0.1, 0, 0);
    glRasterPos3f(-0.97, 0.9, 0);
    char scene4[] = "And tree leaves wither and fall";
    for (int i = 0; i < strlen(scene4); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene4[i]);
    }
    glRasterPos3f(-0.98, 0.83, 0);
    char scene42[] = "to the ground.";
    for (int i = 0; i < strlen(scene42); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene42[i]);
    }
}
void textw1() {
    //glTranslatef(0.3, -0.04, 0);
    //textq();

    glColor3f(1, 1, 1);
    glRasterPos3f(-0.74, 0.87, 0);
    char scene5[] = "Winter, it is the coldest season.";
    for (int i = 0; i < strlen(scene5); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene5[i]);
    }

}
void textw2() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0, -0.45, 0);
    glScalef(1, 1.5, 1);
    textq();
    glPopMatrix();

    glColor3f(0, 0, 0.2);
    glRasterPos3f(-0.96, 0.9, 0);
    char scene52[] = "Rain keeps pouring";
    for (int i = 0; i < strlen(scene52); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene52[i]);
    }
    glRasterPos3f(-0.96, 0.84, 0);
    char scene53[] = "when it stops,";
    for (int i = 0; i < strlen(scene53); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene53[i]);
    }
    glRasterPos3f(-0.96, 0.78, 0);
    char scene54[] = "sometimes a rainbow appears.";
    for (int i = 0; i < strlen(scene54); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene54[i]);
    }
}
void textw3() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.1, 0, 0);
    glScalef(1.1, 1, 1);
    textq();
    glPopMatrix();

    glColor3f(0, 0, 0.3);
    glRasterPos3f(-0.975, 0.9, 0);
    char scene6[] = "  but when snow falls,";
    for (int i = 0; i < strlen(scene6); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene6[i]);
    }
    glRasterPos3f(-0.975, 0.83, 0);
    char scene62[] = "  people like to make smowman.";
    for (int i = 0; i < strlen(scene62); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene62[i]);
    }
}
void textw4() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.2, 0, 0);
    glScalef(1.2, 1, 1);
    textq();
    glPopMatrix();

    glColor3f(0, 0, 0.5);
    glRasterPos3f(-0.98, 0.9, 0);
    char scene7[] = "other times, ";
    for (int i = 0; i < strlen(scene7); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene7[i]);
    }
    glRasterPos3f(-0.98, 0.84, 0);
    char scene72[] = "The sun hides behind the clouds.";
    for (int i = 0; i < strlen(scene72); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene72[i]);
    }

}
void textp1() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.3, 0, 0.0);
    glScalef(1.3, 1, 1.0);
    textq();
    glPopMatrix();

    glColor3f(0, 0.3, 0);
    glRasterPos3f(-0.97, 0.88, 0);
    char scene8[] = "Then Spring comes, weather gets warmer";
    for (int i = 0; i < strlen(scene8); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene8[i]);
    }
}

void textp2() {
    textq();

    glColor3f(0, 0.6, 0.1);
    glRasterPos3f(-0.965, 0.9, 0);
    char scene9[] = "flowers bloom, plants grow,";
    for (int i = 0; i < strlen(scene9); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene9[i]);
    }
    glRasterPos3f(-0.965, 0.82, 0);
    char scene92[] = "and the grass gets greener";
    for (int i = 0; i < strlen(scene92); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene92[i]);
    }
}
void textp3() {
    textq();
    glColor3f(0, 0, 0);
    glRasterPos3f(-0.975, 0.88, 0);
    char scene82[] = "So snow on the mountains melt.";
    for (int i = 0; i < strlen(scene82); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scene82[i]);
    }
}

void texts1() {
    textq();
    glColor3f(0, 0, 0);
    glRasterPos3f(-0.975, 0.88, 0);
    char sceneA[] = "Summer, it is the hottest season";
    for (int i = 0; i < strlen(sceneA); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneA[i]);
    }
}
void texts2() {
    glLoadIdentity();
    textq();

    glColor3f(1, 1, 1);
    glRasterPos3f(-0.96, 0.88, 0);
    char sceneB[] = " The sun's rays are scoring.";
    for (int i = 0; i < strlen(sceneB); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneB[i]);
    }
}
void texts3() {
    glLoadIdentity();
    textq();

    glColor3f(0, 0, 0.3);
    glRasterPos3f(-0.975, 0.91, 0);
    char sceneC[] = "In the summer vacation,";
    for (int i = 0; i < strlen(sceneC); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneC[i]);
    }
    glRasterPos3f(-0.975, 0.83, 0);
    char sceneC2[] = "people like to go to the beach.";
    for (int i = 0; i < strlen(sceneC2); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneC2[i]);
    }
}
void texte1() {
    textq();
    glColor3f(0, 0, 0);
    glRasterPos3f(-0.98, 0.91, 0);
    char sceneD[] = "Now we know the four seasons";
    for (int i = 0; i < strlen(sceneD); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneD[i]);
    }
    glRasterPos3f(-0.98, 0.86, 0);
    char sceneD2[] = "Let's recall them together:";
    for (int i = 0; i < strlen(sceneD2); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneD2[i]);
    }
    glRasterPos3f(-0.98, 0.8, 0);
    char sceneD3[] = "Aumtumn   Wenter   Spring   Summer";
    for (int i = 0; i < strlen(sceneD3); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneD3[i]);
    }
}
void texte2() {
    textq();
    glColor3f(0, 0, 0);
    glRasterPos3f(-0.97, 0.91, 0);
    char sceneE[] = "  Well, that was fun!";
    for (int i = 0; i < strlen(sceneE); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneE[i]);
    }
    glRasterPos3f(-0.97, 0.82, 0);
    char sceneE2[] = "   See you again.";
    for (int i = 0; i < strlen(sceneE2); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sceneE2[i]);
    }
}

void drawFilledHalfCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = (2.0f * PI) / 2;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

// function to simplefy work with axes
void axes()
{

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0.9, 0);
    glVertex2f(-0.9, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0, 0.9);
    glVertex2f(0, -0.9);
    glEnd();
}


void rinbow() {
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHalfCircle(0, 0, 0.49);
    glColor3f(1.0f, 0.373f, 0.082f);
    drawHalfCircle(0, 0, 0.46);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawHalfCircle(0, 0, 0.43);
    glColor3f(0.0f, 0.8f, 0.0f);
    drawHalfCircle(0, 0, 0.40);
    glColor3f(0.537f, 0.811f, 0.94f);
    drawHalfCircle(0, 0, 0.37);
    glColor3f(0.365f, 0.247f, 0.827f);
    drawHalfCircle(0, 0, 0.34);
    glColor3f(0.6f, 0.2f, 0.8f);
    drawHalfCircle(0, 0, 0.31);
    glBegin(GL_LINES);
    glColor4f(0.556, 0.8, 0.898, 1.0);
    glVertex2f(-0.52, 0);
    glVertex2f(0.52, 0);
    glEnd();
}


void coulds1()
{
    /* glBegin(GL_QUADS);
     glColor3f(0.0, 0.0, 0.0);
     glVertex2f(-1.0, -1.0);
     glVertex2f(1.0, -1.0);
     glVertex2f(1.0, 1.0);
     glVertex2f(-1.0, 1.0);
     glEnd();*/



    glLineWidth(10.0f);
    glColor3f(.0f, .0f, .0f); //lines for coulds
    drawHollowCircle(0, 0, 0.2);
    drawHollowCircle(0.2, -0.1, 0.2);
    drawHollowCircle(0.4, -0.2, 0.2);
    drawHollowCircle(0.2, -0.3, 0.2);
    drawHollowCircle(0.0, -0.4, 0.2);
    drawHollowCircle(-0.2, -0.3, 0.2);
    drawHollowCircle(-0.2, -0.1, 0.2);
    drawHollowCircle(-0.4, -0.2, 0.2);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0, 0, 0.2);
    drawFilledCircle(0.2, -0.1, 0.2);
    drawFilledCircle(0.4, -0.2, 0.2);
    drawFilledCircle(0.2, -0.3, 0.2);
    drawFilledCircle(0.0, -0.4, 0.2);
    drawFilledCircle(-0.2, -0.3, 0.2);
    drawFilledCircle(-0.2, -0.1, 0.2);
    drawFilledCircle(-0.4, -0.2, 0.2);

    drawFilledCircle(.0, -0.2, 0.2); // for half

    glLineWidth(3.0f); //eeyes
    glColor3f(.0f, .0f, .0f);
    drawHollowCircle(0.2, -0.1, 0.1);
    drawHollowCircle(-0.2, -0.1, 0.1);

    glColor3f(1.0f, 1.0f, 1.0f);//eyes hide
    drawFilledCircle(0.2, -0.05, 0.12);
    drawFilledCircle(-0.2, -0.05, 0.12);

    glColor3f(.0f, .0f, .0f); //mouth
    drawHollowCircle(0, -0.35, 0.12);

    glColor3f(1.0f, 1.0f, 1.0f);//mouth hide
    drawFilledCircle(0, -0.3, 0.15);

    glColor4f(.8f, .0f, .4f, .3f);//oo
    drawFilledCircle(0.3, -0.3, 0.09);
    drawFilledCircle(-0.3, -0.3, 0.09);

}

void coulds2()
{
    glLineWidth(10.0f);
    glColor3f(.0f, .0f, .0f); //lines for coulds
    drawHollowCircle(0, 0, 0.2);
    drawHollowCircle(0.2, -0.1, 0.2);
    drawHollowCircle(0.4, -0.2, 0.2);
    drawHollowCircle(0.2, -0.3, 0.2);
    drawHollowCircle(0.0, -0.4, 0.2);
    drawHollowCircle(-0.2, -0.3, 0.2);
    drawHollowCircle(-0.2, -0.1, 0.2);
    drawHollowCircle(-0.4, -0.2, 0.2);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0, 0, 0.2);
    drawFilledCircle(0.2, -0.1, 0.2);
    drawFilledCircle(0.4, -0.2, 0.2);
    drawFilledCircle(0.2, -0.3, 0.2);
    drawFilledCircle(0.0, -0.4, 0.2);
    drawFilledCircle(-0.2, -0.3, 0.2);
    drawFilledCircle(-0.2, -0.1, 0.2);
    drawFilledCircle(-0.4, -0.2, 0.2);

    drawFilledCircle(.0, -0.2, 0.2); // for half

}

void tree()
{
    //Tree trunk
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0.07f, -0.9f);
    glVertex2f(0.07f, 0.25f);
    glVertex2f(-0.07f, 0.25f);
    glVertex2f(-0.07f, -0.9f);
    glEnd();
    //branch1
    glBegin(GL_QUADS);
    glVertex2f(0.07f, 0.0f);
    glVertex2f(0.07f, 0.04f);
    glVertex2f(0.31f, 0.15f);
    glVertex2f(0.24f, 0.09f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.16f, 0.05f);
    glVertex2f(0.24f, 0.0f);
    glVertex2f(0.14f, 0.04f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.18f, 0.09f);
    glVertex2f(0.21f, 0.18f);
    glVertex2f(0.21f, 0.1f);
    glEnd();
    //root
    glBegin(GL_QUADS);
    glVertex2f(0.02f, -0.68f);
    glVertex2f(0.12f, -0.85f);
    glVertex2f(0.4f, -0.9f);
    glVertex2f(0.02f, -0.89f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.03f, -0.68f);
    glVertex2f(-0.13f, -0.85f);
    glVertex2f(-0.4f, -0.9f);
    glVertex2f(-0.03f, -0.89f);
    glEnd();
    //branch2
    glBegin(GL_QUADS);
    glVertex2f(-0.07f, 0.12f);
    glVertex2f(-0.44f, 0.3f);
    glVertex2f(-0.4f, 0.25f);
    glVertex2f(-0.07f, 0.09f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, 0.16f);
    glVertex2f(-0.29f, 0.11f);
    glVertex2f(-0.17f, 0.14f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, 0.2f);
    glVertex2f(-0.31f, 0.31f);
    glVertex2f(-0.29f, 0.21f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4f, 0.27f);
    glVertex2f(-0.48f, 0.24f);
    glVertex2f(-0.38f, 0.25f);
    glEnd();
    drawFilledCircle(0.0, 0.26, 0.071);
    //branch3
    glBegin(GL_QUADS);
    glVertex2f(0.06f, 0.29f);
    glVertex2f(0.45f, 0.43f);
    glVertex2f(0.29f, 0.33f);
    glVertex2f(0.07f, 0.26f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.3f, 0.34f);
    glVertex2f(0.45f, 0.25f);
    glVertex2f(0.26f, 0.32f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.36f, 0.29f);
    glVertex2f(0.36f, 0.24f);
    glVertex2f(0.33f, 0.3f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.39f, 0.28f);
    glVertex2f(0.43f, 0.31f);
    glVertex2f(0.41f, 0.25f);
    glEnd();
    //branch4
    glBegin(GL_QUADS);
    glVertex2f(-0.06f, 0.29f);
    glVertex2f(-0.47f, 0.71f);
    glVertex2f(-0.41f, 0.6f);
    glVertex2f(-0.07f, 0.25f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4f, 0.62f);
    glVertex2f(-0.51f, 0.63f);
    glVertex2f(-0.4f, 0.6f);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(-0.46f, 0.62f);
    glVertex2f(-0.49f, 0.66f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.22f, 0.45f);
    glVertex2f(-0.44f, 0.47f);
    glVertex2f(-0.21f, 0.41f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.35f, 0.46f);
    glVertex2f(-0.38f, 0.53f);
    glVertex2f(-0.38f, 0.46);
    glEnd();
    //branch5
    glBegin(GL_TRIANGLES);
    glVertex2f(0.01f, 0.32f);
    glVertex2f(0.42f, 0.78f);
    glVertex2f(0.05f, 0.31f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.25f, 0.57f);
    glVertex2f(0.37f, 0.62f);
    glVertex2f(0.21f, 0.51f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.3f, 0.58f);
    glVertex2f(0.35f, 0.58f);
    glVertex2f(0.26f, 0.55f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.27f, 0.61f);
    glVertex2f(0.27f, 0.71f);
    glVertex2f(0.29f, 0.63f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.32f, 0.66f);
    glVertex2f(0.45f, 0.71f);
    glVertex2f(0.29f, 0.62f);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0.36f, 0.71f);
    glVertex2f(0.37f, 0.78);
    glEnd();
    //branch6
    glBegin(GL_QUADS);
    glVertex2f(-0.03f, 0.31f);
    glVertex2f(-0.03f, 0.75f);
    glVertex2f(0.02f, 0.75f);
    glVertex2f(0.02f, 0.31f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.03f, 0.5f);
    glVertex2f(-0.15f, 0.59f);
    glVertex2f(-0.1f, 0.58f);
    glVertex2f(-0.03f, 0.53f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.11f, 0.57f);
    glVertex2f(-0.1f, 0.62f);
    glVertex2f(-0.09f, 0.56f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(0.02f, 0.6f);
    glVertex2f(0.19f, 0.7f);
    glVertex2f(0.31f, 0.74f);
    glVertex2f(0.02f, 0.57f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.19f, 0.7f);
    glVertex2f(0.23f, 0.78f);
    glVertex2f(0.22f, 0.71f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.71f);
    glVertex2f(-0.21f, 0.83f);
    glVertex2f(-0.03f, 0.75f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(0.01f, 0.75f);
    glVertex2f(0.07f, 0.81f);
    glVertex2f(0.12f, 0.83f);
    glVertex2f(0.02f, 0.73f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.75f);
    glVertex2f(0.0f, 0.82f);
    glVertex2f(0.01f, 0.75f);
    glEnd();
}

//umbrella function
void umbrella() {
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.0f);
    glVertex2f(-0.05f, 0.33f);
    glVertex2f(-0.1f, 0.35f);
    glVertex2f(-0.15f, 0.13f);
    glVertex2f(-0.1f, 0.13f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.35f, 0.37f);
    glVertex2f(0.2f, 0.28f);
    glVertex2f(0.0f, 0.6f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(0.05f, 0.3f);
    glVertex2f(-0.21f, 0.35f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(0.05f, 0.3f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(-0.21f, 0.35f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(-0.35f, 0.37f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.35f, 0.37f);
    glVertex2f(0.2f, 0.28f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(0.2f, 0.28f);
    glEnd();


}

//draw a tree leaf
void leaf() {

    glColor3f(0.7f, 0.4f, 0.1f);
    drawFilledCircle(0, 0, 0.1);

    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.4f, 0.1f);
    glVertex2f(0.3, 0);
    glVertex2f(0, 0.103);
    glVertex2f(0, -0.103);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.4f, 0.1f);
    glVertex2f(-0.2, 0);
    glVertex2f(-0.04, 0.09);
    glVertex2f(-0.04, -0.09);
    glEnd();
}


void BackGroundd() {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    // sky
    glColor3f(0.392f, 0.584f, 0.929f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.7f, 0.8f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}


/////////////////////////////////// --- Texture Moon scense --- ///////////////////////////////////////////
float transValueX;
float transValueY;
float transValueZ;
float nearr;
float farr;

//// buffers

GLuint myTexture1;

char image1Path[] = "C:\\Users\\pc\\Documents\\CG\\Davincii\\moon.bmp";

GLuint LoadTexture(const char* filename, int width, int height)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;


    //The following code will read in our RAW file
    fopen_s(&file, filename, "rb");


    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
        exit(0);
        return 0;
    }

    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    fclose(file);


    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }


    /////////////////////////////////////////

    glGenTextures(1, &texture);            //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    /////////////////////////////////////////

    free(data); //free the texture array

    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    return texture; //return whether it was successfull  
}

//Transitions between scenes by pressing the keyboard
////////////////////////////////////////


static void special(int key, int x, int y)
{

    //handle special keys

    switch (key) {

        //----------------------


    case GLUT_KEY_DOWN:
        rainbowAp = 0;
        toRain = 1;
        cout << " It's rainning :" << toRain << endl;
        glutPostRedisplay();

        break;
    case GLUT_KEY_UP:
        toRain = 0;
        rainbowAp = 1;
        cout << " It's rainning :" << toRain << endl;

        

        glutPostRedisplay();
        break;

    default:

        break;

        //----------------------

    }
}

static
void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON) {

        if (state == GLUT_UP) {
            wavescale = 1;
        }


    }


    if (button == GLUT_RIGHT_BUTTON) {

        if (state == GLUT_UP) {
            wavescale = -1; //reflect
        }
    }
}


//static void play(void)
//{
//    glutPostRedisplay();
//}




void idle() {
    if (flags == 9) {
        cloadPs1 += cloadSpeed;
        if (cloadPs1 > 1.2) {
            cloadPs1 = 0.5;
        }
        cloadPs2 += cloadSpeed;
        if (cloadPs2 > 0.1) {
            cloadPs2 = -0.5;
        }
        glutPostRedisplay();
    }
    glutPostRedisplay();
}


//void specialKey(int key, int x, int y) { 
//    switch (key) { 
//    //case GLUT_KEY_UP: 
//    //    leaf1_y -= translationAmount;  // Translate leaf1 up 
//    //    break; 
//    //case GLUT_KEY_DOWN: 
//    //    leaf1_y += translationAmount;  // Translate leaf1 down 
//    //    break; 
//    //case GLUT_KEY_LEFT: 
//    //    leaf2_y -= translationAmount;  // Translate leaf2 up 
//    //    break; 
//    //case GLUT_KEY_RIGHT: 
//    //    leaf2_y += translationAmount;  // Translate leaf2 down 
//    //    break; 
//    //case GLUT_KEY_F1: 
//    //    leaf3_y -= translationAmount;  // Translate leaf3 up 
//    //    break; 
//    //case GLUT_KEY_F2: 
//    //    leaf3_y += translationAmount;  // Translate leaf3 down 
//    //    break; 
//    //} 
// 
//    glutPostRedisplay();  // Trigger a redraw 
//}






void key(unsigned char key, int x, int y) {
    switch (key) {
    case 's':
        if (flags == 9) {
            // Move all objects down until they reach the target position
            for (size_t i = 0; i < objectX.size(); ++i) {
                if (objectY[i] > targetY[i]) {
                    objectY[i] -= 0.1f;
                    if (objectY[i] < targetY[i]) {
                        objectY[i] = targetY[i];  // Stop at target position

                    }
                }
            }
        }
        //else if(flags == 2) {
        //    // Move all objects down until they reach the target position
        //    objectYA += -0.01;
        //    if (objectYA > targetYA) {
        //        objectYA = 0.5;
        //    }
            //for (float i = 0.0 ; i < objectXA ; ++i) {
            //    if (objectYA[i] > targetYA) {
            //        objectYA[i] -= 0.01f;
            //        objectXA[i] += 0.001f;
            //        if (objectYA[i] < targetYA) {
            //            objectYA[i] = targetYA;  // Stop at target position

            //        }
            //    }
            //}
        //}
        break;
  //------------------------------
    case 'p':
        //if (flags == 8){
        transValue += 0.1;
        break;
        //}
    case 'P':
        //if (flags == 8) {
        transValue -= 0.1;
        break;
        //}
  //------------------------------
    case 'W':
        wtrans -= 0.01;
        break;

    case 'w':
        wtrans += 0.01;
        break;

 //------------------------------
    case'A':
        flags = 1;
        glutPostRedisplay();
        break;
    case'B':
        flags = 2;
        glutPostRedisplay();
        break;
    case'C':
        flags = 3;
        glutPostRedisplay();
        break;
    case'D':
        flags = 4;
        glutPostRedisplay();
        break;
    case'E':
        flags = 5;
        glutPostRedisplay();
        break;

    case'F':
        flags = 6;
        glutPostRedisplay();
        break;
    case'G':
        flags = 7;
        glutPostRedisplay();
        break;
    case'H':
        flags = 8;
        glutPostRedisplay();
        break;
    case'I':
        flags = 9;
        glutPostRedisplay();
        break;

    case'J':
        flags = 10;
        glutPostRedisplay();
        break;

    case'K':
        flags = 11;
        glutPostRedisplay();
        break;
    case'L':
        flags = 12;
        glutPostRedisplay();
        break;
    case'M':
        flags = 13;
        glutPostRedisplay();
        break;
    case'N':
        flags = 14;
        glutPostRedisplay();
        break;

    case'O':
        flags = 15;
        glutPostRedisplay();
        break;
        /*case'T':
            flags = 16;
            glutPostRedisplay();
            break;*/
    }


    glutPostRedisplay();  // Trigger a redraw to update the display
}
///////////////////////////// --- seasons Scenes functions --- ////////////////////////////////

//------------------------------------------   spring scenes  ---------------------------------------------
// 1st scene

void drawGradientBackground()
{
    glBegin(GL_QUADS);

    glColor3f(0.67, 0.76, 1.0); // 171, 196, 255
    glVertex2f(-1.0f, 1.0f);

    glColor3f(0.8, 0.85, 0.99); //  204, 219, 253

    glVertex2f(-1.0f, -1.0f);

    glColor3f(0.8, 0.85, 0.99); //  204, 219, 253
    glVertex2f(1.0f, -1.0f);

    glColor3f(0.67, 0.76, 1.0); // 171, 196, 255
    glVertex2f(1.0f, 1.0f);
    glEnd();

    glFlush();
}

void drawYellowCircle(GLfloat x, GLfloat y, GLfloat radius) {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color

    drawFilledCircle(x, y, radius);
}

void drawSun() {
    const float centerX = 0.8f; // Adjust the X-coordinate for the sun's center
    const float centerY = 0.8f; // Adjust the Y-coordinate for the sun's center
    const float outerRadius = 0.2f;
    const float innerRadius = 0.1f;
    const int numRays = 12;
    const float angleIncrement = 2.0f * PI / numRays;

    // Draw sun rays

    for (int i = 0; i < numRays; i++) {
        const float angle = i * angleIncrement;
        const float x1 = centerX + outerRadius * cos(angle); // Adjust the X-coordinate for the ray's start point
        const float y1 = centerY + outerRadius * sin(angle); // Adjust the Y-coordinate for the ray's start point
        const float x2 = centerX + innerRadius * cos(angle); // Adjust the X-coordinate for the ray's end point
        const float y2 = centerY + innerRadius * sin(angle); // Adjust the Y-coordinate for the ray's end point
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    // Draw sun center
    drawYellowCircle(centerX, centerY, innerRadius);
}

void drawDaisy(GLfloat x, GLfloat y) {

    glColor3f(1.00000f, 0.89804f, 0.89804f);

    const float centerX = 0.0f;
    const float centerY = 0.0f;
    const float outerRadius = 0.02f;
    const float innerRadius = 0.01f;

    const int numOuterCircles = 10;
    const float angleIncrement = 2.0f * PI / numOuterCircles;

    // Draw outer circles
    for (int i = 0; i < numOuterCircles; ++i) {
        const float angle = i * angleIncrement;
        const float x = outerRadius * cos(angle);
        const float y = outerRadius * sin(angle);
        drawFilledCircle(x, y, innerRadius);

    }
    glColor3f(0.95294f, 0.99216f, 0.90980f);
    drawYellowCircle(centerX, centerY, innerRadius);
}

void drawTulip() {
    // Draw a triangle 1
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.1); // Vertex 1
    glVertex2f(0.0, 0.35);  // Vertex 2
    glVertex2f(0.15, 0.1);   // Vertex 3
    glEnd();

    // 2
    glBegin(GL_TRIANGLES);
    glVertex2f(0.31, 0.1); // Vertex 1
    glVertex2f(0.31, 0.35);  // Vertex 2
    glVertex2f(0.15, 0.1);   // Vertex 3
    glEnd();
    //3
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.1); // Vertex 1
    glVertex2f(0.31, 0.1);  // Vertex 2
    glVertex2f(0.15, 0.35);   // Vertex 3
    glEnd();

    //leaf
    glBegin(GL_TRIANGLES);
    glColor3f(0.35686f, 0.60784f, 0.27843f); // Green color

    glVertex2f(0.15, 0.002);
    glVertex2f(0.01, 0.0);
    glVertex2f(-0.095, 0.095);
    glEnd();
    //leaf2
    glBegin(GL_TRIANGLES);
    glColor3f(0.35686f, 0.60784f, 0.27843f); // Green color

    glVertex2f(0.15, -0.095);
    glVertex2f(0.295, -0.075);
    glVertex2f(0.375, 0.043);
    glEnd();


    //stem
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.09804f, 0.41569f, 0.12941f); // Green color
    glVertex2f(0.15, 0.1);
    glVertex2f(0.15, -0.19);
    glEnd();


    // Draw green triangles
    const float triangleSize = 0.05f;
    const float totalWidth = 0.3f;

    const float xOffset = 0.16f;    // X-coordinate offset for the green triangles
    const float yOffset = 0.1f;   // Y-coordinate offset for the green triangles

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.4f, 0.0f);

    for (int i = 0; i < 6; ++i) {
        float x = xOffset - totalWidth / 2.0f + (i * triangleSize);
        float y = yOffset;

        glVertex2f(x, y);                           // Vertex 1
        glVertex2f(x + triangleSize, y);             // Vertex 2
        glVertex2f(x + (triangleSize / 2), y + 0.1f); // Vertex 3
    }

    glEnd();
}

void drawRose()
{
    glBegin(GL_QUADS);

    // glColor3f(1.0f, 0.0f, 0.49f); // pink color

    glVertex2f(-0.4, 0.1); // Bottom-left vertex
    glVertex2f(-0.2f, 0.1);  // Bottom-right vertex
    glVertex2f(-0.2, 0.22);   // Top-right vertex
    glVertex2f(-0.4f, 0.22);  // Top-left vertex

    glEnd();

    // Draw a triangle 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.50f, 0.25f);

    glVertex2f(-0.4, 0.1); // Vertex 1
    glVertex2f(-0.3, 0.1);  // Vertex 2
    glVertex2f(-0.4, 0.3);   // Vertex 3
    glEnd();

    // 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.50f, 0.25f);

    glVertex2f(-0.2, 0.1); // Vertex 1
    glVertex2f(-0.3, 0.1);  // Vertex 2
    glVertex2f(-0.2, 0.3);   // Vertex 3
    glEnd();

    // Draw leaf
    glBegin(GL_TRIANGLES);
    glColor3f(0.32941f, 0.56471f, 0.26667f); // Green color

    glVertex2f(-0.3, 0.0);
    glVertex2f(-0.4, 0.02);
    glVertex2f(-0.45, 0.095);
    glEnd();

    // Draw stem
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.32941f, 0.56471f, 0.26667f); // Green color
    glVertex2f(-0.3, -0.19);
    glVertex2f(-0.3, 0.1);

    glEnd();

}

void Ground() {

    //  glColor3f(0.41569f, 0.63137f, 0.29804f);
    glColor3f(0.25425f, 0.59651f, 0.25596f);
    drawFilledCircle(0.70, -1.0, 0.35);
    drawFilledCircle(0.99, -1.0, 0.35);
    drawFilledCircle(-0.60, -1.0, 0.35);
    drawFilledCircle(-0.90, -1.0, 0.35);
    drawFilledCircle(0.0, -1.1, 0.39);

    glBegin(GL_QUADS);
    glColor3f(0.20242f, 0.54956f, 0.20682f);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glColor3f(0.25425f, 0.59651f, 0.25596f);
    glVertex2f(1.0, -0.73);
    glVertex2f(-1.0, -0.73);
    glEnd();

}


void rever() {

    glBegin(GL_QUADS);
    glColor3f(0.15294f, 0.61961f, 1.00000f); //dark color
    glVertex2f(-1.0, -0.5);
    glColor3f(0.36078f, 0.82353f, 0.90196f); //light color
    glVertex2f(1.0, -0.65);
    glColor3f(0.15294f, 0.61961f, 1.00000f);
    glVertex2f(1.0, -0.2);
    glColor3f(0.36078f, 0.82353f, 0.90196f);
    glVertex2f(-1.0, -0.2);
    glEnd();
}


void drawTreeLeaf() {
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(0.0, 0.0, 0.40);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(0.0, 0.0, 0.35);
    glColor3f(0.29065f, 0.73449f, 0.48217f);
    drawFilledCircle(0.0, 0.0, 0.25);
}

void Grass(GLfloat xOffset, GLfloat yOffset) {
    // Draw green triangles
    const float triangleSize = 0.02f;
    const float totalWidth = 0.02f;

    //  const float xOffset = 0.0f;    // X-coordinate offset for the green triangles
     // const float yOffset = -0.81f;   // Y-coordinate offset for the green triangles

    glBegin(GL_TRIANGLES);
    // glColor3f(0.2f, 0.4f, 0.0f);

    for (int i = 0; i < 6; ++i) {
        float x = xOffset - totalWidth / 2.0f + (i * triangleSize);
        float y = yOffset;

        glVertex2f(x, y);                           // Vertex 1
        glVertex2f(x + triangleSize, y);             // Vertex 2
        glVertex2f(x + (triangleSize / 2), y + 0.1f); // Vertex 3
    }

    glEnd();
}

void cloudsTrans() {
    glPushMatrix();
    glTranslatef(cloadPs1, 0.7, 0.0);
    glScalef(0.4, 0.4, 1.0);
    coulds1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cloadPs2, 0.77, 0.0);
    glScalef(0.4, 0.4, 1.0);
    coulds1();
    glPopMatrix();
}
void springScene1() {
    drawGradientBackground();

    glColor3f(1.0, 1.0, 0.0);
    drawSun();


    /*glPushMatrix();
    glTranslatef(cloadPs, 0.85, 0.0);
    glScalef(0.4, 0.4, 1.0);
    coulds1();
    glPopMatrix();*/


    /*glPushMatrix();
    glTranslatef(-0.5, 0.80, 0.0);
    glScalef(0.4, 0.4, 1.0);
    coulds1();
    glPopMatrix();*/

    drawTreeLeaf();

    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    glScalef(0.6, 0.6, 1.0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12, -0.2, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.190, -0.10, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12, -0.08, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.17, -0.16, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.18, -0.03, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.26, -0.03, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 0.02, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();


    for (size_t i = 0; i < objectX.size(); ++i) {
        glPushMatrix();
        glTranslatef(objectX[i], objectY[i], 0.0f);
        drawDaisy(0.0, 0.0);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(0.16, 0.2, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22, 0.16, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22, 0.16, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22, 0.22, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.27, 0.045, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.215, -0.065, 0.0);
    drawDaisy(0.0f, 0.0f);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.3, -0.5, 0.0);
    glRotatef(200.0, 1.0, 1.0, 1.0);
    drawDaisy(0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, -0.6, 0.0);
    glRotatef(200.0, 1.0, 1.0, 1.0);
    drawDaisy(0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2, -0.3, 0.0);
    glRotatef(200.0, 1.0, 1.0, 1.0);
    drawDaisy(0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, -0.5, 0.0);
    glRotatef(200.0, 1.0, 1.0, 1.0);
    drawDaisy(0.0, 0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.8, -0.6, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glColor3f(0.96863f, 0.54902f, 0.63529f);
    drawRose();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, -0.63, 0.0);
    glScalef(0.3, 0.3, 1.0);
    glColor3f(0.98039f, 0.53333f, 0.70588f);
    drawTulip();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, -0.68, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glColor3f(0.88627f, 0.14902f, 0.33725f);
    drawRose();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, -0.68, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glColor3f(0.84706f, 0.14902f, 0.45882f);
    drawRose();
    glPopMatrix();

    Ground();

    glColor3f(0.2f, 0.4f, 0.0f);

    Grass(0.4, -0.88);
    Grass(0.0, -0.75);
    Grass(0.1, -0.75);
    Grass(-0.1, -0.75);
    Grass(-0.150, -0.75);
    Grass(0.80, -0.85);
    Grass(-0.3, -0.97);
    Grass(-0.88, -0.80);
    Grass(-0.55, -0.73);
    Grass(-0.6, -0.88);

    glColor3f(0.14902f, 0.61961f, 0.19608f);

    Grass(0.4, -0.93);
    Grass(0.0, -0.79);
    Grass(0.1, -0.79);
    Grass(-0.1, -0.79);
    Grass(-0.150, -0.79);
    Grass(0.80, -0.88);
    Grass(-0.3, -0.99);
    Grass(-0.88, -0.85);
    Grass(-0.55, -0.78);
    Grass(-0.6, -0.90);

    glPushMatrix();
    glTranslatef(0.88, -0.63, 0.0);
    glScalef(0.3, 0.3, 1.0);
    glColor3f(0.98039f, 0.53333f, 0.70588f);
    drawTulip();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, -0.63, 0.0);
    glScalef(0.3, 0.3, 1.0);
    glColor3f(0.88627f, 0.14902f, 0.33725f);
    drawTulip();
    glPopMatrix();

    //text part

    //textp1();
}

/////////////////////////////////

//the mountain
void springMountain() {

    //The sky 187 208  255
    glBegin(GL_QUADS);
    glColor3f(0.73333333333, 0.8156862745, 1);
    glVertex2f(-1, 1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glEnd();

    //sun
    //the ground:

    glBegin(GL_POLYGON);
    glColor3f(0.41568627, 0.7, 0.30588235);
    glVertex2f(1, -0.4);
    glVertex2f(0.5, -0.43);
    glVertex2f(0.4, -0.44);
    glVertex2f(0.36, -0.445);
    glVertex2f(0.3, -0.448);
    glVertex2f(0.28, -0.452);
    glVertex2f(0.24, -0.457);
    glVertex2f(0.2, -0.46);
    glVertex2f(0.18, -0.458);
    glVertex2f(0.16, -0.457);
    glVertex2f(0.15, -0.456);
    glVertex2f(0.12, -0.452);
    glVertex2f(0.1, -0.451);
    glVertex2f(0.05, -0.448);
    glVertex2f(0, -0.442);
    glVertex2f(-0.01, -0.4418);
    glVertex2f(-0.03, -0.4414);
    glVertex2f(0.05, -0.441);
    glVertex2f(-0.065, -0.44);
    glVertex2f(-0.08, -0.4415);
    glVertex2f(-0.1, -0.442);
    glVertex2f(-0.15, -0.448);
    glVertex2f(-0.2, -0.45);
    glVertex2f(-0.25, -0.46);
    glVertex2f(-0.3, -0.465);
    glVertex2f(-0.6, -0.49);
    glVertex2f(-0.63, -0.487);
    glVertex2f(-0.66, -0.483);
    glVertex2f(-0.7, -0.48);
    glVertex2f(-0.73, -0.483);
    glVertex2f(-0.76, -0.487);
    glVertex2f(-0.85, -0.53);
    glVertex2f(-0.89, -0.56);
    glVertex2f(-0.91, -0.565);
    glVertex2f(-0.915, -0.57);
    glVertex2f(-0.926, -0.577);
    glVertex2f(-0.93, -0.58);
    glVertex2f(-0.94, -0.59);
    glVertex2f(-0.964, -0.61);
    glVertex2f(-0.97, -0.63);
    glVertex2f(-1, -0.65);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glEnd();





    //rever
    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.9);
    glVertex2f(1, -0.8);
    glVertex2f(0.95, -0.83);
    glVertex2f(0.93, -0.84);
    glVertex2f(0.88, -0.851);
    glVertex2f(0.83, -0.858);
    glVertex2f(0.76, -0.867);
    glVertex2f(0.7, -0.87);
    glVertex2f(0.62, -0.88);
    glVertex2f(0.54, -0.89);
    glVertex2f(0.47, -0.9);
    glVertex2f(0.39, -0.91);
    glVertex2f(0.33, -0.918);
    glVertex2f(0.27, -0.92);
    glVertex2f(0.2, -0.927);
    glVertex2f(0.15, -0.935);
    glVertex2f(0.1, -0.94);
    glVertex2f(0.02, -0.948);
    glVertex2f(0.0, -0.95);
    glVertex2f(-0.03, -0.959);
    glVertex2f(-0.1, -0.965);
    glVertex2f(-0.16, -0.97);
    glVertex2f(-0.22, -0.98);
    glVertex2f(-0.26, -0.985);
    glVertex2f(-0.28, -0.99);
    glVertex2f(-0.3, -1);
    glVertex2f(1, -1);
    glEnd();


    //Mountain
    //1st mountain
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);
    glVertex2f(-1, -0.65);
    glColor3f(0, 0.52, 0);
    glVertex2f(-.65, 0.4);
    glColor3f(0, 0.4, 0);
    glVertex2f(-.24, -.54);
    glEnd();



    //2nd mountain
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);
    glVertex2f(-.65, -0.6);
    glColor3f(0, 0.52, 0);
    glVertex2f(-.3, 0.3);
    glColor3f(0, 0.4, 0);
    glVertex2f(.3, -.52);
    glEnd();

    //3rd mountain
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);
    glVertex2f(-.3, -0.55);
    glColor3f(0, 0.52, 0);
    glVertex2f(.33, 0.2);
    glColor3f(0, 0.4, 0);
    glVertex2f(.7, -.49);
    glEnd();

    // 
    glBegin(GL_QUADS);
    glColor4f(0, 0.8, 0, 0.03);
    glVertex2f(-.7, 0.1);
    glVertex2f(-.67, 0.12);
    glColor4f(0, 1, 0, 0.1);
    glVertex2f(-.8, -0.5);
    glColor4f(0, 1, 0, 0.1);
    glVertex2f(-.9, -.5);
    glEnd();

    //sun
    glColor3f(1.0f, 1.0f, .0f);
    glPushMatrix();
    glTranslatef(-0.9, -.84, 0.0);
    glScalef(2, 2, 1);

    drawSun();
    glPopMatrix();

    //text part
    textp3();
}

////////////////////////////////////////

/// 2nd scene for spring

void Ground2() {

    // glColor3f(0.67843f, 0.92157f, 0.54118f); light
    glColor3f(0.29804f, 0.83137f, 0.02353f);
    drawFilledCircle(-0.95, 0.026, 0.23);
    drawFilledCircle(-0.60, 0.0, 0.20);
    //  glColor3f(0.00000f, 0.68749f, 0.00000f); daRK
    glBegin(GL_QUADS);
    glColor3f(0.00000f, 0.68749f, 0.00000f);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glColor3f(0.29804f, 0.83137f, 0.02353f);
    glVertex2f(1.0, -0.65);
    glVertex2f(-1.0, -0.50);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.00000f, 0.68749f, 0.00000f);
    glVertex2f(-1.0, -0.2);
    glVertex2f(1.0, -0.2);
    // glColor3f(0.25425f, 0.59651f, 0.25596f);
    glColor3f(0.29804f, 0.83137f, 0.02353f);
    glVertex2f(1.0, 0.1);
    glVertex2f(-1.0, 0.1);
    glEnd();


}
void drawRose(float centerX, float centerY)
{

    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glScalef(0.3, 0.3, 1.0);
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.49f); // pink color

    glVertex2f(-0.4, 0.1); // Bottom-left vertex
    glVertex2f(-0.2f, 0.1);  // Bottom-right vertex
    glVertex2f(-0.2, 0.22);   // Top-right vertex
    glVertex2f(-0.4f, 0.22);  // Top-left vertex

    glEnd();

    // Draw a triangle 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.50f, 0.25f);

    glVertex2f(-0.4, 0.1); // Vertex 1
    glVertex2f(-0.3, 0.1);  // Vertex 2
    glVertex2f(-0.4, 0.3);   // Vertex 3
    glEnd();

    // 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.50f, 0.25f);

    glVertex2f(-0.2, 0.1); // Vertex 1
    glVertex2f(-0.3, 0.1);  // Vertex 2
    glVertex2f(-0.2, 0.3);   // Vertex 3
    glEnd();

    // Draw leaf
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.50f, 0.25f); // Green color

    glVertex2f(-0.3, 0.0);
    glVertex2f(-0.4, 0.02);
    glVertex2f(-0.45, 0.095);
    glEnd();

    // Draw stem
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.50f, 0.25f); // Green color
    glVertex2f(-0.3, -0.15);
    glVertex2f(-0.3, 0.1);

    glEnd();
    glPopMatrix();
}

void drawTulip(float centerX, float centerY) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glScalef(0.2, 0.3, 1.0);
    // Draw a triangle 1
    glBegin(GL_TRIANGLES);
    glColor3f(0.95294f, 0.05490f, 0.36078f);
    glVertex2f(0.0, 0.1); // Vertex 1
    glVertex2f(0.0, 0.35);  // Vertex 2
    glVertex2f(0.15, 0.1);   // Vertex 3


    // 2
    glBegin(GL_TRIANGLES);
    glVertex2f(0.31, 0.1); // Vertex 1
    glVertex2f(0.31, 0.35);  // Vertex 2
    glVertex2f(0.15, 0.1);   // Vertex 3

    //3
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.1); // Vertex 1
    glVertex2f(0.31, 0.1);  // Vertex 2
    glVertex2f(0.15, 0.35);   // Vertex 3
    glEnd();

    //leaf
    glBegin(GL_TRIANGLES);
    glColor3f(0.09804f, 0.41569f, 0.12941f); // Green color

    glVertex2f(0.15, 0.002);
    glVertex2f(0.01, 0.0);
    glVertex2f(-0.095, 0.095);
    glEnd();
    //leaf2
    glBegin(GL_TRIANGLES);
    glColor3f(0.09804f, 0.41569f, 0.12941f); // Green color

    glVertex2f(0.15, -0.095);
    glVertex2f(0.295, -0.075);
    glVertex2f(0.375, 0.043);
    glEnd();


    //stem
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.09804f, 0.41569f, 0.12941f); // Green color
    glVertex2f(0.15, 0.1);
    glVertex2f(0.15, -0.19);
    glEnd();


    // Draw green triangles
    const float triangleSize = 0.05f;
    const float totalWidth = 0.3f;

    const float xOffset = 0.16f;    // X-coordinate offset for the green triangles
    const float yOffset = 0.1f;   // Y-coordinate offset for the green triangles

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.4f, 0.0f);

    for (int i = 0; i < 6; ++i) {
        float x = xOffset - totalWidth / 2.0f + (i * triangleSize);
        float y = yOffset;

        glVertex2f(x, y);                           // Vertex 1
        glVertex2f(x + triangleSize, y);             // Vertex 2
        glVertex2f(x + (triangleSize / 2), y + 0.1f); // Vertex 3
    }

    glEnd();

    glPopMatrix();
}

void drawDaisy2(float centerX, float centerY) {

    glColor3f(1.00000f, 0.50196f, 0.50196f);

    const float outerRadius = 0.02f;
    const float innerRadius = 0.01f;

    const int numOuterCircles = 10;
    const float angleIncrement = 2.0f * PI / numOuterCircles;

    // Draw outer circles
    for (int i = 0; i < numOuterCircles; ++i) {
        const float angle = i * angleIncrement;
        const float x = centerX + outerRadius * cos(angle);
        const float y = centerY + outerRadius * sin(angle);
        drawFilledCircle(x, y, innerRadius);
    }


    glColor3f(0.95294f, 0.99216f, 0.90980f);
    drawYellowCircle(centerX, centerY, innerRadius);
}

void bush() {
    //bush 1
    glPushMatrix();
    glTranslatef(-0.1, 0.0, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);
    glColor3f(0.99216f, 0.36471f, 0.36471f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);

    glPopMatrix();

    //bush 2
    glPushMatrix();
    glTranslatef(-0.1, 0.9, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(1.00000f, 0.66667f, 0.65490f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    //bush 3
    glPushMatrix();
    glTranslatef(0.7, 0.85, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(1.00000f, 0.24314f, 0.42745f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    //bush 4
    glPushMatrix();
    glTranslatef(0.4, 0.8, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(0.99216f, 0.36471f, 0.36471f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    //bush 5
    glPushMatrix();
    glTranslatef(-0.6, 0.9, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(1.00000f, 0.24314f, 0.42745f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    //bush 6
    glPushMatrix();
    glTranslatef(-0.7, 0.1, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(1.00000f, 0.66667f, 0.65490f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    // bush 7
    glPushMatrix();
    glTranslatef(0.6, 0.1, 0.0);
    glColor3f(0, 0.4, 0);
    drawFilledCircle(-0.1, -0.90, 0.05);
    drawFilledCircle(-0.13, -0.90, 0.05);
    drawFilledCircle(-0.16, -0.90, 0.05);
    drawFilledCircle(-0.22, -0.90, 0.05);
    drawFilledCircle(-0.12, -0.85, 0.05);
    drawFilledCircle(-0.19, -0.85, 0.05);

    glColor3f(0.95294f, 0.05490f, 0.36078f);
    drawFilledCircle(-0.1, -0.90, 0.01);
    drawFilledCircle(-0.16, -0.90, 0.01);
    drawFilledCircle(-0.22, -0.90, 0.01);
    drawFilledCircle(-0.12, -0.85, 0.01);
    drawFilledCircle(-0.19, -0.85, 0.01);
    glPopMatrix();

    glEnd();
}

void mountain() {
    //Mountain

    //1st mountain    
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);    glVertex2f(1.0, 0.095);
    glColor3f(0, 0.52, 0);    glVertex2f(0.8, 0.5);
    glColor3f(0, 0.4, 0);    glVertex2f(0.6, 0.095);
    glEnd();

    //2nd mountain   
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);    glVertex2f(0.7, 0.095);
    glColor3f(0, 0.52, 0);    glVertex2f(0.55, 0.4);
    glColor3f(0, 0.4, 0);    glVertex2f(0.395, 0.095);
    glEnd();

    //3rd mountain   
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0.4, 0);     glVertex2f(0.5, 0.095);
    glColor3f(0, 0.52, 0);    glVertex2f(0.32, 0.3);
    glColor3f(0, 0.4, 0);     glVertex2f(0.2, 0.095);
    glEnd();

    // lighting  
    glBegin(GL_LINE);
    glLineWidth(0.3);
    glColor3f(0.67843f, 0.92157f, 0.54118f);
    glVertex2f(0.8, 0.45);
    glColor3f(0.67843f, 0.92157f, 0.54118f);
    glVertex2f(0.7, 0.30);
}

void drawTreeLeaf2() {

    //right tree

    //right
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(0.72, -0.58, 0.15);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(0.72, -0.58, 0.10);
    // glColor3f(0.29065f, 0.73449f, 0.48217f);
    drawFilledCircle(0.72, -0.58, 0.05);
    //left
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(0.49, -0.58, 0.15);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(0.49, -0.58, 0.10);
    // glColor3f(0.29065f, 0.73449f, 0.48217f);
    drawFilledCircle(0.49, -0.58, 0.05);
    //middle
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(0.60, -0.45, 0.20);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(0.60, -0.45, 0.15);
    // glColor3f(0.29065f, 0.73449f, 0.48217f);
    drawFilledCircle(0.60, -0.45, 0.10);



    //----left tree----//

   // right

    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(-0.46, -0.50, 0.15);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(-0.46, -0.50, 0.10);
    drawFilledCircle(-0.46, -0.50, 0.05);

    //left
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(-0.73, -0.50, 0.15);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(-0.73, -0.50, 0.10);
    drawFilledCircle(-0.73, -0.50, 0.05);

    //  middle
    glColor3f(0.18039f, 0.72157f, 0.44706f);
    drawFilledCircle(-0.6, -0.38, 0.20);
    glColor3f(0.24271f, 0.76559f, 0.47170f);
    drawFilledCircle(-0.6, -0.38, 0.15);
    // glColor3f(0.29065f, 0.73449f, 0.48217f);
    drawFilledCircle(-0.6, -0.38, 0.10);


}

void springScene2() {
    drawGradientBackground();

    glColor3f(1.0, 1.0, 0.0);
    drawSun();
    rever();
    Ground2();
    bush();
    drawTreeLeaf2();

    glPushMatrix();
    glTranslatef(0.6, -0.65, 0.0);
    glScalef(0.4, 0.35, 1.0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -0.53, 0.0);
    glScalef(0.4, 0.35, 1.0);
    tree();
    glPopMatrix();
    //right tree

    drawDaisy2(0.75, -0.58);
    drawDaisy2(0.45, -0.57);
    drawDaisy2(0.59, -0.39);
    drawDaisy2(0.43, -0.45);
    drawDaisy2(0.75, -0.44);

    //left tree
    drawDaisy2(-0.50, -0.50);
    drawDaisy2(-0.48, -0.30);
    drawDaisy2(-0.75, -0.45);
    drawDaisy2(-0.76, -0.30);
    drawDaisy2(-0.64, -0.25);

    mountain();

    drawRose(0.0, -0.90);
    drawRose(0.0, 0.10);
    drawRose(0.1, -0.1);
    drawRose(-0.8, 0.25);
    drawRose(0.90, -0.90);
    drawRose(0.2, -0.7);
    drawTulip(0.1, -0.92);
    drawTulip(-0.77, -0.95);
    drawTulip(-0.77, 0.18);
    drawTulip(0.90, -0.1);
    drawTulip(0.70, 0.040);
    drawTulip(-0.2, -0.7);


    // text part

    textp2();
}

//------------------------------------------   summer scenes  ---------------------------------------------

//1st scene
void Beach() {

    //The sky
    glBegin(GL_QUADS);
    glColor3f(0, 0.8, 0.9);
    glVertex2f(-1, 1);
    glVertex2f(-1, 0.3);
    glVertex2f(1, 0.3);
    glVertex2f(1, 1);
    glEnd();

    //The sun
    glColor3f(1.0f, 1.0f, 0.1f);
    drawFilledCircle(0.0, 0.3, .49);

    //sun lines
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0.1);
    glVertex2f(0, 0.95);
    glVertex2f(0, 0.82);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0.1);
    glVertex2f(0.25, 0.78);
    glVertex2f(0.35, 0.91);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0.1);
    glVertex2f(0.46, 0.65);
    glVertex2f(0.68, 0.71);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0.1);
    glVertex2f(-0.3, 0.78);
    glVertex2f(-0.4, 0.91);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0.1);
    glVertex2f(-0.43, 0.65);
    glVertex2f(-0.63, 0.71);
    glEnd();

    //The Beach sand
    glBegin(GL_QUADS);
    glColor3f(0.9, 0.8, 0.3);
    glVertex2f(-1, 0.1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 0.1);
    glEnd();

    //sea waves:


    //sea ​​waves near beach
    glBegin(GL_QUADS);
    glColor3f(0.1, 0.6, 0.8);
    glVertex2f(-1, 0.3);
    glVertex2f(-1, 0.0);
    glVertex2f(1, 0.0);
    glVertex2f(1, 0.3);
    glEnd();

    glColor3f(0.1, 0.7, 0.8);
    HalfCircle(0.8, 0.1, .4);
    HalfCircle(0.2, 0.1, .4);
    HalfCircle(-0.4, 0.1, .4);
    HalfCircle(-1, 0.1, .4);

    glColor3f(0.1, 0.6, 0.8);
    HalfCircle(0.8, 0.2, .4);
    HalfCircle(0.2, 0.2, .4);
    HalfCircle(-0.4, 0.2, .4);
    HalfCircle(-1, 0.2, .4);


    //The rocks
    //right corner
    glColor3f(0.8f, 0.6f, 0.7f);
    drawFilledCircle(0.9, -0.9, .33);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.9, -0.9, .33);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.95, -0.92, 0.28);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(1, -1, 0.22);

    //left corner
    glColor3f(0.8f, 0.6f, 0.7f);
    drawFilledCircle(-0.6, -0.95, .23);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-0.6, -0.95, .23);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-0.63, -0.97, 0.20);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-0.65, -1, 0.15);

    glColor3f(0.8f, 0.6f, 0.7f);
    drawFilledCircle(-0.9, -0.9, .30);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-0.9, -0.9, .30);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-0.95, -0.92, 0.27);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(-1, -1, 0.21);


    //The plants
    //right plant
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.21);
    glVertex2f(0.55, -0.88);
    glVertex2f(0.54, -1);
    glVertex2f(0.6, -0.85);
    glVertex2f(0.6, -1);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.21);
    glVertex2f(0.62, -0.87);
    glVertex2f(0.55, -1);
    glVertex2f(0.64, -0.9);
    glVertex2f(0.62, -1);
    glEnd();

    //left plant
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.21);
    glVertex2f(-0.4, -0.9);
    glVertex2f(-0.39, -1);
    glVertex2f(-0.35, -0.86);
    glVertex2f(-0.34, -1);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.21);
    glVertex2f(-0.33, -0.85);
    glVertex2f(-0.38, -1);
    glVertex2f(-0.3, -0.9);
    glVertex2f(-0.32, -1);
    glEnd();


    //carpet 
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(0.1, -0.4);
    glVertex2f(-0.3, -0.4);
    glVertex2f(-0.4, -0.6);
    glVertex2f(0, -0.6);
    glEnd();

    //puple parts of carpet
    glBegin(GL_QUADS);
    glColor3f(0.784313725, 0.71372549, 1);
    glVertex2f(0.1, -0.4);
    glVertex2f(0.01, -0.4);
    glVertex2f(-0.1, -0.6);
    glVertex2f(0, -0.6);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.784313725, 0.71372549, 1);
    glVertex2f(-0.09, -0.4);
    glVertex2f(-0.2, -0.4);
    glVertex2f(-0.3, -0.6);
    glVertex2f(-0.21, -0.6);
    glEnd();

    //lines for carpet
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(0.1, -0.4);
    glVertex2f(-0.3, -0.4);
    glVertex2f(-0.4, -0.6);
    glVertex2f(0, -0.6);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0.01, -0.4);
    glVertex2f(-0.1, -0.6);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.09, -0.4);
    glVertex2f(-0.21, -0.6);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.2, -0.4);
    glVertex2f(-0.3, -0.6);
    glEnd();


    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //cloudes :

    //cloud 1

    glTranslatef(0.7f, 0.87f, 0.0f);
    glScalef(0.4f, 0.4f, 1.0f);
    coulds1();
    glPopMatrix();

    ////cloud 2

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-0.9, 0.65, 0.0);
    glScalef(0.3, 0.3, 1.0);
    coulds1();
    glPopMatrix();

    ////cloud 3
    //
    //Umbrella: 
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.2, -0.6, 0.0);
    glScalef(0.7, 0.7, 1.0);
    umbrella();
    glPopMatrix();

    //text part

    texts3();
}

/*
Function that handles the drawing of a wave
Source: https://poe.com/chat/2nlv887sd09ymf2pxib
*/
void waves() {
    glColor3f(0.1, 0.7, 0.8); // Set color to blue

    //float amplitude = 0.02f; // Amplitude of the waves
    //float wavelength = 0.1f; // Wavelength of the waves
    //float phase = 0.0f; // Phase shift of the waves
    //float waveSpeed = 0.001f; // Speed of the waves

    //int waveSegments = 100; // Number of segments to approximate the wave

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < win_width; i++) {
        float x = static_cast<float>(i) / win_width;
        float y = amplitude * sin((2.0f * 3.14159f / wavelength) * x + phase);
        glVertex2f(x, y);
    }
    glEnd();

    phase += waveSpeed;
}

void waveTrans() {

    glPushMatrix();
    glTranslatef(wtrans, 0, 0.0);
    waves();
    glTranslatef(wtrans, 0.2, 0.0);
    waves();
    glScalef(wavescale, wavescale, 1.0);
    //MyMainObj();
    waves();
    glPopMatrix();

}


////////////////////////////////////////

// 2nd scene for summer 
void summerTree() {

    //The sky
    glBegin(GL_QUADS);
    glColor4f(0.53529412, 0.5235294, 1, 0.7); //182  220  254
    glVertex2f(-1, 1);
    glColor4f(0.33529, 0.823534, 1.0, 0.4);
    glVertex2f(-1, -0.7);
    glColor4f(0.33529, 0.823534, 1.0, 0.4);
    glVertex2f(1, -0.7);
    glColor4f(0.53529412, 0.5235294, 1, 0.7);
    glVertex2f(1, 1);
    glEnd();

    //The sun
    glColor3f(1.0f, 1.0f, 0.1f);
    drawFilledCircle(-0.7f, 0.53, .25);

    //clouds
    //1st cloud
    glColor3f(1, 1, 1);
    drawFilledCircle(0.7, 0.08, 0.1);

    glColor3f(1, 1, 1);
    drawFilledCircle(0.6, 0.06, 0.08);

    glColor3f(1, 1, 1);
    drawFilledCircle(0.52, 0.05, 0.05);

    glColor3f(1, 1, 1);
    drawFilledCircle(0.82, 0.06, 0.08);

    //2nd cloud
    glColor3f(1, 1, 1);
    drawFilledCircle(-0.5, 0.2, 0.1);

    glColor3f(1, 1, 1);
    drawFilledCircle(-0.6, 0.18, 0.08);

    glColor3f(1, 1, 1);
    drawFilledCircle(-0.67, 0.17, 0.05);

    glColor3f(1, 1, 1);
    drawFilledCircle(-0.4, 0.18, 0.08);

    glColor3f(1, 1, 1);
    drawFilledCircle(-0.34, 0.17, 0.05);


    //The gound:

    //rocks

    //yellow rocks 
    glColor3f(0.9568627, 0.82745098, 0.3686274);
    drawFilledCircle(-1, -0.48, .3);

    glBegin(GL_POLYGON);
    glColor3f(0.9568627, 0.82745098, 0.3686274);
    glVertex2f(-0.9, -0.25);
    glVertex2f(-0.8, -0.25);
    glVertex2f(-0.78, -0.28);
    glVertex2f(-0.75, -0.29);
    glVertex2f(-0.33, -0.29);
    glVertex2f(-0.3, -0.31);
    glVertex2f(-0.29, -0.315);
    glVertex2f(-0.12, -0.55);
    glVertex2f(-0.9, -0.55);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9568627, 0.82745098, 0.3686274);
    glVertex2f(0.5, -0.4);
    glVertex2f(0.185, -0.4);
    glVertex2f(0.185, -0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9568627, 0.82745098, 0.3686274);
    glVertex2f(0.185, -0.48);
    glVertex2f(0.07, -0.48);
    glVertex2f(0.07, -0.6);
    glVertex2f(0.185, -0.6);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9568627, 0.82745098, 0.3686274);
    glVertex2f(0.07, -0.51);
    glVertex2f(0.0, -0.52);
    glVertex2f(0.0, -0.6);
    glVertex2f(0.07, -0.6);
    glEnd();

    glColor3f(0.9568627, 0.82745098, 0.3686274);//
    drawFilledCircle(0.199, -0.416, .018);

    glColor3f(0.9568627, 0.82745098, 0.3686274);
    drawFilledCircle(0.07, -0.509, .0254);

    //dark rock
    glColor3f(0.8, 0.6, 0.0);
    drawFilledCircle(0.7, -0.85, .6);

    glColor3f(0.8, 0.6, 0.0);
    HalfCircle(0.0, -0.54, .6);

    glColor3f(0.8, 0.6, 0.0);
    drawFilledCircle(-0.56, -0.8, .47);

    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.6, 0.0);
    glVertex2f(0.4, -0.33);
    glVertex2f(0.4, -0.6);
    glVertex2f(0.0, -0.6);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.6, 0.0);
    glVertex2f(-1, -0.55);
    glVertex2f(-1, -0.4);
    glVertex2f(-0.8, -0.4);
    glVertex2f(-0.8, -0.55);
    glEnd();

    //light rocks
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.7, 0.0);
    glVertex2f(1, -0.42);
    glVertex2f(0.8, -0.42);
    glVertex2f(0.78, -0.424);
    glVertex2f(0.77, -0.45);
    glVertex2f(0.715, -0.48);
    glVertex2f(0.71, -0.51);
    glVertex2f(0.7, -0.522);
    glVertex2f(0.619, -0.522);
    glVertex2f(0.61, -0.5);
    glVertex2f(0.57, -0.58);
    glVertex2f(1, -0.58);

    glEnd();

    glColor3f(0.9, 0.7, 0.0);
    drawFilledCircle(0.77f, -0.48, .061);

    ////light herb
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(-1, -0.9);
    glVertex2f(-1, -0.55);
    glVertex2f(1, -0.55);
    glVertex2f(1, -0.9);
    glEnd();

    //1st square left light plant
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(-1, -0.9);
    glVertex2f(-1, -0.5);
    glVertex2f(-0.6, -0.5);
    glVertex2f(-0.6, -0.9);
    glEnd();

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(-0.6f, -0.56, .061);

    //2nd square left light plant
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(-1, -0.9);
    glVertex2f(-1, -0.47);
    glVertex2f(-0.88, -0.47);
    glVertex2f(-0.88, -0.9);
    glEnd();

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(-0.9f, -0.53, .061);


    //lil half circle near the dark plant
    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(-0.48f, -0.9, .07);

    //dark herb
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.7, 0.0);
    glVertex2f(-1, -0.9);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, -0.9);
    glEnd();



    //square left dark plant
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.7, 0.0);
    glVertex2f(-1, -0.85);
    glVertex2f(-1, -1);
    glVertex2f(-0.7, -1);
    glVertex2f(-0.7, -0.85);
    glEnd();

    glColor3f(0.5, 0.7, 0.0);
    drawFilledCircle(-0.7f, -0.91, .061);



    //1st small plant dark green -right side-
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.7, 0.0);
    glVertex2f(0.85, -0.80);
    glVertex2f(0.85, -0.91);
    glVertex2f(0.9, -0.85);
    glVertex2f(0.9, -0.9);
    glEnd();

    //2nd small plant dark green -right side-
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.7, 0.0);
    glVertex2f(0.75, -0.80);
    glVertex2f(0.75, -0.91);
    glVertex2f(0.8, -0.85);//
    glVertex2f(0.8, -0.9);
    glEnd();

    //3rd small plant dark green -left side-
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.7, 0.0);
    glVertex2f(-0.97, -0.80);
    glVertex2f(-0.97, -0.91);
    glVertex2f(-0.92, -0.75);//
    glVertex2f(-0.92, -0.91);
    glEnd();

    //4th small plant light green -left side-
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(-0.55, -0.45);
    glVertex2f(-0.55, -0.6);
    glVertex2f(-0.5, -0.4);
    glVertex2f(-0.5, -0.6);
    glEnd();

    //5th small plant light green -left side-
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(-0.45, -0.45);
    glVertex2f(-0.45, -0.6);
    glVertex2f(-0.4, -0.4);
    glVertex2f(-0.4, -0.6);
    glEnd();

    //circle plant -right-
    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.35f, -0.58, .08);

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.45f, -0.58, .06);

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.47f, -0.57, .06);

    //square plant -right-
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(1, -0.5);
    glVertex2f(1, -0.6);
    glVertex2f(0.75, -0.6);
    glVertex2f(0.75, -0.5);
    glEnd();

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.75f, -0.56, .06);

    //under the tree ground glColor4f(0.6, 0.7, 0.0,0.75);
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.7, 0.0);
    glVertex2f(0.45, -0.55);
    glVertex2f(0.45, -0.8);
    glVertex2f(-0.35, -0.8);
    glVertex2f(-0.35, -0.55);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.6, 0.7, 0.0);
    glVertex2f(0.6, -0.64);
    glVertex2f(0.6, -0.7);
    glVertex2f(0.45, -0.7);
    glVertex2f(0.45, -0.64);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.6, 0.7, 0.0);
    glVertex2f(-0.35, -0.55);
    glVertex2f(-0.35, -0.63);
    glVertex2f(-0.47, -0.63);
    glVertex2f(-0.47, -0.55);
    glEnd();

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(-0.48f, -0.59, .042);

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.47f, -0.595, .045);

    glBegin(GL_QUADS);
    glColor3f(0.7, 0.8, 0.3);
    glVertex2f(0.45, -0.7);
    glVertex2f(0.45, -0.75);
    glVertex2f(0.4, -0.75);
    glVertex2f(0.4, -0.7);
    glEnd();

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(0.39f, -0.725, .026);

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(0.45f, -0.775, .026);

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(0.53f, -0.775, .026);

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(0.6f, -0.669, .03);

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(-0.4f, -0.725, .026);

    glBegin(GL_QUADS);
    glColor3f(0.6, 0.7, 0.0);
    glVertex2f(-0.4, -0.7);
    glVertex2f(-0.4, -0.75);
    glVertex2f(-0.35, -0.75);
    glVertex2f(-0.35, -0.7);
    glEnd();

    glColor3f(0.6, 0.7, 0.0);
    drawFilledCircle(-0.48f, -0.725, .026);

    glColor3f(0.7, 0.8, 0.3);
    drawFilledCircle(-0.35f, -0.665, .035);


    // Tree leafs
    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(0.0, 0.2, .3);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(0.1, 0.47, .17);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(-0.2, 0.46, .15);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(-0.28, 0.28, .16);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(-0.29, 0.1, .1);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(-0.14, 0.02, .14);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);
    drawFilledCircle(0.25, 0.33, .19);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);//
    drawFilledCircle(0.28, 0.11, .14);

    glColor3f(0.250980398, 0.56862745, 0.4233529411764706);//
    drawFilledCircle(0.11, 0.0, .15);



    //////////
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0, -0.1, 0);
    glScalef(0.7f, 0.7f, 4.0f);
    tree();
    glPopMatrix();

    //text part
    glLoadIdentity();

    //texts1();

}

////////////////////////////////////////

// 3rd scene for summer: -sun and moon-
void sunMoon() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, .0f, .2f);
    glVertex2f(-1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(.0f, .6f, .9f);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glEnd();
    //moon
    glColor4f(.0f, .0f, .0f, .3f);
    drawFilledCircle(-.3, .4, 0.3);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-.3, .4, 0.28);
    //sun
    glColor3f(1.0f, 1.0f, .0f);
    glPushMatrix();
    glScalef(3, 3, 1);
    glTranslatef(-0.7, -.85, 0.0);
    drawSun();
    glPopMatrix();

    // the text part

    texts2();
}


//------------------------------------------   winter scenes  ---------------------------------------------

//1st scene

void winterWithSun() {

    BackGroundd();
    //sun


    //glPushMatrix();
    //glTranslatef(-0.4, 0.2, 0.0);
    //rinbow();
    //glPopMatrix();

    glColor3f(1.0f, 1.0f, .0f);
    drawFilledCircle(0, 0.3, 0.3);

    // Right side1
    glPushMatrix();
    glTranslatef(0.5, 0.75, 0.0);
    glScalef(0.9, 0.6, 1);
    coulds2();
    glPopMatrix();
    // Right side2
    glPushMatrix();
    glTranslatef(0.55, 0.1, 0.0);
    glScalef(0.7, 0.6, 1);
    coulds2();
    glPopMatrix();
    // Right side3
    glPushMatrix();
    glTranslatef(0.7, -0.5, 0.0);
    glScalef(0.6, 0.4, 1);
    coulds2();
    glPopMatrix();

    // Lift side1
    glPushMatrix();
    glTranslatef(-0.9, 1.3, 0.0);
    glScalef(0.9, 0.9, 1);
    coulds2();
    glPopMatrix();

    // Lift side2
    glPushMatrix();
    glTranslatef(-0.55, 0.25, 0.0);
    glScalef(0.7, 0.6, 1);
    coulds2();
    glPopMatrix();

    // Lift side3

    glPushMatrix();
    glTranslatef(-0.7, -0.4, 0.0);
    glScalef(0.8, 0.5, 1);
    coulds2();

    //text part 
    glLoadIdentity();
    textw4();
}

////////////////////////////////////////

//2nd scene
void rain() {
    glColor3f(.9f, 1.0f, 1.0f);
    drawFilledCircle(0, 0, 0.1);

    glBegin(GL_TRIANGLES);
    glColor3f(.9f, 1.0f, 1.0f);
    glVertex2f(-.1, .01);
    glVertex2f(0.1, .01);
    glVertex2f(0, .3);
    glEnd();

}
//reham
void rrain() {
    //BackGround
    glBegin(GL_QUADS);
    glColor4f(0.556, 0.8, 0.898, 1.0);
    //glColor4f(.0, .4, .5, .2);
    glVertex2f(-1, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1, 1.0);
    glEnd();



    //could
    glPushMatrix();
    glTranslatef(0.1, 0.8, 0.0);
    glScalef(0.9, 0.5, 1);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, 0.6, 0.0);
    glScalef(0.6, 0.4, 1);
    coulds2();
    glPopMatrix();

    //text part
    textw2();
}
void rrain2() {

    //BackGround
    glBegin(GL_QUADS);
    glColor4f(0.556, 0.8, 0.898, 1.0);
    //glColor4f(.0, .4, .5, .2);
    glVertex2f(-1, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1, 1.0);
    glEnd();

    glPushMatrix();
    glTranslatef(0.6, 0.6, 0.0);
    glScalef(0.8, 0.8, 0);
    rinbow();
    glPopMatrix();


    //could
    glPushMatrix();
    glTranslatef(0.1, 0.8, 0.0);
    glScalef(0.9, 0.5, 1);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, 0.6, 0.0);
    glScalef(0.6, 0.4, 1);
    coulds2();
    glPopMatrix();

    //text part
    textw2();

}

void wSRAIN() {

    //Right side

    glPushMatrix();
    glTranslatef(0.55, 0.55, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.65, 0.1, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13, 0.55, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.11, 0.15, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0.38, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(0.42, -0.09, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.72, -0.2, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75, -0.6, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45, -0.45, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, -0.33, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25, -0.75, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, -0.85, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();


    //ـــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــLIFT SIDE

    glPushMatrix();
    glTranslatef(-0.1, 0.0, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.28, 0.5, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.42, 0.22, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.71, 0.45, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.68, 0.05, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.72, -0.76, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7, -0.38, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.29, -0.25, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, -0.53, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, -0.78, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    /*
      glPushMatrix();
      glTranslatef(0.3, 0.9, 0.0);
      glScalef(0.7, 0.6, 1);
      rain();
      glPopMatrix();*/

    glPushMatrix();
    glTranslatef(-0.06, -0.48, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.03, 0.33, 0.0);
    glScalef(0.7, 0.6, 1);
    rain();
    glPopMatrix();

    //could
    glPushMatrix();
    glTranslatef(0.1, 0.8, 0.0);
    glScalef(0.9, 0.5, 1);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, 0.6, 0.0);
    glScalef(0.6, 0.4, 1);
    coulds2();
    glPopMatrix();

    //text part
    textw2();
}



////////////////////////////////////////

// 3rd scene
void backgroundSnowMan() {

    glBegin(GL_QUADS);
    glColor3f(0.7098039f, 0.8862745f, 0.9803921f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void snowMan()
{
    // call here every compounant


    // drawing the filled circle
    //first snow
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0, -0.6, .40);
    //secound snow
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0, -0.18, .35);
    //third snow
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0, 0.30, .30);
    //right eye
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.10, 0.38, .025);

    //left eye
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.10, 0.36, .025);

    //blusher
    glColor4f(1.0f, 0.0f, 0.0f, 0.09f);
    drawFilledCircle(-0.12, 0.21, .033);
    glColor4f(0.7411764f, 0.3098039f, 0.4235294f, 0.09f);
    drawFilledCircle(0.14, 0.22, .033);

    //hat line
    glLineWidth(9.0f);
    glBegin(GL_LINES);
    glColor3f(0.5568627f, 0.490196f, 0.745098f);
    glVertex2f(-0.30f, 0.43f);
    glVertex2f(-0.30f, 0.09f);
    glEnd();
    glLineWidth(9.0f);
    glBegin(GL_LINES);
    glColor3f(0.5568627f, 0.490196f, 0.745098f);
    glVertex2f(0.30f, 0.43f);
    glVertex2f(0.30f, 0.09f);
    glEnd();

    //hat circle
    glColor4f(0.4156862f, 0.2980392f, 0.5764705f, 0.9f);
    drawFilledCircleww(-0.30, 0.09, .04);
    glColor4f(0.4156862f, 0.2980392f, 0.5764705f, 0.9f);
    drawFilledCircleww(0.30, 0.09, .04);


    // nose
    glBegin(GL_TRIANGLES);
    glColor3f(0.9960784f, 0.3647058f, 0.1490196f);
    glVertex2f(0.0f, 0.27f);
    glVertex2f(0.0f, 0.19f);
    glVertex2f(0.40f, 0.3f);
    glEnd();

    //RightHand
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(0.34f, -0.10f);
    glVertex2f(0.34f, -0.15f);
    glVertex2f(0.9f, 0.05f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(0.69f, -0.01f);
    glVertex2f(0.6f, -0.03f);
    glVertex2f(0.8f, 0.1f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(0.45f, -0.08f);
    glVertex2f(0.39f, -0.09f);
    glVertex2f(0.53f, 0.0f);
    glEnd();


    //LeftHand
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(-0.34f, -0.10f);
    glVertex2f(-0.34f, -0.15f);
    glVertex2f(-0.9f, 0.07f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(-0.69f, -0.01f);
    glVertex2f(-0.6f, -0.03f);
    glVertex2f(-0.8f, -0.1f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.2274509f, 0.1490196f, 0.0941176f);
    glVertex2f(-0.45f, -0.08f);
    glVertex2f(-0.39f, -0.09f);
    glVertex2f(-0.53f, 0.0f);
    glEnd();


    glLineWidth(6.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.14f);
    glVertex2f(0.01f, 0.13f);
    glVertex2f(0.02f, 0.12f);
    glVertex2f(0.03f, 0.11f);
    glVertex2f(0.04f, 0.10f);
    glVertex2f(0.05f, 0.10f);
    glVertex2f(0.06f, 0.11f);
    glVertex2f(0.07f, 0.12f);
    glVertex2f(0.08f, 0.13f);
    glVertex2f(0.09f, 0.14f);
    glEnd();

    //hat
    glColor3f(0.5568627f, 0.490196f, 0.745098f);
    drawFilledHalfCircle(0.0, 0.46, .31);
    glBegin(GL_QUADS);
    glColor3f(0.4156862f, 0.2980392f, 0.5764705f);
    glVertex2f(0.35f, 0.53f);
    glVertex2f(-0.35f, 0.53f);
    glVertex2f(-0.35f, 0.43f);
    glVertex2f(0.35f, 0.43f);
    glEnd();
    glColor4f(0.4156862f, 0.2980392f, 0.5764705f, 0.9f);
    drawFilledCircleww(0.0, 0.8, .066);

}

void drawFilledCircleS(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI + 66;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void snow() {
    //x+,y+
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(0.1, 0.1, .03);
    drawFilledCircleS(0.5, 0.5, .03);
    drawFilledCircleS(0.9, 0.9, .03);
    drawFilledCircleS(0.1, 0.2, .03);
    drawFilledCircleS(0.1, 0.8, .03);
    drawFilledCircleS(0.3, 0.3, .03);
    drawFilledCircleS(0.2, 1.0, .03);
    drawFilledCircleS(0.4, 0.3, .03);
    drawFilledCircleS(0.5, 0.6, .03);
    drawFilledCircleS(0.8, 0.2, .03);
    drawFilledCircleS(0.7, 0.8, .03);
    drawFilledCircleS(0.8, 0.1, .03);
    drawFilledCircleS(0.9, 0.4, .03);
    ////+x,-y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(0.3, -0.2, .03);
    drawFilledCircleS(0.8, -0.8, .03);
    drawFilledCircleS(0.2, -0.4, .03);
    drawFilledCircleS(0.1, -0.5, .03);
    drawFilledCircleS(0.1, -0.9, .03);
    drawFilledCircleS(0.4, -0.6, .03);
    drawFilledCircleS(0.5, -0.1, .03);
    drawFilledCircleS(0.5, -0.5, .03);
    drawFilledCircleS(0.8, -0.1, .03);
    drawFilledCircleS(0.6, -0.4, .03);
    drawFilledCircleS(0.8, -0.8, .03);
    drawFilledCircleS(0.9, -0.3, .03);
    drawFilledCircleS(1.0, -1.0, .03);
    //-x,+y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(-0.3, 0.3, .03);
    drawFilledCircleS(-0.6, 0.6, .03);
    drawFilledCircleS(-0.2, 0.3, .03);
    drawFilledCircleS(-0.1, 0.8, .03);
    drawFilledCircleS(-0.4, 0.1, .03);
    drawFilledCircleS(-0.3, 0.3, .03);
    drawFilledCircleS(-0.4, 1.0, .03);
    drawFilledCircleS(-0.5, 0.1, .03);
    drawFilledCircleS(-0.5, 0.5, .03);
    //drawFilledCircleS(-0.5, 0.9, .03);
    drawFilledCircleS(-0.7, 0.3, .03);
    drawFilledCircleS(-0.8, 0.9, .03);
    drawFilledCircleS(-0.9, 0.3, .03);
    drawFilledCircleS(-1.0, 1.0, .03);
    ////-x.-y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(-0.1, -0.1, .03);
    drawFilledCircleS(-0.5, -0.5, .03);
    drawFilledCircleS(-0.7, -0.8, .03);
    drawFilledCircleS(-0.9, -0.9, .03);
    drawFilledCircleS(-0.2, -0.6, .03);
    drawFilledCircleS(-0.1, -0.7, .03);
    drawFilledCircleS(-0.2, -1.0, .03);
    drawFilledCircleS(-0.2, -0.2, .03);
    drawFilledCircleS(-0.4, -0.6, .03);
    drawFilledCircleS(-0.2, -1.0, .03);
    drawFilledCircleS(-0.5, -0.1, .03);
    drawFilledCircleS(-0.6, -0.6, .03);
    drawFilledCircleS(-0.6, -1.0, .03);
    drawFilledCircleS(-0.8, -0.2, .03);
    drawFilledCircleS(-0.7, -0.7, .03);
    drawFilledCircleS(-0.8, -0.9, .03);
    drawFilledCircleS(-1.0, -0.4, .03);
    drawFilledCircleS(-1.0, -0.8, .03);

}
void allSnowManWindow() {
    //the background
    backgroundSnowMan();
    glPushMatrix();
    snowMan();
    glTranslatef(0, transValue, 0);
    snow();
    glPushMatrix();


    //text part

    textw3();
}

////////////////////////////////////////

/// 4th scene for winter ////

void backgroundWiter() {

    //1st
    glColor3f(0.24313725f, 0.36078431f, 0.4627451f);
    drawFilledCircle(0.0, 0.6, 40);

    //2nd
    glBegin(GL_POLYGON);
    glColor3f(0.45490196f, 0.54901961f, 0.67058824f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.0f, 0.14f);
    glVertex2f(0.8f, 0.2f);
    glVertex2f(0.5f, 0.3f);
    glVertex2f(0.3f, 0.34f);
    glVertex2f(-0.2f, 0.42f);
    glVertex2f(-0.4f, 0.43f);
    glVertex2f(-0.6f, 0.44f);
    glVertex2f(-0.8f, 0.42f);
    glVertex2f(-1.0f, 0.41f);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(0.0f, -0.1f);
    glEnd();


    //3rd
    glBegin(GL_POLYGON);
    glColor3f(0.55686275f, 0.79215686f, 0.90196078f);
    glVertex2f(1.0f, 0.16f);
    glVertex2f(0.9f, 0.17f);
    glVertex2f(0.8f, 0.16f);
    glVertex2f(0.7f, 0.13f);
    glVertex2f(0.5f, 0.12f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(0.2f, 0.08f);
    glVertex2f(0.1f, 0.05f);
    glVertex2f(0.0f, 0.02f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.2f, -0.01f);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f(0.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glEnd();
    //4th
    glBegin(GL_POLYGON);
    glColor3f(0.56470588f, 0.87843137f, 0.9372549f);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(1.0f, -0.42f);
    glVertex2f(0.79f, -0.31f);
    glVertex2f(0.6f, -0.22f);
    glVertex2f(0.5f, -0.17f);
    glVertex2f(0.4f, -0.15f);
    glVertex2f(0.2f, -0.08f);
    glVertex2f(0.0f, -0.01f);
    glVertex2f(-0.2f, 0.02f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.4f, 0.06f);
    glVertex2f(-0.6f, 0.1f);
    glVertex2f(-0.7f, 0.11f);
    glVertex2f(-0.9f, 0.12f);
    glVertex2f(-1.0f, 0.11f);
    glVertex2f(-1.0f, -0.6f);
    glEnd();

    //5th
    glBegin(GL_POLYGON);
    glColor3f(0.79215686f, 0.94117647f, 0.97254902f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(0.9f, -0.6f);
    glVertex2f(0.7f, -0.52f);
    glVertex2f(0.5f, -0.45f);
    glVertex2f(0.3f, -0.4f);
    glVertex2f(0.1f, -0.33f);
    glVertex2f(-0.1f, -0.29f);
    glVertex2f(-0.2f, -0.25f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(-0.6f, -0.19f);
    glVertex2f(-0.8f, -0.15f);
    glVertex2f(-1.0f, -0.13f);
    glVertex2f(-1.0f, -1.0f);

    glEnd();
    //6th
    glBegin(GL_POLYGON);
    glColor3f(0.9254902f, 0.97254902f, 0.97254902f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.56f);
    glVertex2f(0.8f, -0.55f);
    glVertex2f(0.7f, -0.57f);
    glVertex2f(0.5f, -0.6f);
    glVertex2f(0.3f, -0.62f);
    glVertex2f(0.1f, -0.66f);
    glVertex2f(-0.1f, -0.69f);
    glVertex2f(-0.3f, -0.71f);
    glVertex2f(-0.5f, -0.77f);
    glVertex2f(-0.7f, -0.83f);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    //roof
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(1.0f, -0.33f);
    glVertex2f(0.55f, -0.33f);
    glVertex2f(0.55f, -0.3f);
    glVertex2f(0.85f, -0.05f);
    glVertex2f(1.0f, -0.1f);
    glEnd();

    //house 
    glBegin(GL_POLYGON);
    glColor3f(0.15686275f, 0.29411765f, 0.38823529f);
    glVertex2f(1.0f, -0.56f);
    glVertex2f(0.7f, -0.55f);
    glVertex2f(0.6f, -0.59f);
    glVertex2f(0.6f, -0.3f);
    glVertex2f(0.85f, -0.1f);
    glVertex2f(1.0f, -0.25f);
    glEnd();





    //window
    glColor3f(0.96470588f, 0.66666667f, 0.10980392f);
    drawFilledCircle(0.83, -0.32, 0.07);

    //window line
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.83, -0.32, 0.07);
    glLineWidth(4.0f);

    //window line 1
    glEnable(GL_LINES);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.83f, -0.25f);
    glVertex2f(0.83f, -0.39f);
    glEnd();


    //window line2
    glBegin(GL_LINES);;
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.76f, -0.32f);
    glVertex2f(0.9f, -0.32f);
    glEnd();


    //door
    glPointSize(0.1f);
    glBegin(GL_LINE_LOOP);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.88f, -0.44f);
    glVertex2f(0.75f, -0.44f);
    glVertex2f(0.75f, -0.58f);
    glVertex2f(0.88f, -0.57f);

    glEnd();

    //chimney
    glBegin(GL_QUADS);
    glColor3f(0.15686275f, 0.29411765f, 0.38823529f);
    glVertex2f(0.98f, -0.05f);
    glVertex2f(0.94f, -0.05f);
    glVertex2f(0.94f, -0.1f);
    glVertex2f(0.98f, -0.1f);
    glEnd();

    //smoke
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
    glVertex2f(0.96f, -0.05f);
    glVertex2f(0.97f, -0.03f);
    glVertex2f(0.99f, -0.01f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.03f);
    glVertex2f(0.99f, 0.05f);
    glVertex2f(0.98f, 0.08f);
    glVertex2f(0.97f, 0.1f);
    glVertex2f(0.96f, 0.12f);
    glVertex2f(0.97f, 0.13f);
    glVertex2f(0.98f, 0.15f);
    glVertex2f(0.95f, 0.17f);
    glVertex2f(0.93f, 0.22f);
    glVertex2f(0.95f, 0.23f);
    glVertex2f(0.96f, 0.24f);
    glVertex2f(0.98f, 0.25f);
    glVertex2f(1.0f, 0.27f);
    glVertex2f(1.0f, 0.46f);
    glVertex2f(0.96f, 0.48f);
    glVertex2f(0.92f, 0.51f);
    glVertex2f(0.89f, 0.54f);
    glVertex2f(0.87f, 0.58f);
    glVertex2f(0.85f, 0.63f);
    glVertex2f(0.83f, 0.65f);
    glVertex2f(0.85f, 0.68f);
    glVertex2f(0.87f, 0.74f);
    glVertex2f(0.88f, 0.79f);
    glVertex2f(0.93f, 0.83f);
    glVertex2f(1.0f, 0.89f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.51f, 1.0f);
    glVertex2f(0.54f, 0.98f);
    glVertex2f(0.6f, 0.928f);
    glVertex2f(0.67f, 0.9f);
    glVertex2f(0.74f, 0.85f);
    glVertex2f(0.78f, 0.818f);
    glVertex2f(0.73f, 0.8f);
    glVertex2f(0.71f, 0.78f);
    glVertex2f(0.698f, 0.75f);
    glVertex2f(0.72f, 0.72f);
    glVertex2f(0.75f, 0.7f);
    glVertex2f(0.759f, 0.67f);
    glVertex2f(0.72f, 0.65f);
    glVertex2f(0.68f, 0.63f);
    glVertex2f(0.65f, 0.61f);
    glVertex2f(0.619f, 0.599f);
    glVertex2f(0.599f, 0.55f);
    glVertex2f(0.59f, 0.519f);
    glVertex2f(0.62f, 0.46f);
    glVertex2f(0.67f, 0.43f);
    glVertex2f(0.74f, 0.4f);
    glVertex2f(0.79f, 0.37f);
    glVertex2f(0.82f, 0.308f);
    glVertex2f(0.85f, 0.27f);
    glVertex2f(0.86f, 0.209f);
    glVertex2f(0.88f, 0.169f);
    glVertex2f(0.909f, 0.105f);
    glVertex2f(0.93f, 0.067f);
    glVertex2f(0.95f, 0.04f);
    glVertex2f(0.94f, 0.01f);
    glVertex2f(0.93f, -0.01f);
    glVertex2f(0.928f, -0.03f);
    glVertex2f(0.95f, -0.05f);

    glEnd();
}

void snow2() {
    //x+,y+
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(0.1, 0.1, .03);
    drawFilledCircleS(0.5, 0.5, .03);
    drawFilledCircleS(0.9, 0.9, .03);
    drawFilledCircleS(0.1, 0.2, .03);
    drawFilledCircleS(0.1, 0.8, .03);
    drawFilledCircleS(0.3, 0.3, .03);
    drawFilledCircleS(0.2, 1.0, .03);
    drawFilledCircleS(0.4, 0.3, .03);
    drawFilledCircleS(0.5, 0.6, .03);
    drawFilledCircleS(0.8, 0.2, .03);
    drawFilledCircleS(0.7, 0.8, .03);
    drawFilledCircleS(0.8, 0.1, .03);
    drawFilledCircleS(0.9, 0.4, .03);
    ////+x,-y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(0.3, -0.2, .03);
    drawFilledCircleS(0.8, -0.8, .03);
    drawFilledCircleS(0.2, -0.4, .03);
    drawFilledCircleS(0.1, -0.5, .03);
    drawFilledCircleS(0.1, -0.9, .03);
    drawFilledCircleS(0.4, -0.6, .03);
    drawFilledCircleS(0.5, -0.1, .03);
    drawFilledCircleS(0.5, -0.5, .03);
    drawFilledCircleS(0.8, -0.1, .03);
    drawFilledCircleS(0.6, -0.4, .03);
    drawFilledCircleS(0.8, -0.8, .03);
    drawFilledCircleS(0.9, -0.3, .03);
    drawFilledCircleS(1.0, -1.0, .03);
    //-x,+y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(-0.3, 0.3, .03);
    drawFilledCircleS(-0.6, 0.6, .03);
    drawFilledCircleS(-0.2, 0.3, .03);
    drawFilledCircleS(-0.1, 0.8, .03);
    drawFilledCircleS(-0.4, 0.1, .03);
    drawFilledCircleS(-0.3, 0.3, .03);
    drawFilledCircleS(-0.4, 1.0, .03);
    drawFilledCircleS(-0.5, 0.1, .03);
    drawFilledCircleS(-0.5, 0.5, .03);
    //drawFilledCircleS(-0.5, 0.9, .03);
    drawFilledCircleS(-0.7, 0.3, .03);
    drawFilledCircleS(-0.8, 0.9, .03);
    drawFilledCircleS(-0.9, 0.3, .03);
    drawFilledCircleS(-1.0, 1.0, .03);
    ////-x.-y
    glColor4f(1.0f, 1.0f, 1.0f, 0.7);
    drawFilledCircleS(-0.1, -0.1, .03);
    drawFilledCircleS(-0.5, -0.5, .03);
    drawFilledCircleS(-0.7, -0.8, .03);
    drawFilledCircleS(-0.9, -0.9, .03);
    drawFilledCircleS(-0.2, -0.6, .03);
    drawFilledCircleS(-0.1, -0.7, .03);
    drawFilledCircleS(-0.2, -1.0, .03);
    drawFilledCircleS(-0.2, -0.2, .03);
    drawFilledCircleS(-0.4, -0.6, .03);
    drawFilledCircleS(-0.2, -1.0, .03);
    drawFilledCircleS(-0.5, -0.1, .03);
    drawFilledCircleS(-0.6, -0.6, .03);
    drawFilledCircleS(-0.6, -1.0, .03);
    drawFilledCircleS(-0.8, -0.2, .03);
    drawFilledCircleS(-0.7, -0.7, .03);
    drawFilledCircleS(-0.8, -0.9, .03);
    drawFilledCircleS(-1.0, -0.4, .03);
    drawFilledCircleS(-1.0, -0.8, .03);


}

void winter() {
    backgroundWiter();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;
    glPushMatrix();
    glTranslatef(-0.6, -0.1, 0.0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, transValue, 0.0);

    snow2();
    glPopMatrix();
    //text part

   // textw1();
}

//------------------------------------------   autumn scenes  ---------------------------------------------

//1st scene
void autumnCoulds() {

    glBegin(GL_QUADS);
    glColor3f(.0, .4, .5);
    glVertex2f(-1, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1, 1.0);
    glEnd();


    // Right side1
    glPushMatrix();
    glTranslatef(0.55, 0.7, 0.0);
    glScalef(0.7, 0.3, 1);
    coulds2();
    glPopMatrix();
    // half side1
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glScalef(0.99, 0.6, 1);
    coulds1();
    glPopMatrix();
    // half side2
    glPushMatrix();
    glTranslatef(0.0, -0.22, 0.0);
    glScalef(0.4, 0.2, 1);
    coulds2();
    glPopMatrix();
    // Right side2
    glPushMatrix();
    glTranslatef(0.6, -0.1, 0.0);
    glScalef(0.4, 0.2, 1);
    coulds2();
    glPopMatrix();
    // Right side3
    glPushMatrix();
    glTranslatef(0.55, -0.6, 0.0);
    glScalef(0.7, 0.3, 1);
    coulds2();
    glPopMatrix();

    // Lift side1
    glPushMatrix();
    glTranslatef(-0.55, 0.7, 0.0);
    glScalef(0.7, 0.3, 1);
    coulds2();
    glPopMatrix();

    // Lift side2
    glPushMatrix();
    glTranslatef(-0.6, -0.1, 0.0);
    glScalef(0.4, 0.2, 1);
    coulds2();
    glPopMatrix();

    // Lift side3
    glPushMatrix();
    glTranslatef(-0.55, -0.6, 0.0);
    glScalef(0.7, 0.3, 1);
    coulds2();
    glPopMatrix();

    // text part
    texta2();
}

////////////////////////////////////////

//2nd scene for autumn
void hill()
{

    glColor3f(0.6f, 0.5f, 0.0f);
    drawFilledCircle(-0.5, -0.9, 0.50);

    glColor3f(0.6f, 0.5f, 0.0f);
    drawFilledCircle(-0.2, -0.9, 0.50);

    glColor3f(0.6f, 0.5f, 0.0f);
    drawFilledCircle(0.2, -0.9, 0.50);

    glColor3f(0.6f, 0.5f, 0.0f);
    drawFilledCircle(0.7, -0.9, 0.50);

    glColor3f(0.6f, 0.5f, 0.0f);
    drawFilledCircle(-0.9, -0.9, 0.40);
    //glEnd();
}

void background()
{
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}


void autumnScene() {
    /////tree 4
    glPushMatrix();
    glTranslatef(-0.3f, -0.25f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glColor3f(0.9f, 0.5f, 0.0f);//tree
    drawFilledCircle(-0.05, 0.47, 0.55);
    glColor3f(0.0f, 0.0f, 0.0f);
    tree();
    glPopMatrix();


    /////part 5
    glPushMatrix();
    glTranslatef(0.3f, -0.25f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glColor3f(0.9f, 0.5f, 0.0f);//tree
    drawFilledCircle(-0.05, 0.47, 0.55);
    glColor3f(0.0f, 0.0f, 0.0f);
    tree();
    glPopMatrix();

    /////part one
    //tree one
    background();
    hill();
    glColor3f(0.9f, 0.5f, 0.0f);//tree
    drawFilledCircle(-0.05, 0.47, 0.55);

    //glColor3f(0.0f, 0.0f, 0.0f);
    tree();

    glColor3f(0.7f, 0.4f, 0.1f);
    glPushMatrix();
    glTranslatef(0.22f, -0.020f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-79.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.29f, 0.13f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 1.0, 0.0, 0.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.21f, 0.16f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(70.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.37f, 0.25f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-65.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.43f, 0.25f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 1.0, 0.0, 0.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.43f, 0.29f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.42f, 0.42f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.43f, 0.69f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.35f, 0.59f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.29f, 0.69f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(68.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.38f, 0.76f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(85.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.29f, 0.74f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, 0.76f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1f, 0.82f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.17f, 0.81f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-198.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.12f, 0.57f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-199.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.5f, 0.64f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-190.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45f, 0.69f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-220.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.42f, 0.46f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-160.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45f, 0.30f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-199.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45f, 0.25f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-158.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.32f, 0.30f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-205.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25f, 0.13f, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-160.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();



    //tree2//////////////////////////
    glPushMatrix();
    glTranslatef(-0.7f, -0.25f, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glColor3f(0.9f, 0.5f, 0.0f);//tree
    drawFilledCircle(-0.05, 0.47, 0.55);
    glColor3f(0.0f, 0.0f, 0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f, -0.20f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-160.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55f, -0.012f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(30.0, 1.0, 0.0, 0.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.52f, 0.028f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();///////////////////


    glPushMatrix();
    glTranslatef(-0.8f, -0.59f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-65.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.59f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(20.0, 1.0, 0.0, 0.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.66f, -0.59f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.72f, -0.63f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.74f, -0.65f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.80f, -0.70f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.85f, -0.65f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(68.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.65f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(85.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.70f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.65f, -0.70f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75f, 0.001f, 0.0);//////////////////
    glScalef(0.1, 0.2, 1.0);
    glRotatef(-205.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.87f, 0.014f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-205.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25f, 0.13f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-160.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    //tree 3
    glPushMatrix();
    glTranslatef(0.6f, -0.2f, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glColor3f(0.9f, 0.5f, 0.0f);//tree
    drawFilledCircle(-0.05, 0.47, 0.55);
    glColor3f(0.0f, 0.0f, 0.0f);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.43f, -0.1f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-205.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.15f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-160.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.69f, -0.20f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.69f, -0.14f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(35.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, -0.10f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, -0.015f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, 0.1f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.64f, 0.14f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(50.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.52f, 0.13f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-190.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42f, 0.090f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-195.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.6f, -0.6f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-195.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.57f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-195.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.58f, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glRotatef(-195.0, 0.0, 0.0, 1.0);
    leaf();
    glPopMatrix();

    //text part

    //texta3();
}

////////////////////////////////////////

//3rd scene for autumn
void leaf_orange() {
    glColor3f(0.9f, 0.5f, 0.0f);
    drawFilledCircle(0, 0, 0.1);
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.5f, 0.0f);
    glVertex2f(0.3, 0);
    glVertex2f(0, 0.103);
    glVertex2f(0, -0.103);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.5f, 0.0f);
    glVertex2f(-0.2, 0);
    glVertex2f(-0.04, 0.09);
    glVertex2f(-0.04, -0.09);
    glEnd();
}

void leaf_yellow() {
    glColor3f(0.9f, 0.7f, 0.0f);
    drawFilledCircle(0, 0, 0.1);
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.7f, 0.0f);
    glVertex2f(0.3, 0);
    glVertex2f(0, 0.103);
    glVertex2f(0, -0.103);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.7f, 0.0f);
    glVertex2f(-0.2, 0);
    glVertex2f(-0.04, 0.09);
    glVertex2f(-0.04, -0.09);
    glEnd();
}

void leaf_green() {
    glColor3f(0.0f, 0.5f, 0.0f);
    drawFilledCircle(0, 0, 0.1);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(0.3, 0);
    glVertex2f(0, 0.103);
    glVertex2f(0, -0.103);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.2, 0);
    glVertex2f(-0.04, 0.09);
    glVertex2f(-0.04, -0.09);
    glEnd();
}

void autumnTree() {


    background();
    hill();

    glPushMatrix();
    glTranslatef(0.9f, 0.90f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.60f, 0.79f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f, 0.64f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9f, 0.90f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.75f, 0.65f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4f, 0.90f, 0.0);
    glScalef(0.3, 0.2, 1.0);
    coulds2();
    glPopMatrix();

    glColor3f(0.9f, 0.5f, 0.0f);
    drawFilledCircle(-0.3, 0.43, 0.15);
    drawFilledCircle(-0.3, 0.48, 0.10);
    drawFilledCircle(-0.4, 0.48, 0.10);
    drawFilledCircle(-0.5, 0.48, 0.10);
    drawFilledCircle(-0.5, 0.54, 0.14);
    drawFilledCircle(-0.5, 0.57, 0.10);
    drawFilledCircle(-0.4, 0.57, 0.13);
    drawFilledCircle(-0.4, 0.30, 0.10);
    drawFilledCircle(-0.2, 0.30, 0.10);
    drawFilledCircle(-0.2, 0.25, 0.10);
    drawFilledCircle(-0.15, 0.23, 0.10);
    drawFilledCircle(-0.15, 0.15, 0.10);
    drawFilledCircle(-0.19, 0.15, 0.10);
    drawFilledCircle(-0.23, 0.15, 0.10);
    drawFilledCircle(-0.29, 0.15, 0.15);
    drawFilledCircle(-0.45, 0.19, 0.15);
    drawFilledCircle(-0.52, 0.23, 0.15);
    drawFilledCircle(-0.55, 0.25, 0.15);
    drawFilledCircle(-0.55, 0.30, 0.15);
    drawFilledCircle(-0.1, 0.40, 0.15);
    drawFilledCircle(-0.20, 0.45, 0.15);
    drawFilledCircle(-0.19, 0.5, 0.10);
    drawFilledCircle(-0.20, 0.53, 0.13);

    glColor3f(0.9f, 0.7f, 0.0f);
    drawFilledCircle(-0.1, 0.53, 0.11);
    drawFilledCircle(-0.1, 0.59, 0.13);
    drawFilledCircle(-0.15, 0.60, 0.13);
    drawFilledCircle(-0.15, 0.65, 0.12);
    drawFilledCircle(-0.05, 0.67, 0.12);
    drawFilledCircle(-0.01, 0.80, 0.13);
    drawFilledCircle(-0.1, 0.80, 0.13);
    drawFilledCircle(0.1, 0.75, 0.15);
    drawFilledCircle(0.1, 0.50, 0.15);
    drawFilledCircle(0.2, 0.55, 0.15);
    drawFilledCircle(0.0, 0.48, 0.13);
    drawFilledCircle(0.29, 0.63, 0.15);

    glColor3f(0.0f, 0.5f, 0.0f);
    drawFilledCircle(0.4, 0.30, 0.15);
    drawFilledCircle(0.35, 0.28, 0.15);
    drawFilledCircle(0.35, 0.19, 0.13);
    drawFilledCircle(0.3, 0.15, 0.17);
    drawFilledCircle(0.05, 0.13, 0.13);//////////
    drawFilledCircle(0.2, 0.10, 0.13);
    drawFilledCircle(0.3, 0.30, 0.15);
    drawFilledCircle(0.19, 0.30, 0.13);
    drawFilledCircle(0.4, 0.35, 0.10);

    glColor3f(0.0f, 0.0f, 0.0f);// tree2
    tree();




    //text part
    texta1();
}
void autumnLeaves() {

    //leaf_green 

    glPushMatrix();
    glTranslatef(-0.4f, -0.5f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 1.0, 0.0, 0.0);
    leaf_green();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, -0.1f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    leaf_green();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13f, -0.1f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-80.0, 0.0, 0.0, 1.0);
    leaf_green();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.5f, -0.3f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    leaf_green();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.3f, -0.5f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-50.0, 0.0, 0.0, 1.0);
    leaf_green();
    glPopMatrix();



    //leaf_orange 

    glPushMatrix();
    glTranslatef(-0.5f, -0.015f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf_orange();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.3f, -0.23f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-50.0, 0.0, 0.0, 1.0);
    leaf_orange();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.13f, -0.35f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf_orange();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.35f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    leaf_orange();
    glPopMatrix();




    //leaf_yellow 

    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    leaf_yellow();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f, -0.53f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    leaf_yellow();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.6f, -0.30f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(40.0, 1.0, 0.0, 0.0);
    leaf_yellow();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.3f, -0.18f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    leaf_yellow();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, -0.1f, 0.0);
    glTranslatef(0.0f, leaf_fall_speed * currentTime, 0.0f);
    glScalef(0.2, 0.2, 1.0);
    glRotatef(-20.0, 0.0, 0.0, 1.0);
    leaf_yellow();
    glPopMatrix();

}

/////-----------------------------------///////////// 
void update(int value) {
    currentTime += 1.0f;  // Increment the current time 
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}
/////---------------------------------////////////
void together() { //all seasons together
    //WINTER
    glPushMatrix();
    glTranslatef(0.5, 0.5f, 0.0f);
    glScalef(0.5, 0.5, 1);
    winter();
    glLoadIdentity();
    glPopMatrix();
    //AUTOMN
    glPushMatrix();
    glTranslatef(-0.5, 0.5f, 0.0f);
    glScalef(0.5, 0.5, 1);
    autumnScene();
    glLoadIdentity();
    glPopMatrix();
    //SUMMER
    glPushMatrix();
    glTranslatef(-0.5, -0.5f, 0.0f);
    glScalef(0.5, 0.5, 1);
    //Beach();
    summerTree();
    glLoadIdentity();
    glPopMatrix();
    //SPRING
    glPushMatrix();
    glTranslatef(0.5, -0.5f, 0.0f);
    glScalef(0.5, 0.5, 1);
    springScene1();
    glLoadIdentity();
    glPopMatrix();
}

///////////////////////////// --- End of seasons Scenes functions --- ////////////////////////////////




void reshapeFun(GLint newWidth, GLint newHight)
{
    glViewport(0, 0, newWidth, newHight);
    win_width = newWidth;
    win_hight = newHight;
}

void init()
{
    transValueX = 0.0;
    transValueY = 0.0;
    transValueZ = 2.0;
    nearr = 0.01;
    farr = 50;
    flags = -1;
    toRain = 0;
    rainbowAp = 0;
    transValue = 1;
   

    //------- Texture ---------ـــــــــــــــــــــــــــــــــــــــ

    myTexture1 = LoadTexture(image1Path, 800, 800);


    if (myTexture1 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture1 << endl;

    glClearColor(0.70f, 0.70f, 0.70f, 1.0f); // Set background color to black and opaque

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}
////////////////

void texturee()
{




    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0, 1); glVertex3f(-1, 1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    if (flags == 1) {
        //the intro
        texturee();
        textm();
    }

    if (flags == 2) {
        //----- autumn
        // 1
        autumnTree();
        autumnLeaves();
    }
    if (flags == 3) {
        // 2
        autumnCoulds();
    }

    if (flags == 4) {
        // 3
        autumnScene();
        texta3();
    }

    if (flags == 5) {
        // ---- winter 
        // 1   
        winter();
        textw1();
    }

    if (flags == 6) {
        // 2
        rrain();
        if (toRain == 1) {
            wSRAIN();
        }
        else if (rainbowAp == 1) {
            rrain2();
        }
    }

    if (flags == 7) {
        // 3
        winterWithSun();
    }

    if (flags == 8) {
        // 4
        allSnowManWindow();
    }

    if (flags == 9) {
        // ----spring scenes
        // 1 
        springScene1();
        cloudsTrans();

        textp1();
    }
    if (flags == 10) {
        // 2 
        springMountain();
    }

    if (flags == 11) {
        // 3
        springScene2();
    }
    if (flags == 12) {
        //---summer scenes
        // 1
        summerTree();
        texts1();
    }
    if (flags == 13) {
        // 2 
        sunMoon();
    }
    if (flags == 14) {
        // 3
        Beach();
        waveTrans();
    }
    if (flags == 15) {
        texturee();
        texte2();
    }
    /*if (flags == 16) {
        together();
    }*/
    //axes();

    glFlush();
    glutSwapBuffers();
}

//no changes here

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DOUBLE);   //  Specify the display Mode – RGB, RGBA or color //  Index, single or double Buffer
    glutInitWindowSize(win_width, win_hight);       // Set the window's initial width & height
    glutInitWindowPosition(240, 0);                 // Position the window's initial top-left corner
    glutCreateWindow("The Four Seasons");           // Create a window with the given title

    // ------------------------
    //spring 
    objectX.push_back(-0.27); //-0.27, 0.21
    objectY.push_back(0.21);
    //to stop at specific point
    targetX.push_back(-0.27);
    targetY.push_back(-0.73);

    objectX.push_back(0.22); //0.22, 0.16
    objectY.push_back(0.16);
    //to stop at specific point
    targetX.push_back(0.22); wtrans = 0.0;
    wavescale = 1.0; wtrans = 0.0;
    wavescale = 1.0;
    targetY.push_back(-0.73);

    // ------------------------
    wtrans = 0.0;
    wavescale = 1.0;

    init();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);                       // Register display callback handler for window re-paint
    glutTimerFunc(10, update, 0);

    glutIdleFunc(idle);

    glutReshapeFunc(reshapeFun);

    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);


    glutMainLoop();                                  // Enter the infinitely event-processing loop
    return 0;
}
