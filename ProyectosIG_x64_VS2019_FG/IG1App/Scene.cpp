#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	glEnable(GL_DEPTH_TEST);
	// allocate memory and load resources
    // Lights
	dirLight = new DirLight();
	posLight = new PosLight();
	spotLight = new SpotLight();

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
		auto cil = new TIEAvanzado();
		gObjects.push_back(cil);
	}
	else if (mId == 2)
	{
		glClearColor(0., 0., 0., 1.0);  // background color (alpha=1 -> opaque)

		auto tatooine = new QuadricSphere(300, 80);
		tatooine->SetColor(255, 233, 200);
		gObjects.push_back(tatooine);

		auto comp = new CompoundEntity();

		auto TIE = new TIEAvanzado(0.1f);
		TIE->setModelMat(translate(TIE->modelMat(), dvec3(0, 320, 0)));
		comp->addEntity(TIE);

		gObjects.push_back(comp);

		compCaza = comp;
	}
	else if (mId == 3)
	{
		Cubo* s = new Cubo(200.);
		gObjects.push_back(s);
	}
	else if (mId == 4)
	{
		TrianguloNodoFict* ii = new TrianguloNodoFict();

		gObjects.push_back(ii);
	}
	else if (mId == 5)
	{
		
		Texture* t = new Texture();
		t->load("..\\Bmps\\windowV.bmp", 150);
		gTextures.push_back(t);

		Cristalera* e = new Cristalera(400., 100.);
		e->SetTexture(t);


		gTransObjects.push_back(e);
	}
	else if (mId == 6)
	{
		auto esfera = new Esfera(100, 30, 30);

		auto mat = new Material();
		mat->setGold();
		esfera->setMaterial(mat);

		esfera->setModelMat(translate(esfera->modelMat(), dvec3(0, 0, 250)));

		gObjects.push_back(esfera);

		//-----------------------------------------------------------------------

		auto esferaSinMat = new Esfera(100, 30, 30);

		esferaSinMat->setColor(dvec4(0.8, 0.8, 0.05, 1.));

		esferaSinMat->setModelMat(translate(esferaSinMat->modelMat(), dvec3(250, 0, 0)));

		gObjects.push_back(esferaSinMat);
	}
	else if (mId == 7)
	{
		gObjects.push_back(new Toro(50, 100, 40, 20));
	}
	
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Abs_Entity* el : gTransObjects)
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

void Scene::sceneDirLight(Camera const& cam) const
{
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
void Scene::setLights(Camera const& cam, fvec3 pos) const
{
	glEnable(GL_LIGHTING);

	dirLight->setPosDir(pos);
	posLight->setPosDir(pos);
	spotLight->setPosDir(pos);

	dirLight->setAmb(fvec4(0, 0, 0, 1));
	posLight->setAmb(fvec4(0, 0, 0, 1));
	spotLight->setAmb(fvec4(0, 0, 0, 1));

	dirLight->setDiff(fvec4(1, 1, 1, 1));
	posLight->setDiff(fvec4(1, 1, 1, 1));
	spotLight->setDiff(fvec4(1, 1, 1, 1));

	dirLight->setSpec(fvec4(0.5, 0.5, 0.5, 1));
	posLight->setSpec(fvec4(0.5, 0.5, 0.5, 1));
	spotLight->setSpec(fvec4(0.5, 0.5, 0.5, 1));
}

void Scene::uploadLights() const
{
	dirLight->upload();
}


//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	setLights(cam, fvec3(1, 1, 1));
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (Abs_Entity* el : gTransObjects)
	{
		el->render(cam.viewMat());
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
//-------------------------------------------------------------------------

void Scene::SetState(int id){

	if (id != mId) {
		free();

		for (int i = gObjects.size(); i > 0; i--)
			gObjects.pop_back(); 
		for (int i = gTransObjects.size(); i > 0; i--)
			gTransObjects.pop_back();


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

	for (Abs_Entity* obj : gTransObjects)
	{
		obj->update();
	}
}

void Scene::rota()
{
	if (compCaza != nullptr)
	{
		compCaza->setModelMat(rotate(compCaza->modelMat(), -0.1, dvec3(0, 1, 0)));
	}
}

void Scene::orbita()
{
	if (compCaza != nullptr)
	{
		compCaza->setModelMat(rotate(compCaza->modelMat(), -0.1, dvec3(0, 0, 1)));
	}
}

void Scene::enciendeLuz(int luz, bool on)
{
	switch (luz)
	{
	case 0:
		if (on) dirLight->enable();
		else dirLight->disable();
		break;
	case 1:
		if (on) posLight->enable();
		else posLight->disable();
		break;
	case 2:
		if (on) spotLight->enable();
		else spotLight->disable();
		break;

	default:
		break;
	}

}



