#include "mesh.h"

float spheric2cartx(float r,float theta,float phi){
    // return r*sinf(theta)*cosf(phi);
    // return r*cosf(theta);
    return r*sinf(theta)*sinf(phi);
}

float spheric2carty(float r,float theta,float phi){
    // return r*sinf(theta)*sinf(phi);
    // return r*sinf(theta)*cosf(phi);
    return r*cosf(theta);
}

float spheric2cartz(float r,float theta,float phi){
    // return r*cosf(theta);
    // return r*sinf(theta)*sinf(phi);
    return r*sinf(theta)*cosf(phi);
}

float spheric2cartx(glm::vec3 c){
    return c[0]*sinf(c[1])*cosf(c[2]);
}

float spheric2carty(glm::vec3 c){
    return c[0]*sinf(c[1])*sinf(c[2]);
}

float spheric2cartz(glm::vec3 c){
    return c[0]*cosf(c[1]);
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
    size_t vertexTexBufferSize = sizeof(float)*(m_vertexTexCoords.size());
    glGenBuffers(1, &m_texCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexTexBufferSize, m_vertexTexCoords.data(), GL_DYNAMIC_READ);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(2);

    size_t indexBufferSize = sizeof(unsigned int)*m_triangleIndices.size();
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, m_triangleIndices.data(), GL_DYNAMIC_READ);

    glBindVertexArray(0); // deactivate the VAO for now, will be activated again when rendering
}

void Mesh::render() {
    glBindVertexArray(m_vao);     // activate the VAO storing geometry data
    glDrawElements(GL_TRIANGLES, m_triangleIndices.size(), GL_UNSIGNED_INT, 0); // Call for rendering: stream the current GPU geometry through the current GPU program
}

std::shared_ptr<Mesh> Mesh::genSphere(const size_t _resolution){
    int resolution = (int)_resolution;
    std::shared_ptr<Mesh> sphere = std::make_shared<Mesh>();
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexPositions.push_back(1.f); // le sommet
    sphere->m_vertexPositions.push_back(0.f);

    sphere->m_vertexTexCoords.push_back(1.f);
    sphere->m_vertexTexCoords.push_back(0.f);

    sphere->m_vertexNormals.push_back(0.f);
    sphere->m_vertexNormals.push_back(1.f); // le sommet
    sphere->m_vertexNormals.push_back(0.f);
    float theta = M_PI/(float)resolution;
    int i = 0;
    while(theta<M_PI){
        float phi = 0.f;
        int j = 1;
        while(phi<2*M_PI){
            // std::cout<<"phi = "<<phi<<std::endl;
            // std::cout<<"theta = "<<theta<<std::endl;
            // std::cout<<"x = "<<spheric2cartx(1.f,theta,phi)<<std::endl;
            // std::cout<<"y = "<<spheric2carty(1.f,theta,phi)<<std::endl;
            // std::cout<<"z = "<<spheric2cartz(1.f,theta,phi)<<std::endl;
            sphere->m_vertexPositions.push_back(spheric2cartx(1.f,theta,phi));
            sphere->m_vertexPositions.push_back(spheric2carty(1.f,theta,phi));
            sphere->m_vertexPositions.push_back(spheric2cartz(1.f,theta,phi));
            sphere->m_vertexTexCoords.push_back(1-phi/(2*M_PI));
            sphere->m_vertexTexCoords.push_back(theta/M_PI);

            sphere->m_vertexNormals.push_back(spheric2cartx(1.f,theta,phi));
            sphere->m_vertexNormals.push_back(spheric2carty(1.f,theta,phi));
            sphere->m_vertexNormals.push_back(spheric2cartz(1.f,theta,phi));
            if(!i){
                sphere->m_triangleIndices.push_back((unsigned int)0);
                sphere->m_triangleIndices.push_back((unsigned int)j);
                sphere->m_triangleIndices.push_back((unsigned int)((j+resolution-2)%resolution+1));
                // std::cout<<"triangle "<<0<<", "<<(j+resolution-2)%resolution+1<<", "<<j<<std::endl;
            } else {
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+((j-1+resolution)%resolution)));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)(i*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+j));
                sphere->m_triangleIndices.push_back((unsigned int)((i-1)*resolution+(j+1)));
                // // std::cout<<"triangle "<<i*resolution+((j-1+resolution)%resolution)<<", "<<(i-1)*resolution+j<<", "<<i*resolution+j<<std::endl;
                // // std::cout<<"et triangle "<<(i)*resolution+j<<", "<<(i-1)*resolution+j<<", "<<(i-1)*resolution+(j+1)<<std::endl;
            }
            phi+=2*M_PI/(float)resolution;
            j++;
        }
        theta+=M_PI/(float)resolution;
        i++;
    }
    for (int l=1; l<=resolution; l++){
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-2)+l));
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-2)+l%resolution+1));
        sphere->m_triangleIndices.push_back((unsigned int)(resolution*(resolution-1)+1));
        // // std::cout<<"triangle "<<resolution*(resolution-2)+l<<", "<<resolution*(resolution-2)+l%resolution+1<<", "<<resolution*(resolution-1)+1<<std::endl;
    }

    for (auto& coor : sphere->m_triangleIndices){
        // std::cout<<coor<<" ";
    }
    // std::cout<<std::endl;
    sphere->m_vertexPositions.push_back(0.f);
    sphere->m_vertexPositions.push_back(-1.f); // le bas
    sphere->m_vertexPositions.push_back(0.f);

    sphere->m_vertexTexCoords.push_back(0.f);
    sphere->m_vertexTexCoords.push_back(1.f);

    sphere->m_vertexNormals.push_back(0.f);
    sphere->m_vertexNormals.push_back(-1.f); // le bas
    sphere->m_vertexNormals.push_back(0.f);
    // std::cout<<sphere->m_vertexPositions.size()/3<<", "<<sphere->m_vertexTexCoords.size()/2<<", "<<sphere->m_vertexNormals.size()/3<<", "<<sphere->m_triangleIndices.size()/3<<std::endl;
    return sphere;
}

void Stellar::render(){
    //glm::mat4 model = glm::rotate(glm::translate(glm::scale(glm::mat4(1),glm::vec3(scale)), origin),-23.5f*(float)M_PI/180.f,glm::vec3(0.,0.,1.));
    glm::mat4 roty = glm::rotate(glm::mat4(1.f),-(time)*s_os*(float)M_PI/12.f,glm::vec3(0.,1.,0.));
    glm::mat4 temprotx = glm::rotate(glm::mat4(1.f),0.f*(float)M_PI/2.f,glm::vec3(1.,0.,0.));
    glm::mat4 rotx = glm::rotate(glm::mat4(1.f),-0*(float)M_PI/2.f,glm::vec3(1.,0.,0.));
    //// std::cout<<time<<std::endl;
    glm::mat4 rotz = glm::rotate(glm::mat4(1.f),-23.5f*(float)tilted*(float)M_PI/180.f,glm::vec3(0.,0.,1.));
    glm::mat4 model = glm::translate(glm::scale(glm::mat4(1),glm::vec3(scale)), origin);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "rotz"), 1, GL_FALSE, glm::value_ptr(rotz));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "rotx"), 1, GL_FALSE, glm::value_ptr(rotx));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "temprotx"), 1, GL_FALSE, glm::value_ptr(temprotx));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "roty"), 1, GL_FALSE, glm::value_ptr(roty));

    const glm::vec3 col = color; 
    glUniform3f(glGetUniformLocation(m_program, "col"), col[0], col[1], col[2]);

    const glm::vec3 l = lighting;
    glUniform3f(glGetUniformLocation(m_program, "lighting"), l[0], l[1], l[2]);

    const glm::vec3 lcolor = lcolor;
    glUniform3f(glGetUniformLocation(m_program, "lcolor"), lcolor[0], lcolor[1], lcolor[2]);
    body->render();
}

// void Stellar::update(const float currentTimeInSec){
//     float dt = currentTimeInSec-time;
//     s_o += dt*s_os*M_PI;
//     setOrigin(glm::vec3(spheric2cartx(20.,s_o,0.),spheric2carty(20.,e_o,0.),spheric2cartz(20.,e_o,0.)));
//     glm::vec3 o = items[1]->getOrigin();
//     items[1]->setLighting(items[0]->getOrigin()-o);
//     items[2]->setOrigin(glm::vec3(2*o.x+spheric2cartx(8.,m_o,0.),2*o.y+spheric2carty(8.,m_o,0.),2*o.z+spheric2cartz(8.,m_o,0.)));
//     items[2]->setLighting(items[0]->getOrigin()-items[2]->getOrigin());
//     previousTime = currentTimeInSec;
//     for (auto& item : items){
//         item->setTime(currentTimeInSec);
//     }
// }