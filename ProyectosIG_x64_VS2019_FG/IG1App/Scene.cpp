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

	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0)
	{
		PoligonsRGB* circulo = new PoligonsRGB(360, 250);
		circulo->setColor({ 0,1,1,0 });

		gObjects.push_back(circulo);
		gObjects.push_back(new RectanguloRGB(250 * 2, 250));
		gObjects.push_back(new TrianguloRGB(50, 250, 0));
	}
	else if (id == 1)
	{
		gObjects.push_back(new CuboRGB(90));
	}
	else if (id == 2) {
		Texture* texSuelo = new Texture();
		texSuelo->load("..//Bmps//baldosaC.bmp");
		gTextures.push_back(texSuelo);
		Suelo* suelo_ = new Suelo(100, 5);
		gObjects.push_back(suelo_);
		suelo_->setTextureSuelo(texSuelo, texSuelo);

	}
	else if (id == 3) {

		Texture* cajaFuera = new Texture();
		cajaFuera->load("..//Bmps//container.bmp");
		Texture* cajaDentro = new Texture();
		cajaDentro->load("..//Bmps//papelE.bmp");
		gTextures.push_back(cajaFuera);
		ContornoCaja* cajaCont = new ContornoCaja(100);
		gObjects.push_back(cajaCont);
		cajaCont->setTexturesCaja(cajaFuera, cajaDentro);
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
		Texture* texCristalera = new Texture();
		texCristalera->load("..//Bmps//windowV.bmp", 255 / 2);
		gTextures.push_back(texCristalera);
		Cristalera* crist_ = new Cristalera(200, 100);
		gTranslucidObjects.push_back(crist_);
		gTranslucidObjects.back()->setTexture(texCristalera);
	}
	else if (id == 7) {
		Texture* hText = new Texture();
		hText->load("..//Bmps//grass.bmp", glm::u8vec3(0, 0, 0), 0);

		gObjects.push_back(new Hierba(100));
		gObjects.back()->setTexture(hText);
	}
	else if (id == 8) {

		Texture* fotoText = new Texture();
		fotoText->loadColorBuffer(IG1App::s_ig1app.getWidht(), IG1App::s_ig1app.getHeigth(), GL_FRONT);

		gObjects.push_back(new Foto(100));
		gObjects.back()->setTexture(fotoText);
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
		gObjects.push_back(new Estrella3D(80, 8, 150,-100, 150,-100));
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
		hText->load("..//Bmps//grass.bmp", glm::u8vec3(0, 0, 0), 0);

		gObjects.push_back(new Hierba(100,80,50,-80));
		gObjects.back()->setTexture(hText);
		
		//Foto
		Texture* fotoText = new Texture();
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
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

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
	cam.upload();

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



