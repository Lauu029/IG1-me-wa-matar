#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "IG1App.h"
using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::setTexture(Texture* tex)
{
	mTexture = tex;
}

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
void Abs_Entity::setPos(GLdouble x, GLdouble y, GLdouble z)
{
	posL = dvec3(x, y, z);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l) : Abs_Entity()
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
//------------------------------------------------------------------------
TrianguloRGB::TrianguloRGB(GLdouble r, GLdouble x, GLdouble y)
{
	mMesh = Mesh::generaTriangulo(r, x, y);
	mModelMat = translate(mModelMat, dvec3(x, y, 0));

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
void TrianguloRGB::update()
{
	mModelMat = translate(dmat4(1.0), dvec3(250 * cos(radians(alpha)),
		250 * sin(radians(alpha)), 0.0));
	alpha++;
	mModelMat = rotate(mModelMat, radians(angle), dvec3(0, 0, 1));
	angle -= 15;
	//glRotatef(1.0,0,0,0);

}

//------------------------------------------------------------------------
RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectangulo(w, h);
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
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		mMesh->render();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
//------------------------------------------------------------------------
CuboRGB::CuboRGB(GLdouble l)
{
	mMesh = Mesh::generaCubo(l);
	mModelMat = translate(mModelMat, dvec3(-l / 2, l / 2, l / 2));
	lado = l;
}

CuboRGB::~CuboRGB()
{
	delete mMesh; mMesh = nullptr;
}

void CuboRGB::update()
{
	if (angleY < 180)
	{
		angleY += 3.0;
	}
	else if (angleX < 180)
	{
		angleX += 3.0;
	}
	else if (angleZ < 180)
	{
		angleZ += 3.0;
	}
	else angleX = angleY = angleZ = 0;

	mModelMat = rotate(dmat4(1), radians(angleX), dvec3(1, 0, 0));
	mModelMat = rotate(mModelMat, radians(angleY), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(angleZ), dvec3(0, 0, 1));
	mModelMat = translate(mModelMat, dvec3((-lado / 2), (lado / 2), (lado / 2)));
}

void CuboRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		mMesh->render();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
//------------------------------------------------------------------------
Suelo::Suelo(GLdouble l, GLint n)
{
	mMesh = Mesh::generaRectanguloTexCor(l, l, n, n);
	mModelMat = rotate(mModelMat, radians(-90.0), dvec3(1, 0, 0));
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}

void Suelo::update()
{
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);

		glEnable(GL_CULL_FACE);
		//textura de la cara frontal
		glCullFace(GL_BACK);

		fuera->bind(GL_REPLACE);
		mMesh->render();
		fuera->unbind();

		glCullFace(GL_FRONT);
		dentro->bind(GL_REPLACE);
		mMesh->render();
		dentro->unbind();
		glDisable(GL_CULL_FACE);
		glColor4d(1, 1, 1, 1);
	}
}
void Suelo::setTextureSuelo(Texture* a, Texture* b)
{
	fuera = a; dentro = b;
}
//------------------------------------------------------------------------
ContornoCaja::ContornoCaja(GLdouble l)
{
	mMesh = Mesh::generaCajaTexCor(l, l);
}

ContornoCaja::~ContornoCaja()
{
	delete mMesh; mMesh = nullptr;
}

void ContornoCaja::setTexturesCaja(Texture* a_, Texture* b_)
{
	a = a_;
	b = b_;
}

void ContornoCaja::update()
{

}

void ContornoCaja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		/*glColor4dv(value_ptr(mColor));*/
		glEnable(GL_CULL_FACE);
		//textura de la cara frontal
		glCullFace(GL_BACK);

		a->bind(GL_REPLACE);
		mMesh->render();
		a->unbind();

		glCullFace(GL_FRONT);
		b->bind(GL_REPLACE);
		mMesh->render();
		b->unbind();
		glDisable(GL_CULL_FACE);
		//glColor4d(1, 1, 1, 1);
	}
}
//------------------------------------------------------------------------
Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h, GLdouble x, GLdouble y, GLdouble z)
{
	setPos(x, y, z);
	mMesh = Mesh::generaEstrella3DTexCor(re, np, h);
	mModelMat = translate(mModelMat, posL);
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::update()
{

	mModelMat = translate(dmat4(1), posL);
	mModelMat = rotate(mModelMat, -radians(angle), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(angle), dvec3(0, 0, 1));
	angle++;


}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		aMat = scale(aMat, dvec3(1, 1, -1));
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

	}
}
//------------------------------------------------------------------------

Caja::Caja(GLdouble l, GLdouble x, GLdouble y, GLdouble z)
{
	setPos(x, y, z);
	mMesh = Mesh::generaCajaTexCor(l, l);
	mModelMat = translate(mModelMat, dvec3(posL.x, posL.y, posL.z));
	tapa = new Suelo(l, 1);
	lado = l;

	tapa->setModelMat(translate(dmat4(1), dvec3(posL.x, posL.y + l / 2.0, posL.z)));
	tapa->setModelMat(rotate(tapa->modelMat(), radians(-90.0), dvec3(1, 0, 0)));


	suelo_ = new Suelo(l, 1);
	suelo_->setModelMat(translate(dmat4(1), dvec3(posL.x, posL.y - l / 2.0, posL.z)));
	suelo_->setModelMat(rotate(suelo_->modelMat(), radians(90.0), dvec3(1, 0, 0)));
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
	delete suelo_; suelo_ = nullptr;
	delete tapa; tapa = nullptr;
}

void Caja::update()
{
	if (!giro)
	{
		angle -= 3.0;
	}
	else angle += 3.0;
	if (angle >= 90.0 || angle <= -90.0) giro = !giro;

	tapa->setModelMat(rotate(dmat4(1), 3.14, dvec3(0, 1, 0)));
	tapa->setModelMat(translate(tapa->modelMat(), dvec3(-posL.x, posL.y + (lado / 2), -posL.z + (lado / 2))));
	tapa->setModelMat(rotate(tapa->modelMat(), radians(angle), dvec3(-1, 0, 0)));
	tapa->setModelMat(translate(tapa->modelMat(), dvec3(0, (lado / 2), 0)));
}

void Caja::setTexureCaja(Texture* front_, Texture* back_)
{
	front = front_;
	back = back_;
	tapa->setTextureSuelo(front_, back_);
	suelo_->setTextureSuelo(front_, back_);
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		tapa->render(modelViewMat);
		suelo_->render(modelViewMat);

		glEnable(GL_CULL_FACE);
		//textura de la cara frontal
		glCullFace(GL_BACK);

		upload(aMat);
		front->bind(GL_REPLACE);
		mMesh->render();
		front->unbind();


		glCullFace(GL_FRONT);

		upload(aMat);
		back->bind(GL_REPLACE);
		mMesh->render();
		back->unbind();
		glDisable(GL_CULL_FACE);

	}
}
//------------------------------------------------------------
Cristalera::Cristalera(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaCajaTexCor(w, h);
}

Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
}

void Cristalera::update()
{
}


void Cristalera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

	}
}
//------------------------------------------------------------
Hierba::Hierba(GLdouble w, GLdouble x, GLdouble y, GLdouble z)
{
	setPos(x, y, z);
	mMesh = Mesh::generaRectanguloTexCor(w, w, 1, 1);
	mModelMat = translate(mModelMat, posL);
}

Hierba::~Hierba()
{
	delete mMesh; mMesh = nullptr;
}

void Hierba::update()
{
}


void Hierba::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		mTexture->bind(GL_MODULATE);

		dmat4 aMat = modelViewMat * rotate(mModelMat, radians(60.0), dvec3(0, 1, 0));
		upload(aMat);
		mMesh->render();
		aMat = modelViewMat * rotate(mModelMat, radians(120.0), dvec3(0, 1, 0));
		upload(aMat);
		mMesh->render();
		aMat = modelViewMat * rotate(mModelMat, radians(180.0), dvec3(0, 1, 0));
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glDisable(GL_ALPHA_TEST);
	}
}
//------------------------------------------------------------
Foto::Foto(GLdouble w)
{
	mMesh = Mesh::generaRectanguloTexCor(w, w, 1, 1);
	mModelMat = translate(dmat4(1), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(-90.0), dvec3(1, 0, 0));
}

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
}

void Foto::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.getWidht(), IG1App::s_ig1app.getHeigth(), GL_FRONT);
}


void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);

		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
	}
}

Sphere::Sphere(GLdouble rr)
{
	r = rr;
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	 glEnable(GL_COLOR_MATERIAL);
	 glColor3f(1.0,0.0,0.0);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

QuadricEntity::QuadricEntity()
{
	q = gluNewQuadric();
}
