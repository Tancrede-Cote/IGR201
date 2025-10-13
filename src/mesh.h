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
unsigned int verticesCount(){return m_triangleIndices.size();}
static std::shared_ptr<Mesh> genSphere(const size_t resolution); // should generate a unit sphere
// ...
private:
std::vector<float> m_vertexPositions;
std::vector<float> m_vertexNormals;
std::vector<unsigned int> m_triangleIndices;
GLuint m_vao = 0;
GLuint m_posVbo = 0;
GLuint m_normalVbo = 0;
GLuint m_ibo = 0;
GLuint m_program = 0;
// ...
};