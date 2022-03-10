#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>


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
		Texture* t = new Texture();
		t->load("..//Bmps//baldosaC.bmp");
		gTextures.push_back(t);
		gObjects.push_back(new Suelo());
		gObjects.back()->setTexture(t);

	}
	else if (id == 3) {

		Texture* a = new Texture();
		a->load("..//Bmps//container.bmp");
		gTextures.push_back(a);
		gObjects.push_back(new ContornoCaja(50));
		gObjects.back()->setTexture(a);
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
}
//void Scene::update()
//{
//	/*for (auto g : gObjects)
//		g->update();*/
//}
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
}



