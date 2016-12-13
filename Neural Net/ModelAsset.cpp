//
//  Asset.cpp
//  Game Editor
//
//  Created by Attila Varga on 03/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "ModelAsset.hpp"
#include "glm/gtc/matrix_transform.hpp"

DMGS::ModelAsset::ModelAsset() :
    shaders(NULL),
    texture(NULL),
    vbo(0),
    vao(0),
    drawType(GL_TRIANGLES),
    drawStart(0),
    drawCount(0)
{
    transformation = glm::mat4();
}

DMGS::ModelAsset::ModelAsset(const char* filename) :
    shaders(NULL),
    texture(NULL),
    vbo(0),
    vao(0),
    drawType(GL_TRIANGLES),
    drawStart(0),
drawCount(0)
{
    setShaderProgram(loadShaders("vertex-shader.vsh", "fragment-shader.fsh"));
    
    //setTexture(loadTexture("dwarf2.jpg"));
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("vertex"));
    glVertexAttribPointer(shaders->attrib("vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("UV"));
    glVertexAttribPointer(shaders->attrib("UV"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    // unbind the VAO
    glBindVertexArray(0);
    
    mesh = new MeshLoader(filename);
    
    translate(0,0,0);
    scale(1,1,1);
}

DMGS::Program* DMGS::ModelAsset::loadShaders(const char* vertexFilename, const char* fragmentFilename)
{
    std::vector<DMGS::Shader> shaders;
    
    shaders.push_back(DMGS::Shader::shaderFromFile(ResourcePath(vertexFilename), GL_VERTEX_SHADER));
    shaders.push_back(DMGS::Shader::shaderFromFile(ResourcePath(fragmentFilename), GL_FRAGMENT_SHADER));
    
    //Todo : remove mShaderProgram, create multiple instances for modelassets
    
    return new DMGS::Program(shaders);
}

void DMGS::ModelAsset::setShaderProgram(DMGS::Program* shaderProgram)
{
    shaders = shaderProgram;
}

void DMGS::ModelAsset::setTexture(DMGS::Texture *pTexture)
{
    texture = pTexture;
}

void DMGS::ModelAsset::create()
{
    setShaderProgram(loadShaders("vertex-shader.vsh", "fragment-shader.fsh"));
    drawType = GL_TRIANGLES;
    drawStart = 0;
    drawCount = 6*2*3;
    setTexture(loadTexture("wooden-crate.jpg"));
    
    // make and bind the VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // make and bind the VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // Make a cube out of triangles (two triangles per side)
    GLfloat vertexData[] = {
        //  X     Y     Z       U     V
        // bottom
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        
        // top
        -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        
        // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        
        // back
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
        
        // left
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        
        // right
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("vertex"));
    glVertexAttribPointer(shaders->attrib("vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("UV"));
    glVertexAttribPointer(shaders->attrib("UV"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    // unbind the VAO
    glBindVertexArray(0);
}

void DMGS::ModelAsset::createPlane()
{
    setShaderProgram(loadShaders("vertex-shader.vsh", "fragment-shader.fsh"));
    drawType = GL_TRIANGLES;
    drawStart = 0;
    drawCount = 2*3;
    setTexture(loadTexture("wooden-crate.jpg"));
    
    // make and bind the VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // make and bind the VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    // Make a cube out of triangles (two triangles per side)
    GLfloat vertexData[] = {
        //  X     Y     Z       U     V
        
        // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        
     
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("vertex"));
    glVertexAttribPointer(shaders->attrib("vertex"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(shaders->attrib("UV"));
    glVertexAttribPointer(shaders->attrib("UV"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    
    // unbind the VAO
    glBindVertexArray(0);
}


void DMGS::ModelAsset::render(DMGS::Camera* cam)
{
    
    shaders->use();
    shaders->setUniform("camera", cam->matrix());
    shaders->setUniform("model", transformation);
    shaders->setUniform("tex",0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->object());
    
    glBindVertexArray(vao);
    glDrawArrays(drawType, drawStart, drawCount);
    
    //mesh->draw(shaders->object());
    shaders->stopUsing();
}

void DMGS::ModelAsset::translate(float x, float y, float z)
{
    transformation = glm::translate(glm::mat4(),glm::vec3(x,y,z));
}

void DMGS::ModelAsset::translate(glm::vec3 _pos)
{
    transformation = glm::translate(glm::mat4(),_pos);
}
void DMGS::ModelAsset::scale(float x, float y, float z)
{
    transformation = glm::scale(glm::mat4(),glm::vec3(x,y,z));
}

void DMGS::ModelAsset::scale(glm::vec3 _scale)
{
    transformation = glm::scale(glm::mat4(),_scale);
}

void DMGS::ModelAsset::rotate(float degree, glm::vec3 axis)
{
    transformation = glm::rotate(glm::mat4(), glm::radians(degree), axis);
}
void DMGS::ModelAsset::drawMesh(DMGS::Camera* cam)
{
    shaders->use();
    shaders->setUniform("camera", cam->matrix());
    shaders->setUniform("model", transformation);
    shaders->setUniform("tex",0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->object());
    
    mesh->draw(shaders->object());
    
    shaders->stopUsing();
}

void DMGS::ModelAsset::setTransformation(glm::mat4 _transformation)
{
    transformation = _transformation;
}
