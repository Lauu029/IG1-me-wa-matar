#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const
{
	glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
	  // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}
		//comprueba las normales
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble alfa = 90;
	for (int i = 0; i < num; i++) {
		mesh->vVertices.emplace_back(r * cos(radians(alfa)), r * sin(radians(alfa)), 0.0);

		alfa += 360 / num;
	}
	return mesh;
}

Mesh* Mesh::generaTriangulo(GLdouble r, GLdouble x, GLdouble y)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 3;
	GLdouble alfa = 90;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(r * cos(radians(alfa)), r * sin(radians(alfa)), 0.0);
	mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
	alfa = 210;
	mesh->vVertices.emplace_back(r * cos(radians(alfa)), r * sin(radians(alfa)), 0.0);
	mesh->vColors.emplace_back(0.0, 1.0, 1.0, 1.0);
	alfa = 330;
	mesh->vVertices.emplace_back(r * cos(radians(alfa)), r * sin(radians(alfa)), 0.0);
	mesh->vColors.emplace_back(1.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;

	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0.0);


	return mesh;
}

Mesh* Mesh::generaCubo(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	//front
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);

	//top
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	//left
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	//back
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	//right
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	//bottom
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);

	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);


	return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	Mesh* m = generaRectangulo(w, h);
	m->vTexCoords.reserve(m->mNumVertices);
	m->vTexCoords.emplace_back(0, rw);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(rh, rw);
	m->vTexCoords.emplace_back(rh, 0);
	return m;
}

Mesh* Mesh::generaContornoCaja(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;

	mesh->vVertices.reserve(mesh->mNumVertices);


	mesh->vVertices.emplace_back(-w / 2, h / 2, w / 2);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, w / 2);
	mesh->vVertices.emplace_back(w / 2, h / 2, w / 2);
	mesh->vVertices.emplace_back(w / 2, -h / 2, w / 2);
	mesh->vVertices.emplace_back(w / 2, h / 2, -w / 2);
	mesh->vVertices.emplace_back(w / 2, -h / 2, -w / 2);
	mesh->vVertices.emplace_back(-w / 2, h / 2, -w / 2);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, -w / 2);

	mesh->vVertices.emplace_back(-w / 2, h / 2, w / 2);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, w / 2);

	return mesh;
}

Mesh* Mesh::generaCajaTexCor(GLdouble w, GLdouble h)
{
	Mesh* mesh = generaContornoCaja(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(2, 1);
	mesh->vTexCoords.emplace_back(2, 0);
	mesh->vTexCoords.emplace_back(3, 1);
	mesh->vTexCoords.emplace_back(3, 0);

	mesh->vTexCoords.emplace_back(4, 1);
	mesh->vTexCoords.emplace_back(4, 0);
	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);

	return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->mNumVertices = np * 2 + 2;

	mesh->vVertices.emplace_back(0, 0, 0);

	GLdouble ri = re / 2;
	GLdouble alfa = 0;
	for (int i = 0; i < np * 2; i++) {
		if (i % 2 == 0) {
			mesh->vVertices.emplace_back(re * cos(radians(alfa)), re * sin(radians(alfa)), h);

		}
		else {
			mesh->vVertices.emplace_back(ri * cos(radians(alfa)), ri * sin(radians(alfa)), h);
		}
		alfa += 360 / (np * 2.0);

	}
	mesh->vVertices.emplace_back(re * cos(radians(alfa)), re * sin(radians(alfa)), h);
	return mesh;
}

Mesh* Mesh::generaEstrella3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generaEstrella3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.5f, 0.5f);

	// Vértices de la textura
	GLdouble angle = 0;
	for (int i = 0; i < mesh->mNumVertices - 1; i++) {
		if (i % 2 == 0) {
			mesh->vTexCoords.emplace_back((cos(radians(angle)) / 2 * 0.5f + 0.5f), (sin(radians(angle)) / 2 * 0.5f + 0.5f));
		}
		else {
			mesh->vTexCoords.emplace_back((cos(radians(angle)) / 2 * 0.5f + 0.5f), (sin(radians(angle)) / 2 * 0.5f + 0.5f));
		}
		angle += 360.0f / (np * 2.0f);
	}
	return mesh;
}

Mesh* Mesh::generaAlaTie(GLdouble h, GLdouble w, GLdouble dist)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 8;

	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-w / 2, -h, dist / 2);
	mesh->vVertices.emplace_back(w / 2, -h, dist / 2);

	mesh->vVertices.emplace_back(-w / 2, -h / 2, dist);
	mesh->vVertices.emplace_back(w / 2, -h / 2, dist);

	mesh->vVertices.emplace_back(-w / 2, h / 2, dist);
	mesh->vVertices.emplace_back(w / 2, h / 2, dist);

	mesh->vVertices.emplace_back(-w / 2, h, dist / 2);
	mesh->vVertices.emplace_back(w / 2, h, dist / 2);

	return mesh;
}

Mesh* Mesh::generaAlaTieTexCor(GLdouble h, GLdouble w, GLdouble dist)
{
	Mesh* mesh = generaAlaTie(h, w, dist);

	mesh->vTexCoords.reserve(mesh->mNumVertices);


	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(1, 1);

	mesh->vTexCoords.emplace_back(2, 0);
	mesh->vTexCoords.emplace_back(2, 1);

	mesh->vTexCoords.emplace_back(3, 1);
	mesh->vTexCoords.emplace_back(3, 0);

	return mesh;
}

IndexMesh::IndexMesh()
{
	mPrimitive = GL_TRIANGLE_STRIP;
}

IndexMesh::~IndexMesh()
{
	delete[] vIndices;;
}

void IndexMesh::draw() const
{
	glDrawElements(mPrimitive, mNumIndices, GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaCuboConTapasIndexado(GLdouble l)
{
	IndexMesh* Imesh = new IndexMesh();

	Imesh->mPrimitive = GL_TRIANGLES;

	Imesh->mNumVertices = 8;

	Imesh->vVertices.reserve(Imesh->mNumVertices);

	Imesh->vColors.reserve(Imesh->mNumVertices);
	

	Imesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	Imesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	Imesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	Imesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);

	Imesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	Imesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	Imesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	Imesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	Imesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

	
	Imesh->mNumIndices = 36;

	//Calculo los indices
	Imesh ->vIndices = 
		new GLuint[Imesh->mNumIndices]{ 0,1,2,
										2,1,3,
										2,3,4,
										4,3,5,
										5,6,4,
										5,7,6,
										6,7,1,
										0,6,1,
										6,0,4,
										4,0,2,
										7,1,5,
										5,1,3 };

	Imesh->vNormals.reserve(Imesh->mNumVertices);
	
	//Inicializo el vector de normales
	for (int i = 0; i < Imesh->mNumVertices; i++) {
		Imesh->vNormals.push_back(glm::dvec3(0, 0, 0));
	}

	//Construye los vectores de normales con el método en lugar de manualmente
	Imesh->buildNormalVectors();

	return Imesh;
}

void IndexMesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
	  // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}
		//comprueba las normales
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}
		draw();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
	}
}

void IndexMesh::buildNormalVectors()
{
	vNormals.reserve(mNumVertices);
	for (int i = 0; i < mNumVertices; i++)
	{
		vNormals.push_back(dvec3(0, 0, 0));
	}
	//Recorre los indices de tres en tres
	for (int i = 0; i < mNumIndices; i += 3)
	{
		//Para almacenar los vertices
		dvec3 v1, v2, v3;
		v1 = vVertices.at(vIndices[i]);
		v2 = vVertices.at(vIndices[i + 1]);
		v3 = vVertices.at(vIndices[i + 2]);

		//Calculo los vectores
		dvec3 u1, u2;

		u1 = v2 - v1;
		u2 = v3 - v1;

		//Calculo la normal
		dvec3 n = cross(u1, u2);

		//sumo las normales
		vNormals[vIndices[i]] += n;
		vNormals[vIndices[i + 1]] += n;
		vNormals[vIndices[i + 2]] += n;
	}

	//normalizo el vector
	for (int i = 0; i < vNormals.size(); i++)
	{
		vNormals[i] = normalize(vNormals[i]);
	}
}
