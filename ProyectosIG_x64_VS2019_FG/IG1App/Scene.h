//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Texture.h"
#include "Camera.h"
#include "Entity.h"
#include "Light.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:

	std::vector<Texture*> gTextures;	//Recursos compartidos

	Scene() : mId(0) {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;

	void SetState(int id);

	virtual void update();

	void rota();

	void orbita();

	void enciendeLuz(int luz, bool on);
	
protected:

	CompoundEntity* compCaza;
	int mId;
	GLdouble circRad = 300.;
	void free();
	void setGL();
	void resetGL();

	void sceneDirLight(Camera const& cam) const;
	void setLights();
	void uploadLights(Camera const& cam) const;
	DirLight* dirLight = nullptr;
	PosLight* posLight = nullptr;
	SpotLight* spotLight = nullptr;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gTransObjects;  // Entities (graphic objects) of the scene
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

