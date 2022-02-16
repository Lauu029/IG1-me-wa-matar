#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::setColor(dvec4 col)
{
	mColor = col;
}

dvec4 Abs_Entity::getColor()
{
	return mColor;
}

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

PoligonsRGB::PoligonsRGB(GLuint num, GLdouble r)
{
	mMesh = Mesh::generaPoligonoRegular(num, r);

}

PoligonsRGB::~PoligonsRGB()
{
	delete mMesh; mMesh = nullptr;
}

void PoligonsRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glColor3d(mColor.r, mColor.g, mColor.b);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glColor3d(0, 0, 0);
	}
}
TrianguloRGB::TrianguloRGB(GLdouble r)
{
	mMesh = Mesh::generaTriangulo(r);
}
TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}
void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glColor3d(mColor.r, mColor.g, mColor.b);
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		
		mMesh->render();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(0, 0, 0);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectangulo(w,h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glLineWidth(1);
	}
}

CuboRGB::CuboRGB(GLdouble l)
{
	mMesh = Mesh::generaCubo(l);
}

CuboRGB::~CuboRGB()
{
	delete mMesh; mMesh = nullptr;
}

void CuboRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();
		glLineWidth(1);
	}
}
