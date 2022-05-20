 #include "Material.h"
#include <gtc/type_ptr.hpp>

void Material::upload()
{
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
}

void Material::setCopper()
{
	ambient = { 0.19125, 0.0735, 0.0225, 1 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1 };
	specular = { 0.256777, 0.137622, 0.086014, 1 };
	expF = 12.8;
}

void Material::setGold()
{
	ambient = { 0.24725, 0.1995, 0.0745, 1 };
	diffuse = { 0.75164, 0.60648, 0.22648, 1 };
	specular = { 0.628281, 0.555802, 0.366065, 1 };
	expF = 0.4 * 128;
}

void Material::setObsidian()
{
	ambient = { 0.05375, 0.05, 0.06625, 1 };
	diffuse = { 0.18275, 0.17, 0.22525, 1 };
	specular = { 0.332741, 0.328634, 0.346435, 1 };
	expF = 0.3 * 128;
}
