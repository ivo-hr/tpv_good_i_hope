#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>
//#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	mViewMat = translate(mViewMat, mRight * -cs);
	setAxes();
	uploadVM();
}

void Camera::moveFB(GLdouble cs)
{
	mViewMat = translate(mViewMat, mFront * -cs);
	setAxes();
	uploadVM();
}

void Camera::moveUD(GLdouble cs)
{
	mViewMat = translate(mViewMat, mUp * -cs);
	setAxes();
	uploadVM();
}

void Camera::ChangePrj()
{
	bOrto = !bOrto;
	setPM();
}

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = row(mViewMat, 2);
}

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	mEye = dvec3(0, 0, 500);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	mAng = 1;
	mRadio = mEye.z;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mEye = dvec3(500, 500, 500);  
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);
	mAng = 1;
	mRadio = mEye.z;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1, 0, 0));
	setAxes();
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1, 0));
	setAxes();
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1));
	setAxes();
	//glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::pitchReal(GLdouble a)
{
	//Mup y mlook
					//mirando arriba positivo	
	mViewMat = translate(mViewMat, mEye);

	mViewMat = rotate(mViewMat, glm::radians(a), mRight);

	mViewMat = translate(mViewMat, -mEye);
	setAxes();
	uploadVM();

}
//-------------------------------------------------------------------------

void Camera::yawReal(GLdouble a)
{
	//mlook

	mViewMat = translate(mViewMat, mEye);

	mViewMat = rotate(mViewMat, glm::radians(a), mUpward);

	mViewMat = translate(mViewMat, -mEye);
	setAxes();
	uploadVM();
}
//-------------------------------------------------------------------------

void Camera::rollReal(GLdouble a)
{
	mViewMat = translate(mViewMat, mEye);

	mViewMat = rotate(mViewMat, glm::radians(a), mFront);

	mViewMat = translate(mViewMat, -mEye);
	setAxes();
	uploadVM();
}
//-------------------------------------------------------------------------

void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	mAng += incAng;

	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;

	mEye.y += incY;

	setVM();
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setCenital()
{
	mEye = dvec3(0, mRadio, 0);
	mAng = -90;
	mUp = dvec3(0, 0, -1);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mNearVal = 1;
		mProjMat = ortho(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else
	{
		mNearVal = yTop * mScaleFact;
		mProjMat = frustum(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
	}
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


