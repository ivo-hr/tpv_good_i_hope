//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	static Mesh* generaPoligonoRegular(GLuint num, GLdouble r);

	static Mesh* createTriangleRGB();

	static Mesh* generaRectangulo(GLdouble w, GLdouble h, GLdouble d);

	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);

	static Mesh* generaCubo(GLdouble longitud);
	static Mesh* generaCuboRGB(GLdouble longitud);

	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh, GLdouble d);

	static Mesh* generaContCaja(GLdouble longitud);

	static Mesh* generaContCajaTexCor(GLdouble longitud);

	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaEstrella3DTexCor(GLdouble re, GLuint np, GLdouble h);
	
	static Mesh* generaCristalera(GLdouble longitud, GLdouble h);
	static Mesh* generaCristaleraTexCor(GLdouble longitud, GLdouble h);

	static Mesh* generaAlaTIE(GLdouble dist, GLdouble tam);


	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
	std::vector<glm::dvec3> const& normals() const { return vNormals; };
		
protected:

	std::vector<glm::dvec2> vTexCoors;
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec3> vNormals;	//Normals array
	virtual void draw() const;
};
//-------------------------------------------------------------------------

class IndexMesh : public Mesh 
{
public:
	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);

	virtual void draw() const;

protected:
	GLuint* vIndices = nullptr;
	GLuint mNumIndices = 0;
};

#endif //_H_Scene_H_