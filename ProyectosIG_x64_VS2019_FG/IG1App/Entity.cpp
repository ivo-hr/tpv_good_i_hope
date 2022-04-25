#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB() : triAngl(0)
{
	mMesh = Mesh::createTriangleRGB();
}

TriangleRGB::~TriangleRGB()
{
	delete mMesh; mMesh = nullptr;
}

void TriangleRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_FILL);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}

void TriangleRGB::update()
{
	
	
	mModelMat = rotate(mModelMat, triAngl, dvec3(0, 0, 1));		//"Unrotate" the triangle to go to center
	
	mModelMat = translate(mModelMat, dvec3(-300, 0, 0));	//Go to center duh

	mModelMat = rotate(mModelMat, 0.02, dvec3(0, 0, 1));	//Rotate for translation to next point

	mModelMat = translate(mModelMat, dvec3(+300, 0, 0));	//Translation to next point

	triAngl += 0.1;

	mModelMat = rotate(mModelMat, - triAngl, dvec3(0, 0, 1));	//"Re-rotate" the triangle

	
	// sus
}

RegularPolygon::RegularPolygon(GLdouble l, GLuint vert, glm::dvec4 color)
{
	mMesh = Mesh::generaPoligonoRegular(vert, l);
	setColor(color);
}

RegularPolygon::~RegularPolygon()
{
	delete mMesh; mMesh = nullptr;
}

void RegularPolygon::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		upload(aMat);
		mMesh->render();
		glColor3d(0., 0., 0.);
	}
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectangulo(w, h, 0);
}

Rectangulo::~Rectangulo()
{
	delete mMesh; mMesh = nullptr;
}

void Rectangulo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		glPolygonMode(GL_BACK, GL_FILL);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_LINE);

		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

Cubo::Cubo(GLdouble longitud)
{
	mMesh = IndexMesh::generaCuboConTapasIndexado(longitud);
}

Cubo::~Cubo()
{
	delete mMesh; mMesh = nullptr;
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_POINT);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);

		glColor3d(0.7, 0., 0.);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}

CuboRGB::CuboRGB(GLdouble longitud)
{
	mMesh = Mesh::generaCuboRGB(longitud);
}

CuboRGB::~CuboRGB()
{
	delete mMesh; mMesh = nullptr;
}

void CuboRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_BACK, GL_POINT);

		glPolygonMode(GL_FRONT, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

void CuboRGB::update()
{
	if (axis == 0) {
		if (cubAngl >= 3.125) {
			axis = 1;
			cubAngl = 0.;
		}
		else {
			mModelMat = translate(mModelMat, dvec3(-100, -100, 0));	//Go to center duh

			mModelMat = rotate(mModelMat, 0.02, dvec3(0, 0, 1));	//Rotate for translation to next point
			cubAngl += 0.02;
			mModelMat = translate(mModelMat, dvec3(+100, +100, 0));	//Translation to next point
		}
	}
	else if (axis == 1) {
		if (cubAngl >= 3.125) {
			axis = 2;
			cubAngl = 0.;
		}
		else {
			mModelMat = translate(mModelMat, dvec3(0, -100, -100));	//Go to center duh

			mModelMat = rotate(mModelMat, 0.02, dvec3(1, 0, 0));	//Rotate for translation to next point
			cubAngl += 0.02;
			mModelMat = translate(mModelMat, dvec3(0, +100, +100));	//Translation to next point
		}

	}
	else if (axis == 2) {
		if (cubAngl >= 3.125) {
			axis = 0;
			cubAngl = 0.;
		}
		else {
			mModelMat = translate(mModelMat, dvec3(-100, 0, -100));	//Go to center duh

			mModelMat = rotate(mModelMat, -0.02, dvec3(0, 1, 0));	//Rotate for translation to next point
			cubAngl += 0.02;
			mModelMat = translate(mModelMat, dvec3(+100, 0, +100));	//Translation to next point
		}

	}
	// sus
}

Suelo::Suelo(GLdouble longitud, GLuint repes)
{
	mMesh = Mesh::generaRectanguloTexCor(longitud, longitud, repes, repes, 0);
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();
		glColor4d(1, 1, 1, 1);
	}
}

ContornoCaja::ContornoCaja(GLdouble longitud)
{
	mMesh = Mesh::generaContCajaTexCor(longitud);
}

ContornoCaja::~ContornoCaja()
{
	delete mMesh; mMesh = nullptr;
}

void ContornoCaja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();

		glCullFace(GL_FRONT);

		mTexture2->bind(GL_MODULATE);
		mMesh->render();
		mTexture2->unbind();

		glDisable(GL_CULL_FACE);

		glColor4d(1, 1, 1, 1);
	}
}



Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generaEstrella3DTexCor(re, np, h);
	mMesh2 = Mesh::generaEstrella3DTexCor(re, np, -h);
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mMesh2->render();
		mTexture->unbind();
		glColor4d(1, 1, 1, 1);
	}
}

void Estrella3D::update()
{
	mModelMat = rotate(mModelMat, rotAngl, dvec3(0, 0, 1));		//"Unrotate" the z axis



	mModelMat = rotate(mModelMat, 0.02, dvec3(0, 1, 0));	//Rotate y axis


	rotAngl += 0.1;

	mModelMat = rotate(mModelMat, -rotAngl, dvec3(0, 0, 1));	//"Re-rotate" z axis
}


Cristalera::Cristalera(GLdouble longitud, GLdouble h)
{
	mMesh = Mesh::generaCristaleraTexCor(longitud, h);
}

Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
}

void Cristalera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();
		glColor4d(1, 1, 1, 0.5);
	}
}

Foto::Foto(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1, 0.2);

	mTexture = new Texture();
}

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glColor4dv(value_ptr(mColor));

		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();

		glColor4d(1, 1, 1, 1);
	}
}

void Foto::update()
{
	mTexture->loadColourBuffer(GLUT_WINDOW_WIDTH * 7, GLUT_WINDOW_HEIGHT * 7, GL_FRONT);
}

AlaTIE::AlaTIE(GLdouble dist, GLdouble tam)
{
	mMesh = Mesh::generaAlaTIE(dist, tam);
	mTexture = new Texture();
}

AlaTIE::~AlaTIE()
{
	delete mMesh; mMesh = nullptr;
}

void AlaTIE::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_BACK, GL_FILL);
		glPolygonMode(GL_FRONT, GL_FILL);

		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();

		glColor4d(1, 1, 1, 1);

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}


//=========================================================QUADIRC====================================

QuadricEntity::QuadricEntity()
{
	qObj = gluNewQuadric();
}

QuadricEntity::~QuadricEntity()
{
	gluDeleteQuadric(qObj);
}

QuadricSphere::QuadricSphere(GLdouble radius, GLint res)
{
	r = radius;
	this->res = res;
}

void QuadricSphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);

		
	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(vec3Color.x, vec3Color.y, vec3Color.z);

	//Modo de dibujar
	gluQuadricDrawStyle(qObj, GL_FILL);

	gluSphere(qObj, r, res, res);

	glColor3f(1, 1, 1);
}

QuadricCylinder::QuadricCylinder(GLdouble h, GLdouble radius, GLdouble r, GLint res)
{
	this->h = h;
	this->r = radius;
	this->rr = r;
	this->res = res;
}

void QuadricCylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);

	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(vec3Color.x, vec3Color.y, vec3Color.z);

	//Modo de dibujar
	gluQuadricDrawStyle(qObj, GL_FILL);

	gluCylinder(qObj, r, rr, h, res, res);

	glColor3f(1, 1, 1);
}

QuadricDisk::QuadricDisk(GLfloat innerRadius, GLfloat outerRadius, GLuint reso)
{
	inR = innerRadius;
	ouR = outerRadius;
	res = reso;
}

void QuadricDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);

	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(vec3Color.x, vec3Color.y, vec3Color.z);

	//Modo de dibujar
	gluQuadricDrawStyle(qObj, GL_FILL);

	gluDisk(qObj, inR, ouR, res, res);

	glColor3f(1, 1, 1);
}


CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* a : gObjects)
	{
		delete a;
	}
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{

	glm::dmat4 aMat =  modelViewMat * mModelMat;

	upload(aMat);

	for (Abs_Entity* a : gObjects)
	{
		a->render(aMat);
	}
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

TIEAvanzado::TIEAvanzado()
{

	//==================CUERPO===================

	auto cuerpo = new QuadricSphere(75, 40);
	cuerpo->SetColor(0, 65, 106);
	addEntity(cuerpo);

	//==================CABINA===================

	auto cabina = new QuadricCylinder(20, 45, 45, 40);
	cabina->SetColor(0, 65, 106);
	cabina->setModelMat(translate(cabina->modelMat(), dvec3(60, 0, 0)));
	cabina->setModelMat(rotate(cabina->modelMat(), 3.141516 / 2, dvec3(0, 1, 0)));
	addEntity(cabina);

	//==================CRISTAL===================

	auto cristal = new QuadricDisk(0, 45, 40);
	cristal->SetColor(0, 65, 106);
	cristal->setModelMat(translate(cristal->modelMat(), dvec3(80, 0, 0)));
	cristal->setModelMat(rotate(cristal->modelMat(), 3.141516 / 2, dvec3(0, 1, 0)));
	addEntity(cristal);

	//==================ESCUDOS===================

	Texture* t = new Texture();
	t->load("..\\Bmps\\Noche.bmp", 150);
	auto escudo = new AlaTIE(120, 100);
	escudo->SetTexture(t);
	addEntity(escudo);
	auto escudo2 = new AlaTIE(-120, 100);
	escudo2->SetTexture(t);
	addEntity(escudo2);

	//==================EJE===================

	auto eje = new QuadricCylinder(240, 20, 20, 40);
	eje->setModelMat(translate(eje->modelMat(), dvec3(0, 0, -120)));
	eje->SetColor(0, 65, 106);
	addEntity(eje);
}


TIEAvanzado::TIEAvanzado(float size)
{

	//==================CUERPO===================

	auto cuerpo = new QuadricSphere(75 * size, 40);
	cuerpo->SetColor(0, 65, 106);
	addEntity(cuerpo);

	//==================CABINA===================

	auto cabina = new QuadricCylinder(20 * size, 45 * size, 45 * size, 40);
	cabina->SetColor(0, 65, 106);
	cabina->setModelMat(translate(cabina->modelMat(), dvec3(60 * size, 0, 0)));
	cabina->setModelMat(rotate(cabina->modelMat(), 3.141516 / 2, dvec3(0, 1, 0)));
	addEntity(cabina);

	//==================CRISTAL===================

	auto cristal = new QuadricDisk(0, 45 * size, 40 * size);
	cristal->SetColor(0, 65, 106);
	cristal->setModelMat(translate(cristal->modelMat(), dvec3(80 * size, 0, 0)));
	cristal->setModelMat(rotate(cristal->modelMat(), 3.141516 / 2, dvec3(0, 1, 0)));
	addEntity(cristal);

	//==================ESCUDOS===================

	Texture* t = new Texture();
	t->load("..\\Bmps\\Noche.bmp", 150);
	auto escudo = new AlaTIE(120 * size, 100 * size);
	escudo->SetTexture(t);
	addEntity(escudo);
	auto escudo2 = new AlaTIE(-120 * size, 100 * size);
	escudo2->SetTexture(t);
	addEntity(escudo2);

	//==================EJE===================

	auto eje = new QuadricCylinder(240 * size, 20 * size, 20 * size, 40);
	eje->setModelMat(translate(eje->modelMat(), dvec3(0, 0, -120 * size)));
	eje->SetColor(0, 65, 106);
	addEntity(eje);
}

TIEAvanzado::~TIEAvanzado()
{
}

TrianguloNodoFict::TrianguloNodoFict()
{
	auto triang = new TriangleFict();
	triang->setModelMat(translate(triang->modelMat(), dvec3(300, 0, 0)));
	addEntity(triang);
}

TrianguloNodoFict::~TrianguloNodoFict()
{
}

void TrianguloNodoFict::update()
{
	mModelMat = rotate(mModelMat, 0.02, dvec3(0, 0, 1));
	for (Abs_Entity* ent : gObjects)
	{
		ent->update();
	}
}

void TriangleFict::update()
{
	mModelMat = rotate(mModelMat, -0.04, dvec3(0, 0, 1));
}
