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
	mMesh = Mesh::generaRectangulo(w, h);
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
	mMesh = Mesh::generaCubo(longitud);
}

Cubo::~Cubo()
{
	delete mMesh; mMesh = nullptr;
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glFrontFace(GL_CW);

		glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);

		glColor3d(0., 0., 0.);

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
	mMesh = Mesh::generaRectanguloTexCor(longitud, longitud, repes, repes);
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
		
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);


		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();
		
		glPolygonMode(GL_FRONT, GL_POINT);
		glPolygonMode(GL_BACK, GL_FILL);

		mTexture2->bind(GL_MODULATE);
		mMesh->render();
		mTexture2->unbind();
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