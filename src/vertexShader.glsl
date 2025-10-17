#version 330 core            // Minimal GL version support expected from the GPU

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal; // Now, the 2nd input attribute is the vertex normal.
layout(location=2) in vec2 vertexTexCoord;
out vec3 fNormal;
out vec3 fPosition;
out vec3 coords;
out vec4 fPositionE;
out vec2 fragmentTexCoord;

uniform mat4 model, viewMat, projMat;

void main() {   
        gl_Position = projMat*viewMat*model*vec4(vPosition, 1.0); // mandatory to rasterize properly
        // fPositionE = model*projMat*viewMat*vec4(vPosition, 1.0);
        fNormal=vNormal;
        fPosition=vPosition;
        fragmentTexCoord=vertexTexCoord;
}
