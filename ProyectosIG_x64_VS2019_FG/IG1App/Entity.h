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
	Abs_Entity() : mModelMat(1.0), mColor(3), posL(0, 0, 0) {};  // 4x4 identity matrix
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

	void setPos(GLdouble x, GLdouble y, GLdouble z);
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;		//Para los colores
	glm::dvec3 posL;	//posicion de la entidad
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
	explicit Suelo(GLdouble l, GLint n);
	~Suelo();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void setTextureSuelo(Texture* a, Texture* b);
protected:
	Texture* fuera = nullptr;
	Texture* dentro = nullptr;
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
	Texture* a = nullptr;
	Texture* b = nullptr;
};
//-------------------------------------
class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h, GLdouble x = 0, GLdouble y = 0, GLdouble z = 0);
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
	explicit Caja(GLdouble l, GLdouble x = 0, GLdouble y = 0, GLdouble z = 0);
	~Caja();
	virtual void update() override;
	void setTexureCaja(Texture* front, Texture* back);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble angle = 90.0;
	GLdouble lado = 0.0;
	Suelo* tapa = nullptr;
	Suelo* suelo_ = nullptr;
	bool giro = false;
	Texture* front = nullptr;
	Texture* back = nullptr;
};
//-------------------------------------
class Cristalera : public Abs_Entity
{
public:
	explicit Cristalera(GLdouble w, GLdouble h);
	~Cristalera();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble angle = 90.0;
	GLdouble lado = 0.0;
};
//-----------------------------------------------
class Hierba : public Abs_Entity
{
public:
	explicit Hierba(GLdouble w, GLdouble x = 0, GLdouble y = 0, GLdouble z = 0);
	~Hierba();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------
class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w);
	~Foto();
	virtual void update() override;
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------
class QuadricEntity : public Abs_Entity {
public:
	explicit QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};
//-------------------------------------------------------------
class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble rr); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};
//-------------------------------------------------------------
class Cylinder : public QuadricEntity
{
public:
	explicit Cylinder(GLdouble br_, GLdouble tr_, GLdouble h_);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble br, tr, h;

};
//-------------------------------------------------------------
class Disk : public QuadricEntity
{
public:
	explicit Disk(GLdouble ird_, GLdouble ord_);
	
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ird, ord ;
};
//-------------------------------------------------------------
class PartialDisk : public QuadricEntity
{
public:
	explicit PartialDisk(GLdouble ird_,GLdouble ord_, GLdouble stan_,GLdouble swan_);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ird, ord, stan, swan;
};
//--------------------------------------------------------------
class CompoundEntity : public Abs_Entity {
public:
	~CompoundEntity();
	void addEntity(Abs_Entity* ae);
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	std::vector<Abs_Entity*> gObjects;
};
//--------------------------------------------------------------
class TIEavanzado : public CompoundEntity {
public:
	explicit TIEavanzado();
protected:
};
#endif //_H_Entities_H_