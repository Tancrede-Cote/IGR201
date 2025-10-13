#include "mesh.h"

float spheric2cartx(float r,float theta,float phi){
    return r*sinf(theta)*cosf(phi);
}

float spheric2carty(float r,float theta,float phi){
    return r*sinf(theta)*sinf(phi);
}

float spheric2cartz(float r,float theta,float phi){
    return r*cosf(theta);
}

void Mesh::init(){
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);
    size_t vertexBufferSize = sizeof(float)*(m_vertexPositions.size());
    glGenBuffers(1, &m_posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, m_vertexPositions.data(), GL_DYNAMIC_READ);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &m_normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, m_vertexNormals.data(), GL_DYNAMIC_READ);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);

    size_t indexBufferSize = sizeof(unsigned int)*m_triangleIndices.size();
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, m_triangleIndices.data(), GL_DYNAMIC_READ);

    glBindVertexArray(0); // deactivate the VAO for now, will be activated again when rendering
}

void Mesh::render() {
    glm::mat4 model = glm::translate(glm::scale(glm::mat4(1),glm::vec3(scale)), origin);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    const glm::vec3 col = color; 
    glUniform3f(glGetUniformLocation(m_program, "col"), col[0], col[1], col[2]);
    
    glBindVertexArray(m_vao);     // activate the VAO storing geometry data
    glDrawElements(GL_TRIANGLES, m_triangleIndices.size(), GL_UNSIGNED_INT, 0); // Call for rendering: stream the current GPU geometry through the current GPU program
}

std::shared_ptr<Mesh> Mesh::genSphere(const size_t _resolution){
    int resolution = (int)_resolution;
    std::shared_ptr<Mesh> sphere = std::make_shared<Mesh>();
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexPositions.push_back(1.f); // le sommet
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexNormals.push_back(0.f);
    sphere->m_vertexNormals.push_back(1.f); // le sommet
    sphere->m_vertexNormals.push_back(0.f);
    float theta = M_PI/(float)resolution;
    int i = 0;
    while(theta<M_PI){
        float phi = 0.f;
        int j = 1;
        while(phi<2*M_PI){
            sphere->m_vertexPositions.push_back(spheric2cartx(1.f,theta,phi));
            sphere->m_vertexPositions.push_back(spheric2cartz(1.f,theta,phi));
            sphere->m_vertexPositions.push_back(spheric2carty(1.f,theta,phi));
            sphere->m_vertexNormals.push_back(spheric2cartx(1.f,theta,phi));
            sphere->m_vertexNormals.push_back(spheric2cartz(1.f,theta,phi));
            sphere->m_vertexNormals.push_back(spheric2carty(1.f,theta,phi));
            if(!i){
                sphere->m_triangleIndices.push_back((unsigned int)0);
                sphere->m_triangleIndices.push_back((unsigned int)((j+resolution-2)%resolution+1));
                sphere->m_triangleIndices.push_back((unsigned int)j);
            } else {
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+((j-1+resolution)%resolution)));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+(j%resolution+1)));
            }
            phi+=2*M_PI/resolution;
            j++;
        }
        theta+=M_PI/resolution;
        i++;
    }
    for (int l=1; l<=resolution; l++){
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-2)+l));
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-2)+l%resolution+1));
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-1)+1));
    }
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexPositions.push_back(-1.f); // le bas
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexNormals.push_back(0.f);
    sphere->m_vertexNormals.push_back(-1.f); // le bas
    sphere->m_vertexNormals.push_back(0.f);
    // for(int k=0; k<sphere->m_vertexPositions.size()/3;k++){
    //     // std::cout<<sphere->m_vertexPositions[3*k]*sphere->m_vertexPositions[3*k]+sphere->m_vertexPositions[3*k+1]*sphere->m_vertexPositions[3*k+1]+sphere->m_vertexPositions[3*k+2]*sphere->m_vertexPositions[3*k+2]<<std::endl;
    //     std::cout<<"la face "<<sphere->m_triangleIndices[3*k]<<", "<<sphere->m_triangleIndices[3*k+1]<<", "<<sphere->m_triangleIndices[3*k+2]<<" donne la normale "<<sphere->m_vertexNormals[3*k]<<", "<<sphere->m_vertexNormals[3*k+1]<<", "<<sphere->m_vertexNormals[3*k+2]<<std::endl;
    // }
    // int k = 0;
    // for (auto& index : sphere->m_vertexPositions){
    //     k++;
    //     std::cout<<index<<" ";
    //     if (k%3 == 0){
    //         std::cout<<std::endl;
    //     }
    // }

    return sphere;
}