#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data

      if (vTexCoors.size() > 0)
      {
          glEnableClientState(GL_TEXTURE_COORD_ARRAY);
          glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoors.data());
      }


    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = num;
    mesh->vVertices.reserve(mesh->mNumVertices);

    long double sect = (4 * glm::acos(0.0)) / num;  //  2*Pi / n� of sides

    for (int i = 0; i < num; i++) {

        mesh->vVertices.emplace_back(r * -glm::sin(sect * i), r * glm::cos(sect * i), 0.);
    }

    return mesh;
}
Mesh* Mesh::createTriangleRGB()
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 3;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0., 50., 0.);
    mesh->vVertices.emplace_back(-50., -50., 0.);
    mesh->vVertices.emplace_back(50., -50., 0.);


    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vColors.emplace_back(1.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);

    return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h, GLdouble d)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(w / 2., d, h / 2.);
    mesh->vVertices.emplace_back(w / 2., d, -h / 2.);
    mesh->vVertices.emplace_back(-w / 2., d, h / 2.);
    mesh->vVertices.emplace_back(-w / 2., d, -h / 2.);

    return mesh;
}
Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(w / 2., h / 2., 0.);
    mesh->vVertices.emplace_back(-w / 2., h / 2., 0.);
    mesh->vVertices.emplace_back(-w / 2., -h / 2., 0.);
    mesh->vVertices.emplace_back(w / 2., -h / 2., 0.);


    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}
//---------------------------------------------------------
Mesh* Mesh::generaCubo(GLdouble longitud)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 14;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);

    return mesh;
}

Mesh* Mesh::generaCuboRGB(GLdouble longitud)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 36;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);


    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);

    //---------------------------------

    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);

    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);


    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);

    //-------------------------------------

    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);


    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);

    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);

    mesh->vColors.reserve(mesh->mNumVertices);

    for (int i = 0;i < mesh->mNumVertices; i++){

        if (i < 12){
            mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); //r
        }
        else if (i < 24){
            mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); //g
        } 
        else{
            mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); //b
        } 
    }

    return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh, GLdouble d)
{
    Mesh* m = generaRectangulo(w, h, d);

    m->vTexCoors.reserve(m->mNumVertices);

    m->vTexCoors.emplace_back(rw, 0);
    m->vTexCoors.emplace_back(rw, rh);
    m->vTexCoors.emplace_back(0, 0);
    m->vTexCoors.emplace_back(0, rh);

    return m;
}

Mesh* Mesh::generaContCaja(GLdouble longitud)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., -longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., longitud / 2., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., -longitud / 2., longitud / 2.);

    return mesh;
}

Mesh* Mesh::generaContCajaTexCor(GLdouble longitud)
{
    Mesh* m = generaContCaja(longitud);

    m->vTexCoors.reserve(m->mNumVertices);
    
    m->vTexCoors.emplace_back(0, 1);
    m->vTexCoors.emplace_back(0, 0);
    m->vTexCoors.emplace_back(1, 1);
    m->vTexCoors.emplace_back(1, 0);
    m->vTexCoors.emplace_back(2, 1);
    m->vTexCoors.emplace_back(2, 0);
    m->vTexCoors.emplace_back(3, 1);
    m->vTexCoors.emplace_back(3, 0);
    m->vTexCoors.emplace_back(4, 1);
    m->vTexCoors.emplace_back(4, 0);

    return m;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;

    mesh->mNumVertices = (np * 2) + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble ri = re/2;

    long double sect = (4 * glm::acos(0.0)) / (np * 2);  //  2*Pi / n� of sides

    mesh->vVertices.emplace_back(0, 0, 0);

    for (int i = 0; i < np * 2; i += 2)
    {
        mesh->vVertices.emplace_back(re * -glm::sin(sect * i), re * glm::cos(sect * i), h);
        mesh->vVertices.emplace_back(ri * -glm::sin(sect * (i + 1)), ri * glm::cos(sect * (i + 1)), h);
    }

    mesh->vVertices.emplace_back(re * -glm::sin(0), re * glm::cos(0), h);

    return mesh;
}



Mesh* Mesh::generaEstrella3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = generaEstrella3D(re, np, h);
    
    mesh->vTexCoors.reserve(mesh->mNumVertices);

    mesh->vTexCoors.emplace_back(0.5, 0.5);

    
    mesh->vTexCoors.emplace_back(0,     0);
    mesh->vTexCoors.emplace_back(0.25,  0);
    mesh->vTexCoors.emplace_back(0.5,   0);
    mesh->vTexCoors.emplace_back(0.75,  0);
    mesh->vTexCoors.emplace_back(1,     0);
    mesh->vTexCoors.emplace_back(1,     0.25);
    mesh->vTexCoors.emplace_back(1,     0.5);
    mesh->vTexCoors.emplace_back(1,     0.75);
    mesh->vTexCoors.emplace_back(1,     1);
    mesh->vTexCoors.emplace_back(0.75,  1);
    mesh->vTexCoors.emplace_back(0.5,   1);
    mesh->vTexCoors.emplace_back(0.25,  1);
    mesh->vTexCoors.emplace_back(0,     1);
    mesh->vTexCoors.emplace_back(0,     0.75);
    mesh->vTexCoors.emplace_back(0,     0.5);
    mesh->vTexCoors.emplace_back(0,     0.25);


    mesh->vTexCoors.emplace_back(0, 0);

    return mesh;
}

Mesh* Mesh::generaCristalera(GLdouble longitud, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(longitud / 2., h, longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., 0., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., h, -longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., 0., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., h, -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., 0., -longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., h, longitud / 2.);
    mesh->vVertices.emplace_back(-longitud / 2., 0., longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., h, longitud / 2.);
    mesh->vVertices.emplace_back(longitud / 2., 0., longitud / 2.);

    return mesh;
}

Mesh* Mesh::generaCristaleraTexCor(GLdouble longitud, GLdouble h)
{
    Mesh* m = generaCristalera(longitud, h);

    m->vTexCoors.reserve(m->mNumVertices);

    m->vTexCoors.emplace_back(0, 1);
    m->vTexCoors.emplace_back(0, 0);
    m->vTexCoors.emplace_back(1, 1);
    m->vTexCoors.emplace_back(1, 0);
    m->vTexCoors.emplace_back(2, 1);
    m->vTexCoors.emplace_back(2, 0);
    m->vTexCoors.emplace_back(3, 1);
    m->vTexCoors.emplace_back(3, 0);
    m->vTexCoors.emplace_back(4, 1);
    m->vTexCoors.emplace_back(4, 0);

    return m;
}
