//
//  SceneNode.cpp
//  Game Editor
//
//  Created by Attila Varga on 12/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "SceneNode.hpp"

DMGS::SceneNode::SceneNode()
{
    mName               = std::string();
    mNumberOfChildren   = 0;
    renderable          = false;
    orientation         = glm::mat4();
    upVector            = 0.0f;
    rightVector         = 0.0f;
}

DMGS::SceneNode::SceneNode(std::string pName)
{
    mName               = pName;
    mNumberOfChildren   = 0;
    renderable          = false;
    orientation         = glm::mat4();
    upVector            = 0.0f;
    rightVector         = 0.0f;
}

DMGS::SceneNode::~SceneNode()
{
    mChildrenList.empty();
    
    //delete pointer only
    if(parent)
        delete parent;
}

void DMGS::SceneNode::addChild(SceneNode* child)
{
    mNumberOfChildren++;
    mChildrenList.push_back(child);
}

bool DMGS::SceneNode::hasChild()
{
    if (mChildrenList.size() > 0)
        return true;
    else
        return false;
}

void DMGS::SceneNode::setPosition(glm::vec3 _position)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = _position.z;
}

void DMGS::SceneNode::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
    
}

void DMGS::SceneNode::setScale(glm::vec3 _scale)
{
    scale.x = _scale.x;
    scale.y = _scale.y;
    scale.z = _scale.z;
}

void DMGS::SceneNode::setScale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;
    
}

void DMGS::SceneNode::rotate(float degree, glm::vec3 axis)
{
    orientation = glm::rotate(glm::mat4(), degree, axis);
}

void DMGS::SceneNode::translate(glm::vec3 direction)
{
    glm::vec4 newDir = glm::vec4(direction,0) * orientation;
    
    position += glm::vec3(newDir) ;
    
}

void DMGS::SceneNode::lookAt(glm::vec3 direction)
{
    
}

void DMGS::SceneNode::render(Camera* cam)
{
    setupTransformation();
    
    //setup transformation then draw
    attachedModel->drawMesh(cam);
}

bool DMGS::SceneNode::drawable()
{
    return renderable;
}
void DMGS::SceneNode::attachGameObject(DMGS::ModelAsset* object)
{
    renderable = true;
    attachedModel = object;
}

void DMGS::SceneNode::setupTransformation()
{
    //create helper matrices to easly multiply them to the final transformation
    
    glm::mat4 _pos = glm::translate(glm::mat4(), position);
    glm::mat4 _scale = glm::scale(glm::mat4(), scale);
    
    
    attachedModel->setTransformation( _pos * orientation *_scale );
}
