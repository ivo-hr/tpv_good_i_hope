#include "Light.h"
#include <gtc/type_ptr.hpp> //puede que sea .hpp :v

GLuint Light::cont = 0;
Light::Light()
{
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}
}

void Light::uploadL()
{
	// Transfiere las caracter�sticas de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}
