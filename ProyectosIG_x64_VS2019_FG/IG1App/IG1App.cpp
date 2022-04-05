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
	mViewPort3 = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera3 = new Camera(mViewPort3);
	mCamera3->set2D();

	mViewPort2 = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera2 = new Camera(mViewPort2);

	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mCamera->set2D();

	mScene = new Scene;
	mScene->init();
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
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mCamera2; mCamera2 = nullptr;
	delete mCamera3; mCamera3 = nullptr;
	delete mViewPort; mViewPort = nullptr;
	delete mViewPort2; mViewPort2 = nullptr;
	delete mViewPort3; mViewPort3 = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const   
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (m2Vistas)
	{
		Camera mCamera2 = *mCamera;
		Camera mCamera3 = *mCamera;
		Viewport mViewPort2 = *mViewPort;
		Viewport mViewPort3 = *mViewPort;

		mViewPort2.setSize(mWinW / 2, mWinH);
		mViewPort3.setSize(mWinW / 2, mWinH);

		mCamera2.setSize(mViewPort->width(), mViewPort->height());
		mCamera3.setSize(mViewPort->width(), mViewPort->height());

		*mViewPort = mViewPort3;

		mViewPort->setPos(0, 0);
		mScene->render(mCamera3);

		*mViewPort = mViewPort2;

		mViewPort->setPos(mWinW/2, 0);
		mCamera2.setCenital();
		mScene->render(mCamera2);
	}
	else
	{
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW, mWinH);
		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	}
	
	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort3->setSize(newWidth / 2, newHeight);
	mViewPort2->setSize(newWidth / 2, newHeight);
	mViewPort2->setPos(newWidth / 2, 0);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera3->setSize(mViewPort3->width(), mViewPort3->height());
	mCamera2->setSize(mViewPort2->width(), mViewPort2->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		updating = !updating;
		break;
	case 'U':
		updating = !updating;
		break;
	case 'd':
		mCamera->moveLR(1);
		break;
	case 'a':
		mCamera->moveLR(-1);
		break;
	case 'w':
		mCamera->moveUD(1);
		break;
	case 's':
		mCamera->moveUD(-1);
		break;
	case 'q':
		mCamera->moveFB(1);
		break;
	case 'e':
		mCamera->moveFB(-1);
		break;
	case '1':
		mScene->SetState(0);
		break;
	case '2':
		mScene->SetState(1);
		break;
	case '3':
		mScene->SetState(2);
		break;
	case '4':
		mScene->SetState(3);
		break;
	case '5':
		mScene->SetState(4);
		break;
	case '6':
		mScene->SetState(5);
		break;
	case '7':
		mScene->SetState(6);
		break;
	case 'p':
		mCamera->ChangePrj();
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		if (m2Vistas)
		{
			mCamera3->set3D();
			mCamera2->setCenital();
		}
		else {
			mCamera->set2D();
		}
		break;
	case 'c':
		orbiting = !orbiting;
		orbitHeight = 0;
		break;
	case 'x':
		mCamera->setCenital();
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
	
	int unit = 1;

	if (mdf == GLUT_ACTIVE_SHIFT)
		unit = 10;
	else unit = 1;
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->pitchReal(-unit);   // rotates -1 on the X axis
		else
			mCamera->pitchReal(unit);    // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
		    mCamera->yawReal(unit);      // rotates 1 on the Y axis 
		else 
			mCamera->yawReal(-unit);     // rotate -1 on the Y axis 
		break;
	case GLUT_KEY_UP:
		if (mdf == GLUT_ACTIVE_CTRL)
			orbitHeight++;
		else mCamera->rollReal(unit);    // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		if (mdf == GLUT_ACTIVE_CTRL)
			orbitHeight--;
		else mCamera->rollReal(-unit); ;   // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}

//-------------------------------------------------------------------------

void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseButt = button;

	mMouseCoord = {(double)x, -(double)(glutGet(GLUT_INIT_WINDOW_HEIGHT) - y)};
}
void IG1App::motion(int x, int y)
{
	glm::dvec2 mov = { (double)x, -(double)(glutGet(GLUT_INIT_WINDOW_HEIGHT) - y) };
	mov -= mMouseCoord;
	mMouseCoord = { (double)x, -(double)(glutGet(GLUT_INIT_WINDOW_HEIGHT) - y) };

	if (mMouseButt == 0)
	{
		mCamera->moveLR(-mov.x);
		mCamera->moveUD(mov.y);

		glutPostRedisplay();
	}
	else if (mMouseButt == 2)
	{
		mCamera->yawReal(-mov.x);
		mCamera->pitchReal(-mov.y);

		glutPostRedisplay();
	}
}
void IG1App::mouseWheel(int wheelButNo, int dir, int x, int y)
{
	if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		mCamera->setScale(dir * 0.01f);
		glutPostRedisplay();
	}
	else
	{
		mCamera->moveFB(-dir * 100);
		glutPostRedisplay();
	}
}

//-------------------------------------------------------------------------

void IG1App::update() {

	if (updating)
	{
		if (glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime > (1000 / 60))
		{
			mScene->update();
			if (orbiting) mCamera->orbit(1, orbitHeight);
			mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
			glutPostRedisplay();
		}
	}
}

