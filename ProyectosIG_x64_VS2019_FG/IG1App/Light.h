//#pragma once
#ifndef _H_Light_H_
#define _H_Light_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"
#include <string>

//-------------------------------------------------------------------------

class Light { // Abstract class
public:
	Light();
	virtual ~Light() { disable(); }

	void uploadL();

	virtual void upload(glm::dmat4 const& modelViewMat) const = 0; 

	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };

	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };

	void setAmb (glm::fvec4 amb)  { ambient  = amb;  uploadL(); };
	void setDiff(glm::fvec4 diff) { diffuse  = diff; uploadL(); };
	void setSpec(glm::fvec4 spec) { specular = spec; uploadL(); };

protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido

	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient =  { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse =  { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	glm::fvec4 posDir =   { 0, 0, 1, 0 };

	// Añade setter’s para cambiar el valor de los atributos lumínicos
};

#endif //_H_Light_H_