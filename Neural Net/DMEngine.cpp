//
//  DMEngine.cpp
//  Game Editor
//
//  Created by Attila Varga on 27/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "DMEngine.hpp"

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void DMGS::DMEngine::startEngine()
{
    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    

    mCamera = new Camera();
    rotationDegree = 0.0f;
    
    asset1 = new ModelAsset();
    asset2 = new ModelAsset();
    model = new ModelAsset("duck.fbx");
    model->setTexture(loadTexture("level01groundside.jpg"));
    
    mSceneGraph = new SceneGraph();
    
    ModelAsset* level = new ModelAsset("plane.3ds");
    level->setTexture(loadTexture("level01groundside.jpg"));
    
    ModelAsset *planeAsset = new ModelAsset();
    planeAsset->createPlane();
    
    foodSeeker = new ModelAsset("plane.3ds");
    foodSeeker->setTexture(loadTexture("wooden-crate.jpg"));
    
    SceneNode* model1Node = new SceneNode();

    SceneNode* model2Node = new SceneNode();
    SceneNode* planeNode = new SceneNode();
   
    
    model1Node->attachGameObject(level);
    model1Node->setPosition(0, 0, 0);
    model1Node->setScale(10,10,0.01);
    
   // model2Node->attachGameObject(spider);
    //model2Node->setPosition(-3,-1,-6);
   // model2Node->setScale(10, 10, 10);
    
    for (int i = 0; i < 10 ; i++)
    {
        SceneNode* foodSeekers = new SceneNode(std::to_string(i));
        foodSeekers->attachGameObject(foodSeeker);
        
        foodSeekers->setPosition(-i*2,i*2,0);
        foodSeekers->setScale(1,1,1);
        mSceneGraph->addSceneNodeToRoot(foodSeekers);
    }
    
    SceneNode* tmpObj = mSceneGraph->getSceneNodeByName("3");
    
    tmpObj->rotate(10, glm::vec3(0,0,1));
    
    planeNode->attachGameObject(planeAsset);
    planeNode->setPosition(0,3,3);
    planeNode->setScale(1,1,1);
    
    mSceneGraph->addSceneNodeToRoot(model1Node);
    mSceneGraph->addSceneNodeToRoot(model2Node);
    //mSceneGraph->addSceneNodeToRoot(planeNode);
}


void DMGS::DMEngine::createScene()
{
    asset1->create();
    
    
    
    // setup gCamera
    mCamera->setPosition(glm::vec3(0,2,32));
    mCamera->setViewportAspectRatio(800/600);
}

void DMGS::DMEngine::render(float elapsedTime)
{
    mElapsedTime = elapsedTime;
    
    update(mElapsedTime);
    
    // clear everything
    glClearColor(0.7, 0.7, 0.7, 1); // grey
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    asset1->render(mCamera);
    //asset2->render(mCamera);
    
   // model->drawMesh(mCamera);
    
    //foodSeeker->rotate(2, glm::vec3(0,1,0));
    
    renderQueue();
}

void DMGS::DMEngine::update(float elapsedTime)
{
    const GLfloat degreesPerSecond = 180.0f;
    rotationDegree += elapsedTime * degreesPerSecond;
    //if(rotationDegree > 360.0f) rotationDegree -= 360.0f;
    
    SceneNode* tmpObj = mSceneGraph->getSceneNodeByName("3");
    
    //tmpObj->rotate(rotationDegree * 0.01, glm::vec3(0,0,1));
    
    glm::vec4 forward = glm::inverse(tmpObj->getOrientation()) * glm::vec4(0,1,0,1);
    glm::normalize(forward);
    
    tmpObj->translate(glm::vec3(0,1,0) * glm::vec3(forward) * 0.04f);
    
    mCamera->update(elapsedTime);
}

void DMGS::DMEngine::cameraLook(float x, float y)
{
    mouseSensitivity = 4.0f;
    
    mCamera->offsetOrientation(mouseSensitivity * y * mElapsedTime, mouseSensitivity * x * mElapsedTime);
}

DMGS::Camera* DMGS::DMEngine::getCamera()
{
    return mCamera;
}

void DMGS::DMEngine::renderQueue()
{
    //Get a list of all scene nodes in the scene graph
    std::list<SceneNode*> nodeList = mSceneGraph->getAllSceneNodes();
    
    //create an iterator to access all elements
    std::list<SceneNode*>::const_iterator itr;
    
    //iterate through the nodes
    for(itr = nodeList.begin() ; itr != nodeList.end(); itr++)
    {
        //render it, if drawable object
        if((*itr)->drawable())
            (*itr)->render(mCamera);
    }
}
