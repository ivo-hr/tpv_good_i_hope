//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(1.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	glm::dvec4 const& getColor() const { return mColor; };
	void setColor(glm::dvec4 const& mcol) { mColor = mcol; };
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;		//colo
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class TriangleRGB : public Abs_Entity
{
public:
	explicit TriangleRGB();
	~TriangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class RegularPolygon : public Abs_Entity
{
public:
	explicit RegularPolygon(GLdouble l, GLuint vert, glm::dvec4 color);
	~RegularPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};



//-------------------------------------------------------------------------

class Rectangulo : public Abs_Entity
{
public:
	explicit Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Cubo : public Abs_Entity
{
public:
	explicit Cubo(GLdouble longitud);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

#endif //_H_Entities_H_