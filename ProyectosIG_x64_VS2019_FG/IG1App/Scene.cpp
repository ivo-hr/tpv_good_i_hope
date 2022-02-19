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

	gObjects.push_back(new EjesRGB(400.0));

	if (mId == 0)
	{
		auto tri = new TriangleRGB();
		auto rec = new RectanguloRGB(300.0, 400.0);
		auto cir = new RegularPolygon(circRad, 100, glm::dvec4(1., 0., 1., 1.));
		
		gObjects.push_back(tri);
		gObjects.push_back(rec);
		gObjects.push_back(cir);
		
		tri->setModelMat(translate(tri->modelMat(), dvec3(circRad, 0, 0)));
		
	}
	else if (mId == 1)
	{
		gObjects.push_back(new CuboRGB(200.));
	}

    // Graphics objects (entities) of the scene
	
	//gObjects.push_back(new TriangleRGB());
	//gObjects.push_back(new RegularPolygon(250., 7, glm::dvec4(0., 0., 0., 1.)));
	//gObjects.push_back(new RegularPolygon(250., 3, glm::dvec4(0., 1., 1., 1.)));
	//gObjects.push_back(new RegularPolygon(250., 100, glm::dvec4(1., 0., 1., 1.)));
	//gObjects.push_back(new RectanguloRGB(300.0, 400.0));
	//gObjects.push_back(new Cubo(200.));
	
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.2, 0.2, 0.2, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
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
//-------------------------------------------------------------------------

void Scene::SetState(int id){

	if (id != mId) {
		free();

		for (int i = gObjects.size(); i > 0; i--)
			gObjects.pop_back();

		mId = id;

		init();
	}
}

void Scene::update()
{
	for (Abs_Entity* obj : gObjects )
	{
		obj->update();
	}
}


