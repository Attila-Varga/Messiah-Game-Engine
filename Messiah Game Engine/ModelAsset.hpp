//
//  Asset.hpp
//  Game Editor
//
//  Created by Attila Varga on 03/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef ModelAsset_hpp
#define ModelAsset_hpp

#include "OpenGL/gl3.h"
#include "glm/glm.hpp"

#include "Program.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "MeshLoader.hpp"

namespace DMGS
{
    class ModelAsset
    {
    public:
        ModelAsset();
        ModelAsset(const char* filename);
        
        void setShaderProgram(DMGS::Program* shaderProgram);
        void setTexture(DMGS::Texture* pTexture);
        
        Program* loadShaders(const char* vertexFilename, const char* fragmentFilename);
        
        //create the object
        void create();
        void createPlane();
        
        //the main render function
        void render(DMGS::Camera* cam);
        
        //render mesh from file
        void drawMesh(DMGS::Camera* cam);
        
        void setTransformation(glm::mat4 _transformation);
        
        void translate(float x, float y, float z);
        void translate(glm::vec3 _pos);
        void scale(float x, float y, float z);
        void scale(glm::vec3 _scale);
        void rotate(float degree, glm::vec3 axis);
        
        GLuint vbo;
        GLuint vao;
        GLenum drawType;
        GLint drawStart;
        
        GLint drawCount;
       
        //getters
        DMGS::Program* getShader() const { return shaders; }
        DMGS::Texture* getTexture() const { return texture; }
    private:
        DMGS::Program* shaders;
         DMGS::Texture* texture;
        
        glm::mat4 transformation;
        
        MeshLoader* mesh;
    protected:
    };
}

#endif /* ModelAsset_hpp */
