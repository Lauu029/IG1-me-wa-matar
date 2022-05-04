#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "IG1App.h"
using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{
	setGL();  // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures
	// Graphics objects (entities) of the scene
	GLfloat amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	setLights();
	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0)
	{
		PoligonsRGB* circulo = new PoligonsRGB(360, 250);
		circulo->setColor({ 0,1,1,0 });

		gObjects.push_back(circulo);
		gObjects.push_back(new RectanguloRGB(250 * 2, 250));
		//gObjects.push_back(new TrianguloRGB(50, 250, 0));
		CompoundEntity* nodoFicticio = new CompoundEntity();
		CompoundEntity* nodoFicticio2 = new CompoundEntity();
		TrianguloRGB* tr = new TrianguloRGB(50, 250, 0);
		nodoFicticio2->addEntity(tr);
		nodoFicticio->addEntity(nodoFicticio2);
		gObjects.push_back(nodoFicticio);
		
	}
	else if (id == 1)
	{
		gObjects.push_back(new CuboRGB(90));
	}
	else if (id == 2) {
		/*Texture* texSuelo = new Texture();
		texSuelo->load("..//Bmps//baldosaC.bmp");
		gTextures.push_back(texSuelo);
		Suelo* suelo_ = new Suelo(100, 5);
		gObjects.push_back(suelo_);
		suelo_->setTextureSuelo(texSuelo, texSuelo);*/

		Esfera* e = new Esfera(100.0, 10.0, 10.0);
		Material* mat = new Material();
		mat->setGold();
		e->setMaterial(mat);
		gMaterials.push_back(mat);
		dmat4 esfTr = translate(e->modelMat(), dvec3(0.0, 0.0, 200.0));
		e->setModelMat(esfTr);
		gObjects.push_back(e);
		
		Esfera* e2 = new Esfera(100.0, 10.0, 10.0);
		e2->setColor(dvec4(1.0, 0.91, 0.0, 1.0));
		dmat4 esfTr2 = translate(e2->modelMat(), dvec3(200.0, 0.0, 0.0));
		e2->setModelMat(esfTr2);
		gObjects.push_back(e2);

	}
	else if (id == 3) {

		/*Texture* cajaFuera = new Texture();
		cajaFuera->load("..//Bmps//container.bmp");
		Texture* cajaDentro = new Texture();
		cajaDentro->load("..//Bmps//papelE.bmp");
		gTextures.push_back(cajaFuera);
		gTextures.push_back(cajaDentro);
		ContornoCaja* cajaCont = new ContornoCaja(100);
		gObjects.push_back(cajaCont);
		cajaCont->setTexturesCaja(cajaFuera, cajaDentro);*/
		Toro* t = new Toro(20.0, 100.0, 12, 20.0);
		gObjects.push_back(t);
	}
	else if (id == 4) {
		Texture* texEstrella = new Texture();
		texEstrella->load("..//Bmps//baldosaP.bmp");
		gTextures.push_back(texEstrella);
		gObjects.push_back(new Estrella3D(100, 8, 150));
		gObjects.back()->setTexture(texEstrella);
	}
	else if (id == 5) {
		Texture* fuera = new Texture();
		fuera->load("..//Bmps//container.bmp");
		gTextures.push_back(fuera);
		Texture* dentro = new Texture();
		dentro->load("..//Bmps//papelE.bmp");
		gTextures.push_back(dentro);
		Caja* caja = new Caja(100);
		gObjects.push_back(caja);
		caja->setTexureCaja(fuera, dentro);
	}
	else if (id == 6) {
		/*Texture* texCristalera = new Texture();
		texCristalera->load("..//Bmps//windowV.bmp", 255 / 2);
		gTextures.push_back(texCristalera);
		Cristalera* crist_ = new Cristalera(200, 100);
		gTranslucidObjects.push_back(crist_);
		gTranslucidObjects.back()->setTexture(texCristalera);*/
		Cubo* c = new Cubo(50.0);
		gObjects.push_back(c);
	}
	else if (id == 7) {
		/*Texture* hText = new Texture();
		hText->load("..//Bmps//grass.bmp", glm::u8vec3(0, 0, 0), 0);
		gTextures.push_back(hText);
		gObjects.push_back(new Hierba(100));
		gObjects.back()->setTexture(hText);*/

		//Esfera
		Sphere* esfera = new Sphere(100.0);
		dvec4 colorEsfera;
		colorEsfera.r = 1.0;
		colorEsfera.g = 0.5;
		colorEsfera.b = 0.0;
		colorEsfera.a = 1.0;
		esfera->setColor(colorEsfera);
		gObjects.push_back(esfera);

		//disco
		Disk* disco = new Disk(50.0, 100.0);
		dvec4 colorDisco;
		colorDisco.r = 1.0;
		colorDisco.g = 0.0;
		colorDisco.b = 0.0;
		colorDisco.a = 1.0;
		disco->setColor(colorDisco);
		dmat4 discTrans = translate(disco->modelMat(), dvec3(0.0, 80.0, 0.0));
		discTrans = rotate(discTrans, radians(90.0), dvec3(1.0, 0.0, 0.0));
		disco->setModelMat(discTrans);
		gObjects.push_back(disco);

		//Conos
		Cylinder* ojo1 = new Cylinder(5.0, 0.0, 10.0);
		dvec4 colorOjo1;
		colorOjo1.r = 0.0;
		colorOjo1.g = 0.0;
		colorOjo1.b = 1.0;
		colorOjo1.a = 1.0;
		ojo1->setColor(colorOjo1);
		dmat4 conTrans = translate(ojo1->modelMat(), dvec3(-30.0, 30.0, 90.0));
		ojo1->setModelMat(conTrans);
		gObjects.push_back(ojo1);

		Cylinder* ojo2 = new Cylinder(5.0, 0.0, 10.0);
		dvec4 colorOjo2;
		colorOjo2.r = 0.16;
		colorOjo2.g = 0.19;
		colorOjo2.b =  0.2;
		colorOjo2.a = 1.0;
		ojo2->setColor(colorOjo2);
		dmat4 conTrans2 = translate(ojo2->modelMat(), dvec3(30.0, 30.0, 90.0));
		ojo2->setModelMat(conTrans2);
		gObjects.push_back(ojo2);
		//disco
		PartialDisk* discoParcial = new PartialDisk(50.0, 100.0,90.0,180.0);
		dvec4 colorDiscoP;
		colorDiscoP.r = 0.0;
		colorDiscoP.g = 1.0;
		colorDiscoP.b = 0.0;
		colorDiscoP.a = 1.0;
		discoParcial->setColor(colorDiscoP);
		dmat4 discPTrans = translate(discoParcial->modelMat(), dvec3(0.0, 0.0, 50.0));
	
		discoParcial->setModelMat(discPTrans);
		gObjects.push_back(discoParcial);
	}
	else if (id == 8) {

		/*Texture* fotoText = new Texture();
		gTextures.push_back(fotoText);
		fotoText->loadColorBuffer(IG1App::s_ig1app.getWidht(), IG1App::s_ig1app.getHeigth(), GL_FRONT);

		gObjects.push_back(new Foto(100));
		gObjects.back()->setTexture(fotoText);*/
		glClearColor(0.0, 0.0, 0.0,0.0);
		
		//planeta
		GLdouble radioPlaneta = 250.0;
		Sphere* esfera = new Sphere(radioPlaneta);

		esfera->setColor(dvec4(1.0,0.91,0.0,1.0));
		gObjects.push_back(esfera);

		//nave
		GLdouble altoNave=50.0;
		rotacionTie = new CompoundEntity();
		Texture* texAla = new Texture();
		texAla->load("..//Bmps//noche.bmp",255/2);
		TIEavanzado* tie = new TIEavanzado(texAla,altoNave,75);
		tie->setModelMat(translate(tie->modelMat(),dvec3(0.0,radioPlaneta+altoNave,0.0)));
		gTextures.push_back(texAla);
		rotacionTie->addEntity(tie);
		gObjects.push_back(rotacionTie);
	}
	else if (id == 9) {
		//Suelo
		Texture* texSuelo = new Texture();
		texSuelo->load("..//Bmps//baldosaC.bmp");
		gTextures.push_back(texSuelo);
		Suelo* suelo_ = new Suelo(300, 5);
		gObjects.push_back(suelo_);
		suelo_->setTextureSuelo(texSuelo, texSuelo);

		//Caja
		Texture* fuera = new Texture();
		fuera->load("..//Bmps//container.bmp");
		gTextures.push_back(fuera);
		Texture* dentro = new Texture();
		dentro->load("..//Bmps//papelE.bmp");
		gTextures.push_back(dentro);
		Caja* caja = new Caja(70, -100, 35, -100);
		gObjects.push_back(caja);
		caja->setTexureCaja(fuera, dentro);

		//Estrella
		Texture* texEstrella = new Texture();
		texEstrella->load("..//Bmps//baldosaP.bmp");
		gTextures.push_back(texEstrella);
		gObjects.push_back(new Estrella3D(80, 8, 150, -100, 150, -100));
		gObjects.back()->setTexture(texEstrella);

		//Cristalera
		Texture* texCristalera = new Texture();
		texCristalera->load("..//Bmps//windowV.bmp", 255 / 2);
		gTextures.push_back(texCristalera);
		Cristalera* crist_ = new Cristalera(300, 100);
		gTranslucidObjects.push_back(crist_);
		gTranslucidObjects.back()->setTexture(texCristalera);
		//hierba
		Texture* hText = new Texture();
		gTextures.push_back(hText);
		hText->load("..//Bmps//grass.bmp", glm::u8vec3(0, 0, 0), 0);

		gObjects.push_back(new Hierba(100, 80, 50, -80));
		gObjects.back()->setTexture(hText);

		//Foto
		Texture* fotoText = new Texture();
		gTextures.push_back(fotoText);
		fotoText->loadColorBuffer(IG1App::s_ig1app.getWidht(), IG1App::s_ig1app.getHeigth(), GL_FRONT);

		gObjects.push_back(new Foto(100));
		gObjects.back()->setTexture(fotoText);
	}
}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
	for (Abs_Entity* el : gTranslucidObjects)
	{
		delete el;  el = nullptr;
	}
	gTranslucidObjects.clear();
	for (Texture* t : gTextures) {
		delete t; t = nullptr;
	}
	gTextures.clear();
	for (Material* m : gMaterials) {
		delete m; m = nullptr;
	}
	gMaterials.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	//sceneDirLight(cam);
	cam.upload();
	uploadLights(cam);

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());
	}
	//preparacion para el render translucido
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* tr : gTranslucidObjects) {
		tr->render(cam.viewMat());
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
//-----------------------------------------------------------------------
void Scene::setScene(int id)
{
	free();
	gObjects.clear();
	setId(id);
	init();
}

void Scene::setId(int _id)
{
	id = _id;
}

void Scene::Update()
{
	for (auto g : gObjects)
		g->update();
	for (auto g : gTranslucidObjects)
		g->update();
}

void Scene::savePhoto()
{
	Texture* photo = new Texture();
	photo->loadColorBuffer(IG1App::s_ig1app.getWidht(), IG1App::s_ig1app.getHeigth());
	photo->save("..//Bmps//foto.bmp");
	delete photo;

}


void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

void Scene::rota()
{
	rotacionTie->setModelMat(rotate(rotacionTie->modelMat(), radians(3.0), dvec3(0.0, 1.0, 0.0)));
}

void Scene::orbita()
{
	//rota en la direccion del morro
	rotacionTie->setModelMat(rotate(rotacionTie->modelMat(), radians(1.0), dvec3(0.0, 0.0, -1.0)));
}

void Scene::setLights()
{
	dirLight = new DirLight();
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	dirLight->setAmbient(ambient);
	dirLight->setSpecular(diffuse);
	dirLight->setDiffuse(specular);
	dirLight->setPosDir(posDir);
}

void Scene::DirLightAble(bool active)
{
	if (active) dirLight->enable();
	else  dirLight->disable();
}

void Scene::uploadLights(Camera const& cam) const
{
	dirLight->upload(cam.viewMat());
}
