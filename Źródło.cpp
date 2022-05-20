////
/////**
//// * CPSC 424, Fall 2015, Lab 6:  Light and Material in OpenGL 1.1.
//// * This program shows a square "stage" with a variety of objects
//// * arranged on it.  The objects use several shapes and materials
//// * and include a wireframe object that is drawn with lighting
//// * turned off.  The user can rotate the scene about the y-axis by
//// * dragging the mouse horizontally.
//// *
//// * This program use GLU as well as GLUT, and it depends on polyhedron.c,
//// * which requires the math library.  It can be compiled with
//// *
//// *        gcc -o lab6 lab6.c polyhedron.c -lGL -lglut -lGLU -lm
//// */
////
//#include <windows.h>
//#include <GL/gl.h>
//#include <GL/freeglut.h>
//#include <stdio.h>      // (Can be used for debugging messages, with printf().)
//#include "polyhedron.h" // For access to the regular polyhedra from polyhedron.c.
//
//
//static double rotateY;  // rotation amount about the y-axis
//
//// --------------------------- Data for some materials ---------------------------------------------------
//
///**
// * One of the rows of this array corresponds to a set of material properties.  Items 0 to 4 in a row
// * specify an ambient color; items 4 through 7, a diffuse color; items 8 through 11, a specular color;
// * and item 12, a specular exponent (shininess value).  The data is adapted from the table on the page
// * http://devernay.free.fr/cours/opengl/materials.html
// */
//float materials[][13] = {
//    { /* "emerald" */   0.0215f, 0.1745f, 0.0215f, 1.0f, 0.07568f, 0.61424f, 0.07568f, 1.0f, 0.633f, 0.727811f, 0.633f, 1.0f, 0.6f * 128 },
//    { /* "jade" */   0.135f, 0.2225f, 0.1575f, 1.0f, 0.54f, 0.89f, 0.63f, 1.0f, 0.316228f, 0.316228f, 0.316228f, 1.0f, 0.1f * 128 },
//    { /* "obsidian" */   0.05375f, 0.05f, 0.06625f, 1.0f, 0.18275f, 0.17f, 0.22525f, 1.0f, 0.332741f, 0.328634f, 0.346435f, 1.0f, 0.3f * 128 },
//    { /* "pearl" */   0.25f, 0.20725f, 0.20725f, 1.0f, 1.0f, 0.829f, 0.829f, 1.0f, 0.296648f, 0.296648f, 0.296648f, 1.0f, 0.088f * 128 },
//    { /* "ruby" */   0.1745f, 0.01175f, 0.01175f, 1.0f, 0.61424f, 0.04136f, 0.04136f, 1.0f, 0.727811f, 0.626959f, 0.626959f, 1.0f, 0.6f * 128 },
//    { /* "turquoise" */   0.1f, 0.18725f, 0.1745f, 1.0f, 0.396f, 0.74151f, 0.69102f, 1.0f, 0.297254f, 0.30829f, 0.306678f, 1.0f, 0.1f * 128 },
//    { /* "brass" */   0.329412f, 0.223529f, 0.027451f, 1.0f, 0.780392f, 0.568627f, 0.113725f, 1.0f, 0.992157f, 0.941176f, 0.807843f, 1.0f, 0.21794872f * 128 },
//    { /* "bronze" */   0.2125f, 0.1275f, 0.054f, 1.0f, 0.714f, 0.4284f, 0.18144f, 1.0f, 0.393548f, 0.271906f, 0.166721f, 1.0f, 0.2f * 128 },
//    { /* "chrome" */   0.25f, 0.25f, 0.25f, 1.0f, 0.4f, 0.4f, 0.4f, 1.0f, 0.774597f, 0.774597f, 0.774597f, 1.0f, 0.6f * 128 },
//    { /* "copper" */   0.19125f, 0.0735f, 0.0225f, 1.0f, 0.7038f, 0.27048f, 0.0828f, 1.0f, 0.256777f, 0.137622f, 0.086014f, 1.0f, 0.1f * 128 },
//    { /* "gold" */   0.24725f, 0.1995f, 0.0745f, 1.0f, 0.75164f, 0.60648f, 0.22648f, 1.0f, 0.628281f, 0.555802f, 0.366065f, 1.0f, 0.4f * 128 },
//    { /* "silver" */   0.19225f, 0.19225f, 0.19225f, 1.0f, 0.50754f, 0.50754f, 0.50754f, 1.0f, 0.508273f, 0.508273f, 0.508273f, 1.0f, 0.4f * 128 },
//    { /* "cyan plastic" */   0.0f, 0.1f, 0.06f, 1.0f, 0.0f, 0.50980392f, 0.50980392f, 1.0f, 0.50196078f, 0.50196078f, 0.50196078f, 1.0f, .25f * 128 },
//    { /* "green plastic" */   0.0f, 0.0f, 0.0f, 1.0f, 0.1f, 0.35f, 0.1f, 1.0f, 0.45f, 0.55f, 0.45f, 1.0f, .25f * 128 },
//    { /* "red plastic" */   0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.7f, 0.6f, 0.6f, 1.0f, .25f * 128 },
//    { /* "cyan rubber" */   0.0f, 0.05f, 0.05f, 1.0f, 0.4f, 0.5f, 0.5f, 1.0f, 0.04f, 0.7f, 0.7f, 1.0f, .078125f * 128 },
//    { /* "green rubber" */   0.0f, 0.05f, 0.0f, 1.0f, 0.4f, 0.5f, 0.4f, 1.0f, 0.04f, 0.7f, 0.04f, 1.0f, .078125f * 128 },
//    { /* "red rubber" */   0.05f, 0.0f, 0.0f, 1.0f, 0.5f, 0.4f, 0.4f, 1.0f, 0.7f, 0.04f, 0.04f, 1.0f, .078125f * 128 },
//};
//
//
//// ------------------------ OpenGL rendering and  initialization -----------------------
//
///**
// * The display method is called when the panel needs to be drawn.
// * Here, it draws a stage and some objects on the stage.
// */
//void display() {
//    // called whenever the display needs to be redrawn
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    gluLookAt(0, 8, 40, 0, 1, 0, 0, 1, 0);  // viewing transform	
//
//    glRotated(rotateY, 0, 1, 0);  // modeling transform: rotation of the scene about y-axis
//
//    float gray[] = { 0.6f, 0.6f, 0.6f, 1 };
//    float zero[] = { 0, 0, 0, 1 };
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
//    glPushMatrix();
//    glTranslatef(0, -1.5, 0); // Move top of stage down to y = 0
//    glScalef(1, 0.05, 1); // Stage will be one unit thick,
//    glutSolidCube(20);
//    glPopMatrix();
//
//    // TODO draw some shapes!
//
//
//    glutSwapBuffers();  // (Required for double-buffered drawing, at the end of display().)
//}
//
///**
// * initGL() is called just once, by main(), to do initialization of OpenGL state
// * and other global state. Here, it sets up a projection, configures some lighting,
// * and enables the depth test.  It also calls createPolyhedra(), whcih is defined
// * in the included file, polyhedron.h.
// */
//void initGL() {
//    createPolyhedra();
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(20, 2, 1, 100);
//    glMatrixMode(GL_MODELVIEW);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    // TODO configure better lighting!
//}  // end initGL()
//
//
//// ------------------------------ mouse handling functions ----------------------------------
//
//int dragging;        // 0 or 1 to indicate whether a drag operation is in progress
//int dragButton;      // which button started the drag operation
//int prevX;           // previous mouse x coordinate during drag
//
///*  mouseUpOrDown() is set up in main() to be called when the user presses or releases
// *  a button on the mouse.  The button paramter is one of the contants GLUT_LEFT_BUTTON,
// *  GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.  The buttonState is GLUT_UP or GLUT_DOWN and
// *  tells whether this is a mouse press or a mouse release event.  x and y give the
// *  mouse position in pixel coordinates, with (0,0) at the UPPER LEFT.
// */
//void mouseUpOrDown(int button, int buttonState, int x, int y) {
//    // called to respond to mouse press and mouse release events
//    if (buttonState == GLUT_DOWN) {  // a mouse button was pressed
//        if (dragging)
//            return;  // Ignore a second button press during a draw operation.
//        dragging = 1;
//        dragButton = button;
//        prevX = x;
//    }
//    else {  // a mouse button was released
//        if (!dragging || button != dragButton)
//            return; // this mouse release does not end a drag operation.
//        dragging = 0;
//    }
//}
//
///*  mouseDragged() is set up in main() to be called when the user moves the mouse,
// *  but only when one or more mouse buttons are pressed.  x and y give the position
// *  of the mouse in pixel coordinates.
// */
//void mouseDragged(int x, int y) {
//    // called to respond when the mouse moves during a drag
//    if (!dragging)
//        return;
//    double dx = x - prevX;
//    rotateY += dx / 7;
//    glutPostRedisplay();  // make OpenGL redraw the scene
//    prevX = x;
//}
//
//
//// ----------------- main routine -------------------------------------------------
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Allows processing of certain GLUT command line options
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  // Use double buffering and a depth buffer.
//    glutInitWindowSize(1000, 500);       // size of display area, in pixels
//    glutInitWindowPosition(100, 100);    // location in window coordinates
//    glutCreateWindow("Stage");          // parameter is window title  
//    initGL();                           // do OpenGL initialization for the window
//    glutDisplayFunc(display);           // call display() to draw the scene
//    glutMouseFunc(mouseUpOrDown);       // call mouseUpOrDown() for mousedown and mouseup events
//    glutMotionFunc(mouseDragged);       // call mouseDragged() when mouse moves, only during a drag gesture
//    glutMainLoop(); // Run the event loop!  This function does not return.
//    return 0;
//}



///*
// * CPSC 424, Fall 2015, Lab 4:  Some objects in 3D.  The arrow keys
// * can be used to rotate the object.  The number keys 1 through 5
// * select the object.  The space bar toggles the use of anaglyph
// * stereo.  Compile this program with:
// *
// *           gcc -o lab4 lab4.c -lGL -lglut
// */
//
#define  _USE_MATH_DEFINES
#include <windows.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <cmath>

#include "polyhedron.h"
////
////
////
//////void display();
//////void init()
//////{
//////    glClearColor(1.0,1.0,0.0,1.0);
//////}
//////
//////int main(int argc, char ** argv)
//////{
//////    glutInit(&argc,argv);
//////    glutInitDisplayMode(GLUT_RGB);
//////
//////    glutInitWindowPosition(200,100);
//////    glutInitWindowSize(500,500);
//////
//////    
//////
//////    glutCreateWindow("Window 1");
//////
//////    glutDisplayFunc(display);
//////    init();
//////
//////    glutMainLoop();
//////    
//////}
//////
//////void display()
//////{
//////    glClear(GL_COLOR_BUFFER_BIT);
//////    glLoadIdentity();
//////
//////
//////
//////
//////    glFlush();
//////}
////
////
////
//// //-------------------Data for stellated dodecahedron ------------------
////
//double dodecVertices[][3] = {
//    {-0.650000,0.000000,-0.248278},
//    {0.401722,0.401722,0.401722},            // This array contains the coordinates
//    {0.650000,0.000000,0.248278},            // for the vertices of the polyhedron
//    {0.401722,-0.401722,0.401722},           // known as a stellated dodecahedron
//    {0.000000,-0.248278,0.650000},
//    {0.000000,0.248278,0.650000},            // Each row of the 2D array contains
//    {0.650000,0.000000,-0.248278},           // the xyz-coordinates for one of
//    {0.401722,0.401722,-0.401722},           // the vertices.
//    {0.248278,0.650000,0.000000},
//    {-0.248278,0.650000,0.000000},
//    {-0.401722,0.401722,-0.401722},
//    {0.000000,0.248278,-0.650000},
//    {0.401722,-0.401722,-0.401722},
//    {0.248278,-0.650000,0.000000},
//    {-0.248278,-0.650000,0.000000},
//    {-0.650000,0.000000,0.248278},
//    {-0.401722,0.401722,0.401722},
//    {-0.401722,-0.401722,-0.401722},
//    {0.000000,-0.248278,-0.650000},
//    {-0.401722,-0.401722,0.401722},
//    {0.000000,1.051722,0.650000},
//    {-0.000000,1.051722,-0.650000},
//    {1.051722,0.650000,-0.000000},
//    {1.051722,-0.650000,-0.000000},
//    {-0.000000,-1.051722,-0.650000},
//    {-0.000000,-1.051722,0.650000},
//    {0.650000,0.000000,1.051722},
//    {-0.650000,0.000000,1.051722},
//    {0.650000,-0.000000,-1.051722},
//    {-0.650000,0.000000,-1.051722},
//    {-1.051722,0.650000,-0.000000},
//    {-1.051722,-0.650000,0.000000}
//};
//
//int dodecTriangles[][3] = {
//   {16,9,20},
//   {9,8,20},
//   {8,1,20},              // This array specifies the faces of
//   {1,5,20},              // the stellated dodecahedron.
//   {5,16,20},
//   {9,10,21},             // Each row in the 2D array is a list
//   {10,11,21},            // of three integers.  The integers
//   {11,7,21},             // are indices into the vertex array,
//   {7,8,21},              // dodecVertices.  The vertices at
//   {8,9,21},              // at those indices are the vertices
//   {8,7,22},              // of one of the triangular faces of
//   {7,6,22},              // the polyhedron.
//   {6,2,22},
//   {2,1,22},              // For example, the first row, {16,9,20},
//   {1,8,22},              // means that vertices number 16, 9, and
//   {6,12,23},             // 20 are the vertices of a face.
//   {12,13,23},
//   {13,3,23},             // There are 60 faces.
//   {3,2,23},
//   {2,6,23},
//   {18,17,24},
//   {17,14,24},
//   {14,13,24},
//   {13,12,24},
//   {12,18,24},
//   {14,19,25},
//   {19,4,25},
//   {4,3,25},
//   {3,13,25},
//   {13,14,25},
//   {4,5,26},
//   {5,1,26},
//   {1,2,26},
//   {2,3,26},
//   {3,4,26},
//   {15,16,27},
//   {16,5,27},
//   {5,4,27},
//   {4,19,27},
//   {19,15,27},
//   {7,11,28},
//   {11,18,28},
//   {18,12,28},
//   {12,6,28},
//   {6,7,28},
//   {10,0,29},
//   {0,17,29},
//   {17,18,29},
//   {18,11,29},
//   {11,10,29},
//   {0,10,30},
//   {10,9,30},
//   {9,16,30},
//   {16,15,30},
//   {15,0,30},
//   {17,0,31},
//   {0,15,31},
//   {15,19,31},
//   {19,14,31},
//   {14,17,31}
//};
//
//
//
////------------------- TODO: Complete this section! ---------------------
//
//int objectNumber;        // Which object to draw (1 ,2, 3, 4, 5, or 6)?
//                                     //   (Controlled by number keys.)
//
//int useAnaglyph = 0; // Should anaglyph stereo be used?
//                             //    (Controlled by space bar.)
//
//int rotateX = 0;    // Rotations of the cube about the axes.
//int rotateY = 0;    //   (Controlled by arrow, PageUp, PageDown keys;
//int rotateZ = 0;    //    Home key sets all rotations to 0.)
//
//
///*
// * The function that draws the current object, with its modeling transformation.
//
//
//
// */
//
//void triangle(float r,float g, float b) {
//
//    glBegin(GL_TRIANGLES);          
//          
//    glColor3f(r, g, b);     
//    glVertex3f(0.0f, 4.0f, 0.0f);
//    glColor3f(r, g, b);     
//    glVertex3f(-1.15f, -2.0f, 2.0f);
//    glColor3f(r, g, b);     
//    glVertex3f(1.15f, -2.0f, 2.0f);
//
//
//    glEnd();
//}
//
//
//void draw() {
//
//    glRotatef(rotateZ, 0, 0, 1);   // Apply rotations to complete object.
//    glRotatef(rotateY, 0, 1, 0);
//    glRotatef(rotateX, 1, 0, 0);
//
//    // TODO: Draw the currently selected object, number 1, 2, 3, 4, or 5.
//    // (Objects should lie in the cube with x, y, and z coordinates in the
//    // range -5 to 5.)
//    if (objectNumber == 1)
//    {
//        float radius = 0.0f;
//        float x;
//        float y;
//        float z;
//        GLfloat sizes[2];
//        float curSize;
//        float step;
//
//        glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
//        glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
//        curSize = sizes[0];
//        glColor3f(1.0, 0.0, 0.0);
//        glBegin(0);
//        for (float angle = 0; angle < 2160; angle += 1)
//        {
//            glPointSize(curSize);
//            x = 0.04 * cos(angle * M_PI / 180) * radius;
//            y = 0.1 * radius - 5;
//            z = 0.04 * sin(angle * M_PI / 180) * radius;
//            radius += 0.05f;
//            glVertex3f(x, y, z);
//            curSize += step;
//
//        }
//        glEnd();
//    }
//
//    else if (objectNumber == 2)
//    {
//
//     
//        glPushMatrix();
//        glScalef(1,1,1);
//        triangle(1,0,0);
//        
//        glPushMatrix();
//        glRotatef(60,0,1,0);
//        triangle(0,1,0);  
//
//        glPushMatrix();
//        glRotatef(60, 0, 1, 0);
//        triangle(1, 0, 0);
//
//        glPushMatrix();
//        glRotatef(60, 0, 1, 0);
//        triangle(0, 1, 0);
//
//        glPushMatrix();
//        glRotatef(60, 0, 1, 0);
//        triangle(1, 0, 0);
//
//        glPushMatrix();
//        glRotatef(60, 0, 1, 0);
//        triangle(1, 0, 0);
//
//
//
//        
//
//    }
//
//}
//
////-------------------- Draw the Scene  -------------------------
//
///*
// * The display function is called when the window needs to be drawn.
// * It's called when the window opens and it is called by the keyboard-handling
// * functions when the user hits a key that modifies the scene.
// */
//void display() {  // Display function will draw the image.
//
//    if (useAnaglyph) {
//        glDisable(GL_COLOR_MATERIAL); // in anaglyph mode, everything is drawn in white
//        float white[] = { 1,1,1,1 };
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
//    }
//    else {
//        glEnable(GL_COLOR_MATERIAL);  // in non-anaglyph mode, glColor* is respected
//    }
//    glNormal3f(0, 0, 1); // (Make sure normal vector is correct for object 1.)
//
//    glClearColor(0, 0, 0, 1); // Background color (black).
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    if (!useAnaglyph) {
//        glLoadIdentity(); // Make sure we start with no transformation!
//        glTranslated(0, 0, -15);  // Move object away from viewer (at (0,0,0)).
//        draw();
//    }
//    else {
//        glLoadIdentity();
//        glColorMask(1, 0, 0, 1);
//        glRotatef(4, 0, 1, 0);
//        glTranslated(1, 0, -15);
//        draw();
//        glColorMask(1, 0, 0, 1);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glLoadIdentity();
//        glRotatef(-4, 0, 1, 0);
//        glTranslated(-1, 0, -15);
//        glColorMask(0, 1, 1, 1);
//        draw();
//        glColorMask(1, 1, 1, 1);
//    }
//
//    glutSwapBuffers(); // Required AT THE END to copy color buffer onto the screen.
//
//} // end display()
//
//
///*  The initGL function is called once from main() to initialize
// *  OpenGL.  Here, it sets up a projection, turns on some lighting,
// *  and enables the depth test.
// */
//void initGL() {
//    glMatrixMode(GL_PROJECTION);
//    glFrustum(-3.5, 3.5, -3.5, 3.5, 5, 25);
//    glMatrixMode(GL_MODELVIEW);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    float gray[] = { 0.7,0.7,0.7,1 };
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, gray);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
//    glEnable(GL_DEPTH_TEST);
//    glLineWidth(3);  // make wide lines for the stellated dodecahedron.
//}
//
////-------------------- Key-handling functions ---------------------------
//
//void doSpecialKey(int key, int x, int y) {
//    // called when a special key is pressed
//    int redraw = 1;
//    if (key == GLUT_KEY_LEFT)
//        rotateY -= 15;
//    else if (key == GLUT_KEY_RIGHT)
//        rotateY += 15;
//    else if (key == GLUT_KEY_DOWN)
//        rotateX += 15;
//    else if (key == GLUT_KEY_UP)
//        rotateX -= 15;
//    else if (key == GLUT_KEY_PAGE_UP)
//        rotateZ += 15;
//    else if (key == GLUT_KEY_PAGE_DOWN)
//        rotateZ -= 15;
//    else if (key == GLUT_KEY_HOME)
//        rotateX = rotateY = rotateZ = 0;
//    else
//        redraw = 0;
//    if (redraw)
//        glutPostRedisplay(); // will repaint the window
//}
//
//void doKeyboard(unsigned char ch, int x, int y) {
//    int redraw = 1;
//    if (ch == '1')
//        objectNumber = 1;
//    else if (ch == '2')
//        objectNumber = 2;
//    else if (ch == '3')
//        objectNumber = 3;
//    else if (ch == '4')
//        objectNumber = 4;
//    else if (ch == '5')
//        objectNumber = 5;
//    else if (ch == '6')
//        objectNumber = 6;
//    else if (ch == ' ')
//        useAnaglyph = !useAnaglyph;
//    else
//        redraw = 0;
//    if (redraw)
//        glutPostRedisplay(); // will repaint the window
//}
//
//
//// --------------------------- main() -------------------------------------
//
//int main(int argc, char** argv) {  // Initialize GLUT and open the window
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  // Use double-buffering and depth buffer.
//    glutInitWindowSize(700, 700);            // Size of display area, in pixels.
//    glutInitWindowPosition(100, 100);        // Location of window in screen coordinates.
//    glutCreateWindow("Some Objects in 3D"); // Parameter is window title.
//    initGL();   // Call the OpenGL initialization function, defined above; must be after glutCreateWindow.
//    glutDisplayFunc(display);               // display() is called when the window needs to be redrawn.
//    glutKeyboardFunc(doKeyboard);           // doKeyboard() is called to process normal keys.
//    glutSpecialFunc(doSpecialKey);          // doSpecialKey() is called to process other keys (such as arrows).
//    glutMainLoop();
//    return 0;
//}
//
//
//
//
//
//
//
//
//




//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1LAB6
















/**
 * CPSC 424, Fall 2015, Lab 6:  Light and Material in OpenGL 1.1.
 * This program shows a square "stage" with a variety of objects
 * arranged on it.  The objects use several shapes and materials
 * and include a wireframe object that is drawn with lighting
 * turned off.  The user can rotate the scene about the y-axis by
 * dragging the mouse horizontally.
 *
 * This program use GLU as well as GLUT, and it depends on polyhedron.c,
 * which requires the math library.  It can be compiled with
 *
 *        gcc -o lab6 lab6.c polyhedron.c -lGL -lglut -lGLU -lm
 */

      //(Can be used for debugging messages, with printf().)
//#include "polyhedron.h" // For access to the regular polyhedra from polyhedron.c.


static double rotateY;  // rotation amount about the y-axis

// --------------------------- Data for some materials ---------------------------------------------------

/**
 * One of the rows of this array corresponds to a set of material properties.  Items 0 to 4 in a row
 * specify an ambient color; items 4 through 7, a diffuse color; items 8 through 11, a specular color;
 * and item 12, a specular exponent (shininess value).  The data is adapted from the table on the page
 * http://devernay.free.fr/cours/opengl/materials.html
 */
float materials[][13] = {
    { /* "emerald" */   0.0215f, 0.1745f, 0.0215f, 1.0f, 0.07568f, 0.61424f, 0.07568f, 1.0f, 0.633f, 0.727811f, 0.633f, 1.0f, 0.6f * 128 },
    { /* "jade" */   0.135f, 0.2225f, 0.1575f, 1.0f, 0.54f, 0.89f, 0.63f, 1.0f, 0.316228f, 0.316228f, 0.316228f, 1.0f, 0.1f * 128 },
    { /* "obsidian" */   0.05375f, 0.05f, 0.06625f, 1.0f, 0.18275f, 0.17f, 0.22525f, 1.0f, 0.332741f, 0.328634f, 0.346435f, 1.0f, 0.3f * 128 },
    { /* "pearl" */   0.25f, 0.20725f, 0.20725f, 1.0f, 1.0f, 0.829f, 0.829f, 1.0f, 0.296648f, 0.296648f, 0.296648f, 1.0f, 0.088f * 128 },
    { /* "ruby" */   0.1745f, 0.01175f, 0.01175f, 1.0f, 0.61424f, 0.04136f, 0.04136f, 1.0f, 0.727811f, 0.626959f, 0.626959f, 1.0f, 0.6f * 128 },
    { /* "turquoise" */   0.1f, 0.18725f, 0.1745f, 1.0f, 0.396f, 0.74151f, 0.69102f, 1.0f, 0.297254f, 0.30829f, 0.306678f, 1.0f, 0.1f * 128 },
    { /* "brass" */   0.329412f, 0.223529f, 0.027451f, 1.0f, 0.780392f, 0.568627f, 0.113725f, 1.0f, 0.992157f, 0.941176f, 0.807843f, 1.0f, 0.21794872f * 128 },
    { /* "bronze" */   0.2125f, 0.1275f, 0.054f, 1.0f, 0.714f, 0.4284f, 0.18144f, 1.0f, 0.393548f, 0.271906f, 0.166721f, 1.0f, 0.2f * 128 },
    { /* "chrome" */   0.25f, 0.25f, 0.25f, 1.0f, 0.4f, 0.4f, 0.4f, 1.0f, 0.774597f, 0.774597f, 0.774597f, 1.0f, 0.6f * 128 },
    { /* "copper" */   0.19125f, 0.0735f, 0.0225f, 1.0f, 0.7038f, 0.27048f, 0.0828f, 1.0f, 0.256777f, 0.137622f, 0.086014f, 1.0f, 0.1f * 128 },
    { /* "gold" */   0.24725f, 0.1995f, 0.0745f, 1.0f, 0.75164f, 0.60648f, 0.22648f, 1.0f, 0.628281f, 0.555802f, 0.366065f, 1.0f, 0.4f * 128 },
    { /* "silver" */   0.19225f, 0.19225f, 0.19225f, 1.0f, 0.50754f, 0.50754f, 0.50754f, 1.0f, 0.508273f, 0.508273f, 0.508273f, 1.0f, 0.4f * 128 },
    { /* "cyan plastic" */   0.0f, 0.1f, 0.06f, 1.0f, 0.0f, 0.50980392f, 0.50980392f, 1.0f, 0.50196078f, 0.50196078f, 0.50196078f, 1.0f, .25f * 128 },
    { /* "green plastic" */   0.0f, 0.0f, 0.0f, 1.0f, 0.1f, 0.35f, 0.1f, 1.0f, 0.45f, 0.55f, 0.45f, 1.0f, .25f * 128 },
    { /* "red plastic" */   0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.7f, 0.6f, 0.6f, 1.0f, .25f * 128 },
    { /* "cyan rubber" */   0.0f, 0.05f, 0.05f, 1.0f, 0.4f, 0.5f, 0.5f, 1.0f, 0.04f, 0.7f, 0.7f, 1.0f, .078125f * 128 },
    { /* "green rubber" */   0.0f, 0.05f, 0.0f, 1.0f, 0.4f, 0.5f, 0.4f, 1.0f, 0.04f, 0.7f, 0.04f, 1.0f, .078125f * 128 },
    { /* "red rubber" */   0.05f, 0.0f, 0.0f, 1.0f, 0.5f, 0.4f, 0.4f, 1.0f, 0.7f, 0.04f, 0.04f, 1.0f, .078125f * 128 },
};


// ------------------------ OpenGL rendering and  initialization -----------------------

/**
 * The display method is called when the panel needs to be drawn.
 * Here, it draws a stage and some objects on the stage.
 */

void triangle(float r, float g, float b) {

    glBegin(GL_TRIANGLES);

    glColor3f(r, g, b);
    glVertex3f(0.0f, 4.0f, 0.0f);
    glColor3f(r, g, b);
    glVertex3f(-1.15f, -2.0f, 2.0f);
    glColor3f(r, g, b);
    glVertex3f(1.15f, -2.0f, 2.0f);


    glEnd();
}

//int rotateX = 0;    // Rotations of the cube about the axes.
//int rotateY = 0;    //   (Controlled by arrow, PageUp, PageDown keys;
//int rotateZ = 0;   

void display() {

  
    // called whenever the display needs to be redrawn

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 8, 40, 0, 1, 0, 0, 1, 0);  // viewing transform	

    // modeling transform: rotation of the scene about y-axis
    glRotated(rotateY, 0, 0.5, 0);
    float gray[] = { 0.6f, 0.6f, 0.6f, 1 };
    float zero[] = { 0, 0, 0, 1 };

    float gold[13] = { 0.24725, 0.1995, 0.0745, 1.0,
0.75164, 0.60648, 0.22648, 1.0,
0.628281, 0.555802, 0.366065, 1.0,
50.0
    };


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &gold[4]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &gold[8]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold[12]);

    /*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);*/
    glPushMatrix();
    glTranslatef(0, -1.5, 0); // Move top of stage down to y = 0
    glScalef(1, 0.05, 1); // Stage will be one unit thick,
    glutSolidCube(20);
    glPopMatrix();
    glPushMatrix();
   

    glRotated(rotateY, 0, 0.5, 0);
  
            glPushMatrix();
            glScalef(1,1,1);
            triangle(1,0,0);
            
            glPushMatrix();
            glRotatef(60,0,1,0);
            triangle(0,1,0);  
    
            glPushMatrix();
            glRotatef(60, 0, 1, 0);
            triangle(1, 0, 0);
    
            glPushMatrix();
            glRotatef(60, 0, 1, 0);
            triangle(0, 1, 0);
    
            glPushMatrix();
            glRotatef(60, 0, 1, 0);
            triangle(1, 0, 0);
    
            glPushMatrix();
            glRotatef(60, 0, 1, 0);
            triangle(1, 0, 0);
         

    glutSwapBuffers();  // (Required for double-buffered drawing, at the end of display().)
}

/**
 * initGL() is called just once, by main(), to do initialization of OpenGL state
 * and other global state. Here, it sets up a projection, configures some lighting,
 * and enables the depth test.  It also calls createPolyhedra(), whcih is defined
 * in the included file, polyhedron.h.
 */
void initGL() {
    //createPolyhedra();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, 2, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    

      glEnable(GL_LIGHTING);

      glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
      float ambientLevel[] = { 0.15, 0.15, 0.15, 1 };
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLevel);

    
      float blue1[4] = { 0.4, 0.4, 0.6, 1 };
      float blue2[4] = { 0.0, 0, 0.8, 1 };
      float blue3[4] = { 0.0, 0, 0.15, 1 };
      glLightfv(GL_LIGHT1, GL_DIFFUSE, blue1);
      glLightfv(GL_LIGHT1, GL_SPECULAR, blue2);
      glLightfv(GL_LIGHT1, GL_AMBIENT, blue3);
      glEnable(GL_LIGHT1);

      float blue11[4] = { 0.4, 0.4, 0.6, 1 };
      float blue21[4] = { 10.0, 0, 0.8, 1 };
      float blue31[4] = { 0.0, 0, 0.15, 1 };
      glLightfv(GL_LIGHT4, GL_SHININESS, blue11);
      glLightfv(GL_LIGHT4, GL_SPECULAR, blue21);
      glLightfv(GL_LIGHT4, GL_AMBIENT, blue31);
      glEnable(GL_LIGHT4);


      float blue111[4] = { 0.4, 0.4, 0.6, 1 };
      float blue211[4] = { 10.0, 0, 0.8, 1 };
      float blue311[4] = { 0.0, 0, 0.15, 1 };
      glLightfv(GL_LIGHT7, GL_SHININESS, blue111);
      glLightfv(GL_LIGHT7, GL_SPECULAR, blue211);
      glLightfv(GL_LIGHT7, GL_AMBIENT, blue311);
      glEnable(GL_LIGHT7);


    


    
    // TODO configure better lighting!
}  // end initGL()


// ------------------------------ mouse handling functions ----------------------------------

int dragging;        // 0 or 1 to indicate whether a drag operation is in progress
int dragButton;      // which button started the drag operation
int prevX;           // previous mouse x coordinate during drag

/*  mouseUpOrDown() is set up in main() to be called when the user presses or releases
 *  a button on the mouse.  The button paramter is one of the contants GLUT_LEFT_BUTTON,
 *  GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.  The buttonState is GLUT_UP or GLUT_DOWN and
 *  tells whether this is a mouse press or a mouse release event.  x and y give the
 *  mouse position in pixel coordinates, with (0,0) at the UPPER LEFT.
 */
void mouseUpOrDown(int button, int buttonState, int x, int y) {
    // called to respond to mouse press and mouse release events
    if (buttonState == GLUT_DOWN) {  // a mouse button was pressed
        if (dragging)
            return;  // Ignore a second button press during a draw operation.
        dragging = 1;
        dragButton = button;
        prevX = x;
    }
    else {  // a mouse button was released
        if (!dragging || button != dragButton)
            return; // this mouse release does not end a drag operation.
        dragging = 0;
    }
}

/*  mouseDragged() is set up in main() to be called when the user moves the mouse,
 *  but only when one or more mouse buttons are pressed.  x and y give the position
 *  of the mouse in pixel coordinates.
 */
void mouseDragged(int x, int y) {
    // called to respond when the mouse moves during a drag
    if (!dragging)
        return;
    double dx = x - prevX;
    rotateY += dx / 7;
    glutPostRedisplay();  // make OpenGL redraw the scene
    prevX = x;
}


// ----------------- main routine -------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Allows processing of certain GLUT command line options
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  // Use double buffering and a depth buffer.
    glutInitWindowSize(1000, 500);       // size of display area, in pixels
    glutInitWindowPosition(100, 100);    // location in window coordinates
    glutCreateWindow("Stage");          // parameter is window title  
    initGL();                           // do OpenGL initialization for the window
    glutDisplayFunc(display);           // call display() to draw the scene
    glutMouseFunc(mouseUpOrDown);       // call mouseUpOrDown() for mousedown and mouseup events
    glutMotionFunc(mouseDragged);       // call mouseDragged() when mouse moves, only during a drag gesture
    glutMainLoop(); // Run the event loop!  This function does not return.
    return 0;
}




