#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

#pragma once

float spheric2cartx(float,float,float);
float spheric2carty(float,float,float);
float spheric2cartz(float,float,float);


class Mesh {
public:
void init();
// should properly set up the geometry buffer
void render(); // should be called in the main rendering loop
static std::shared_ptr<Mesh> genSphere(const size_t resolution); // should generate a unit sphere
// ...
private:
std::vector<float> m_vertexPositions;
std::vector<float> m_vertexNormals;
std::vector<unsigned int> m_triangleIndices;
std::vector<float> m_vertexTexCoords;
GLuint m_texCoordVbo = 0;
GLuint m_vao = 0;
GLuint m_posVbo = 0;
GLuint m_normalVbo = 0;
GLuint m_ibo = 0;
// ...
};

class Stellar {
private:
std::shared_ptr<Mesh> body;
glm::vec3 origin{};
glm::vec3 color{};
glm::vec3 lighting{};
glm::vec3 lcolor{};
float scale=1.f;
GLuint m_program = 0;
public:
Stellar(){body=Mesh::genSphere(16);}
Stellar(const size_t res,GLuint g_program,glm::vec3 o,glm::vec3 col, glm::vec3 l, glm::vec3 lc, float s) : m_program(g_program), origin(o), color(col), lighting(l), lcolor(lc), scale(s) {body=Mesh::genSphere(res);body->init();}
void setProgram(GLuint& g_program){m_program=g_program;}
void setOrigin(glm::vec3 o){origin=o;}
glm::vec3 getOrigin(){return origin;}
void setColor(glm::vec3 col){color=col;}
void setScale(float s){scale=s;}
void setLighting(glm::vec3 l){lighting=l;}
void render();
};