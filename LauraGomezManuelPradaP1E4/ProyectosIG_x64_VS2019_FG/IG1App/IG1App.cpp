#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort1 = new Viewport(mWinW / 2, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	//mViewPort2 = new Viewport(mWinW / 2, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera1 = new Camera(mViewPort1);
	//mCamera2 = new Camera(mViewPort2);
	mScene1 = new Scene;
	//mScene2 = new Scene;


	mViewPort1->setPos(0, 0);
	mCamera1->set3D();
	mScene1->setScene(9);

	//mViewPort2->setPos(mWinW / 2, 0);
	//mCamera2->set2D();
	//mScene2->setScene(0);

	mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);

	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);
	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene1; mScene1 = nullptr;
	//delete mScene2; mScene2 = nullptr;
	delete mCamera1; mCamera1 = nullptr;
	//delete mCamera2; mCamera2 = nullptr;
	delete mViewPort1; mViewPort1 = nullptr;
	//delete mViewPort2; mViewPort2 = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (set2Views) {
		mScene1->render(*mCamera1);
		mScene1->render(*mCamera2);

		//display2Views();
	}
	else {

		mScene1->render(*mCamera1);  // uploads the viewport and camera to the GPU
		//mScene2->render(*mCamera2);  // uploads the viewport and camera to the GPU
	}

	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort1->setSize(newWidth , newHeight);
	//mViewPort2->setSize(newWidth / 2, newHeight);

	//mViewPort2->setPos(newWidth / 2, 0);
	// Resize Scene Visible Area such that the scale is not modified
	mCamera1->setSize(mViewPort1->width(), mViewPort1->height());
	//mCamera2->setSize(mViewPort2->width(), mViewPort2->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;
	bool isUpdateing = false;

	bool posRaton = mMouseCoord.x <= mWinW / 2;
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		//if (posRaton)
		//	mCamera1->setScale(+0.01);  // zoom in  (increases the scale)
		//else
			mCamera1->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		//if (posRaton)
		//	mCamera1->setScale(-0.01);  // zoom out (decreases the scale)
		//else
			mCamera1->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		/*if (posRaton)
			mCamera1->set3D();
		else*/
			mCamera1->set3D();
		break;
	case 'o':
		/*if (posRaton)
			mCamera1->set2D();
		else*/
			mCamera1->set2D();
		break;
	case'p':
		/*if (posRaton)
			mCamera1->changePrj();
		else*/
			mCamera1->changePrj();
		break;
	case 'f':
		mScene1->rota();
		break;
	case 'g':
		mScene1->orbita();
		break;
	case '0':
		//if (posRaton)
			mScene1->setScene(0);
		break;
	case '1':
		/*if (posRaton)
			mScene1->setScene(1);
		else*/
			mScene1->setScene(1);
		break;
	case '2':
		/*if (posRaton)
			mScene1->setScene(2);
		else*/
			mScene1->setScene(2);
		break;
	case '3':
		/*if (posRaton)
			mScene1->setScene(3);
		else*/
			mScene1->setScene(3);
		break;
	case '4':
		/*if (posRaton)
			mScene1->setScene(4);
		else*/
			mScene1->setScene(4);
		break;
	case '5':
		/*if (posRaton)
			mScene1->setScene(5);
		else*/
			mScene1->setScene(5);
		break;
	case '6':
		/*if (posRaton)
			mScene1->setScene(6);
		else*/
			mScene1->setScene(6);
		break;
	case'7':
		/*if (posRaton)
			mScene1->setScene(7);
		else*/
			mScene1->setScene(7);
		break;
	case '8':
		//if (posRaton)
			mScene1->setScene(8);
		break;
	case '9':
		/*if (posRaton)
			mScene1->setScene(9);
		else*/
			mScene1->setScene(9);
		break;
	case 'F':
		/*if (posRaton)
			mScene1->savePhoto();
		else*/
			mScene1->savePhoto();

		break;
	case 'u':
		/*if (posRaton)
			mScene1->Update();
		else*/
			mScene1->Update();
		break;
	case'U':
		activeMovement = !activeMovement;
		break;
		change2Views();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	bool posRaton = mMouseCoord.x <= mWinW / 2;
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			/*if (posRaton)
				mCamera1->pitchReal(-1);
			else*/
				mCamera1->pitchReal(-1);
		//mCamera->moveLR(-1);//Movimiento en x
		//mCamera->pitch(-1);   // rotates -1 on the X axis
		else
			/*if (posRaton)
				mCamera1->pitchReal(1);
			else*/
				mCamera1->pitchReal(1);
		//mCamera->moveLR(1);
	//mCamera->pitch(1);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			/*if (posRaton)
				mCamera1->yawReal(1);
			else*/
				mCamera1->yawReal(1);
		//mCamera->moveFB(1);//Movimiento en y
		//	mCamera->yaw(1);      // rotates 1 on the Y axis 
		else
			/*if (posRaton)
				mCamera1->yawReal(-1);
			else*/
				mCamera1->yawReal(-1);

		//mCamera->yaw(-1);     // rotate -1 on the Y axis 
		//mCamera->moveFB(-1);
		break;
	case GLUT_KEY_UP:
		//if (posRaton)
			mCamera1->rollReal(1);
		//else
			//mCamera2->rollReal(1);
		//mCamera->moveUD(1);//Movimiento en z
		//mCamera->roll(1);    // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		//if (posRaton)
			mCamera1->rollReal(-1);
		//else
		//	mCamera2->rollReal(-1);
		//mCamera->moveUD(-1);
		//mCamera->roll(-1);   // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
void IG1App::s_mouse(int button, int state, int x, int y)
{
	s_ig1app.mouse(button, state, x, y);
}
void IG1App::s_motion(int x, int y)
{
	s_ig1app.motion(x, y);
}
void IG1App::s_mouseWheel(int n, int d, int x, int y)
{
	s_ig1app.mouseWheel(n, d, x, y);
}
void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseButt = button;
	mMouseCoord = dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}
void IG1App::motion(int x, int y)
{
	bool posRaton = mMouseCoord.x <= mWinW / 2;
	dvec2 mp = mMouseCoord - dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mMouseCoord = dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	if (mMouseButt == GLUT_LEFT_BUTTON) {
		//if (posRaton)
			mCamera1->orbit(mp.x * 0.05, mp.y);
		//else
		//	mCamera2->orbit(mp.x * 0.05, mp.y);
	}
	else {
		//if (posRaton) {
			mCamera1->moveUD(mp.y);
			mCamera1->moveLR(mp.x);
		//}
		/*else {
			mCamera2->moveUD(mp.y);
			mCamera2->moveLR(mp.x);
		}*/
	}
	glutPostRedisplay();
}
void IG1App::mouseWheel(int wheelButtonNumber, int direction, int x, int y)
{
	bool posRaton = x <= mWinW / 2;
	int tics = glutGetModifiers();
	if (tics == GLUT_ACTIVE_CTRL) {
		//if (posRaton)
			mCamera1->setScale(direction * 0.05);
		/*else
			mCamera2->setScale(direction * 0.05);*/
	}
	else {
		//if (posRaton)
			mCamera1->moveFB(direction);
		/*else
			mCamera2->moveFB(direction);*/
	}
	glutPostRedisplay();
}
void IG1App::update()
{

	if (glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime >= 30 && activeMovement)
	{
		mScene1->Update();
		//mScene2->Update();
		//mCamera1->update();
		mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
		//mLastUpdateTime = 0;
		glutPostRedisplay();
	}
}
void IG1App::display2Views()const
{

	Camera auxCam = *mCamera1;

	Viewport auxVP = *mViewPort1;

	mViewPort1->setSize(mWinW / 2, mWinH);

	auxCam.setSize(mViewPort1->width(), mViewPort1->height());

	//Escena 3d
	mViewPort1->setPos(0, 0);
	auxCam.set3D();
	mScene1->render(auxCam);

	//Escena cenital
	mViewPort1->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene1->render(auxCam);

	*mViewPort1 = auxVP;
}
void IG1App::change2Views()
{
	set2Views = !set2Views;
	if (set2Views) {
		mCamera2->setCenital();
	}
	else {
		mCamera2->set2D();
	}
}
//-------------------------------------------------------------------------

