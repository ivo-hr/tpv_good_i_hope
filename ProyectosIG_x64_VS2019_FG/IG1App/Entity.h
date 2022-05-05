//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Texture.h"
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

	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	glm::dvec4 const& getColor() const { return mColor; };
	void setColor(glm::dvec4 const& mcol) { mColor = mcol; };

	void SetTexture(Texture* tex) { mTexture = tex; };
	void SetTexture2(Texture* tex) { mTexture2 = tex; };
	
protected:

	Texture* mTexture = nullptr;
	Texture* mTexture2 = nullptr;

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;		//colo
	glm::vec3 vec3Color;	//colo
	
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
	double triAngl = 0;
public:
	explicit TriangleRGB();
	~TriangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() override;
};
class TriangleFict : public TriangleRGB
{
	double triAngl = 0;
public:
	explicit TriangleFict() {};
	~TriangleFict() {};
	virtual void update() override;
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

//-------------------------------------------------------------------------

class CuboRGB : public Abs_Entity
{
public:
	double cubAngl = 0;
	int axis = 0;
	explicit CuboRGB(GLdouble longitud);
	~CuboRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update();
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble longitud, GLuint repes);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class ContornoCaja : public Abs_Entity
{
public:
	explicit ContornoCaja(GLdouble longitud);
	~ContornoCaja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Estrella3D : public Abs_Entity
{
	Mesh* mMesh2 = nullptr;
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	double rotAngl = 0;

	void update();
};

//-------------------------------------------------------------------------

class Cristalera : public Abs_Entity
{
public:
	explicit Cristalera(GLdouble longitud, GLdouble h);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

//-------------------------------------------------------------------------

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() override;

};

//-------------------------------------------------------------------------

class AlaTIE : public Abs_Entity
{
public:
	explicit AlaTIE(GLdouble dist, GLdouble tam);
	~AlaTIE();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

//------------------------------------------------------------
class Esfera : public Abs_Entity
{
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m);
	~Esfera();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

//------------------------------------------------------------



class QuadricEntity : public Abs_Entity
{
public:

	QuadricEntity();
	~QuadricEntity();

	void SetColor(GLfloat r, GLfloat g, GLfloat b) { vec3Color = glm::vec3(r/255, g/255, b/255); };

protected:
	GLUquadricObj* qObj;
};

class QuadricSphere : public QuadricEntity
{
public:
	QuadricSphere(GLdouble radius, GLint res);
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble r;
	GLint res;

};
class QuadricCylinder : public QuadricEntity
{
public:
	QuadricCylinder(GLdouble h, GLdouble radius, GLdouble r, GLint res);
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble r, rr;
	GLdouble h;
	GLint res;

};
class QuadricDisk : public QuadricEntity
{
public:
	QuadricDisk(GLfloat innerRadius, GLfloat outerRadius, GLuint reso);
	void render(glm::dmat4 const& modelViewMat) const;

protected:
	GLdouble inR, ouR;
	GLint res;
};
class QuadricPartialDisk : public QuadricEntity
{

};

//--------------------------------------------------------------------

class CompoundEntity : public Abs_Entity 
{
public:
	CompoundEntity();
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void addEntity(Abs_Entity* ae);

protected:
	std::vector<Abs_Entity*> gObjects;
};

class TIEAvanzado : public CompoundEntity
{
public:
	TIEAvanzado();
	TIEAvanzado(float size);
	~TIEAvanzado();
};
//--------------------------------------------------------------
class TrianguloNodoFict : public CompoundEntity
{
public:
	TrianguloNodoFict();
	~TrianguloNodoFict();

	virtual void update() override;
};


#endif //_H_Entities_H_