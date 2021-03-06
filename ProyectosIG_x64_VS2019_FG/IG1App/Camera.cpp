#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp) : mViewPort(vp), mViewMat(1.0), mProjMat(1.0),
xRight(vp->width() / 2.0), xLeft(-xRight),
yTop(vp->height() / 2.0), yBot(-yTop)
{
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
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
	mRadio = 500;
	mEye = dvec3(0, 0, mRadio);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	mAng = -90;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	mRadio = 500;
	mEye = dvec3(mRadio, mRadio, mRadio);
	mLook = dvec3(0, 10, 0);
	mUp = dvec3(0, 1, 0);
	mAng = -45;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
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

void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}

void Camera::moveLR(GLdouble cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}

void Camera::moveFB(GLdouble cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::moveUD(GLdouble cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}
void Camera::pitchReal(GLdouble cs)
{
	mViewMat = translate(mViewMat, mEye - mLook);
	mViewMat = rotate(mViewMat, radians(cs), mRight);
	mViewMat = translate(mViewMat, mLook - mEye);
	setAxes();
}
void Camera::yawReal(GLdouble cs)
{
	mViewMat = translate(mViewMat, mEye - mLook);
	mViewMat = rotate(mViewMat, radians(cs), mUp);
	mViewMat = translate(mViewMat, mLook - mEye);
	setAxes();

}
void Camera::rollReal(GLdouble cs)
{
	mViewMat = translate(mViewMat, mEye - mLook);
	mViewMat = rotate(mViewMat, radians(cs), mFront);
	mViewMat = translate(mViewMat, mLook - mEye);
	setAxes();
}

void Camera::update()
{
	/*moveUD(1);
	moveLR(-1);
	rollReal(1);
	setVM();*/
	;	/*mViewMat = translate(dmat4(1.0), dvec3(250 * cos(radians(alpha)), 250 * sin(radians(alpha)), 0.0));
		alpha++;
		mViewMat = rotate(mViewMat, radians(mAng), dvec3(0, 0, 1));
		mAng -= 15;
		setAxes();*/
}
void Camera::setCenital()
{
	mEye = dvec3(0, mRadio, 0);
	mAng = -90;
	mUp = dvec3(0, 0, -1);
	setVM();
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

void Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mNearVal = 1;
		mProjMat = ortho(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		GLfloat aux = 90;
		mNearVal = yTop / tan(aux / 2.0);
		mProjMat = frustum(-yTop * (xRight / yTop) * mScaleFact, yTop * (xRight / yTop) * mScaleFact,
			-mNearVal * tan(aux / 2.0) * mScaleFact, mNearVal * tan(aux / 2.0) * mScaleFact,mNearVal, mFarVal);
	}
	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------
