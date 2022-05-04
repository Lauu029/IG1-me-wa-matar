//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>
#include "Texture.h"
#include "Light.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { delete dirLight; dirLight = nullptr; free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;
	//virtual void update();
	
	void setScene(int id);
	void setId(int _id);
	void Update();
	void savePhoto();
	void sceneDirLight(Camera const& cam)const;
	void rota();
	void orbita();
	void setLights();
	void DirLightAble(bool active);

	void uploadLights(Camera const& cam)const;
protected:
	CompoundEntity* rotacionTie;
	void free();
	void setGL();
	void resetGL();
	int id=0;
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gTranslucidObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
	std::vector<Material*> gMaterials;

	DirLight* dirLight;
	PosLight* posLight;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

