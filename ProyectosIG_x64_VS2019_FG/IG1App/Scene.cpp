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
		auto cub = new CuboRGB(200.);

		gObjects.push_back(cub);

		cub->setModelMat(translate(cub->modelMat(), dvec3(100, 100, 100)));
	}
	else if (mId == 2)
	{
		Texture* t = new Texture();
		t->load("..\\Bmps\\baldosaC.bmp");
		gTextures.push_back(t);

		Suelo* s = new Suelo(800., 4);
		s->SetTexture(t);

		gObjects.push_back(s);
	}
	else if (mId == 3)
	{
		Texture* t = new Texture();
		Texture* u = new Texture();
		t->load("..\\Bmps\\container.bmp");
		u->load("..\\Bmps\\papelE.bmp");
		gTextures.push_back(t);
		gTextures.push_back(u);

		ContornoCaja* s = new ContornoCaja(200.);
		s->SetTexture(t);
		s->SetTexture2(u);

		

		gObjects.push_back(s);
	}
	else if (mId == 4)
	{
		Texture* t = new Texture();
		t->load("..\\Bmps\\baldosaP.bmp");
		gTextures.push_back(t);

		Estrella3D* e = new Estrella3D(200., 8, 200.);
		e->SetTexture(t);


		gObjects.push_back(e);
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

	for (Texture* tex : gTextures)
	{
		delete tex;  tex = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.2, 0.2, 0.2, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glDisable(GL_TEXTURE_2D);
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


