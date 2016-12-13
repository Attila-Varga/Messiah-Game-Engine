//
//  SceneGraph.cpp
//  Game Editor
//
//  Created by Attila Varga on 12/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "SceneGraph.hpp"

DMGS::SceneGraph::SceneGraph()
{
    mRootSceneNode = new SceneNode();
}

DMGS::SceneGraph::~SceneGraph()
{
    delete mRootSceneNode;
}

void DMGS::SceneGraph::addSceneNodeToRoot(DMGS::SceneNode *object)
{
    mRootSceneNode->addChild(object);
    
    mNodeList.push_back(object);
}

DMGS::SceneNode* DMGS::SceneGraph::getRootSceneNode() const
{
    return mRootSceneNode;
}

//*************TO DO : REPLACE TO STD::FIND_IF*******************************

DMGS::SceneNode* DMGS::SceneGraph::getSceneNodeByName(std::string name)
{
    //Get a list of all scene nodes in the scene graph
    std::list<SceneNode*> nodeList = getAllSceneNodes();
    
    //create an iterator to access all elements
    std::list<SceneNode*>::const_iterator itr;
    
    //iterate through the nodes
    for(itr = nodeList.begin() ; itr != nodeList.end(); itr++)
    {
       //return it, when found
        if((*itr)->getName() == name)
            return *itr;
    }
    
    return 0;
}

std::list<DMGS::SceneNode*> DMGS::SceneGraph::getAllSceneNodes() const
{
    return mNodeList;
}
