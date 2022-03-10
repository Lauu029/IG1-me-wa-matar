//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
using namespace glm;
//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(3),posL(0,0,0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() {};

	void setTexture(Texture* tex);

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	void setColor(glm::dvec4 col);
	glm::dvec4 getColor();
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;		//Para los colores
	glm::dvec3 posL;
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
	Texture* mTexture = nullptr;
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class PoligonsRGB : public Abs_Entity
{
public:
	explicit PoligonsRGB(GLuint num, GLdouble r);
	~PoligonsRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble r, GLdouble x, GLdouble y);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() override;
private:
	float alpha = 0.0f;
	GLdouble angle = 0.0f;
};
//------------------------------------------------------------------
class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//--------------------------------------------------------------------
class CuboRGB : public Abs_Entity
{
public:
	explicit CuboRGB(GLdouble l);
	~CuboRGB();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble angleX = 0.0f;
	GLdouble angleY = 0.0f;
	GLdouble angleZ = 0.0f;
	GLdouble lado = 0.0f;
};
//--------------------------------------------------------------
class Suelo : public Abs_Entity
{
public:
	explicit Suelo();
	~Suelo();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:

};
//--------------------------------------------------
class ContornoCaja : public Abs_Entity
{
public:
	explicit ContornoCaja(GLdouble l);
	~ContornoCaja();
	void setTexturesCaja(Texture* a_, Texture* b_);
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	Texture* a; Texture* b;
};
//-------------------------------------
class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble angle = 0.0;
};
//-------------------------------------
class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble l);
	~Caja();
	virtual void update() override;
	void setTexureCaja(Texture* front, Texture* back);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble angle = 0.0;
	Mesh* tapa = nullptr;
	dmat4 tapaModelMat = dmat4(1);
	Mesh* suelo = nullptr;
	dmat4 sueloModelMat = dmat4(1);
	Texture* front;
	Texture* back;
	dvec3 posicion;
};
#endif //_H_Entities_H_