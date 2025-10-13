#version 330 core            // Minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal; // Now, the 2nd input attribute is the vertex normal.
out vec3 fNormal;
out vec3 fPosition;
out vec3 coords;
out vec4 fPositionE;

uniform mat4 model, viewMat, projMat;

void main() {   
        gl_Position = model*projMat*viewMat*vec4(vPosition, 1.0); // mandatory to rasterize properly
        // fPositionE = model*projMat*viewMat*vec4(vPosition, 1.0);
        fNormal=vNormal;
        fPosition=vPosition;
}
