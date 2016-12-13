//
//  DMEngine.hpp
//  Game Editor
//
//  Created by Attila Varga on 27/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef DMEngine_hpp
#define DMEngine_hpp

#include "Common.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "SceneGraph.hpp"
#include "MeshLoader.hpp"

#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"





namespace DMGS
{
    class DMEngine
    {
    public:
        //Initialize the 3D Engine
        void startEngine();
        
        //Load the shaders
        DMGS::Program* loadShaders(const char* vertexFilename, const char* fragmentFilename);
        
        //Load a texture
       // DMGS::Texture* loadTexture(const char* textureFileName);
        
        //Create a triangle
        void createScene();
        
        //Render the scene
        void render(float elapsedTime);
        
        //Update the Scene
        void update(float elapsedTime);
        
        //camera look
        void cameraLook(float x, float y);
        
        //returns the camera object
        Camera* getCamera();
        
        //Render all objects from scenegraph
        void renderQueue();
        
    private:
        //the shader we use
        Program* mShaderProgram;
        
        //the Vertex Array Object
        GLuint mVAO;
        
        //the Vertex Buffer Object
        GLuint mVBO;
        
        //texture object
        Texture *mTexture;
        
        //The camera object
        Camera *mCamera;
        
        //time since last frame
        float mElapsedTime;
        
        //rotation degree test
        GLfloat rotationDegree;
        
        //mouse sensitivity,camera move speed
        float mouseSensitivity;
        float cameraMoveSpeed;
        
        //TODO - remove
        ModelAsset* asset1;
        ModelAsset* asset2;
        
        ModelAsset* model;
        
        MeshLoader* mesh1;
        
        ModelAsset* foodSeeker;
        
        //Scene Graph object
        SceneGraph* mSceneGraph;
        
    protected:
    };
}

#endif /* DMEngine_hpp */
